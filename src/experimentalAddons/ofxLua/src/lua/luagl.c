/* ======================================================================
** luagl.c - Copyright (C) 2005-2006 Varol Kaptan
** see LICENSE for more information
** ======================================================================
** vim: set ts=3 et: */

#include <stdio.h>
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <lua.h>
#include <lauxlib.h>
#include "macros.h"

#define MYNAME "luagl"
#define VERSION "0.5"

/* ====================================================================== */
/* This is the GL API                                                     */
/* ====================================================================== */
/* order same as: http://rush3d.com/reference/opengl-bluebook-1.0/        */

   /* === 1. Primitives ============================================= */

   //Specify vertices or rectangles:

   FUN_vE   (glBegin)      //void glBegin (GLenum mode);
   FUN_v    (glEnd)        //void glEnd (void);
   FUN_vD2  (glVertex2d)   //void glVertex2{sifd}{v} (TYPE x, TYPE y);
   FUN_vD3  (glVertex3d)   //void glVertex3{sifd}{v} (TYPE x, TYPE y, TYPE z);
   FUN_vD4  (glVertex4d)   //void glVertex4{sifd}{v} (TYPE x, TYPE y, TYPE z, TYPE w);
   FUN_vD4  (glRectd)      //void glRect{sifd} (TYPE x1, TYPE y1, TYPE x2, TYPE y2);
   //void glRect{sifd}v (const TYPE *v1, const TYPE *v2);

   //Specify polygon edge treatment:

   FUN_vB   (glEdgeFlag)   //void glEdgeFlag (GLboolean flag);
   //void glEdgeFlagv (const GLboolean *flag);

   /* === 2. Coordinate Transformations ============================= */

   //Transform the current matrix:

   FUN_vD4  (glRotated)       //void glRotate{fd} (TYPE angle, TYPE x, TYPE y, TYPE z);
   FUN_vD3  (glTranslated)    //void glTranslate{fd} (TYPE x, TYPE y, TYPE z);
   FUN_vD3  (glScaled)        //void glScale{fd} (TYPE x, TYPE y, TYPE z);
   FUN_vp   (glMultMatrixd)   //void glMultMatrix{fd} (const TYPE *m);
   FUN_vD6  (glFrustum)       //void glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);
   FUN_vD6  (glOrtho)         //void glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);

   //Replace the current matrix:

   FUN_vp   (glLoadMatrixd)   //void glLoadMatrix{fd} (const TYPE *m);
   FUN_v    (glLoadIdentity)  //void glLoadIdentity (void);

   //Manipulate the matrix stack:

   FUN_vE   (glMatrixMode)    //void glMatrixMode (GLenum mode);
   FUN_v    (glPushMatrix)    //void glPushMatrix (void);
   FUN_v    (glPopMatrix)     //void glPopMatrix (void);

   //Specify the viewport:

   FUN_vD2  (glDepthRange)    //void glDepthRange (GLclampd near, GLclampd far);
   FUN_vI2Z2(glViewport)      //void glViewport (GLint x, GLint y, GLsizei width, GLsizei height);

   /* === 3. Coloring and Lighting ================================== */

   //Set the current color, color index, or normal vector:

   FUN_vD3  (glColor3d)          //void glColor3{bsifd ubusui}{v} (TYPE red, TYPE green, TYPE blue);
   FUN_vD4  (glColor4d)          //void glColor4{bsifd ubusui}{v} (TYPE red, TYPE green, TYPE blue, TYPE alpha);
   FUN_vD   (glIndexd)           //void glIndex{sifd}{v} (TYPE index);
   FUN_vD3  (glNormal3d)         //void glNormal3{bsifd}{v} (TYPE nx, TYPE ny, TYPE nz);

   //Specify light source, material, or lighting model parameter values:

   FUN_vE2F (glLightf)           //void glLight{if}{v} (GLenum light, GLenum pname, TYPE param);
   FUN_SPEC (glLightfv)
   FUN_vE2F (glMaterialf)        //void glMaterial{if}{v} (GLenum face, GLenum pname, TYPE param);
   FUN_SPEC (glMaterialfv)
   FUN_vEF  (glLightModelf)      //void glLightModel{if}{v} (GLenum pname, TYPE param);

   //Choose a shading model:

   FUN_vE   (glShadeModel)       //void glShadeModel (GLenum mode);

   //Specify which polygon orientation is front-facing:

   FUN_vE   (glFrontFace)        //void glFrontFace (GLenum dir);

   //Cause a material color to track the current color:

   FUN_vE2  (glColorMaterial)    //void glColorMaterial (GLenum face, GLenum mode);

   //Obtain light source or material parameter values:

   FUN_vE2p (glGetLightfv)       //void glGetLight{if}v (GLenum light, GLenum pname, TYPE *params);
   FUN_vE2p (glGetMaterialfv)    //void glGetMaterial{if}v (GLenum face, GLenum pname, TYPE *params);

   /* === 4. Clipping =============================================== */

   //Specify a clipping plane:

   FUN_vEp  (glClipPlane)        //void glClipPlane (GLenum plane, const GLdouble *equation);

   //Return clipping plane coefficients:

   FUN_vEp  (glGetClipPlane)     //void glGetClipPlane (GLenum plane, GLdouble *equation);

   /* === 5. Rasterization ========================================== */

   //Set the current raster position:

   FUN_vD2  (glRasterPos2d)         //void glRasterPos2{sifd}{v}(TYPE x, TYPE y);
   FUN_vD3  (glRasterPos3d)         //void glRasterPos3{sifd}{v}(TYPE x, TYPE y, TYPE z);
   FUN_vD4  (glRasterPos4d)         //void glRasterPos4{sifd}{v}(TYPE x, TYPE y, TYPE z, TYPE w);

   //Specify a bitmap:

   FUN_vZ2F4p  (glBitmap)           //void glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);

   //Specify the dimensions of points or lines:

   FUN_vF   (glPointSize)           //void glPointSize (GLfloat size);
   FUN_vF   (glLineWidth)           //void glLineWidth (GLfloat width);

   //Specify or return a stipple pattern for lines or polygons:

   FUN_vIuH (glLineStipple)         //void glLineStipple (GLint factor, GLushort pattern);
   FUN_vp   (glPolygonStipple)      //void glPolygonStipple (const GLubyte *mask);
   FUN_vp   (glGetPolygonStipple)   //void glGetPolygonStipple (GLubyte *mask);

   //Choose how polygons are rasterized:

   FUN_vE   (glCullFace)            //void glCullFace (GLenum mode);
   FUN_vE2  (glPolygonMode)         //void glPolygonMode (GLenum face, GLenum mode);

   /* === 6. Pixel Operations ======================================= */

   //Select the source for pixel reads or copies:

   FUN_vE   (glReadBuffer)          //void glReadBuffer (GLenum mode);

   //Read, write, and copy pixels:

   FUN_vI2Z2E2p   (glReadPixels)    //void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
   FUN_vZ2E2p     (glDrawPixels)    //void glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
   FUN_vI2Z2E     (glCopyPixels)    //void glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);

   //Specify or query how pixels are encoded or processed:

   FUN_vEI  (glPixelStorei)         //void glPixelStore{if} (GLenum pname, TYPE param);
   FUN_vEF  (glPixelStoref)         //void glPixelStore{if} (GLenum pname, TYPE param);
   FUN_vEI  (glPixelTransferi)      //void glPixelTransfer{if} (GLenum pname, TYPE param);
   FUN_vEF  (glPixelTransferf)      //void glPixelTransfer{if} (GLenum pname, TYPE param);
   FUN_vEIp (glPixelMapfv)          //void glPixelMap{f usui}v (GLenum map, GLint mapsize, const TYPE *values);
   FUN_vEp  (glGetPixelMapfv)       //void glGetPixelMap{f usui}v (GLenum map, TYPE *values);

   //Control pixel rasterization:

   FUN_vF2  (glPixelZoom)           //void glPixelZoom (GLfloat xfactor, GLfloat yfactor);

   /* === 7. Texture Mapping ======================================== */

   // Control how a texture is applied to a fragment:

   FUN_vE2F (glTexParameterf) // void glTexParameter{if}{v} (GLenum target, GLenum pname, TYPE param);
   FUN_vE2F (glTexEnvf)       // void glTexEnv{if}{v} (GLenum target, GLenum pname, TYPE param);

   // Set the current texture coordinates:

   FUN_vD   (glTexCoord1d)    // void glTexCoord1{sifd}{v} (TYPE s);
   FUN_vD2  (glTexCoord2d)    // void glTexCoord2{sifd}{v} (TYPE s, TYPE t);
   FUN_vD3  (glTexCoord3d)    // void glTexCoord3{sifd}{v} (TYPE s, TYPE t, TYPE r);
   FUN_vD4  (glTexCoord4d)    // void glTexCoord4{sifd}{v} (TYPE s, TYPE t, TYPE r, TYPE q);

   // Control the generation of texture coordinates:

   FUN_vE2D (glTexGend)       // void glTexGen{ifd}{v} (GLenum coord, GLenum pname, TYPE param);

   // Specify a one- or two-dimensional texture image:

   FUN_vEI2ZIE2p  (glTexImage1D)    // void glTexImage1D (GLenum target, GLint level, GLint components, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
   FUN_vEI2Z2IE2p (glTexImage2D)    // void glTexImage2D (GLenum target, GLint level, GLint components, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

   // Obtain texture-related parameter values:

   FUN_vE2p    (glGetTexEnvfv)            // void glGetTexEnv{if}v (GLenum target, GLenum pname, TYPE *params);
   FUN_vE2p    (glGetTexGenfv)            // void glGetTexGen{ifd}v (GLenum coord, GLenum pname, TYPE *params);
   FUN_vEIE2p  (glGetTexImage)            // void glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
   FUN_vEIEp   (glGetTexLevelParameterfv) // void glGetTexLevelParameter{if}v (GLenum target, GLint level, GLenum pname, TYPE *params);
   FUN_vE2p    (glGetTexParameterfv)      // void glGetTexParameter{if}v (GLenum target, GLenum pname, TYPE *params);

   FUN_vZp     (glGenTextures)
   FUN_vEuI    (glBindTexture)
   FUN_vZp     (glDeleteTextures)

   /* === 8. Fog ==================================================== */

   // Set fog parameters:

   FUN_vEI  (glFogi)       //void glFog{if}{v} (GLenum pname, TYPE param);
   FUN_vEF  (glFogf)       //void glFog{if}{v} (GLenum pname, TYPE param);

   /* === 9. Frame Buffer Operations ================================ */

   //Control per-fragment testing:

   FUN_vI2Z2(glScissor)       //void glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
   FUN_vEF  (glAlphaFunc)     //void glAlphaFunc (GLenum func, GLclampf ref);
   FUN_vEIuI(glStencilFunc)   //void glStencilFunc (GLenum func, GLint ref, GLuint mask);
   FUN_vE3  (glStencilOp)     //void glStencilOp (GLenum fail, GLenum pass, GLenum zpass);
   FUN_vE   (glDepthFunc)     //void glDepthFunc (GLenum func);

   //Combine fragment and frame buffer values:

   FUN_vE2  (glBlendFunc)        //void glBlendFunc (GLenum sfactor, GLenum dfactor);
   FUN_vE   (glLogicOp)          //void glLogicOp (GLenum opcode);

   //Clear some or all buffers:

   FUN_vT   (glClear)            //void glClear (GLbitfield mask);

   //Specify color, depth, and stencil values for clears:

   FUN_vF4  (glClearAccum)       //void glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
   FUN_vF4  (glClearColor)       //void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
   FUN_vD   (glClearDepth)       //void glClearDepth (GLclampd depth);
   FUN_vF   (glClearIndex)       //void glClearIndex (GLfloat c);
   FUN_vI   (glClearStencil)     //void glClearStencil (GLint s);

   //Control buffers enabled for writing:

   FUN_vE   (glDrawBuffer)       //void glDrawBuffer (GLenum mode);
   FUN_vuI  (glIndexMask)        //void glIndexMask (GLuint mask);
   FUN_vB4  (glColorMask)        //void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
   FUN_vB   (glDepthMask)        //void glDepthMask (GLboolean flag);
   FUN_vuI  (glStencilMask)      //void glStencilMask (GLuint mask);

   //Operate on the accumulation buffer:

   FUN_vEF  (glAccum)            //void glAccum (GLenum op, GLfloat value);

   /* 10. Evaluators */

   //Define a one- or two-dimensional evaluator:

   //void glMap1{fd} (GLenum target, TYPE u1, TYPE u2, GLint stride, GLint order, const TYPE *points);
   //void glMap2{fd} (GLenum target, TYPE u1, TYPE u2, GLint ustride, GLint uorder, TYPE v1, TYPE v2, GLint vstride, GLint vorder, const TYPE *points);

   //Generate and evaluate a series of map domain values:

   //void glMapGrid1{fd} (GLint n, TYPE u1, TYPE u2);
   //void glMapGrid2{fd} (GLint un, TYPE u1, TYPE u2, GLint vn, TYPE v1, TYPE v2);
   //void glEvalMesh1 (GLenum mode, GLint i1, GLint i2);
   //void glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
   //void glEvalPoint1 (GLint i);
   //void glEvalPoint2 (GLint i, GLint j);

   //Evaluate one- and two-dimensional maps at a specified domain coordinate:

   //void glEvalCoord1{fd}{v} (TYPE u);
   //void glEvalCoord2{fd}{v} (TYPE u, TYPE v);

   //Obtain evaluator parameter values:

   //void glGetMap{idf}v (GLenum target, GLenum query, TYPE *v);

   /* 11. Selection and Feedback */

   //Control the mode and corresponding buffer:

   FUN_IE   (glRenderMode)       //GLint glRenderMode (GLenum mode);

   FUN_vZp  (glSelectBuffer)     //void glSelectBuffer (GLsizei size, GLuint *buffer);
   FUN_vZEp (glFeedbackBuffer)   //void glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer);

   //Supply a token for feedback mode:

   FUN_vF   (glPassThrough)      //void glPassThrough (GLfloat token);

   //Control the name stack for selection:

   FUN_v    (glInitNames)        //void glInitNames (void);
   FUN_vuI  (glLoadName)         //void glLoadName (GLuint name);
   FUN_vuI  (glPushName)         //void glPushName (GLuint name);
   FUN_v    (glPopName)          //void glPopName (void);

   /* === 12. Display Lists ========================================= */

   //Create or delete display lists:

   FUN_vuIE (glNewList)       //void glNewList (GLuint list, GLenum mode);
   FUN_v    (glEndList)       //void glEndList (void);
   FUN_vuIZ (glDeleteLists)   //void glDeleteLists (GLuint list, GLsizei range);

   //Execute a display list or set of lists:

   FUN_vuI  (glCallList)      //void glCallList (GLuint list);
   FUN_vZEp (glCallLists)     //void glCallLists (GLsizei n, GLenum type, const GLvoid *lists);

   //Manage display-list indices:

   FUN_uIZ  (glGenLists)      //GLuint glGenLists (GLsizei range);
   FUN_BuI  (glIsList)        //GLboolean glIsList (GLuint list);
   FUN_vuI  (glListBase)      //void glListBase (GLuint base);

   /* === 13. Modes and Execution =================================== */

   //Enable, disable, and query modes:

   FUN_vE   (glEnable)        //void glEnable (GLenum cap);
   FUN_vE   (glDisable)       //void glDisable (GLenum cap);
   FUN_BE   (glIsEnabled)     //GLboolean glIsEnabled (GLenum cap);

   //Wait until all OpenGL commands have executed completely:

   FUN_v    (glFinish)        //void glFinish (void);

   //Force all issued OpenGL commands to be executed:

   FUN_v    (glFlush)         //void glFlush (void);

   //Specify hints for OpenGL operation:

   FUN_vE2  (glHint)          //void glHint (GLenum target, GLenum mode);

   /* === 14. State Queries ========================================= */

   //Obtain information about an error or the current OpenGL connection:

   FUN_E    (glGetError)      //GLenum glGetError (void);
   FUN_sE   (glGetString)     //const GLubyte * glGetString (GLenum name);

   //Query state variables:

   FUN_vEp  (glGetBooleanv)   //void glGetBooleanv (GLenum pname, GLboolean *params);
   FUN_vEp  (glGetDoublev)    //void glGetDoublev (GLenum pname, GLdouble *params);
   FUN_vEp  (glGetFloatv)     //void glGetFloatv (GLenum pname, GLfloat *params);
   FUN_vEp  (glGetIntegerv)   //void glGetIntegerv (GLenum pname, GLint *params);

   //Save and restore sets of state variables:

   FUN_vT   (glPushAttrib)    //void glPushAttrib (GLbitfield mask);
   FUN_v    (glPopAttrib)     //void glPopAttrib (void);


LUA_API int LglLightfv(lua_State * L)
{
   GLenum a1 = check_GLenum(L, 1);
   GLenum a2 = check_GLenum(L, 2);
   GLfloat a3v[4], *a3 = a3v;
   int n, i;

   if (lua_type(L, 3) == LUA_TTABLE) {
      n = luaL_getn(L, 3);
      for (i = 1; i <= n; ++i) {
         lua_rawgeti(L, 3, i);
         a3v[i-1] = check_GLfloat(L, -1);
         lua_pop(L, 1);
      }
      a3 = a3v;
   } else if (lua_type(L, 3) == LUA_TLIGHTUSERDATA) {
      a3 = (GLfloat *) lua_touserdata(L, 3);
   } else
      luaL_error(L, "LglLightfv:invalid argument 3: table or lightuserdata required\n");
   glLightfv(a1, a2, a3);
   return 0;
}

LUA_API int LglMaterialfv(lua_State * L)
{
   GLenum a1 = check_GLenum(L, 1);
   GLenum a2 = check_GLenum(L, 2);
   GLfloat a3v[4], *a3 = a3v;
   int n, i;

   if (lua_type(L, 3) == LUA_TTABLE) {
      n = luaL_getn(L, 3);
      for (i = 1; i <= n; ++i) {
         lua_rawgeti(L, 3, i);
         a3v[i-1] = check_GLfloat(L, -1);
         lua_pop(L, 1);
      }
      a3 = a3v;
   } else if (lua_type(L, 3) == LUA_TLIGHTUSERDATA) {
      a3 = (GLfloat *) lua_touserdata(L, 3);
   } else
      luaL_error(L, "LglMaterialfv:invalid argument 3: table or lightuserdata required\n");
   glMaterialfv(a1, a2, a3);
   return 0;
}

void register_gl(lua_State *L)
{
   /* taken from mesa gl.h (XFree86-devel-4.3.0-55 fc1) */

   /* Boolean values */
   CONSTANT(GL_FALSE)
   CONSTANT(GL_TRUE)

   /* Data types */
   CONSTANT(GL_BYTE)
   CONSTANT(GL_UNSIGNED_BYTE)
   CONSTANT(GL_SHORT)
   CONSTANT(GL_UNSIGNED_SHORT)
   CONSTANT(GL_INT)
   CONSTANT(GL_UNSIGNED_INT)
   CONSTANT(GL_FLOAT)
   CONSTANT(GL_DOUBLE)
   CONSTANT(GL_2_BYTES)
   CONSTANT(GL_3_BYTES)
   CONSTANT(GL_4_BYTES)

   /* Primitives */
   CONSTANT(GL_POINTS)
   CONSTANT(GL_LINES)
   CONSTANT(GL_LINE_LOOP)
   CONSTANT(GL_LINE_STRIP)
   CONSTANT(GL_TRIANGLES)
   CONSTANT(GL_TRIANGLE_STRIP)
   CONSTANT(GL_TRIANGLE_FAN)
   CONSTANT(GL_QUADS)
   CONSTANT(GL_QUAD_STRIP)
   CONSTANT(GL_POLYGON)

   /* Vertex Arrays */
   CONSTANT(GL_VERTEX_ARRAY)
   CONSTANT(GL_NORMAL_ARRAY)
   CONSTANT(GL_COLOR_ARRAY)
   CONSTANT(GL_INDEX_ARRAY)
   CONSTANT(GL_TEXTURE_COORD_ARRAY)
   CONSTANT(GL_EDGE_FLAG_ARRAY)
   CONSTANT(GL_VERTEX_ARRAY_SIZE)
   CONSTANT(GL_VERTEX_ARRAY_TYPE)
   CONSTANT(GL_VERTEX_ARRAY_STRIDE)
   CONSTANT(GL_NORMAL_ARRAY_TYPE)
   CONSTANT(GL_NORMAL_ARRAY_STRIDE)
   CONSTANT(GL_COLOR_ARRAY_SIZE)
   CONSTANT(GL_COLOR_ARRAY_TYPE)
   CONSTANT(GL_COLOR_ARRAY_STRIDE)
   CONSTANT(GL_INDEX_ARRAY_TYPE)
   CONSTANT(GL_INDEX_ARRAY_STRIDE)
   CONSTANT(GL_TEXTURE_COORD_ARRAY_SIZE)
   CONSTANT(GL_TEXTURE_COORD_ARRAY_TYPE)
   CONSTANT(GL_TEXTURE_COORD_ARRAY_STRIDE)
   CONSTANT(GL_EDGE_FLAG_ARRAY_STRIDE)
   CONSTANT(GL_VERTEX_ARRAY_POINTER)
   CONSTANT(GL_NORMAL_ARRAY_POINTER)
   CONSTANT(GL_COLOR_ARRAY_POINTER)
   CONSTANT(GL_INDEX_ARRAY_POINTER)
   CONSTANT(GL_TEXTURE_COORD_ARRAY_POINTER)
   CONSTANT(GL_EDGE_FLAG_ARRAY_POINTER)
   CONSTANT(GL_V2F)
   CONSTANT(GL_V3F)
   CONSTANT(GL_C4UB_V2F)
   CONSTANT(GL_C4UB_V3F)
   CONSTANT(GL_C3F_V3F)
   CONSTANT(GL_N3F_V3F)
   CONSTANT(GL_C4F_N3F_V3F)
   CONSTANT(GL_T2F_V3F)
   CONSTANT(GL_T4F_V4F)
   CONSTANT(GL_T2F_C4UB_V3F)
   CONSTANT(GL_T2F_C3F_V3F)
   CONSTANT(GL_T2F_N3F_V3F)
   CONSTANT(GL_T2F_C4F_N3F_V3F)
   CONSTANT(GL_T4F_C4F_N3F_V4F)

   /* Matrix Mode */
   CONSTANT(GL_MATRIX_MODE)
   CONSTANT(GL_MODELVIEW)
   CONSTANT(GL_PROJECTION)
   CONSTANT(GL_TEXTURE)

   /* Points */
   CONSTANT(GL_POINT_SMOOTH)
   CONSTANT(GL_POINT_SIZE)
   CONSTANT(GL_POINT_SIZE_GRANULARITY )
   CONSTANT(GL_POINT_SIZE_RANGE)

   /* Lines */
   CONSTANT(GL_LINE_SMOOTH)
   CONSTANT(GL_LINE_STIPPLE)
   CONSTANT(GL_LINE_STIPPLE_PATTERN)
   CONSTANT(GL_LINE_STIPPLE_REPEAT)
   CONSTANT(GL_LINE_WIDTH)
   CONSTANT(GL_LINE_WIDTH_GRANULARITY)
   CONSTANT(GL_LINE_WIDTH_RANGE)

   /* Polygons */
   CONSTANT(GL_POINT)
   CONSTANT(GL_LINE)
   CONSTANT(GL_FILL)
   CONSTANT(GL_CW)
   CONSTANT(GL_CCW)
   CONSTANT(GL_FRONT)
   CONSTANT(GL_BACK)
   CONSTANT(GL_POLYGON_MODE)
   CONSTANT(GL_POLYGON_SMOOTH)
   CONSTANT(GL_POLYGON_STIPPLE)
   CONSTANT(GL_EDGE_FLAG)
   CONSTANT(GL_CULL_FACE)
   CONSTANT(GL_CULL_FACE_MODE)
   CONSTANT(GL_FRONT_FACE)
   CONSTANT(GL_POLYGON_OFFSET_FACTOR)
   CONSTANT(GL_POLYGON_OFFSET_UNITS)
   CONSTANT(GL_POLYGON_OFFSET_POINT)
   CONSTANT(GL_POLYGON_OFFSET_LINE)
   CONSTANT(GL_POLYGON_OFFSET_FILL)

   /* Display Lists */
   CONSTANT(GL_COMPILE)
   CONSTANT(GL_COMPILE_AND_EXECUTE)
   CONSTANT(GL_LIST_BASE)
   CONSTANT(GL_LIST_INDEX)
   CONSTANT(GL_LIST_MODE)

   /* Depth buffer */
   CONSTANT(GL_NEVER)
   CONSTANT(GL_LESS)
   CONSTANT(GL_EQUAL)
   CONSTANT(GL_LEQUAL)
   CONSTANT(GL_GREATER)
   CONSTANT(GL_NOTEQUAL)
   CONSTANT(GL_GEQUAL)
   CONSTANT(GL_ALWAYS)
   CONSTANT(GL_DEPTH_TEST)
   CONSTANT(GL_DEPTH_BITS)
   CONSTANT(GL_DEPTH_CLEAR_VALUE)
   CONSTANT(GL_DEPTH_FUNC)
   CONSTANT(GL_DEPTH_RANGE)
   CONSTANT(GL_DEPTH_WRITEMASK)
   CONSTANT(GL_DEPTH_COMPONENT)

   /* Lighting */
   CONSTANT(GL_LIGHTING)
   CONSTANT(GL_LIGHT0)
   CONSTANT(GL_LIGHT1)
   CONSTANT(GL_LIGHT2)
   CONSTANT(GL_LIGHT3)
   CONSTANT(GL_LIGHT4)
   CONSTANT(GL_LIGHT5)
   CONSTANT(GL_LIGHT6)
   CONSTANT(GL_LIGHT7)
   CONSTANT(GL_SPOT_EXPONENT)
   CONSTANT(GL_SPOT_CUTOFF)
   CONSTANT(GL_CONSTANT_ATTENUATION)
   CONSTANT(GL_LINEAR_ATTENUATION)
   CONSTANT(GL_QUADRATIC_ATTENUATION)
   CONSTANT(GL_AMBIENT)
   CONSTANT(GL_DIFFUSE)
   CONSTANT(GL_SPECULAR)
   CONSTANT(GL_SHININESS)
   CONSTANT(GL_EMISSION)
   CONSTANT(GL_POSITION)
   CONSTANT(GL_SPOT_DIRECTION)
   CONSTANT(GL_AMBIENT_AND_DIFFUSE)
   CONSTANT(GL_COLOR_INDEXES)
   CONSTANT(GL_LIGHT_MODEL_TWO_SIDE)
   CONSTANT(GL_LIGHT_MODEL_LOCAL_VIEWER)
   CONSTANT(GL_LIGHT_MODEL_AMBIENT)
   CONSTANT(GL_FRONT_AND_BACK)
   CONSTANT(GL_SHADE_MODEL)
   CONSTANT(GL_FLAT)
   CONSTANT(GL_SMOOTH)
   CONSTANT(GL_COLOR_MATERIAL)
   CONSTANT(GL_COLOR_MATERIAL_FACE)
   CONSTANT(GL_COLOR_MATERIAL_PARAMETER)
   CONSTANT(GL_NORMALIZE)

   /* User clipping planes */
   CONSTANT(GL_CLIP_PLANE0)
   CONSTANT(GL_CLIP_PLANE1)
   CONSTANT(GL_CLIP_PLANE2)
   CONSTANT(GL_CLIP_PLANE3)
   CONSTANT(GL_CLIP_PLANE4)
   CONSTANT(GL_CLIP_PLANE5)

   /* Accumulation buffer */
   CONSTANT(GL_ACCUM_RED_BITS)
   CONSTANT(GL_ACCUM_GREEN_BITS)
   CONSTANT(GL_ACCUM_BLUE_BITS)
   CONSTANT(GL_ACCUM_ALPHA_BITS)
   CONSTANT(GL_ACCUM_CLEAR_VALUE)
   CONSTANT(GL_ACCUM)
   CONSTANT(GL_ADD)
   CONSTANT(GL_LOAD)
   CONSTANT(GL_MULT)
   CONSTANT(GL_RETURN)

   /* Alpha testing */
   CONSTANT(GL_ALPHA_TEST)
   CONSTANT(GL_ALPHA_TEST_REF)
   CONSTANT(GL_ALPHA_TEST_FUNC)

   /* Blending */
   CONSTANT(GL_BLEND)
   CONSTANT(GL_BLEND_SRC)
   CONSTANT(GL_BLEND_DST)
   CONSTANT(GL_ZERO)
   CONSTANT(GL_ONE)
   CONSTANT(GL_SRC_COLOR)
   CONSTANT(GL_ONE_MINUS_SRC_COLOR)
   CONSTANT(GL_SRC_ALPHA)
   CONSTANT(GL_ONE_MINUS_SRC_ALPHA)
   CONSTANT(GL_DST_ALPHA)
   CONSTANT(GL_ONE_MINUS_DST_ALPHA)
   CONSTANT(GL_DST_COLOR)
   CONSTANT(GL_ONE_MINUS_DST_COLOR)
   CONSTANT(GL_SRC_ALPHA_SATURATE)
   CONSTANT(GL_CONSTANT_COLOR)
   CONSTANT(GL_ONE_MINUS_CONSTANT_COLOR)
   CONSTANT(GL_CONSTANT_ALPHA)
   CONSTANT(GL_ONE_MINUS_CONSTANT_ALPHA)

   /* Render Mode */
   CONSTANT(GL_FEEDBACK)
   CONSTANT(GL_RENDER)
   CONSTANT(GL_SELECT)

   /* Feedback */
   CONSTANT(GL_2D)
   CONSTANT(GL_3D)
   CONSTANT(GL_3D_COLOR)
   CONSTANT(GL_3D_COLOR_TEXTURE)
   CONSTANT(GL_4D_COLOR_TEXTURE)
   CONSTANT(GL_POINT_TOKEN)
   CONSTANT(GL_LINE_TOKEN)
   CONSTANT(GL_LINE_RESET_TOKEN)
   CONSTANT(GL_POLYGON_TOKEN)
   CONSTANT(GL_BITMAP_TOKEN)
   CONSTANT(GL_DRAW_PIXEL_TOKEN)
   CONSTANT(GL_COPY_PIXEL_TOKEN)
   CONSTANT(GL_PASS_THROUGH_TOKEN)
   CONSTANT(GL_FEEDBACK_BUFFER_POINTER)
   CONSTANT(GL_FEEDBACK_BUFFER_SIZE)
   CONSTANT(GL_FEEDBACK_BUFFER_TYPE)

   /* Selection */
   CONSTANT(GL_SELECTION_BUFFER_POINTER)
   CONSTANT(GL_SELECTION_BUFFER_SIZE)

   /* Fog */
   CONSTANT(GL_FOG)
   CONSTANT(GL_FOG_MODE)
   CONSTANT(GL_FOG_DENSITY)
   CONSTANT(GL_FOG_COLOR)
   CONSTANT(GL_FOG_INDEX)
   CONSTANT(GL_FOG_START)
   CONSTANT(GL_FOG_END)
   CONSTANT(GL_LINEAR)
   CONSTANT(GL_EXP)
   CONSTANT(GL_EXP2)

   /* Logic Ops */
   CONSTANT(GL_LOGIC_OP)
   CONSTANT(GL_INDEX_LOGIC_OP)
   CONSTANT(GL_COLOR_LOGIC_OP)
   CONSTANT(GL_LOGIC_OP_MODE)
   CONSTANT(GL_CLEAR)
   CONSTANT(GL_SET)
   CONSTANT(GL_COPY)
   CONSTANT(GL_COPY_INVERTED)
   CONSTANT(GL_NOOP)
   CONSTANT(GL_INVERT)
   CONSTANT(GL_AND)
   CONSTANT(GL_NAND)
   CONSTANT(GL_OR)
   CONSTANT(GL_NOR)
   CONSTANT(GL_XOR)
   CONSTANT(GL_EQUIV)
   CONSTANT(GL_AND_REVERSE)
   CONSTANT(GL_AND_INVERTED)
   CONSTANT(GL_OR_REVERSE)
   CONSTANT(GL_OR_INVERTED)

   /* Stencil */
   CONSTANT(GL_STENCIL_TEST)
   CONSTANT(GL_STENCIL_WRITEMASK)
   CONSTANT(GL_STENCIL_BITS)
   CONSTANT(GL_STENCIL_FUNC)
   CONSTANT(GL_STENCIL_VALUE_MASK)
   CONSTANT(GL_STENCIL_REF)
   CONSTANT(GL_STENCIL_FAIL)
   CONSTANT(GL_STENCIL_PASS_DEPTH_PASS)
   CONSTANT(GL_STENCIL_PASS_DEPTH_FAIL)
   CONSTANT(GL_STENCIL_CLEAR_VALUE)
   CONSTANT(GL_STENCIL_INDEX)
   CONSTANT(GL_KEEP)
   CONSTANT(GL_REPLACE)
   CONSTANT(GL_INCR)
   CONSTANT(GL_DECR)

   /* Buffers, Pixel Drawing/Reading */
   CONSTANT(GL_NONE)
   CONSTANT(GL_LEFT)
   CONSTANT(GL_RIGHT)
   CONSTANT(GL_FRONT_LEFT)
   CONSTANT(GL_FRONT_RIGHT)
   CONSTANT(GL_BACK_LEFT)
   CONSTANT(GL_BACK_RIGHT)
   CONSTANT(GL_AUX0)
   CONSTANT(GL_AUX1)
   CONSTANT(GL_AUX2)
   CONSTANT(GL_AUX3)
   CONSTANT(GL_COLOR_INDEX)
   CONSTANT(GL_RED)
   CONSTANT(GL_GREEN)
   CONSTANT(GL_BLUE)
   CONSTANT(GL_ALPHA)
   CONSTANT(GL_LUMINANCE)
   CONSTANT(GL_LUMINANCE_ALPHA)
   CONSTANT(GL_ALPHA_BITS)
   CONSTANT(GL_RED_BITS)
   CONSTANT(GL_GREEN_BITS)
   CONSTANT(GL_BLUE_BITS)
   CONSTANT(GL_INDEX_BITS)
   CONSTANT(GL_SUBPIXEL_BITS)
   CONSTANT(GL_AUX_BUFFERS)
   CONSTANT(GL_READ_BUFFER)
   CONSTANT(GL_DRAW_BUFFER)
   CONSTANT(GL_DOUBLEBUFFER)
   CONSTANT(GL_STEREO)
   CONSTANT(GL_BITMAP)
   CONSTANT(GL_COLOR)
   CONSTANT(GL_DEPTH)
   CONSTANT(GL_STENCIL)
   CONSTANT(GL_DITHER)
   CONSTANT(GL_RGB)
   CONSTANT(GL_RGBA)

   /* Implementation limits */
   CONSTANT(GL_MAX_LIST_NESTING)
   CONSTANT(GL_MAX_ATTRIB_STACK_DEPTH)
   CONSTANT(GL_MAX_MODELVIEW_STACK_DEPTH)
   CONSTANT(GL_MAX_NAME_STACK_DEPTH)
   CONSTANT(GL_MAX_PROJECTION_STACK_DEPTH)
   CONSTANT(GL_MAX_TEXTURE_STACK_DEPTH)
   CONSTANT(GL_MAX_EVAL_ORDER)
   CONSTANT(GL_MAX_LIGHTS)
   CONSTANT(GL_MAX_CLIP_PLANES)
   CONSTANT(GL_MAX_TEXTURE_SIZE)
   CONSTANT(GL_MAX_PIXEL_MAP_TABLE)
   CONSTANT(GL_MAX_VIEWPORT_DIMS)
   CONSTANT(GL_MAX_CLIENT_ATTRIB_STACK_DEPTH)

   /* Gets */
   CONSTANT(GL_ATTRIB_STACK_DEPTH)
   CONSTANT(GL_CLIENT_ATTRIB_STACK_DEPTH)
   CONSTANT(GL_COLOR_CLEAR_VALUE)
   CONSTANT(GL_COLOR_WRITEMASK)
   CONSTANT(GL_CURRENT_INDEX)
   CONSTANT(GL_CURRENT_COLOR)
   CONSTANT(GL_CURRENT_NORMAL)
   CONSTANT(GL_CURRENT_RASTER_COLOR)
   CONSTANT(GL_CURRENT_RASTER_DISTANCE)
   CONSTANT(GL_CURRENT_RASTER_INDEX)
   CONSTANT(GL_CURRENT_RASTER_POSITION)
   CONSTANT(GL_CURRENT_RASTER_TEXTURE_COORDS)
   CONSTANT(GL_CURRENT_RASTER_POSITION_VALID)
   CONSTANT(GL_CURRENT_TEXTURE_COORDS)
   CONSTANT(GL_INDEX_CLEAR_VALUE)
   CONSTANT(GL_INDEX_MODE)
   CONSTANT(GL_INDEX_WRITEMASK)
   CONSTANT(GL_MODELVIEW_MATRIX)
   CONSTANT(GL_MODELVIEW_STACK_DEPTH)
   CONSTANT(GL_NAME_STACK_DEPTH)
   CONSTANT(GL_PROJECTION_MATRIX)
   CONSTANT(GL_PROJECTION_STACK_DEPTH)
   CONSTANT(GL_RENDER_MODE)
   CONSTANT(GL_RGBA_MODE)
   CONSTANT(GL_TEXTURE_MATRIX)
   CONSTANT(GL_TEXTURE_STACK_DEPTH)
   CONSTANT(GL_VIEWPORT)

   /* Evaluators */
   CONSTANT(GL_AUTO_NORMAL)
   CONSTANT(GL_MAP1_COLOR_4)
   CONSTANT(GL_MAP1_GRID_DOMAIN)
   CONSTANT(GL_MAP1_GRID_SEGMENTS)
   CONSTANT(GL_MAP1_INDEX)
   CONSTANT(GL_MAP1_NORMAL)
   CONSTANT(GL_MAP1_TEXTURE_COORD_1)
   CONSTANT(GL_MAP1_TEXTURE_COORD_2)
   CONSTANT(GL_MAP1_TEXTURE_COORD_3)
   CONSTANT(GL_MAP1_TEXTURE_COORD_4)
   CONSTANT(GL_MAP1_VERTEX_3)
   CONSTANT(GL_MAP1_VERTEX_4)
   CONSTANT(GL_MAP2_COLOR_4)
   CONSTANT(GL_MAP2_GRID_DOMAIN)
   CONSTANT(GL_MAP2_GRID_SEGMENTS)
   CONSTANT(GL_MAP2_INDEX)
   CONSTANT(GL_MAP2_NORMAL)
   CONSTANT(GL_MAP2_TEXTURE_COORD_1)
   CONSTANT(GL_MAP2_TEXTURE_COORD_2)
   CONSTANT(GL_MAP2_TEXTURE_COORD_3)
   CONSTANT(GL_MAP2_TEXTURE_COORD_4)
   CONSTANT(GL_MAP2_VERTEX_3)
   CONSTANT(GL_MAP2_VERTEX_4)
   CONSTANT(GL_COEFF)
   CONSTANT(GL_DOMAIN)
   CONSTANT(GL_ORDER)

   /* Hints */
   CONSTANT(GL_FOG_HINT)
   CONSTANT(GL_LINE_SMOOTH_HINT)
   CONSTANT(GL_PERSPECTIVE_CORRECTION_HINT)
   CONSTANT(GL_POINT_SMOOTH_HINT)
   CONSTANT(GL_POLYGON_SMOOTH_HINT)
   CONSTANT(GL_DONT_CARE)
   CONSTANT(GL_FASTEST)
   CONSTANT(GL_NICEST)

   /* Scissor box */
   CONSTANT(GL_SCISSOR_TEST)
   CONSTANT(GL_SCISSOR_BOX)

   /* Pixel Mode / Transfer */
   CONSTANT(GL_MAP_COLOR)
   CONSTANT(GL_MAP_STENCIL)
   CONSTANT(GL_INDEX_SHIFT)
   CONSTANT(GL_INDEX_OFFSET)
   CONSTANT(GL_RED_SCALE)
   CONSTANT(GL_RED_BIAS)
   CONSTANT(GL_GREEN_SCALE)
   CONSTANT(GL_GREEN_BIAS)
   CONSTANT(GL_BLUE_SCALE)
   CONSTANT(GL_BLUE_BIAS)
   CONSTANT(GL_ALPHA_SCALE)
   CONSTANT(GL_ALPHA_BIAS)
   CONSTANT(GL_DEPTH_SCALE)
   CONSTANT(GL_DEPTH_BIAS)
   CONSTANT(GL_PIXEL_MAP_S_TO_S_SIZE)
   CONSTANT(GL_PIXEL_MAP_I_TO_I_SIZE)
   CONSTANT(GL_PIXEL_MAP_I_TO_R_SIZE)
   CONSTANT(GL_PIXEL_MAP_I_TO_G_SIZE)
   CONSTANT(GL_PIXEL_MAP_I_TO_B_SIZE)
   CONSTANT(GL_PIXEL_MAP_I_TO_A_SIZE)
   CONSTANT(GL_PIXEL_MAP_R_TO_R_SIZE)
   CONSTANT(GL_PIXEL_MAP_G_TO_G_SIZE)
   CONSTANT(GL_PIXEL_MAP_B_TO_B_SIZE)
   CONSTANT(GL_PIXEL_MAP_A_TO_A_SIZE)
   CONSTANT(GL_PIXEL_MAP_S_TO_S)
   CONSTANT(GL_PIXEL_MAP_I_TO_I)
   CONSTANT(GL_PIXEL_MAP_I_TO_R)
   CONSTANT(GL_PIXEL_MAP_I_TO_G)
   CONSTANT(GL_PIXEL_MAP_I_TO_B)
   CONSTANT(GL_PIXEL_MAP_I_TO_A)
   CONSTANT(GL_PIXEL_MAP_R_TO_R)
   CONSTANT(GL_PIXEL_MAP_G_TO_G)
   CONSTANT(GL_PIXEL_MAP_B_TO_B)
   CONSTANT(GL_PIXEL_MAP_A_TO_A)
   CONSTANT(GL_PACK_ALIGNMENT)
   CONSTANT(GL_PACK_LSB_FIRST)
   CONSTANT(GL_PACK_ROW_LENGTH)
   CONSTANT(GL_PACK_SKIP_PIXELS)
   CONSTANT(GL_PACK_SKIP_ROWS)
   CONSTANT(GL_PACK_SWAP_BYTES)
   CONSTANT(GL_UNPACK_ALIGNMENT)
   CONSTANT(GL_UNPACK_LSB_FIRST)
   CONSTANT(GL_UNPACK_ROW_LENGTH)
   CONSTANT(GL_UNPACK_SKIP_PIXELS)
   CONSTANT(GL_UNPACK_SKIP_ROWS)
   CONSTANT(GL_UNPACK_SWAP_BYTES)
   CONSTANT(GL_ZOOM_X)
   CONSTANT(GL_ZOOM_Y)

   /* Texture mapping */
   CONSTANT(GL_TEXTURE_ENV)
   CONSTANT(GL_TEXTURE_ENV_MODE)
   CONSTANT(GL_TEXTURE_1D)
   CONSTANT(GL_TEXTURE_2D)
   CONSTANT(GL_TEXTURE_WRAP_S)
   CONSTANT(GL_TEXTURE_WRAP_T)
   CONSTANT(GL_TEXTURE_MAG_FILTER)
   CONSTANT(GL_TEXTURE_MIN_FILTER)
   CONSTANT(GL_TEXTURE_ENV_COLOR)
   CONSTANT(GL_TEXTURE_GEN_S)
   CONSTANT(GL_TEXTURE_GEN_T)
   CONSTANT(GL_TEXTURE_GEN_MODE)
   CONSTANT(GL_TEXTURE_BORDER_COLOR)
   CONSTANT(GL_TEXTURE_WIDTH)
   CONSTANT(GL_TEXTURE_HEIGHT)
   CONSTANT(GL_TEXTURE_BORDER)
   CONSTANT(GL_TEXTURE_COMPONENTS)
   CONSTANT(GL_TEXTURE_RED_SIZE)
   CONSTANT(GL_TEXTURE_GREEN_SIZE)
   CONSTANT(GL_TEXTURE_BLUE_SIZE)
   CONSTANT(GL_TEXTURE_ALPHA_SIZE)
   CONSTANT(GL_TEXTURE_LUMINANCE_SIZE)
   CONSTANT(GL_TEXTURE_INTENSITY_SIZE)
   CONSTANT(GL_NEAREST_MIPMAP_NEAREST)
   CONSTANT(GL_NEAREST_MIPMAP_LINEAR)
   CONSTANT(GL_LINEAR_MIPMAP_NEAREST)
   CONSTANT(GL_LINEAR_MIPMAP_LINEAR)
   CONSTANT(GL_OBJECT_LINEAR)
   CONSTANT(GL_OBJECT_PLANE)
   CONSTANT(GL_EYE_LINEAR)
   CONSTANT(GL_EYE_PLANE)
   CONSTANT(GL_SPHERE_MAP)
   CONSTANT(GL_DECAL)
   CONSTANT(GL_MODULATE)
   CONSTANT(GL_NEAREST)
   CONSTANT(GL_REPEAT)
   CONSTANT(GL_CLAMP)
   CONSTANT(GL_S)
   CONSTANT(GL_T)
   CONSTANT(GL_R)
   CONSTANT(GL_Q)
   CONSTANT(GL_TEXTURE_GEN_R)
   CONSTANT(GL_TEXTURE_GEN_Q)

   /* Utility */
   CONSTANT(GL_VENDOR)
   CONSTANT(GL_RENDERER)
   CONSTANT(GL_VERSION)
   CONSTANT(GL_EXTENSIONS)

   /* Errors */
   CONSTANT(GL_NO_ERROR)
   CONSTANT(GL_INVALID_VALUE)
   CONSTANT(GL_INVALID_ENUM)
   CONSTANT(GL_INVALID_OPERATION)
   CONSTANT(GL_STACK_OVERFLOW)
   CONSTANT(GL_STACK_UNDERFLOW)
   CONSTANT(GL_OUT_OF_MEMORY)

   /* glPush/PopAttrib bits */
   CONSTANT(GL_CURRENT_BIT)
   CONSTANT(GL_POINT_BIT)
   CONSTANT(GL_LINE_BIT)
   CONSTANT(GL_POLYGON_BIT)
   CONSTANT(GL_POLYGON_STIPPLE_BIT)
   CONSTANT(GL_PIXEL_MODE_BIT)
   CONSTANT(GL_LIGHTING_BIT)
   CONSTANT(GL_FOG_BIT)
   CONSTANT(GL_DEPTH_BUFFER_BIT)
   CONSTANT(GL_ACCUM_BUFFER_BIT)
   CONSTANT(GL_STENCIL_BUFFER_BIT)
   CONSTANT(GL_VIEWPORT_BIT)
   CONSTANT(GL_TRANSFORM_BIT)
   CONSTANT(GL_ENABLE_BIT)
   CONSTANT(GL_COLOR_BUFFER_BIT)
   CONSTANT(GL_HINT_BIT)
   CONSTANT(GL_EVAL_BIT)
   CONSTANT(GL_LIST_BIT)
   CONSTANT(GL_TEXTURE_BIT)
   CONSTANT(GL_SCISSOR_BIT)
   CONSTANT(GL_ALL_ATTRIB_BITS)

#ifdef GL_VERSION_1_1
   /* OpenGL 1.1 */
   CONSTANT(GL_PROXY_TEXTURE_1D)
   CONSTANT(GL_PROXY_TEXTURE_2D)
   CONSTANT(GL_TEXTURE_PRIORITY)
   CONSTANT(GL_TEXTURE_RESIDENT)
   CONSTANT(GL_TEXTURE_BINDING_1D)
   CONSTANT(GL_TEXTURE_BINDING_2D)
   CONSTANT(GL_TEXTURE_INTERNAL_FORMAT)
   CONSTANT(GL_ALPHA4)
   CONSTANT(GL_ALPHA8)
   CONSTANT(GL_ALPHA12)
   CONSTANT(GL_ALPHA16)
   CONSTANT(GL_LUMINANCE4)
   CONSTANT(GL_LUMINANCE8)
   CONSTANT(GL_LUMINANCE12)
   CONSTANT(GL_LUMINANCE16)
   CONSTANT(GL_LUMINANCE4_ALPHA4)
   CONSTANT(GL_LUMINANCE6_ALPHA2)
   CONSTANT(GL_LUMINANCE8_ALPHA8)
   CONSTANT(GL_LUMINANCE12_ALPHA4)
   CONSTANT(GL_LUMINANCE12_ALPHA12)
   CONSTANT(GL_LUMINANCE16_ALPHA16)
   CONSTANT(GL_INTENSITY)
   CONSTANT(GL_INTENSITY4)
   CONSTANT(GL_INTENSITY8)
   CONSTANT(GL_INTENSITY12)
   CONSTANT(GL_INTENSITY16)
   CONSTANT(GL_R3_G3_B2)
   CONSTANT(GL_RGB4)
   CONSTANT(GL_RGB5)
   CONSTANT(GL_RGB8)
   CONSTANT(GL_RGB10)
   CONSTANT(GL_RGB12)
   CONSTANT(GL_RGB16)
   CONSTANT(GL_RGBA2)
   CONSTANT(GL_RGBA4)
   CONSTANT(GL_RGB5_A1)
   CONSTANT(GL_RGBA8)
   CONSTANT(GL_RGB10_A2)
   CONSTANT(GL_RGBA12)
   CONSTANT(GL_RGBA16)
   CONSTANT(GL_CLIENT_PIXEL_STORE_BIT)
   CONSTANT(GL_CLIENT_VERTEX_ARRAY_BIT)
   //CONSTANT(GL_ALL_CLIENT_ATTRIB_BITS )
   //CONSTANT(GL_CLIENT_ALL_ATTRIB_BITS )
#endif

#ifdef GL_VERSION_1_2
   /* OpenGL 1.2 */
   CONSTANT(GL_RESCALE_NORMAL)
   CONSTANT(GL_CLAMP_TO_EDGE)
#if GL_EXT_draw_range_elements
   CONSTANT(GL_MAX_ELEMENTS_VERTICES_EXT)
   CONSTANT(GL_MAX_ELEMENTS_INDICES_EXT)
#endif
#if GL_EXT_bgra
   CONSTANT(GL_BGR_EXT)
   CONSTANT(GL_BGRA_EXT)
#endif
   CONSTANT(GL_UNSIGNED_BYTE_3_3_2)
   CONSTANT(GL_UNSIGNED_BYTE_2_3_3_REV)
   CONSTANT(GL_UNSIGNED_SHORT_5_6_5)
   CONSTANT(GL_UNSIGNED_SHORT_5_6_5_REV)
   CONSTANT(GL_UNSIGNED_SHORT_4_4_4_4)
   CONSTANT(GL_UNSIGNED_SHORT_4_4_4_4_REV)
   CONSTANT(GL_UNSIGNED_SHORT_5_5_5_1)
   CONSTANT(GL_UNSIGNED_SHORT_1_5_5_5_REV)
   CONSTANT(GL_UNSIGNED_INT_8_8_8_8)
   CONSTANT(GL_UNSIGNED_INT_8_8_8_8_REV)
   CONSTANT(GL_UNSIGNED_INT_10_10_10_2)
   CONSTANT(GL_UNSIGNED_INT_2_10_10_10_REV)
#if GL_EXT_separate_specular_color
   CONSTANT(GL_LIGHT_MODEL_COLOR_CONTROL_EXT)
   CONSTANT(GL_SINGLE_COLOR_EXT)
   CONSTANT(GL_SEPARATE_SPECULAR_COLOR_EXT)
#endif
   CONSTANT(GL_TEXTURE_MIN_LOD)
   CONSTANT(GL_TEXTURE_MAX_LOD)
   CONSTANT(GL_TEXTURE_BASE_LEVEL)
   CONSTANT(GL_TEXTURE_MAX_LEVEL)
   /* GetTarget1_2 */
#ifdef GL_SMOOTH_POINT_SIZE_RANGE
   CONSTANT(GL_SMOOTH_POINT_SIZE_RANGE)
#endif
#ifdef GL_SMOOTH_POINT_SIZE_GRANULARITY
   CONSTANT(GL_SMOOTH_POINT_SIZE_GRANULARITY)
#endif
#ifdef GL_SMOOTH_LINE_WIDTH_RANGE
   CONSTANT(GL_SMOOTH_LINE_WIDTH_RANGE)
#endif
#ifdef GL_SMOOTH_LINE_WIDTH_GRANULARITY
   CONSTANT(GL_SMOOTH_LINE_WIDTH_GRANULARITY)
#endif
#ifdef GL_ALIASED_POINT_SIZE_RANGE
   CONSTANT(GL_ALIASED_POINT_SIZE_RANGE)
#endif
#ifdef GL_ALIASED_LINE_WIDTH_RANGE
   CONSTANT(GL_ALIASED_LINE_WIDTH_RANGE)
#endif

   CONSTANT(GL_PACK_SKIP_IMAGES)
   CONSTANT(GL_PACK_IMAGE_HEIGHT)
   CONSTANT(GL_UNPACK_SKIP_IMAGES)
   CONSTANT(GL_UNPACK_IMAGE_HEIGHT)
   CONSTANT(GL_TEXTURE_3D)
   CONSTANT(GL_PROXY_TEXTURE_3D)
   CONSTANT(GL_TEXTURE_DEPTH)
   CONSTANT(GL_TEXTURE_WRAP_R)
   CONSTANT(GL_MAX_3D_TEXTURE_SIZE)
   #if !defined(__WIN32__) && !defined(macintosh)
   /* ugly fix for mingw and macos ?!? */
   CONSTANT(GL_TEXTURE_BINDING_3D)
   #endif

   /* OpenGL 1.2 imaging subset */
   /* GL_EXT_color_table */
   CONSTANT(GL_COLOR_TABLE)
   CONSTANT(GL_POST_CONVOLUTION_COLOR_TABLE)
   CONSTANT(GL_POST_COLOR_MATRIX_COLOR_TABLE)
   CONSTANT(GL_PROXY_COLOR_TABLE)
   CONSTANT(GL_PROXY_POST_CONVOLUTION_COLOR_TABLE)
   CONSTANT(GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE)
   CONSTANT(GL_COLOR_TABLE_SCALE)
   CONSTANT(GL_COLOR_TABLE_BIAS)
   CONSTANT(GL_COLOR_TABLE_FORMAT)
   CONSTANT(GL_COLOR_TABLE_WIDTH)
   CONSTANT(GL_COLOR_TABLE_RED_SIZE)
   CONSTANT(GL_COLOR_TABLE_GREEN_SIZE)
   CONSTANT(GL_COLOR_TABLE_BLUE_SIZE)
   CONSTANT(GL_COLOR_TABLE_ALPHA_SIZE)
   CONSTANT(GL_COLOR_TABLE_LUMINANCE_SIZE)
   CONSTANT(GL_COLOR_TABLE_INTENSITY_SIZE)
   /* GL_EXT_convolution and GL_HP_convolution_border_modes */
   CONSTANT(GL_CONVOLUTION_1D)
   CONSTANT(GL_CONVOLUTION_2D)
   CONSTANT(GL_SEPARABLE_2D)
   CONSTANT(GL_CONVOLUTION_BORDER_MODE)
   CONSTANT(GL_CONVOLUTION_FILTER_SCALE)
   CONSTANT(GL_CONVOLUTION_FILTER_BIAS)
   CONSTANT(GL_REDUCE)
   CONSTANT(GL_CONVOLUTION_FORMAT)
   CONSTANT(GL_CONVOLUTION_WIDTH)
   CONSTANT(GL_CONVOLUTION_HEIGHT)
   CONSTANT(GL_MAX_CONVOLUTION_WIDTH)
   CONSTANT(GL_MAX_CONVOLUTION_HEIGHT)
   CONSTANT(GL_POST_CONVOLUTION_RED_SCALE)
   CONSTANT(GL_POST_CONVOLUTION_GREEN_SCALE)
   CONSTANT(GL_POST_CONVOLUTION_BLUE_SCALE)
   CONSTANT(GL_POST_CONVOLUTION_ALPHA_SCALE)
   CONSTANT(GL_POST_CONVOLUTION_RED_BIAS)
   CONSTANT(GL_POST_CONVOLUTION_GREEN_BIAS)
   CONSTANT(GL_POST_CONVOLUTION_BLUE_BIAS)
   CONSTANT(GL_POST_CONVOLUTION_ALPHA_BIAS)
   /* GL_HP_convolution_border_modes */
#ifdef GL_CONSTANT_BORDER
   CONSTANT(GL_CONSTANT_BORDER)
#endif
#ifdef GL_REPLICATE_BORDER
   CONSTANT(GL_REPLICATE_BORDER)
#endif
#ifdef GL_CONVOLUTION_BORDER_COLOR
   CONSTANT(GL_CONVOLUTION_BORDER_COLOR)
#endif
   /* GL_SGI_color_matrix */
   CONSTANT(GL_COLOR_MATRIX)
   CONSTANT(GL_COLOR_MATRIX_STACK_DEPTH)
   CONSTANT(GL_MAX_COLOR_MATRIX_STACK_DEPTH)
   CONSTANT(GL_POST_COLOR_MATRIX_RED_SCALE)
   CONSTANT(GL_POST_COLOR_MATRIX_GREEN_SCALE)
   CONSTANT(GL_POST_COLOR_MATRIX_BLUE_SCALE)
   CONSTANT(GL_POST_COLOR_MATRIX_ALPHA_SCALE)
   CONSTANT(GL_POST_COLOR_MATRIX_RED_BIAS)
   CONSTANT(GL_POST_COLOR_MATRIX_GREEN_BIAS)
   CONSTANT(GL_POST_COLOR_MATRIX_BLUE_BIAS)
   #if !defined(__WIN32__) && !defined(macintosh)
   /* ugly fix for mingw and macos ?!? */
   CONSTANT(GL_POST_COLOR_MATRIX_ALPHA_BIAS)
   #endif
   /* GL_EXT_histogram */
   CONSTANT(GL_HISTOGRAM)
   CONSTANT(GL_PROXY_HISTOGRAM)
   CONSTANT(GL_HISTOGRAM_WIDTH)
   CONSTANT(GL_HISTOGRAM_FORMAT)
   CONSTANT(GL_HISTOGRAM_RED_SIZE)
   CONSTANT(GL_HISTOGRAM_GREEN_SIZE)
   CONSTANT(GL_HISTOGRAM_BLUE_SIZE)
   CONSTANT(GL_HISTOGRAM_ALPHA_SIZE)
   CONSTANT(GL_HISTOGRAM_LUMINANCE_SIZE)
   CONSTANT(GL_HISTOGRAM_SINK)
   CONSTANT(GL_MINMAX)
   CONSTANT(GL_MINMAX_FORMAT)
   CONSTANT(GL_MINMAX_SINK)
   CONSTANT(GL_TABLE_TOO_LARGE)
   /* GL_EXT_blend_color, GL_EXT_blend_minmax */
   CONSTANT(GL_BLEND_EQUATION)
   CONSTANT(GL_MIN)
   CONSTANT(GL_MAX)
   CONSTANT(GL_FUNC_ADD)
   CONSTANT(GL_FUNC_SUBTRACT)
   CONSTANT(GL_FUNC_REVERSE_SUBTRACT)
   CONSTANT(GL_BLEND_COLOR)
#endif

#ifdef GL_VERSION_1_3
   /* OpenGL 1.3 */
   /* multitexture */
   CONSTANT(GL_TEXTURE0)
   CONSTANT(GL_TEXTURE1)
   CONSTANT(GL_TEXTURE2)
   CONSTANT(GL_TEXTURE3)
   CONSTANT(GL_TEXTURE4)
   CONSTANT(GL_TEXTURE5)
   CONSTANT(GL_TEXTURE6)
   CONSTANT(GL_TEXTURE7)
   CONSTANT(GL_TEXTURE8)
   CONSTANT(GL_TEXTURE9)
   CONSTANT(GL_TEXTURE10)
   CONSTANT(GL_TEXTURE11)
   CONSTANT(GL_TEXTURE12)
   CONSTANT(GL_TEXTURE13)
   CONSTANT(GL_TEXTURE14)
   CONSTANT(GL_TEXTURE15)
   CONSTANT(GL_TEXTURE16)
   CONSTANT(GL_TEXTURE17)
   CONSTANT(GL_TEXTURE18)
   CONSTANT(GL_TEXTURE19)
   CONSTANT(GL_TEXTURE20)
   CONSTANT(GL_TEXTURE21)
   CONSTANT(GL_TEXTURE22)
   CONSTANT(GL_TEXTURE23)
   CONSTANT(GL_TEXTURE24)
   CONSTANT(GL_TEXTURE25)
   CONSTANT(GL_TEXTURE26)
   CONSTANT(GL_TEXTURE27)
   CONSTANT(GL_TEXTURE28)
   CONSTANT(GL_TEXTURE29)
   CONSTANT(GL_TEXTURE30)
   CONSTANT(GL_TEXTURE31)
   CONSTANT(GL_ACTIVE_TEXTURE)
   CONSTANT(GL_CLIENT_ACTIVE_TEXTURE)
   CONSTANT(GL_MAX_TEXTURE_UNITS)
   /* texture_cube_map */
   CONSTANT(GL_NORMAL_MAP)
   CONSTANT(GL_REFLECTION_MAP)
   CONSTANT(GL_TEXTURE_CUBE_MAP)
   CONSTANT(GL_TEXTURE_BINDING_CUBE_MAP)
   CONSTANT(GL_TEXTURE_CUBE_MAP_POSITIVE_X)
   CONSTANT(GL_TEXTURE_CUBE_MAP_NEGATIVE_X)
   CONSTANT(GL_TEXTURE_CUBE_MAP_POSITIVE_Y)
   CONSTANT(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)
   CONSTANT(GL_TEXTURE_CUBE_MAP_POSITIVE_Z)
   CONSTANT(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
   CONSTANT(GL_PROXY_TEXTURE_CUBE_MAP)
   CONSTANT(GL_MAX_CUBE_MAP_TEXTURE_SIZE)
   /* texture_compression */
   CONSTANT(GL_COMPRESSED_ALPHA)
   CONSTANT(GL_COMPRESSED_LUMINANCE)
   CONSTANT(GL_COMPRESSED_LUMINANCE_ALPHA)
   CONSTANT(GL_COMPRESSED_INTENSITY)
   CONSTANT(GL_COMPRESSED_RGB)
   CONSTANT(GL_COMPRESSED_RGBA)
   CONSTANT(GL_TEXTURE_COMPRESSION_HINT)
   CONSTANT(GL_TEXTURE_COMPRESSED_IMAGE_SIZE)
   CONSTANT(GL_TEXTURE_COMPRESSED)
   CONSTANT(GL_NUM_COMPRESSED_TEXTURE_FORMATS)
   CONSTANT(GL_COMPRESSED_TEXTURE_FORMATS)
   /* multisample */
   CONSTANT(GL_MULTISAMPLE)
   CONSTANT(GL_SAMPLE_ALPHA_TO_COVERAGE)
   CONSTANT(GL_SAMPLE_ALPHA_TO_ONE)
   CONSTANT(GL_SAMPLE_COVERAGE)
   CONSTANT(GL_SAMPLE_BUFFERS)
   CONSTANT(GL_SAMPLES)
   CONSTANT(GL_SAMPLE_COVERAGE_VALUE)
   CONSTANT(GL_SAMPLE_COVERAGE_INVERT)
   CONSTANT(GL_MULTISAMPLE_BIT)
   /* transpose_matrix */
   CONSTANT(GL_TRANSPOSE_MODELVIEW_MATRIX)
   CONSTANT(GL_TRANSPOSE_PROJECTION_MATRIX)
   CONSTANT(GL_TRANSPOSE_TEXTURE_MATRIX)
   CONSTANT(GL_TRANSPOSE_COLOR_MATRIX)
   /* texture_env_combine */
   CONSTANT(GL_COMBINE)
   CONSTANT(GL_COMBINE_RGB)
   CONSTANT(GL_COMBINE_ALPHA)
   CONSTANT(GL_SOURCE0_RGB)
   CONSTANT(GL_SOURCE1_RGB)
   CONSTANT(GL_SOURCE2_RGB)
   CONSTANT(GL_SOURCE0_ALPHA)
   CONSTANT(GL_SOURCE1_ALPHA)
   CONSTANT(GL_SOURCE2_ALPHA)
   CONSTANT(GL_OPERAND0_RGB)
   CONSTANT(GL_OPERAND1_RGB)
   CONSTANT(GL_OPERAND2_RGB)
   CONSTANT(GL_OPERAND0_ALPHA)
   CONSTANT(GL_OPERAND1_ALPHA)
   CONSTANT(GL_OPERAND2_ALPHA)
   CONSTANT(GL_RGB_SCALE)
   CONSTANT(GL_ADD_SIGNED)
   CONSTANT(GL_INTERPOLATE)
   CONSTANT(GL_SUBTRACT)
   CONSTANT(GL_CONSTANT)
   CONSTANT(GL_PRIMARY_COLOR)
   CONSTANT(GL_PREVIOUS)
   /* texture_env_dot3 */
   CONSTANT(GL_DOT3_RGB)
   CONSTANT(GL_DOT3_RGBA)
   /* texture_border_clamp */
   CONSTANT(GL_CLAMP_TO_BORDER)
#endif

   /* =============================================================== */
   /* OpenGL Functions                                                */
   /* =============================================================== */
   /* order same as: http://rush3d.com/reference/opengl-bluebook-1.0/ */

   FUN   (glBegin)
   FUN   (glEnd)
   FUN   (glVertex2d)
   FUN   (glVertex3d)
   FUN   (glVertex4d)
   FUN   (glRectd)
   FUN   (glEdgeFlag)
   FUN   (glRotated)
   FUN   (glTranslated)
   FUN   (glScaled)
   FUN   (glMultMatrixd)
   FUN   (glFrustum)
   FUN   (glOrtho)
   FUN   (glLoadMatrixd)
   FUN   (glLoadIdentity)
   FUN   (glMatrixMode)
   FUN   (glPushMatrix)
   FUN   (glPopMatrix)
   FUN   (glDepthRange)
   FUN   (glViewport)
   FUN   (glColor3d)
   FUN   (glColor4d)
   FUN   (glIndexd)
   FUN   (glNormal3d)
   FUN   (glLightf)
   FUN   (glLightfv)
   FUN   (glMaterialf)
   FUN   (glMaterialfv)
   FUN   (glLightModelf)
   FUN   (glShadeModel)
   FUN   (glFrontFace)
   FUN   (glColorMaterial)
   FUN   (glGetLightfv)
   FUN   (glGetMaterialfv)
   FUN   (glClipPlane)
   FUN   (glGetClipPlane)
   FUN   (glRasterPos2d)
   FUN   (glRasterPos3d)
   FUN   (glRasterPos4d)
   FUN   (glBitmap)
   FUN   (glPointSize)
   FUN   (glLineWidth)
   FUN   (glLineStipple)
   FUN   (glPolygonStipple)
   FUN   (glGetPolygonStipple)
   FUN   (glCullFace)
   FUN   (glPolygonMode)
   FUN   (glReadBuffer)
   FUN   (glReadPixels)
   FUN   (glDrawPixels)
   FUN   (glCopyPixels)
   FUN   (glPixelStorei)
   FUN   (glPixelStoref)
   FUN   (glPixelTransferf)
   FUN   (glPixelMapfv)
   FUN   (glGetPixelMapfv)
   FUN   (glPixelZoom)
   FUN   (glTexParameterf)
   FUN   (glTexEnvf)
   FUN   (glTexCoord1d)
   FUN   (glTexCoord2d)
   FUN   (glTexCoord3d)
   FUN   (glTexCoord4d)
   FUN   (glTexGend)
   FUN   (glTexImage1D)
   FUN   (glTexImage2D)
   FUN   (glGetTexEnvfv)
   FUN   (glGetTexGenfv)
   FUN   (glGetTexImage)
   FUN   (glGetTexLevelParameterfv)
   FUN   (glGetTexParameterfv)

   FUN   (glGenTextures)
   FUN   (glBindTexture)
   FUN   (glDeleteTextures)

   FUN   (glFogf)
   FUN   (glScissor)
   FUN   (glAlphaFunc)
   FUN   (glStencilFunc)
   FUN   (glStencilOp)
   FUN   (glDepthFunc)
   FUN   (glBlendFunc)
   FUN   (glLogicOp)
   FUN   (glClear)
   FUN   (glClearAccum)
   FUN   (glClearColor)
   FUN   (glClearDepth)
   FUN   (glClearIndex)
   FUN   (glClearStencil)
   FUN   (glDrawBuffer)
   FUN   (glIndexMask)
   FUN   (glColorMask)
   FUN   (glDepthMask)
   FUN   (glStencilMask)
   FUN   (glAccum)
   FUN   (glRenderMode)
   FUN   (glSelectBuffer)
   FUN   (glFeedbackBuffer)
   FUN   (glPassThrough)
   FUN   (glInitNames)
   FUN   (glLoadName)
   FUN   (glPushName)
   FUN   (glPopName)
   FUN   (glNewList)
   FUN   (glEndList)
   FUN   (glDeleteLists)
   FUN   (glCallList)
   FUN   (glCallLists)
   FUN   (glGenLists)
   FUN   (glIsList)
   FUN   (glListBase)
   FUN   (glEnable)
   FUN   (glDisable)
   FUN   (glIsEnabled)
   FUN   (glFinish)
   FUN   (glFlush)
   FUN   (glHint)
   FUN   (glGetError)
   FUN   (glGetString)

   FUN   (glGetBooleanv)
   FUN   (glGetDoublev)
   FUN   (glGetFloatv)
   FUN   (glGetIntegerv)

   FUN   (glPushAttrib)
   FUN   (glPopAttrib)
}


LUALIB_API int luaopen_luagl(lua_State * L)
{
   register_gl(L);

   lua_newtable(L);

   lua_pushstring(L, "VERSION");
   lua_pushstring(L, VERSION);
   lua_settable(L, -3);

   lua_pushstring(L, MYNAME);
   lua_pushvalue(L, -2);
   lua_settable(L, LUA_GLOBALSINDEX);

   return 1;
}
