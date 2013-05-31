/* ======================================================================
** luagutl.c - Copyright (C) 2005-2006 Varol Kaptan
** see LICENSE for more information
** ======================================================================
** vim: set ts=3 et: */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(USE_OPENGLUT)
 #include <GL/openglut.h>
 #include <GL/openglut_exp.h>
#elif defined(USE_OPENGLEAN)
 #include <GL/openglean.h>
 #include <GL/openglean_exp.h>
#elif defined(USE_FREEGLUT)
 #include <GL/freeglut.h>
#elif defined(__APPLE__) && defined(__MACH__)
 #include <GLUT/glut.h>
#else
 #include <GL/glut.h>
#endif

#include <lua.h>
#include <lauxlib.h>
#include <assert.h>
#include "macros.h"

#include "menus.h"

#define MYNAME "luaglut"
#define VERSION "0.5"

static lua_State *ref_L = NULL;

LUA_API int LglutInit(lua_State *L)
{
   int argc, i;
   char **argv;

   assert(L == ref_L);

   if ( (lua_gettop(L) == 0) || lua_isnil(L, -1)) {
      argc = 0;
      argv = NULL;
   } else {
      luaL_checktype(L, -1, LUA_TTABLE);

      argc = (int) luaL_getn(L, -1) + 1;
      argv = (char **) malloc( (argc) * sizeof(char *) );

      for (i = 0; i < argc; ++i) {
         lua_rawgeti(L, -1, i);
         if (lua_type(L, -1) == LUA_TSTRING) {
            argv[i] = (char *) malloc(lua_strlen(L, -1) + 1);
            strcpy(argv[i], lua_tostring(L, -1));
         } else {
            argv[i] = (char *) malloc(1);
            argv[i][0] = '\0';
         }
         lua_pop(L, 1);
      }
   }

   glutInit(&argc, argv);

   return 0;
   // small memory leak, but it is ok for now
   // will deal with this later
}

/* ======================================================================
   The following three functions are used for book-keeping of window
   creation, destruction and callback dispatch. The information is kept
   on the Lua side in the global table 'luaglut.window'
   ====================================================================== */

/*
   alloc_wintable(): This function allocates a table (luaglut.window[id])
   and populates it like this: { parent = parent, children = {} }. It also
   adds the id in luaglut.window[parent].children .
*/

static void alloc_wintable(lua_State *L, int id, int parent)
{
   if (id > 0) {
      /* get global 'luaglut' */
      lua_pushstring(L, "luaglut");
      lua_gettable(L, LUA_GLOBALSINDEX);

      /* get luaglut.window */
      lua_pushstring(L, "window");
      lua_gettable(L, -2);

      /* put id in parent's list of children */
      if (parent > 0) {
         /* get luaglut.window[parent] */
         lua_pushnumber(L, parent);
         lua_gettable(L, -2);

         /* get .children */
         lua_pushstring(L, "children");
         lua_gettable(L, -2);

         /* add id to .children */
         lua_pushnumber(L, id);
         lua_rawseti(L, -2, id);
         /* remove children and window[parent] */
         lua_pop(L, 2);
      }

      /* push id and create a new_table */
      lua_pushnumber(L, id);
      lua_newtable(L);

      /* record parent, if any */
      if (parent > 0) {
         /* new_table.parent = parent_id */
         lua_pushstring(L, "parent");
         lua_pushnumber(L, parent);
         lua_settable(L, -3);
      }

      /* new_table.children = table */
      lua_pushstring(L, "children");
      lua_newtable(L);
      lua_settable(L, -3);

      /* luaglut.window[id] = new_table */
      lua_settable(L, -3);

      /* remove luaglut.window and luaglut */
      lua_pop(L, 2);

   } else {
      luaL_error(L, "luaglut:alloc_wintable(%d) - invalid window id\n", id);
   }
}

/*
   dealloc_wintable(): This function will remove luaglut.window[id] and
   all it's children windows. It will also remove id from the table containing
   all the children of its parent.
*/

static void dealloc_wintable(lua_State *L, int id)
{
   int child;

   if (id > 0) {
      /* get global 'luaglut' */
      lua_pushstring(L, "luaglut");
      lua_gettable(L, LUA_GLOBALSINDEX);

      /* get luaglut.window */
      lua_pushstring(L, "window");
      lua_gettable(L, -2);

      /* get luaglut.window[id] */
      lua_pushnumber(L, id);
      lua_gettable(L, -2);

      if (lua_type(L, -1) != LUA_TTABLE)
         luaL_error(L, "luaglut:dealloc_wintable(%d) - unknown window id\n", id);

      /* get .children */
      lua_pushstring(L, "children");
      lua_gettable(L, -2);

      /* clear all the children here */
      lua_pushnil(L);
      while (lua_next(L, -2) != 0) {
         child = luaL_checknumber(L, -1);
         dealloc_wintable(L, child);
      }

      /* pop .children */
      lua_pop(L, 1);

      /* get window[id].parent */
      lua_pushstring(L, "parent");
      lua_gettable(L, -2);
      /* pop window[id], keep parent */
      lua_replace(L, -2);

      if (!lua_isnil(L, -1)) {
         /* get window[parent] */
         lua_gettable(L, -2);
         /* get window[parent].children */
         lua_pushstring(L, "children");
         lua_gettable(L, -2);
         /* pop window[parent], keep children */
         lua_replace(L, -2);
         /* remove id from children */
         lua_pushnil(L);
         lua_rawseti(L, -2, id);
      }

      /* pop [children|nil] */
      lua_pop(L, 1);

      /* window[id] = nil */
      lua_pushnil(L);
      lua_rawseti(L, -2, id);

      /* remove window, luaglut */
      lua_pop(L, 2);

   } else {
      luaL_error(L, "luaglut:dealloc_wintable(%d) - invalid window id\n", id);
   }
}

/*
   get_wintable(): Puts luaglut.window[glutGetWindow()] on the top of
   the stack. Will issue an error if there is no current glut window or if
   window id is not reflected in luaglut (i.e. result of the operation should
   be a table).
*/
static void get_wintable(lua_State *L)
{
   int id = glutGetWindow();

   if (id > 0) {
      lua_pushstring(L, "luaglut");
      lua_gettable(L, LUA_GLOBALSINDEX);
      lua_pushstring(L, "window");
      lua_gettable(L, -2);
      lua_pushnumber(L, id);
      lua_gettable(L, -2);

      if (lua_type(L, -1) != LUA_TTABLE) {
         luaL_error(L, "luaglut:get_wintable(%d) - unknown window id\n", id);
      }

      lua_replace(L, -3);
      lua_pop(L, 1);

   } else {
      luaL_error(L, "luaglut:get_wintable(%d) - no active glut window\n");
   }
}

/* ======================================================================
   Here is the window management API:
   glutCreateWindow
   glutCreateSubWindow
   glutDestroyWindow
      OPENGLEAN
      glutCreateMenuWindow
   ====================================================================== */

LUA_API int LglutCreateWindow(lua_State *L)
{
   const char * name = check_string(L, 1);
   int id = glutCreateWindow(name);
   alloc_wintable(L, id, 0);
   lua_pushnumber(L, id);
   return 1;
}

LUA_API int LglutCreateSubWindow(lua_State *L)
{
   int win    = check_int(L, 1);
   int x      = check_int(L, 2);
   int y      = check_int(L, 3);
   int width  = check_int(L, 4);
   int height = check_int(L, 5);
   int id     = glutCreateSubWindow(win, x, y, width, height);

   alloc_wintable(L, id, win);
   lua_pushnumber(L, id);
   return 1;
}

LUA_API int LglutDestroyWindow(lua_State *L)
{
   int id = check_int(L, 1);

   glutDestroyWindow(id);
   dealloc_wintable(L, id);
   return 0;
}

#if defined(USE_OPENGLEAN)
LUA_API int LglutCreateMenuWindow(lua_State *L)
{
   int win    = check_int(L, 1);
   int x      = check_int(L, 2);
   int y      = check_int(L, 3);
   int width  = check_int(L, 4);
   int height = check_int(L, 5);
   int id     = glutCreateMenuWindow(win, x, y, width, height);

   alloc_wintable(L, id, win);
   lua_pushnumber(L, id);
   return 1;
}
#endif

/* =====================================================================
   callback registration and implementation
   ===================================================================== */

#define IMPLEMENT_WINCALLBACK_v(name)\
void name ## _func(void)\
{\
   get_wintable(ref_L);\
   lua_pushstring(ref_L, #name "_func");\
   lua_gettable(ref_L, -2);\
   lua_call(ref_L, 0, 0);\
}

#define IMPLEMENT_WINCALLBACK_i2(name)\
void name ## _func(int a1, int a2)\
{\
   get_wintable(ref_L);\
   lua_pushstring(ref_L, #name "_func");\
   lua_gettable(ref_L, -2);\
   lua_pushnumber(ref_L, (lua_Number) a1);\
   lua_pushnumber(ref_L, (lua_Number) a2);\
   lua_call(ref_L, 2, 0);\
}

#define IMPLEMENT_WINCALLBACK_uci2(name)\
void name ## _func(unsigned char a1, int a2, int a3)\
{\
   get_wintable(ref_L);\
   lua_pushstring(ref_L, #name "_func");\
   lua_gettable(ref_L, -2);\
   lua_pushnumber(ref_L, (lua_Number) a1);\
   lua_pushnumber(ref_L, (lua_Number) a2);\
   lua_pushnumber(ref_L, (lua_Number) a3);\
   lua_call(ref_L, 3, 0);\
}

#define IMPLEMENT_WINCALLBACK_i3(name)\
void name ## _func(int a1, int a2, int a3)\
{\
   get_wintable(ref_L);\
   lua_pushstring(ref_L, #name "_func");\
   lua_gettable(ref_L, -2);\
   lua_pushnumber(ref_L, (lua_Number) a1);\
   lua_pushnumber(ref_L, (lua_Number) a2);\
   lua_pushnumber(ref_L, (lua_Number) a3);\
   lua_call(ref_L, 3, 0);\
}

#define IMPLEMENT_WINCALLBACK_i4(name)\
void name ## _func(int a1, int a2, int a3, int a4)\
{\
   get_wintable(ref_L);\
   lua_pushstring(ref_L, #name "_func");\
   lua_gettable(ref_L, -2);\
   lua_pushnumber(ref_L, (lua_Number) a1);\
   lua_pushnumber(ref_L, (lua_Number) a2);\
   lua_pushnumber(ref_L, (lua_Number) a3);\
   lua_pushnumber(ref_L, (lua_Number) a4);\
   lua_call(ref_L, 4, 0);\
}

#define IMPLEMENT_SETWINCALLBACK(Name, name)\
LUA_API int Lglut ## Name ## Func(lua_State *L)\
{\
   assert(L == ref_L);\
   get_wintable(L);\
   lua_pushstring(L, #name "_func");\
   lua_pushvalue(L, -3);\
   lua_settable(L, -3);\
   glut ## Name ## Func( lua_isnil(L, -1) ? NULL : name ## _func);\
   return 0;\
}

IMPLEMENT_WINCALLBACK_v    ( display         )
IMPLEMENT_WINCALLBACK_v    ( overlaydisplay  )
IMPLEMENT_WINCALLBACK_uci2 ( keyboard        )
IMPLEMENT_WINCALLBACK_i3   ( special         )
IMPLEMENT_WINCALLBACK_i2   ( reshape         )
IMPLEMENT_WINCALLBACK_i4   ( mouse           )
IMPLEMENT_WINCALLBACK_i2   ( motion          )
IMPLEMENT_WINCALLBACK_i2   ( passivemotion   )

IMPLEMENT_SETWINCALLBACK ( Display,          display           )
IMPLEMENT_SETWINCALLBACK ( OverlayDisplay,   overlaydisplay    )
IMPLEMENT_SETWINCALLBACK ( Keyboard,         keyboard          )
IMPLEMENT_SETWINCALLBACK ( Special,          special           )
IMPLEMENT_SETWINCALLBACK ( Reshape,          reshape           )
IMPLEMENT_SETWINCALLBACK ( Mouse,            mouse             )
IMPLEMENT_SETWINCALLBACK ( Motion,           motion            )
IMPLEMENT_SETWINCALLBACK ( PassiveMotion,    passivemotion     )

/* ======================================================================
   Here is the idle function implementation. The lua callback functioin
   is stored in luaglut.idle_func on the Lua side.
   ====================================================================== */

void idle_func(void)
{
   lua_pushstring(ref_L, "luaglut");
   lua_gettable(ref_L, LUA_GLOBALSINDEX);
   lua_pushstring(ref_L, "idle_func");
   lua_gettable(ref_L, -2);
   lua_call(ref_L, 0, 0);
}


LUA_API int LglutIdleFunc(lua_State *L)
{
   assert(L == ref_L);
   lua_pushstring(L, "luaglut");
   lua_gettable(L, LUA_GLOBALSINDEX);
   lua_pushstring(L, "idle_func");
   lua_pushvalue(L, -3);
   lua_settable(L, -3);
   glutIdleFunc( lua_isnil(L, -1) ? NULL : idle_func);
   return 0;
}

/* ======================================================================
   Here is the timer implementation. Timer callback setup and dispatch
   are implemented in C.
   ====================================================================== */

void timer_func(int index)
{
   /* get luaglut */
   lua_pushstring(ref_L, "luaglut");
   lua_gettable(ref_L, LUA_GLOBALSINDEX);

   /* get luaglut.timer */
   lua_pushstring(ref_L, "timer");
   lua_gettable(ref_L, -2);

   /* get luaglut.timer.values */
   lua_pushstring(ref_L, "values");
   lua_gettable(ref_L, -2);

   /* get timer[index] */
   lua_rawgeti(ref_L, -2, index);

   /* get timer.values[index] */
   lua_rawgeti(ref_L, -2, index);

   /* make the call */
   lua_call(ref_L, 1, 0);

   /* set timer[index] = next_free */
   lua_pushnumber(ref_L, index);
   lua_pushstring(ref_L, "next_free");
   lua_gettable(ref_L, -4);
   lua_settable(ref_L, -4);

   /* set timer.next_free = index */
   lua_pushstring(ref_L, "next_free");
   lua_pushnumber(ref_L, index);
   lua_settable(ref_L, -4);
}


LUA_API int LglutTimerFunc(lua_State *L)
{
   unsigned int msec;
   int value;
   int next_free, new_next_free;
   int index;

   assert(L == ref_L);

   msec = (unsigned int) check_int(L, -3);
   value = check_int(L, -1);

   /* get luaglut */
   lua_pushstring(L, "luaglut");
   lua_gettable(L, LUA_GLOBALSINDEX);

   /* get luaglut.timer */
   lua_pushstring(L, "timer");
   lua_gettable(L, -2);

   /* get luaglut.timer.values */
   lua_pushstring(L, "values");
   lua_gettable(L, -2);

   /* get luaglut.timer.next_free */
   lua_pushstring(L, "next_free");
   lua_gettable(L, -3);
   next_free = luaL_checknumber(L, -1);

   if (next_free < 0) {
      /* no more free? abs(next_free) == size */

      /* timer[-next_free] = func*/
      lua_pushvalue(L, -6);
      lua_rawseti(L, -4, -next_free);

      /* timer.values[-next_free] = value */
      lua_pushvalue(L, -5);
      lua_rawseti(L, -3, -next_free);

      /* next_free = next_free -1 */
      lua_pushstring(L, "next_free");
      lua_pushnumber(L, next_free - 1);
      lua_rawset(L, -5);

      index = -next_free;

   } else {
      /* can reuse some index */

      /* get timer[next_free], i.e. our new_next_free */
      lua_rawgeti(L, -3, next_free);
      new_next_free = luaL_checknumber(L, -1);

      /* set timer[next_free] = func */
      lua_pushvalue(L, -7);
      lua_rawseti(L, -5, next_free);

      /* next_free = new_next_free */
      lua_pushstring(L, "next_free");
      lua_pushnumber(L, new_next_free);
      lua_rawset(L, -6);

      /* values[next_free] = value */
      lua_pushnumber(L, value);
      lua_rawseti(L, -4, next_free);

      index = next_free;
   }

   glutTimerFunc(msec, timer_func, index);
   return 0;
}

/* ====================================================================== */
/* Most of the real menu subsystem is in the lua space. Only stuff        */
/* related to the menu callback is here. Check menus.lua for the details  */
/* ====================================================================== */

void menu_func(int value)
{
   lua_pushstring(ref_L, "luaglut");
   lua_gettable(ref_L, LUA_GLOBALSINDEX);

   lua_pushstring(ref_L, "menu");
   lua_gettable(ref_L, -2);

   lua_pushstring(ref_L, "uidmap");
   lua_gettable(ref_L, -2);

   lua_pushnumber(ref_L, value);
   lua_gettable(ref_L, -2);

   if (lua_type(ref_L, -1) == LUA_TTABLE) {
      lua_pushstring(ref_L, "callback");
      lua_rawget(ref_L, -2);

      lua_pushstring(ref_L, "value");
      lua_rawget(ref_L, -3);

      /* if the value is a function, then we will call the function rather
         than the callback with parameter value */
      if (lua_type(ref_L, -1) == LUA_TFUNCTION)
         lua_call(ref_L, 0, 0);
      else
         lua_call(ref_L, 1, 0);
   } else {
      luaL_error(ref_L, "luaglut:menu_callback(%d) - unknown uid\n", value);
   }
}


LUA_API int LglutCreateMenu(lua_State *L)
{
   lua_pushnumber(L, (lua_Number) glutCreateMenu(menu_func));
   return 1;
}


/* ====================================================================== */
/* This is the GLUT API                                                   */
/* ====================================================================== */
/* from http://www.opengl.org/resources/libraries/glut/spec3/spec3.html   */

/* 2. Initialization */
   FUN_SPEC (glutInit)
   FUN_vi2  (glutInitWindowSize)
   FUN_vi2  (glutInitWindowPosition)
   FUN_vui  (glutInitDisplayMode)

/* 3. Event Processing */
   FUN_v    (glutMainLoop)

/* 4. Window Management */
   FUN_SPEC (glutCreateWindow)
   FUN_SPEC (glutCreateSubWindow)
   FUN_vi   (glutSetWindow)
   FUN_i    (glutGetWindow)
   FUN_SPEC (glutDestroyWindow)
   FUN_v    (glutPostRedisplay)
   FUN_v    (glutSwapBuffers)
   FUN_vi2  (glutPositionWindow)
   FUN_vi2  (glutReshapeWindow)
   FUN_v    (glutFullScreen)
   FUN_v    (glutPopWindow)
   FUN_v    (glutPushWindow)
   FUN_v    (glutShowWindow)
   FUN_v    (glutHideWindow)
   FUN_v    (glutIconifyWindow)
   FUN_vs   (glutSetWindowTitle)
   FUN_vs   (glutSetIconTitle)
   FUN_vi   (glutSetCursor)

/* 5. Overlay Management */
   FUN_v    (glutEstablishOverlay)
   FUN_vE   (glutUseLayer)
   FUN_v    (glutRemoveOverlay)
   FUN_v    (glutPostOverlayRedisplay)
   FUN_v    (glutShowOverlay)
   FUN_v    (glutHideOverlay)

/* 6. Menu Management */
   FUN_SPEC (glutCreateMenu)
   FUN_vi   (glutSetMenu)
   FUN_i    (glutGetMenu)
   FUN_vi   (glutDestroyMenu)
   FUN_vsi  (glutAddMenuEntry)
   FUN_vsi  (glutAddSubMenu)
   FUN_visi (glutChangeToMenuEntry)
   FUN_visi (glutChangeToSubMenu)
   FUN_vi   (glutRemoveMenuItem)
   FUN_vi   (glutAttachMenu)
   FUN_vi   (glutDetachMenu)

/* 7. Callback Registration */
   FUN_SPEC (glutDisplayFunc)
   FUN_SPEC (glutOverlayDisplayFunc)
   FUN_SPEC (glutReshapeFunc)
   FUN_SPEC (glutKeyboardFunc)
   FUN_SPEC (glutMouseFunc)
   FUN_SPEC (glutMotionFunc)
   FUN_SPEC (glutPassiveMotionFunc)
   FUN_SPEC (glutSpecialFunc)
   FUN_SPEC (glutIdleFunc)
   FUN_SPEC (glutTimerFunc)
   /* implemented [+]:
       + glutDisplayFunc
       + glutOverlayDisplayFunc
       + glutReshapeFunc
       + glutKeyboardFunc
       + glutMouseFunc
       + glutMotionFunc
       + glutPassiveMotionFunc
         glutVisibilityFunc
         glutEntryFunc
       + glutSpecialFunc
         glutSpaceballMotionFunc
         glutSpaceballRotateFunc
         glutSpaceballButtonFunc
         glutButtonBoxFunc
         glutDialsFunc
         glutTabletMotionFunc
         glutTabletButtonFunc
         glutMenuStatusFunc
       + glutIdleFunc
       + glutTimerFunc */

/* 8. Colormap Management */
   FUN_viF3 (glutSetColor)
   FUN_Fi2  (glutGetColor)
   FUN_vi   (glutCopyColormap)

/* 9. State Retrieval */
   FUN_iE   (glutGet)
   FUN_iE   (glutLayerGet )
   FUN_iE   (glutDeviceGet)
   FUN_i    (glutGetModifiers)
   FUN_is   (glutExtensionSupported)

/* 10. Font Rendering */
   FUN_vpi  (glutBitmapCharacter)
   FUN_ipi  (glutBitmapWidth)
   FUN_vpi  (glutStrokeCharacter)
   FUN_ipi  (glutStrokeWidth)

/* 11. Geometric Object Rendering */
   FUN_vDI2 (glutSolidSphere)
   FUN_vDI2 (glutWireSphere)
   FUN_vD   (glutSolidCube)
   FUN_vD   (glutWireCube)
   FUN_vD2I2(glutSolidCone)
   FUN_vD2I2(glutWireCone)
   FUN_vD2I2(glutSolidTorus)
   FUN_vD2I2(glutWireTorus)
   FUN_v    (glutSolidDodecahedron)
   FUN_v    (glutWireDodecahedron)
   FUN_v    (glutSolidOctahedron)
   FUN_v    (glutWireOctahedron)
   FUN_v    (glutSolidTetrahedron)
   FUN_v    (glutWireTetrahedron)
   FUN_v    (glutSolidIcosahedron)
   FUN_v    (glutWireIcosahedron)
   FUN_vD   (glutSolidTeapot)
   FUN_vD   (glutWireTeapot)


/* ====================================================================== */
/* These are the FREEGLUT/OPENGLUT/OPENGLEAN extensions                   */
/* ====================================================================== */

   #if defined(USE_OPENGLUT) || defined(USE_OPENGLEAN) || defined (USE_FREEGLUT)
   FUN_ip   (glutBitmapHeight)
   FUN_vps  (glutBitmapString)
   FUN_ip   (glutStrokeHeight)
   FUN_vps  (glutStrokeString)

   FUN_p    (glutGetMenuData)
   FUN_vp   (glutSetMenuData)

   FUN_ps   (glutGetProcAddress)

   FUN_p    (glutGetWindowData)
   FUN_vp   (glutSetWindowData)

   FUN_v    (glutLeaveMainLoop)
   FUN_v    (glutMainLoopEvent)

   FUN_SPEC (glutMenuDestroyFunc)
   FUN_SPEC (glutCloseFunc)
   FUN_SPEC (glutWMCloseFunc)
   FUN_SPEC (glutMouseWheelFunc)
   FUN_SPEC (glutSetOption)

   FUN_vD2I2(glutWireCylinder)
   FUN_v    (glutWireRhombicDodecahedron)
   FUN_vD2I2(glutSolidCylinder)
   FUN_v    (glutSolidRhombicDodecahedron)
   #endif

   #if defined(USE_OPENGLUT) | defined(USE_OPENGLEAN)
   /* really experimental features */
   FUN_SPEC (glutCreateMenuWindow)
   FUN_vI   (glutSetWindowStayOnTop)
   #endif

/* ====================================================================== */
/* This is the GLU API                                                    */
/*   this will eventually go in a separate library (luaglu) but for now   */
/*   it stays here                                                        */
/* ====================================================================== */

   FUN_IEIZE2p (gluBuild1DMipmaps)
   FUN_IEIZ2E2p  (gluBuild2DMipmaps)
   FUN_vD9  (gluLookAt)
   FUN_vD4  (gluOrtho2D)
   FUN_vD4  (gluPerspective)
   FUN_vD4p (gluPickMatrix)
   FUN_iD3p6(gluProject)
   /* gluScaleImage */
   FUN_iD3p6(gluUnProject)


void register_glut(lua_State *L)
{
   /* as extracted from glut.h version 3.7 */

   #if !defined(USE_OPENGLEAN)
   CONSTANT(GLUT_API_VERSION)
   #endif
   /* CONSTANT(GLUT_XLIB_IMPLEMENTATION) not in freeglut <= 2.2.0 */
   CONSTANT(GLUT_RGB)
   CONSTANT(GLUT_RGBA)
   CONSTANT(GLUT_INDEX)
   CONSTANT(GLUT_SINGLE)
   CONSTANT(GLUT_DOUBLE)
   CONSTANT(GLUT_ACCUM)
   CONSTANT(GLUT_ALPHA)
   CONSTANT(GLUT_DEPTH)
   CONSTANT(GLUT_STENCIL)
   CONSTANT(GLUT_MULTISAMPLE)
   CONSTANT(GLUT_STEREO)
   CONSTANT(GLUT_LUMINANCE)
   CONSTANT(GLUT_LEFT_BUTTON)
   CONSTANT(GLUT_MIDDLE_BUTTON)
   CONSTANT(GLUT_RIGHT_BUTTON)
   CONSTANT(GLUT_DOWN)
   CONSTANT(GLUT_UP)
   CONSTANT(GLUT_KEY_F1)
   CONSTANT(GLUT_KEY_F2)
   CONSTANT(GLUT_KEY_F3)
   CONSTANT(GLUT_KEY_F4)
   CONSTANT(GLUT_KEY_F5)
   CONSTANT(GLUT_KEY_F6)
   CONSTANT(GLUT_KEY_F7)
   CONSTANT(GLUT_KEY_F8)
   CONSTANT(GLUT_KEY_F9)
   CONSTANT(GLUT_KEY_F10)
   CONSTANT(GLUT_KEY_F11)
   CONSTANT(GLUT_KEY_F12)
   CONSTANT(GLUT_KEY_LEFT)
   CONSTANT(GLUT_KEY_UP)
   CONSTANT(GLUT_KEY_RIGHT)
   CONSTANT(GLUT_KEY_DOWN)
   CONSTANT(GLUT_KEY_PAGE_UP)
   CONSTANT(GLUT_KEY_PAGE_DOWN)
   CONSTANT(GLUT_KEY_HOME)
   CONSTANT(GLUT_KEY_END)
   CONSTANT(GLUT_KEY_INSERT)
   CONSTANT(GLUT_LEFT)
   CONSTANT(GLUT_ENTERED)
   CONSTANT(GLUT_MENU_NOT_IN_USE)
   CONSTANT(GLUT_MENU_IN_USE)
   CONSTANT(GLUT_NOT_VISIBLE)
   CONSTANT(GLUT_VISIBLE)
   CONSTANT(GLUT_HIDDEN)
   CONSTANT(GLUT_FULLY_RETAINED)
   CONSTANT(GLUT_PARTIALLY_RETAINED)
   CONSTANT(GLUT_FULLY_COVERED)
   CONSTANT(GLUT_RED)
   CONSTANT(GLUT_GREEN)
   CONSTANT(GLUT_BLUE)
   CONSTANT(GLUT_NORMAL)
   CONSTANT(GLUT_OVERLAY)

   POINTER(GLUT_STROKE_ROMAN)
   POINTER(GLUT_STROKE_MONO_ROMAN)
   POINTER(GLUT_BITMAP_9_BY_15)
   POINTER(GLUT_BITMAP_8_BY_13)
   POINTER(GLUT_BITMAP_TIMES_ROMAN_10)
   POINTER(GLUT_BITMAP_TIMES_ROMAN_24)
   POINTER(GLUT_BITMAP_HELVETICA_10)
   POINTER(GLUT_BITMAP_HELVETICA_12)
   POINTER(GLUT_BITMAP_HELVETICA_18)

   CONSTANT(GLUT_WINDOW_X)
   CONSTANT(GLUT_WINDOW_Y)
   CONSTANT(GLUT_WINDOW_WIDTH)
   CONSTANT(GLUT_WINDOW_HEIGHT)
   CONSTANT(GLUT_WINDOW_BUFFER_SIZE)
   CONSTANT(GLUT_WINDOW_STENCIL_SIZE)
   CONSTANT(GLUT_WINDOW_DEPTH_SIZE)
   CONSTANT(GLUT_WINDOW_RED_SIZE)
   CONSTANT(GLUT_WINDOW_GREEN_SIZE)
   CONSTANT(GLUT_WINDOW_BLUE_SIZE)
   CONSTANT(GLUT_WINDOW_ALPHA_SIZE)
   CONSTANT(GLUT_WINDOW_ACCUM_RED_SIZE)
   CONSTANT(GLUT_WINDOW_ACCUM_GREEN_SIZE)
   CONSTANT(GLUT_WINDOW_ACCUM_BLUE_SIZE)
   CONSTANT(GLUT_WINDOW_ACCUM_ALPHA_SIZE)
   CONSTANT(GLUT_WINDOW_DOUBLEBUFFER)
   CONSTANT(GLUT_WINDOW_RGBA)
   CONSTANT(GLUT_WINDOW_PARENT)
   CONSTANT(GLUT_WINDOW_NUM_CHILDREN)
   CONSTANT(GLUT_WINDOW_COLORMAP_SIZE)
   CONSTANT(GLUT_WINDOW_NUM_SAMPLES)
   CONSTANT(GLUT_WINDOW_STEREO)
   CONSTANT(GLUT_WINDOW_CURSOR)
   CONSTANT(GLUT_SCREEN_WIDTH)
   CONSTANT(GLUT_SCREEN_HEIGHT)
   CONSTANT(GLUT_SCREEN_WIDTH_MM)
   CONSTANT(GLUT_SCREEN_HEIGHT_MM)
   CONSTANT(GLUT_MENU_NUM_ITEMS)
   CONSTANT(GLUT_DISPLAY_MODE_POSSIBLE)
   CONSTANT(GLUT_INIT_WINDOW_X)
   CONSTANT(GLUT_INIT_WINDOW_Y)
   CONSTANT(GLUT_INIT_WINDOW_WIDTH)
   CONSTANT(GLUT_INIT_WINDOW_HEIGHT)
   CONSTANT(GLUT_INIT_DISPLAY_MODE)
   CONSTANT(GLUT_ELAPSED_TIME)
   CONSTANT(GLUT_WINDOW_FORMAT_ID)
   CONSTANT(GLUT_HAS_KEYBOARD)
   CONSTANT(GLUT_HAS_MOUSE)
   CONSTANT(GLUT_HAS_SPACEBALL)
   CONSTANT(GLUT_HAS_DIAL_AND_BUTTON_BOX)
   CONSTANT(GLUT_HAS_TABLET)
   CONSTANT(GLUT_NUM_MOUSE_BUTTONS)
   CONSTANT(GLUT_NUM_SPACEBALL_BUTTONS)
   CONSTANT(GLUT_NUM_BUTTON_BOX_BUTTONS)
   CONSTANT(GLUT_NUM_DIALS)
   CONSTANT(GLUT_NUM_TABLET_BUTTONS)
   CONSTANT(GLUT_DEVICE_IGNORE_KEY_REPEAT)
   CONSTANT(GLUT_DEVICE_KEY_REPEAT)
   CONSTANT(GLUT_HAS_JOYSTICK)
   CONSTANT(GLUT_OWNS_JOYSTICK)
   CONSTANT(GLUT_JOYSTICK_BUTTONS)
   CONSTANT(GLUT_JOYSTICK_AXES)
   CONSTANT(GLUT_JOYSTICK_POLL_RATE)
   CONSTANT(GLUT_OVERLAY_POSSIBLE)
   CONSTANT(GLUT_LAYER_IN_USE)
   CONSTANT(GLUT_HAS_OVERLAY)
   CONSTANT(GLUT_TRANSPARENT_INDEX)
   CONSTANT(GLUT_NORMAL_DAMAGED)
   CONSTANT(GLUT_OVERLAY_DAMAGED)
   CONSTANT(GLUT_VIDEO_RESIZE_POSSIBLE)
   CONSTANT(GLUT_VIDEO_RESIZE_IN_USE)
   CONSTANT(GLUT_VIDEO_RESIZE_X_DELTA)
   CONSTANT(GLUT_VIDEO_RESIZE_Y_DELTA)
   CONSTANT(GLUT_VIDEO_RESIZE_WIDTH_DELTA)
   CONSTANT(GLUT_VIDEO_RESIZE_HEIGHT_DELTA)
   CONSTANT(GLUT_VIDEO_RESIZE_X)
   CONSTANT(GLUT_VIDEO_RESIZE_Y)
   CONSTANT(GLUT_VIDEO_RESIZE_WIDTH)
   CONSTANT(GLUT_VIDEO_RESIZE_HEIGHT)
   CONSTANT(GLUT_ACTIVE_SHIFT)
   CONSTANT(GLUT_ACTIVE_CTRL)
   CONSTANT(GLUT_ACTIVE_ALT)
   CONSTANT(GLUT_CURSOR_RIGHT_ARROW)
   CONSTANT(GLUT_CURSOR_LEFT_ARROW)
   CONSTANT(GLUT_CURSOR_INFO)
   CONSTANT(GLUT_CURSOR_DESTROY)
   CONSTANT(GLUT_CURSOR_HELP)
   CONSTANT(GLUT_CURSOR_CYCLE)
   CONSTANT(GLUT_CURSOR_SPRAY)
   CONSTANT(GLUT_CURSOR_WAIT)
   CONSTANT(GLUT_CURSOR_TEXT)
   CONSTANT(GLUT_CURSOR_CROSSHAIR)
   CONSTANT(GLUT_CURSOR_UP_DOWN)
   CONSTANT(GLUT_CURSOR_LEFT_RIGHT)
   CONSTANT(GLUT_CURSOR_TOP_SIDE)
   CONSTANT(GLUT_CURSOR_BOTTOM_SIDE)
   CONSTANT(GLUT_CURSOR_LEFT_SIDE)
   CONSTANT(GLUT_CURSOR_RIGHT_SIDE)
   CONSTANT(GLUT_CURSOR_TOP_LEFT_CORNER)
   CONSTANT(GLUT_CURSOR_TOP_RIGHT_CORNER)
   CONSTANT(GLUT_CURSOR_BOTTOM_RIGHT_CORNER)
   CONSTANT(GLUT_CURSOR_BOTTOM_LEFT_CORNER)
   CONSTANT(GLUT_CURSOR_INHERIT)
   CONSTANT(GLUT_CURSOR_NONE)
   CONSTANT(GLUT_CURSOR_FULL_CROSSHAIR)
   CONSTANT(GLUT_KEY_REPEAT_OFF)
   CONSTANT(GLUT_KEY_REPEAT_ON)
   CONSTANT(GLUT_KEY_REPEAT_DEFAULT)
   CONSTANT(GLUT_JOYSTICK_BUTTON_A)
   CONSTANT(GLUT_JOYSTICK_BUTTON_B)
   CONSTANT(GLUT_JOYSTICK_BUTTON_C)
   CONSTANT(GLUT_JOYSTICK_BUTTON_D)
   CONSTANT(GLUT_GAME_MODE_ACTIVE)
   CONSTANT(GLUT_GAME_MODE_POSSIBLE)
   CONSTANT(GLUT_GAME_MODE_WIDTH)
   CONSTANT(GLUT_GAME_MODE_HEIGHT)
   CONSTANT(GLUT_GAME_MODE_PIXEL_DEPTH)
   CONSTANT(GLUT_GAME_MODE_REFRESH_RATE)
   CONSTANT(GLUT_GAME_MODE_DISPLAY_CHANGED)

   #if defined(USE_OPENGLUT) || defined(USE_OPENGLEAN) || defined(USE_FREEGLUT)
   CONSTANT(GLUT_ACTION_CONTINUE_EXECUTION)
   CONSTANT(GLUT_ACTION_EXIT)
   CONSTANT(GLUT_ACTION_GLUTMAINLOOP_RETURNS)
   CONSTANT(GLUT_ACTION_ON_WINDOW_CLOSE)
   CONSTANT(GLUT_CREATE_NEW_CONTEXT)
   CONSTANT(GLUT_RENDERING_CONTEXT)
   CONSTANT(GLUT_USE_CURRENT_CONTEXT)
   CONSTANT(GLUT_VERSION)
   CONSTANT(GLUT_WINDOW_BORDER_WIDTH)
   CONSTANT(GLUT_WINDOW_HEADER_HEIGHT)
   #endif

   #if defined(USE_OPENGLUT) || defined(USE_OPENGLEAN)
   /* experimental features */
   CONSTANT(GLUT_OFFSCREEN)
   CONSTANT(GLUT_BORDERLESS)
   #endif

   /* =============================================================== */
   /* GLUT Functions                                                  */
   /* =============================================================== */
   /* from http://www.opengl.org/resources/libraries/glut/spec3/spec3.html */

   /* 2. Initialization */
   FUN   (glutInit)
   FUN   (glutInitWindowSize)
   FUN   (glutInitWindowPosition)
   FUN   (glutInitDisplayMode)

   /* 3. Event Processing */
   FUN   (glutMainLoop)

   /* 4. Window Management */
   FUN   (glutCreateWindow)
   FUN   (glutCreateSubWindow)
   FUN   (glutSetWindow)
   FUN   (glutGetWindow)
   FUN   (glutDestroyWindow)
   FUN   (glutPostRedisplay)
   FUN   (glutSwapBuffers)
   FUN   (glutPositionWindow)
   FUN   (glutReshapeWindow)
   FUN   (glutFullScreen)
   FUN   (glutPopWindow)
   FUN   (glutPushWindow)
   FUN   (glutShowWindow)
   FUN   (glutHideWindow)
   FUN   (glutIconifyWindow)
   FUN   (glutSetWindowTitle)
   FUN   (glutSetIconTitle)
   FUN   (glutSetCursor)

   /* 5. Overlay Management */
   FUN   (glutEstablishOverlay)
   FUN   (glutUseLayer)
   FUN   (glutRemoveOverlay)
   FUN   (glutPostOverlayRedisplay)
   FUN   (glutShowOverlay)
   FUN   (glutHideOverlay)

   /* 6. Menu Management */
   FUN   (glutCreateMenu)
   FUN   (glutSetMenu)
   FUN   (glutGetMenu)
   FUN   (glutDestroyMenu)
   FUN   (glutAddMenuEntry)
   FUN   (glutAddSubMenu)
   FUN   (glutChangeToMenuEntry)
   FUN   (glutChangeToSubMenu)
   FUN   (glutRemoveMenuItem)
   FUN   (glutAttachMenu)
   FUN   (glutDetachMenu)

   /* 7. Callback Registration */
   FUN   (glutDisplayFunc)
   FUN   (glutOverlayDisplayFunc)
   FUN   (glutReshapeFunc)
   FUN   (glutKeyboardFunc)
   FUN   (glutMouseFunc)
   FUN   (glutMotionFunc)
   FUN   (glutPassiveMotionFunc)
   FUN   (glutSpecialFunc)
   FUN   (glutIdleFunc)
   FUN   (glutTimerFunc)

   /* 8. Colormap Management */
   FUN   (glutSetColor)
   FUN   (glutGetColor)
   FUN   (glutCopyColormap)

   /* 9. State Retrieval */
   FUN   (glutGet)
   FUN   (glutLayerGet )
   FUN   (glutDeviceGet)
   FUN   (glutGetModifiers)
   FUN   (glutExtensionSupported)

   /* 10. Font Rendering */
   FUN   (glutBitmapCharacter)
   FUN   (glutBitmapWidth)
   FUN   (glutStrokeCharacter)
   FUN   (glutStrokeWidth)

   /* 11. Geometric Object Rendering */
   FUN   (glutSolidSphere)
   FUN   (glutWireSphere)
   FUN   (glutSolidCube)
   FUN   (glutWireCube)
   FUN   (glutSolidCone)
   FUN   (glutWireCone)
   FUN   (glutSolidTorus)
   FUN   (glutWireTorus)
   FUN   (glutSolidDodecahedron)
   FUN   (glutWireDodecahedron)
   FUN   (glutSolidOctahedron)
   FUN   (glutWireOctahedron)
   FUN   (glutSolidTetrahedron)
   FUN   (glutWireTetrahedron)
   FUN   (glutSolidIcosahedron)
   FUN   (glutWireIcosahedron)
   FUN   (glutSolidTeapot)
   FUN   (glutWireTeapot)

   /* ====================================================================== */
   /* This is the GLU API                                                    */
   /* ====================================================================== */

   FUN   (gluBuild1DMipmaps)
   FUN   (gluBuild2DMipmaps)
   FUN   (gluLookAt)
   FUN   (gluOrtho2D)
   FUN   (gluPerspective)
   FUN   (gluPickMatrix)
   FUN   (gluProject)
   FUN   (gluUnProject)

   /* ====================================================================== */
   /* OPENGLUT extensions                                                    */
   /* ====================================================================== */

   #if defined(USE_OPENGLUT) || defined(USE_OPENGLEAN) || defined(USE_FREEGLUT)
   FUN   (glutBitmapHeight)
   FUN   (glutBitmapString)
   FUN   (glutStrokeHeight)
   FUN   (glutStrokeString)

   FUN   (glutGetMenuData)
   FUN   (glutSetMenuData)

   FUN   (glutGetProcAddress)

   FUN   (glutGetWindowData)
   FUN   (glutSetWindowData)

   FUN   (glutLeaveMainLoop)
   FUN   (glutMainLoopEvent)

   /*
   FUN_SPEC (glutMenuDestroyFunc)
   FUN_SPEC (glutCloseFunc)
   FUN_SPEC (glutWMCloseFunc)
   FUN_SPEC (glutMouseWheelFunc)
   FUN_SPEC (glutSetOption)
   */

   FUN   (glutWireCylinder)
   FUN   (glutWireRhombicDodecahedron)
   FUN   (glutSolidCylinder)
   FUN   (glutSolidRhombicDodecahedron)
   #endif

   #if defined(USE_OPENGLUT) || defined(USE_OPENGLEAN)
   /* really experimental features */
   FUN   (glutCreateMenuWindow)
   FUN   (glutSetWindowStayOnTop)
   #endif
}


LUALIB_API int luaopen_luaglut(lua_State * L)
{
   register_glut(L);

   /* local luaglut = { } */
   lua_newtable(L);

   /* luaglut.VERSION = version */
   lua_pushstring(L, "VERSION");
   lua_pushstring(L, VERSION);
   lua_settable(L, -3);

   /* luaglut.window = { } */
   lua_pushstring(L, "window");
   lua_newtable(L);
   lua_settable(L, -3);

   /* local timer = { } */
   lua_pushstring(L, "timer");
   lua_newtable(L);

   /* timer.values = { } */
   lua_pushstring(L, "values");
   lua_newtable(L);
   lua_settable(L, -3);

   /* timer.next_free = -1 */
   lua_pushstring(L, "next_free");
   lua_pushnumber(L, -1);
   lua_settable(L, -3);

   /* luaglut.timer = timer */
   lua_settable(L, -3);

   /* _G.luaglut = luaglut */
   lua_pushstring(L, MYNAME);
   lua_pushvalue(L, -2);
   lua_settable(L, LUA_GLOBALSINDEX);

   /* keep the lua context */
   ref_L = L;

   /* plug-in the menu subsystem */
   luaL_loadbuffer(L, (const char *) menus_lua, menus_lua_len, "menus.lua");
   lua_pcall(L, 0, 0, lua_gettop(L));

   return 1;
}
