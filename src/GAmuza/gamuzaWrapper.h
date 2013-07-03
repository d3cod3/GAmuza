/*
 * Extending ofxLuaWrapper for GAmuza 0.3 | ALMOST ENTIRE OF 0.7.4 Wrapper + GAmuza Wrapper + OPENGL 1.1 Wrapper
 *
 * ORIGINAL FILE FROM:
 * Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 * This project uses the following libraries:
 *
 * Lua, Copyright (c) 1994–2011 Lua.org, PUC-Rio using the MIT License.
 * See the file "COPYRIGHT" in src/lua.
 * See http://www.lua.org/docs.html for documentation
 *
 * Luabind, Copyright (c) 2003 Daniel Wallin and Arvid Norberg using the
 * MIT License. See the file "LICENSE" in src/luabind.
 * See http://www.rasterbar.com/products/luabind/docs.html for documentation
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxLua.h"

#include "gamuzaGetters.h"
#include "gamuzaIncludes.h"


class ofGamuzaWrapper{
	
	public:
	
	/// static function called when binding
	static void bind(ofxLua& lua) {
		
		using namespace luabind;
        
        
		module(lua)
		[
         
         //////////////////////////////////////////////////////////////
         ///////////////////////////////
         /// OpenFrameworks 0.7.4 api wrapper
         ///
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section arduino [ofArduino]
         
         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM, MANAGED FROM GUI (arduino module)
         
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section 3D [ofNode, ofEasyCam, ofMesh, ofCamera]
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofNode
         
         class_<ofNode>("ofNode")
		 .def(constructor<>())
		 .def("setParent", (void(ofNode::*)(ofNode&)) &ofNode::setParent)
         .def("clearParent", (void(ofNode::*)(void)) &ofNode::clearParent)
         .def("getParent", (ofNode(ofNode::*)(void)) &ofNode::getParent)
         .def("getPosition", (ofVec3f(ofNode::*)(void)) &ofNode::getPosition)
         .def("getX", (float(ofNode::*)(void)) &ofNode::getX)
         .def("getY", (float(ofNode::*)(void)) &ofNode::getY)
         .def("getZ", (float(ofNode::*)(void)) &ofNode::getZ)
         .def("getXAxis", (ofVec3f(ofNode::*)(void)) &ofNode::getXAxis)
         .def("getYAxis", (ofVec3f(ofNode::*)(void)) &ofNode::getYAxis)
         .def("getZAxis", (ofVec3f(ofNode::*)(void)) &ofNode::getZAxis)
         .def("getSideDir", (ofVec3f(ofNode::*)(void)) &ofNode::getSideDir)
         .def("getLookAtDir", (ofVec3f(ofNode::*)(void)) &ofNode::getLookAtDir)
         .def("getUpDir", (ofVec3f(ofNode::*)(void)) &ofNode::getUpDir)
         .def("getPitch", (float(ofNode::*)(void)) &ofNode::getPitch)
         .def("getHeading", (float(ofNode::*)(void)) &ofNode::getHeading)
         .def("getRoll", (float(ofNode::*)(void)) &ofNode::getRoll)
         .def("getOrientationQuat", (ofQuaternion(ofNode::*)(void)) &ofNode::getOrientationQuat)
         .def("getOrientationEuler", (ofVec3f(ofNode::*)(void)) &ofNode::getOrientationEuler)
         .def("getScale", (ofVec3f(ofNode::*)(void)) &ofNode::getScale)
         .def("getLocalTransformMatrix", (ofMatrix4x4(ofNode::*)(void)) &ofNode::getLocalTransformMatrix)
         .def("getGlobalTransformMatrix", (ofMatrix4x4(ofNode::*)(void)) &ofNode::getGlobalTransformMatrix)
         .def("getGlobalPosition", (ofVec3f(ofNode::*)(void)) &ofNode::getGlobalPosition)
         .def("getGlobalOrientation", (ofQuaternion(ofNode::*)(void)) &ofNode::getGlobalOrientation)
         .def("setTransformMatrix", (void(ofNode::*)(const ofMatrix4x4&)) &ofNode::setTransformMatrix)
         .def("setPosition", (void(ofNode::*)(float,float,float)) &ofNode::setPosition)
         .def("setPosition", (void(ofNode::*)(const ofVec3f&)) &ofNode::setPosition)
         .def("setGlobalPosition", (void(ofNode::*)(float,float,float)) &ofNode::setGlobalPosition)
         .def("setGlobalPosition", (void(ofNode::*)(const ofVec3f&)) &ofNode::setGlobalPosition)
         .def("setOrientation", (void(ofNode::*)(const ofQuaternion&)) &ofNode::setOrientation)
         .def("setOrientation", (void(ofNode::*)(const ofVec3f&)) &ofNode::setOrientation)
         .def("setGlobalOrientation", (void(ofNode::*)(const ofQuaternion&)) &ofNode::setGlobalOrientation)
         .def("setScale", (void(ofNode::*)(float,float,float)) &ofNode::setScale)
         .def("setScale", (void(ofNode::*)(const ofVec3f&)) &ofNode::setScale)         
         .def("move", (void(ofNode::*)(float,float,float)) &ofNode::move)
         .def("move", (void(ofNode::*)(const ofVec3f&)) &ofNode::move)
         .def("truck", (void(ofNode::*)(float)) &ofNode::truck)
         .def("boom", (void(ofNode::*)(float)) &ofNode::boom)
         .def("dolly", (void(ofNode::*)(float)) &ofNode::dolly)
         .def("tilt", (void(ofNode::*)(float)) &ofNode::tilt)
         .def("pan", (void(ofNode::*)(float)) &ofNode::pan)
         .def("roll", (void(ofNode::*)(float)) &ofNode::roll)
         .def("rotate", (void(ofNode::*)(const ofQuaternion&)) &ofNode::rotate)
         .def("rotate", (void(ofNode::*)(float,const ofVec3f&)) &ofNode::rotate)
         .def("rotate", (void(ofNode::*)(float,float,float,float)) &ofNode::rotate)
         .def("rotateAround", (void(ofNode::*)(const ofQuaternion&,const ofVec3f&)) &ofNode::rotateAround)
         .def("rotateAround", (void(ofNode::*)(float,const ofVec3f&,const ofVec3f&)) &ofNode::rotateAround)
         .def("lookAt", (void(ofNode::*)(const ofVec3f&,ofVec3f)) &ofNode::lookAt)
         .def("orbit", (void(ofNode::*)(float,float,float,const ofVec3f&)) &ofNode::orbit)
         .def("orbit", (void(ofNode::*)(float,float,float,ofNode&)) &ofNode::orbit)
         .def("transformGL", (void(ofNode::*)(void)) &ofNode::transformGL)
         .def("restoreTransformGL", (void(ofNode::*)(void)) &ofNode::restoreTransformGL)
         .def("resetTransform", (void(ofNode::*)(void)) &ofNode::resetTransform)
         .def("draw", (void(ofNode::*)(void)) &ofNode::draw),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofEasyCam
         
         class_<ofEasyCam>("ofEasyCam")
		 .def(constructor<>())
         .def("beginCamera", (void(ofEasyCam::*)(ofRectangle)) &ofEasyCam::begin)
         .def("endCamera", (void(ofEasyCam::*)(void)) &ofEasyCam::end)
         .def("reset", (void(ofEasyCam::*)(void)) &ofEasyCam::reset)
         .def("setTarget", (void(ofEasyCam::*)(const ofVec3f&)) &ofEasyCam::setTarget)
         .def("setTarget", (void(ofEasyCam::*)(ofNode&)) &ofEasyCam::setTarget)
         .def("getTarget", (ofNode(ofEasyCam::*)(void)) &ofEasyCam::getTarget)
         .def("setDistance", (void(ofEasyCam::*)(float)) &ofEasyCam::setDistance)
         .def("getDistance", (float(ofEasyCam::*)(void)) &ofEasyCam::getDistance)
         .def("setDrag", (void(ofEasyCam::*)(float)) &ofEasyCam::setDrag)
         .def("getDrag", (float(ofEasyCam::*)(void)) &ofEasyCam::getDrag)
         .def("enableMouseInput", (void(ofEasyCam::*)(void)) &ofEasyCam::enableMouseInput)
         .def("disableMouseInput", (void(ofEasyCam::*)(void)) &ofEasyCam::disableMouseInput)
         .def("getMouseInputEnabled", (bool(ofEasyCam::*)(void)) &ofEasyCam::getMouseInputEnabled),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMesh
         
         class_<ofMesh>("ofMesh")
		 .def(constructor<>())
         .def("setMode", (void(ofMesh::*)(ofPrimitiveMode)) &ofMesh::setMode)
         .def("getMode", (ofPrimitiveMode(ofMesh::*)(void)) &ofMesh::getMode)
         .def("clear", (void(ofMesh::*)(void)) &ofMesh::clear)
         .def("setupIndicesAuto", (void(ofMesh::*)(void)) &ofMesh::setupIndicesAuto)
         .def("getVertex", (ofVec3f(ofMesh::*)(int)) &ofMesh::getVertex)
         .def("removeVertex", (void(ofMesh::*)(ofIndexType)) &ofMesh::removeVertex)
         .def("clearVertices", (void(ofMesh::*)(void)) &ofMesh::clearVertices)
         .def("getNormal", (ofVec3f(ofMesh::*)(int)) &ofMesh::getNormal)
         .def("removeNormal", (void(ofMesh::*)(ofIndexType)) &ofMesh::removeNormal)
         .def("clearNormals", (void(ofMesh::*)(void)) &ofMesh::clearNormals)
         .def("getColor", (ofFloatColor(ofMesh::*)(int)) &ofMesh::getColor)
         .def("removeColor", (void(ofMesh::*)(ofIndexType)) &ofMesh::removeColor)
         .def("clearColors", (void(ofMesh::*)(void)) &ofMesh::clearColors)
         .def("getTexCoord", (ofVec2f(ofMesh::*)(int)) &ofMesh::getTexCoord)
         .def("removeTexCoord", (void(ofMesh::*)(ofIndexType)) &ofMesh::removeTexCoord)
         .def("clearTexCoords", (void(ofMesh::*)(void)) &ofMesh::clearTexCoords)
         .def("getIndex", (ofIndexType(ofMesh::*)(int)) &ofMesh::getTexCoord)
         .def("addIndex", (void(ofMesh::*)(ofIndexType)) &ofMesh::addIndex)
         .def("removeIndex", (void(ofMesh::*)(ofIndexType)) &ofMesh::removeIndex)
         .def("setIndex", (void(ofMesh::*)(int,ofIndexType)) &ofMesh::setIndex)
         .def("clearIndices", (void(ofMesh::*)(void)) &ofMesh::clearIndices)
         .def("addTriangle", (void(ofMesh::*)(ofIndexType,ofIndexType,ofIndexType)) &ofMesh::addTriangle)
         .def("getNumVertices", (int(ofMesh::*)(void)) &ofMesh::getNumVertices)
         .def("getNumColors", (int(ofMesh::*)(void)) &ofMesh::getNumColors)
         .def("getNumNormals", (int(ofMesh::*)(void)) &ofMesh::getNumNormals)
         .def("getNumTexCoords", (int(ofMesh::*)(void)) &ofMesh::getNumTexCoords)
         .def("getNumIndices", (int(ofMesh::*)(void)) &ofMesh::getNumIndices)
         .def("getVerticesPointer", (ofVec3f*(ofMesh::*)(void)) &ofMesh::getVerticesPointer)
         .def("getColorsPointer", (ofFloatColor*(ofMesh::*)(void)) &ofMesh::getColorsPointer)
         .def("getNormalsPointer", (ofVec3f*(ofMesh::*)(void)) &ofMesh::getNormalsPointer)
         .def("getTexCoordsPointer", (ofVec2f*(ofMesh::*)(void)) &ofMesh::getTexCoordsPointer)
         .def("getIndexPointer", (ofIndexType*(ofMesh::*)(void)) &ofMesh::getIndexPointer)
         .def("setName", (void(ofMesh::*)(string)) &ofMesh::setName)
         .def("haveVertsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveVertsChanged)
         .def("haveColorsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveColorsChanged)
         .def("haveNormalsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveNormalsChanged)
         .def("haveTexCoordsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveTexCoordsChanged)
         .def("haveIndicesChanged", (bool(ofMesh::*)(void)) &ofMesh::haveIndicesChanged)
         .def("hasVertices", (bool(ofMesh::*)(void)) &ofMesh::hasVertices)
         .def("hasColors", (bool(ofMesh::*)(void)) &ofMesh::hasColors)
         .def("hasNormals", (bool(ofMesh::*)(void)) &ofMesh::hasNormals)
         .def("hasTexCoords", (bool(ofMesh::*)(void)) &ofMesh::hasTexCoords)
         .def("hasIndices", (bool(ofMesh::*)(void)) &ofMesh::hasIndices)
         .def("drawVertices", (void(ofMesh::*)(void)) &ofMesh::drawVertices)
         .def("drawWireframe", (void(ofMesh::*)(void)) &ofMesh::drawWireframe)
         .def("drawFaces", (void(ofMesh::*)(void)) &ofMesh::drawFaces)
         .def("draw", (void(ofMesh::*)(void)) &ofMesh::draw)
         .def("addVertex", (void(ofMesh::*)(const ofVec3f&)) &ofMesh::addVertex)
         .def("setVertex", (void(ofMesh::*)(int,const ofVec3f&)) &ofMesh::setVertex)
         .def("addNormal", (void(ofMesh::*)(const ofVec3f&)) &ofMesh::addNormal)
         .def("setNormal", (void(ofMesh::*)(int,const ofVec3f&)) &ofMesh::setNormal)
         .def("addColor", (void(ofMesh::*)(const ofFloatColor&)) &ofMesh::addColor)
         .def("setColor", (void(ofMesh::*)(int,const ofFloatColor&)) &ofMesh::setColor)
         .def("addTexCoord", (void(ofMesh::*)(const ofVec2f&)) &ofMesh::addTexCoord)
         .def("setTexCoord", (void(ofMesh::*)(int,const ofVec2f&)) &ofMesh::setTexCoord)
         .def("addIndices", (void(ofMesh::*)(const ofIndexType*,int)) &ofMesh::addIndices)
         .def("getCentroid", (const ofVec3f(ofMesh::*)(void)) &ofMesh::getCentroid),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofCamera
         
         class_<ofCamera>("ofCamera")
		 .def(constructor<>())
		 .def("setFov", (void(ofCamera::*)(float)) &ofCamera::setFov)
         .def("setNearClip", (void(ofCamera::*)(float)) &ofCamera::setNearClip)
		 .def("setFarClip", (void(ofCamera::*)(float)) &ofCamera::setFarClip)
         .def("setLensOffset", (void(ofCamera::*)(const ofVec2f&)) &ofCamera::setLensOffset)
         .def("setAspectRatio", (void(ofCamera::*)(float)) &ofCamera::setAspectRatio)
         .def("setForceAspectRatio", (void(ofCamera::*)(bool)) &ofCamera::setForceAspectRatio)
         .def("getFov", (const float(ofCamera::*)(void)) &ofCamera::getFov)
         .def("getNearClip", (const float(ofCamera::*)(void)) &ofCamera::getNearClip)
		 .def("getFarClip", (const float(ofCamera::*)(void)) &ofCamera::getFarClip)
         .def("getLensOffset", (const ofVec2f(ofCamera::*)(void)) &ofCamera::getLensOffset)
         .def("getForceAspectRatio", (const bool(ofCamera::*)(void)) &ofCamera::getForceAspectRatio)
         .def("getAspectRatio", (const float(ofCamera::*)(void)) &ofCamera::getAspectRatio)
         .def("setupPerspective", (void(ofCamera::*)(bool,float,float,float,const ofVec2f&)) &ofCamera::setupPerspective)
         .def("setupOffAxisViewPortal", (void(ofCamera::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofCamera::setupOffAxisViewPortal)
         .def("enableOrtho", (void(ofCamera::*)(void)) &ofCamera::enableOrtho)
         .def("disableOrtho", (void(ofCamera::*)(void)) &ofCamera::disableOrtho)
         .def("getOrtho", (bool(ofCamera::*)(void)) &ofCamera::getOrtho)
         .def("getModelViewMatrix", (ofMatrix4x4(ofCamera::*)(void)) &ofCamera::getModelViewMatrix)
         .def("setPosition", (void(ofCamera::*)(float,float,float)) &ofCamera::setPosition)
         .def("setPosition", (void(ofCamera::*)(const ofVec3f&)) &ofCamera::setPosition)
         .def("setScale", (void(ofCamera::*)(float)) &ofCamera::setScale)
         .def("setScale", (void(ofCamera::*)(float,float,float)) &ofCamera::setScale)
         .def("setScale", (void(ofCamera::*)(const ofVec3f&)) &ofCamera::setScale)
         .def("move", (void(ofCamera::*)(float,float,float)) &ofCamera::move)
         .def("move", (void(ofCamera::*)(const ofVec3f&)) &ofCamera::move)
         .def("truck", (void(ofCamera::*)(float)) &ofCamera::truck)
         .def("boom", (void(ofCamera::*)(float)) &ofCamera::boom)
         .def("dolly", (void(ofCamera::*)(float)) &ofCamera::dolly)
         .def("tilt", (void(ofCamera::*)(float)) &ofCamera::tilt)
         .def("pan", (void(ofCamera::*)(float)) &ofCamera::pan)
         .def("roll", (void(ofCamera::*)(float)) &ofCamera::roll)
         .def("rotate", (void(ofCamera::*)(float,const ofVec3f&)) &ofCamera::rotate)
         .def("rotate", (void(ofCamera::*)(float,float,float,float)) &ofCamera::rotate)
         .def("lookAt", (void(ofCamera::*)(const ofVec3f&,ofVec3f)) &ofCamera::lookAt)
         .def("orbit", (void(ofCamera::*)(float,float,float,const ofVec3f&)) &ofCamera::orbit)
         .def("transformGL", (void(ofCamera::*)(void)) &ofCamera::transformGL)
         .def("restoreTransformGL", (void(ofCamera::*)(void)) &ofCamera::restoreTransformGL)
         .def("resetTransform", (void(ofCamera::*)(void)) &ofCamera::resetTransform)
         .def("draw", (void(ofCamera::*)(void)) &ofCamera::draw)
         .def("getImagePlaneDistance", (float(ofCamera::*)(ofRectangle)) &ofCamera::getImagePlaneDistance)
         .def("getProjectionMatrix", (ofMatrix4x4(ofCamera::*)(ofRectangle)) &ofCamera::getProjectionMatrix)
         .def("getModelViewProjectionMatrix", (ofMatrix4x4(ofCamera::*)(ofRectangle)) &ofCamera::getModelViewProjectionMatrix)
         .def("worldToScreen", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::worldToScreen)
         .def("screenToWorld", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::screenToWorld)
         .def("worldToCamera", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::worldToCamera)
         .def("cameraToWorld", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::cameraToWorld)
         
         .def("beginCamera", (void(ofCamera::*)(ofRectangle)) &ofCamera::begin)
         .def("endCamera", (void(ofCamera::*)(void)) &ofCamera::end),
         
         def("ofDrawAxis", (void(*)(float)) &ofDrawAxis),
         def("ofDrawGrid", (void(*)(float,float,bool,bool,bool,bool)) &ofDrawGrid),
         def("ofDrawGridPlane", (void(*)(float,float,bool)) &ofDrawGridPlane),
         def("ofDrawArrow", (void(*)(const ofVec3f&,const ofVec3f&,float)) &ofDrawArrow),
         def("ofDrawRotationAxes", (void(*)(float,float,int)) &ofDrawRotationAxes),
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section math [ofMath, ofMatrix3x3, ofMatrix4x4, ofQuaternion, ofVec2f, ofVec3f, ofVec4f]
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMath
         
         def("ofSeedRandom", (void(*)(void)) &ofSeedRandom),
		 def("ofSeedRandom", (void(*)(int)) &ofSeedRandom),
         def("ofRandom", (float(*)(float)) &ofRandom),
		 def("ofRandom", (float(*)(float,float)) &ofRandom),
		 def("ofRandomf", (float(*)(void)) &ofRandomf),
		 def("ofRandomuf", (float(*)(void)) &ofRandomuf),
         def("ofNextPow2", (int(*)(int)) &ofNextPow2),
		 def("ofNormalize", &ofNormalize),
		 def("ofMap", (float(*)(float,float,float,float,float,bool)) &ofMap),
         def("ofMap", &map5),
		 def("ofClamp", &ofClamp),
		 def("ofLerp", &ofLerp),
		 def("ofDist", &ofDist),
		 def("ofDistSquared", &ofDistSquared),
		 def("ofSign", &ofSign),
		 def("ofInRange", &ofInRange),
		 def("ofRadToDeg", &ofRadToDeg),
		 def("ofDegToRad", &ofDegToRad),
		 def("ofLerpDegrees", &ofLerpDegrees),
		 def("ofLerpRadians", &ofLerpRadians),
		 def("ofAngleDifferenceDegrees", &ofAngleDifferenceDegrees),
		 def("ofAngleDifferenceRadians", &ofAngleDifferenceRadians),
		 def("ofWrapRadians", &ofWrapRadians),
		 def("ofWrapDegrees", &ofWrapDegrees),
		 def("ofNoise", (float(*)(float)) &ofNoise),
		 def("ofNoise", (float(*)(float,float)) &ofNoise),
		 def("ofNoise", (float(*)(float,float,float)) &ofNoise),
		 def("ofNoise", (float(*)(float,float,float,float)) &ofNoise),
		 def("ofSignedNoise", (float(*)(float)) &ofSignedNoise),
		 def("ofSignedNoise", (float(*)(float,float)) &ofSignedNoise),
		 def("ofSignedNoise", (float(*)(float,float,float)) &ofSignedNoise),
		 def("ofSignedNoise", (float(*)(float,float,float,float)) &ofSignedNoise),
         def("ofInsidePoly", (bool(*)(float,float,const vector<ofPoint>&)) &ofInsidePoly),
         def("ofInsidePoly", (bool(*)(const ofPoint&,const vector<ofPoint>&)) &ofInsidePoly),
         def("ofLineSegmentIntersection", (bool(*)(ofPoint,ofPoint,ofPoint,ofPoint,ofPoint)) &ofLineSegmentIntersection),
         def("ofBezierPoint", (ofPoint(*)(ofPoint,ofPoint,ofPoint,ofPoint,float)) &ofBezierPoint),
         def("ofCurvePoint", (ofPoint(*)(ofPoint,ofPoint,ofPoint,ofPoint,float)) &ofCurvePoint),
         def("ofBezierTangent", (ofPoint(*)(ofPoint,ofPoint,ofPoint,ofPoint,float)) &ofBezierTangent),
         def("ofCurveTangent", (ofPoint(*)(ofPoint,ofPoint,ofPoint,ofPoint,float)) &ofCurveTangent),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMatrix3x3
         
         class_<ofMatrix3x3>("ofMatrix3x3")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float,float,float,float,float,float>())
         .def("set", (void(ofMatrix3x3::*)(float,float,float,float,float,float,float,float,float)) &ofMatrix3x3::set)
         .def("transpose", (void(ofMatrix3x3::*)(void)) &ofMatrix3x3::transpose)
         //.def("transpose", (void(ofMatrix3x3::*)(void)) &ofMatrix3x3::transpose)
         //.def("determinant", (const float(ofMatrix3x3::*)(void)) &ofMatrix3x3::determinant)
         .def("determinant", (float(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::determinant)
         .def("invert", (void(ofMatrix3x3::*)(void)) &ofMatrix3x3::invert)
         .def("inverse", (ofMatrix3x3(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::inverse)
         .def(self + other<const ofMatrix3x3&>())
         .def(self - other<const ofMatrix3x3&>())
         .def(self * other<const ofMatrix3x3&>())
         .def(self + other<float>())
         .def(self - other<float>())
         .def(self * other<float>())
         .def(self / other<float>())
         .def_readonly("a", &ofMatrix3x3::a)
		 .def_readonly("b", &ofMatrix3x3::b)
         .def_readonly("c", &ofMatrix3x3::c)
		 .def_readonly("d", &ofMatrix3x3::d)
         .def_readonly("e", &ofMatrix3x3::e)
		 .def_readonly("f", &ofMatrix3x3::f)
         .def_readonly("g", &ofMatrix3x3::g)
		 .def_readonly("h", &ofMatrix3x3::h)
         .def_readonly("i", &ofMatrix3x3::i),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMatrix4x4
         
         class_<ofMatrix4x4>("ofMatrix4x4")
		 .def(constructor<>())
         .def(constructor<const ofMatrix4x4&>())
         .def(constructor<const ofQuaternion&>())
         //.def(constructor<float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float>())
         .def("getRowAsVec3f", (ofVec3f(ofMatrix4x4::*)(int)) &ofMatrix4x4::getRowAsVec3f)
         .def("getRowAsVec4f", (ofVec4f(ofMatrix4x4::*)(int)) &ofMatrix4x4::getRowAsVec4f)
         .def("isValid", (bool(ofMatrix4x4::*)(void)) &ofMatrix4x4::isValid)
         .def("isNaN", (bool(ofMatrix4x4::*)(void)) &ofMatrix4x4::isNaN)
         .def("set", (void(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::set)
         .def("isIdentity", (bool(ofMatrix4x4::*)(void)) &ofMatrix4x4::isIdentity)
         .def("makeIdentityMatrix", (void(ofMatrix4x4::*)(void)) &ofMatrix4x4::makeIdentityMatrix)
         .def("makeScaleMatrix", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::makeScaleMatrix)
         .def("makeScaleMatrix", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::makeScaleMatrix)
         .def("makeTranslationMatrix", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::makeTranslationMatrix)
         .def("makeTranslationMatrix", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::makeTranslationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,const ofVec3f&)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeInvertOf", (bool(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::makeInvertOf)
         .def("makeOrthoNormalOf", (void(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::makeOrthoNormalOf)
         .def("makeFromMultiplicationOf", (void(ofMatrix4x4::*)(const ofMatrix4x4&,const ofMatrix4x4&)) &ofMatrix4x4::makeFromMultiplicationOf)
         .def("getInverse", (void(ofMatrix4x4::*)(void)) &ofMatrix4x4::getInverse)
         .def("makeOrthoMatrix", (void(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::makeOrthoMatrix)
         .def("makeOrtho2DMatrix", (void(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::makeOrtho2DMatrix)
         .def("makeFrustumMatrix", (void(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::makeFrustumMatrix)
         .def("makePerspectiveMatrix", (void(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::makePerspectiveMatrix)
         .def("makeLookAtMatrix", (void(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::makeLookAtMatrix)
         .def("makeLookAtViewMatrix", (void(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::makeLookAtViewMatrix)
         .def("getOrtho", (bool(ofMatrix4x4::*)(double&,double&,double&,double&,double&,double&)) &ofMatrix4x4::getOrtho)
         .def("getFrustum", (bool(ofMatrix4x4::*)(double&,double&,double&,double&,double&,double&)) &ofMatrix4x4::getFrustum)
         .def("getPerspective", (bool(ofMatrix4x4::*)(double&,double&,double&,double&)) &ofMatrix4x4::getPerspective)
         .def("getLookAt", (void(ofMatrix4x4::*)(ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofMatrix4x4::getLookAt)
         .def("decompose", (void(ofMatrix4x4::*)(ofVec3f&,ofQuaternion&,ofVec3f&,ofQuaternion&)) &ofMatrix4x4::decompose)
         //.def("postMult", (inline ofVec3f(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::postMult)
         //.def("postMult", (inline ofVec4f(ofMatrix4x4::*)(const ofVec4f&)) &ofMatrix4x4::postMult)
         .def(self * other<const ofVec3f&>())
         .def(self * other<const ofVec4f&>())
         .def(self * other<const ofMatrix4x4&>())
         //.def("preMult", (inline ofVec3f(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::preMult)
         //.def("preMult", (inline ofVec4f(ofMatrix4x4::*)(const ofVec4f&)) &ofMatrix4x4::preMult)
         .def("setRotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::setRotate)
         .def("setTranslation", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::setTranslation)
         .def("rotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::rotate)
         .def("translate", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::translate)
         .def("scale", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::scale)
         .def("glRotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::glRotate)
         .def("glTranslate", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::glTranslate)
         .def("glScale", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::glScale)
         .def("getRotate", (ofQuaternion(ofMatrix4x4::*)(void)) &ofMatrix4x4::getRotate)
         .def("getTranslation", (ofVec3f(ofMatrix4x4::*)(void)) &ofMatrix4x4::getTranslation)
         .def("getScale", (ofVec3f(ofMatrix4x4::*)(void)) &ofMatrix4x4::getScale)
         //.def("newIdentityMatrix", (ofMatrix4x4(ofMatrix4x4::*)(void)) &ofMatrix4x4::newIdentityMatrix)
         //.def("newScaleMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::newScaleMatrix)
         //.def("newTranslationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::newTranslationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::newRotationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::newRotationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(float,const ofVec3f&)) &ofMatrix4x4::newRotationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&)) &ofMatrix4x4::newRotationMatrix)
         //.def("getInverseOf", (ofMatrix4x4(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::getInverseOf)
         //.def("getTransposedOf", (ofMatrix4x4(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::getTransposedOf)
         //.def("getOrthoNormalOf", (ofMatrix4x4(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::getOrthoNormalOf)
         //def("newOrthoMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::newOrthoMatrix)
         //.def("newOrtho2DMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::newOrtho2DMatrix)
         //.def("newFrustumMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::newFrustumMatrix)
         //.def("newPerspectiveMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::newPerspectiveMatrix)
         //.def("newLookAtMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::newLookAtMatrix)
         //.def("transform3x3", (ofVec3f(ofMatrix4x4::*)(const ofVec3f&,const ofMatrix4x4&)) &ofMatrix4x4::transform3x3)
         //.def("transform3x3", (ofVec3f(ofMatrix4x4::*)(const ofMatrix4x4&,const ofVec3f&)) &ofMatrix4x4::transform3x3)
         .def_readonly("_mat", &ofMatrix4x4::_mat),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofQuaternion
         
         class_<ofQuaternion>("ofQuaternion")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
		 .def(constructor<const ofVec4f&>())
         .def(constructor<float,const ofVec3f&>())
         .def(constructor<float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&>())
         .def(self == other<const ofQuaternion&>())
         .def(self + other<const ofQuaternion&>())
         .def(self - other<const ofQuaternion&>())
         .def(self * other<const ofQuaternion&>())
         .def(self / other<const ofQuaternion&>())
         .def(self * other<const ofVec3f&>())
         .def(self * other<float>())
         .def(self / other<float>())
         .def("asVec4", (ofVec4f(ofQuaternion::*)(void)) &ofQuaternion::asVec4)
         .def("asVec3", (ofVec3f(ofQuaternion::*)(void)) &ofQuaternion::asVec3)
         .def("set", (void(ofQuaternion::*)(float,float,float,float)) &ofQuaternion::set)
         .def("set", (void(ofQuaternion::*)(const ofVec4f&)) &ofQuaternion::set)
         .def("set", (void(ofQuaternion::*)(const ofMatrix4x4&)) &ofQuaternion::set)
         .def("get", (void(ofQuaternion::*)(const ofMatrix4x4&)) &ofQuaternion::get)
         //.def("x", (float(ofQuaternion::*)(void)) &ofQuaternion::x)
         //.def("y", (float(ofQuaternion::*)(void)) &ofQuaternion::y)
         //.def("z", (float(ofQuaternion::*)(void)) &ofQuaternion::z)
         //.def("w", (float(ofQuaternion::*)(void)) &ofQuaternion::w)
         .def("zeroRotation", (bool(ofQuaternion::*)(void)) &ofQuaternion::zeroRotation)
         .def("length", (float(ofQuaternion::*)(void)) &ofQuaternion::length)
         .def("length2", (float(ofQuaternion::*)(void)) &ofQuaternion::length2)
         .def("conj", (ofQuaternion(ofQuaternion::*)(void)) &ofQuaternion::conj)
         .def("inverse", (ofQuaternion(ofQuaternion::*)(void)) &ofQuaternion::inverse)
         .def("makeRotate", (void(ofQuaternion::*)(float,float,float,float)) &ofQuaternion::makeRotate)
         .def("makeRotate", (void(ofQuaternion::*)(float,const ofVec3f&)) &ofQuaternion::makeRotate)
         .def("makeRotate", (void(ofQuaternion::*)(float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&)) &ofQuaternion::makeRotate)
         .def("makeRotate", (void(ofQuaternion::*)(const ofVec3f&,const ofVec3f&)) &ofQuaternion::makeRotate)
         .def("makeRotate_original", (void(ofQuaternion::*)(const ofVec3f&,const ofVec3f&)) &ofQuaternion::makeRotate_original)
         //.def("getRotate", (void(ofQuaternion::*)(float&,float&,float&,float&)) &ofQuaternion::getRotate)
         //.def("getRotate", (void(ofQuaternion::*)(float&,ofVec3f&)) &ofQuaternion::getRotate)
         .def("getEuler", (void(ofQuaternion::*)(void)) &ofQuaternion::getEuler)
         .def("slerp", (void(ofQuaternion::*)(float,const ofQuaternion&,const ofQuaternion&)) &ofQuaternion::slerp)
         .def_readonly("_v", &ofQuaternion::_v),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVec2f
         
         class_<ofVec2f>("ofVec2f")
		 .def(constructor<>())
		 .def(constructor<float,float>())
		 .def(constructor<const ofVec3f&>())
		 .def(constructor<const ofVec4f&>())
		 .def("set", (void(ofVec2f::*)(float,float)) &ofVec2f::set)
         .def("set", (void(ofVec2f::*)(const ofVec2f&)) &ofVec2f::set)
         .def(self == other<const ofVec2f&>())
         .def("match", (bool(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::match)
         .def("align", (bool(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::align)
         .def("alignRad", (bool(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::alignRad)
         .def(self + other<const ofVec2f&>())
         .def(self - other<const ofVec2f&>())
         .def(self * other<const ofVec2f&>())
         .def(self / other<const ofVec2f&>())
         .def(self + other<const float>())
         .def(self - other<const float>())
         .def(self * other<const float>())
         .def(self / other<const float>())
         .def("getScaled", (ofVec2f(ofVec2f::*)(const float)) &ofVec2f::getScaled)
         .def("scale", (ofVec2f&(ofVec2f::*)(const float)) &ofVec2f::scale)
         //.def("getRotated", (const ofVec2f(ofVec2f::*)(float)) &ofVec2f::getRotated)
         //.def("getRotatedRad", (const ofVec2f(ofVec2f::*)(float)) &ofVec2f::getRotatedRad)
         .def("rotate", (ofVec2f&(ofVec2f::*)(float)) &ofVec2f::rotate)
         .def("rotateRad", (ofVec2f&(ofVec2f::*)(float)) &ofVec2f::rotateRad)
         //.def("getRotated", (ofVec2f(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::getRotated)
         //.def("getRotatedRad", (ofVec2f(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::getRotatedRad)
         .def("rotate", (ofVec2f&(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::rotate)
         .def("rotateRad", (ofVec2f&(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::rotateRad)
		 //.def("rotated", (ofVec2f(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::rotated)
         .def("getMapped", (ofVec2f(ofVec2f::*)(const ofVec2f&,const ofVec2f&,const ofVec2f&)) &ofVec2f::getMapped)
         .def("map", (ofVec2f&(ofVec2f::*)(const ofVec2f&,const ofVec2f&,const ofVec2f&)) &ofVec2f::map)
         .def("distance", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::distance)
         .def("squareDistance", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::squareDistance)
         .def("getInterpolated", (ofVec2f(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::getInterpolated)
         .def("interpolate", (ofVec2f&(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::interpolate)
         .def("getMiddle", (ofVec2f(ofVec2f::*)(const ofVec2f&)) &ofVec2f::getMiddle)
         .def("middle", (ofVec2f&(ofVec2f::*)(const ofVec2f&)) &ofVec2f::middle)
         .def("average", (ofVec2f&(ofVec2f::*)(const ofVec2f&,int)) &ofVec2f::average)
         .def("getNormalized", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::getNormalized)
         .def("normalize", (ofVec2f&(ofVec2f::*)(void)) &ofVec2f::normalize)
         .def("getLimited", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::getLimited)
         .def("limit", (ofVec2f&(ofVec2f::*)(float)) &ofVec2f::limit)
         .def("getPerpendicular", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::getPerpendicular)
         .def("perpendicular", (ofVec2f&(ofVec2f::*)(void)) &ofVec2f::perpendicular)
         .def("length", (float(ofVec2f::*)(void)) &ofVec2f::length)
         .def("squareLength", (float(ofVec2f::*)(void)) &ofVec2f::squareLength)
         .def("angle", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::angle)
         .def("angleRad", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::angleRad)
         .def("dot", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::dot)
         .def("rescaled", (ofVec2f(ofVec2f::*)(const float)) &ofVec2f::rescaled)
         .def("rescale", (ofVec2f&(ofVec2f::*)(const float)) &ofVec2f::rescale)
         //.def("rotated", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::rotated)
         .def("normalized", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::normalized)
         .def("limited", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::limited)
         .def("perpendiculared", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::perpendiculared)
         .def("lengthSquared", (float(ofVec2f::*)(void)) &ofVec2f::lengthSquared)
         .def("interpolated", (ofVec2f(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::interpolated)
         .def("middled", (ofVec2f(ofVec2f::*)(const ofVec2f&)) &ofVec2f::middled)
         .def("mapped", (ofVec2f(ofVec2f::*)(const ofVec2f&,const ofVec2f&,const ofVec2f&)) &ofVec2f::mapped)
         .def("distanceSquared", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::distanceSquared)
         .def_readwrite("x", &ofVec2f::x)
		 .def_readwrite("y", &ofVec2f::y),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVec3f
         
         class_<ofVec3f>("ofVec3f")
		 .def(constructor<>())
		 .def(constructor<float,float,float>())
		 .def(constructor<const ofVec2f&>())
		 .def(constructor<const ofVec4f&>())
		 .def("set", (void(ofVec3f::*)(float,float,float)) &ofVec3f::set)
		 .def("set", (void(ofVec3f::*)(const ofVec3f&)) &ofVec3f::set)
         .def(self == other<const ofVec3f&>())
         .def("match", (bool(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::match)
         .def("align", (bool(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::align)
         .def("alignRad", (bool(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::alignRad)
         .def(self + other<const ofVec3f&>())
         .def(self - other<const ofVec3f&>())
         .def(self * other<const ofVec3f&>())
         .def(self / other<const ofVec3f&>())
         .def(self + other<const float>())
         .def(self - other<const float>())
         .def(self * other<const float>())
         .def(self / other<const float>())
         .def("getScaled", (ofVec3f(ofVec3f::*)(const float)) &ofVec3f::getScaled)
         .def("scale", (ofVec3f&(ofVec3f::*)(const float)) &ofVec3f::scale)
         //.def("getRotated", (ofVec3f(ofVec3f::*)(float,float,float)) &ofVec3f::getRotated)
         //.def("getRotatedRad", (ofVec3f(ofVec3f::*)(float,float,float)) &ofVec3f::getRotatedRad)
         .def("rotate", (ofVec3f&(ofVec3f::*)(float,float,float)) &ofVec3f::rotate)
         .def("rotateRad", (ofVec3f&(ofVec3f::*)(float,float,float)) &ofVec3f::rotateRad)
         //.def("getRotated", (ofVec3f(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::getRotated)
         //.def("getRotatedRad", (ofVec3f(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::getRotatedRad)
         .def("rotate", (ofVec3f&(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::rotate)
         .def("rotateRad", (ofVec3f&(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::rotateRad)
		 //.def("rotated", (ofVec3f(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::rotated)
         .def("getMapped", (ofVec3f(ofVec3f::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofVec3f::getMapped)
         .def("map", (ofVec3f&(ofVec3f::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofVec3f::map)
         .def("distance", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::distance)
         .def("squareDistance", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::squareDistance)
         .def("getInterpolated", (ofVec3f(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::getInterpolated)
         .def("interpolate", (ofVec3f&(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::interpolate)
         .def("getMiddle", (ofVec3f(ofVec3f::*)(const ofVec3f&)) &ofVec3f::getMiddle)
         .def("middle", (ofVec3f&(ofVec3f::*)(const ofVec3f&)) &ofVec3f::middle)
         .def("average", (ofVec3f&(ofVec3f::*)(const ofVec3f&,int)) &ofVec3f::average)
         .def("getNormalized", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::getNormalized)
         .def("normalize", (ofVec3f&(ofVec3f::*)(void)) &ofVec3f::normalize)
         .def("getLimited", (ofVec3f(ofVec3f::*)(float)) &ofVec3f::getLimited)
         .def("limit", (ofVec3f&(ofVec3f::*)(float)) &ofVec3f::limit)
         .def("getCrossed", (ofVec3f(ofVec3f::*)(const ofVec3f&)) &ofVec3f::getCrossed)
         .def("cross", (ofVec3f&(ofVec3f::*)(const ofVec3f&)) &ofVec3f::cross)
         .def("getPerpendicular", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::getPerpendicular)
         .def("perpendicular", (ofVec3f&(ofVec3f::*)(void)) &ofVec3f::perpendicular)
         .def("length", (float(ofVec3f::*)(void)) &ofVec3f::length)
         .def("squareLength", (float(ofVec3f::*)(void)) &ofVec3f::squareLength)
         .def("angle", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::angle)
         .def("angleRad", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::angleRad)
         .def("dot", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::dot)
         .def("rescaled", (ofVec3f(ofVec3f::*)(const float)) &ofVec3f::rescaled)
         .def("rescale", (ofVec3f&(ofVec3f::*)(const float)) &ofVec3f::rescale)
         //.def("rotated", (ofVec3f(ofVec3f::*)(float)) &ofVec3f::rotated)
         .def("normalized", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::normalized)
         .def("limited", (ofVec3f(ofVec3f::*)(float)) &ofVec3f::limited)
         .def("perpendiculared", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::perpendiculared)
         .def("lengthSquared", (float(ofVec3f::*)(void)) &ofVec3f::lengthSquared)
         .def("interpolated", (ofVec3f(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::interpolated)
         .def("middled", (ofVec3f(ofVec3f::*)(const ofVec3f&)) &ofVec3f::middled)
         .def("mapped", (ofVec3f(ofVec3f::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofVec3f::mapped)
         .def("distanceSquared", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::distanceSquared)
         .def_readwrite("x", &ofVec3f::x)
		 .def_readwrite("y", &ofVec3f::y)
         .def_readwrite("z", &ofVec3f::z),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVec4f
         
         class_<ofVec4f>("ofVec4f")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
		 .def(constructor<const ofVec2f&>())
		 .def(constructor<const ofVec3f&>())
		 .def("set", (void(ofVec4f::*)(float,float,float,float)) &ofVec4f::set)
		 .def("set", (void(ofVec4f::*)(const ofVec4f&)) &ofVec4f::set)
         .def(self == other<const ofVec4f&>())
         .def("match", (bool(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::match)
         .def(self + other<const ofVec4f&>())
         .def(self - other<const ofVec4f&>())
         .def(self * other<const ofVec4f&>())
         .def(self / other<const ofVec4f&>())
         .def(self + other<const float>())
         .def(self - other<const float>())
         .def(self * other<const float>())
         .def(self / other<const float>())
         .def("getScaled", (ofVec4f(ofVec4f::*)(const float)) &ofVec4f::getScaled)
         .def("scale", (ofVec4f&(ofVec4f::*)(const float)) &ofVec4f::scale)
         //.def("getRotated", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::getRotated)
         //.def("getRotatedRad", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::getRotatedRad)
         //.def("rotate", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::rotate)
         //.def("rotateRad", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::rotateRad)
         //.def("getRotated", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::getRotated)
         //.def("getRotatedRad", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::getRotatedRad)
         //.def("rotate", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::rotate)
         //.def("rotateRad", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::rotateRad)
		 //.def("rotated", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::rotated)
         .def("distance", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::distance)
         .def("squareDistance", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::squareDistance)
         .def("getInterpolated", (ofVec4f(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::getInterpolated)
         .def("interpolate", (ofVec4f&(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::interpolate)
         .def("getMiddle", (ofVec4f(ofVec4f::*)(const ofVec4f&)) &ofVec4f::getMiddle)
         .def("middle", (ofVec4f&(ofVec4f::*)(const ofVec4f&)) &ofVec4f::middle)
         .def("average", (ofVec4f&(ofVec4f::*)(const ofVec4f&,int)) &ofVec4f::average)
         .def("getNormalized", (ofVec4f(ofVec4f::*)(void)) &ofVec4f::getNormalized)
         .def("normalize", (ofVec4f&(ofVec4f::*)(void)) &ofVec4f::normalize)
         .def("getLimited", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::getLimited)
         .def("limit", (ofVec4f&(ofVec4f::*)(float)) &ofVec4f::limit)
         .def("length", (float(ofVec4f::*)(void)) &ofVec4f::length)
         .def("squareLength", (float(ofVec4f::*)(void)) &ofVec4f::squareLength)
         .def("dot", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::dot)
         .def("rescaled", (ofVec4f(ofVec4f::*)(const float)) &ofVec4f::rescaled)
         .def("rescale", (ofVec4f&(ofVec4f::*)(const float)) &ofVec4f::rescale)
         .def("normalized", (ofVec4f(ofVec4f::*)(void)) &ofVec4f::normalized)
         .def("limited", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::limited)
         .def("lengthSquared", (float(ofVec4f::*)(void)) &ofVec4f::lengthSquared)
         .def("interpolated", (ofVec4f(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::interpolated)
         .def("middled", (ofVec4f(ofVec4f::*)(const ofVec4f&)) &ofVec4f::middled)
         .def("distanceSquared", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::distanceSquared)
         .def_readwrite("x", &ofVec4f::x)
		 .def_readwrite("y", &ofVec4f::y)
         .def_readwrite("z", &ofVec4f::z)
         .def_readwrite("w", &ofVec4f::w),
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section gl [ofMaterials, ofFbo, ofGLRenderer, ofVbo, ofTextureData, ofShader, ofVboMesh, ofTexture, ofGLUtils, ofLight]
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMaterial
         
         class_<ofMaterial>("ofMaterial")
		 .def(constructor<>())
         .def("setColors", (void(ofMaterial::*)(ofFloatColor,ofFloatColor,ofFloatColor,ofFloatColor)) &ofMaterial::setColors)
         .def("setDiffuseColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setDiffuseColor)
         .def("setAmbientColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setAmbientColor)
         .def("setSpecularColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setSpecularColor)
         .def("setEmissiveColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setEmissiveColor)
         .def("setShininess", (void(ofMaterial::*)(float)) &ofMaterial::setShininess)
         .def("getDiffuseColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getDiffuseColor)
         .def("getAmbientColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getAmbientColor)
         .def("getSpecularColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getSpecularColor)
         .def("getEmissiveColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getEmissiveColor)
         .def("getShininess", (float(ofMaterial::*)(void)) &ofMaterial::getShininess)
         .def("beginMaterial", (void(ofMaterial::*)(void)) &ofMaterial::begin)
		 .def("endMaterial", (void(ofMaterial::*)(void)) &ofMaterial::end),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFbo
         
         class_<ofFbo>("ofFbo")
		 .def(constructor<>())
         .def(constructor<const ofFbo&>())
		 .def("allocate", (void(ofFbo::*)(int,int,int,int)) &ofFbo::allocate) // int width, int height, int internalformat, int numSamples
         .def("draw", (void(ofFbo::*)(float,float)) &ofFbo::draw)
         .def("draw", (void(ofFbo::*)(float,float,float,float)) &ofFbo::draw)
         .def("setAnchorPercent", (void(ofFbo::*)(float,float)) &ofFbo::setAnchorPercent)
         .def("setAnchorPoint", (void(ofFbo::*)(float,float)) &ofFbo::setAnchorPoint)
         .def("resetAnchor", (void(ofFbo::*)(void)) &ofFbo::resetAnchor)
         .def("setDefaultTextureIndex", (void(ofFbo::*)(int)) &ofFbo::setDefaultTextureIndex)
         .def("getDefaultTextureIndex", (int(ofFbo::*)(void)) &ofFbo::getDefaultTextureIndex)
         .def("getTextureReference", (ofTexture&(ofFbo::*)(void)) &ofFbo::getTextureReference)
         .def("getTextureReference", (ofTexture&(ofFbo::*)(int)) &ofFbo::getTextureReference)
         .def("getDepthTexture", (ofTexture&(ofFbo::*)(void)) &ofFbo::getDepthTexture)
         .def("setUseTexture", (void(ofFbo::*)(bool)) &ofFbo::setUseTexture)
         .def("beginFbo", (void(ofFbo::*)(void)) &ofFbo::begin)
		 .def("endFbo", (void(ofFbo::*)(void)) &ofFbo::end)
         .def("readToPixels", (void(ofFbo::*)(ofPixels&,int)) &ofFbo::readToPixels)
         .def("readToPixels", (void(ofFbo::*)(ofShortPixels&,int)) &ofFbo::readToPixels)
         .def("readToPixels", (void(ofFbo::*)(ofFloatPixels&,int)) &ofFbo::readToPixels)
         .def("getWidth", (float(ofFbo::*)(void)) &ofFbo::getWidth)
		 .def("getHeight", (float(ofFbo::*)(void)) &ofFbo::getHeight)
         .def("bind", (void(ofFbo::*)(void)) &ofFbo::bind)
		 .def("unbind", (void(ofFbo::*)(void)) &ofFbo::unbind)
         .def("getNumTextures", (int(ofFbo::*)(void)) &ofFbo::getNumTextures)
         .def("getFbo", (GLuint(ofFbo::*)(void)) &ofFbo::getFbo)
         .def("getDepthBuffer", (GLuint(ofFbo::*)(void)) &ofFbo::getDepthBuffer)
         .def("getStencilBuffer", (GLuint(ofFbo::*)(void)) &ofFbo::getStencilBuffer)
         .def("checkGLSupport", (bool(*)(void)) &ofFbo::checkGLSupport)
         .def("maxColorAttachments", (int(*)(void)) &ofFbo::maxColorAttachments)
         .def("maxDrawBuffers", (int(*)(void)) &ofFbo::maxDrawBuffers)
         .def("maxSamples", (int(*)(void)) &ofFbo::maxSamples),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofGLRenderer
         
         class_<ofGLRenderer>("ofGLRenderer")
		 .def(constructor<bool>())
         .def("getType", (string(ofGLRenderer::*)(void)) &ofGLRenderer::getType)
         .def("setCurrentFBO", (void(ofGLRenderer::*)(ofFbo*)) &ofGLRenderer::setCurrentFBO)
         .def("update", (void(ofGLRenderer::*)(void)) &ofGLRenderer::update)
         .def("draw", (void(ofGLRenderer::*)(ofMesh&,bool,bool,bool)) &ofGLRenderer::draw)
         .def("draw", (void(ofGLRenderer::*)(ofMesh&,ofPolyRenderMode,bool,bool,bool)) &ofGLRenderer::draw)
         .def("draw", (void(ofGLRenderer::*)(ofPolyline&)) &ofGLRenderer::draw)
         .def("draw", (void(ofGLRenderer::*)(ofPath&)) &ofGLRenderer::draw)
         .def("draw", (void(ofGLRenderer::*)(ofImage&,float,float,float,float,float,float,float,float,float)) &ofGLRenderer::draw)
         .def("draw", (void(ofGLRenderer::*)(ofFloatImage&,float,float,float,float,float,float,float,float,float)) &ofGLRenderer::draw)
         .def("draw", (void(ofGLRenderer::*)(ofShortImage&,float,float,float,float,float,float,float,float,float)) &ofGLRenderer::draw)
         .def("rendersPathPrimitives", (bool(ofGLRenderer::*)(void)) &ofGLRenderer::rendersPathPrimitives)
         .def("pushView", (void(ofGLRenderer::*)(void)) &ofGLRenderer::pushView)
         .def("popView", (void(ofGLRenderer::*)(void)) &ofGLRenderer::popView)
         .def("viewport", (void(ofGLRenderer::*)(ofRectangle)) &ofGLRenderer::viewport)
         .def("viewport", (void(ofGLRenderer::*)(float,float,float,float,bool)) &ofGLRenderer::viewport)
         .def("setupScreenPerspective", (void(ofGLRenderer::*)(float,float,ofOrientation,bool,float,float,float)) &ofGLRenderer::setupScreenPerspective)
         .def("setupScreenOrtho", (void(ofGLRenderer::*)(float,float,ofOrientation,bool,float,float)) &ofGLRenderer::setupScreenOrtho)
         .def("getCurrentViewport", (ofRectangle(ofGLRenderer::*)(void)) &ofGLRenderer::getCurrentViewport)
         .def("getViewportWidth", (int(ofGLRenderer::*)(void)) &ofGLRenderer::getViewportWidth)
         .def("getViewportHeight", (int(ofGLRenderer::*)(void)) &ofGLRenderer::getViewportHeight)
         .def("pushMatrix", (void(ofGLRenderer::*)(void)) &ofGLRenderer::pushMatrix)
         .def("popMatrix", (void(ofGLRenderer::*)(void)) &ofGLRenderer::popMatrix)
         .def("translate", (void(ofGLRenderer::*)(const ofPoint&)) &ofGLRenderer::translate)
         .def("translate", (void(ofGLRenderer::*)(float,float,float)) &ofGLRenderer::translate)
         .def("scale", (void(ofGLRenderer::*)(float,float,float)) &ofGLRenderer::scale)
         .def("rotate", (void(ofGLRenderer::*)(float,float,float,float)) &ofGLRenderer::rotate)
         .def("rotate", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotate)
         .def("rotateX", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotateX)
         .def("rotateY", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotateY)
         .def("rotateZ", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotateZ)
         .def("setupGraphicDefaults", (void(ofGLRenderer::*)(void)) &ofGLRenderer::setupGraphicDefaults)
         .def("setupScreen", (void(ofGLRenderer::*)(void)) &ofGLRenderer::setupScreen)
         .def("setFillMode", (void(ofGLRenderer::*)(ofFillFlag)) &ofGLRenderer::setFillMode)
         .def("getFillMode", (ofFillFlag(ofGLRenderer::*)(void)) &ofGLRenderer::getFillMode)
         .def("setCircleResolution", (void(ofGLRenderer::*)(int)) &ofGLRenderer::setCircleResolution)
         .def("setRectMode", (void(ofGLRenderer::*)(ofRectMode)) &ofGLRenderer::setRectMode)
         .def("getRectMode", (ofRectMode(ofGLRenderer::*)(void)) &ofGLRenderer::getRectMode)
         .def("setLineWidth", (void(ofGLRenderer::*)(float)) &ofGLRenderer::setLineWidth)
         .def("setLineSmoothing", (void(ofGLRenderer::*)(bool)) &ofGLRenderer::setLineSmoothing)
         .def("setBlendMode", (void(ofGLRenderer::*)(ofBlendMode)) &ofGLRenderer::setBlendMode)
         .def("enablePointSprites", (void(ofGLRenderer::*)(void)) &ofGLRenderer::enablePointSprites)
         .def("disablePointSprites", (void(ofGLRenderer::*)(void)) &ofGLRenderer::disablePointSprites)
         .def("setColor", (void(ofGLRenderer::*)(int,int,int)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(int,int,int,int)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(const ofColor&)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(const ofColor&,int)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(int)) &ofGLRenderer::setColor)
         .def("setHexColor", (void(ofGLRenderer::*)(int)) &ofGLRenderer::setHexColor)
         .def("getBgColor", (ofFloatColor(ofGLRenderer::*)(void)) &ofGLRenderer::getBgColor)
         .def("bClearBg", (bool(ofGLRenderer::*)(void)) &ofGLRenderer::bClearBg)
         .def("background", (void(ofGLRenderer::*)(const ofColor&)) &ofGLRenderer::background)
         .def("background", (void(ofGLRenderer::*)(float)) &ofGLRenderer::background)
         .def("background", (void(ofGLRenderer::*)(int,float)) &ofGLRenderer::background)
         .def("background", (void(ofGLRenderer::*)(int,int,int,int)) &ofGLRenderer::background)
         .def("setBackgroundAuto", (void(ofGLRenderer::*)(bool)) &ofGLRenderer::setBackgroundAuto)
         .def("clear", (void(ofGLRenderer::*)(float,float,float,float)) &ofGLRenderer::clear)
         .def("clear", (void(ofGLRenderer::*)(float,float)) &ofGLRenderer::clear)
         .def("clearAlpha", (void(ofGLRenderer::*)(void)) &ofGLRenderer::clearAlpha)
         .def("drawLine", (void(ofGLRenderer::*)(float,float,float,float,float,float)) &ofGLRenderer::drawLine)
         .def("drawRectangle", (void(ofGLRenderer::*)(float,float,float,float,float)) &ofGLRenderer::drawRectangle)
         .def("drawTriangle", (void(ofGLRenderer::*)(float,float,float,float,float,float,float,float,float)) &ofGLRenderer::drawTriangle)
         .def("drawCircle", (void(ofGLRenderer::*)(float,float,float,float)) &ofGLRenderer::drawCircle)
         .def("drawSphere", (void(ofGLRenderer::*)(float,float,float,float)) &ofGLRenderer::drawSphere)
         .def("drawEllipse", (void(ofGLRenderer::*)(float,float,float,float,float)) &ofGLRenderer::drawEllipse)
         .def("drawString", (void(ofGLRenderer::*)(string,float,float,float,ofDrawBitmapMode)) &ofGLRenderer::drawString),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVbo
         
         class_<ofVbo>("ofVbo")
		 .def(constructor<>())
         .def(constructor<const ofVbo&>())
         .def("getVertId", (GLuint(ofVbo::*)(void)) &ofVbo::getVertId)
         .def("getColorId", (GLuint(ofVbo::*)(void)) &ofVbo::getColorId)
         .def("getNormalId", (GLuint(ofVbo::*)(void)) &ofVbo::getNormalId)
         .def("getTexCoordId", (GLuint(ofVbo::*)(void)) &ofVbo::getTexCoordId)
         .def("getIndexId", (GLuint(ofVbo::*)(void)) &ofVbo::getIndexId)
         .def("getIsAllocated", (bool(ofVbo::*)(void)) &ofVbo::getIsAllocated)
         .def("getUsingVerts", (bool(ofVbo::*)(void)) &ofVbo::getUsingVerts)
         .def("getUsingColors", (bool(ofVbo::*)(void)) &ofVbo::getUsingColors)
         .def("getUsingNormals", (bool(ofVbo::*)(void)) &ofVbo::getUsingNormals)
         .def("getUsingTexCoords", (bool(ofVbo::*)(void)) &ofVbo::getUsingTexCoords)
         .def("getUsingIndices", (bool(ofVbo::*)(void)) &ofVbo::getUsingIndices)
         .def("draw", (void(ofVbo::*)(int,int,int)) &ofVbo::draw)
         .def("drawElements", (void(ofVbo::*)(int,int)) &ofVbo::drawElements)
         .def("bind", (void(ofVbo::*)(void)) &ofVbo::bind)
         .def("unbind", (void(ofVbo::*)(void)) &ofVbo::unbind)
         .def("clear", (void(ofVbo::*)(void)) &ofVbo::clear)
         .def("setMesh", (void(ofVbo::*)(const ofMesh&,int)) &ofVbo::setMesh)
         .def("setVertex3Data", (void(ofVbo::*)(const ofVec3f*,int,int)) &ofVbo::setVertexData)
         .def("setVertex2Data", (void(ofVbo::*)(const ofVec2f*,int,int)) &ofVbo::setVertexData)
         .def("setColorData", (void(ofVbo::*)(const ofFloatColor*,int,int)) &ofVbo::setColorData)
         .def("setNormalData", (void(ofVbo::*)(const ofVec3f*,int,int)) &ofVbo::setNormalData)
         .def("setTexCoordData", (void(ofVbo::*)(const ofVec2f*,int,int)) &ofVbo::setTexCoordData)
         .def("setIndexData", (void(ofVbo::*)(const ofIndexType*,int,int)) &ofVbo::setIndexData)
         .def("setColorData", (void(ofVbo::*)(const float*,int,int,int)) &ofVbo::setColorData)
         .def("setNormalData", (void(ofVbo::*)(const float*,int,int,int)) &ofVbo::setNormalData)
         .def("setTexCoordData", (void(ofVbo::*)(const float*,int,int,int)) &ofVbo::setTexCoordData)
         .def("updateMesh", (void(ofVbo::*)(const ofMesh&)) &ofVbo::updateMesh)
         .def("updateVertex3Data", (void(ofVbo::*)(const ofVec3f*,int)) &ofVbo::updateVertexData)
         .def("updateVertex2Data", (void(ofVbo::*)(const ofVec2f*,int)) &ofVbo::updateVertexData)
         .def("updateColorData", (void(ofVbo::*)(const ofFloatColor*,int)) &ofVbo::updateColorData)
         .def("updateNormalData", (void(ofVbo::*)(const ofVec3f*,int)) &ofVbo::updateNormalData)
         .def("updateTexCoordDataF", (void(ofVbo::*)(const ofVec2f*,int)) &ofVbo::updateTexCoordData)
         .def("updateIndexData", (void(ofVbo::*)(const ofIndexType*,int)) &ofVbo::updateIndexData)
         .def("updateVertexDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateVertexData)
         .def("updateColorDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateColorData)
         .def("updateNormalDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateNormalData)
         .def("updateTexCoordDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateTexCoordData),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTextureData
         
         class_<ofTextureData>("ofTextureData")
		 .def(constructor<>())
         .def_readonly("textureID", &ofTextureData::textureID)
         .def_readonly("textureTarget", &ofTextureData::textureTarget)
         .def_readonly("glTypeInternal", &ofTextureData::glTypeInternal)
         .def_readonly("glType", &ofTextureData::glType)
         .def_readonly("pixelType", &ofTextureData::pixelType)
         .def_readonly("tex_t", &ofTextureData::tex_t)
         .def_readonly("tex_u", &ofTextureData::tex_u)
         .def_readonly("tex_w", &ofTextureData::tex_w)
         .def_readonly("tex_h", &ofTextureData::tex_h)
         .def_readonly("width", &ofTextureData::width)
         .def_readonly("height", &ofTextureData::height)
         .def_readonly("bFlipTexture", &ofTextureData::bFlipTexture)
         .def_readonly("compressionType", &ofTextureData::compressionType)
         .def_readonly("bAllocated", &ofTextureData::bAllocated),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofShader
         
         class_<ofShader>("ofShader")
		 .def(constructor<>())
         .def("load", (bool(ofShader::*)(string)) &ofShader::load)
         .def("load", (bool(ofShader::*)(string,string,string)) &ofShader::load)
         .def("beginShader", (void(ofShader::*)(void)) &ofShader::begin)
         .def("endShader", (void(ofShader::*)(void)) &ofShader::end)
         .def("setUniformTexture", (void(ofShader::*)(const char*,ofBaseHasTexture&,int)) &ofShader::setUniformTexture)
         .def("setUniformTexture", (void(ofShader::*)(const char*,ofTexture&,int)) &ofShader::setUniformTexture)
         .def("setUniform1i", (void(ofShader::*)(const char*,int)) &ofShader::setUniform1i)
         .def("setUniform2i", (void(ofShader::*)(const char*,int,int)) &ofShader::setUniform2i)
         .def("setUniform3i", (void(ofShader::*)(const char*,int,int,int)) &ofShader::setUniform3i)
         .def("setUniform4i", (void(ofShader::*)(const char*,int,int,int,int)) &ofShader::setUniform4i)
         .def("setUniform1f", (void(ofShader::*)(const char*,float)) &ofShader::setUniform1f)
         .def("setUniform2f", (void(ofShader::*)(const char*,float,float)) &ofShader::setUniform2f)
         .def("setUniform3f", (void(ofShader::*)(const char*,float,float,float)) &ofShader::setUniform3f)
         .def("setUniform4f", (void(ofShader::*)(const char*,float,float,float,float)) &ofShader::setUniform4f)
         .def("unload", (void(ofShader::*)(void)) &ofShader::unload),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVboMesh
         
         class_<ofVboMesh>("ofVboMesh")
		 .def(constructor<>())
         .def(constructor<const ofMesh&>())
         .def("setUsage", (void(ofVboMesh::*)(int)) &ofVboMesh::setUsage)
         
         .def("setMode", (void(ofVboMesh::*)(ofPrimitiveMode)) &ofVboMesh::setMode)
         .def("getMode", (ofPrimitiveMode(ofVboMesh::*)(void)) &ofVboMesh::getMode)
         .def("clear", (void(ofVboMesh::*)(void)) &ofVboMesh::clear)
         .def("setupIndicesAuto", (void(ofVboMesh::*)(void)) &ofVboMesh::setupIndicesAuto)
         .def("getVertex", (ofVec3f(ofVboMesh::*)(int)) &ofVboMesh::getVertex)
         //.def("removeVertex", (void(ofVboMesh::*)(int)) &ofVboMesh::removeVertex)
         .def("clearVertices", (void(ofVboMesh::*)(void)) &ofVboMesh::clearVertices)
         .def("getNormal", (ofVec3f(ofVboMesh::*)(int)) &ofVboMesh::getNormal)
         //.def("removeNormal", (void(ofVboMesh::*)(int)) &ofVboMesh::removeNormal)
         .def("clearNormals", (void(ofVboMesh::*)(void)) &ofVboMesh::clearNormals)
         .def("getColor", (ofFloatColor(ofVboMesh::*)(int)) &ofVboMesh::getColor)
         //.def("removeColor", (void(ofVboMesh::*)(int)) &ofVboMesh::removeColor)
         .def("clearColors", (void(ofVboMesh::*)(void)) &ofVboMesh::clearColors)
         .def("getTexCoord", (ofVec2f(ofVboMesh::*)(int)) &ofVboMesh::getTexCoord)
         //.def("removeTexCoord", (void(ofVboMesh::*)(int)) &ofVboMesh::removeTexCoord)
         .def("clearTexCoords", (void(ofVboMesh::*)(void)) &ofVboMesh::clearTexCoords)
         .def("getIndex", (ofIndexType(ofVboMesh::*)(int)) &ofVboMesh::getTexCoord)
         .def("addIndex", (void(ofVboMesh::*)(ofIndexType)) &ofVboMesh::addIndex)
         //.def("removeIndex", (void(ofVboMesh::*)(int)) &ofVboMesh::removeIndex)
         .def("setIndex", (void(ofVboMesh::*)(int,ofIndexType)) &ofVboMesh::setIndex)
         .def("clearIndices", (void(ofVboMesh::*)(void)) &ofVboMesh::clearIndices)
         .def("addTriangle", (void(ofVboMesh::*)(ofIndexType,ofIndexType,ofIndexType)) &ofVboMesh::addTriangle)
         .def("getNumVertices", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumVertices)
         .def("getNumColors", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumColors)
         .def("getNumNormals", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumNormals)
         .def("getNumTexCoords", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumTexCoords)
         .def("getNumIndices", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumIndices)
         .def("getVerticesPointer", (ofVec3f*(ofVboMesh::*)(void)) &ofVboMesh::getVerticesPointer)
         .def("getColorsPointer", (ofFloatColor*(ofVboMesh::*)(void)) &ofVboMesh::getColorsPointer)
         .def("getNormalsPointer", (ofVec3f*(ofVboMesh::*)(void)) &ofVboMesh::getNormalsPointer)
         .def("getTexCoordsPointer", (ofVec2f*(ofVboMesh::*)(void)) &ofVboMesh::getTexCoordsPointer)
         .def("getIndexPointer", (ofIndexType*(ofVboMesh::*)(void)) &ofVboMesh::getIndexPointer)
         .def("setName", (void(ofVboMesh::*)(string)) &ofVboMesh::setName)
         .def("haveVertsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveVertsChanged)
         .def("haveColorsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveColorsChanged)
         .def("haveNormalsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveNormalsChanged)
         .def("haveTexCoordsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveTexCoordsChanged)
         .def("haveIndicesChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveIndicesChanged)
         .def("hasVertices", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasVertices)
         .def("hasColors", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasColors)
         .def("hasNormals", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasNormals)
         .def("hasTexCoords", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasTexCoords)
         .def("hasIndices", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasIndices)
         .def("drawVertices", (void(ofVboMesh::*)(void)) &ofVboMesh::drawVertices)
         .def("drawWireframe", (void(ofVboMesh::*)(void)) &ofVboMesh::drawWireframe)
         .def("drawFaces", (void(ofVboMesh::*)(void)) &ofVboMesh::drawFaces)
         .def("draw", (void(ofVboMesh::*)(void)) &ofVboMesh::draw)
         .def("addVertex", (void(ofVboMesh::*)(const ofVec3f&)) &ofVboMesh::addVertex)
         .def("setVertex", (void(ofVboMesh::*)(int,const ofVec3f&)) &ofVboMesh::setVertex)
         .def("addNormal", (void(ofVboMesh::*)(const ofVec3f&)) &ofVboMesh::addNormal)
         .def("setNormal", (void(ofVboMesh::*)(int,const ofVec3f&)) &ofVboMesh::setNormal)
         .def("addColor", (void(ofVboMesh::*)(const ofFloatColor&)) &ofVboMesh::addColor)
         .def("setColor", (void(ofVboMesh::*)(int,const ofFloatColor&)) &ofVboMesh::setColor)
         .def("addTexCoord", (void(ofVboMesh::*)(const ofVec2f&)) &ofVboMesh::addTexCoord)
         .def("setTexCoord", (void(ofVboMesh::*)(int,const ofVec2f&)) &ofVboMesh::setTexCoord)
         .def("addIndices", (void(ofVboMesh::*)(const ofIndexType*,int)) &ofVboMesh::addIndices),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTexture
         
         class_<ofTexture>("ofTexture")
		 .def(constructor<>())
		 .def("allocate", (void(ofTexture::*)(int,int,int)) &ofTexture::allocate)
         .def("allocate", (void(ofTexture::*)(int,int,int,bool)) &ofTexture::allocate)
		 .def("clear", (void(ofTexture::*)(void)) &ofTexture::clear)
		 .def("loadData", (void(ofTexture::*)(const float*,int,int,int)) &ofTexture::loadData)
		 .def("loadData", &loadDataOLD)
		 .def("loadData", (void(ofTexture::*)(const unsigned short*,int,int,int)) &ofTexture::loadData)
		 .def("loadData", (void(ofTexture::*)(const ofPixels&)) &ofTexture::loadData)
         .def("loadScreenData", (void(ofTexture::*)(int,int,int,int)) &ofTexture::loadScreenData)
		 .def("setAnchorPercent", (void(ofTexture::*)(float,float)) &ofTexture::setAnchorPercent)
		 .def("setAnchorPoint", (void(ofTexture::*)(float,float)) &ofTexture::setAnchorPoint)
		 .def("resetAnchor", (void(ofTexture::*)(void)) &ofTexture::resetAnchor)
         .def("readToPixels", (void(ofTexture::*)(ofPixels&)) &ofTexture::readToPixels)
		 .def("draw", (void(ofTexture::*)(const ofRectangle&)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(const ofPoint&)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(const ofPoint&, float, float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float,float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float,float,float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float,float,float,float)) &ofTexture::draw)
         .def("bAllocated", (bool(ofTexture::*)(void)) &ofTexture::bAllocated)
         .def("getCoordFromPoint", (ofPoint(ofTexture::*)(float,float)) &ofTexture::getCoordFromPoint)
         .def("getCoordFromPercent", (ofPoint(ofTexture::*)(float,float)) &ofTexture::getCoordFromPercent)
         .def("setTextureWrap", (void(ofTexture::*)(GLint,GLint)) &ofTexture::setTextureWrap)
         .def("setTextureMinMagFilter", (void(ofTexture::*)(GLint,GLint)) &ofTexture::setTextureMinMagFilter)
         .def("setCompression", (void(ofTexture::*)(ofTexCompression)) &ofTexture::setCompression)
         .def("isAllocated", (bool(ofTexture::*)(void)) &ofTexture::isAllocated)
         .def("bind", &ofTexture::bind)
         .def("unbind", &ofTexture::unbind)
		 .def("getWidth", &ofTexture::getWidth)
		 .def("getHeight", &ofTexture::getHeight),
         
         def("getGlInternalFormat", (int(*)(const ofPixels&)) &ofGetGlInternalFormat),
         def("getGlFormatAndType", (void(*)(int,int&,int&)) &ofGetGlFormatAndType),
         def("getImageTypeFromGLType", (ofImage(*)(int)) &ofGetImageTypeFromGLType),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofGLUtils
         
         def("getGLPolyMode", (GLuint(*)(ofPolyRenderMode)) &ofGetGLPolyMode),
         def("getOFPolyMode", (ofPolyRenderMode(*)(GLuint)) &ofGetOFPolyMode),
         def("getGLPrimitiveMode", (GLuint(*)(ofPolyRenderMode)) &ofGetGLPrimitiveMode),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofLight
         
         class_<ofLight>("ofLight")
		 .def(constructor<>())
         .def(constructor<const ofLight&>())
         .def("destroy", (void(ofLight::*)(void)) &ofLight::destroy)
         .def("enable", (void(ofLight::*)(void)) &ofLight::enable)
         .def("disable", (void(ofLight::*)(void)) &ofLight::disable)
         .def("getIsEnabled", (bool(ofLight::*)(void)) &ofLight::getIsEnabled)
         .def("setDirectional", (void(ofLight::*)(void)) &ofLight::setDirectional)
         .def("getIsDirectional", (bool(ofLight::*)(void)) &ofLight::getIsDirectional)
         .def("setSpotlight", (void(ofLight::*)(float,float)) &ofLight::setSpotlight)
         .def("getIsSpotlight", (bool(ofLight::*)(void)) &ofLight::getIsSpotlight)
         .def("setSpotlightCutOff", (void(ofLight::*)(float)) &ofLight::setSpotlightCutOff)
         .def("setSpotConcentration", (void(ofLight::*)(float)) &ofLight::setSpotConcentration)
         .def("setPointLight", (void(ofLight::*)(void)) &ofLight::setPointLight)
         .def("getIsPointLight", (bool(ofLight::*)(void)) &ofLight::getIsPointLight)
         .def("setAttenuation", (void(ofLight::*)(float,float,float)) &ofLight::setAttenuation)
         .def("getType", (int(ofLight::*)(void)) &ofLight::getType)
         .def("setAmbientColor", (void(ofLight::*)(const ofFloatColor&)) &ofLight::setAmbientColor)
         .def("setDiffuseColor", (void(ofLight::*)(const ofFloatColor&)) &ofLight::setDiffuseColor)
         .def("setSpecularColor", (void(ofLight::*)(const ofFloatColor&)) &ofLight::setSpecularColor)
         .def("getAmbientColor", (ofFloatColor(ofLight::*)(void)) &ofLight::getAmbientColor)
         .def("getDiffuseColor", (ofFloatColor(ofLight::*)(void)) &ofLight::getDiffuseColor)
         .def("getSpecularColor", (ofFloatColor(ofLight::*)(void)) &ofLight::getSpecularColor)
         .def("getLightID", (int(ofLight::*)(void)) &ofLight::getLightID)
         .def("customDraw", (void(ofLight::*)(void)) &ofLight::customDraw)
         
         // from ofNode, transform functionality
         .def("getPosition", (ofVec3f(ofLight::*)(void)) &ofLight::getPosition)
         .def("getX", (float(ofLight::*)(void)) &ofLight::getX)
         .def("getY", (float(ofLight::*)(void)) &ofLight::getY)
         .def("getZ", (float(ofLight::*)(void)) &ofLight::getZ)
         .def("getXAxis", (ofVec3f(ofLight::*)(void)) &ofLight::getXAxis)
         .def("getYAxis", (ofVec3f(ofLight::*)(void)) &ofLight::getYAxis)
         .def("getZAxis", (ofVec3f(ofLight::*)(void)) &ofLight::getZAxis)
         .def("getSideDir", (ofVec3f(ofLight::*)(void)) &ofLight::getSideDir)
         .def("getLookAtDir", (ofVec3f(ofLight::*)(void)) &ofLight::getLookAtDir)
         .def("getUpDir", (ofVec3f(ofLight::*)(void)) &ofLight::getUpDir)
         .def("getPitch", (float(ofLight::*)(void)) &ofLight::getPitch)
         .def("getHeading", (float(ofLight::*)(void)) &ofLight::getHeading)
         .def("getRoll", (float(ofLight::*)(void)) &ofLight::getRoll)
         .def("getOrientationQuat", (ofQuaternion(ofLight::*)(void)) &ofLight::getOrientationQuat)
         .def("getOrientationEuler", (ofVec3f(ofLight::*)(void)) &ofLight::getOrientationEuler)
         .def("getScale", (ofVec3f(ofLight::*)(void)) &ofLight::getScale)
         .def("getLocalTransformMatrix", (ofMatrix4x4(ofLight::*)(void)) &ofLight::getLocalTransformMatrix)
         .def("getGlobalTransformMatrix", (ofMatrix4x4(ofLight::*)(void)) &ofLight::getGlobalTransformMatrix)
         .def("getGlobalPosition", (ofVec3f(ofLight::*)(void)) &ofLight::getGlobalPosition)
         .def("getGlobalOrientation", (ofQuaternion(ofLight::*)(void)) &ofLight::getGlobalOrientation)
         .def("setTransformMatrix", (void(ofLight::*)(const ofMatrix4x4&)) &ofLight::setTransformMatrix)
         .def("setPosition", (void(ofLight::*)(float,float,float)) &ofLight::setPosition)
         .def("setPosition", (void(ofLight::*)(const ofVec3f&)) &ofLight::setPosition)
         .def("setGlobalPosition", (void(ofLight::*)(float,float,float)) &ofLight::setGlobalPosition)
         .def("setGlobalPosition", (void(ofLight::*)(const ofVec3f&)) &ofLight::setGlobalPosition)
         .def("setOrientation", (void(ofLight::*)(const ofQuaternion&)) &ofLight::setOrientation)
         .def("setOrientation", (void(ofLight::*)(const ofVec3f&)) &ofLight::setOrientation)
         .def("setGlobalOrientation", (void(ofLight::*)(const ofQuaternion&)) &ofLight::setGlobalOrientation)
         .def("setScale", (void(ofLight::*)(float,float,float)) &ofLight::setScale)
         .def("setScale", (void(ofLight::*)(const ofVec3f&)) &ofLight::setScale)         
         .def("move", (void(ofLight::*)(float,float,float)) &ofLight::move)
         .def("move", (void(ofLight::*)(const ofVec3f&)) &ofLight::move)
         .def("truck", (void(ofLight::*)(float)) &ofLight::truck)
         .def("boom", (void(ofLight::*)(float)) &ofLight::boom)
         .def("dolly", (void(ofLight::*)(float)) &ofLight::dolly)
         .def("tilt", (void(ofLight::*)(float)) &ofLight::tilt)
         .def("pan", (void(ofLight::*)(float)) &ofLight::pan)
         .def("roll", (void(ofLight::*)(float)) &ofLight::roll)
         .def("rotate", (void(ofLight::*)(const ofQuaternion&)) &ofLight::rotate)
         .def("rotate", (void(ofLight::*)(float,const ofVec3f&)) &ofLight::rotate)
         .def("rotate", (void(ofLight::*)(float,float,float,float)) &ofLight::rotate)
         .def("rotateAround", (void(ofLight::*)(const ofQuaternion&,const ofVec3f&)) &ofLight::rotateAround)
         .def("rotateAround", (void(ofLight::*)(float,const ofVec3f&,const ofVec3f&)) &ofLight::rotateAround)
         .def("lookAt", (void(ofLight::*)(const ofVec3f&,ofVec3f)) &ofLight::lookAt)
         .def("orbit", (void(ofLight::*)(float,float,float,const ofVec3f&)) &ofLight::orbit)
         .def("orbit", (void(ofLight::*)(float,float,float,ofNode&)) &ofLight::orbit),
         
         def("ofEnableLighting", (void(*)(void)) &ofEnableLighting),
         def("ofDisableLighting", (void(*)(void)) &ofDisableLighting),
         def("ofEnableSeparateSpecularLight", (void(*)(void)) &ofEnableSeparateSpecularLight),
         def("ofDisableSeparateSpecularLight", (void(*)(void)) &ofDisableSeparateSpecularLight),
         def("ofGetLightingEnabled", (bool(*)(void)) &ofGetLightingEnabled),
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section utils [ofDirectory, ofHttpResponse, ofFileDialogResult, ofLogError, ofLogWarning, ofSystemUtils,
         ///                    ofBuffer, ofFile, ofLogNotice, ofFileUtils, ofFilePath, ofHttpRequest, ofLogVerbose, ofLog,
         ///                    ofPtr, ofUtils, ofThread, ofLogFatalError, ofURLFileLoader]
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofDirectory
         
         class_<ofDirectory>("ofDirectory")
		 .def(constructor<>())
         .def(constructor<string>())
         .def("open", (void(ofDirectory::*)(string)) &ofDirectory::open)
         .def("close", (void(ofDirectory::*)(void)) &ofDirectory::close)
         .def("create", (bool(ofDirectory::*)(bool)) &ofDirectory::create)
         .def("exists", (bool(ofDirectory::*)(void)) &ofDirectory::exists)
         .def("path", (string(ofDirectory::*)(void)) &ofDirectory::path)
         //.def("canRead", (const bool(ofDirectory::*)(void)) &ofDirectory::canRead)
         //.def("canWrite", (const bool(ofDirectory::*)(void)) &ofDirectory::canWrite)
         //.def("canExecute", (const bool(ofDirectory::*)(void)) &ofDirectory::canExecute)
         .def("isDirectory", (bool(ofDirectory::*)(void)) &ofDirectory::isDirectory)
         .def("isHidden", (bool(ofDirectory::*)(void)) &ofDirectory::isHidden)
         .def("setWriteable", (void(ofDirectory::*)(bool)) &ofDirectory::setWriteable)
         .def("setReadOnly", (void(ofDirectory::*)(bool)) &ofDirectory::setReadOnly)
         .def("setExecutable", (void(ofDirectory::*)(bool)) &ofDirectory::setExecutable)
         .def("setShowHidden", (void(ofDirectory::*)(bool)) &ofDirectory::setShowHidden)
         .def("copyTo", (bool(ofDirectory::*)(string,bool,bool)) &ofDirectory::copyTo)
         .def("moveTo", (bool(ofDirectory::*)(string,bool,bool)) &ofDirectory::moveTo)
         .def("renameTo", (bool(ofDirectory::*)(string,bool,bool)) &ofDirectory::renameTo)
         .def("remove", (bool(ofDirectory::*)(bool)) &ofDirectory::remove)
         .def("allowExt", (void(ofDirectory::*)(string)) &ofDirectory::allowExt)
         .def("listDir", (int(ofDirectory::*)(string)) &ofDirectory::listDir)
         .def("listDir", (int(ofDirectory::*)(void)) &ofDirectory::listDir)
         .def("getName", (string(ofDirectory::*)(unsigned int)) &ofDirectory::getName)
         .def("getPath", (string(ofDirectory::*)(unsigned int)) &ofDirectory::getPath)
         .def("getFile", (ofFile(ofDirectory::*)(unsigned int,ofFile)) &ofDirectory::getFile)
         .def("getFiles", (ofFile(ofDirectory::*)(void)) &ofDirectory::getFiles)
         .def("getShowHidden", (bool(ofDirectory::*)(void)) &ofDirectory::getShowHidden)
         .def("reset", (void(ofDirectory::*)(void)) &ofDirectory::reset)
         .def("sort", (void(ofDirectory::*)(void)) &ofDirectory::sort)
         .def("size", (unsigned int(ofDirectory::*)(void)) &ofDirectory::size)
         .def("numFiles", (int(ofDirectory::*)(void)) &ofDirectory::numFiles)
         .def("createDirectory", (bool(*)(string,bool,bool)) &ofDirectory::createDirectory)
         .def("isDirectoryEmpty", (bool(*)(string,bool)) &ofDirectory::isDirectoryEmpty)
         .def("doesDirectoryExist", (bool(*)(string,bool)) &ofDirectory::doesDirectoryExist)
         .def("removeDirectory", (bool(*)(string,bool,bool)) &ofDirectory::removeDirectory)
         //.def("getOriginalDirectory", (string(*)(void)) &ofDirectory::getOriginalDirectory)
         .def("getFile", (ofFile(ofDirectory::*)(unsigned int,ofFile)) &ofDirectory::getFile),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofHttpResponse
         
         class_<ofHttpResponse>("ofHttpResponse")
		 .def(constructor<>())
         .def(constructor<ofHttpRequest,const ofBuffer&,int,string>())
         .def(constructor<ofHttpRequest,int,string>())
         .def_readonly("request", &ofHttpResponse::request)
		 .def_readonly("data", &ofHttpResponse::data)
         .def_readonly("status", &ofHttpResponse::status)
		 .def_readonly("error", &ofHttpResponse::error),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFileDialogResult
         
         class_<ofFileDialogResult>("ofFileDialogResult")
		 .def(constructor<>())
         .def("getName", (string(ofFileDialogResult::*)(void)) &ofFileDialogResult::getName)
         .def("getPath", (string(ofFileDialogResult::*)(void)) &ofFileDialogResult::getPath)
         .def_readonly("filePath", &ofFileDialogResult::filePath)
		 .def_readonly("fileName", &ofFileDialogResult::fileName)
         .def_readonly("bSuccess", &ofFileDialogResult::bSuccess),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofSystemUtils
         
         def("ofSystemAlertDialog", (void(*)(string)) &ofSystemAlertDialog),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofBuffer
         
         class_<ofBuffer>("ofBuffer")
		 .def(constructor<>())
         .def(constructor<const char*,unsigned int>())
         .def(constructor<const string&>())
         .def(constructor<const ofBuffer&>())
         .def("set", (void(ofBuffer::*)(const char*,unsigned int)) &ofBuffer::set)
         .def("set", (void(ofBuffer::*)(const string&)) &ofBuffer::set)
         .def("set", (bool(ofBuffer::*)(istream&)) &ofBuffer::set)
         .def("writeTo", (bool(ofBuffer::*)(ostream&)) &ofBuffer::writeTo)
         .def("clear", (void(ofBuffer::*)(void)) &ofBuffer::clear)
         .def("allocate", (void(ofBuffer::*)(long)) &ofBuffer::allocate)
         .def("setBinaryBuffer", (void(ofBuffer::*)(int,char)) &ofBuffer::setBinaryBuffer)
         .def("getBinaryBuffer", (char(ofBuffer::*)(int)) &ofBuffer::getBinaryBuffer)
         .def("getBinaryBuffer", (char*(ofBuffer::*)(void)) &ofBuffer::getBinaryBuffer)
         .def("getText", (string(ofBuffer::*)(void)) &ofBuffer::getText)
         .def("size", (long(ofBuffer::*)(void)) &ofBuffer::size)
         .def("getNextLine", (string(ofBuffer::*)(void)) &ofBuffer::getNextLine)
         .def("getFirstLine", (string(ofBuffer::*)(void)) &ofBuffer::getFirstLine)
         .def("isLastLine", (bool(ofBuffer::*)(void)) &ofBuffer::isLastLine)
         .def("resetLineReader", (void(ofBuffer::*)(void)) &ofBuffer::resetLineReader),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFile
         
         class_<ofFile>("ofFile")
		 .def(constructor<>())
         .def(constructor<const ofFile&>())
         .def("open", &openFile) // file:open("test/test.txt")
         .def("close", (void(ofFile::*)(void)) &ofFile::close)
         .def("create", (bool(ofFile::*)(void)) &ofFile::create)
         .def("exists", (bool(ofFile::*)(void)) &ofFile::exists)
         .def("path", (string(ofFile::*)(void)) &ofFile::path)
         .def("getExtension", (string(ofFile::*)(void)) &ofFile::getExtension)
         .def("getFileName", (string(ofFile::*)(void)) &ofFile::getFileName)
         .def("getBaseName", (string(ofFile::*)(void)) &ofFile::getBaseName)
         .def("getEnclosingDirectory", (string(ofFile::*)(void)) &ofFile::getEnclosingDirectory)
         .def("getAbsolutePath", (string(ofFile::*)(void)) &ofFile::getAbsolutePath)
         .def("canRead", (bool(ofFile::*)(void)) &ofFile::canRead)
         .def("canWrite", (bool(ofFile::*)(void)) &ofFile::canWrite)
         .def("canExecute", (bool(ofFile::*)(void)) &ofFile::canExecute)
         .def("isFile", (bool(ofFile::*)(void)) &ofFile::isFile)
         .def("isLink", (bool(ofFile::*)(void)) &ofFile::isLink)
         .def("isDirectory", (bool(ofFile::*)(void)) &ofFile::isDirectory)
         .def("isDevice", (bool(ofFile::*)(void)) &ofFile::isDevice)
         .def("isHidden", (bool(ofFile::*)(void)) &ofFile::isHidden)
         .def("setWriteable", (void(ofFile::*)(bool)) &ofFile::setWriteable)
         .def("setReadOnly", (void(ofFile::*)(bool)) &ofFile::setReadOnly)
         .def("setExecutable", (void(ofFile::*)(bool)) &ofFile::setExecutable)
         .def("copyTo", (bool(ofFile::*)(string,bool,bool)) &ofFile::copyTo)
         .def("moveTo", (bool(ofFile::*)(string,bool,bool)) &ofFile::moveTo)
         .def("renameTo", (bool(ofFile::*)(string,bool,bool)) &ofFile::renameTo)
         .def("remove", (bool(ofFile::*)(bool)) &ofFile::remove)
         .def("getSize", (uint64_t(ofFile::*)(void)) &ofFile::getSize)
         .def("readToBuffer", (ofBuffer(ofFile::*)(void)) &ofFile::readToBuffer)
         .def("writeFromBuffer", (bool(ofFile::*)(ofBuffer)) &ofFile::writeFromBuffer)
         .def("copyFromTo", (bool(*)(string,string,bool,bool)) &ofFile::copyFromTo)
         .def("moveFromTo", (bool(*)(string,string,bool,bool)) &ofFile::moveFromTo)
         .def("doesFileExist", (bool(*)(string,bool)) &ofFile::moveFromTo)
         .def("removeFile", (bool(*)(string,bool)) &ofFile::removeFile),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFileUtils
         
         def("ofBufferFromFile", &ofBufferFromFile),
         def("ofBufferToFile", &ofBufferToFile),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofHttpRequest
         
         class_<ofHttpRequest>("ofHttpRequest")
		 .def(constructor<>())
         .def(constructor<string,string,bool>())
         .def("getID", (int(ofHttpRequest::*)(void)) &ofHttpRequest::getID)
         .def_readonly("url", &ofHttpRequest::url)
         .def_readonly("name", &ofHttpRequest::name)
         .def_readonly("saveTo", &ofHttpRequest::saveTo),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPtr
         //class_<ofPtr>("ofPtr"),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofUtils
         
         def("ofGetElapsedTimeMillis", (int(*)(void)) &ofGetElapsedTimeMillis),
         def("ofGetElapsedTimeMicros", (unsigned long(*)(void)) &ofGetElapsedTimeMicros),
         def("ofGetElapsedTimef", (float(*)(void)) &ofGetElapsedTimef),
         def("ofGetSeconds", (int(*)(void)) &ofGetSeconds),
		 def("ofGetMinutes", (int(*)(void)) &ofGetMinutes),
		 def("ofGetHours", (int(*)(void)) &ofGetHours),
         def("ofLaunchBrowser", &ofLaunchBrowser),
         def("ofGetVersionInfo", &ofGetVersionInfo),
         def("ofToInt", (int(*)(const string&)) &ofToInt),
         def("ofToFloat", (float(*)(const string&)) &ofToFloat),
         def("ofSaveScreen", &ofSaveScreen),
         def("ofSaveFrame", &ofSaveFrame),
         def("ofSaveViewport", &ofSaveViewport),
         def("ofSplitString", (vector<string>(*)(const string&, const string&, bool)) &ofSplitString),
         def("ofGetYear", (int(*)(void)) &ofGetYear),
		 def("ofGetMonth", (int(*)(void)) &ofGetMonth),
		 def("ofGetDay", (int(*)(void)) &ofGetDay),
		 def("ofGetWeekday", (int(*)(void)) &ofGetWeekday),
         def("ofResetElapsedTimeCounter", (void(*)(void)) &ofResetElapsedTimeCounter),
         def("ofGetUnixTime", (unsigned int(*)(void)) &ofGetUnixTime),
         def("ofGetSystemTime", (unsigned long(*)(void)) &ofGetSystemTime),
         def("ofGetSystemTimeMicros", (unsigned long(*)(void)) &ofGetSystemTimeMicros),
         def("ofGetTimestampString", (string(*)(void)) &ofGetTimestampString),
		 def("ofGetTimestampString", (string(*)(string)) &ofGetTimestampString),
         def("ofToChar", (char(*)(const string&)) &ofToChar),
		 def("ofToBool", (bool(*)(const string&)) &ofToBool),
		 def("ofToBinary", (string(*)(const string&)) &ofToBinary),
		 //def("ofToBinary", (string(*)(const char*)) &ofToBinary),
		 def("ofBinaryToInt", (int(*)(const string&)) &ofBinaryToInt),
		 def("ofBinaryToChar", (char(*)(const string&)) &ofBinaryToChar),
		 def("ofBinaryToFloat", (float(*)(const string&)) &ofBinaryToFloat),
		 def("ofBinaryToString", (string(*)(const string&)) &ofBinaryToString),
		 def("ofJoinString", (string(*)(vector<string>, const string&)) &ofJoinString),
         def("ofHexToInt", (int(*)(const string&)) &ofHexToInt),
         def("ofHexToChar", (char(*)(const string&)) &ofHexToChar),
         def("ofHexToFloat", (float(*)(const string&)) &ofHexToFloat),
         def("ofHexToString", (string(*)(const string&)) &ofHexToString),
		 def("ofStringReplace", (void(*)(string&, string, string)) &ofStringReplace),
		 def("ofIsStringInString", (bool(*)(string, string)) &ofIsStringInString),
		 //def("ofGetFrameRate", &ofGetFrameRate),
		 //def("ofSetFrameRate", &ofSetFrameRate),
		 def("ofSleepMillis", &ofSleepMillis),
		 //def("ofGetLastFrameTime", &ofGetLastFrameTime),
		 //def("ofGetFrameNum", &ofGetFrameNum),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofThread
         
         class_<ofThread>("ofThread")
		 .def(constructor<>())
         .def("isThreadRunning", (bool(ofThread::*)(void)) &ofThread::isThreadRunning)
         .def("startThread", (void(ofThread::*)(bool,bool)) &ofThread::startThread)
         .def("lock", (void(ofThread::*)(void)) &ofThread::lock)
         .def("unlock", (void(ofThread::*)(void)) &ofThread::unlock)
         .def("stopThread", (void(ofThread::*)(bool)) &ofThread::stopThread)
         .def("waitForThread", (void(ofThread::*)(bool)) &ofThread::waitForThread),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofURLFileLoader
         
         class_<ofURLFileLoader>("ofURLFileLoader")
		 .def(constructor<>())
         .def("get", (ofHttpResponse(ofURLFileLoader::*)(string)) &ofURLFileLoader::get)
         .def("getAsync", (int(ofURLFileLoader::*)(string,string)) &ofURLFileLoader::getAsync)
         .def("saveTo", (ofHttpResponse(ofURLFileLoader::*)(string,string)) &ofURLFileLoader::saveTo)
         .def("saveAsync", (int(ofURLFileLoader::*)(string,string)) &ofURLFileLoader::saveAsync)
         .def("remove", (void(ofURLFileLoader::*)(int)) &ofURLFileLoader::remove)
         .def("clear", (void(ofURLFileLoader::*)(void)) &ofURLFileLoader::clear),
         
         def("ofLoadURL", (ofHttpResponse(*)(string)) &ofLoadURL),
         def("ofLoadURLAsync", (int(*)(string,string)) &ofLoadURLAsync),
         def("ofSaveURLTo", (ofHttpResponse(*)(string,string)) &ofSaveURLTo),
         def("ofSaveURLAsync", (int(*)(string,string)) &ofSaveURLAsync),
         def("ofRemoveURLRequest", (void(*)(int)) &ofRemoveURLRequest),
         def("ofRemoveAllURLRequests", (void(*)(void)) &ofRemoveAllURLRequests),
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section Video [ofVideoPlayer, ofVideoGrabber]
         
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVideoPlayer
         
         class_<ofVideoPlayer>("ofVideoPlayer")
		 .def(constructor<>())
		 .def("loadMovie", (bool(ofVideoPlayer::*)(string)) &ofVideoPlayer::loadMovie)
		 .def("closeMovie", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::closeMovie)
		 .def("close", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::close)
		 .def("update", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::update)
		 .def("idleMovie", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::idleMovie)
		 .def("play", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::play)
		 .def("stop", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::stop)
		 .def("isFrameNew", &ofVideoPlayer::isFrameNew)
		 .def("getPixels", (unsigned char*(ofVideoPlayer::*)(void)) &ofVideoPlayer::getPixels)
		 .def("getPosition", &ofVideoPlayer::getPosition)
		 .def("getSpeed", &ofVideoPlayer::getSpeed)
		 .def("getDuration", &ofVideoPlayer::getDuration)
		 .def("getIsMovieDone", &ofVideoPlayer::getIsMovieDone)
		 .def("setPosition", (void(ofVideoPlayer::*)(float)) &ofVideoPlayer::setPosition)
		 .def("setVolume", (void(ofVideoPlayer::*)(int)) &ofVideoPlayer::setVolume)
		 .def("setLoopState", &ofVideoPlayer::setLoopState)
		 .def("getLoopState", &ofVideoPlayer::getLoopState)
		 .def("setSpeed", (void(ofVideoPlayer::*)(float)) &ofVideoPlayer::setSpeed)
		 .def("setFrame", (void(ofVideoPlayer::*)(int)) &ofVideoPlayer::setFrame)
		 .def("setUseTexture", &ofVideoPlayer::setUseTexture)
		 .def("getTextureReference", &ofVideoPlayer::getTextureReference)
		 .def("draw", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::draw)
		 .def("draw", (void(ofVideoPlayer::*)(float,float,float,float)) &ofVideoPlayer::draw)
		 .def("draw", (void(ofVideoPlayer::*)(const ofPoint&)) &ofVideoPlayer::draw)
		 .def("draw", (void(ofVideoPlayer::*)(const ofRectangle&)) &ofVideoPlayer::draw)
		 .def("setAnchorPercent", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::setAnchorPercent)
		 .def("setAnchorPoint", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::setAnchorPoint)
		 .def("resetAnchor", &ofVideoPlayer::resetAnchor)
		 .def("setPaused", (void(ofVideoPlayer::*)(bool)) &ofVideoPlayer::setPaused)
		 .def("getCurrentFrame", &ofVideoPlayer::getCurrentFrame)
		 .def("getTotalNumFrames", &ofVideoPlayer::getTotalNumFrames)
		 .def("firstFrame", &ofVideoPlayer::firstFrame)
		 .def("nextFrame", &ofVideoPlayer::nextFrame)
		 .def("previousFrame", &ofVideoPlayer::previousFrame)
		 .def("getHeight", &ofVideoPlayer::getHeight)
		 .def("getWidth", &ofVideoPlayer::getWidth)
		 .def("isPaused", &ofVideoPlayer::isPaused)
		 .def("isLoaded", &ofVideoPlayer::isLoaded)
		 .def("isPlaying", &ofVideoPlayer::isPlaying)
		 .def_readonly("width", &ofVideoPlayer::width)
		 .def_readonly("height", &ofVideoPlayer::height),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVideoGrabber
         
         // LIMITED, ofVideoGrabber NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM
         // &
         // MANAGED FROM GUI (video tracking module) & FROM gamuza LIVE CODING FUNCTIONS (ga. module)
         
         
		 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section graphics [ofPath, ofImage, ofFloatImage, ofPixels, ofGraphics, ofPixelUtils, ofTrueTypeFont, ofTTFCharacter, ofPolyline, ofTessellator, ofRendererCollection]
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPath
         
         class_<ofPath>("ofPath")
		 .def(constructor<>())
		 .def("clear", (void(ofPath::*)(void)) &ofPath::clear)
         .def("newSubPath", (void(ofPath::*)(void)) &ofPath::newSubPath)
         .def("close", (void(ofPath::*)(void)) &ofPath::close)
         .def("lineTo", (void(ofPath::*)(const ofPoint&)) &ofPath::lineTo)
         .def("lineTo", (void(ofPath::*)(float,float,float)) &ofPath::lineTo)
         .def("moveTo", (void(ofPath::*)(const ofPoint&)) &ofPath::moveTo)
         .def("moveTo", (void(ofPath::*)(float,float,float)) &ofPath::moveTo)
         .def("curveTo", (void(ofPath::*)(const ofPoint&)) &ofPath::curveTo)
         .def("curveTo", (void(ofPath::*)(float,float)) &ofPath::curveTo)
         .def("curveTo", (void(ofPath::*)(float,float,float)) &ofPath::curveTo)
         .def("bezierTo", (void(ofPath::*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofPath::bezierTo)
         .def("bezierTo", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::bezierTo)
         .def("bezierTo", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::bezierTo)
         .def("quadBezierTo", (void(ofPath::*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofPath::quadBezierTo)
         .def("quadBezierTo", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::quadBezierTo)
         .def("quadBezierTo", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::quadBezierTo)
         .def("arc", (void(ofPath::*)(const ofPoint&,float,float,float,float)) &ofPath::arc)
         .def("arc", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::arc)
         .def("arc", (void(ofPath::*)(float,float,float,float,float,float,float)) &ofPath::arc)
         .def("setPolyWindingMode", (void(ofPath::*)(ofPolyWindingMode)) &ofPath::setPolyWindingMode)
         .def("setFilled", (void(ofPath::*)(bool)) &ofPath::setFilled)
         .def("setStrokeWidth", (void(ofPath::*)(float)) &ofPath::setStrokeWidth)
         .def("setColor", (void(ofPath::*)(const ofColor&)) &ofPath::setColor)
         .def("setHexColor", (void(ofPath::*)(int)) &ofPath::setHexColor)
         .def("setFillColor", (void(ofPath::*)(const ofColor&)) &ofPath::setFillColor)
         .def("setFillHexColor", (void(ofPath::*)(int)) &ofPath::setFillHexColor)
         .def("setStrokeColor", (void(ofPath::*)(const ofColor&)) &ofPath::setStrokeColor)
         .def("setStrokeHexColor", (void(ofPath::*)(int)) &ofPath::setStrokeHexColor)
         .def("getWindingMode", (ofPolyWindingMode(ofPath::*)(void)) &ofPath::getWindingMode)
         .def("isFilled", (bool(ofPath::*)(void)) &ofPath::isFilled)
         .def("getFillColor", (ofColor(ofPath::*)(void)) &ofPath::getFillColor)
         .def("getStrokeColor", (ofColor(ofPath::*)(void)) &ofPath::getStrokeColor)
         .def("getStrokeWidth", (float(ofPath::*)(void)) &ofPath::getStrokeWidth)
         .def("hasOutline", (bool(ofPath::*)(void)) &ofPath::hasOutline)
         .def("draw", (void(ofPath::*)(float,float)) &ofPath::draw)
         .def("draw", (void(ofPath::*)(void)) &ofPath::draw)
         //.def("getSubPaths", (ofSubPath(ofPath::*)(void)) &ofPath::getSubPaths)               NOT AVAILABLE
         .def("getOutline", (ofPolyline(ofPath::*)(void)) &ofPath::getOutline)
         .def("getTessellation", (ofMesh(ofPath::*)(void)) &ofPath::getTessellation)
         .def("simplify", (void(ofPath::*)(float)) &ofPath::simplify)
         .def("flagShapeChanged", (void(ofPath::*)(void)) &ofPath::flagShapeChanged)
         //.def("setMode", (void(ofPath::*)(Mode)) &ofPath::setMode)                            NOT AVAILABLE
         .def("setCurveResolution", (void(ofPath::*)(int)) &ofPath::setCurveResolution)
         .def("getCurveResolution", (int(ofPath::*)(void)) &ofPath::getCurveResolution)
         .def("setArcResolution", (void(ofPath::*)(int)) &ofPath::setArcResolution)
         .def("getArcResolution", (int(ofPath::*)(void)) &ofPath::getArcResolution)
         .def("setUseShapeColor", (void(ofPath::*)(bool)) &ofPath::setUseShapeColor)
         .def("getUseShapeColor", (bool(ofPath::*)(void)) &ofPath::getUseShapeColor)
         .def("tessellate", (void(ofPath::*)(void)) &ofPath::tessellate)
         .def("translate", (void(ofPath::*)(const ofPoint&)) &ofPath::translate)
         .def("rotate", (void(ofPath::*)(float,const ofVec3f&)) &ofPath::rotate)
         .def("scale", (void(ofPath::*)(float,float)) &ofPath::scale),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofImage
		 
		 class_<ofImage>("ofImage")
		 .def(constructor<>())
		 .def(constructor<const string&>())
		 .def("allocate", (void(ofImage::*)(int,int,int)) &ofImage::allocate)
		 .def("clear", (void(ofImage::*)(void)) &ofImage::clear)
         .def("clone", (void(ofImage::*)(const ofImage&)) &ofImage::clone)
         .def("setUseTexture", (void(ofImage::*)(bool)) &ofImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofImage::*)(void)) &ofImage::getTextureReference)
		 .def("loadImage", (bool(ofImage::*)(string)) &ofImage::loadImage)
         .def("saveImage", (void(ofImage::*)(string, ofImageQualityType)) &ofImage::saveImage)
         .def("saveImageBuffer", (void(ofImage::*)(ofBuffer&, ofImageQualityType)) &ofImage::saveImage)
		 .def("getPixels", (unsigned char*(ofImage::*)(void)) &ofImage::getPixels)
         .def("getPixelsRef", (ofPixels&(ofImage::*)(void)) &ofImage::getPixelsRef)
         .def("setFromPixels", (void(ofImage::*)(const ofPixels&)) &ofImage::setFromPixels)
		 .def("setImageType", (void(ofImage::*)(int)) &ofImage::setImageType)
         .def("resize", (void(ofImage::*)(int,int)) &ofImage::resize)
         .def("grabScreen", (void(ofImage::*)(int,int,int,int)) &ofImage::grabScreen)
         .def("update", (void(ofImage::*)(void)) &ofImage::update)
		 .def("draw", (void(ofImage::*)(float,float)) &ofImage::draw)
		 .def("draw", (void(ofImage::*)(float,float,float,float)) &ofImage::draw)
         .def("getWidth", (float(ofImage::*)(void)) &ofImage::getWidth)
         .def("getHeight", (float(ofImage::*)(void)) &ofImage::getHeight)
		 .def("getColor", (ofColor(ofImage::*)(int,int)) &ofImage::getColor)
		 .def("setColor", (void(ofImage::*)(int,int,ofColor)) &ofImage::setColor)
         .def("setImageType", (void(ofImage::*)(ofImageType)) &ofImage::setImageType)
         .def("crop", (void(ofImage::*)(int,int,int,int)) &ofImage::crop)
         .def("cropFrom", (void(ofImage::*)(ofImage&,int,int,int,int)) &ofImage::cropFrom)
         .def("rotate90", (void(ofImage::*)(int)) &ofImage::rotate90)
		 .def("mirror", (void(ofImage::*)(bool,bool)) &ofImage::mirror)
		 .def("setAnchorPoint", (void(ofImage::*)(float,float)) &ofImage::setAnchorPoint)
         .def("draw", (void(ofImage::*)(const ofRectangle&)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(const ofPoint&,float,float)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(float,float,float)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(const ofPoint&)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(float,float,float,float,float)) &ofImage::draw)
		 .def("bAllocated", (void(ofImage::*)(bool)) &ofImage::bAllocated)
         .def("reloadTexture", (void(ofImage::*)(void)) &ofImage::reloadTexture)
		 .def_readonly("width", &ofImage::width)
		 .def_readonly("height", &ofImage::height)
         .def_readonly("type", &ofImage::type)
		 .def_readonly("bpp", &ofImage::bpp),
         
         def("ofLoadImage",	(bool(*)(ofPixels&,string)) &ofLoadImage),
         //def("loadImage",	(bool(*)(ofPixels&,const ofBuffer&)) &ofLoadImage),
         //def("loadImage",	(bool(*)(ofTexture&,string)) &ofLoadImage),
         //def("loadImage",	(bool(*)(ofTexture&,const ofBuffer&)) &ofLoadImage),
         def("ofSaveImage",	(void(*)(ofPixels&,string,ofImageQualityType)) &ofSaveImage),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFloatImage
		 
		 class_<ofFloatImage>("ofFloatImage")
		 .def(constructor<>())
		 .def(constructor<const string&>())
		 .def("allocate", (void(ofFloatImage::*)(int,int,int)) &ofFloatImage::allocate)
		 .def("clear", (void(ofFloatImage::*)(void)) &ofFloatImage::clear)
         .def("clone", (void(ofFloatImage::*)(const ofFloatImage&)) &ofFloatImage::clone)
         .def("setUseTexture", (void(ofFloatImage::*)(bool)) &ofFloatImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofFloatImage::*)(void)) &ofFloatImage::getTextureReference)
		 .def("loadImage", (bool(ofFloatImage::*)(string)) &ofFloatImage::loadImage)
         .def("saveImage", (void(ofFloatImage::*)(string, ofImageQualityType)) &ofFloatImage::saveImage)
         .def("saveImageBuffer", (void(ofFloatImage::*)(ofBuffer&, ofImageQualityType)) &ofFloatImage::saveImage)
		 .def("getPixels", (unsigned char*(ofFloatImage::*)(void)) &ofFloatImage::getPixels)
         .def("setFromPixels", (void(ofImage::*)(const ofPixels&)) &ofImage::setFromPixels)
		 .def("setImageType", (void(ofFloatImage::*)(int)) &ofFloatImage::setImageType)
         .def("resize", (void(ofFloatImage::*)(int,int)) &ofFloatImage::resize)
         .def("grabScreen", (void(ofFloatImage::*)(int,int,int,int)) &ofFloatImage::grabScreen)
         .def("update", (void(ofFloatImage::*)(void)) &ofFloatImage::update)
		 .def("draw", (void(ofFloatImage::*)(float,float)) &ofFloatImage::draw)
		 .def("draw", (void(ofFloatImage::*)(float,float,float,float)) &ofFloatImage::draw)
         .def("getWidth", (float(ofFloatImage::*)(void)) &ofFloatImage::getWidth)
         .def("getHeight", (float(ofFloatImage::*)(void)) &ofFloatImage::getHeight)
		 .def("getColor", (ofColor(ofFloatImage::*)(int,int)) &ofFloatImage::getColor)
		 .def("setColor", (void(ofFloatImage::*)(int,int,ofColor)) &ofFloatImage::setColor)
         .def("setImageType", (void(ofFloatImage::*)(ofImageType)) &ofFloatImage::setImageType)
         .def("crop", (void(ofFloatImage::*)(int,int,int,int)) &ofFloatImage::crop)
         .def("cropFrom", (void(ofFloatImage::*)(ofFloatImage&,int,int,int,int)) &ofFloatImage::cropFrom)
         .def("rotate90", (void(ofFloatImage::*)(int)) &ofFloatImage::rotate90)
		 .def("mirror", (void(ofFloatImage::*)(bool,bool)) &ofFloatImage::mirror)
		 .def("setAnchorPoint", (void(ofFloatImage::*)(float,float)) &ofFloatImage::setAnchorPoint)
         .def("draw", (void(ofFloatImage::*)(const ofRectangle&)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(const ofPoint&,float,float)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(float,float,float)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(const ofPoint&)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(float,float,float,float,float)) &ofFloatImage::draw)
		 .def("bAllocated", (void(ofFloatImage::*)(bool)) &ofFloatImage::bAllocated)
         .def("reloadTexture", (void(ofFloatImage::*)(void)) &ofFloatImage::reloadTexture)
		 .def_readonly("width", &ofFloatImage::width)
		 .def_readonly("height", &ofFloatImage::height)
         .def_readonly("type", &ofFloatImage::type)
		 .def_readonly("bpp", &ofFloatImage::bpp),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPixels
		 
		 class_<ofPixels>("ofPixels")
		 .def(constructor<>())
		 .def("allocate", (void(ofPixels::*)(int,int,int)) &ofPixels::allocate)
		 .def("set", (void(ofPixels::*)(unsigned char)) &ofPixels::set)
         .def("setFromPixels", (void(ofPixels::*)(const unsigned char*,int,int,int)) &ofPixels::setFromPixels)
         .def("setFromPixels", (void(ofPixels::*)(const unsigned char*,int,int,ofImageType)) &ofPixels::setFromPixels)
         .def("setFromExternalPixels", (void(ofPixels::*)(unsigned char*,int,int,int)) &ofPixels::setFromExternalPixels)
         .def("setFromAlignedPixels", (void(ofPixels::*)(const unsigned char*,int,int,int,int)) &ofPixels::setFromAlignedPixels)
         .def("swapRgb", (void(ofPixels::*)(void)) &ofPixels::swapRgb)
         .def("clear", (void(ofPixels::*)(void)) &ofPixels::clear)
         .def("getPixels", (unsigned char*(ofPixels::*)(void)) &ofPixels::getPixels)
         .def("getPixelIndex", (int(ofPixels::*)(int,int)) &ofPixels::getPixelIndex)
         .def("getColor", (ofColor(ofPixels::*)(int,int)) &ofPixels::getColor)
		 .def("setColor", (void(ofPixels::*)(int,int,ofColor)) &ofPixels::setColor)
         .def("isAllocated", (bool(ofPixels::*)(void)) &ofPixels::isAllocated)
         .def("getWidth", (int(ofPixels::*)(void)) &ofPixels::getWidth)
		 .def("getHeight", (int(ofPixels::*)(void)) &ofPixels::getHeight)
         .def("getBytesPerPixel", (int(ofPixels::*)(void)) &ofPixels::getBytesPerPixel)
         .def("getBitsPerPixel", (int(ofPixels::*)(void)) &ofPixels::getBitsPerPixel)
         .def("getImageType", (ofImageType(ofPixels::*)(void)) &ofPixels::getImageType)
         
         // from ofPixelUtils, useful here because of the live-coding lua system wrapper
         .def("crop", (void(ofPixels::*)(int,int,int,int)) &ofPixels::crop)
         .def("rotate90", (void(ofPixels::*)(int)) &ofPixels::rotate90)
         .def("mirror", (void(ofPixels::*)(bool,bool)) &ofPixels::mirror)
         .def("resize", (void(ofPixels::*)(int,int)) &ofPixels::resize),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofGraphics
         
		 def("ofBackground",	(void(*)(int)) &background),
		 def("ofBackground",	(void(*)(int,int)) &ofBackground),
		 def("ofBackground",	(void(*)(int,int,int)) &background),
		 def("ofBackground",	(void(*)(int,int,int,int)) &ofBackground),
         def("ofBackgroundGradient",	(void(*)(const ofColor&, const ofColor&, ofGradientMode)) &ofBackgroundGradient),
         def("ofSetCircleResolution", (void(*)(int)) &ofSetCircleResolution),
         def("ofSetRectMode", (void(*)(int)) &ofSetRectMode),
         def("ofGetRectMode", (ofRectMode(*)(void)) &ofGetRectMode),
         def("ofRect", (void(*)(float,float,float,float)) &ofRect),
		 def("ofTriangle", (void(*)(float,float,float,float,float,float)) &ofTriangle),
		 def("ofCircle", (void(*)(float,float,float)) &ofCircle),
		 def("ofEllipse",	(void(*)(float,float,float,float)) &ofEllipse),
         def("ofLine", (void(*)(float,float,float,float)) &ofLine),
         def("ofCurve", (void(*)(float,float,float,float,float,float,float,float)) &ofCurve),
		 def("ofBezier", (void(*)(float,float,float,float,float,float,float,float)) &ofBezier),
         def("ofSetPolyMode", (void(*)(int)) &ofSetPolyMode),
         def("ofBeginShape", (void(*)(void)) &ofBeginShape),
         def("ofVertex",	(void(*)(float,float)) &ofVertex),
         def("ofVertex",	(void(*)(float,float,float)) &ofVertex),
		 def("ofCurveVertex", (void(*)(float,float)) &ofCurveVertex),
         def("ofCurveVertex", (void(*)(float,float,float)) &ofCurveVertex),
		 def("ofBezierVertex", (void(*)(float,float,float,float,float,float)) &ofBezierVertex),
         def("ofBezierVertex", (void(*)(float,float,float,float,float,float,float,float,float)) &ofBezierVertex),
		 def("ofNextContour", (void(*)(bool)) &ofNextContour),
         def("ofEndShape", (void(*)(bool)) &ofEndShape),
         def("ofNoFill", (void(*)(void)) &ofNoFill),
		 def("ofFill", (void(*)(void)) &ofFill),
         def("ofSetColor", (void(*)(int)) &setColor1),
         def("ofSetColor", (void(*)(int,int)) &setColor2),
         def("ofSetColor", (void(*)(int,int,int)) &ofSetColor),
		 def("ofSetColor", (void(*)(int,int,int,int)) &ofSetColor),
		 def("ofSetHexColor", (void(*)(int)) &ofSetHexColor),
         def("ofEnableAlphaBlending", (void(*)(void)) &ofEnableAlphaBlending),
		 def("ofDisableAlphaBlending", (void(*)(void)) &ofDisableAlphaBlending),
         def("ofEnableSmoothing", (void(*)(void)) &ofEnableSmoothing),
		 def("ofDisableSmoothing", (void(*)(void)) &ofDisableSmoothing),
         def("ofDrawBitmapString", (void(*)(string,const ofPoint&)) &ofDrawBitmapString),
         def("ofDrawBitmapString", (void(*)(string,float,float)) &ofDrawBitmapString),
         def("ofDrawBitmapString", (void(*)(string,float,float,float)) &ofDrawBitmapString),
         def("ofDrawBitmapStringHighlight", (void(*)(string,const ofPoint&,const ofColor&,const ofColor&)) &ofDrawBitmapStringHighlight),
         def("ofDrawBitmapStringHighlight", (void(*)(string,int,int,const ofColor&,const ofColor&)) &ofDrawBitmapStringHighlight),
         def("ofRotate", (void(*)(float,float,float,float)) &ofRotate),
         def("ofRotateX", (void(*)(float)) &ofRotateX),
		 def("ofRotateY", (void(*)(float)) &ofRotateY),
		 def("ofRotateZ", (void(*)(float)) &ofRotateZ),
         def("ofPushStyle", (void(*)(void)) &ofPushStyle),
         def("ofPopStyle", (void(*)(void)) &ofPopStyle),
         def("ofSetStyle", (void(*)(ofStyle)) &ofSetStyle),
         def("ofGetStyle", (void(*)(ofStyle)) &ofGetStyle),
         def("ofSetLineWidth", (void(*)(float)) &ofSetLineWidth),
         def("ofPushMatrix", (void(*)(void)) &ofPushMatrix),
		 def("ofPopMatrix", (void(*)(void)) &ofPopMatrix),
         def("ofTranslate", (void(*)(float,float,float)) &ofTranslate),
		 def("ofScale", (void(*)(float,float,float)) &ofScale),
         def("ofBeginSaveScreenAsPDF", (void(*)(string,bool,bool,ofRectangle)) &ofBeginSaveScreenAsPDF),
         def("ofEndSaveScreenAsPDF", (void(*)(void)) &ofEndSaveScreenAsPDF),
         def("ofPushView", (void(*)(void)) &ofPushView),
		 def("ofPopView", (void(*)(void)) &ofPopView),
         def("ofViewport", (void(*)(ofRectangle)) &ofViewport),
         def("ofViewport", (void(*)(float,float,float,float,bool)) &ofViewport),
         def("ofGetCurrentViewport", (ofRectangle(*)(void)) &ofGetCurrentViewport),
         def("ofGetViewportWidth", (int(*)(void)) &ofGetViewportWidth),
         def("ofGetViewportHeight", (int(*)(void)) &ofGetViewportHeight),
         def("ofTranslate", (void(*)(const ofPoint&)) &ofTranslate),
         def("ofRotate", (void(*)(float)) &ofRotate),
         def("ofSetupGraphicDefaults", (void(*)(void)) &ofSetupGraphicDefaults),
         def("ofSetupScreen", (void(*)(void)) &ofSetupScreen),
		 def("ofSetCurveResolution", (void(*)(int)) &ofSetCurveResolution),
         def("ofSetSphereResolution", (void(*)(int)) &ofSetSphereResolution),
         def("ofGetFill", (ofFillFlag(*)(void)) &ofGetFill),
         def("ofSetColor", (void(*)(const ofColor&)) &ofSetColor),
         def("ofSetColor", (void(*)(const ofColor&,int)) &ofSetColor),
         def("ofEnableBlendMode", (void(*)(ofBlendMode)) &ofEnableBlendMode),
		 def("ofDisableBlendMode", (void(*)(void)) &ofDisableBlendMode),
         def("ofEnablePointSprites", (void(*)(void)) &ofEnablePointSprites),
		 def("ofDisablePointSprites", (void(*)(void)) &ofDisablePointSprites),
		 def("ofClear", (void(*)(float,float,float,float)) &ofClear),
         def("ofClear", (void(*)(float,float)) &ofClear),
		 def("ofClearAlpha", (void(*)(void)) &ofClearAlpha),
         def("ofTriangle", (void(*)(float,float,float,float,float,float,float,float,float)) &ofTriangle),
         def("ofTriangle", (void(*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofTriangle),
         def("ofCircle", (void(*)(float,float,float,float)) &ofCircle),
         def("ofCircle", (void(*)(const ofPoint&,float)) &ofCircle),
         def("ofEllipse",	(void(*)(float,float,float,float,float)) &ofEllipse),
         def("ofEllipse",	(void(*)(const ofPoint&,float,float)) &ofEllipse),
         def("ofLine", (void(*)(float,float,float,float,float,float)) &ofLine),
         def("ofLine", (void(*)(const ofPoint&,const ofPoint&)) &ofLine),
         def("ofRect", (void(*)(const ofRectangle&)) &ofRect),
         def("ofRect", (void(*)(const ofPoint&,float,float)) &ofRect),
         def("ofRect", (void(*)(float,float,float,float,float)) &ofRect),
         def("ofVertex", (void(*)(ofPoint&)) &ofVertex),
         def("ofCurveVertex",	(void(*)(ofPoint&)) &ofCurveVertex),
         def("ofBezierVertex", (void(*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofBezierVertex),
         def("ofSphere", (void(*)(float,float,float,float)) &ofSphere),
         def("ofSphere", (void(*)(float,float,float)) &ofSphere),
         def("ofSphere", (void(*)(const ofPoint&,float)) &ofSphere),
         def("ofSphere", (void(*)(float)) &ofSphere),
         def("ofBox", (void(*)(float,float,float,float)) &ofBox),
         def("ofBox", (void(*)(float,float,float)) &ofBox),
         def("ofBox", (void(*)(const ofPoint&,float)) &ofBox),
         def("ofBox", (void(*)(float)) &ofBox),
         def("ofCone", (void(*)(float,float,float,float,float)) &ofCone),
         def("ofCone", (void(*)(float,float,float,float)) &ofCone),
         def("ofCone", (void(*)(const ofPoint&,float,float)) &ofCone),
         def("ofCone", (void(*)(float,float)) &ofCone),
         def("ofSetDrawBitmapMode", (void(*)(ofDrawBitmapMode)) &ofSetDrawBitmapMode),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPixelsUtils
         
         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM
         
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTrueTypeFont
		 
		 class_<ofTrueTypeFont>("ofTrueTypeFont")
		 .def(constructor<>())
         .def("loadFont", &loadFont2)
		 .def("loadFont", &loadFont4)
         .def("loadFont", &loadFont5)
         .def("loadFont", &loadFont7)
		 .def("getLineHeight", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getLineHeight)
		 .def("setLineHeight", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setLineHeight)
         .def("stringWidth", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringWidth)
		 .def("stringHeight", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringHeight)
         .def("getStringBoundingBox", (ofRectangle(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::getStringBoundingBox)
         .def("drawString", (void(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::drawString)
         .def("drawStringAsShapes", (void(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::drawStringAsShapes)
         .def("isLoaded", (bool(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::isLoaded)
         .def("isAntiAliased", (bool(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::isAntiAliased)
         .def("hasFullCharacterSet", (bool(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::hasFullCharacterSet)
         .def("getSize", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSize)
		 .def("getLetterSpacing", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getLetterSpacing)
		 .def("setLetterSpacing", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setLetterSpacing)
		 .def("getSpaceSize", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSpaceSize)
		 .def("setSpaceSize", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setSpaceSize)
		 .def("getNumCharacters", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getNumCharacters)
         .def("getCharacterAsPoints", (ofPath(ofTrueTypeFont::*)(int)) &ofTrueTypeFont::getCharacterAsPoints)
		 .def("getStringAsPoints", (vector<ofPath>(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::getStringAsPoints)
         .def("bind", (void(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::bind)
         .def("unbind", (void(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::unbind),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPolyLine
		 
		 class_<ofPolyline>("ofPolyline")
		 .def(constructor<>())
         .def("clear", (void(ofPolyline::*)(void)) &ofPolyline::clear)
         .def("addVertex", (void(ofPolyline::*)(float,float,float)) &ofPolyline::addVertex)
         .def("addVertexes", (void(ofPolyline::*)(const vector<ofPoint>&)) &ofPolyline::addVertexes)
         .def("lineTo", (void(ofPolyline::*)(const ofPoint&)) &ofPolyline::lineTo)
         .def("lineTo", (void(ofPolyline::*)(float,float,float)) &ofPolyline::lineTo)
         .def("arc", (void(ofPolyline::*)(const ofPoint&,float,float,float,float,int)) &ofPolyline::arc)
         .def("arc", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::arc)
         .def("arc", (void(ofPolyline::*)(float,float,float,float,float,float,float,int)) &ofPolyline::arc)
         .def("curveTo", (void(ofPolyline::*)(const ofPoint&,int)) &ofPolyline::curveTo)
         .def("curveTo", (void(ofPolyline::*)(float,float,float,int)) &ofPolyline::curveTo) // float x, float y, float z, int curveResolution
         .def("bezierTo", (void(ofPolyline::*)(const ofPoint&,const ofPoint&,const ofPoint&,int)) &ofPolyline::bezierTo)
         .def("bezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::bezierTo)
         .def("bezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,float,float,float,int)) &ofPolyline::bezierTo)
         .def("quadBezierTo", (void(ofPolyline::*)(const ofPoint&,const ofPoint&,const ofPoint&,int)) &ofPolyline::quadBezierTo)
         .def("quadBezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::quadBezierTo)
         .def("quadBezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,float,float,float,int)) &ofPolyline::quadBezierTo)
         .def("getSmoothed", (ofPolyline(ofPolyline::*)(int,float)) &ofPolyline::getSmoothed) // int smoothingSize
         .def("getResampledBySpacing", (ofPolyline(ofPolyline::*)(float)) &ofPolyline::getResampledBySpacing) // float spacing
         .def("getResampledByCount", (ofPolyline(ofPolyline::*)(int)) &ofPolyline::getResampledByCount) // int count
         .def("getBoundingBox", (ofRectangle(ofPolyline::*)(void)) &ofPolyline::getBoundingBox)
         .def("getClosestPoint", (ofPoint(ofPolyline::*)(const ofPoint&,unsigned int*)) &ofPolyline::getClosestPoint)
         .def("simplify", (void(ofPolyline::*)(float)) &ofPolyline::simplify)
         .def("size", (size_t(ofPolyline::*)(void)) &ofPolyline::size)
         .def("resize", (void(ofPolyline::*)(size_t)) &ofPolyline::resize)
         .def("setClosed", (void(ofPolyline::*)(bool)) &ofPolyline::setClosed)
         .def("isClosed", (bool(ofPolyline::*)(void)) &ofPolyline::isClosed)
         .def("close", (void(ofPolyline::*)(void)) &ofPolyline::close)
         .def("hasChanged", (bool(ofPolyline::*)(void)) &ofPolyline::hasChanged)
         .def("getVertices", (vector<ofPoint>&(ofPolyline::*)(void)) &ofPolyline::getVertices)
         .def("getPerimeter", (float(ofPolyline::*)(void)) &ofPolyline::getPerimeter)
         .def("draw", (void(ofPolyline::*)(void)) &ofPolyline::draw),
		 
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTessellator
         
         class_<ofTessellator>("ofTessellator")
		 .def(constructor<>())
         .def(constructor<const ofTessellator&>()),
         // void ofTessellator::tessellateToMesh(const vector< ofPolyline > &src, ofPolyWindingMode polyWindingMode, ofMesh &dstmesh, bool bIs2D=false)
         //.def("tessellateToMesh", (float(ofTessellator::*)(const ofPolyline&, ofPolyWindingMode, ofMesh&,bool)) &ofTessellator::tessellateToMesh),
         // void ofTessellator::tessellateToPolylines(const vector< ofPolyline > &src, ofPolyWindingMode polyWindingMode, vector< ofPolyline > &dstpoly, bool bIs2D=false)
         // void ofTessellator::tessellateToPolylines(const ofPolyline &src, ofPolyWindingMode polyWindingMode, vector< ofPolyline > &dstpoly, bool bIs2D=false)
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofRendererCollection
         
         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM
         
		 
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section types [ofColor, ofStyle, ofTypes, ofRectangle, ofPoint]
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofColor
		 
		 class_<ofColor>("ofColor")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
         .def(constructor<ofColor const&>())
         .def(constructor<ofColor const&,float>())
		 .def(constructor<float,float>())
         .def("getHex", (int(ofColor::*)(void)) &ofColor::getHex)
         .def("clamp", (ofColor(ofColor::*)(void)) &ofColor::clamp)
         .def("invert", (ofColor(ofColor::*)(void)) &ofColor::invert)
         .def("normalize", (ofColor(ofColor::*)(void)) &ofColor::normalize)
         .def("getClamped", (ofColor(ofColor::*)(void)) &ofColor::getClamped)
         .def("getInverted", (ofColor(ofColor::*)(void)) &ofColor::getInverted)
         .def("getNormalized", (ofColor(ofColor::*)(void)) &ofColor::getNormalized)
         .def("getHue", (float(ofColor::*)(void)) &ofColor::getHue)
		 .def("getSaturation", (float(ofColor::*)(void)) &ofColor::getSaturation)
		 .def("getBrightness", (float(ofColor::*)(void)) &ofColor::getBrightness)
         .def("getLightness", (float(ofColor::*)(void)) &ofColor::getLightness)
         .def("setHue", (void(ofColor::*)(float)) &ofColor::setHue)
		 .def("setSaturation", (void(ofColor::*)(float)) &ofColor::setSaturation)
		 .def("setBrightness", (void(ofColor::*)(float)) &ofColor::setBrightness)
         .def("setHsb", (void(ofColor::*)(float,float,float,float)) &ofColor::setHsb)
         .def("setHsb", (void(ofColor::*)(float,float,float)) &ofColor::setHsb)
		 .def("set", (void(ofColor::*)(float,float,float,float)) &ofColor::set)
		 .def("set", (void(ofColor::*)(float,float)) &ofColor::set)
         .def("set", (void(ofColor::*)(ofColor const&)) &ofColor::set)
		 .def("setHex", (void(ofColor::*)(int,float)) &ofColor::setHex)
		 .def("lerp", (ofColor(ofColor::*)(const ofColor&, float)) &ofColor::lerp)
         .def("getLerped", (ofColor(ofColor::*)(const ofColor&, float)) &ofColor::getLerped)
		 .def("getHsb", (void(ofColor::*)(float&,float&,float&)) &ofColor::getHsb)
         .def_readonly("r", &ofColor::r)
		 .def_readonly("g", &ofColor::g)
		 .def_readonly("b", &ofColor::b)
		 .def_readonly("a", &ofColor::a),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFloatColor
		 
		 class_<ofFloatColor>("ofFloatColor")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
         .def(constructor<ofFloatColor const&>())
         .def(constructor<ofFloatColor const&,float>())
		 .def(constructor<float,float>())
         .def("getHex", (int(ofFloatColor::*)(void)) &ofFloatColor::getHex)
         .def("clamp", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::clamp)
         .def("invert", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::invert)
         .def("normalize", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::normalize)
         .def("getClamped", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::getClamped)
         .def("getInverted", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::getInverted)
         .def("getNormalized", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::getNormalized)
         .def("getHue", (float(ofFloatColor::*)(void)) &ofFloatColor::getHue)
		 .def("getSaturation", (float(ofFloatColor::*)(void)) &ofFloatColor::getSaturation)
		 .def("getBrightness", (float(ofFloatColor::*)(void)) &ofFloatColor::getBrightness)
         .def("getLightness", (float(ofFloatColor::*)(void)) &ofFloatColor::getLightness)
         .def("setHue", (void(ofFloatColor::*)(float)) &ofFloatColor::setHue)
		 .def("setSaturation", (void(ofFloatColor::*)(float)) &ofFloatColor::setSaturation)
		 .def("setBrightness", (void(ofFloatColor::*)(float)) &ofFloatColor::setBrightness)
         .def("setHsb", (void(ofFloatColor::*)(float,float,float,float)) &ofFloatColor::setHsb)
         .def("setHsb", (void(ofFloatColor::*)(float,float,float)) &ofFloatColor::setHsb)
		 .def("set", (void(ofFloatColor::*)(float,float,float,float)) &ofFloatColor::set)
		 .def("set", (void(ofFloatColor::*)(float,float)) &ofFloatColor::set)
         .def("set", (void(ofFloatColor::*)(ofFloatColor const&)) &ofFloatColor::set)
		 .def("setHex", (void(ofFloatColor::*)(int,float)) &ofFloatColor::setHex)
		 .def("lerp", (ofFloatColor(ofFloatColor::*)(const ofFloatColor&, float)) &ofFloatColor::lerp)
         .def("getLerped", (ofFloatColor(ofFloatColor::*)(const ofFloatColor&, float)) &ofFloatColor::getLerped)
		 .def("getHsb", (void(ofFloatColor::*)(float&,float&,float&)) &ofFloatColor::getHsb)
         .def_readonly("r", &ofFloatColor::r)
		 .def_readonly("g", &ofFloatColor::g)
		 .def_readonly("b", &ofFloatColor::b)
		 .def_readonly("a", &ofFloatColor::a),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofShortColor
		 
		 class_<ofShortColor>("ofShortColor")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
         .def(constructor<ofShortColor const&>())
         .def(constructor<ofShortColor const&,float>())
		 .def(constructor<float,float>())
         .def("getHex", (int(ofShortColor::*)(void)) &ofShortColor::getHex)
         .def("clamp", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::clamp)
         .def("invert", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::invert)
         .def("normalize", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::normalize)
         .def("getClamped", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::getClamped)
         .def("getInverted", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::getInverted)
         .def("getNormalized", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::getNormalized)
         .def("getHue", (float(ofShortColor::*)(void)) &ofShortColor::getHue)
		 .def("getSaturation", (float(ofShortColor::*)(void)) &ofShortColor::getSaturation)
		 .def("getBrightness", (float(ofShortColor::*)(void)) &ofShortColor::getBrightness)
         .def("getLightness", (float(ofShortColor::*)(void)) &ofShortColor::getLightness)
         .def("setHue", (void(ofShortColor::*)(float)) &ofShortColor::setHue)
		 .def("setSaturation", (void(ofShortColor::*)(float)) &ofShortColor::setSaturation)
		 .def("setBrightness", (void(ofShortColor::*)(float)) &ofShortColor::setBrightness)
         .def("setHsb", (void(ofShortColor::*)(float,float,float,float)) &ofShortColor::setHsb)
         .def("setHsb", (void(ofShortColor::*)(float,float,float)) &ofShortColor::setHsb)
		 .def("set", (void(ofShortColor::*)(float,float,float,float)) &ofShortColor::set)
		 .def("set", (void(ofShortColor::*)(float,float)) &ofShortColor::set)
         .def("set", (void(ofShortColor::*)(ofShortColor const&)) &ofShortColor::set)
		 .def("setHex", (void(ofShortColor::*)(int,float)) &ofShortColor::setHex)
		 .def("lerp", (ofShortColor(ofShortColor::*)(const ofShortColor&, float)) &ofShortColor::lerp)
         .def("getLerped", (ofShortColor(ofShortColor::*)(const ofShortColor&, float)) &ofShortColor::getLerped)
		 .def("getHsb", (void(ofShortColor::*)(float&,float&,float&)) &ofShortColor::getHsb)
         .def_readonly("r", &ofShortColor::r)
		 .def_readonly("g", &ofShortColor::g)
		 .def_readonly("b", &ofShortColor::b)
		 .def_readonly("a", &ofShortColor::a),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofStyle
         
         class_<ofStyle>("ofStyle")
		 .def(constructor<>())
         .def_readwrite("color", &ofStyle::color)
         .def_readwrite("polyMode", &ofStyle::polyMode)
         .def_readwrite("rectMode", &ofStyle::rectMode)
         .def_readwrite("bFill", &ofStyle::bFill)
         .def_readwrite("smoothing", &ofStyle::smoothing)
         .def_readwrite("circleResolution", &ofStyle::circleResolution)
         .def_readwrite("lineWidth", &ofStyle::lineWidth)
         .def_readwrite("bgColor", &ofStyle::bgColor)
         .def_readwrite("drawBitmapMode", &ofStyle::drawBitmapMode)
         .def_readwrite("blendingMode", &ofStyle::blendingMode)
         .def_readwrite("sphereResolution", &ofStyle::sphereResolution)
         .def_readwrite("curveResolution", &ofStyle::curveResolution),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTypes
         
         ////////////////////////////////////////////
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofRectangle
         
         class_<ofRectangle>("ofRectangle")
		 .def(constructor<>())
         .def(constructor<float,float,float,float>())
		 .def(constructor<ofRectangle const&>())
		 .def("set", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::set)
         .def("set", (void(ofRectangle::*)(const ofPoint&,float,float)) &ofRectangle::set)
		 .def("set", (void(ofRectangle::*)(const ofRectangle&)) &ofRectangle::set)
         .def("setX", (void(ofRectangle::*)(float)) &ofRectangle::setX)
         .def("setY", (void(ofRectangle::*)(float)) &ofRectangle::setY)
         .def("setWidth", (void(ofRectangle::*)(float)) &ofRectangle::setWidth)
         .def("setHeight", (void(ofRectangle::*)(float)) &ofRectangle::setHeight)
         .def("setPosition", (void(ofRectangle::*)(float,float)) &ofRectangle::setPosition)
         .def("setPosition", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::setPosition)
		 .def("setFromCenter", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::setFromCenter)
         .def("setFromCenter", (void(ofRectangle::*)(const ofPoint&,float,float)) &ofRectangle::setFromCenter)
         .def("translate", (void(ofRectangle::*)(float,float)) &ofRectangle::translate)
         .def("translate", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::translate)
         .def("translateX", (void(ofRectangle::*)(float)) &ofRectangle::translateX)
         .def("translateY", (void(ofRectangle::*)(float)) &ofRectangle::translateY)
         .def("scale", (void(ofRectangle::*)(float)) &ofRectangle::scale)
         .def("scale", (void(ofRectangle::*)(float,float)) &ofRectangle::scale)
         .def("scale", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::scale)
         .def("scaleWidth", (void(ofRectangle::*)(float)) &ofRectangle::scaleWidth)
         .def("scaleHeight", (void(ofRectangle::*)(float)) &ofRectangle::scaleHeight)
         .def("scaleFromCenter", (void(ofRectangle::*)(float)) &ofRectangle::scaleFromCenter)
         .def("scaleFromCenter", (void(ofRectangle::*)(float,float)) &ofRectangle::scaleFromCenter)
         .def("scaleFromCenter", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::scaleFromCenter)
         .def("scaleTo", (void(ofRectangle::*)(const ofRectangle&,ofScaleMode)) &ofRectangle::scaleTo)
         .def("scaleTo", (void(ofRectangle::*)(const ofRectangle&,ofAspectRatioMode,ofAlignHorz,ofAlignVert)) &ofRectangle::scaleTo)
         .def("scaleTo", (void(ofRectangle::*)(const ofRectangle&,ofAspectRatioMode,ofAlignHorz,ofAlignVert,ofAlignHorz,ofAlignVert)) &ofRectangle::scaleTo)
         .def("alignToHorz", (void(ofRectangle::*)(const float&,ofAlignHorz)) &ofRectangle::alignToHorz)
         .def("alignToHorz", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz)) &ofRectangle::alignToHorz)
         .def("alignToHorz", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz,ofAlignHorz)) &ofRectangle::alignToHorz)
         .def("alignToVert", (void(ofRectangle::*)(const float&,ofAlignVert)) &ofRectangle::alignToVert)
         .def("alignToVert", (void(ofRectangle::*)(const ofRectangle&,ofAlignVert)) &ofRectangle::alignToVert)
         .def("alignToVert", (void(ofRectangle::*)(const ofRectangle&,ofAlignVert,ofAlignVert)) &ofRectangle::alignToVert)
         .def("alignTo", (void(ofRectangle::*)(const ofPoint&,ofAlignHorz,ofAlignVert)) &ofRectangle::alignTo)
         .def("alignTo", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz,ofAlignVert)) &ofRectangle::alignTo)
         .def("alignTo", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz,ofAlignVert,ofAlignHorz,ofAlignVert)) &ofRectangle::alignTo)
         //.def("inside", (const bool(ofRectangle::*)(const ofPoint&)) &ofRectangle::inside)
         //.def("inside", (const bool(ofRectangle::*)(const ofRectangle&)) &ofRectangle::inside)
		 //.def("inside", (const bool(ofRectangle::*)(float,float)) &ofRectangle::inside)
         //.def("inside", (const bool(ofRectangle::*)(const ofPoint&,const ofPoint&)) &ofRectangle::inside)
         //.def("intersects", (bool(ofRectangle::*)(const ofRectangle&)) &ofRectangle::intersects)
         //.def("intersects", (bool(ofRectangle::*)(const ofPoint&,const ofPoint&)) &ofRectangle::intersects)
         .def("growToInclude", (void(ofRectangle::*)(float,float)) &ofRectangle::growToInclude)
         .def("growToInclude", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::growToInclude)
         .def("growToInclude", (void(ofRectangle::*)(const ofRectangle&)) &ofRectangle::growToInclude)
         .def("growToInclude", (void(ofRectangle::*)(const ofPoint&,const ofPoint&)) &ofRectangle::growToInclude)
         .def("getIntersection", (ofRectangle(ofRectangle::*)(const ofRectangle&)) &ofRectangle::getIntersection)
         .def("getUnion", (ofRectangle(ofRectangle::*)(const ofRectangle&)) &ofRectangle::getUnion)
         .def("standardize", (void(ofRectangle::*)(void)) &ofRectangle::standardize)
         .def("getStandardized", (ofRectangle(ofRectangle::*)(void)) &ofRectangle::getStandardized)
         .def("isStandardized", (bool(ofRectangle::*)(void)) &ofRectangle::isStandardized)
         .def("getArea", (float(ofRectangle::*)(void)) &ofRectangle::getArea)
         .def("getPerimeter", (float(ofRectangle::*)(void)) &ofRectangle::getPerimeter)
         .def("getAspectRatio", (float(ofRectangle::*)(void)) &ofRectangle::getAspectRatio)
         .def("isEmpty", (bool(ofRectangle::*)(void)) &ofRectangle::isEmpty)
         .def("getMin", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getMin)
         .def("getMax", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getMax)
         .def("getMinX", (float(ofRectangle::*)(void)) &ofRectangle::getMinX)
         .def("getMaxX", (float(ofRectangle::*)(void)) &ofRectangle::getMaxX)
         .def("getMinY", (float(ofRectangle::*)(void)) &ofRectangle::getMinY)
         .def("getMaxY", (float(ofRectangle::*)(void)) &ofRectangle::getMaxY)
         .def("getLeft", (float(ofRectangle::*)(void)) &ofRectangle::getLeft)
         .def("getRight", (float(ofRectangle::*)(void)) &ofRectangle::getRight)
         .def("getTop", (float(ofRectangle::*)(void)) &ofRectangle::getTop)
         .def("getBottom", (float(ofRectangle::*)(void)) &ofRectangle::getBottom)
         .def("getTopLeft", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getTopLeft)
         .def("getTopRight", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getTopRight)
         .def("getBottomLeft", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getBottomLeft)
         .def("getBottomRight", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getBottomRight)
         .def("getHorzAnchor", (float(ofRectangle::*)(ofAlignHorz)) &ofRectangle::getHorzAnchor)
         .def("getVertAnchor", (float(ofRectangle::*)(ofAlignVert)) &ofRectangle::getVertAnchor)
         .def("getPosition", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getPosition)
         .def("getCenter", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getCenter)
         .def("getX", (float(ofRectangle::*)(void)) &ofRectangle::getX)
         .def("getY", (float(ofRectangle::*)(void)) &ofRectangle::getY)
         .def("getWidth", (float(ofRectangle::*)(void)) &ofRectangle::getWidth)
         .def("getHeight", (float(ofRectangle::*)(void)) &ofRectangle::getHeight)
		 .def_readonly("position", &ofRectangle::position)
		 .def_readonly("width", &ofRectangle::width)
		 .def_readonly("height", &ofRectangle::height),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPoint --  Use ofVec3f instead
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section events [ofKeyEventArgs, ofAudioEventArgs, ofCoreEvents, ofEventArgs, ofEvent, ofMouseEventArgs, ofResizeEventArgs, ofEvents, ofEventUtils]
         
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofEvents
         
         /*def("ofGetMousePressed", &ofGetMousePressed),
         def("ofGetKeyPressed", &ofGetKeyPressed),
         def("ofGetMouseX", &ofGetMouseX),
         def("ofGetMouseY", &ofGetMouseY),
         def("ofGetPreviousMouseX", &ofGetPreviousMouseX),
         def("ofGetPreviousMouseY", &ofGetPreviousMouseY),*/
         
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section sound [ofSoundPlayer, ofSoundStream]
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofSoundPlayer
         
         def("ofSoundUpdate", &ofSoundUpdate),
         def("ofSoundGetSpectrum", &ofSoundGetSpectrum),
		 
		 class_<ofSoundPlayer>("ofSoundPlayer")
		 .def(constructor<>())
		 .def("loadSound", (void(ofSoundPlayer::*)(string,bool)) &ofSoundPlayer::loadSound)
		 .def("unloadSound", (void(ofSoundPlayer::*)(void)) &ofSoundPlayer::unloadSound)
		 .def("play", (void(ofSoundPlayer::*)(void)) &ofSoundPlayer::play)
		 .def("stop", (void(ofSoundPlayer::*)(void)) &ofSoundPlayer::stop)
		 .def("setVolume", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setVolume)
		 .def("setPan", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setPan)
		 .def("setSpeed", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setSpeed)
		 .def("setPaused", (void(ofSoundPlayer::*)(bool)) &ofSoundPlayer::setPaused)
		 .def("setLoop", (void(ofSoundPlayer::*)(bool)) &ofSoundPlayer::setLoop)
		 .def("setMultiPlay", (void(ofSoundPlayer::*)(bool)) &ofSoundPlayer::setMultiPlay)
		 .def("setPosition", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setPosition)
         .def("setPositionMS", (void(ofSoundPlayer::*)(int)) &ofSoundPlayer::setPositionMS)
         .def("getPositionMS", (int(ofSoundPlayer::*)(void)) &ofSoundPlayer::getPositionMS)
		 .def("getPosition", (float(ofSoundPlayer::*)(void)) &ofSoundPlayer::getPosition)
		 .def("getIsPlaying", (bool(ofSoundPlayer::*)(void)) &ofSoundPlayer::getIsPlaying)
		 .def("getSpeed", (float(ofSoundPlayer::*)(void)) &ofSoundPlayer::getSpeed)
		 .def("getPan", (float(ofSoundPlayer::*)(void)) &ofSoundPlayer::getPan)
         .def("getVolume", (float(ofSoundPlayer::*)(void)) &ofSoundPlayer::getVolume)
         .def("isLoaded", (bool(ofSoundPlayer::*)(void)) &ofSoundPlayer::isLoaded),
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofSoundStream
         
         // MANAGED FROM GUI (audio module) & FROM gamuza LIVE CODING FUNCTIONS
        
         
         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section serial
         
         class_<ofSerial>("ofSerial")
		 .def(constructor<>())
		 .def("listDevices", (void(ofSerial::*)(void)) &ofSerial::listDevices)
         .def("close", (void(ofSerial::*)(void)) &ofSerial::close)
         .def("setup", (bool(ofSerial::*)(void)) &ofSerial::setup)
         .def("setup", (bool(ofSerial::*)(string,int)) &ofSerial::setup)
         .def("setup", (bool(ofSerial::*)(int,int)) &ofSerial::setup)
         .def("readBytes", (void(ofSerial::*)(unsigned char*,int)) &ofSerial::readBytes)
         .def("writeBytes", (void(ofSerial::*)(unsigned char*,int)) &ofSerial::writeBytes)
         .def("writeByte", (void(ofSerial::*)(unsigned char)) &ofSerial::writeByte)
         
         .def("readByte", (int(ofSerial::*)(void)) &ofSerial::readByte)
         .def("flush", (void(ofSerial::*)(bool,bool)) &ofSerial::flush)
         .def("available", (int(ofSerial::*)(void)) &ofSerial::available)
         .def("drain", (void(ofSerial::*)(void)) &ofSerial::drain),
         
         
         ///////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////
		 
        
        //////////////////////////////////////////////////////////////
		///////////////////////////////
		/// OpenFrameworks 0.7.4 addons api wrapper
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFX3DMODELLOADER
         
         ///////////////////////////////
         // ofx3DBaseLoader
         class_<ofx3DBaseLoader>("ofx3DBaseLoader")
         .def(constructor<>())
         .def("loadModel", (void(ofx3DBaseLoader::*)(string,float)) &ofx3DBaseLoader::loadModel)
         .def("loadModel", (void(ofx3DBaseLoader::*)(string)) &ofx3DBaseLoader::loadModel)
         .def("draw", (void(ofx3DBaseLoader::*)(void)) &ofx3DBaseLoader::draw)
         .def_readonly("hasTexture", &ofx3DBaseLoader::hasTexture),
         
         ///////////////////////////////
         // ofx3DModelLoader
         class_<ofx3DModelLoader>("ofx3DModelLoader")
         .def(constructor<>())
         .def("loadModel", (void(ofx3DModelLoader::*)(string,float)) &ofx3DModelLoader::loadModel)
         .def("setPosition", (void(ofx3DModelLoader::*)(float,float,float)) &ofx3DModelLoader::setPosition)
         .def("setScale", (void(ofx3DModelLoader::*)(float,float,float)) &ofx3DModelLoader::setScale)
         .def("setRotation", (void(ofx3DModelLoader::*)(int,float,float,float,float)) &ofx3DModelLoader::setRotation)
         .def("draw", (void(ofx3DModelLoader::*)(void)) &ofx3DModelLoader::draw)
         .def_readonly("rotAngle", &ofx3DModelLoader::rotAngle)
         .def_readonly("rotAxis", &ofx3DModelLoader::rotAxis)
         .def_readonly("scale", &ofx3DModelLoader::scale)
         .def_readonly("pos", &ofx3DModelLoader::pos)
         .def_readonly("numRotations", &ofx3DModelLoader::numRotations)
         .def_readonly("model", &ofx3DModelLoader::model),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXASSIMPMODELLOADER
         
         ///////////////////////////////
         // ofxAssimpModelLoader
         class_<ofxAssimpModelLoader>("ofxAssimpModelLoader")
         .def(constructor<>())
         .def("loadModel", (bool(ofxAssimpModelLoader::*)(string,bool)) &ofxAssimpModelLoader::loadModel)
         .def("loadModel", (bool(ofxAssimpModelLoader::*)(ofBuffer&,bool,const char*)) &ofxAssimpModelLoader::loadModel)
         .def("createEmptyModel", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::createEmptyModel)
         .def("createLightsFromAiModel", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::createLightsFromAiModel)
         .def("optimizeScene", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::optimizeScene)
         .def("update", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::update)
         .def("hasAnimations", (bool(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::hasAnimations)
         .def("getAnimationCount", (unsigned int(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getAnimationCount)
         .def("getAnimation", (ofxAssimpAnimation&(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getAnimation)
         .def("playAllAnimations", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::playAllAnimations)
         .def("stopAllAnimations", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::stopAllAnimations)
         .def("resetAllAnimations", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::resetAllAnimations)
         .def("setPausedForAllAnimations", (void(ofxAssimpModelLoader::*)(bool)) &ofxAssimpModelLoader::setPausedForAllAnimations)
         .def("setLoopStateForAllAnimations", (void(ofxAssimpModelLoader::*)(ofLoopType)) &ofxAssimpModelLoader::setLoopStateForAllAnimations)
         .def("setPositionForAllAnimations", (void(ofxAssimpModelLoader::*)(float)) &ofxAssimpModelLoader::setPositionForAllAnimations)
         .def("hasMeshes", (bool(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::hasMeshes)
         .def("getMeshCount", (unsigned int(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getMeshCount)
         .def("getMeshHelper", (ofxAssimpMeshHelper&(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getMeshHelper)
         .def("clear", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::clear)
         .def("setScale", (void(ofxAssimpModelLoader::*)(float,float,float)) &ofxAssimpModelLoader::setScale)
         .def("setPosition", (void(ofxAssimpModelLoader::*)(float,float,float)) &ofxAssimpModelLoader::setPosition)
         .def("setRotation", (void(ofxAssimpModelLoader::*)(int,float,float,float,float)) &ofxAssimpModelLoader::setRotation)
         .def("setScaleNomalization", (void(ofxAssimpModelLoader::*)(bool)) &ofxAssimpModelLoader::setScaleNomalization)
         .def("setNormalizationFactor", (void(ofxAssimpModelLoader::*)(float)) &ofxAssimpModelLoader::setNormalizationFactor)
         .def("getNumMeshes", (int(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getNumMeshes)
         .def("getMesh", (ofMesh(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getMesh)
         .def("getMesh", (ofMesh(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getMesh)
         .def("getCurrentAnimatedMesh", (ofMesh(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getCurrentAnimatedMesh)
         .def("getCurrentAnimatedMesh", (ofMesh(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getCurrentAnimatedMesh)
         .def("getMaterialForMesh", (ofMaterial(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getMaterialForMesh)
         .def("getMaterialForMesh", (ofMaterial(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getMaterialForMesh)
         .def("getTextureForMesh", (ofTexture(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getTextureForMesh)
         .def("getTextureForMesh", (ofTexture(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getTextureForMesh)
         .def("drawWireframe", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::drawWireframe)
         .def("drawFaces", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::drawFaces)
         .def("drawVertices", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::drawVertices)
         .def("enableTextures", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableTextures)
         .def("disableTextures", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableTextures)
         .def("enableNormals", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableNormals)
         .def("enableMaterials", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableMaterials)
         .def("disableNormals", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableNormals)
         .def("enableColors", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableColors)
         .def("disableColors", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableColors)
         .def("disableMaterials", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableMaterials)
         .def("draw", (void(ofxAssimpModelLoader::*)(ofPolyRenderMode)) &ofxAssimpModelLoader::draw)
         .def("getPosition", (ofPoint(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getPosition)
         .def("getSceneCenter", (ofPoint(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getSceneCenter)
         .def("getNormalizedScale", (float(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getNormalizedScale)
         .def("getScale", (ofPoint(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getScale)
         .def("getModelMatrix", (ofMatrix4x4(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getModelMatrix)
         .def("getSceneMin", (ofPoint(ofxAssimpModelLoader::*)(bool)) &ofxAssimpModelLoader::getSceneMin)
         .def("getSceneMax", (ofPoint(ofxAssimpModelLoader::*)(bool)) &ofxAssimpModelLoader::getSceneMax)
         .def("getNumRotations", (int(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getNumRotations)
         .def("getRotationAxis", (ofPoint(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getRotationAxis)
         .def("getRotationAngle", (float(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getRotationAngle)
         .def("calculateDimensions", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::calculateDimensions),
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXNETWORK
         
         ///////////////////////////////
         // ofxTCPClient
         class_<ofxTCPClient>("ofxTCPClient")
         .def(constructor<>())
         .def("setVerbose", (void(ofxTCPClient::*)(bool)) &ofxTCPClient::setVerbose)
         .def("setup", (bool(ofxTCPClient::*)(string,int,bool)) &ofxTCPClient::setup)
         .def("setMessageDelimiter", (void(ofxTCPClient::*)(string)) &ofxTCPClient::setMessageDelimiter)
         .def("close", (bool(ofxTCPClient::*)(void)) &ofxTCPClient::close)
         .def("send", (bool(ofxTCPClient::*)(string)) &ofxTCPClient::send)
         .def("sendRaw", (bool(ofxTCPClient::*)(string)) &ofxTCPClient::sendRaw)
         .def("getNumReceivedBytes", (int(ofxTCPClient::*)(void)) &ofxTCPClient::getNumReceivedBytes)
         .def("sendRawBytes", (bool(ofxTCPClient::*)(const char*, const int)) &ofxTCPClient::sendRawBytes)
         .def("receive", (string(ofxTCPClient::*)(void)) &ofxTCPClient::receive)
         .def("receiveRaw", (string(ofxTCPClient::*)(void)) &ofxTCPClient::receiveRaw)
         .def("receiveRawBytes", (int(ofxTCPClient::*)(const char*,int)) &ofxTCPClient::receiveRawBytes)
         .def("isConnected", (bool(ofxTCPClient::*)(void)) &ofxTCPClient::isConnected)
         .def("getPort", (int(ofxTCPClient::*)(void)) &ofxTCPClient::getPort)
         .def("getIP", (string(ofxTCPClient::*)(void)) &ofxTCPClient::getIP)
         .def("setup", (bool(ofxTCPClient::*)(int,bool)) &ofxTCPClient::setup)
         .def_readonly("TCPClient", &ofxTCPClient::TCPClient),
         
         ///////////////////////////////
         // ofxUDPManager
         class_<ofxUDPManager>("ofxUDPManager")
         .def(constructor<>())
         .def("Close", (bool(ofxUDPManager::*)(void)) &ofxUDPManager::Close)
         .def("Create", (bool(ofxUDPManager::*)(void)) &ofxUDPManager::Create)
         .def("Connect", (bool(ofxUDPManager::*)(const char*,unsigned short)) &ofxUDPManager::Connect)
         .def("ConnectMcast", (bool(ofxUDPManager::*)(const char*,unsigned short)) &ofxUDPManager::ConnectMcast)
         .def("Bind", (bool(ofxUDPManager::*)(unsigned short)) &ofxUDPManager::Bind)
         .def("BindMcast", (bool(ofxUDPManager::*)(const char*,unsigned short)) &ofxUDPManager::BindMcast)
         .def("Send", (int(ofxUDPManager::*)(const char*,const int)) &ofxUDPManager::Send)
         .def("SendAll", (int(ofxUDPManager::*)(const char*,const int)) &ofxUDPManager::SendAll)
         .def("Receive", (int(ofxUDPManager::*)(const char*,const int)) &ofxUDPManager::Receive)
         .def("SetTimeoutSend", (void(ofxUDPManager::*)(int)) &ofxUDPManager::SetTimeoutSend)
         .def("SetTimeoutReceive", (void(ofxUDPManager::*)(int)) &ofxUDPManager::SetTimeoutReceive)
         .def("GetTimeoutSend", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetTimeoutSend)
         .def("GetTimeoutReceive", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetTimeoutReceive)
         .def("GetRemoteAddr", (bool(ofxUDPManager::*)(const char*)) &ofxUDPManager::GetRemoteAddr)
         .def("SetReceiveBufferSize", (bool(ofxUDPManager::*)(int)) &ofxUDPManager::SetReceiveBufferSize)
         .def("SetSendBufferSize", (bool(ofxUDPManager::*)(int)) &ofxUDPManager::SetSendBufferSize)
         .def("GetReceiveBufferSize", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetReceiveBufferSize)
         .def("GetSendBufferSize", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetSendBufferSize)
         .def("SetReuseAddress", (bool(ofxUDPManager::*)(bool)) &ofxUDPManager::SetReuseAddress)
         .def("SetEnableBroadcast", (bool(ofxUDPManager::*)(bool)) &ofxUDPManager::SetEnableBroadcast)
         .def("SetNonBlocking", (bool(ofxUDPManager::*)(bool)) &ofxUDPManager::SetNonBlocking)
         .def("GetMaxMsgSize", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetMaxMsgSize)
         .def("GetTTL", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetTTL)
         .def("SetTTL", (bool(ofxUDPManager::*)(int)) &ofxUDPManager::SetTTL),
         
         ///////////////////////////////
         // ofxTCPManager
         class_<ofxTCPManager>("ofxTCPManager")
         .def(constructor<>())
         .def("Close", (bool(ofxTCPManager::*)(void)) &ofxTCPManager::Close)
         .def("Create", (bool(ofxTCPManager::*)(void)) &ofxTCPManager::Create)
         .def("Listen", (bool(ofxTCPManager::*)(int)) &ofxTCPManager::Listen)
         .def("Connect", (bool(ofxTCPManager::*)(const char*,unsigned short)) &ofxTCPManager::Connect)
         .def("Bind", (bool(ofxTCPManager::*)(unsigned short)) &ofxTCPManager::Bind)
         .def("Accept", (bool(ofxTCPManager::*)(ofxTCPManager&)) &ofxTCPManager::Accept)
         .def("Send", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::Send)
         .def("SendAll", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::SendAll)
         .def("Receive", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::Receive)
         .def("ReceiveAll", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::ReceiveAll)
         .def("Write", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::Write)
         .def("GetRemoteAddr", &ofxTCPManager::GetRemoteAddr)
         .def("GetInetAddr", &ofxTCPManager::GetInetAddr)
         .def("SetTimeoutSend", (void(ofxTCPManager::*)(int)) &ofxTCPManager::SetTimeoutSend)
         .def("SetTimeoutReceive", (void(ofxTCPManager::*)(int)) &ofxTCPManager::SetTimeoutReceive)
         .def("SetTimeoutAccept", (void(ofxTCPManager::*)(int)) &ofxTCPManager::SetTimeoutAccept)
         .def("GetTimeoutSend", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetTimeoutSend)
         .def("GetTimeoutReceive", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetTimeoutReceive)
         .def("GetTimeoutAccept", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetTimeoutAccept)
         .def("SetReceiveBufferSize", (bool(ofxTCPManager::*)(int)) &ofxTCPManager::SetReceiveBufferSize)
         .def("SetSendBufferSize", (bool(ofxTCPManager::*)(int)) &ofxTCPManager::SetSendBufferSize)
         .def("GetReceiveBufferSize", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetReceiveBufferSize)
         .def("GetSendBufferSize", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetSendBufferSize)
         .def("GetMaxConnections", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetMaxConnections)
         .def("SetNonBlocking", (bool(ofxTCPManager::*)(bool)) &ofxTCPManager::SetNonBlocking)
         .def("CheckHost", (bool(ofxTCPManager::*)(const char*)) &ofxTCPManager::CheckHost)
         .def("CleanUp", (void(ofxTCPManager::*)(void)) &ofxTCPManager::CleanUp),
         
         ///////////////////////////////
         // ofxTCPServer
         class_<ofxTCPServer>("ofxTCPServer")
         .def(constructor<>())
         .def("setVerbose", (void(ofxTCPServer::*)(bool)) &ofxTCPServer::setVerbose)
         .def("setup", (bool(ofxTCPServer::*)(int,bool)) &ofxTCPServer::setup)
         .def("setMessageDelimiter", (void(ofxTCPServer::*)(string)) &ofxTCPServer::setMessageDelimiter)
         .def("close", (bool(ofxTCPServer::*)(void)) &ofxTCPServer::close)
         .def("disconnectClient", (bool(ofxTCPServer::*)(int)) &ofxTCPServer::disconnectClient)
         .def("getNumClients", (int(ofxTCPServer::*)(void)) &ofxTCPServer::getNumClients)
         .def("getLastID", (int(ofxTCPServer::*)(void)) &ofxTCPServer::getLastID)
         .def("getPort", (int(ofxTCPServer::*)(void)) &ofxTCPServer::getPort)
         .def("isConnected", (bool(ofxTCPServer::*)(void)) &ofxTCPServer::isConnected)
         .def("getClientPort", (int(ofxTCPServer::*)(int)) &ofxTCPServer::getClientPort)
         .def("getClientIP", (string(ofxTCPServer::*)(int)) &ofxTCPServer::getClientIP)
         .def("isClientSetup", (bool(ofxTCPServer::*)(int)) &ofxTCPServer::isClientSetup)
         .def("isClientConnected", (bool(ofxTCPServer::*)(int)) &ofxTCPServer::isClientConnected)
         .def("send", (bool(ofxTCPServer::*)(int,string)) &ofxTCPServer::send)
         .def("sendToAll", (bool(ofxTCPServer::*)(string)) &ofxTCPServer::sendToAll)
         .def("sendRawBytes", (bool(ofxTCPServer::*)(int, const char*, const int)) &ofxTCPServer::sendRawBytes)
         .def("sendRawBytesToAll", (bool(ofxTCPServer::*)(const char*, const int)) &ofxTCPServer::sendRawBytesToAll)
         .def("getNumReceivedBytes", (int(ofxTCPServer::*)(int)) &ofxTCPServer::getNumReceivedBytes)
         .def("receive", (string(ofxTCPServer::*)(int)) &ofxTCPServer::receive)
         .def("receiveRawBytes", (void(ofxTCPServer::*)(int, const char*, int)) &ofxTCPServer::receiveRawBytes),
         
         /////////////////////////////////////////////////////////////////////////////////////
         // OFXOPENCV
         
         ///////////////////////////////
         // ofxCvColorImage
         class_<ofxCvColorImage>("ofxCvColorImage")
         .def(constructor<>())
         .def(constructor<const ofxCvColorImage&>())
         
         .def("allocate", (void(ofxCvColorImage::*)(int,int)) &ofxCvColorImage::allocate)
         .def("clear", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::clear)
         .def("getWidth", (float(ofxCvColorImage::*)(void)) &ofxCvColorImage::getWidth)
         .def("getHeight", (float(ofxCvColorImage::*)(void)) &ofxCvColorImage::getHeight)
         .def("setUseTexture", (void(ofxCvColorImage::*)(bool)) &ofxCvColorImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofxCvColorImage::*)(void)) &ofxCvColorImage::getTextureReference)
         .def("flagImageChanged", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::flagImageChanged)
         .def("setROI", (void(ofxCvColorImage::*)(int,int,int,int)) &ofxCvColorImage::setROI)
         .def("setROI", (void(ofxCvColorImage::*)(const ofRectangle&)) &ofxCvColorImage::setROI)
         .def("getROI", (ofRectangle(ofxCvColorImage::*)(void)) &ofxCvColorImage::getROI)
         .def("resetROI", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::resetROI)
         .def("getIntersectionROI", (ofRectangle(ofxCvColorImage::*)(const ofRectangle&,const ofRectangle&)) &ofxCvColorImage::getIntersectionROI)
         .def("setFromPixels", (void(ofxCvColorImage::*)(const ofPixels&)) &ofxCvColorImage::setFromPixels)
         .def("setRoiFromPixels", (void(ofxCvColorImage::*)(const ofPixels&)) &ofxCvColorImage::setRoiFromPixels)
         .def("updateTexture", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::updateTexture)
         .def("draw", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::draw)
         .def("draw", (void(ofxCvColorImage::*)(float,float,float,float)) &ofxCvColorImage::draw)
         .def("draw", (void(ofxCvColorImage::*)(const ofRectangle&)) &ofxCvColorImage::draw)
         .def("drawROI", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::drawROI)
         .def("drawROI", (void(ofxCvColorImage::*)(float,float,float,float)) &ofxCvColorImage::drawROI)
         .def("setAnchorPercent", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::setAnchorPercent)
         .def("setAnchorPoint", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::setAnchorPoint)
         .def("resetAnchor", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::resetAnchor)
         .def("erode", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::erode)
         .def("dilate", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::dilate)
         .def("blur", (void(ofxCvColorImage::*)(int)) &ofxCvColorImage::blur)
         .def("blurGaussian", (void(ofxCvColorImage::*)(int)) &ofxCvColorImage::blurGaussian)
         .def("invert", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::invert)
         .def("mirror", (void(ofxCvColorImage::*)(bool,bool)) &ofxCvColorImage::mirror)
         .def("translate", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::translate)
         .def("rotate", (void(ofxCvColorImage::*)(float,float,float)) &ofxCvColorImage::rotate)
         .def("scale", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::scale)
         .def("transform", (void(ofxCvColorImage::*)(float,float,float,float,float,float,float)) &ofxCvColorImage::transform)
         .def("undistort", (void(ofxCvColorImage::*)(float,float,float,float,float,float,float,float)) &ofxCvColorImage::undistort)
         .def("warpPerspective", (void(ofxCvColorImage::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofxCvColorImage::warpPerspective)
         .def("warpIntoMe", (void(ofxCvColorImage::*)(ofxCvImage&,const ofPoint,const ofPoint)) &ofxCvColorImage::warpIntoMe)
         .def("countNonZeroInRegion", (void(ofxCvColorImage::*)(int,int,int,int)) &ofxCvColorImage::countNonZeroInRegion)
         
         .def("set", (void(ofxCvColorImage::*)(float)) &ofxCvColorImage::set)
         .def("set", (void(ofxCvColorImage::*)(int,int,int)) &ofxCvColorImage::set)
         .def("setFromGrayscalePlanarImages", (void(ofxCvColorImage::*)(ofxCvGrayscaleImage&,ofxCvGrayscaleImage&,ofxCvGrayscaleImage&)) &ofxCvColorImage::setFromGrayscalePlanarImages)
         .def("convertToGrayscalePlanarImages", (void(ofxCvColorImage::*)(ofxCvGrayscaleImage&,ofxCvGrayscaleImage&,ofxCvGrayscaleImage&)) &ofxCvColorImage::convertToGrayscalePlanarImages)
         .def("convertToGrayscalePlanarImages", (void(ofxCvColorImage::*)(ofxCvGrayscaleImage&,int)) &ofxCvColorImage::convertToGrayscalePlanarImages)
         .def("contrastStretch", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::contrastStretch)
         .def("convertToRange", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::convertToRange)
         .def("resize", (void(ofxCvColorImage::*)(int,int)) &ofxCvColorImage::resize)
         .def("scaleIntoMe", &scaleIntoMeColor)
         .def("convertRgbToHsv", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::convertRgbToHsv)
         .def("convertHsvToRgb", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::convertHsvToRgb)
         .def_readonly("width", &ofxCvColorImage::width)
		 .def_readonly("height", &ofxCvColorImage::height)
         .def_readonly("bAllocated", &ofxCvColorImage::bAllocated),
         
         ///////////////////////////////
         // ofxCvContourFinder
         class_<ofxCvContourFinder>("ofxCvContourFinder")
         .def(constructor<>())
         .def("getWidth", (float(ofxCvContourFinder::*)(void)) &ofxCvContourFinder::getWidth)
         .def("getHeight", (float(ofxCvContourFinder::*)(void)) &ofxCvContourFinder::getHeight)
         .def("findContours", &gaFindContours)
         .def("draw", (void(ofxCvContourFinder::*)(void)) &ofxCvContourFinder::draw)
         .def("draw", (void(ofxCvContourFinder::*)(float,float)) &ofxCvContourFinder::draw)
         .def("draw", (void(ofxCvContourFinder::*)(float,float,float,float)) &ofxCvContourFinder::draw)
         .def("draw", (void(ofxCvContourFinder::*)(const ofPoint&)) &ofxCvContourFinder::draw)
         .def("draw", (void(ofxCvContourFinder::*)(const ofRectangle&)) &ofxCvContourFinder::draw)
         .def("setAnchorPercent", (void(ofxCvContourFinder::*)(float,float)) &ofxCvContourFinder::setAnchorPercent)
         .def("setAnchorPoint", (void(ofxCvContourFinder::*)(int,int)) &ofxCvContourFinder::setAnchorPoint)
         .def("resetAnchor", (void(ofxCvContourFinder::*)(void)) &ofxCvContourFinder::resetAnchor),
         
         ///////////////////////////////
         // ofxCvFloatImage
         class_<ofxCvFloatImage>("ofxCvFloatImage")
         .def(constructor<>())
         .def(constructor<const ofxCvFloatImage&>())
         
         .def("allocate", (void(ofxCvFloatImage::*)(int,int)) &ofxCvFloatImage::allocate)
         .def("clear", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::clear)
         .def("getWidth", (float(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getWidth)
         .def("getHeight", (float(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getHeight)
         .def("setUseTexture", (void(ofxCvFloatImage::*)(bool)) &ofxCvFloatImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getTextureReference)
         .def("flagImageChanged", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::flagImageChanged)
         .def("setROI", (void(ofxCvFloatImage::*)(int,int,int,int)) &ofxCvFloatImage::setROI)
         .def("setROI", (void(ofxCvFloatImage::*)(const ofRectangle&)) &ofxCvFloatImage::setROI)
         .def("getROI", (ofRectangle(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getROI)
         .def("resetROI", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::resetROI)
         .def("getIntersectionROI", (ofRectangle(ofxCvFloatImage::*)(const ofRectangle&,const ofRectangle&)) &ofxCvFloatImage::getIntersectionROI)
         .def("setFromPixels", (void(ofxCvFloatImage::*)(const unsigned char*,int,int)) &ofxCvFloatImage::setFromPixels)
         .def("setFromPixels", (void(ofxCvFloatImage::*)(float*,int,int)) &ofxCvFloatImage::setFromPixels)
         .def("setRoiFromPixels", (void(ofxCvFloatImage::*)(const unsigned char*,int,int)) &ofxCvFloatImage::setRoiFromPixels)
         .def("setRoiFromPixels", (void(ofxCvFloatImage::*)(float*,int,int)) &ofxCvFloatImage::setRoiFromPixels)
         .def("updateTexture", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::updateTexture)
         .def("draw", (void(ofxCvFloatImage::*)(float,float)) &ofxCvFloatImage::draw)
         .def("draw", (void(ofxCvFloatImage::*)(float,float,float,float)) &ofxCvFloatImage::draw)
         .def("draw", (void(ofxCvFloatImage::*)(const ofRectangle&)) &ofxCvFloatImage::draw)
         .def("drawROI", (void(ofxCvFloatImage::*)(float,float)) &ofxCvFloatImage::drawROI)
         .def("drawROI", (void(ofxCvFloatImage::*)(float,float,float,float)) &ofxCvFloatImage::drawROI)
         .def("setAnchorPercent", (void(ofxCvFloatImage::*)(float,float)) &ofxCvFloatImage::setAnchorPercent)
         .def("setAnchorPoint", (void(ofxCvFloatImage::*)(float,float)) &ofxCvFloatImage::setAnchorPoint)
         .def("resetAnchor", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::resetAnchor)
         .def("erode", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::erode)
         .def("dilate", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::dilate)
         .def("blur", (void(ofxCvFloatImage::*)(int)) &ofxCvFloatImage::blur)
         .def("blurGaussian", (void(ofxCvFloatImage::*)(int)) &ofxCvFloatImage::blurGaussian)
         .def("invert", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::invert)
         .def("mirror", (void(ofxCvFloatImage::*)(bool,bool)) &ofxCvFloatImage::mirror)
         .def("translate", (void(ofxCvFloatImage::*)(float,float)) &ofxCvFloatImage::translate)
         .def("rotate", (void(ofxCvFloatImage::*)(float,float,float)) &ofxCvFloatImage::rotate)
         .def("scale", (void(ofxCvFloatImage::*)(float,float)) &ofxCvFloatImage::scale)
         .def("transform", (void(ofxCvFloatImage::*)(float,float,float,float,float,float,float)) &ofxCvFloatImage::transform)
         .def("undistort", (void(ofxCvFloatImage::*)(float,float,float,float,float,float,float,float)) &ofxCvFloatImage::undistort)
         .def("warpPerspective", (void(ofxCvFloatImage::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofxCvFloatImage::warpPerspective)
         .def("warpIntoMe", (void(ofxCvFloatImage::*)(ofxCvImage&,const ofPoint,const ofPoint)) &ofxCvFloatImage::warpIntoMe)
         .def("countNonZeroInRegion", (void(ofxCvFloatImage::*)(int,int,int,int)) &ofxCvFloatImage::countNonZeroInRegion)
         
         .def("set", (void(ofxCvFloatImage::*)(float)) &ofxCvFloatImage::set)
         .def("addWeighted", (void(ofxCvFloatImage::*)(ofxCvGrayscaleImage&,float)) &ofxCvFloatImage::addWeighted)
         .def("getPixelsAsFloats", (float*(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getPixelsAsFloats)
         .def("getFloatPixelsRef", (ofFloatPixels&(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getFloatPixelsRef)
         .def("getRoiPixelsAsFloats", (float*(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getRoiPixelsAsFloats)
         .def("getRoiFloatPixelsRef", (ofFloatPixels&(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::getRoiFloatPixelsRef)
         .def("contrastStretch", (void(ofxCvFloatImage::*)(void)) &ofxCvFloatImage::contrastStretch)
         .def("convertToRange", (void(ofxCvFloatImage::*)(float,float)) &ofxCvFloatImage::convertToRange)
         .def("resize", (void(ofxCvFloatImage::*)(int,int)) &ofxCvFloatImage::resize)
         .def("scaleIntoMe", &scaleIntoMeFloat)
         .def_readonly("width", &ofxCvFloatImage::width)
         .def_readonly("height", &ofxCvFloatImage::height)
         .def_readonly("bAllocated", &ofxCvFloatImage::bAllocated),
         
         ///////////////////////////////
         // ofxCvGrayscaleImage
         class_<ofxCvGrayscaleImage>("ofxCvGrayscaleImage")
         .def(constructor<>())
         .def(constructor<const ofxCvGrayscaleImage&>())
         
         .def("allocate", (void(ofxCvGrayscaleImage::*)(int,int)) &ofxCvGrayscaleImage::allocate)
         .def("clear", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::clear)
         .def("getWidth", (float(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getWidth)
         .def("getHeight", (float(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getHeight)
         .def("setUseTexture", (void(ofxCvGrayscaleImage::*)(bool)) &ofxCvGrayscaleImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getTextureReference)
         .def("flagImageChanged", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::flagImageChanged)
         .def("setROI", (void(ofxCvGrayscaleImage::*)(int,int,int,int)) &ofxCvGrayscaleImage::setROI)
         .def("setROI", (void(ofxCvGrayscaleImage::*)(const ofRectangle&)) &ofxCvGrayscaleImage::setROI)
         .def("getROI", (ofRectangle(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getROI)
         .def("resetROI", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::resetROI)
         .def("getIntersectionROI", (ofRectangle(ofxCvGrayscaleImage::*)(const ofRectangle&,const ofRectangle&)) &ofxCvGrayscaleImage::getIntersectionROI)
         .def("setFromPixels", (void(ofxCvGrayscaleImage::*)(const ofPixels&)) &ofxCvGrayscaleImage::setFromPixels)
         .def("setRoiFromPixels", (void(ofxCvGrayscaleImage::*)(const ofPixels&)) &ofxCvGrayscaleImage::setRoiFromPixels)
         .def("updateTexture", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::updateTexture)
         .def("draw", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::draw)
         .def("draw", (void(ofxCvGrayscaleImage::*)(float,float,float,float)) &ofxCvGrayscaleImage::draw)
         .def("draw", (void(ofxCvGrayscaleImage::*)(const ofRectangle&)) &ofxCvGrayscaleImage::draw)
         .def("drawROI", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::drawROI)
         .def("drawROI", (void(ofxCvGrayscaleImage::*)(float,float,float,float)) &ofxCvGrayscaleImage::drawROI)
         .def("setAnchorPercent", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::setAnchorPercent)
         .def("setAnchorPoint", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::setAnchorPoint)
         .def("resetAnchor", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::resetAnchor)
         .def("erode", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::erode)
         .def("dilate", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::dilate)
         .def("blur", (void(ofxCvGrayscaleImage::*)(int)) &ofxCvGrayscaleImage::blur)
         .def("blurGaussian", (void(ofxCvGrayscaleImage::*)(int)) &ofxCvGrayscaleImage::blurGaussian)
         .def("invert", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::invert)
         .def("mirror", (void(ofxCvGrayscaleImage::*)(bool,bool)) &ofxCvGrayscaleImage::mirror)
         .def("translate", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::translate)
         .def("rotate", (void(ofxCvGrayscaleImage::*)(float,float,float)) &ofxCvGrayscaleImage::rotate)
         .def("scale", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::scale)
         .def("transform", (void(ofxCvGrayscaleImage::*)(float,float,float,float,float,float,float)) &ofxCvGrayscaleImage::transform)
         .def("undistort", (void(ofxCvGrayscaleImage::*)(float,float,float,float,float,float,float,float)) &ofxCvGrayscaleImage::undistort)
         .def("warpPerspective", (void(ofxCvGrayscaleImage::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofxCvGrayscaleImage::warpPerspective)
         .def("warpIntoMe", (void(ofxCvGrayscaleImage::*)(ofxCvImage&,const ofPoint,const ofPoint)) &ofxCvGrayscaleImage::warpIntoMe)
         .def("countNonZeroInRegion", (void(ofxCvGrayscaleImage::*)(int,int,int,int)) &ofxCvGrayscaleImage::countNonZeroInRegion)
         
         .def("set", (void(ofxCvGrayscaleImage::*)(float)) &ofxCvGrayscaleImage::set)
         .def("setFromCvColorImage", (void(ofxCvGrayscaleImage::*)(ofxCvColorImage&)) &ofxCvGrayscaleImage::setFromCvColorImage)
         .def("absDiff", (void(ofxCvGrayscaleImage::*)(ofxCvGrayscaleImage&)) &ofxCvGrayscaleImage::absDiff)
         .def("absDiff", (void(ofxCvGrayscaleImage::*)(ofxCvGrayscaleImage&,ofxCvGrayscaleImage&)) &ofxCvGrayscaleImage::absDiff)
         .def("contrastStretch", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::contrastStretch)
         .def("convertToRange", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::convertToRange)
         .def("threshold", (void(ofxCvGrayscaleImage::*)(int,bool)) &ofxCvGrayscaleImage::threshold)
         .def("adaptiveThreshold", (void(ofxCvGrayscaleImage::*)(int,int,bool,bool)) &ofxCvGrayscaleImage::adaptiveThreshold)
         .def("brightnessContrast", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::brightnessContrast)
         .def("resize", (void(ofxCvGrayscaleImage::*)(int,int)) &ofxCvGrayscaleImage::resize)
         .def("scaleIntoMe", &scaleIntoMeGray)
         .def("blurHeavily", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::blurHeavily)
         .def("erode_3x3", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::erode_3x3)
         .def("dilate_3x3", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::dilate_3x3)
         .def("setFromColorImage", (void(ofxCvGrayscaleImage::*)(ofxCvFloatImage&)) &ofxCvGrayscaleImage::setFromColorImage)
         .def_readonly("width", &ofxCvGrayscaleImage::width)
		 .def_readonly("height", &ofxCvGrayscaleImage::height)
         .def_readonly("bAllocated", &ofxCvGrayscaleImage::bAllocated),
         
         ///////////////////////////////
         // ofxCvHaarFinder
         class_<ofxCvHaarFinder>("ofxCvHaarFinder")
         .def(constructor<>())
         .def(constructor<const ofxCvHaarFinder&>())
         
         .def("setup", (void(ofxCvHaarFinder::*)(string)) &ofxCvHaarFinder::setup)
         .def("setScaleHaar", (void(ofxCvHaarFinder::*)(float)) &ofxCvHaarFinder::setScaleHaar)
         .def("setNeighbors", (void(ofxCvHaarFinder::*)(unsigned)) &ofxCvHaarFinder::setNeighbors)
         .def("findHaarObjects", (int(ofxCvHaarFinder::*)(ofImage&,int,int)) &ofxCvHaarFinder::findHaarObjects)
         .def("findHaarObjects", (int(ofxCvHaarFinder::*)(const ofxCvGrayscaleImage&,int,int)) &ofxCvHaarFinder::findHaarObjects)
         .def("findHaarObjects", (int(ofxCvHaarFinder::*)(const ofxCvGrayscaleImage&,ofRectangle&,int,int)) &ofxCvHaarFinder::findHaarObjects)
         .def("findHaarObjects", (int(ofxCvHaarFinder::*)(const ofxCvGrayscaleImage&,int,int,int,int,int,int)) &ofxCvHaarFinder::findHaarObjects)
         .def("getWidth", (float(ofxCvHaarFinder::*)(void)) &ofxCvHaarFinder::getWidth)
         .def("getHeight", (float(ofxCvHaarFinder::*)(void)) &ofxCvHaarFinder::getHeight)
         .def("draw", (void(ofxCvHaarFinder::*)(float,float)) &ofxCvHaarFinder::draw),
         
         ///////////////////////////////
         // ofxCvShortImage
         class_<ofxCvShortImage>("ofxCvShortImage")
         .def(constructor<>())
         .def(constructor<const ofxCvShortImage&>())
         
         .def("allocate", (void(ofxCvShortImage::*)(int,int)) &ofxCvShortImage::allocate)
         .def("clear", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::clear)
         .def("getWidth", (float(ofxCvShortImage::*)(void)) &ofxCvShortImage::getWidth)
         .def("getHeight", (float(ofxCvShortImage::*)(void)) &ofxCvShortImage::getHeight)
         .def("setUseTexture", (void(ofxCvShortImage::*)(bool)) &ofxCvShortImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofxCvShortImage::*)(void)) &ofxCvShortImage::getTextureReference)
         .def("flagImageChanged", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::flagImageChanged)
         .def("setROI", (void(ofxCvShortImage::*)(int,int,int,int)) &ofxCvShortImage::setROI)
         .def("setROI", (void(ofxCvShortImage::*)(const ofRectangle&)) &ofxCvShortImage::setROI)
         .def("getROI", (ofRectangle(ofxCvShortImage::*)(void)) &ofxCvShortImage::getROI)
         .def("resetROI", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::resetROI)
         .def("getIntersectionROI", (ofRectangle(ofxCvShortImage::*)(const ofRectangle&,const ofRectangle&)) &ofxCvShortImage::getIntersectionROI)
         .def("setFromPixels", (void(ofxCvShortImage::*)(const ofPixels&)) &ofxCvShortImage::setFromPixels)
         .def("setRoiFromPixels", (void(ofxCvShortImage::*)(const ofPixels&)) &ofxCvShortImage::setRoiFromPixels)
         .def("updateTexture", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::updateTexture)
         .def("draw", (void(ofxCvShortImage::*)(float,float)) &ofxCvShortImage::draw)
         .def("draw", (void(ofxCvShortImage::*)(float,float,float,float)) &ofxCvShortImage::draw)
         .def("draw", (void(ofxCvShortImage::*)(const ofRectangle&)) &ofxCvShortImage::draw)
         .def("drawROI", (void(ofxCvShortImage::*)(float,float)) &ofxCvShortImage::drawROI)
         .def("drawROI", (void(ofxCvShortImage::*)(float,float,float,float)) &ofxCvShortImage::drawROI)
         .def("setAnchorPercent", (void(ofxCvShortImage::*)(float,float)) &ofxCvShortImage::setAnchorPercent)
         .def("setAnchorPoint", (void(ofxCvShortImage::*)(float,float)) &ofxCvShortImage::setAnchorPoint)
         .def("resetAnchor", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::resetAnchor)
         .def("erode", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::erode)
         .def("dilate", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::dilate)
         .def("blur", (void(ofxCvShortImage::*)(int)) &ofxCvShortImage::blur)
         .def("blurGaussian", (void(ofxCvShortImage::*)(int)) &ofxCvShortImage::blurGaussian)
         .def("invert", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::invert)
         .def("mirror", (void(ofxCvShortImage::*)(bool,bool)) &ofxCvShortImage::mirror)
         .def("translate", (void(ofxCvShortImage::*)(float,float)) &ofxCvShortImage::translate)
         .def("rotate", (void(ofxCvShortImage::*)(float,float,float)) &ofxCvShortImage::rotate)
         .def("scale", (void(ofxCvShortImage::*)(float,float)) &ofxCvShortImage::scale)
         .def("transform", (void(ofxCvShortImage::*)(float,float,float,float,float,float,float)) &ofxCvShortImage::transform)
         .def("undistort", (void(ofxCvShortImage::*)(float,float,float,float,float,float,float,float)) &ofxCvShortImage::undistort)
         .def("warpPerspective", (void(ofxCvShortImage::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofxCvShortImage::warpPerspective)
         .def("warpIntoMe", (void(ofxCvShortImage::*)(ofxCvImage&,const ofPoint,const ofPoint)) &ofxCvShortImage::warpIntoMe)
         .def("countNonZeroInRegion", (void(ofxCvShortImage::*)(int,int,int,int)) &ofxCvShortImage::countNonZeroInRegion)
         
         .def("set", (void(ofxCvShortImage::*)(float)) &ofxCvShortImage::set)
         .def("addWeighted", (void(ofxCvShortImage::*)(ofxCvGrayscaleImage&,float)) &ofxCvShortImage::addWeighted)
         .def("getShortPixelsRef", (ofShortPixels&(ofxCvShortImage::*)(void)) &ofxCvShortImage::getShortPixelsRef)
         .def("getRoiShortPixelsRef", (ofShortPixels&(ofxCvShortImage::*)(void)) &ofxCvShortImage::getRoiShortPixelsRef)
         .def("contrastStretch", (void(ofxCvShortImage::*)(void)) &ofxCvShortImage::contrastStretch)
         .def("convertToRange", (void(ofxCvShortImage::*)(float,float)) &ofxCvShortImage::convertToRange)
         .def("resize", (void(ofxCvShortImage::*)(int,int)) &ofxCvShortImage::resize)
         .def("scaleIntoMe", &scaleIntoMeShort)
         .def_readonly("width", &ofxCvShortImage::width)
         .def_readonly("height", &ofxCvShortImage::height)
         .def_readonly("bAllocated", &ofxCvShortImage::bAllocated),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXSVG
         class_<ofxSVG>("ofxSVG")
         .def(constructor<>())
         .def("getWidth", (float(ofxSVG::*)(void)) &ofxSVG::getWidth)
         .def("getHeight", (float(ofxSVG::*)(void)) &ofxSVG::getHeight)
         .def("load", (void(ofxSVG::*)(string)) &ofxSVG::load)
         .def("draw", (void(ofxSVG::*)(void)) &ofxSVG::draw)
         .def("getNumPath", (int(ofxSVG::*)(void)) &ofxSVG::getNumPath)
         .def("getPathAt", (ofPath&(ofxSVG::*)(int)) &ofxSVG::getPathAt),
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXVECTORGRAPHICS
         class_<ofxVectorGraphics>("ofxVectorGraphics")
         .def(constructor<>())
         .def("beginEPS", (void(ofxVectorGraphics::*)(string,int,int,int,int)) &ofxVectorGraphics::beginEPS)
         .def("endEPS", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::endEPS)
         .def("enableDraw", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::enableDraw)
         .def("disableDraw", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::disableDraw)
         .def("enableCenterRect", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::enableCenterRect)
         .def("disableCenterRect", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::disableCenterRect)
         .def("fill", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::fill)
         .def("noFill", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::noFill)
         .def("setLineWidth", (void(ofxVectorGraphics::*)(float)) &ofxVectorGraphics::setLineWidth)
         .def("setColor", (void(ofxVectorGraphics::*)(int,int,int)) &ofxVectorGraphics::setColor)
         .def("setColor", (void(ofxVectorGraphics::*)(int)) &ofxVectorGraphics::setColor)
         .def("changeColor", (void(ofxVectorGraphics::*)(float,float,float)) &ofxVectorGraphics::changeColor)
         .def("rect", (void(ofxVectorGraphics::*)(float,float,float,float)) &ofxVectorGraphics::rect)
         .def("triangle", (void(ofxVectorGraphics::*)(float,float,float,float,float,float)) &ofxVectorGraphics::triangle)
         .def("circle", (void(ofxVectorGraphics::*)(float,float,float)) &ofxVectorGraphics::circle)
         .def("ellipse", (void(ofxVectorGraphics::*)(float,float,float,float)) &ofxVectorGraphics::ellipse)
         .def("line", (void(ofxVectorGraphics::*)(float,float,float,float)) &ofxVectorGraphics::line)
         .def("arc", (void(ofxVectorGraphics::*)(float,float,float,float,float)) &ofxVectorGraphics::arc)
         .def("bezier", (void(ofxVectorGraphics::*)(float,float,float,float,float,float,float,float)) &ofxVectorGraphics::bezier)
         .def("curve", (void(ofxVectorGraphics::*)(float,float,float,float,float,float,float,float)) &ofxVectorGraphics::curve)
         .def("beginShape", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::beginShape)
         .def("polyVertex", (void(ofxVectorGraphics::*)(float,float)) &ofxVectorGraphics::polyVertex)
         .def("bezierVertex", (void(ofxVectorGraphics::*)(float,float,float,float,float,float)) &ofxVectorGraphics::bezierVertex)
         .def("curveVertex", (void(ofxVectorGraphics::*)(float,float)) &ofxVectorGraphics::curveVertex)
         .def("endShape", (void(ofxVectorGraphics::*)(bool)) &ofxVectorGraphics::endShape)
         .def_readonly("creeps", &ofxVectorGraphics::creeps),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXXMLSETTINGS
         class_<ofxXmlSettings>("ofxXmlSettings")
         .def(constructor<>())
         .def(constructor<const string&>())
         .def("setVerbose", (void(ofxXmlSettings::*)(bool)) &ofxXmlSettings::setVerbose)
         .def("loadFile", (bool(ofxXmlSettings::*)(const string&)) &ofxXmlSettings::loadFile)
         .def("saveFile", (bool(ofxXmlSettings::*)(const string&)) &ofxXmlSettings::saveFile)
         .def("saveFile", (bool(ofxXmlSettings::*)(void)) &ofxXmlSettings::saveFile)
         .def("clearTagContents", (void(ofxXmlSettings::*)(const string&,int)) &ofxXmlSettings::clearTagContents)
         .def("removeTag", (void(ofxXmlSettings::*)(const string&,int)) &ofxXmlSettings::removeTag)
         .def("tagExists", (bool(ofxXmlSettings::*)(const string&,int)) &ofxXmlSettings::tagExists)
         .def("clear", (void(ofxXmlSettings::*)(void)) &ofxXmlSettings::clear)
         .def("getValue", (int(ofxXmlSettings::*)(const string&,int,int)) &ofxXmlSettings::getValue)
         .def("getValue", (double(ofxXmlSettings::*)(const string&,double,int)) &ofxXmlSettings::getValue)
         .def("getValue", (string(ofxXmlSettings::*)(const string&,const string&,int)) &ofxXmlSettings::getValue)
         .def("setValue", (int(ofxXmlSettings::*)(const string&,int,int)) &ofxXmlSettings::setValue)
         .def("setValue", (int(ofxXmlSettings::*)(const string&,double,int)) &ofxXmlSettings::setValue)
         .def("setValue", (int(ofxXmlSettings::*)(const string&,const string&,int)) &ofxXmlSettings::setValue)
         .def("pushTag", (bool(ofxXmlSettings::*)(const string&,int)) &ofxXmlSettings::pushTag)
         .def("popTag", (int(ofxXmlSettings::*)(void)) &ofxXmlSettings::popTag)
         .def("getPushLevel", (int(ofxXmlSettings::*)(void)) &ofxXmlSettings::getPushLevel)
         .def("getNumTags", (int(ofxXmlSettings::*)(const string&)) &ofxXmlSettings::getNumTags)
         .def("addValue", (int(ofxXmlSettings::*)(const string&,int)) &ofxXmlSettings::addValue)
         .def("addValue", (int(ofxXmlSettings::*)(const string&,double)) &ofxXmlSettings::addValue)
         .def("addValue", (int(ofxXmlSettings::*)(const string&,const string&)) &ofxXmlSettings::addValue)
         .def("addTag", (int(ofxXmlSettings::*)(const string&)) &ofxXmlSettings::addTag)
         .def("addAttribute", (int(ofxXmlSettings::*)(const string&,const string&,int,int)) &ofxXmlSettings::addAttribute)
         .def("addAttribute", (int(ofxXmlSettings::*)(const string&,const string&,double,int)) &ofxXmlSettings::addAttribute)
         .def("addAttribute", (int(ofxXmlSettings::*)(const string&,const string&,const string&,int)) &ofxXmlSettings::addAttribute)
         .def("removeAttribute", (void(ofxXmlSettings::*)(const string&,const string&,int)) &ofxXmlSettings::removeAttribute)
         .def("clearTagAttributes", (void(ofxXmlSettings::*)(const string&,int)) &ofxXmlSettings::clearTagAttributes)
         .def("getNumAttributes", (int(ofxXmlSettings::*)(const string&,int)) &ofxXmlSettings::getNumAttributes)
         .def("attributeExists", (bool(ofxXmlSettings::*)(const string&,const string&,int)) &ofxXmlSettings::attributeExists)
         .def("getAttribute", (int(ofxXmlSettings::*)(const string&,const string&,int,int)) &ofxXmlSettings::getAttribute)
         .def("getAttribute", (double(ofxXmlSettings::*)(const string&,const string&,double,int)) &ofxXmlSettings::getAttribute)
         .def("getAttribute", (string(ofxXmlSettings::*)(const string&,const string&,const string&,int)) &ofxXmlSettings::getAttribute)
         .def("setAttribute", (int(ofxXmlSettings::*)(const string&,const string&,int,int)) &ofxXmlSettings::setAttribute)
         .def("setAttribute", (int(ofxXmlSettings::*)(const string&,const string&,double,int)) &ofxXmlSettings::setAttribute)
         .def("setAttribute", (int(ofxXmlSettings::*)(const string&,const string&,const string&,int)) &ofxXmlSettings::setAttribute)
         .def("loadFromBuffer", (bool(ofxXmlSettings::*)(string)) &ofxXmlSettings::loadFromBuffer)
         .def("copyXmlToString", (void(ofxXmlSettings::*)(string&)) &ofxXmlSettings::copyXmlToString),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXARCTEXT --> extending ofTrueTypeFont
         class_<ofxArcText>("ofxArcText")
         .def(constructor<>())
         .def(constructor<bool>())
         
         .def("loadFont", &loadArcFont2)
		 .def("loadFont", &loadArcFont4)
         .def("stringWidth", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringWidth)
		 .def("stringHeight", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringHeight)
         .def("getStringBoundingBox", (ofRectangle(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::getStringBoundingBox)
         .def("getSize", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSize)
		 .def("getLetterSpacing", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getLetterSpacing)
		 .def("setLetterSpacing", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setLetterSpacing)
		 .def("getSpaceSize", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSpaceSize)
		 .def("setSpaceSize", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setSpaceSize)
		 .def("getNumCharacters", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getNumCharacters)
		 .def("getStringAsPoints", (ofTTFCharacter(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::getStringAsPoints)
         
         .def("drawString", (void(ofxArcText::*)(string,float,float,float)) &ofxArcText::drawString)
         .def("getCharacterWidth", (float(ofxArcText::*)(char)) &ofxArcText::getCharacterWidth),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXBOX2D
         class_<b2World>("b2World")
         .def(constructor<const b2Vec2&,bool>()),
         
         ///////////////////////////////
         // ofxBox2d
         class_<ofxBox2d>("ofxBox2d")
         .def(constructor<>())
         .def("init", (void(ofxBox2d::*)(void)) &ofxBox2d::init)
         .def("setFPS", (void(ofxBox2d::*)(float)) &ofxBox2d::setFPS)
         .def("registerGrabbing", (void(ofxBox2d::*)(void)) &ofxBox2d::registerGrabbing)
         .def("grabShapeDown", (void(ofxBox2d::*)(float,float)) &ofxBox2d::grabShapeDown)
         .def("grabShapeUp", (void(ofxBox2d::*)(float,float)) &ofxBox2d::grabShapeUp)
         .def("grabShapeDragged", (void(ofxBox2d::*)(float,float)) &ofxBox2d::grabShapeDragged)
         .def("getWorld", (b2World*(ofxBox2d::*)(void)) &ofxBox2d::getWorld)
         .def("getBodyCount", (int(ofxBox2d::*)(void)) &ofxBox2d::getBodyCount)
         .def("getJointCount", (int(ofxBox2d::*)(void)) &ofxBox2d::getJointCount)
         .def("enableGrabbing", (void(ofxBox2d::*)(void)) &ofxBox2d::enableGrabbing)
         .def("disableGrabbing", (void(ofxBox2d::*)(void)) &ofxBox2d::disableGrabbing)
         .def("setContactListener", (void(ofxBox2d::*)(ofxBox2dContactListener*)) &ofxBox2d::setContactListener)
         .def("setIterations", (void(ofxBox2d::*)(int,int)) &ofxBox2d::setIterations)
         .def("setGravity", (void(ofxBox2d::*)(float,float)) &ofxBox2d::setGravity)
         .def("setGravity", (void(ofxBox2d::*)(ofPoint)) &ofxBox2d::setGravity)
         .def("setBounds", (void(ofxBox2d::*)(ofPoint,ofPoint)) &ofxBox2d::setBounds)
         .def("createBounds", (void(ofxBox2d::*)(float,float,float,float)) &ofxBox2d::createBounds)
         .def("createBounds", (void(ofxBox2d::*)(ofRectangle&)) &ofxBox2d::createBounds)
         .def("createGround", (void(ofxBox2d::*)(const ofPoint&,const ofPoint&)) &ofxBox2d::createGround)
         .def("createGround", (void(ofxBox2d::*)(float,float,float,float)) &ofxBox2d::createGround)
         .def("checkBounds", (void(ofxBox2d::*)(bool)) &ofxBox2d::checkBounds)
         .def("update", (void(ofxBox2d::*)(void)) &ofxBox2d::update)
         .def("draw", (void(ofxBox2d::*)(void)) &ofxBox2d::draw)
         .def("drawGround", (void(ofxBox2d::*)(void)) &ofxBox2d::drawGround),
         
         ///////////////////////////////
         // ofxBox2dCircle
         class_<ofxBox2dCircle>("ofxBox2dCircle")
         .def(constructor<>())
         // from ofxBox2dBaseShape
         .def("isBody", (bool(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::isBody)
         .def("isFixed", (bool(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::isFixed)
         .def("getWorld", (b2World*(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::getWorld)
         .def("create", (void(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::create)
         .def("setBounce", (void(ofxBox2dCircle::*)(float)) &ofxBox2dCircle::setBounce)
         .def("setDensity", (void(ofxBox2dCircle::*)(float)) &ofxBox2dCircle::setDensity)
         .def("setFriction", (void(ofxBox2dCircle::*)(float)) &ofxBox2dCircle::setFriction)
         .def("setPhysics", (void(ofxBox2dCircle::*)(float,float,float)) &ofxBox2dCircle::setPhysics)
         .def("setData", (void*(ofxBox2dCircle::*)(void*)) &ofxBox2dCircle::setData)
         .def("getData", (void*(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::getData)
         .def("setFilterData", (void(ofxBox2dCircle::*)(b2Filter)) &ofxBox2dCircle::setFilterData)
         .def("enableGravity", (void(ofxBox2dCircle::*)(bool)) &ofxBox2dCircle::enableGravity)
         .def("setFixedRotation", (void(ofxBox2dCircle::*)(bool)) &ofxBox2dCircle::setFixedRotation)
         .def("setRotationFriction", (void(ofxBox2dCircle::*)(float)) &ofxBox2dCircle::setRotationFriction)
         .def("getRotation", (float(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::getRotation)
         .def("getPosition", (ofVec2f(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::getPosition)
         .def("getB2DPosition", (ofVec2f(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::getB2DPosition)
         .def("setVelocity", (void(ofxBox2dCircle::*)(float,float)) &ofxBox2dCircle::setVelocity)
         .def("setVelocity", (void(ofxBox2dCircle::*)(ofVec2f)) &ofxBox2dCircle::setVelocity)
         .def("getVelocity", (ofVec2f(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::getVelocity)
         .def("setDamping", (void(ofxBox2dCircle::*)(float)) &ofxBox2dCircle::setDamping)
         .def("setDamping", (void(ofxBox2dCircle::*)(float,float)) &ofxBox2dCircle::setDamping)
         .def("addForce", (void(ofxBox2dCircle::*)(ofVec2f,float)) &ofxBox2dCircle::addForce)
         .def("addImpulseForce", (void(ofxBox2dCircle::*)(ofVec2f,ofVec2f)) &ofxBox2dCircle::addImpulseForce)
         .def("destroy", (void(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::destroy)
         .def("update", (void(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::update)
         
         .def("setup", (void(ofxBox2dCircle::*)(b2World*,float,float,float)) &ofxBox2dCircle::setup)
         .def("getRadius", (float(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::getRadius)
         .def("setRadius", (void(ofxBox2dCircle::*)(float)) &ofxBox2dCircle::setRadius)
         .def("draw", (void(ofxBox2dCircle::*)(void)) &ofxBox2dCircle::draw)
         .def("addAttractionPoint", (void(ofxBox2dCircle::*)(float,float,float)) &ofxBox2dCircle::addAttractionPoint)
         .def("addAttractionPoint", (void(ofxBox2dCircle::*)(ofVec2f,float)) &ofxBox2dCircle::addAttractionPoint)
         .def("addRepulsionForce", (void(ofxBox2dCircle::*)(float,float,float)) &ofxBox2dCircle::addRepulsionForce)
         .def("addRepulsionForce", (void(ofxBox2dCircle::*)(ofVec2f,float)) &ofxBox2dCircle::addRepulsionForce),
         
         ///////////////////////////////
         // ofxBox2dJoint
         class_<ofxBox2dJoint>("ofxBox2dJoint")
         .def(constructor<>())
         .def(constructor<b2World*,b2Body*,b2Body*,float,float,bool>())
         .def(constructor<b2World*,b2Body*,b2Body*,b2Vec2,b2Vec2,float,float,bool>())
         .def("setWorld", (void(ofxBox2dJoint::*)(b2World*)) &ofxBox2dJoint::setWorld)
         .def("setup", (void(ofxBox2dJoint::*)(b2World*,b2Body*,b2Body*,float,float,bool)) &ofxBox2dJoint::setup)
         .def("setup", (void(ofxBox2dJoint::*)(b2World*,b2Body*,b2Body*,b2Vec2,b2Vec2,float,float,bool)) &ofxBox2dJoint::setup)
         .def("isSetup", (bool(ofxBox2dJoint::*)(void)) &ofxBox2dJoint::isSetup)
         .def("draw", (void(ofxBox2dJoint::*)(void)) &ofxBox2dJoint::draw)
         .def("destroy", (void(ofxBox2dJoint::*)(void)) &ofxBox2dJoint::destroy)
         .def("setLength", (void(ofxBox2dJoint::*)(float)) &ofxBox2dJoint::setLength)
         .def("getLength", (float(ofxBox2dJoint::*)(void)) &ofxBox2dJoint::getLength)
         .def("setFrequency", (void(ofxBox2dJoint::*)(float)) &ofxBox2dJoint::setFrequency)
         .def("getFrequency", (float(ofxBox2dJoint::*)(void)) &ofxBox2dJoint::getFrequency)
         .def("setDamping", (void(ofxBox2dJoint::*)(float)) &ofxBox2dJoint::setDamping)
         .def("getDamping", (float(ofxBox2dJoint::*)(void)) &ofxBox2dJoint::getDamping)
         .def("getReactionForce", (ofVec2f(ofxBox2dJoint::*)(float)) &ofxBox2dJoint::getReactionForce)
         .def("getReactionForceB2D", (b2Vec2(ofxBox2dJoint::*)(float)) &ofxBox2dJoint::getReactionForceB2D)
         .def("getReactionTorque", (float(ofxBox2dJoint::*)(float)) &ofxBox2dJoint::getReactionTorque),
         
         ///////////////////////////////
         // ofxBox2dDistanceJoint
         class_<ofxBox2dDistanceJoint>("ofxBox2dDistanceJoint")
         .def(constructor<>())
         .def("setWorld", (void(ofxBox2dDistanceJoint::*)(b2World*)) &ofxBox2dDistanceJoint::setWorld)
         .def("isAlive", (bool(ofxBox2dDistanceJoint::*)(void)) &ofxBox2dDistanceJoint::isAlive)
         .def("destroy", (void(ofxBox2dDistanceJoint::*)(void)) &ofxBox2dDistanceJoint::destroy)
         
         .def("setup", (void(ofxBox2dDistanceJoint::*)(b2World*,b2Body*,b2Body*,float,float,float,bool)) &ofxBox2dDistanceJoint::setup)
         .def("setup", (void(ofxBox2dDistanceJoint::*)(b2World*,b2Body*,b2Body*,float,float,bool)) &ofxBox2dDistanceJoint::setup)
         .def("setup", (void(ofxBox2dDistanceJoint::*)(b2World*,b2Body*,b2Body*,b2Vec2,b2Vec2,float,float,float,bool)) &ofxBox2dDistanceJoint::setup)
         .def("setup", (void(ofxBox2dDistanceJoint::*)(b2World*,b2Body*,b2Body*,b2Vec2,b2Vec2,float,float,bool)) &ofxBox2dDistanceJoint::setup)
         .def("setLength", (void(ofxBox2dDistanceJoint::*)(float)) &ofxBox2dDistanceJoint::setLength)
         .def("getLength", (float(ofxBox2dDistanceJoint::*)(void)) &ofxBox2dDistanceJoint::getLength)
         .def("setFrequency", (void(ofxBox2dDistanceJoint::*)(float)) &ofxBox2dDistanceJoint::setFrequency)
         .def("getFrequency", (float(ofxBox2dDistanceJoint::*)(void)) &ofxBox2dDistanceJoint::getFrequency)
         .def("setDamping", (void(ofxBox2dDistanceJoint::*)(float)) &ofxBox2dDistanceJoint::setDamping)
         .def("getDamping", (float(ofxBox2dDistanceJoint::*)(void)) &ofxBox2dDistanceJoint::getDamping)
         .def("getReactionForce", (ofVec2f(ofxBox2dDistanceJoint::*)(float)) &ofxBox2dDistanceJoint::getReactionForce)
         .def("getReactionForceB2D", (b2Vec2(ofxBox2dDistanceJoint::*)(float)) &ofxBox2dDistanceJoint::getReactionForceB2D)
         .def("getReactionTorque", (float(ofxBox2dDistanceJoint::*)(float)) &ofxBox2dDistanceJoint::getReactionTorque),
         
         ///////////////////////////////
         // ofxBox2dGearJoint
         class_<ofxBox2dGearJoint>("ofxBox2dGearJoint")
         .def(constructor<>())
         .def("setWorld", (void(ofxBox2dGearJoint::*)(b2World*)) &ofxBox2dGearJoint::setWorld)
         .def("isAlive", (bool(ofxBox2dGearJoint::*)(void)) &ofxBox2dGearJoint::isAlive)
         .def("destroy", (void(ofxBox2dGearJoint::*)(void)) &ofxBox2dGearJoint::destroy)
         
         .def("setup", (void(ofxBox2dGearJoint::*)(b2World*,ofxBox2dRevoluteJoint*,ofxBox2dPrismaticJoint*,float,bool)) &ofxBox2dGearJoint::setup)
         .def("setRatio", (void(ofxBox2dGearJoint::*)(float)) &ofxBox2dGearJoint::setRatio)
         .def("getRatio", (float(ofxBox2dGearJoint::*)(void)) &ofxBox2dGearJoint::getRatio)
         .def("getReactionForce", (ofVec2f(ofxBox2dGearJoint::*)(float)) &ofxBox2dGearJoint::getReactionForce)
         .def("getReactionForceB2D", (b2Vec2(ofxBox2dGearJoint::*)(float)) &ofxBox2dGearJoint::getReactionForceB2D)
         .def("getReactionTorque", (float(ofxBox2dGearJoint::*)(float)) &ofxBox2dGearJoint::getReactionTorque),
         
         ///////////////////////////////
         // ofxBox2dPrismaticJoint
         class_<ofxBox2dPrismaticJoint>("ofxBox2dPrismaticJoint")
         .def(constructor<>())
         .def("setWorld", (void(ofxBox2dPrismaticJoint::*)(b2World*)) &ofxBox2dPrismaticJoint::setWorld)
         .def("isAlive", (bool(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::isAlive)
         .def("destroy", (void(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::destroy)
         
         //.def("setup", (void(ofxBox2dPrismaticJoint::*)(b2World*,b2Body*,b2Body*,b2Vec2,b2Vec2,float,float,float,bool,float,float,bool,bool)) &ofxBox2dPrismaticJoint::setup)
         .def("getJoint", (b2PrismaticJoint*(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::getJoint)
         .def("getLowerLimit", (float(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::getLowerLimit)
         .def("getUpperLimit", (float(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::getUpperLimit)
         .def("setLimits", (void(ofxBox2dPrismaticJoint::*)(float,float)) &ofxBox2dPrismaticJoint::setLimits)
         .def("setEnableLimit", (void(ofxBox2dPrismaticJoint::*)(bool)) &ofxBox2dPrismaticJoint::setEnableLimit)
         .def("isLimitEnabled", (bool(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::isLimitEnabled)
         .def("isMotorEnabled", (bool(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::isMotorEnabled)
         .def("setEnableMotor", (void(ofxBox2dPrismaticJoint::*)(bool)) &ofxBox2dPrismaticJoint::setEnableMotor)
         .def("setMotorSpeed", (void(ofxBox2dPrismaticJoint::*)(float)) &ofxBox2dPrismaticJoint::setMotorSpeed)
         .def("getMotorSpeed", (float(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::getMotorSpeed)
         .def("setMaxMotorForce", (void(ofxBox2dPrismaticJoint::*)(float)) &ofxBox2dPrismaticJoint::setMaxMotorForce)
         .def("getMotorForce", (float(ofxBox2dPrismaticJoint::*)(void)) &ofxBox2dPrismaticJoint::getMotorForce)
         .def("getReactionForce", (ofVec2f(ofxBox2dPrismaticJoint::*)(float)) &ofxBox2dPrismaticJoint::getReactionForce)
         .def("getReactionForceB2D", (b2Vec2(ofxBox2dPrismaticJoint::*)(float)) &ofxBox2dPrismaticJoint::getReactionForceB2D)
         .def("getReactionTorque", (float(ofxBox2dPrismaticJoint::*)(float)) &ofxBox2dPrismaticJoint::getReactionTorque),
         
         ///////////////////////////////
         // ofxBox2dPulleyJoint
         class_<ofxBox2dPulleyJoint>("ofxBox2dPulleyJoint")
         .def(constructor<>())
         .def("setWorld", (void(ofxBox2dPulleyJoint::*)(b2World*)) &ofxBox2dPulleyJoint::setWorld)
         .def("isAlive", (bool(ofxBox2dPulleyJoint::*)(void)) &ofxBox2dPulleyJoint::isAlive)
         .def("destroy", (void(ofxBox2dPulleyJoint::*)(void)) &ofxBox2dPulleyJoint::destroy)
         
         .def("setup", (void(ofxBox2dPulleyJoint::*)(b2World*,b2Body*,b2Body*,const b2Vec2&,const b2Vec2&,const b2Vec2&,const b2Vec2&,float,bool)) &ofxBox2dPulleyJoint::setup)
         .def("getLength1", (float(ofxBox2dPulleyJoint::*)(void)) &ofxBox2dPulleyJoint::getLength1)
         .def("getLength2", (float(ofxBox2dPulleyJoint::*)(void)) &ofxBox2dPulleyJoint::getLength2)
         .def("getRatio", (float(ofxBox2dPulleyJoint::*)(void)) &ofxBox2dPulleyJoint::getRatio)
         .def("getReactionForce", (ofVec2f(ofxBox2dPulleyJoint::*)(float)) &ofxBox2dPulleyJoint::getReactionForce)
         .def("getReactionForceB2D", (b2Vec2(ofxBox2dPulleyJoint::*)(float)) &ofxBox2dPulleyJoint::getReactionForceB2D)
         .def("getReactionTorque", (float(ofxBox2dPulleyJoint::*)(float)) &ofxBox2dPulleyJoint::getReactionTorque),
         
         ///////////////////////////////
         // ofxBox2dRevoluteJoint
         class_<ofxBox2dRevoluteJoint>("ofxBox2dRevoluteJoint")
         .def(constructor<>())
         .def("setWorld", (void(ofxBox2dRevoluteJoint::*)(b2World*)) &ofxBox2dRevoluteJoint::setWorld)
         .def("isAlive", (bool(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::isAlive)
         .def("destroy", (void(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::destroy)
         
         //.def("setup", (void(ofxBox2dRevoluteJoint::*)(b2World*,b2Body*,b2Body*,b2Vec2,float,float,float,bool,float,float,bool,bool)) &ofxBox2dRevoluteJoint::setup)
         //.def("setup", (void(ofxBox2dRevoluteJoint::*)(b2World*,b2Body*,b2Body*,b2Vec2,float,float,bool,float,float,bool,bool)) &ofxBox2dRevoluteJoint::setup)
         .def("getJoint", (b2RevoluteJoint*(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::getJoint)
         .def("getLowerLimit", (float(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::getLowerLimit)
         .def("getUpperLimit", (float(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::getUpperLimit)
         .def("getAngle", (float(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::getAngle)
         .def("setLimits", (void(ofxBox2dRevoluteJoint::*)(float,float)) &ofxBox2dRevoluteJoint::setLimits)
         .def("setEnableLimit", (void(ofxBox2dRevoluteJoint::*)(bool)) &ofxBox2dRevoluteJoint::setEnableLimit)
         .def("isLimitEnabled", (bool(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::isLimitEnabled)
         .def("isMotorEnabled", (bool(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::isMotorEnabled)
         .def("setEnableMotor", (void(ofxBox2dRevoluteJoint::*)(bool)) &ofxBox2dRevoluteJoint::setEnableMotor)
         .def("setMotorSpeed", (void(ofxBox2dRevoluteJoint::*)(float)) &ofxBox2dRevoluteJoint::setMotorSpeed)
         .def("getMotorSpeed", (float(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::getMotorSpeed)
         .def("setMaxMotorTorque", (void(ofxBox2dRevoluteJoint::*)(float)) &ofxBox2dRevoluteJoint::setMaxMotorTorque)
         .def("getMotorTorque", (float(ofxBox2dRevoluteJoint::*)(void)) &ofxBox2dRevoluteJoint::getMotorTorque)
         .def("getReactionForce", (ofVec2f(ofxBox2dRevoluteJoint::*)(float)) &ofxBox2dRevoluteJoint::getReactionForce)
         .def("getReactionForceB2D", (b2Vec2(ofxBox2dRevoluteJoint::*)(float)) &ofxBox2dRevoluteJoint::getReactionForceB2D)
         .def("getReactionTorque", (float(ofxBox2dRevoluteJoint::*)(float)) &ofxBox2dRevoluteJoint::getReactionTorque),
         
         ///////////////////////////////
         // ofxBox2dWeldJoint
         class_<ofxBox2dWeldJoint>("ofxBox2dWeldJoint")
         .def(constructor<>())
         .def("setWorld", (void(ofxBox2dWeldJoint::*)(b2World*)) &ofxBox2dWeldJoint::setWorld)
         .def("isAlive", (bool(ofxBox2dWeldJoint::*)(void)) &ofxBox2dWeldJoint::isAlive)
         .def("destroy", (void(ofxBox2dWeldJoint::*)(void)) &ofxBox2dWeldJoint::destroy)
         
         .def("setup", (void(ofxBox2dWeldJoint::*)(b2World*,b2Body*,b2Body*,const b2Vec2&,float,bool)) &ofxBox2dWeldJoint::setup)
         .def("setup", (void(ofxBox2dWeldJoint::*)(b2World*,b2Body*,b2Body*,const b2Vec2&,bool)) &ofxBox2dWeldJoint::setup)
         .def("getReactionForce", (ofVec2f(ofxBox2dWeldJoint::*)(float)) &ofxBox2dWeldJoint::getReactionForce)
         .def("getReactionForceB2D", (b2Vec2(ofxBox2dWeldJoint::*)(float)) &ofxBox2dWeldJoint::getReactionForceB2D)
         .def("getReactionTorque", (float(ofxBox2dWeldJoint::*)(float)) &ofxBox2dWeldJoint::getReactionTorque),
         
         ///////////////////////////////
         // ofxBox2dPolygon
         class_<ofxBox2dPolygon>("ofxBox2dPolygon")
         .def(constructor<>())
         // from ofPolyline
         .def("clear", (void(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::clear)
         .def("addVertex", (void(ofxBox2dPolygon::*)(float,float,float)) &ofxBox2dPolygon::addVertex)
         .def("lineTo", (void(ofxBox2dPolygon::*)(const ofPoint&)) &ofxBox2dPolygon::lineTo)
         .def("lineTo", (void(ofxBox2dPolygon::*)(float,float,float)) &ofxBox2dPolygon::lineTo)
         .def("arc", (void(ofxBox2dPolygon::*)(const ofPoint&,float,float,float,float,int)) &ofxBox2dPolygon::arc)
         .def("arc", (void(ofxBox2dPolygon::*)(float,float,float,float,float,float,int)) &ofxBox2dPolygon::arc)
         .def("arc", (void(ofxBox2dPolygon::*)(float,float,float,float,float,float,float,int)) &ofxBox2dPolygon::arc)
         .def("curveTo", (void(ofxBox2dPolygon::*)(const ofPoint&,int)) &ofxBox2dPolygon::curveTo)
         .def("curveTo", (void(ofxBox2dPolygon::*)(float,float,float,int)) &ofxBox2dPolygon::curveTo)
         .def("bezierTo", (void(ofxBox2dPolygon::*)(const ofPoint&,const ofPoint&,const ofPoint&,int)) &ofxBox2dPolygon::bezierTo)
         .def("bezierTo", (void(ofxBox2dPolygon::*)(float,float,float,float,float,float,int)) &ofxBox2dPolygon::bezierTo)
         .def("bezierTo", (void(ofxBox2dPolygon::*)(float,float,float,float,float,float,float,float,float,int)) &ofxBox2dPolygon::bezierTo)
         .def("quadBezierTo", (void(ofxBox2dPolygon::*)(const ofPoint&,const ofPoint&,const ofPoint&,int)) &ofxBox2dPolygon::quadBezierTo)
         .def("quadBezierTo", (void(ofxBox2dPolygon::*)(float,float,float,float,float,float,int)) &ofxBox2dPolygon::quadBezierTo)
         .def("quadBezierTo", (void(ofxBox2dPolygon::*)(float,float,float,float,float,float,float,float,float,int)) &ofxBox2dPolygon::quadBezierTo)
         .def("getSmoothed", (ofxBox2dPolygon(ofxBox2dPolygon::*)(int,float)) &ofxBox2dPolygon::getSmoothed)
         .def("getResampledBySpacing", (ofxBox2dPolygon(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::getResampledBySpacing)
         .def("getResampledByCount", (ofxBox2dPolygon(ofxBox2dPolygon::*)(int)) &ofxBox2dPolygon::getResampledByCount)
         .def("getBoundingBox", (ofRectangle(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getBoundingBox)
         .def("getClosestPoint", (ofPoint(ofxBox2dPolygon::*)(const ofPoint&,unsigned int*)) &ofxBox2dPolygon::getClosestPoint)
         .def("simplify", (void(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::simplify)
         .def("size", (size_t(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::size)
         .def("resize", (void(ofxBox2dPolygon::*)(size_t)) &ofxBox2dPolygon::resize)
         .def("setClosed", (void(ofxBox2dPolygon::*)(bool)) &ofxBox2dPolygon::setClosed)
         .def("isClosed", (bool(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::isClosed)
         .def("close", (void(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::close)
         .def("hasChanged", (bool(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::hasChanged)
         .def("getVertices", (ofPoint(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getVertices)
         .def("getPerimeter", (float(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getPerimeter)
         // from ofxBox2dBaseShape
         .def("isBody", (bool(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::isBody)
         .def("isFixed", (bool(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::isFixed)
         .def("getWorld", (b2World*(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getWorld)
         .def("create", (void(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::create)
         .def("setBounce", (void(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::setBounce)
         .def("setDensity", (void(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::setDensity)
         .def("setFriction", (void(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::setFriction)
         .def("setPhysics", (void(ofxBox2dPolygon::*)(float,float,float)) &ofxBox2dPolygon::setPhysics)
         .def("setData", (void*(ofxBox2dPolygon::*)(void*)) &ofxBox2dPolygon::setData)
         .def("getData", (void*(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getData)
         .def("setFilterData", (void(ofxBox2dPolygon::*)(b2Filter)) &ofxBox2dPolygon::setFilterData)
         .def("enableGravity", (void(ofxBox2dPolygon::*)(bool)) &ofxBox2dPolygon::enableGravity)
         .def("setFixedRotation", (void(ofxBox2dPolygon::*)(bool)) &ofxBox2dPolygon::setFixedRotation)
         .def("setRotationFriction", (void(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::setRotationFriction)
         .def("getRotation", (float(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getRotation)
         .def("getPosition", (ofVec2f(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getPosition)
         .def("getB2DPosition", (ofVec2f(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getB2DPosition)
         .def("setVelocity", (void(ofxBox2dPolygon::*)(float,float)) &ofxBox2dPolygon::setVelocity)
         .def("setVelocity", (void(ofxBox2dPolygon::*)(ofVec2f)) &ofxBox2dPolygon::setVelocity)
         .def("getVelocity", (ofVec2f(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getVelocity)
         .def("setDamping", (void(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::setDamping)
         .def("setDamping", (void(ofxBox2dPolygon::*)(float,float)) &ofxBox2dPolygon::setDamping)
         .def("addForce", (void(ofxBox2dPolygon::*)(ofVec2f,float)) &ofxBox2dPolygon::addForce)
         .def("addImpulseForce", (void(ofxBox2dPolygon::*)(ofVec2f,ofVec2f)) &ofxBox2dPolygon::addImpulseForce)
         .def("destroy", (void(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::destroy)
         .def("update", (void(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::update)
         
         .def("setup", (void(ofxBox2dPolygon::*)(b2World*)) &ofxBox2dPolygon::setup)
         .def("addTriangle", (void(ofxBox2dPolygon::*)(const ofVec2f&,const ofVec2f&,const ofVec2f&)) &ofxBox2dPolygon::addTriangle)
         .def("addVertexes", (void(ofxBox2dPolygon::*)(ofPolyline&)) &ofxBox2dPolygon::addVertexes)
         .def("simplify", (void(ofxBox2dPolygon::*)(float)) &ofxBox2dPolygon::simplify)
         .def("triangulate", (void(ofxBox2dPolygon::*)(float,int)) &ofxBox2dPolygon::triangulate)
         .def("getCenter", (ofVec2f(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getCenter)
         .def("getArea", (float(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::getArea)
         .def("isGoodShape", (bool(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::isGoodShape)
         .def("setAsEdge", (void(ofxBox2dPolygon::*)(bool)) &ofxBox2dPolygon::setAsEdge)
         .def("addAttractionPoint", (void(ofxBox2dPolygon::*)(ofVec2f,float)) &ofxBox2dPolygon::addAttractionPoint)
         .def("addAttractionPoint", (void(ofxBox2dPolygon::*)(float,float,float)) &ofxBox2dPolygon::addAttractionPoint)
         .def("addRepulsionForce", (void(ofxBox2dPolygon::*)(ofVec2f,float)) &ofxBox2dPolygon::addRepulsionForce)
         .def("addRepulsionForce", (void(ofxBox2dPolygon::*)(float,float,float)) &ofxBox2dPolygon::addRepulsionForce)
         .def("updateShape", (void(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::updateShape)
         .def("create", (void(ofxBox2dPolygon::*)(b2World*)) &ofxBox2dPolygon::create)
         .def("draw", (void(ofxBox2dPolygon::*)(void)) &ofxBox2dPolygon::draw),
         
         ///////////////////////////////
         // ofxBox2dRect
         class_<ofxBox2dRect>("ofxBox2dRect")
         .def(constructor<>())
         // from ofxBox2dBaseShape
         .def("isBody", (bool(ofxBox2dRect::*)(void)) &ofxBox2dRect::isBody)
         .def("isFixed", (bool(ofxBox2dRect::*)(void)) &ofxBox2dRect::isFixed)
         .def("getWorld", (b2World*(ofxBox2dRect::*)(void)) &ofxBox2dRect::getWorld)
         .def("create", (void(ofxBox2dRect::*)(void)) &ofxBox2dRect::create)
         .def("setBounce", (void(ofxBox2dRect::*)(float)) &ofxBox2dRect::setBounce)
         .def("setDensity", (void(ofxBox2dRect::*)(float)) &ofxBox2dRect::setDensity)
         .def("setFriction", (void(ofxBox2dRect::*)(float)) &ofxBox2dRect::setFriction)
         .def("setPhysics", (void(ofxBox2dRect::*)(float,float,float)) &ofxBox2dRect::setPhysics)
         .def("setData", (void*(ofxBox2dRect::*)(void*)) &ofxBox2dRect::setData)
         .def("getData", (void*(ofxBox2dRect::*)(void)) &ofxBox2dRect::getData)
         .def("setFilterData", (void(ofxBox2dRect::*)(b2Filter)) &ofxBox2dRect::setFilterData)
         .def("enableGravity", (void(ofxBox2dRect::*)(bool)) &ofxBox2dRect::enableGravity)
         .def("setFixedRotation", (void(ofxBox2dRect::*)(bool)) &ofxBox2dRect::setFixedRotation)
         .def("setRotationFriction", (void(ofxBox2dRect::*)(float)) &ofxBox2dRect::setRotationFriction)
         .def("getRotation", (float(ofxBox2dRect::*)(void)) &ofxBox2dRect::getRotation)
         .def("getPosition", (ofVec2f(ofxBox2dRect::*)(void)) &ofxBox2dRect::getPosition)
         .def("getB2DPosition", (ofVec2f(ofxBox2dRect::*)(void)) &ofxBox2dRect::getB2DPosition)
         .def("setVelocity", (void(ofxBox2dRect::*)(float,float)) &ofxBox2dRect::setVelocity)
         .def("setVelocity", (void(ofxBox2dRect::*)(ofVec2f)) &ofxBox2dRect::setVelocity)
         .def("getVelocity", (ofVec2f(ofxBox2dRect::*)(void)) &ofxBox2dRect::getVelocity)
         .def("setDamping", (void(ofxBox2dRect::*)(float)) &ofxBox2dRect::setDamping)
         .def("setDamping", (void(ofxBox2dRect::*)(float,float)) &ofxBox2dRect::setDamping)
         .def("addForce", (void(ofxBox2dRect::*)(ofVec2f,float)) &ofxBox2dRect::addForce)
         .def("addImpulseForce", (void(ofxBox2dRect::*)(ofVec2f,ofVec2f)) &ofxBox2dRect::addImpulseForce)
         .def("destroy", (void(ofxBox2dRect::*)(void)) &ofxBox2dRect::destroy)
         .def("update", (void(ofxBox2dRect::*)(void)) &ofxBox2dRect::update)
         
         .def("setup", (void(ofxBox2dRect::*)(b2World*,ofRectangle)) &ofxBox2dRect::setup)
         .def("setup", (void(ofxBox2dRect::*)(b2World*,float,float,float,float)) &ofxBox2dRect::setup)
         .def("draw", (void(ofxBox2dRect::*)(void)) &ofxBox2dRect::draw)
         .def("getWidth", (float(ofxBox2dRect::*)(void)) &ofxBox2dRect::getWidth)
         .def("getHeight", (float(ofxBox2dRect::*)(void)) &ofxBox2dRect::getHeight)
         .def("addAttractionPoint", (void(ofxBox2dRect::*)(float,float,float)) &ofxBox2dRect::addAttractionPoint)
         .def("addAttractionPoint", (void(ofxBox2dRect::*)(ofVec2f,float)) &ofxBox2dRect::addAttractionPoint)
         .def("addRepulsionForce", (void(ofxBox2dRect::*)(float,float,float)) &ofxBox2dRect::addRepulsionForce)
         .def("addRepulsionForce", (void(ofxBox2dRect::*)(ofVec2f,float)) &ofxBox2dRect::addRepulsionForce),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXCHROMAKEY --> extending ofImage
         class_<ofxChromaKey>("ofxChromaKey")
         .def(constructor<>())
         .def("setPixels", (void(ofxChromaKey::*)(ofPixelsRef)) &ofxChromaKey::setPixels)
         .def("setPixels", (void(ofxChromaKey::*)(unsigned char*,int,int)) &ofxChromaKey::setPixels)
         .def("learnBgColor", (void(ofxChromaKey::*)(ofPixelsRef)) &ofxChromaKey::learnBgColor)
         .def("setBgColor", (void(ofxChromaKey::*)(ofColor)) &ofxChromaKey::setBgColor)
         .def("getBgColor", (ofColor(ofxChromaKey::*)(void)) &ofxChromaKey::getBgColor)
         .def("setThreshold", (void(ofxChromaKey::*)(float)) &ofxChromaKey::setThreshold)
         .def("drawBgColor", (void(ofxChromaKey::*)(int,int,int,int)) &ofxChromaKey::drawBgColor)
         .def("draw", (void(ofxChromaKey::*)(int,int,int,int,bool)) &ofxChromaKey::draw)
         .def("getThreshold", (float(ofxChromaKey::*)(void)) &ofxChromaKey::getThreshold),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXCLD
         class_<ofxCLD>("ofxCLD")
         .def(constructor<>())
         .def("setup", (void(ofxCLD::*)(int,int)) &ofxCLD::setup)
         .def("getCLDTextureRef", (ofTexture&(ofxCLD::*)(ofPixels,int,float,float,float,float)) &ofxCLD::getCLDTextureRef),
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXCRYPTO
         class_<ofxCrypto>("ofxCrypto")
         .def(constructor<>())
         .def("md5", (string(ofxCrypto::*)(string)) &ofxCrypto::md5)
         .def("sha1", (string(ofxCrypto::*)(string)) &ofxCrypto::sha1)
         .def("base64_encode", (string(ofxCrypto::*)(string)) &ofxCrypto::base64_encode)
         .def("base64_decode", (string(ofxCrypto::*)(string)) &ofxCrypto::base64_decode)
         .def("base64_encode", (string(ofxCrypto::*)(ofBuffer&)) &ofxCrypto::sha1)
         .def("base64_decode_to_buffer", (ofBuffer(ofxCrypto::*)(string)) &ofxCrypto::base64_decode_to_buffer),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXDELAUNAY
         class_<ofxDelaunay>("ofxDelaunay")
         .def(constructor<>())
         .def("setMaxPoints", (void(ofxDelaunay::*)(int)) &ofxDelaunay::setMaxPoints)
         .def("reset", (void(ofxDelaunay::*)(void)) &ofxDelaunay::reset)
         .def("addPoint", (int(ofxDelaunay::*)(const ofPoint&)) &ofxDelaunay::addPoint)
         .def("addPoint", (int(ofxDelaunay::*)(float,float,float)) &ofxDelaunay::addPoint)
         .def("triangulate", (int(ofxDelaunay::*)(void)) &ofxDelaunay::triangulate)
         .def("draw", (void(ofxDelaunay::*)(void)) &ofxDelaunay::draw)
         .def("drawTriangle", (void(ofxDelaunay::*)(int)) &ofxDelaunay::drawTriangle)
         .def("drawCenter", (void(ofxDelaunay::*)(int)) &ofxDelaunay::drawCenter),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXDITHER
         class_<ofxDither>("ofxDither")
         .def(constructor<>())
         .def("ordered", &ditherOrdered)
         .def("floyd_steinberg", (void(ofxDither::*)(ofImage&,ofImage&)) &ofxDither::dither_floyd_steinberg)
         .def("atkinson", (void(ofxDither::*)(ofImage&,ofImage&)) &ofxDither::dither_atkinson),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXDMX
         class_<ofxDmx>("ofxDmx")
         .def(constructor<>())
         .def("connect", (bool(ofxDmx::*)(int,unsigned int)) &ofxDmx::connect)
         .def("connect", (bool(ofxDmx::*)(string,unsigned int)) &ofxDmx::connect)
         .def("disconnect", (void(ofxDmx::*)(void)) &ofxDmx::disconnect)
         .def("setLevel", (bool(ofxDmx::*)(unsigned int,unsigned char)) &ofxDmx::setLevel)
         .def("clear", (void(ofxDmx::*)(void)) &ofxDmx::clear)
         .def("getLevel", (unsigned char(ofxDmx::*)(unsigned int)) &ofxDmx::getLevel)
         .def("update", (void(ofxDmx::*)(bool)) &ofxDmx::update)
         .def("setChannels", (void(ofxDmx::*)(unsigned int)) &ofxDmx::setChannels)
         .def("isConnected", (bool(ofxDmx::*)(void)) &ofxDmx::isConnected),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // ofxDOF
         class_<ofxDOF>("ofxDOF")
         .def(constructor<>())
         .def("setup", (void(ofxDOF::*)(int,int)) &ofxDOF::setup)
         .def("setShaderPath", (void(ofxDOF::*)(string)) &ofxDOF::setShaderPath)
         .def("reloadShader", (void(ofxDOF::*)(void)) &ofxDOF::reloadShader)
         .def("setBlurAmount", (void(ofxDOF::*)(float)) &ofxDOF::setBlurAmount)
         .def("getBlurAmount", (float(ofxDOF::*)(void)) &ofxDOF::getBlurAmount)
         .def("setFocalRange", (void(ofxDOF::*)(float)) &ofxDOF::setFocalRange)
         .def("getFocalRange", (float(ofxDOF::*)(void)) &ofxDOF::getFocalRange)
         .def("setFocalDistance", (void(ofxDOF::*)(float)) &ofxDOF::setFocalDistance)
         .def("getFocalDistance", (float(ofxDOF::*)(void)) &ofxDOF::getFocalDistance)
         .def("getWidth", (int(ofxDOF::*)(void)) &ofxDOF::getWidth)
         .def("getHeight", (int(ofxDOF::*)(void)) &ofxDOF::getHeight)
         .def("getDimensions", (ofRectangle(ofxDOF::*)(void)) &ofxDOF::getDimensions)
         .def("beginDOF", (void(ofxDOF::*)(void)) &ofxDOF::begin)
         .def("endDOF", (void(ofxDOF::*)(void)) &ofxDOF::end)
         .def("getFbo", (ofFbo&(ofxDOF::*)(void)) &ofxDOF::getFbo)
         .def("drawFocusAssist", (void(ofxDOF::*)(int,int)) &ofxDOF::drawFocusAssist)
         .def("drawFocusAssist", (void(ofxDOF::*)(int,int,int,int)) &ofxDOF::drawFocusAssist)
         .def("drawFocusAssist", (void(ofxDOF::*)(ofRectangle)) &ofxDOF::drawFocusAssist),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXFX
         
         // ofxFXObject
         class_<ofxFXObject>("ofxFXObject")
         .def(constructor<>())
         .def("allocate", (void(ofxFXObject::*)(int,int,int)) &ofxFXObject::allocate)
         .def("allocate", (void(ofxFXObject::*)(int,int)) &ofxFXObject::allocate)
         .def("set", (void(ofxFXObject::*)(ofRectangle const&)) &ofxFXObject::set)
         .def("setCode", (bool(ofxFXObject::*)(string)) &ofxFXObject::setCode)
         .def("load", (bool(ofxFXObject::*)(string)) &ofxFXObject::load)
         .def("compileCode", (bool(ofxFXObject::*)(void)) &ofxFXObject::compileCode)
         .def("setPasses", (void(ofxFXObject::*)(int)) &ofxFXObject::setPasses)
         .def("setInternalFormat", (void(ofxFXObject::*)(int)) &ofxFXObject::setInternalFormat)
         .def("setTexture", (void(ofxFXObject::*)(ofTexture&,int)) &ofxFXObject::setTexture)
         .def("beginFx", (void(ofxFXObject::*)(int)) &ofxFXObject::begin)
         .def("endFx", (void(ofxFXObject::*)(int)) &ofxFXObject::end)
         .def("compiled", (bool(ofxFXObject::*)(void)) &ofxFXObject::compiled)
         .def("getCode", (string(ofxFXObject::*)(void)) &ofxFXObject::getCode)
         .def("getWidth", (float(ofxFXObject::*)(void)) &ofxFXObject::getWidth)
         .def("getHeight", (float(ofxFXObject::*)(void)) &ofxFXObject::getHeight)
         .def("getPasses", (int(ofxFXObject::*)(void)) &ofxFXObject::getPasses)
         .def("getResolution", (ofVec2f(ofxFXObject::*)(void)) &ofxFXObject::getResolution)
         .def("getInternalFormat", (int(ofxFXObject::*)(void)) &ofxFXObject::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxFXObject::*)(void)) &ofxFXObject::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxFXObject::*)(void)) &ofxFXObject::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxFXObject::*)(void)) &ofxFXObject::getTextureReference)
         .def("clear", (void(ofxFXObject::*)(int)) &ofxFXObject::clear)
         .def("update", (void(ofxFXObject::*)(void)) &ofxFXObject::update)
         .def("draw", (void(ofxFXObject::*)(ofRectangle&)) &ofxFXObject::draw)
         .def("draw", (void(ofxFXObject::*)(int,int,float,float)) &ofxFXObject::draw),
         
         // ofxAbsDiff
         class_<ofxAbsDiff>("ofxAbsDiff")
         .def(constructor<>())
         .def("allocate", (void(ofxAbsDiff::*)(int,int,int)) &ofxAbsDiff::allocate)
         .def("allocate", (void(ofxAbsDiff::*)(int,int)) &ofxAbsDiff::allocate)
         .def("set", (void(ofxAbsDiff::*)(ofRectangle const&)) &ofxAbsDiff::set)
         .def("setCode", (bool(ofxAbsDiff::*)(string)) &ofxAbsDiff::setCode)
         .def("load", (bool(ofxAbsDiff::*)(string)) &ofxAbsDiff::load)
         .def("compileCode", (bool(ofxAbsDiff::*)(void)) &ofxAbsDiff::compileCode)
         .def("setPasses", (void(ofxAbsDiff::*)(int)) &ofxAbsDiff::setPasses)
         .def("setInternalFormat", (void(ofxAbsDiff::*)(int)) &ofxAbsDiff::setInternalFormat)
         .def("setTexture", (void(ofxAbsDiff::*)(ofTexture&,int)) &ofxAbsDiff::setTexture)
         .def("beginFx", (void(ofxAbsDiff::*)(int)) &ofxAbsDiff::begin)
         .def("endFx", (void(ofxAbsDiff::*)(int)) &ofxAbsDiff::end)
         .def("compiled", (bool(ofxAbsDiff::*)(void)) &ofxAbsDiff::compiled)
         .def("getCode", (string(ofxAbsDiff::*)(void)) &ofxAbsDiff::getCode)
         .def("getWidth", (float(ofxAbsDiff::*)(void)) &ofxAbsDiff::getWidth)
         .def("getHeight", (float(ofxAbsDiff::*)(void)) &ofxAbsDiff::getHeight)
         .def("getPasses", (int(ofxAbsDiff::*)(void)) &ofxAbsDiff::getPasses)
         .def("getResolution", (ofVec2f(ofxAbsDiff::*)(void)) &ofxAbsDiff::getResolution)
         .def("getInternalFormat", (int(ofxAbsDiff::*)(void)) &ofxAbsDiff::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxAbsDiff::*)(void)) &ofxAbsDiff::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxAbsDiff::*)(void)) &ofxAbsDiff::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxAbsDiff::*)(void)) &ofxAbsDiff::getTextureReference)
         .def("clear", (void(ofxAbsDiff::*)(int)) &ofxAbsDiff::clear)
         .def("update", (void(ofxAbsDiff::*)(void)) &ofxAbsDiff::update)
         .def("draw", (void(ofxAbsDiff::*)(ofRectangle&)) &ofxAbsDiff::draw)
         .def("draw", (void(ofxAbsDiff::*)(int,int,float,float)) &ofxAbsDiff::draw),
         
         // ofxBlend
         class_<ofxBlend>("ofxBlend")
         .def(constructor<>())
         .def("allocate", (void(ofxBlend::*)(int,int,int)) &ofxBlend::allocate)
         .def("allocate", (void(ofxBlend::*)(int,int)) &ofxBlend::allocate)
         .def("set", (void(ofxBlend::*)(ofRectangle const&)) &ofxBlend::set)
         .def("setCode", (bool(ofxBlend::*)(string)) &ofxBlend::setCode)
         .def("load", (bool(ofxBlend::*)(string)) &ofxBlend::load)
         .def("compileCode", (bool(ofxBlend::*)(void)) &ofxBlend::compileCode)
         .def("setPasses", (void(ofxBlend::*)(int)) &ofxBlend::setPasses)
         .def("setInternalFormat", (void(ofxBlend::*)(int)) &ofxBlend::setInternalFormat)
         .def("setTexture", (void(ofxBlend::*)(ofTexture&,int)) &ofxBlend::setTexture)
         .def("beginFx", (void(ofxBlend::*)(int)) &ofxBlend::begin)
         .def("endFx", (void(ofxBlend::*)(int)) &ofxBlend::end)
         .def("compiled", (bool(ofxBlend::*)(void)) &ofxBlend::compiled)
         .def("getCode", (string(ofxBlend::*)(void)) &ofxBlend::getCode)
         .def("getWidth", (float(ofxBlend::*)(void)) &ofxBlend::getWidth)
         .def("getHeight", (float(ofxBlend::*)(void)) &ofxBlend::getHeight)
         .def("getPasses", (int(ofxBlend::*)(void)) &ofxBlend::getPasses)
         .def("getResolution", (ofVec2f(ofxBlend::*)(void)) &ofxBlend::getResolution)
         .def("getInternalFormat", (int(ofxBlend::*)(void)) &ofxBlend::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxBlend::*)(void)) &ofxBlend::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxBlend::*)(void)) &ofxBlend::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxBlend::*)(void)) &ofxBlend::getTextureReference)
         .def("clear", (void(ofxBlend::*)(int)) &ofxBlend::clear)
         .def("update", (void(ofxBlend::*)(void)) &ofxBlend::update)
         .def("draw", (void(ofxBlend::*)(ofRectangle&)) &ofxBlend::draw)
         .def("draw", (void(ofxBlend::*)(int,int,float,float)) &ofxBlend::draw)
         
         .def("setBlendMode", (void(ofxBlend::*)(PSBlendMode)) &ofxBlend::setBlendMode)
         .def("addLayer", (void(ofxBlend::*)(ofTexture&,PSBlendMode)) &ofxBlend::addLayer)
         .def("beginBackground", (void(ofxBlend::*)(void)) &ofxBlend::beginBackground)
         .def("endBackground", (void(ofxBlend::*)(void)) &ofxBlend::endBackground)
         .def("draw", (void(ofxBlend::*)(int,int)) &ofxBlend::draw),
         
         class_<ofxClone>("ofxClone")
         .def(constructor<>())
         .def("allocate", (void(ofxClone::*)(int,int,int)) &ofxClone::allocate)
         .def("allocate", (void(ofxClone::*)(int,int)) &ofxClone::allocate)
         .def("set", (void(ofxClone::*)(ofRectangle const&)) &ofxClone::set)
         .def("setCode", (bool(ofxClone::*)(string)) &ofxClone::setCode)
         .def("load", (bool(ofxClone::*)(string)) &ofxClone::load)
         .def("compileCode", (bool(ofxClone::*)(void)) &ofxClone::compileCode)
         .def("setPasses", (void(ofxClone::*)(int)) &ofxClone::setPasses)
         .def("setInternalFormat", (void(ofxClone::*)(int)) &ofxClone::setInternalFormat)
         .def("setTexture", (void(ofxClone::*)(ofTexture&,int)) &ofxClone::setTexture)
         .def("beginFx", (void(ofxClone::*)(int)) &ofxClone::begin)
         .def("endFx", (void(ofxClone::*)(int)) &ofxClone::end)
         .def("compiled", (bool(ofxClone::*)(void)) &ofxClone::compiled)
         .def("getCode", (string(ofxClone::*)(void)) &ofxClone::getCode)
         .def("getWidth", (float(ofxClone::*)(void)) &ofxClone::getWidth)
         .def("getHeight", (float(ofxClone::*)(void)) &ofxClone::getHeight)
         .def("getPasses", (int(ofxClone::*)(void)) &ofxClone::getPasses)
         .def("getResolution", (ofVec2f(ofxClone::*)(void)) &ofxClone::getResolution)
         .def("getInternalFormat", (int(ofxClone::*)(void)) &ofxClone::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxClone::*)(void)) &ofxClone::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxClone::*)(void)) &ofxClone::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxClone::*)(void)) &ofxClone::getTextureReference)
         .def("clear", (void(ofxClone::*)(int)) &ofxClone::clear)
         .def("update", (void(ofxClone::*)(void)) &ofxClone::update)
         .def("draw", (void(ofxClone::*)(ofRectangle&)) &ofxClone::draw)
         .def("draw", (void(ofxClone::*)(int,int,float,float)) &ofxClone::draw)
         
         .def("setStrength", (void(ofxClone::*)(int)) &ofxClone::setStrength),
         
         class_<ofxMask>("ofxMask")
         .def(constructor<>())
         .def("allocate", (void(ofxMask::*)(int,int,int)) &ofxMask::allocate)
         .def("allocate", (void(ofxMask::*)(int,int)) &ofxMask::allocate)
         .def("set", (void(ofxMask::*)(ofRectangle const&)) &ofxMask::set)
         .def("setCode", (bool(ofxMask::*)(string)) &ofxMask::setCode)
         .def("load", (bool(ofxMask::*)(string)) &ofxMask::load)
         .def("compileCode", (bool(ofxMask::*)(void)) &ofxMask::compileCode)
         .def("setPasses", (void(ofxMask::*)(int)) &ofxMask::setPasses)
         .def("setInternalFormat", (void(ofxMask::*)(int)) &ofxMask::setInternalFormat)
         .def("setTexture", (void(ofxMask::*)(ofTexture&,int)) &ofxMask::setTexture)
         .def("beginFx", (void(ofxMask::*)(int)) &ofxMask::begin)
         .def("endFx", (void(ofxMask::*)(int)) &ofxMask::end)
         .def("compiled", (bool(ofxMask::*)(void)) &ofxMask::compiled)
         .def("getCode", (string(ofxMask::*)(void)) &ofxMask::getCode)
         .def("getWidth", (float(ofxMask::*)(void)) &ofxMask::getWidth)
         .def("getHeight", (float(ofxMask::*)(void)) &ofxMask::getHeight)
         .def("getPasses", (int(ofxMask::*)(void)) &ofxMask::getPasses)
         .def("getResolution", (ofVec2f(ofxMask::*)(void)) &ofxMask::getResolution)
         .def("getInternalFormat", (int(ofxMask::*)(void)) &ofxMask::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxMask::*)(void)) &ofxMask::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxMask::*)(void)) &ofxMask::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxMask::*)(void)) &ofxMask::getTextureReference)
         .def("clear", (void(ofxMask::*)(int)) &ofxMask::clear)
         .def("update", (void(ofxMask::*)(void)) &ofxMask::update)
         .def("draw", (void(ofxMask::*)(ofRectangle&)) &ofxMask::draw)
         .def("draw", (void(ofxMask::*)(int,int,float,float)) &ofxMask::draw),
         
         class_<ofxMultiTexture>("ofxMultiTexture")
         .def(constructor<>())
         .def("allocate", (void(ofxMultiTexture::*)(int,int,int)) &ofxMultiTexture::allocate)
         .def("allocate", (void(ofxMultiTexture::*)(int,int)) &ofxMultiTexture::allocate)
         .def("set", (void(ofxMultiTexture::*)(ofRectangle const&)) &ofxMultiTexture::set)
         .def("setCode", (bool(ofxMultiTexture::*)(string)) &ofxMultiTexture::setCode)
         .def("load", (bool(ofxMultiTexture::*)(string)) &ofxMultiTexture::load)
         .def("compileCode", (bool(ofxMultiTexture::*)(void)) &ofxMultiTexture::compileCode)
         .def("setPasses", (void(ofxMultiTexture::*)(int)) &ofxMultiTexture::setPasses)
         .def("setInternalFormat", (void(ofxMultiTexture::*)(int)) &ofxMultiTexture::setInternalFormat)
         .def("setTexture", (void(ofxMultiTexture::*)(ofTexture&,int)) &ofxMultiTexture::setTexture)
         .def("beginFx", (void(ofxMultiTexture::*)(int)) &ofxMultiTexture::begin)
         .def("endFx", (void(ofxMultiTexture::*)(int)) &ofxMultiTexture::end)
         .def("compiled", (bool(ofxMultiTexture::*)(void)) &ofxMultiTexture::compiled)
         .def("getCode", (string(ofxMultiTexture::*)(void)) &ofxMultiTexture::getCode)
         .def("getWidth", (float(ofxMultiTexture::*)(void)) &ofxMultiTexture::getWidth)
         .def("getHeight", (float(ofxMultiTexture::*)(void)) &ofxMultiTexture::getHeight)
         .def("getPasses", (int(ofxMultiTexture::*)(void)) &ofxMultiTexture::getPasses)
         .def("getResolution", (ofVec2f(ofxMultiTexture::*)(void)) &ofxMultiTexture::getResolution)
         .def("getInternalFormat", (int(ofxMultiTexture::*)(void)) &ofxMultiTexture::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxMultiTexture::*)(void)) &ofxMultiTexture::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxMultiTexture::*)(void)) &ofxMultiTexture::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxMultiTexture::*)(void)) &ofxMultiTexture::getTextureReference)
         .def("clear", (void(ofxMultiTexture::*)(int)) &ofxMultiTexture::clear)
         .def("update", (void(ofxMultiTexture::*)(void)) &ofxMultiTexture::update)
         .def("draw", (void(ofxMultiTexture::*)(ofRectangle&)) &ofxMultiTexture::draw)
         .def("draw", (void(ofxMultiTexture::*)(int,int,float,float)) &ofxMultiTexture::draw),
         
         class_<ofxSubstract>("ofxSubstract")
         .def(constructor<>())
         .def("allocate", (void(ofxSubstract::*)(int,int,int)) &ofxSubstract::allocate)
         .def("allocate", (void(ofxSubstract::*)(int,int)) &ofxSubstract::allocate)
         .def("set", (void(ofxSubstract::*)(ofRectangle const&)) &ofxSubstract::set)
         .def("setCode", (bool(ofxSubstract::*)(string)) &ofxSubstract::setCode)
         .def("load", (bool(ofxSubstract::*)(string)) &ofxSubstract::load)
         .def("compileCode", (bool(ofxSubstract::*)(void)) &ofxSubstract::compileCode)
         .def("setPasses", (void(ofxSubstract::*)(int)) &ofxSubstract::setPasses)
         .def("setInternalFormat", (void(ofxSubstract::*)(int)) &ofxSubstract::setInternalFormat)
         .def("setTexture", (void(ofxSubstract::*)(ofTexture&,int)) &ofxSubstract::setTexture)
         .def("beginFx", (void(ofxSubstract::*)(int)) &ofxSubstract::begin)
         .def("endFx", (void(ofxSubstract::*)(int)) &ofxSubstract::end)
         .def("compiled", (bool(ofxSubstract::*)(void)) &ofxSubstract::compiled)
         .def("getCode", (string(ofxSubstract::*)(void)) &ofxSubstract::getCode)
         .def("getWidth", (float(ofxSubstract::*)(void)) &ofxSubstract::getWidth)
         .def("getHeight", (float(ofxSubstract::*)(void)) &ofxSubstract::getHeight)
         .def("getPasses", (int(ofxSubstract::*)(void)) &ofxSubstract::getPasses)
         .def("getResolution", (ofVec2f(ofxSubstract::*)(void)) &ofxSubstract::getResolution)
         .def("getInternalFormat", (int(ofxSubstract::*)(void)) &ofxSubstract::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxSubstract::*)(void)) &ofxSubstract::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxSubstract::*)(void)) &ofxSubstract::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxSubstract::*)(void)) &ofxSubstract::getTextureReference)
         .def("clear", (void(ofxSubstract::*)(int)) &ofxSubstract::clear)
         .def("update", (void(ofxSubstract::*)(void)) &ofxSubstract::update)
         .def("draw", (void(ofxSubstract::*)(ofRectangle&)) &ofxSubstract::draw)
         .def("draw", (void(ofxSubstract::*)(int,int,float,float)) &ofxSubstract::draw),
         
         class_<ofxBloom>("ofxBloom")
         .def(constructor<>())
         .def("allocate", (void(ofxBloom::*)(int,int,int)) &ofxBloom::allocate)
         .def("allocate", (void(ofxBloom::*)(int,int)) &ofxBloom::allocate)
         .def("set", (void(ofxBloom::*)(ofRectangle const&)) &ofxBloom::set)
         .def("setCode", (bool(ofxBloom::*)(string)) &ofxBloom::setCode)
         .def("load", (bool(ofxBloom::*)(string)) &ofxBloom::load)
         .def("compileCode", (bool(ofxBloom::*)(void)) &ofxBloom::compileCode)
         .def("setPasses", (void(ofxBloom::*)(int)) &ofxBloom::setPasses)
         .def("setInternalFormat", (void(ofxBloom::*)(int)) &ofxBloom::setInternalFormat)
         .def("setTexture", (void(ofxBloom::*)(ofTexture&,int)) &ofxBloom::setTexture)
         .def("beginFx", (void(ofxBloom::*)(int)) &ofxBloom::begin)
         .def("endFx", (void(ofxBloom::*)(int)) &ofxBloom::end)
         .def("compiled", (bool(ofxBloom::*)(void)) &ofxBloom::compiled)
         .def("getCode", (string(ofxBloom::*)(void)) &ofxBloom::getCode)
         .def("getWidth", (float(ofxBloom::*)(void)) &ofxBloom::getWidth)
         .def("getHeight", (float(ofxBloom::*)(void)) &ofxBloom::getHeight)
         .def("getPasses", (int(ofxBloom::*)(void)) &ofxBloom::getPasses)
         .def("getResolution", (ofVec2f(ofxBloom::*)(void)) &ofxBloom::getResolution)
         .def("getInternalFormat", (int(ofxBloom::*)(void)) &ofxBloom::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxBloom::*)(void)) &ofxBloom::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxBloom::*)(void)) &ofxBloom::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxBloom::*)(void)) &ofxBloom::getTextureReference)
         .def("clear", (void(ofxBloom::*)(int)) &ofxBloom::clear)
         .def("update", (void(ofxBloom::*)(void)) &ofxBloom::update)
         .def("draw", (void(ofxBloom::*)(ofRectangle&)) &ofxBloom::draw)
         .def("draw", (void(ofxBloom::*)(int,int,float,float)) &ofxBloom::draw),
         
         class_<ofxBlur>("ofxBlur")
         .def(constructor<>())
         .def("allocate", (void(ofxBlur::*)(int,int,int)) &ofxBlur::allocate)
         .def("allocate", (void(ofxBlur::*)(int,int)) &ofxBlur::allocate)
         .def("set", (void(ofxBlur::*)(ofRectangle const&)) &ofxBlur::set)
         .def("setCode", (bool(ofxBlur::*)(string)) &ofxBlur::setCode)
         .def("load", (bool(ofxBlur::*)(string)) &ofxBlur::load)
         .def("compileCode", (bool(ofxBlur::*)(void)) &ofxBlur::compileCode)
         .def("setPasses", (void(ofxBlur::*)(int)) &ofxBlur::setPasses)
         .def("setInternalFormat", (void(ofxBlur::*)(int)) &ofxBlur::setInternalFormat)
         .def("setTexture", (void(ofxBlur::*)(ofTexture&,int)) &ofxBlur::setTexture)
         .def("beginFx", (void(ofxBlur::*)(int)) &ofxBlur::begin)
         .def("endFx", (void(ofxBlur::*)(int)) &ofxBlur::end)
         .def("compiled", (bool(ofxBlur::*)(void)) &ofxBlur::compiled)
         .def("getCode", (string(ofxBlur::*)(void)) &ofxBlur::getCode)
         .def("getWidth", (float(ofxBlur::*)(void)) &ofxBlur::getWidth)
         .def("getHeight", (float(ofxBlur::*)(void)) &ofxBlur::getHeight)
         .def("getPasses", (int(ofxBlur::*)(void)) &ofxBlur::getPasses)
         .def("getResolution", (ofVec2f(ofxBlur::*)(void)) &ofxBlur::getResolution)
         .def("getInternalFormat", (int(ofxBlur::*)(void)) &ofxBlur::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxBlur::*)(void)) &ofxBlur::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxBlur::*)(void)) &ofxBlur::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxBlur::*)(void)) &ofxBlur::getTextureReference)
         .def("clear", (void(ofxBlur::*)(int)) &ofxBlur::clear)
         .def("update", (void(ofxBlur::*)(void)) &ofxBlur::update)
         .def("draw", (void(ofxBlur::*)(ofRectangle&)) &ofxBlur::draw)
         .def("draw", (void(ofxBlur::*)(int,int,float,float)) &ofxBlur::draw)
         
         .def("setFade", (void(ofxBlur::*)(float)) &ofxBlur::setFade),
         
         class_<ofxBokeh>("ofxBokeh")
         .def(constructor<>())
         .def("allocate", (void(ofxBokeh::*)(int,int,int)) &ofxBokeh::allocate)
         .def("allocate", (void(ofxBokeh::*)(int,int)) &ofxBokeh::allocate)
         .def("set", (void(ofxBokeh::*)(ofRectangle const&)) &ofxBokeh::set)
         .def("setCode", (bool(ofxBokeh::*)(string)) &ofxBokeh::setCode)
         .def("load", (bool(ofxBokeh::*)(string)) &ofxBokeh::load)
         .def("compileCode", (bool(ofxBokeh::*)(void)) &ofxBokeh::compileCode)
         .def("setPasses", (void(ofxBokeh::*)(int)) &ofxBokeh::setPasses)
         .def("setInternalFormat", (void(ofxBokeh::*)(int)) &ofxBokeh::setInternalFormat)
         .def("setTexture", (void(ofxBokeh::*)(ofTexture&,int)) &ofxBokeh::setTexture)
         .def("beginFx", (void(ofxBokeh::*)(int)) &ofxBokeh::begin)
         .def("endFx", (void(ofxBokeh::*)(int)) &ofxBokeh::end)
         .def("compiled", (bool(ofxBokeh::*)(void)) &ofxBokeh::compiled)
         .def("getCode", (string(ofxBokeh::*)(void)) &ofxBokeh::getCode)
         .def("getWidth", (float(ofxBokeh::*)(void)) &ofxBokeh::getWidth)
         .def("getHeight", (float(ofxBokeh::*)(void)) &ofxBokeh::getHeight)
         .def("getPasses", (int(ofxBokeh::*)(void)) &ofxBokeh::getPasses)
         .def("getResolution", (ofVec2f(ofxBokeh::*)(void)) &ofxBokeh::getResolution)
         .def("getInternalFormat", (int(ofxBokeh::*)(void)) &ofxBokeh::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxBokeh::*)(void)) &ofxBokeh::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxBokeh::*)(void)) &ofxBokeh::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxBokeh::*)(void)) &ofxBokeh::getTextureReference)
         .def("clear", (void(ofxBokeh::*)(int)) &ofxBokeh::clear)
         .def("update", (void(ofxBokeh::*)(void)) &ofxBokeh::update)
         .def("draw", (void(ofxBokeh::*)(ofRectangle&)) &ofxBokeh::draw)
         .def("draw", (void(ofxBokeh::*)(int,int,float,float)) &ofxBokeh::draw)
         
         .def("setRadius", (void(ofxBokeh::*)(float)) &ofxBokeh::setRadius),
         
         class_<ofxChromaAb>("ofxChromaAb")
         .def(constructor<>())
         .def("allocate", (void(ofxChromaAb::*)(int,int,int)) &ofxChromaAb::allocate)
         .def("allocate", (void(ofxChromaAb::*)(int,int)) &ofxChromaAb::allocate)
         .def("set", (void(ofxChromaAb::*)(ofRectangle const&)) &ofxChromaAb::set)
         .def("setCode", (bool(ofxChromaAb::*)(string)) &ofxChromaAb::setCode)
         .def("load", (bool(ofxChromaAb::*)(string)) &ofxChromaAb::load)
         .def("compileCode", (bool(ofxChromaAb::*)(void)) &ofxChromaAb::compileCode)
         .def("setPasses", (void(ofxChromaAb::*)(int)) &ofxChromaAb::setPasses)
         .def("setInternalFormat", (void(ofxChromaAb::*)(int)) &ofxChromaAb::setInternalFormat)
         .def("setTexture", (void(ofxChromaAb::*)(ofTexture&,int)) &ofxChromaAb::setTexture)
         .def("beginFx", (void(ofxChromaAb::*)(int)) &ofxChromaAb::begin)
         .def("endFx", (void(ofxChromaAb::*)(int)) &ofxChromaAb::end)
         .def("compiled", (bool(ofxChromaAb::*)(void)) &ofxChromaAb::compiled)
         .def("getCode", (string(ofxChromaAb::*)(void)) &ofxChromaAb::getCode)
         .def("getWidth", (float(ofxChromaAb::*)(void)) &ofxChromaAb::getWidth)
         .def("getHeight", (float(ofxChromaAb::*)(void)) &ofxChromaAb::getHeight)
         .def("getPasses", (int(ofxChromaAb::*)(void)) &ofxChromaAb::getPasses)
         .def("getResolution", (ofVec2f(ofxChromaAb::*)(void)) &ofxChromaAb::getResolution)
         .def("getInternalFormat", (int(ofxChromaAb::*)(void)) &ofxChromaAb::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxChromaAb::*)(void)) &ofxChromaAb::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxChromaAb::*)(void)) &ofxChromaAb::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxChromaAb::*)(void)) &ofxChromaAb::getTextureReference)
         .def("clear", (void(ofxChromaAb::*)(int)) &ofxChromaAb::clear)
         .def("update", (void(ofxChromaAb::*)(void)) &ofxChromaAb::update)
         .def("draw", (void(ofxChromaAb::*)(ofRectangle&)) &ofxChromaAb::draw)
         .def("draw", (void(ofxChromaAb::*)(int,int,float,float)) &ofxChromaAb::draw)
         
         .def_readwrite("offset", &ofxChromaAb::offset),
         
         class_<ofxContrast>("ofxContrast")
         .def(constructor<>())
         .def("allocate", (void(ofxContrast::*)(int,int,int)) &ofxContrast::allocate)
         .def("allocate", (void(ofxContrast::*)(int,int)) &ofxContrast::allocate)
         .def("set", (void(ofxContrast::*)(ofRectangle const&)) &ofxContrast::set)
         .def("setCode", (bool(ofxContrast::*)(string)) &ofxContrast::setCode)
         .def("load", (bool(ofxContrast::*)(string)) &ofxContrast::load)
         .def("compileCode", (bool(ofxContrast::*)(void)) &ofxContrast::compileCode)
         .def("setPasses", (void(ofxContrast::*)(int)) &ofxContrast::setPasses)
         .def("setInternalFormat", (void(ofxContrast::*)(int)) &ofxContrast::setInternalFormat)
         .def("setTexture", (void(ofxContrast::*)(ofTexture&,int)) &ofxContrast::setTexture)
         .def("beginFx", (void(ofxContrast::*)(int)) &ofxContrast::begin)
         .def("endFx", (void(ofxContrast::*)(int)) &ofxContrast::end)
         .def("compiled", (bool(ofxContrast::*)(void)) &ofxContrast::compiled)
         .def("getCode", (string(ofxContrast::*)(void)) &ofxContrast::getCode)
         .def("getWidth", (float(ofxContrast::*)(void)) &ofxContrast::getWidth)
         .def("getHeight", (float(ofxContrast::*)(void)) &ofxContrast::getHeight)
         .def("getPasses", (int(ofxContrast::*)(void)) &ofxContrast::getPasses)
         .def("getResolution", (ofVec2f(ofxContrast::*)(void)) &ofxContrast::getResolution)
         .def("getInternalFormat", (int(ofxContrast::*)(void)) &ofxContrast::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxContrast::*)(void)) &ofxContrast::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxContrast::*)(void)) &ofxContrast::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxContrast::*)(void)) &ofxContrast::getTextureReference)
         .def("clear", (void(ofxContrast::*)(int)) &ofxContrast::clear)
         .def("update", (void(ofxContrast::*)(void)) &ofxContrast::update)
         .def("draw", (void(ofxContrast::*)(ofRectangle&)) &ofxContrast::draw)
         .def("draw", (void(ofxContrast::*)(int,int,float,float)) &ofxContrast::draw)
         
         .def_readwrite("contrast", &ofxContrast::contrast)
         .def_readwrite("brightness", &ofxContrast::brightness),
         
         class_<ofxGaussianBlur>("ofxGaussianBlur")
         .def(constructor<>())
         .def("allocate", (void(ofxGaussianBlur::*)(int,int,int)) &ofxGaussianBlur::allocate)
         .def("allocate", (void(ofxGaussianBlur::*)(int,int)) &ofxGaussianBlur::allocate)
         .def("set", (void(ofxGaussianBlur::*)(ofRectangle const&)) &ofxGaussianBlur::set)
         .def("setCode", (bool(ofxGaussianBlur::*)(string)) &ofxGaussianBlur::setCode)
         .def("load", (bool(ofxGaussianBlur::*)(string)) &ofxGaussianBlur::load)
         .def("setPasses", (void(ofxGaussianBlur::*)(int)) &ofxGaussianBlur::setPasses)
         .def("setInternalFormat", (void(ofxGaussianBlur::*)(int)) &ofxGaussianBlur::setInternalFormat)
         .def("setTexture", (void(ofxGaussianBlur::*)(ofTexture&,int)) &ofxGaussianBlur::setTexture)
         .def("beginFx", (void(ofxGaussianBlur::*)(int)) &ofxGaussianBlur::begin)
         .def("endFx", (void(ofxGaussianBlur::*)(int)) &ofxGaussianBlur::end)
         .def("compiled", (bool(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::compiled)
         .def("getCode", (string(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getCode)
         .def("getWidth", (float(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getWidth)
         .def("getHeight", (float(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getHeight)
         .def("getPasses", (int(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getPasses)
         .def("getResolution", (ofVec2f(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getResolution)
         .def("getInternalFormat", (int(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::getTextureReference)
         .def("clear", (void(ofxGaussianBlur::*)(int)) &ofxGaussianBlur::clear)
         .def("update", (void(ofxGaussianBlur::*)(void)) &ofxGaussianBlur::update)
         .def("draw", (void(ofxGaussianBlur::*)(ofRectangle&)) &ofxGaussianBlur::draw)
         .def("draw", (void(ofxGaussianBlur::*)(int,int,float,float)) &ofxGaussianBlur::draw)
         
         .def("setRadius", (ofxGaussianBlur&(ofxGaussianBlur::*)(float)) &ofxGaussianBlur::setRadius),
         
         class_<ofxGlow>("ofxGlow")
         .def(constructor<>())
         .def("allocate", (void(ofxGlow::*)(int,int,int)) &ofxGlow::allocate)
         .def("allocate", (void(ofxGlow::*)(int,int)) &ofxGlow::allocate)
         .def("set", (void(ofxGlow::*)(ofRectangle const&)) &ofxGlow::set)
         .def("setCode", (bool(ofxGlow::*)(string)) &ofxGlow::setCode)
         .def("load", (bool(ofxGlow::*)(string)) &ofxGlow::load)
         .def("setPasses", (void(ofxGlow::*)(int)) &ofxGlow::setPasses)
         .def("setInternalFormat", (void(ofxGlow::*)(int)) &ofxGlow::setInternalFormat)
         .def("setTexture", (void(ofxGlow::*)(ofTexture&,int)) &ofxGlow::setTexture)
         .def("beginFx", (void(ofxGlow::*)(int)) &ofxGlow::begin)
         .def("endFx", (void(ofxGlow::*)(int)) &ofxGlow::end)
         .def("compiled", (bool(ofxGlow::*)(void)) &ofxGlow::compiled)
         .def("getCode", (string(ofxGlow::*)(void)) &ofxGlow::getCode)
         .def("getWidth", (float(ofxGlow::*)(void)) &ofxGlow::getWidth)
         .def("getHeight", (float(ofxGlow::*)(void)) &ofxGlow::getHeight)
         .def("getPasses", (int(ofxGlow::*)(void)) &ofxGlow::getPasses)
         .def("getResolution", (ofVec2f(ofxGlow::*)(void)) &ofxGlow::getResolution)
         .def("getInternalFormat", (int(ofxGlow::*)(void)) &ofxGlow::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxGlow::*)(void)) &ofxGlow::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxGlow::*)(void)) &ofxGlow::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxGlow::*)(void)) &ofxGlow::getTextureReference)
         .def("clear", (void(ofxGlow::*)(int)) &ofxGlow::clear)
         .def("update", (void(ofxGlow::*)(void)) &ofxGlow::update)
         .def("draw", (void(ofxGlow::*)(ofRectangle&)) &ofxGlow::draw)
         .def("draw", (void(ofxGlow::*)(int,int,float,float)) &ofxGlow::draw)
         
         .def("setRadius", (ofxGlow&(ofxGlow::*)(float)) &ofxGlow::setRadius),
         
         class_<ofxGrayscale>("ofxGrayscale")
         .def(constructor<>())
         .def("allocate", (void(ofxGrayscale::*)(int,int,int)) &ofxGrayscale::allocate)
         .def("allocate", (void(ofxGrayscale::*)(int,int)) &ofxGrayscale::allocate)
         .def("set", (void(ofxGrayscale::*)(ofRectangle const&)) &ofxGrayscale::set)
         .def("setCode", (bool(ofxGrayscale::*)(string)) &ofxGrayscale::setCode)
         .def("load", (bool(ofxGrayscale::*)(string)) &ofxGrayscale::load)
         .def("compileCode", (bool(ofxGrayscale::*)(void)) &ofxGrayscale::compileCode)
         .def("setPasses", (void(ofxGrayscale::*)(int)) &ofxGrayscale::setPasses)
         .def("setInternalFormat", (void(ofxGrayscale::*)(int)) &ofxGrayscale::setInternalFormat)
         .def("setTexture", (void(ofxGrayscale::*)(ofTexture&,int)) &ofxGrayscale::setTexture)
         .def("beginFx", (void(ofxGrayscale::*)(int)) &ofxGrayscale::begin)
         .def("endFx", (void(ofxGrayscale::*)(int)) &ofxGrayscale::end)
         .def("compiled", (bool(ofxGrayscale::*)(void)) &ofxGrayscale::compiled)
         .def("getCode", (string(ofxGrayscale::*)(void)) &ofxGrayscale::getCode)
         .def("getWidth", (float(ofxGrayscale::*)(void)) &ofxGrayscale::getWidth)
         .def("getHeight", (float(ofxGrayscale::*)(void)) &ofxGrayscale::getHeight)
         .def("getPasses", (int(ofxGrayscale::*)(void)) &ofxGrayscale::getPasses)
         .def("getResolution", (ofVec2f(ofxGrayscale::*)(void)) &ofxGrayscale::getResolution)
         .def("getInternalFormat", (int(ofxGrayscale::*)(void)) &ofxGrayscale::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxGrayscale::*)(void)) &ofxGrayscale::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxGrayscale::*)(void)) &ofxGrayscale::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxGrayscale::*)(void)) &ofxGrayscale::getTextureReference)
         .def("clear", (void(ofxGrayscale::*)(int)) &ofxGrayscale::clear)
         .def("update", (void(ofxGrayscale::*)(void)) &ofxGrayscale::update)
         .def("draw", (void(ofxGrayscale::*)(ofRectangle&)) &ofxGrayscale::draw)
         .def("draw", (void(ofxGrayscale::*)(int,int,float,float)) &ofxGrayscale::draw),
         
         class_<ofxInverse>("ofxInverse")
         .def(constructor<>())
         .def("allocate", (void(ofxInverse::*)(int,int,int)) &ofxInverse::allocate)
         .def("allocate", (void(ofxInverse::*)(int,int)) &ofxInverse::allocate)
         .def("set", (void(ofxInverse::*)(ofRectangle const&)) &ofxInverse::set)
         .def("setCode", (bool(ofxInverse::*)(string)) &ofxInverse::setCode)
         .def("load", (bool(ofxInverse::*)(string)) &ofxInverse::load)
         .def("compileCode", (bool(ofxInverse::*)(void)) &ofxInverse::compileCode)
         .def("setPasses", (void(ofxInverse::*)(int)) &ofxInverse::setPasses)
         .def("setInternalFormat", (void(ofxInverse::*)(int)) &ofxInverse::setInternalFormat)
         .def("setTexture", (void(ofxInverse::*)(ofTexture&,int)) &ofxInverse::setTexture)
         .def("beginFx", (void(ofxInverse::*)(int)) &ofxInverse::begin)
         .def("endFx", (void(ofxInverse::*)(int)) &ofxInverse::end)
         .def("compiled", (bool(ofxInverse::*)(void)) &ofxInverse::compiled)
         .def("getCode", (string(ofxInverse::*)(void)) &ofxInverse::getCode)
         .def("getWidth", (float(ofxInverse::*)(void)) &ofxInverse::getWidth)
         .def("getHeight", (float(ofxInverse::*)(void)) &ofxInverse::getHeight)
         .def("getPasses", (int(ofxInverse::*)(void)) &ofxInverse::getPasses)
         .def("getResolution", (ofVec2f(ofxInverse::*)(void)) &ofxInverse::getResolution)
         .def("getInternalFormat", (int(ofxInverse::*)(void)) &ofxInverse::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxInverse::*)(void)) &ofxInverse::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxInverse::*)(void)) &ofxInverse::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxInverse::*)(void)) &ofxInverse::getTextureReference)
         .def("clear", (void(ofxInverse::*)(int)) &ofxInverse::clear)
         .def("update", (void(ofxInverse::*)(void)) &ofxInverse::update)
         .def("draw", (void(ofxInverse::*)(ofRectangle&)) &ofxInverse::draw)
         .def("draw", (void(ofxInverse::*)(int,int,float,float)) &ofxInverse::draw),
         
         class_<ofxLUT>("ofxLUT")
         .def(constructor<>())
         .def("allocate", (void(ofxLUT::*)(int,int,int)) &ofxLUT::allocate)
         .def("allocate", (void(ofxLUT::*)(int,int)) &ofxLUT::allocate)
         .def("set", (void(ofxLUT::*)(ofRectangle const&)) &ofxLUT::set)
         .def("setCode", (bool(ofxLUT::*)(string)) &ofxLUT::setCode)
         .def("load", (bool(ofxLUT::*)(string)) &ofxLUT::load)
         .def("compileCode", (bool(ofxLUT::*)(void)) &ofxLUT::compileCode)
         .def("setPasses", (void(ofxLUT::*)(int)) &ofxLUT::setPasses)
         .def("setInternalFormat", (void(ofxLUT::*)(int)) &ofxLUT::setInternalFormat)
         .def("setTexture", (void(ofxLUT::*)(ofTexture&,int)) &ofxLUT::setTexture)
         .def("beginFx", (void(ofxLUT::*)(int)) &ofxLUT::begin)
         .def("endFx", (void(ofxLUT::*)(int)) &ofxLUT::end)
         .def("compiled", (bool(ofxLUT::*)(void)) &ofxLUT::compiled)
         .def("getCode", (string(ofxLUT::*)(void)) &ofxLUT::getCode)
         .def("getWidth", (float(ofxLUT::*)(void)) &ofxLUT::getWidth)
         .def("getHeight", (float(ofxLUT::*)(void)) &ofxLUT::getHeight)
         .def("getPasses", (int(ofxLUT::*)(void)) &ofxLUT::getPasses)
         .def("getResolution", (ofVec2f(ofxLUT::*)(void)) &ofxLUT::getResolution)
         .def("getInternalFormat", (int(ofxLUT::*)(void)) &ofxLUT::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxLUT::*)(void)) &ofxLUT::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxLUT::*)(void)) &ofxLUT::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxLUT::*)(void)) &ofxLUT::getTextureReference)
         .def("clear", (void(ofxLUT::*)(int)) &ofxLUT::clear)
         .def("update", (void(ofxLUT::*)(void)) &ofxLUT::update)
         .def("draw", (void(ofxLUT::*)(ofRectangle&)) &ofxLUT::draw)
         .def("draw", (void(ofxLUT::*)(int,int,float,float)) &ofxLUT::draw)
         
         .def("loadLUT", (bool(ofxLUT::*)(ofBuffer&)) &ofxLUT::loadLUT)
         .def("loadLUT", (bool(ofxLUT::*)(string)) &ofxLUT::loadLUT),
         
         class_<ofxMedian>("ofxMedian")
         .def(constructor<>())
         .def("allocate", (void(ofxMedian::*)(int,int,int)) &ofxMedian::allocate)
         .def("allocate", (void(ofxMedian::*)(int,int)) &ofxMedian::allocate)
         .def("set", (void(ofxMedian::*)(ofRectangle const&)) &ofxMedian::set)
         .def("setCode", (bool(ofxMedian::*)(string)) &ofxMedian::setCode)
         .def("load", (bool(ofxMedian::*)(string)) &ofxMedian::load)
         .def("compileCode", (bool(ofxMedian::*)(void)) &ofxMedian::compileCode)
         .def("setPasses", (void(ofxMedian::*)(int)) &ofxMedian::setPasses)
         .def("setInternalFormat", (void(ofxMedian::*)(int)) &ofxMedian::setInternalFormat)
         .def("setTexture", (void(ofxMedian::*)(ofTexture&,int)) &ofxMedian::setTexture)
         .def("beginFx", (void(ofxMedian::*)(int)) &ofxMedian::begin)
         .def("endFx", (void(ofxMedian::*)(int)) &ofxMedian::end)
         .def("compiled", (bool(ofxMedian::*)(void)) &ofxMedian::compiled)
         .def("getCode", (string(ofxMedian::*)(void)) &ofxMedian::getCode)
         .def("getWidth", (float(ofxMedian::*)(void)) &ofxMedian::getWidth)
         .def("getHeight", (float(ofxMedian::*)(void)) &ofxMedian::getHeight)
         .def("getPasses", (int(ofxMedian::*)(void)) &ofxMedian::getPasses)
         .def("getResolution", (ofVec2f(ofxMedian::*)(void)) &ofxMedian::getResolution)
         .def("getInternalFormat", (int(ofxMedian::*)(void)) &ofxMedian::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxMedian::*)(void)) &ofxMedian::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxMedian::*)(void)) &ofxMedian::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxMedian::*)(void)) &ofxMedian::getTextureReference)
         .def("clear", (void(ofxMedian::*)(int)) &ofxMedian::clear)
         .def("update", (void(ofxMedian::*)(void)) &ofxMedian::update)
         .def("draw", (void(ofxMedian::*)(ofRectangle&)) &ofxMedian::draw)
         .def("draw", (void(ofxMedian::*)(int,int,float,float)) &ofxMedian::draw)
         
         .def_readwrite("radius", &ofxMedian::radius),
         
         class_<ofxOldTv>("ofxOldTv")
         .def(constructor<>())
         .def("allocate", (void(ofxOldTv::*)(int,int,int)) &ofxOldTv::allocate)
         .def("allocate", (void(ofxOldTv::*)(int,int)) &ofxOldTv::allocate)
         .def("set", (void(ofxOldTv::*)(ofRectangle const&)) &ofxOldTv::set)
         .def("setCode", (bool(ofxOldTv::*)(string)) &ofxOldTv::setCode)
         .def("load", (bool(ofxOldTv::*)(string)) &ofxOldTv::load)
         .def("compileCode", (bool(ofxOldTv::*)(void)) &ofxOldTv::compileCode)
         .def("setPasses", (void(ofxOldTv::*)(int)) &ofxOldTv::setPasses)
         .def("setInternalFormat", (void(ofxOldTv::*)(int)) &ofxOldTv::setInternalFormat)
         .def("setTexture", (void(ofxOldTv::*)(ofTexture&,int)) &ofxOldTv::setTexture)
         .def("beginFx", (void(ofxOldTv::*)(int)) &ofxOldTv::begin)
         .def("endFx", (void(ofxOldTv::*)(int)) &ofxOldTv::end)
         .def("compiled", (bool(ofxOldTv::*)(void)) &ofxOldTv::compiled)
         .def("getCode", (string(ofxOldTv::*)(void)) &ofxOldTv::getCode)
         .def("getWidth", (float(ofxOldTv::*)(void)) &ofxOldTv::getWidth)
         .def("getHeight", (float(ofxOldTv::*)(void)) &ofxOldTv::getHeight)
         .def("getPasses", (int(ofxOldTv::*)(void)) &ofxOldTv::getPasses)
         .def("getResolution", (ofVec2f(ofxOldTv::*)(void)) &ofxOldTv::getResolution)
         .def("getInternalFormat", (int(ofxOldTv::*)(void)) &ofxOldTv::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxOldTv::*)(void)) &ofxOldTv::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxOldTv::*)(void)) &ofxOldTv::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxOldTv::*)(void)) &ofxOldTv::getTextureReference)
         .def("clear", (void(ofxOldTv::*)(int)) &ofxOldTv::clear)
         .def("update", (void(ofxOldTv::*)(void)) &ofxOldTv::update)
         .def("draw", (void(ofxOldTv::*)(ofRectangle&)) &ofxOldTv::draw)
         .def("draw", (void(ofxOldTv::*)(int,int,float,float)) &ofxOldTv::draw)
         
         .def_readwrite("brightness", &ofxOldTv::brightness)
         .def_readwrite("rowsSize", &ofxOldTv::rowsSize)
         .def_readwrite("colorTint", &ofxOldTv::colorTint),
         
         class_<ofxFire>("ofxFire")
         .def(constructor<>())
         .def("allocate", (void(ofxFire::*)(int,int,int)) &ofxFire::allocate)
         .def("allocate", (void(ofxFire::*)(int,int)) &ofxFire::allocate)
         .def("set", (void(ofxFire::*)(ofRectangle const&)) &ofxFire::set)
         .def("setCode", (bool(ofxFire::*)(string)) &ofxFire::setCode)
         .def("load", (bool(ofxFire::*)(string)) &ofxFire::load)
         .def("compileCode", (bool(ofxFire::*)(void)) &ofxFire::compileCode)
         .def("setPasses", (void(ofxFire::*)(int)) &ofxFire::setPasses)
         .def("setInternalFormat", (void(ofxFire::*)(int)) &ofxFire::setInternalFormat)
         .def("setTexture", (void(ofxFire::*)(ofTexture&,int)) &ofxFire::setTexture)
         .def("beginFx", (void(ofxFire::*)(int)) &ofxFire::begin)
         .def("endFx", (void(ofxFire::*)(int)) &ofxFire::end)
         .def("compiled", (bool(ofxFire::*)(void)) &ofxFire::compiled)
         .def("getCode", (string(ofxFire::*)(void)) &ofxFire::getCode)
         .def("getWidth", (float(ofxFire::*)(void)) &ofxFire::getWidth)
         .def("getHeight", (float(ofxFire::*)(void)) &ofxFire::getHeight)
         .def("getPasses", (int(ofxFire::*)(void)) &ofxFire::getPasses)
         .def("getResolution", (ofVec2f(ofxFire::*)(void)) &ofxFire::getResolution)
         .def("getInternalFormat", (int(ofxFire::*)(void)) &ofxFire::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxFire::*)(void)) &ofxFire::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxFire::*)(void)) &ofxFire::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxFire::*)(void)) &ofxFire::getTextureReference)
         .def("clear", (void(ofxFire::*)(int)) &ofxFire::clear)
         .def("update", (void(ofxFire::*)(void)) &ofxFire::update)
         .def("draw", (void(ofxFire::*)(ofRectangle&)) &ofxFire::draw)
         .def("draw", (void(ofxFire::*)(int,int,float,float)) &ofxFire::draw)
         
         .def("setZoom", (void(ofxFire::*)(float)) &ofxFire::setZoom)
         .def("clear", (void(ofxFire::*)(void)) &ofxFire::clear),
         
         class_<ofxGrayScott>("ofxGrayScott")
         .def(constructor<>())
         .def("allocate", (void(ofxGrayScott::*)(int,int,int)) &ofxGrayScott::allocate)
         .def("allocate", (void(ofxGrayScott::*)(int,int)) &ofxGrayScott::allocate)
         .def("set", (void(ofxGrayScott::*)(ofRectangle const&)) &ofxGrayScott::set)
         .def("setCode", (bool(ofxGrayScott::*)(string)) &ofxGrayScott::setCode)
         .def("load", (bool(ofxGrayScott::*)(string)) &ofxGrayScott::load)
         .def("compileCode", (bool(ofxGrayScott::*)(void)) &ofxGrayScott::compileCode)
         .def("setPasses", (void(ofxGrayScott::*)(int)) &ofxGrayScott::setPasses)
         .def("setInternalFormat", (void(ofxGrayScott::*)(int)) &ofxGrayScott::setInternalFormat)
         .def("setTexture", (void(ofxGrayScott::*)(ofTexture&,int)) &ofxGrayScott::setTexture)
         .def("beginFx", (void(ofxGrayScott::*)(int)) &ofxGrayScott::begin)
         .def("endFx", (void(ofxGrayScott::*)(int)) &ofxGrayScott::end)
         .def("compiled", (bool(ofxGrayScott::*)(void)) &ofxGrayScott::compiled)
         .def("getCode", (string(ofxGrayScott::*)(void)) &ofxGrayScott::getCode)
         .def("getWidth", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getWidth)
         .def("getHeight", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getHeight)
         .def("getPasses", (int(ofxGrayScott::*)(void)) &ofxGrayScott::getPasses)
         .def("getResolution", (ofVec2f(ofxGrayScott::*)(void)) &ofxGrayScott::getResolution)
         .def("getInternalFormat", (int(ofxGrayScott::*)(void)) &ofxGrayScott::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxGrayScott::*)(void)) &ofxGrayScott::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxGrayScott::*)(void)) &ofxGrayScott::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxGrayScott::*)(void)) &ofxGrayScott::getTextureReference)
         .def("clear", (void(ofxGrayScott::*)(int)) &ofxGrayScott::clear)
         .def("update", (void(ofxGrayScott::*)(void)) &ofxGrayScott::update)
         .def("draw", (void(ofxGrayScott::*)(ofRectangle&)) &ofxGrayScott::draw)
         .def("draw", (void(ofxGrayScott::*)(int,int,float,float)) &ofxGrayScott::draw)
         .def("setPasses", (ofxGrayScott&(ofxGrayScott::*)(int)) &ofxGrayScott::setPasses)
         .def("setDiffU", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setDiffU)
         .def("setDiffV", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setDiffV)
         .def("setK", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setK)
         .def("setF", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setF)
         
         .def("getDiffU", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getDiffU)
         .def("getDiffV", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getDiffV)
         .def("getK", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getK)
         .def("getF", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getF),
         
         class_<ofxNoise>("ofxNoise")
         .def(constructor<>())
         .def("allocate", (void(ofxNoise::*)(int,int,int)) &ofxNoise::allocate)
         .def("allocate", (void(ofxNoise::*)(int,int)) &ofxNoise::allocate)
         .def("set", (void(ofxNoise::*)(ofRectangle const&)) &ofxNoise::set)
         .def("setCode", (bool(ofxNoise::*)(string)) &ofxNoise::setCode)
         .def("load", (bool(ofxNoise::*)(string)) &ofxNoise::load)
         .def("compileCode", (bool(ofxNoise::*)(void)) &ofxNoise::compileCode)
         .def("setPasses", (void(ofxNoise::*)(int)) &ofxNoise::setPasses)
         .def("setInternalFormat", (void(ofxNoise::*)(int)) &ofxNoise::setInternalFormat)
         .def("setTexture", (void(ofxNoise::*)(ofTexture&,int)) &ofxNoise::setTexture)
         .def("beginFx", (void(ofxNoise::*)(int)) &ofxNoise::begin)
         .def("endFx", (void(ofxNoise::*)(int)) &ofxNoise::end)
         .def("compiled", (bool(ofxNoise::*)(void)) &ofxNoise::compiled)
         .def("getCode", (string(ofxNoise::*)(void)) &ofxNoise::getCode)
         .def("getWidth", (float(ofxNoise::*)(void)) &ofxNoise::getWidth)
         .def("getHeight", (float(ofxNoise::*)(void)) &ofxNoise::getHeight)
         .def("getPasses", (int(ofxNoise::*)(void)) &ofxNoise::getPasses)
         .def("getResolution", (ofVec2f(ofxNoise::*)(void)) &ofxNoise::getResolution)
         .def("getInternalFormat", (int(ofxNoise::*)(void)) &ofxNoise::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxNoise::*)(void)) &ofxNoise::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxNoise::*)(void)) &ofxNoise::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxNoise::*)(void)) &ofxNoise::getTextureReference)
         .def("clear", (void(ofxNoise::*)(int)) &ofxNoise::clear)
         .def("update", (void(ofxNoise::*)(void)) &ofxNoise::update)
         .def("draw", (void(ofxNoise::*)(ofRectangle&)) &ofxNoise::draw)
         .def("draw", (void(ofxNoise::*)(int,int,float,float)) &ofxNoise::draw)
         
         .def("setZoom", (void(ofxNoise::*)(float)) &ofxNoise::setZoom)
         .def("clear", (void(ofxNoise::*)(void)) &ofxNoise::clear),
         
         class_<ofxTint>("ofxTint")
         .def(constructor<>())
         .def("allocate", (void(ofxTint::*)(int,int,int)) &ofxTint::allocate)
         .def("allocate", (void(ofxTint::*)(int,int)) &ofxTint::allocate)
         .def("set", (void(ofxTint::*)(ofRectangle const&)) &ofxTint::set)
         .def("setCode", (bool(ofxTint::*)(string)) &ofxTint::setCode)
         .def("load", (bool(ofxTint::*)(string)) &ofxTint::load)
         .def("compileCode", (bool(ofxTint::*)(void)) &ofxTint::compileCode)
         .def("setPasses", (void(ofxTint::*)(int)) &ofxTint::setPasses)
         .def("setInternalFormat", (void(ofxTint::*)(int)) &ofxTint::setInternalFormat)
         .def("setTexture", (void(ofxTint::*)(ofTexture&,int)) &ofxTint::setTexture)
         .def("beginFx", (void(ofxTint::*)(int)) &ofxTint::begin)
         .def("endFx", (void(ofxTint::*)(int)) &ofxTint::end)
         .def("compiled", (bool(ofxTint::*)(void)) &ofxTint::compiled)
         .def("getCode", (string(ofxTint::*)(void)) &ofxTint::getCode)
         .def("getWidth", (float(ofxTint::*)(void)) &ofxTint::getWidth)
         .def("getHeight", (float(ofxTint::*)(void)) &ofxTint::getHeight)
         .def("getPasses", (int(ofxTint::*)(void)) &ofxTint::getPasses)
         .def("getResolution", (ofVec2f(ofxTint::*)(void)) &ofxTint::getResolution)
         .def("getInternalFormat", (int(ofxTint::*)(void)) &ofxTint::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxTint::*)(void)) &ofxTint::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxTint::*)(void)) &ofxTint::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxTint::*)(void)) &ofxTint::getTextureReference)
         .def("clear", (void(ofxTint::*)(int)) &ofxTint::clear)
         .def("update", (void(ofxTint::*)(void)) &ofxTint::update)
         .def("draw", (void(ofxTint::*)(ofRectangle&)) &ofxTint::draw)
         .def("draw", (void(ofxTint::*)(int,int,float,float)) &ofxTint::draw)
         
         .def("setZoom", (void(ofxTint::*)(float)) &ofxTint::setZoom)
         .def("setFade", (void(ofxTint::*)(float)) &ofxTint::setFade)
         .def("clear", (void(ofxTint::*)(void)) &ofxTint::clear),
         
         class_<ofxFlocking>("ofxFlocking")
         .def(constructor<>())
         .def("allocate", (void(ofxFlocking::*)(int,int,int)) &ofxFlocking::allocate)
         .def("allocate", (void(ofxFlocking::*)(int,int)) &ofxFlocking::allocate)
         .def("set", (void(ofxFlocking::*)(ofRectangle const&)) &ofxFlocking::set)
         .def("setCode", (bool(ofxFlocking::*)(string)) &ofxFlocking::setCode)
         .def("load", (bool(ofxFlocking::*)(string)) &ofxFlocking::load)
         .def("compileCode", (bool(ofxFlocking::*)(void)) &ofxFlocking::compileCode)
         .def("setPasses", (void(ofxFlocking::*)(int)) &ofxFlocking::setPasses)
         .def("setInternalFormat", (void(ofxFlocking::*)(int)) &ofxFlocking::setInternalFormat)
         .def("setTexture", (void(ofxFlocking::*)(ofTexture&,int)) &ofxFlocking::setTexture)
         .def("beginFx", (void(ofxFlocking::*)(int)) &ofxFlocking::begin)
         .def("endFx", (void(ofxFlocking::*)(int)) &ofxFlocking::end)
         .def("compiled", (bool(ofxFlocking::*)(void)) &ofxFlocking::compiled)
         .def("getCode", (string(ofxFlocking::*)(void)) &ofxFlocking::getCode)
         .def("getWidth", (float(ofxFlocking::*)(void)) &ofxFlocking::getWidth)
         .def("getHeight", (float(ofxFlocking::*)(void)) &ofxFlocking::getHeight)
         .def("getPasses", (int(ofxFlocking::*)(void)) &ofxFlocking::getPasses)
         .def("getResolution", (ofVec2f(ofxFlocking::*)(void)) &ofxFlocking::getResolution)
         .def("getInternalFormat", (int(ofxFlocking::*)(void)) &ofxFlocking::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxFlocking::*)(void)) &ofxFlocking::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxFlocking::*)(void)) &ofxFlocking::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxFlocking::*)(void)) &ofxFlocking::getTextureReference)
         .def("clear", (void(ofxFlocking::*)(int)) &ofxFlocking::clear)
         .def("update", (void(ofxFlocking::*)(void)) &ofxFlocking::update)
         .def("draw", (void(ofxFlocking::*)(ofRectangle&)) &ofxFlocking::draw)
         .def("draw", (void(ofxFlocking::*)(int,int,float,float)) &ofxFlocking::draw)
         
         .def("setParticleSize", (ofxFlocking&(ofxFlocking::*)(float)) &ofxFlocking::setParticleSize)
         .def("setTimpeStep", (ofxFlocking&(ofxFlocking::*)(float)) &ofxFlocking::setTimpeStep),
         
         class_<ofxFluid>("ofxFluid")
         .def(constructor<>())
         .def("allocate", (void(ofxFluid::*)(int,int,int)) &ofxFluid::allocate)
         .def("allocate", (void(ofxFluid::*)(int,int)) &ofxFluid::allocate)
         .def("set", (void(ofxFluid::*)(ofRectangle const&)) &ofxFluid::set)
         .def("setCode", (bool(ofxFluid::*)(string)) &ofxFluid::setCode)
         .def("load", (bool(ofxFluid::*)(string)) &ofxFluid::load)
         .def("compileCode", (bool(ofxFluid::*)(void)) &ofxFluid::compileCode)
         .def("setPasses", (void(ofxFluid::*)(int)) &ofxFluid::setPasses)
         .def("setInternalFormat", (void(ofxFluid::*)(int)) &ofxFluid::setInternalFormat)
         .def("setTexture", (void(ofxFluid::*)(ofTexture&,int)) &ofxFluid::setTexture)
         .def("beginFx", (void(ofxFluid::*)(int)) &ofxFluid::begin)
         .def("endFx", (void(ofxFluid::*)(int)) &ofxFluid::end)
         .def("compiled", (bool(ofxFluid::*)(void)) &ofxFluid::compiled)
         .def("getCode", (string(ofxFluid::*)(void)) &ofxFluid::getCode)
         .def("getWidth", (float(ofxFluid::*)(void)) &ofxFluid::getWidth)
         .def("getHeight", (float(ofxFluid::*)(void)) &ofxFluid::getHeight)
         .def("getPasses", (int(ofxFluid::*)(void)) &ofxFluid::getPasses)
         .def("getResolution", (ofVec2f(ofxFluid::*)(void)) &ofxFluid::getResolution)
         .def("getInternalFormat", (int(ofxFluid::*)(void)) &ofxFluid::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxFluid::*)(void)) &ofxFluid::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxFluid::*)(void)) &ofxFluid::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxFluid::*)(void)) &ofxFluid::getTextureReference)
         .def("clear", (void(ofxFluid::*)(int)) &ofxFluid::clear)
         .def("update", (void(ofxFluid::*)(void)) &ofxFluid::update)
         .def("draw", (void(ofxFluid::*)(ofRectangle&)) &ofxFluid::draw)
         .def("draw", (void(ofxFluid::*)(int,int,float,float)) &ofxFluid::draw)
         
         .def("setTexture", (void(ofxFluid::*)(ofTexture&)) &ofxFluid::setTexture)
         .def("setVelocity", (void(ofxFluid::*)(ofTexture&)) &ofxFluid::setVelocity)
         .def("setTemperature", (void(ofxFluid::*)(ofTexture&)) &ofxFluid::setTemperature)
         .def("setGravity", (void(ofxFluid::*)(ofPoint)) &ofxFluid::setGravity)
         
         .def("allocate", (void(ofxFluid::*)(int,int,float)) &ofxFluid::allocate)
         .def("addTemporalForce", (void(ofxFluid::*)(ofPoint,ofPoint,ofFloatColor,float,float,float)) &ofxFluid::addTemporalForce)
         .def("addConstantForce", (void(ofxFluid::*)(ofPoint,ofPoint,ofFloatColor,float,float,float)) &ofxFluid::addConstantForce)
         .def_readwrite("dissipation", &ofxFluid::dissipation)
         .def_readwrite("velocityDissipation", &ofxFluid::velocityDissipation)
         .def_readwrite("temperatureDissipation", &ofxFluid::temperatureDissipation)
         .def_readwrite("pressureDissipation", &ofxFluid::pressureDissipation),
         
         class_<ofxBounce>("ofxBounce")
         .def(constructor<>())
         .def("allocate", (void(ofxBounce::*)(int,int,int)) &ofxBounce::allocate)
         .def("allocate", (void(ofxBounce::*)(int,int)) &ofxBounce::allocate)
         .def("set", (void(ofxBounce::*)(ofRectangle const&)) &ofxBounce::set)
         .def("setCode", (bool(ofxBounce::*)(string)) &ofxBounce::setCode)
         .def("load", (bool(ofxBounce::*)(string)) &ofxBounce::load)
         .def("compileCode", (bool(ofxBounce::*)(void)) &ofxBounce::compileCode)
         .def("setPasses", (void(ofxBounce::*)(int)) &ofxBounce::setPasses)
         .def("setInternalFormat", (void(ofxBounce::*)(int)) &ofxBounce::setInternalFormat)
         .def("setTexture", (void(ofxBounce::*)(ofTexture&,int)) &ofxBounce::setTexture)
         .def("beginFx", (void(ofxBounce::*)(int)) &ofxBounce::begin)
         .def("endFx", (void(ofxBounce::*)(int)) &ofxBounce::end)
         .def("compiled", (bool(ofxBounce::*)(void)) &ofxBounce::compiled)
         .def("getCode", (string(ofxBounce::*)(void)) &ofxBounce::getCode)
         .def("getWidth", (float(ofxBounce::*)(void)) &ofxBounce::getWidth)
         .def("getHeight", (float(ofxBounce::*)(void)) &ofxBounce::getHeight)
         .def("getPasses", (int(ofxBounce::*)(void)) &ofxBounce::getPasses)
         .def("getResolution", (ofVec2f(ofxBounce::*)(void)) &ofxBounce::getResolution)
         .def("getInternalFormat", (int(ofxBounce::*)(void)) &ofxBounce::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxBounce::*)(void)) &ofxBounce::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxBounce::*)(void)) &ofxBounce::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxBounce::*)(void)) &ofxBounce::getTextureReference)
         .def("clear", (void(ofxBounce::*)(int)) &ofxBounce::clear)
         .def("update", (void(ofxBounce::*)(void)) &ofxBounce::update)
         .def("draw", (void(ofxBounce::*)(ofRectangle&)) &ofxBounce::draw)
         .def("draw", (void(ofxBounce::*)(int,int,float,float)) &ofxBounce::draw),
         
         class_<ofxDisplacePixels>("ofxDisplacePixels")
         .def(constructor<>())
         .def("allocate", (void(ofxDisplacePixels::*)(int,int,int)) &ofxDisplacePixels::allocate)
         .def("allocate", (void(ofxDisplacePixels::*)(int,int)) &ofxDisplacePixels::allocate)
         .def("set", (void(ofxDisplacePixels::*)(ofRectangle const&)) &ofxDisplacePixels::set)
         .def("setCode", (bool(ofxDisplacePixels::*)(string)) &ofxDisplacePixels::setCode)
         .def("load", (bool(ofxDisplacePixels::*)(string)) &ofxDisplacePixels::load)
         .def("compileCode", (bool(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::compileCode)
         .def("setPasses", (void(ofxDisplacePixels::*)(int)) &ofxDisplacePixels::setPasses)
         .def("setInternalFormat", (void(ofxDisplacePixels::*)(int)) &ofxDisplacePixels::setInternalFormat)
         .def("setTexture", (void(ofxDisplacePixels::*)(ofTexture&,int)) &ofxDisplacePixels::setTexture)
         .def("beginFx", (void(ofxDisplacePixels::*)(int)) &ofxDisplacePixels::begin)
         .def("endFx", (void(ofxDisplacePixels::*)(int)) &ofxDisplacePixels::end)
         .def("compiled", (bool(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::compiled)
         .def("getCode", (string(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getCode)
         .def("getWidth", (float(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getWidth)
         .def("getHeight", (float(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getHeight)
         .def("getPasses", (int(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getPasses)
         .def("getResolution", (ofVec2f(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getResolution)
         .def("getInternalFormat", (int(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::getTextureReference)
         .def("clear", (void(ofxDisplacePixels::*)(int)) &ofxDisplacePixels::clear)
         .def("update", (void(ofxDisplacePixels::*)(void)) &ofxDisplacePixels::update)
         .def("draw", (void(ofxDisplacePixels::*)(ofRectangle&)) &ofxDisplacePixels::draw)
         .def("draw", (void(ofxDisplacePixels::*)(int,int,float,float)) &ofxDisplacePixels::draw),
         
         class_<ofxNormals>("ofxNormals")
         .def(constructor<>())
         .def("allocate", (void(ofxNormals::*)(int,int,int)) &ofxNormals::allocate)
         .def("allocate", (void(ofxNormals::*)(int,int)) &ofxNormals::allocate)
         .def("set", (void(ofxNormals::*)(ofRectangle const&)) &ofxNormals::set)
         .def("setCode", (bool(ofxNormals::*)(string)) &ofxNormals::setCode)
         .def("load", (bool(ofxNormals::*)(string)) &ofxNormals::load)
         .def("compileCode", (bool(ofxNormals::*)(void)) &ofxNormals::compileCode)
         .def("setPasses", (void(ofxNormals::*)(int)) &ofxNormals::setPasses)
         .def("setInternalFormat", (void(ofxNormals::*)(int)) &ofxNormals::setInternalFormat)
         .def("setTexture", (void(ofxNormals::*)(ofTexture&,int)) &ofxNormals::setTexture)
         .def("beginFx", (void(ofxNormals::*)(int)) &ofxNormals::begin)
         .def("endFx", (void(ofxNormals::*)(int)) &ofxNormals::end)
         .def("compiled", (bool(ofxNormals::*)(void)) &ofxNormals::compiled)
         .def("getCode", (string(ofxNormals::*)(void)) &ofxNormals::getCode)
         .def("getWidth", (float(ofxNormals::*)(void)) &ofxNormals::getWidth)
         .def("getHeight", (float(ofxNormals::*)(void)) &ofxNormals::getHeight)
         .def("getPasses", (int(ofxNormals::*)(void)) &ofxNormals::getPasses)
         .def("getResolution", (ofVec2f(ofxNormals::*)(void)) &ofxNormals::getResolution)
         .def("getInternalFormat", (int(ofxNormals::*)(void)) &ofxNormals::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxNormals::*)(void)) &ofxNormals::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxNormals::*)(void)) &ofxNormals::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxNormals::*)(void)) &ofxNormals::getTextureReference)
         .def("clear", (void(ofxNormals::*)(int)) &ofxNormals::clear)
         .def("update", (void(ofxNormals::*)(void)) &ofxNormals::update)
         .def("draw", (void(ofxNormals::*)(ofRectangle&)) &ofxNormals::draw)
         .def("draw", (void(ofxNormals::*)(int,int,float,float)) &ofxNormals::draw),
         
         class_<ofxRipples>("ofxRipples")
         .def(constructor<>())
         .def("allocate", (void(ofxRipples::*)(int,int,int)) &ofxRipples::allocate)
         .def("allocate", (void(ofxRipples::*)(int,int)) &ofxRipples::allocate)
         .def("set", (void(ofxRipples::*)(ofRectangle const&)) &ofxRipples::set)
         .def("setCode", (bool(ofxRipples::*)(string)) &ofxRipples::setCode)
         .def("load", (bool(ofxRipples::*)(string)) &ofxRipples::load)
         .def("compileCode", (bool(ofxRipples::*)(void)) &ofxRipples::compileCode)
         .def("setPasses", (void(ofxRipples::*)(int)) &ofxRipples::setPasses)
         .def("setInternalFormat", (void(ofxRipples::*)(int)) &ofxRipples::setInternalFormat)
         .def("setTexture", (void(ofxRipples::*)(ofTexture&,int)) &ofxRipples::setTexture)
         .def("beginFx", (void(ofxRipples::*)(int)) &ofxRipples::begin)
         .def("endFx", (void(ofxRipples::*)(int)) &ofxRipples::end)
         .def("compiled", (bool(ofxRipples::*)(void)) &ofxRipples::compiled)
         .def("getCode", (string(ofxRipples::*)(void)) &ofxRipples::getCode)
         .def("getWidth", (float(ofxRipples::*)(void)) &ofxRipples::getWidth)
         .def("getHeight", (float(ofxRipples::*)(void)) &ofxRipples::getHeight)
         .def("getPasses", (int(ofxRipples::*)(void)) &ofxRipples::getPasses)
         .def("getResolution", (ofVec2f(ofxRipples::*)(void)) &ofxRipples::getResolution)
         .def("getInternalFormat", (int(ofxRipples::*)(void)) &ofxRipples::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxRipples::*)(void)) &ofxRipples::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxRipples::*)(void)) &ofxRipples::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxRipples::*)(void)) &ofxRipples::getTextureReference)
         .def("clear", (void(ofxRipples::*)(int)) &ofxRipples::clear)
         .def("update", (void(ofxRipples::*)(void)) &ofxRipples::update)
         .def("draw", (void(ofxRipples::*)(ofRectangle&)) &ofxRipples::draw)
         .def("draw", (void(ofxRipples::*)(int,int,float,float)) &ofxRipples::draw)
         
         .def("beginFx", (void(ofxRipples::*)(void)) &ofxRipples::begin)
         .def("endFx", (void(ofxRipples::*)(void)) &ofxRipples::end)
         .def_readwrite("damping", &ofxRipples::damping),
         
         class_<ofxThreshold>("ofxThreshold")
         .def(constructor<>())
         .def("allocate", (void(ofxThreshold::*)(int,int,int)) &ofxThreshold::allocate)
         .def("allocate", (void(ofxThreshold::*)(int,int)) &ofxThreshold::allocate)
         .def("set", (void(ofxThreshold::*)(ofRectangle const&)) &ofxThreshold::set)
         .def("setCode", (bool(ofxThreshold::*)(string)) &ofxThreshold::setCode)
         .def("load", (bool(ofxThreshold::*)(string)) &ofxThreshold::load)
         .def("compileCode", (bool(ofxThreshold::*)(void)) &ofxThreshold::compileCode)
         .def("setPasses", (void(ofxThreshold::*)(int)) &ofxThreshold::setPasses)
         .def("setInternalFormat", (void(ofxThreshold::*)(int)) &ofxThreshold::setInternalFormat)
         .def("setTexture", (void(ofxThreshold::*)(ofTexture&,int)) &ofxThreshold::setTexture)
         .def("beginFx", (void(ofxThreshold::*)(int)) &ofxThreshold::begin)
         .def("endFx", (void(ofxThreshold::*)(int)) &ofxThreshold::end)
         .def("compiled", (bool(ofxThreshold::*)(void)) &ofxThreshold::compiled)
         .def("getCode", (string(ofxThreshold::*)(void)) &ofxThreshold::getCode)
         .def("getWidth", (float(ofxThreshold::*)(void)) &ofxThreshold::getWidth)
         .def("getHeight", (float(ofxThreshold::*)(void)) &ofxThreshold::getHeight)
         .def("getPasses", (int(ofxThreshold::*)(void)) &ofxThreshold::getPasses)
         .def("getResolution", (ofVec2f(ofxThreshold::*)(void)) &ofxThreshold::getResolution)
         .def("getInternalFormat", (int(ofxThreshold::*)(void)) &ofxThreshold::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxThreshold::*)(void)) &ofxThreshold::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxThreshold::*)(void)) &ofxThreshold::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxThreshold::*)(void)) &ofxThreshold::getTextureReference)
         .def("clear", (void(ofxThreshold::*)(int)) &ofxThreshold::clear)
         .def("update", (void(ofxThreshold::*)(void)) &ofxThreshold::update)
         .def("draw", (void(ofxThreshold::*)(ofRectangle&)) &ofxThreshold::draw)
         .def("draw", (void(ofxThreshold::*)(int,int,float,float)) &ofxThreshold::draw)
         
         .def_readwrite("threshold", &ofxThreshold::threshold),
         
         class_<ofxRotate>("ofxRotate")
         .def(constructor<>())
         .def("allocate", (void(ofxRotate::*)(int,int,int)) &ofxRotate::allocate)
         .def("allocate", (void(ofxRotate::*)(int,int)) &ofxRotate::allocate)
         .def("set", (void(ofxRotate::*)(ofRectangle const&)) &ofxRotate::set)
         .def("setCode", (bool(ofxRotate::*)(string)) &ofxRotate::setCode)
         .def("load", (bool(ofxRotate::*)(string)) &ofxRotate::load)
         .def("compileCode", (bool(ofxRotate::*)(void)) &ofxRotate::compileCode)
         .def("setPasses", (void(ofxRotate::*)(int)) &ofxRotate::setPasses)
         .def("setInternalFormat", (void(ofxRotate::*)(int)) &ofxRotate::setInternalFormat)
         .def("setTexture", (void(ofxRotate::*)(ofTexture&,int)) &ofxRotate::setTexture)
         .def("beginFx", (void(ofxRotate::*)(int)) &ofxRotate::begin)
         .def("endFx", (void(ofxRotate::*)(int)) &ofxRotate::end)
         .def("compiled", (bool(ofxRotate::*)(void)) &ofxRotate::compiled)
         .def("getCode", (string(ofxRotate::*)(void)) &ofxRotate::getCode)
         .def("getWidth", (float(ofxRotate::*)(void)) &ofxRotate::getWidth)
         .def("getHeight", (float(ofxRotate::*)(void)) &ofxRotate::getHeight)
         .def("getPasses", (int(ofxRotate::*)(void)) &ofxRotate::getPasses)
         .def("getResolution", (ofVec2f(ofxRotate::*)(void)) &ofxRotate::getResolution)
         .def("getInternalFormat", (int(ofxRotate::*)(void)) &ofxRotate::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxRotate::*)(void)) &ofxRotate::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxRotate::*)(void)) &ofxRotate::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxRotate::*)(void)) &ofxRotate::getTextureReference)
         .def("clear", (void(ofxRotate::*)(int)) &ofxRotate::clear)
         .def("update", (void(ofxRotate::*)(void)) &ofxRotate::update)
         .def("draw", (void(ofxRotate::*)(ofRectangle&)) &ofxRotate::draw)
         .def("draw", (void(ofxRotate::*)(int,int,float,float)) &ofxRotate::draw)
         
         .def("setRotation", (void(ofxRotate::*)(float)) &ofxRotate::setRotation)
         .def_readwrite("angle", &ofxRotate::angle),
         
         class_<ofxKaleidoscope>("ofxKaleidoscope")
         .def(constructor<>())
         .def("allocate", (void(ofxKaleidoscope::*)(int,int,int)) &ofxKaleidoscope::allocate)
         .def("allocate", (void(ofxKaleidoscope::*)(int,int)) &ofxKaleidoscope::allocate)
         .def("set", (void(ofxKaleidoscope::*)(ofRectangle const&)) &ofxKaleidoscope::set)
         .def("setCode", (bool(ofxKaleidoscope::*)(string)) &ofxKaleidoscope::setCode)
         .def("load", (bool(ofxKaleidoscope::*)(string)) &ofxKaleidoscope::load)
         .def("compileCode", (bool(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::compileCode)
         .def("setPasses", (void(ofxKaleidoscope::*)(int)) &ofxKaleidoscope::setPasses)
         .def("setInternalFormat", (void(ofxKaleidoscope::*)(int)) &ofxKaleidoscope::setInternalFormat)
         .def("setTexture", (void(ofxKaleidoscope::*)(ofTexture&,int)) &ofxKaleidoscope::setTexture)
         .def("beginFx", (void(ofxKaleidoscope::*)(int)) &ofxKaleidoscope::begin)
         .def("endFx", (void(ofxKaleidoscope::*)(int)) &ofxKaleidoscope::end)
         .def("compiled", (bool(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::compiled)
         .def("getCode", (string(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getCode)
         .def("getWidth", (float(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getWidth)
         .def("getHeight", (float(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getHeight)
         .def("getPasses", (int(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getPasses)
         .def("getResolution", (ofVec2f(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getResolution)
         .def("getInternalFormat", (int(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getInternalFormat)
         .def("getNumberOfCalledTextures", (int(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getNumberOfCalledTextures)
         .def("getBackBuffer", (ofFbo*(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getBackBuffer)
         .def("getTextureReference", (ofTexture&(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::getTextureReference)
         .def("clear", (void(ofxKaleidoscope::*)(int)) &ofxKaleidoscope::clear)
         .def("update", (void(ofxKaleidoscope::*)(void)) &ofxKaleidoscope::update)
         .def("draw", (void(ofxKaleidoscope::*)(ofRectangle&)) &ofxKaleidoscope::draw)
         .def("draw", (void(ofxKaleidoscope::*)(int,int,float,float)) &ofxKaleidoscope::draw)
         
         .def("setRotation", (void(ofxKaleidoscope::*)(float)) &ofxKaleidoscope::setRotation)
         .def("setFacesRotation", (void(ofxKaleidoscope::*)(float)) &ofxKaleidoscope::setFacesRotation)
         .def("setTotalFaces", (void(ofxKaleidoscope::*)(float)) &ofxKaleidoscope::setTotalFaces)
         .def_readwrite("angle", &ofxKaleidoscope::angle)
         .def_readwrite("offset", &ofxKaleidoscope::offset),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXGAMECAMERA
         class_<ofxGameCamera>("ofxGameCamera")
         .def(constructor<>())
         .def("setFov", (void(ofxGameCamera::*)(float)) &ofxGameCamera::setFov)
         .def("setNearClip", (void(ofxGameCamera::*)(float)) &ofxGameCamera::setNearClip)
		 .def("setFarClip", (void(ofxGameCamera::*)(float)) &ofxGameCamera::setFarClip)
         .def("setLensOffset", (void(ofxGameCamera::*)(const ofVec2f&)) &ofxGameCamera::setLensOffset)
         .def("setAspectRatio", (void(ofxGameCamera::*)(float)) &ofxGameCamera::setAspectRatio)
         .def("setForceAspectRatio", (void(ofxGameCamera::*)(bool)) &ofxGameCamera::setForceAspectRatio)
         .def("getFov", (const float(ofxGameCamera::*)(void)) &ofxGameCamera::getFov)
         .def("getNearClip", (const float(ofxGameCamera::*)(void)) &ofxGameCamera::getNearClip)
		 .def("getFarClip", (const float(ofxGameCamera::*)(void)) &ofxGameCamera::getFarClip)
         .def("getLensOffset", (const ofVec2f(ofxGameCamera::*)(void)) &ofxGameCamera::getLensOffset)
         .def("getForceAspectRatio", (const bool(ofxGameCamera::*)(void)) &ofxGameCamera::getForceAspectRatio)
         .def("getAspectRatio", (const float(ofxGameCamera::*)(void)) &ofxGameCamera::getAspectRatio)
         .def("setupPerspective", (void(ofxGameCamera::*)(bool,float,float,float,const ofVec2f&)) &ofxGameCamera::setupPerspective)
         .def("setupOffAxisViewPortal", (void(ofxGameCamera::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofxGameCamera::setupOffAxisViewPortal)
         .def("enableOrtho", (void(ofxGameCamera::*)(void)) &ofxGameCamera::enableOrtho)
         .def("disableOrtho", (void(ofxGameCamera::*)(void)) &ofxGameCamera::disableOrtho)
         .def("getOrtho", (bool(ofxGameCamera::*)(void)) &ofxGameCamera::getOrtho)
         .def("getModelViewMatrix", (ofMatrix4x4(ofxGameCamera::*)(void)) &ofxGameCamera::getModelViewMatrix)
         .def("setPosition", (void(ofxGameCamera::*)(float,float,float)) &ofxGameCamera::setPosition)
         .def("setPosition", (void(ofxGameCamera::*)(const ofVec3f&)) &ofxGameCamera::setPosition)
         .def("setScale", (void(ofxGameCamera::*)(float)) &ofxGameCamera::setScale)
         .def("setScale", (void(ofxGameCamera::*)(float,float,float)) &ofxGameCamera::setScale)
         .def("setScale", (void(ofxGameCamera::*)(const ofVec3f&)) &ofxGameCamera::setScale)
         .def("move", (void(ofxGameCamera::*)(float,float,float)) &ofxGameCamera::move)
         .def("move", (void(ofxGameCamera::*)(const ofVec3f&)) &ofxGameCamera::move)
         .def("truck", (void(ofxGameCamera::*)(float)) &ofxGameCamera::truck)
         .def("boom", (void(ofxGameCamera::*)(float)) &ofxGameCamera::boom)
         .def("dolly", (void(ofxGameCamera::*)(float)) &ofxGameCamera::dolly)
         .def("tilt", (void(ofxGameCamera::*)(float)) &ofxGameCamera::tilt)
         .def("pan", (void(ofxGameCamera::*)(float)) &ofxGameCamera::pan)
         .def("roll", (void(ofxGameCamera::*)(float)) &ofxGameCamera::roll)
         .def("rotate", (void(ofxGameCamera::*)(float,const ofVec3f&)) &ofxGameCamera::rotate)
         .def("rotate", (void(ofxGameCamera::*)(float,float,float,float)) &ofxGameCamera::rotate)
         .def("lookAt", (void(ofxGameCamera::*)(const ofVec3f&,ofVec3f)) &ofxGameCamera::lookAt)
         .def("orbit", (void(ofxGameCamera::*)(float,float,float,const ofVec3f&)) &ofxGameCamera::orbit)
         .def("transformGL", (void(ofxGameCamera::*)(void)) &ofxGameCamera::transformGL)
         .def("restoreTransformGL", (void(ofxGameCamera::*)(void)) &ofxGameCamera::restoreTransformGL)
         .def("resetTransform", (void(ofxGameCamera::*)(void)) &ofxGameCamera::resetTransform)
         .def("draw", (void(ofxGameCamera::*)(void)) &ofxGameCamera::draw)
         .def("getImagePlaneDistance", (float(ofxGameCamera::*)(ofRectangle)) &ofxGameCamera::getImagePlaneDistance)
         .def("getProjectionMatrix", (ofMatrix4x4(ofxGameCamera::*)(ofRectangle)) &ofxGameCamera::getProjectionMatrix)
         .def("getModelViewProjectionMatrix", (ofMatrix4x4(ofxGameCamera::*)(ofRectangle)) &ofxGameCamera::getModelViewProjectionMatrix)
         .def("worldToScreen", (ofVec3f(ofxGameCamera::*)(ofVec3f,ofRectangle)) &ofxGameCamera::worldToScreen)
         .def("screenToWorld", (ofVec3f(ofxGameCamera::*)(ofVec3f,ofRectangle)) &ofxGameCamera::screenToWorld)
         .def("worldToCamera", (ofVec3f(ofxGameCamera::*)(ofVec3f,ofRectangle)) &ofxGameCamera::worldToCamera)
         .def("cameraToWorld", (ofVec3f(ofxGameCamera::*)(ofVec3f,ofRectangle)) &ofxGameCamera::cameraToWorld)
         .def("beginCamera", (void(ofxGameCamera::*)(ofRectangle)) &ofxGameCamera::begin)
         .def("endCamera", (void(ofxGameCamera::*)(void)) &ofxGameCamera::end)
         
         .def("setup", (void(ofxGameCamera::*)(void)) &ofxGameCamera::setup)
         .def("updateRotation", (void(ofxGameCamera::*)(void)) &ofxGameCamera::updateRotation)
         .def("saveCameraPosition", (void(ofxGameCamera::*)(void)) &ofxGameCamera::saveCameraPosition)
         .def("loadCameraPosition", (void(ofxGameCamera::*)(void)) &ofxGameCamera::loadCameraPosition)
         .def("setAnglesFromOrientation", (void(ofxGameCamera::*)(void)) &ofxGameCamera::setAnglesFromOrientation)
         .def("reset", (void(ofxGameCamera::*)(void)) &ofxGameCamera::reset),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXGAUSSIAN
         def("ofxGaussian", (float(*)(void)) &ofxGaussian),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXGENERATIVE
         
         // ofx1DExtruder
         class_<ofx1DExtruder>("ofx1DExtruder")
         .def(constructor<>())
         .def(constructor<float>())
         .def("setPhysics", (void(ofx1DExtruder::*)(float,float,float)) &ofx1DExtruder::setPhysics)
         .def("setDamping", (void(ofx1DExtruder::*)(float)) &ofx1DExtruder::setDamping)
         .def("setAccLimit", (void(ofx1DExtruder::*)(float)) &ofx1DExtruder::setAccLimit)
         .def("setVelLimit", (void(ofx1DExtruder::*)(float)) &ofx1DExtruder::setVelLimit)
         .def("getDamping", (float(ofx1DExtruder::*)(void)) &ofx1DExtruder::getDamping)
         .def("getVelLimit", (float(ofx1DExtruder::*)(void)) &ofx1DExtruder::getVelLimit)
         .def("getAccLimit", (float(ofx1DExtruder::*)(void)) &ofx1DExtruder::getAccLimit)
         .def("update", (void(ofx1DExtruder::*)(void)) &ofx1DExtruder::update)
         .def("goHome", (float(ofx1DExtruder::*)(void)) &ofx1DExtruder::goHome)
         .def("draw", (void(ofx1DExtruder::*)(void)) &ofx1DExtruder::draw)
         .def("getPos", (float(ofx1DExtruder::*)(void)) &ofx1DExtruder::getPos)
         .def("setPos", (void(ofx1DExtruder::*)(float)) &ofx1DExtruder::setPos)
         .def("setHome", (void(ofx1DExtruder::*)(float)) &ofx1DExtruder::setHome)
         .def("getHome", (float(ofx1DExtruder::*)(void)) &ofx1DExtruder::getHome)
         .def("setPosAndHome", (void(ofx1DExtruder::*)(float)) &ofx1DExtruder::setPosAndHome)
         .def("addForce", (void(ofx1DExtruder::*)(float)) &ofx1DExtruder::addForce),
         
         // ofxBehavior
         class_<ofxBehavior>("ofxBehavior")
         .def(constructor<>())
         .def("update", (void(ofxBehavior::*)(void)) &ofxBehavior::update)
         .def("actUpon", (void(ofxBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxBehavior::actUpon)
         .def("isEnabled", (bool(ofxBehavior::*)(void)) &ofxBehavior::isEnabled)
         .def("getMagnitude", (float(ofxBehavior::*)(void)) &ofxBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxBehavior::*)(float)) &ofxBehavior::setMagnitude),
         
         // ofxBoidParticle
         class_<ofxBoidParticle>("ofxBoidParticle")
         .def(constructor<>())
         .def(constructor<ofVec3f>())
         .def("setBorders", (void(ofxBoidParticle::*)(float,float)) &ofxBoidParticle::setBorders)
         .def("update", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::update)
         .def("draw", (void(ofxBoidParticle::*)(void)) &ofxBoidParticle::draw)
         .def("drawVertex", (void(ofxBoidParticle::*)(void)) &ofxBoidParticle::drawVertex)
         .def("borders", (void(ofxBoidParticle::*)(void)) &ofxBoidParticle::borders)
         .def("elasticBorder", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::elasticBorder)
         .def("circleborders", (void(ofxBoidParticle::*)(void)) &ofxBoidParticle::circleborders)
         .def("setRadius", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::setRadius)
         .def("setPos", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::setPos)
         .def("setVel", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::setVel)
         .def("setAcc", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::setAcc)
         .def("setHome", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::setHome)
         .def("setHome", (void(ofxBoidParticle::*)(float,float,float)) &ofxBoidParticle::setHome)
         .def("setColor", (void(ofxBoidParticle::*)(ofColor)) &ofxBoidParticle::setColor)
         .def("setDamping", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::setDamping)
         .def("setAccerationLimit", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::setAccerationLimit)
         .def("setVelocityLimit", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::setVelocityLimit)
         .def("addExternalForce", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::addExternalForce)
         .def("addSpringForce", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::addSpringForce)
         .def("setFixed", (void(ofxBoidParticle::*)(bool)) &ofxBoidParticle::setFixed)
         .def("isFixed", (bool(ofxBoidParticle::*)(void)) &ofxBoidParticle::isFixed)
         .def("addForce", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::addForce)
         .def("getPos", (ofVec3f&(ofxBoidParticle::*)(void)) &ofxBoidParticle::getPos)
         .def("getHome", (ofVec3f&(ofxBoidParticle::*)(void)) &ofxBoidParticle::getHome)
         .def("getPpos", (ofVec3f&(ofxBoidParticle::*)(void)) &ofxBoidParticle::getPpos)
         .def("getVel", (ofVec3f&(ofxBoidParticle::*)(void)) &ofxBoidParticle::getVel)
         .def("getAcc", (ofVec3f&(ofxBoidParticle::*)(void)) &ofxBoidParticle::getAcc)
         .def("getColor", (ofColor&(ofxBoidParticle::*)(void)) &ofxBoidParticle::getColor)
         .def("setColorAlpha", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::setColorAlpha)
         .def("getColorAlpha", (float(ofxBoidParticle::*)(void)) &ofxBoidParticle::getColorAlpha)
         .def("getRadius", (float(ofxBoidParticle::*)(void)) &ofxBoidParticle::getRadius)
         .def("getID", (int(ofxBoidParticle::*)(void)) &ofxBoidParticle::getID)
         .def("setID", (void(ofxBoidParticle::*)(int)) &ofxBoidParticle::setID)
         .def("decay", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::decay)
         .def("getLifeTime", (float(ofxBoidParticle::*)(void)) &ofxBoidParticle::getLifeTime)
         .def("isDead", (bool(ofxBoidParticle::*)(void)) &ofxBoidParticle::isDead)
         
         .def("setZoneRadius", (void(ofxBoidParticle::*)(float)) &ofxBoidParticle::setZoneRadius)
         .def("separation", (void(ofxBoidParticle::*)(void)) &ofxBoidParticle::separation)
         .def("drawDebug", (void(ofxBoidParticle::*)(void)) &ofxBoidParticle::drawDebug)
         .def("borders", (void(ofxBoidParticle::*)(float,float)) &ofxBoidParticle::borders)
         .def("addNeighborPos", (void(ofxBoidParticle::*)(ofVec3f)) &ofxBoidParticle::addNeighborPos),
         
         // ofxBoidSystem
         class_<ofxBoidSystem>("ofxBoidSystem")
         .def(constructor<>())
         .def("clear", (void(ofxBoidSystem::*)(void)) &ofxBoidSystem::clear)
         .def("update", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::update)
         .def("updateAndDecay", (void(ofxBoidSystem::*)(float,float)) &ofxBoidSystem::updateAndDecay)
         .def("setDamping", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setDamping)
         .def("setVelocityLimit", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setVelocityLimit)
         .def("setAccerationLimit", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setAccerationLimit)
         .def("randomize", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::randomize)
         .def("draw", (void(ofxBoidSystem::*)(void)) &ofxBoidSystem::draw)
         .def("addParticle", (void(ofxBoidSystem::*)(ofxBoidParticle*)) &ofxBoidSystem::addParticle)
         .def("getCount", (int(ofxBoidSystem::*)(void)) &ofxBoidSystem::getCount)
         .def("getParticle", (ofxParticle*(ofxBoidSystem::*)(int)) &ofxBoidSystem::getParticle)
         
         .def("angleSigned", (float(ofxBoidSystem::*)(ofVec3f&,ofVec3f&)) &ofxBoidSystem::angleSigned)
         .def("setZoneRadius", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setZoneRadius)
         .def("setThreshLow", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setThreshLow)
         .def("setThreshHigh", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setThreshHigh)
         .def("setAttractForceConstant", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setAttractForceConstant)
         .def("setRepelForceConstant", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setRepelForceConstant)
         .def("setCohesionForceConstant", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setCohesionForceConstant)
         .def("setAlignForceConstant", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setAlignForceConstant)
         .def("setPerlinForceConstant", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setPerlinForceConstant)
         .def("setVelLimitLow", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setVelLimitLow)
         .def("setVelLimitHigh", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setVelLimitHigh)
         .def("setVelLimitLowAndHigh", (void(ofxBoidSystem::*)(float,float)) &ofxBoidSystem::setVelLimitLowAndHigh)
         .def("setAccLimitHigh", (void(ofxBoidSystem::*)(float)) &ofxBoidSystem::setAccLimitHigh),
         
         // ofxBufferEffectorBehavior
         class_<ofxBufferEffectorBehavior>("ofxBufferEffectorBehavior")
         .def(constructor<>())
         .def("update", (void(ofxBufferEffectorBehavior::*)(void)) &ofxBufferEffectorBehavior::update)
         .def("actUpon", (void(ofxBufferEffectorBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxBufferEffectorBehavior::actUpon)
         .def("isEnabled", (bool(ofxBufferEffectorBehavior::*)(void)) &ofxBufferEffectorBehavior::isEnabled)
         .def("getMagnitude", (float(ofxBufferEffectorBehavior::*)(void)) &ofxBufferEffectorBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxBufferEffectorBehavior::*)(float)) &ofxBufferEffectorBehavior::setMagnitude)
         
         .def("setup", (void(ofxBufferEffectorBehavior::*)(void)) &ofxBufferEffectorBehavior::setup)
         .def("getBuffer", (float*(ofxBufferEffectorBehavior::*)(void)) &ofxBufferEffectorBehavior::getBuffer)
         .def("setBuffer", (void(ofxBufferEffectorBehavior::*)(float*,int)) &ofxBufferEffectorBehavior::setBuffer)
         .def("getBufferSize", (int(ofxBufferEffectorBehavior::*)(void)) &ofxBufferEffectorBehavior::getBufferSize),
         
         // ofxCircle
         class_<ofxCircle>("ofxCircle")
         .def(constructor<>())
         .def(constructor<float,int,ofVec3f>())
         .def("setRadius", (void(ofxCircle::*)(float)) &ofxCircle::setRadius)
         .def("reset", (void(ofxCircle::*)(void)) &ofxCircle::reset),
         
         // ofxDamperBehavior
         class_<ofxDamperBehavior>("ofxDamperBehavior")
         .def(constructor<>())
         .def("update", (void(ofxDamperBehavior::*)(void)) &ofxDamperBehavior::update)
         .def("actUpon", (void(ofxDamperBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxDamperBehavior::actUpon)
         .def("isEnabled", (bool(ofxDamperBehavior::*)(void)) &ofxDamperBehavior::isEnabled)
         .def("getMagnitude", (float(ofxDamperBehavior::*)(void)) &ofxDamperBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxDamperBehavior::*)(float)) &ofxDamperBehavior::setMagnitude)
         
         .def("setup", (void(ofxDamperBehavior::*)(void)) &ofxDamperBehavior::setup),
         
         // ofxDistorterBehavior
         class_<ofxDistorterBehavior>("ofxDistorterBehavior")
         .def(constructor<>())
         .def("update", (void(ofxDistorterBehavior::*)(void)) &ofxDistorterBehavior::update)
         .def("actUpon", (void(ofxDistorterBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxDistorterBehavior::actUpon)
         .def("isEnabled", (bool(ofxDistorterBehavior::*)(void)) &ofxDistorterBehavior::isEnabled)
         .def("getMagnitude", (float(ofxDistorterBehavior::*)(void)) &ofxDistorterBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxDistorterBehavior::*)(float)) &ofxDistorterBehavior::setMagnitude)
         
         .def("setup", (void(ofxDistorterBehavior::*)(void)) &ofxDistorterBehavior::setup)
         .def("getPosition", (ofVec3f&(ofxDistorterBehavior::*)(void)) &ofxDistorterBehavior::getPosition)
         .def("setPosition", (void(ofxDistorterBehavior::*)(ofVec3f)) &ofxDistorterBehavior::setPosition)
         .def("getRadius", (float(ofxDistorterBehavior::*)(void)) &ofxDistorterBehavior::getRadius)
         .def("setRadius", (void(ofxDistorterBehavior::*)(float)) &ofxDistorterBehavior::setRadius)
         .def("getExpFactor", (float(ofxDistorterBehavior::*)(void)) &ofxDistorterBehavior::getExpFactor)
         .def("setExpFactor", (void(ofxDistorterBehavior::*)(float)) &ofxDistorterBehavior::setExpFactor),
         
         // ofxElectroStaticBehavior
         class_<ofxElectroStaticBehavior>("ofxElectroStaticBehavior")
         .def(constructor<>())
         .def("update", (void(ofxElectroStaticBehavior::*)(void)) &ofxElectroStaticBehavior::update)
         .def("actUpon", (void(ofxElectroStaticBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxElectroStaticBehavior::actUpon)
         .def("isEnabled", (bool(ofxElectroStaticBehavior::*)(void)) &ofxElectroStaticBehavior::isEnabled)
         .def("getMagnitude", (float(ofxElectroStaticBehavior::*)(void)) &ofxElectroStaticBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxElectroStaticBehavior::*)(float)) &ofxElectroStaticBehavior::setMagnitude)
         
         .def("setup", (void(ofxElectroStaticBehavior::*)(void)) &ofxElectroStaticBehavior::setup),
         
         // ofxField2D
         class_<ofxField2D>("ofxField2D")
         .def(constructor<>())
         .def("init", (void(ofxField2D::*)(int,int,int,int)) &ofxField2D::init)
         .def("resize", (void(ofxField2D::*)(int,int)) &ofxField2D::resize)
         .def("reset", (void(ofxField2D::*)(void)) &ofxField2D::reset)
         .def("randomize", (void(ofxField2D::*)(void)) &ofxField2D::randomize)
         .def("update", (void(ofxField2D::*)(void)) &ofxField2D::update)
         .def("input", (void(ofxField2D::*)(float,float,float,float,float)) &ofxField2D::input)
         .def("setViscosity", (void(ofxField2D::*)(float)) &ofxField2D::setViscosity)
         .def("setDensityDecay", (void(ofxField2D::*)(float)) &ofxField2D::setDensityDecay)
         .def("setDifferential", (void(ofxField2D::*)(float)) &ofxField2D::setDifferential)
         .def("setDt", (void(ofxField2D::*)(float)) &ofxField2D::setDt)
         .def("setIterations", (void(ofxField2D::*)(int)) &ofxField2D::setIterations)
         .def("setPointSize", (void(ofxField2D::*)(float)) &ofxField2D::setPointSize)
         .def("setLineWidth", (void(ofxField2D::*)(float)) &ofxField2D::setLineWidth)
         .def("getPointSize", (float&(ofxField2D::*)(void)) &ofxField2D::getPointSize)
         .def("getLineWidth", (float&(ofxField2D::*)(void)) &ofxField2D::getLineWidth)
         .def("getViscosity", (float&(ofxField2D::*)(void)) &ofxField2D::getViscosity)
         .def("getDensityDecay", (float&(ofxField2D::*)(void)) &ofxField2D::getDensityDecay)
         .def("getDifferential", (float&(ofxField2D::*)(void)) &ofxField2D::getDifferential)
         .def("getDt", (float&(ofxField2D::*)(void)) &ofxField2D::getDt)
         .def("getIterations", (int&(ofxField2D::*)(void)) &ofxField2D::getIterations)
         .def("getVector", (ofPoint(ofxField2D::*)(int,int,bool)) &ofxField2D::getVector)
         .def("getDensity", (float(ofxField2D::*)(int,int)) &ofxField2D::getDensity)
         .def("adaptFromImage", (void(ofxField2D::*)(ofPixels&,float)) &ofxField2D::adaptFromImage)
         .def("draw", (void(ofxField2D::*)(void)) &ofxField2D::draw)
         .def("getRenderType", (int(ofxField2D::*)(void)) &ofxField2D::getRenderType)
         .def("setRenderType", (void(ofxField2D::*)(int)) &ofxField2D::setRenderType)
         .def("getWidth", (int(ofxField2D::*)(void)) &ofxField2D::getWidth)
         .def("getHeight", (int(ofxField2D::*)(void)) &ofxField2D::getHeight),
         
         // ofxFieldAgitator
         class_<ofxFieldAgitator>("ofxFieldAgitator")
         .def(constructor<>())
         .def(constructor<ofVec3f>())
         .def("update", (void(ofxFieldAgitator::*)(void)) &ofxFieldAgitator::update)
         .def("getAngle", (float(ofxFieldAgitator::*)(void)) &ofxFieldAgitator::getAngle)
         .def("getDistance", (ofVec3f(ofxFieldAgitator::*)(void)) &ofxFieldAgitator::getDistance)
         .def("draw", (void(ofxFieldAgitator::*)(void)) &ofxFieldAgitator::draw),
         
         // ofxGenericShape
         class_<ofxGenericShape>("ofxGenericShape")
         .def(constructor<>())
         .def(constructor<ofPolyline,int,float,ofVec3f>())
         .def("init", (void(ofxGenericShape::*)(ofPolyline&,int,float,ofVec3f&)) &ofxGenericShape::init)
         .def("update", (void(ofxGenericShape::*)(void)) &ofxGenericShape::update)
         .def("setVelocityLimit", (void(ofxGenericShape::*)(float)) &ofxGenericShape::setVelocityLimit)
         .def("setAccerationLimit", (void(ofxGenericShape::*)(float)) &ofxGenericShape::setAccerationLimit)
         .def("setDamping", (void(ofxGenericShape::*)(float)) &ofxGenericShape::setDamping)
         .def("setRadius", (void(ofxGenericShape::*)(float,bool)) &ofxGenericShape::setRadius)
         .def("setOffset", (void(ofxGenericShape::*)(float,float,bool)) &ofxGenericShape::setOffset),
         
         // ofxHomingBehavior
         class_<ofxHomingBehavior>("ofxHomingBehavior")
         .def(constructor<>())
         .def("update", (void(ofxHomingBehavior::*)(void)) &ofxHomingBehavior::update)
         .def("actUpon", (void(ofxHomingBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxHomingBehavior::actUpon)
         .def("isEnabled", (bool(ofxHomingBehavior::*)(void)) &ofxHomingBehavior::isEnabled)
         .def("getMagnitude", (float(ofxHomingBehavior::*)(void)) &ofxHomingBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxHomingBehavior::*)(float)) &ofxHomingBehavior::setMagnitude)
         
         .def("setup", (void(ofxHomingBehavior::*)(void)) &ofxHomingBehavior::setup),
         
         // ofxParticle
         class_<ofxParticle>("ofxParticle")
         .def(constructor<>())
         .def(constructor<ofVec3f>())
         .def("setBorders", (void(ofxParticle::*)(float,float)) &ofxParticle::setBorders)
         .def("update", (void(ofxParticle::*)(float)) &ofxParticle::update)
         .def("draw", (void(ofxParticle::*)(void)) &ofxParticle::draw)
         .def("drawVertex", (void(ofxParticle::*)(void)) &ofxParticle::drawVertex)
         .def("borders", (void(ofxParticle::*)(void)) &ofxParticle::borders)
         .def("elasticBorder", (void(ofxParticle::*)(float)) &ofxParticle::elasticBorder)
         .def("circleborders", (void(ofxParticle::*)(void)) &ofxParticle::circleborders)
         .def("setRadius", (void(ofxParticle::*)(float)) &ofxParticle::setRadius)
         .def("setPos", (void(ofxParticle::*)(ofVec3f)) &ofxParticle::setPos)
         .def("setVel", (void(ofxParticle::*)(ofVec3f)) &ofxParticle::setVel)
         .def("setAcc", (void(ofxParticle::*)(ofVec3f)) &ofxParticle::setAcc)
         .def("setHome", (void(ofxParticle::*)(ofVec3f)) &ofxParticle::setHome)
         .def("setHome", (void(ofxParticle::*)(float,float,float)) &ofxParticle::setHome)
         .def("setColor", (void(ofxParticle::*)(ofColor)) &ofxParticle::setColor)
         .def("setDamping", (void(ofxParticle::*)(float)) &ofxParticle::setDamping)
         .def("setAccerationLimit", (void(ofxParticle::*)(float)) &ofxParticle::setAccerationLimit)
         .def("setVelocityLimit", (void(ofxParticle::*)(float)) &ofxParticle::setVelocityLimit)
         .def("addExternalForce", (void(ofxParticle::*)(ofVec3f)) &ofxParticle::addExternalForce)
         .def("addSpringForce", (void(ofxParticle::*)(ofVec3f)) &ofxParticle::addSpringForce)
         .def("setFixed", (void(ofxParticle::*)(bool)) &ofxParticle::setFixed)
         .def("isFixed", (bool(ofxParticle::*)(void)) &ofxParticle::isFixed)
         .def("addForce", (void(ofxParticle::*)(ofVec3f)) &ofxParticle::addForce)
         .def("getPos", (ofVec3f&(ofxParticle::*)(void)) &ofxParticle::getPos)
         .def("getHome", (ofVec3f&(ofxParticle::*)(void)) &ofxParticle::getHome)
         .def("getPpos", (ofVec3f&(ofxParticle::*)(void)) &ofxParticle::getPpos)
         .def("getVel", (ofVec3f&(ofxParticle::*)(void)) &ofxParticle::getVel)
         .def("getAcc", (ofVec3f&(ofxParticle::*)(void)) &ofxParticle::getAcc)
         .def("getColor", (ofColor&(ofxParticle::*)(void)) &ofxParticle::getColor)
         .def("setColorAlpha", (void(ofxParticle::*)(float)) &ofxParticle::setColorAlpha)
         .def("getColorAlpha", (float(ofxParticle::*)(void)) &ofxParticle::getColorAlpha)
         .def("getRadius", (float(ofxParticle::*)(void)) &ofxParticle::getRadius)
         .def("getID", (int(ofxParticle::*)(void)) &ofxParticle::getID)
         .def("setID", (void(ofxParticle::*)(int)) &ofxParticle::setID)
         .def("decay", (void(ofxParticle::*)(float)) &ofxParticle::decay)
         .def("getLifeTime", (float(ofxParticle::*)(void)) &ofxParticle::getLifeTime)
         .def("isDead", (bool(ofxParticle::*)(void)) &ofxParticle::isDead),
         
         // ofxParticleSystem
         class_<ofxParticleSystem>("ofxParticleSystem")
         .def(constructor<>())
         .def("clear", (void(ofxParticleSystem::*)(void)) &ofxParticleSystem::clear)
         .def("update", (void(ofxParticleSystem::*)(float)) &ofxParticleSystem::update)
         .def("updateAndDecay", (void(ofxParticleSystem::*)(float,float)) &ofxParticleSystem::updateAndDecay)
         .def("setDamping", (void(ofxParticleSystem::*)(float)) &ofxParticleSystem::setDamping)
         .def("setVelocityLimit", (void(ofxParticleSystem::*)(float)) &ofxParticleSystem::setVelocityLimit)
         .def("setAccerationLimit", (void(ofxParticleSystem::*)(float)) &ofxParticleSystem::setAccerationLimit)
         .def("randomize", (void(ofxParticleSystem::*)(float)) &ofxParticleSystem::randomize)
         .def("draw", (void(ofxParticleSystem::*)(void)) &ofxParticleSystem::draw)
         .def("addParticle", (void(ofxParticleSystem::*)(ofxParticle*)) &ofxParticleSystem::addParticle)
         .def("getCount", (int(ofxParticleSystem::*)(void)) &ofxParticleSystem::getCount)
         .def("getParticle", (ofxParticle*(ofxParticleSystem::*)(int)) &ofxParticleSystem::getParticle),
         
         // ofxPerlinBehavior
         class_<ofxPerlinBehavior>("ofxPerlinBehavior")
         .def(constructor<>())
         .def("update", (void(ofxPerlinBehavior::*)(void)) &ofxPerlinBehavior::update)
         .def("actUpon", (void(ofxPerlinBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxPerlinBehavior::actUpon)
         .def("isEnabled", (bool(ofxPerlinBehavior::*)(void)) &ofxPerlinBehavior::isEnabled)
         .def("getMagnitude", (float(ofxPerlinBehavior::*)(void)) &ofxPerlinBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxPerlinBehavior::*)(float)) &ofxPerlinBehavior::setMagnitude)
         
         .def("setup", (void(ofxPerlinBehavior::*)(void)) &ofxPerlinBehavior::setup),
         
         // ofxRezaParticle
         class_<ofxRezaParticle>("ofxRezaParticle")
         .def(constructor<>())
         .def(constructor<ofVec3f>())
         .def("setBorders", (void(ofxRezaParticle::*)(float,float)) &ofxRezaParticle::setBorders)
         .def("update", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::update)
         .def("draw", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::draw)
         .def("drawVertex", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::drawVertex)
         .def("borders", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::borders)
         .def("elasticBorder", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::elasticBorder)
         .def("circleborders", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::circleborders)
         .def("setRadius", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setRadius)
         .def("setPos", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::setPos)
         .def("setVel", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::setVel)
         .def("setAcc", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::setAcc)
         .def("setHome", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::setHome)
         .def("setHome", (void(ofxRezaParticle::*)(float,float,float)) &ofxRezaParticle::setHome)
         .def("setColor", (void(ofxRezaParticle::*)(ofColor)) &ofxRezaParticle::setColor)
         .def("setDamping", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setDamping)
         .def("setAccerationLimit", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setAccerationLimit)
         .def("setVelocityLimit", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setVelocityLimit)
         .def("addExternalForce", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::addExternalForce)
         .def("addSpringForce", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::addSpringForce)
         .def("setFixed", (void(ofxRezaParticle::*)(bool)) &ofxRezaParticle::setFixed)
         .def("isFixed", (bool(ofxRezaParticle::*)(void)) &ofxRezaParticle::isFixed)
         .def("addForce", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::addForce)
         .def("getPos", (ofVec3f&(ofxRezaParticle::*)(void)) &ofxRezaParticle::getPos)
         .def("getHome", (ofVec3f&(ofxRezaParticle::*)(void)) &ofxRezaParticle::getHome)
         .def("getPpos", (ofVec3f&(ofxRezaParticle::*)(void)) &ofxRezaParticle::getPpos)
         .def("getVel", (ofVec3f&(ofxRezaParticle::*)(void)) &ofxRezaParticle::getVel)
         .def("getAcc", (ofVec3f&(ofxRezaParticle::*)(void)) &ofxRezaParticle::getAcc)
         .def("getColor", (ofColor&(ofxRezaParticle::*)(void)) &ofxRezaParticle::getColor)
         .def("setColorAlpha", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setColorAlpha)
         .def("getColorAlpha", (float(ofxRezaParticle::*)(void)) &ofxRezaParticle::getColorAlpha)
         .def("getRadius", (float(ofxRezaParticle::*)(void)) &ofxRezaParticle::getRadius)
         .def("getID", (int(ofxRezaParticle::*)(void)) &ofxRezaParticle::getID)
         .def("setID", (void(ofxRezaParticle::*)(int)) &ofxRezaParticle::setID)
         .def("decay", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::decay)
         .def("getLifeTime", (float(ofxRezaParticle::*)(void)) &ofxRezaParticle::getLifeTime)
         .def("isDead", (bool(ofxRezaParticle::*)(void)) &ofxRezaParticle::isDead)
         
         .def("goSpherical", (ofVec3f(ofxRezaParticle::*)(void)) &ofxRezaParticle::goSpherical)
         .def("goHome", (ofVec3f(ofxRezaParticle::*)(void)) &ofxRezaParticle::goHome)
         .def("addDistortion", (ofVec3f(ofxRezaParticle::*)(void)) &ofxRezaParticle::addDistortion)
         .def("setCenterPos", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::setCenterPos)
         .def("setTargetHome", (void(ofxRezaParticle::*)(bool)) &ofxRezaParticle::setTargetHome)
         .def("toggleTargetHome", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::toggleTargetHome)
         .def("setTargetSphere", (void(ofxRezaParticle::*)(bool)) &ofxRezaParticle::setTargetSphere)
         .def("toggleTargetSphere", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::toggleTargetSphere)
         .def("setRandomizeVel", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::setRandomizeVel)
         .def("setRandomizeVel", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setRandomizeVel)
         .def("setSphericalRadius", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setSphericalRadius)
         .def("getSphericalRadius", (float(ofxRezaParticle::*)(void)) &ofxRezaParticle::getSphericalRadius)
         .def("setDistortion", (void(ofxRezaParticle::*)(bool)) &ofxRezaParticle::setDistortion)
         .def("toggleDistortion", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::toggleDistortion)
         .def("setDistortVector", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::setDistortVector)
         
         .def("goSphericalCenter", (ofVec3f(ofxRezaParticle::*)(void)) &ofxRezaParticle::goSphericalCenter)
         .def("repulse", (ofVec3f(ofxRezaParticle::*)(void)) &ofxRezaParticle::repulse)
         .def("setRepulsion", (void(ofxRezaParticle::*)(bool)) &ofxRezaParticle::setRepulsion)
         .def("toggleRepulsion", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::toggleRepulsion)
         .def("setAbsCenter", (void(ofxRezaParticle::*)(ofVec3f)) &ofxRezaParticle::setAbsCenter)
         .def("toggleAbsCenter", (void(ofxRezaParticle::*)(void)) &ofxRezaParticle::toggleAbsCenter)
         .def("setCenterTargeting", (void(ofxRezaParticle::*)(bool)) &ofxRezaParticle::setCenterTargeting)
         .def("setSAMulti", (void(ofxRezaParticle::*)(float)) &ofxRezaParticle::setSAMulti),
         
         // ofxRezaParticleSystem
         class_<ofxRezaParticleSystem>("ofxRezaParticleSystem")
         .def(constructor<>())
         .def("clear", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::clear)
         .def("update", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::update)
         .def("updateAndDecay", (void(ofxRezaParticleSystem::*)(float,float)) &ofxRezaParticleSystem::updateAndDecay)
         .def("setDamping", (void(ofxRezaParticleSystem::*)(float)) &ofxRezaParticleSystem::setDamping)
         .def("setVelocityLimit", (void(ofxRezaParticleSystem::*)(float)) &ofxRezaParticleSystem::setVelocityLimit)
         .def("setAccerationLimit", (void(ofxRezaParticleSystem::*)(float)) &ofxRezaParticleSystem::setAccerationLimit)
         .def("randomize", (void(ofxRezaParticleSystem::*)(float)) &ofxRezaParticleSystem::randomize)
         .def("draw", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::draw)
         .def("addParticle", (void(ofxRezaParticleSystem::*)(ofxRezaParticle*)) &ofxRezaParticleSystem::addParticle)
         .def("getCount", (int(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::getCount)
         .def("getParticle", (ofxParticle*(ofxRezaParticleSystem::*)(int)) &ofxRezaParticleSystem::getParticle)
         
         .def("setCenter", (void(ofxRezaParticleSystem::*)(ofVec3f*)) &ofxRezaParticleSystem::setCenter)
         .def("setTargetHome", (void(ofxRezaParticleSystem::*)(bool)) &ofxRezaParticleSystem::setTargetHome)
         .def("getTargetHome", (bool(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::getTargetHome)
         .def("toggleTargetHome", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::toggleTargetHome)
         .def("setTargetSphere", (void(ofxRezaParticleSystem::*)(bool)) &ofxRezaParticleSystem::setTargetSphere)
         .def("getTargetSphere", (bool(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::getTargetSphere)
         .def("toggleTargetSphere", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::toggleTargetSphere)
         .def("setSphericalRadius", (void(ofxRezaParticleSystem::*)(float)) &ofxRezaParticleSystem::setSphericalRadius)
         .def("getSphericalRadius", (float(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::getSphericalRadius)
         .def("setRandomizeVel", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::setRandomizeVel)
         .def("setRandomizeVel", (void(ofxRezaParticleSystem::*)(float)) &ofxRezaParticleSystem::setRandomizeVel)
         .def("toggleDistortion", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::toggleDistortion)
         .def("setDistortion", (void(ofxRezaParticleSystem::*)(bool)) &ofxRezaParticleSystem::setDistortion)
         .def("setDistortVector", (void(ofxRezaParticleSystem::*)(ofVec3f*)) &ofxRezaParticleSystem::setDistortVector)
         
         .def("setRepulsion", (void(ofxRezaParticleSystem::*)(bool)) &ofxRezaParticleSystem::setRepulsion)
         .def("getRepulsion", (bool(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::getRepulsion)
         .def("toggleRepulsion", (void(ofxRezaParticleSystem::*)(void)) &ofxRezaParticleSystem::toggleRepulsion)
         .def("billBoard", (void(ofxRezaParticleSystem::*)(ofVec3f,ofVec3f)) &ofxRezaParticleSystem::billBoard)
         .def("setCameraRef", (void(ofxRezaParticleSystem::*)(ofEasyCam)) &ofxRezaParticleSystem::setCameraRef)
         .def("setGlowImage", (void(ofxRezaParticleSystem::*)(ofImage)) &ofxRezaParticleSystem::setGlowImage),
         
         // ofxRParticle
         class_<ofxRParticle>("ofxRParticle")
         .def(constructor<>())
         .def(constructor<ofVec3f>())
         .def("calculateAcceleration", (ofVec3f&(ofxRParticle::*)(ofVec3f&,ofVec3f&,float)) &ofxRParticle::calculateAcceleration)
         .def("setRadius", (void(ofxRParticle::*)(float)) &ofxRParticle::setRadius)
         .def("setPos", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::setPos)
         .def("setPpos", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::setPpos)
         .def("setVel", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::setVel)
         .def("setAcc", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::setAcc)
         .def("setHome", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::setHome)
         .def("setHome", (void(ofxRParticle::*)(float,float,float)) &ofxRParticle::setHome)
         .def("setColor", (void(ofxRParticle::*)(ofColor)) &ofxRParticle::setColor)
         .def("setDamping", (void(ofxRParticle::*)(float)) &ofxRParticle::setDamping)
         .def("setRestitution", (void(ofxRParticle::*)(float)) &ofxRParticle::setRestitution)
         .def("setAccerationLimit", (void(ofxRParticle::*)(float)) &ofxRParticle::setAccerationLimit)
         .def("setVelocityLimit", (void(ofxRParticle::*)(float)) &ofxRParticle::setVelocityLimit)
         .def("addExternalForce", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::addExternalForce)
         .def("addSpringForce", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::addSpringForce)
         .def("setFixed", (void(ofxRParticle::*)(bool)) &ofxRParticle::setFixed)
         .def("isFixed", (bool(ofxRParticle::*)(void)) &ofxRParticle::isFixed)
         .def("addForce", (void(ofxRParticle::*)(ofVec3f)) &ofxRParticle::addForce)
         .def("getPos", (ofVec3f&(ofxRParticle::*)(void)) &ofxRParticle::getPos)
         .def("getHome", (ofVec3f&(ofxRParticle::*)(void)) &ofxRParticle::getHome)
         .def("getPpos", (ofVec3f&(ofxRParticle::*)(void)) &ofxRParticle::getPpos)
         .def("getVel", (ofVec3f&(ofxRParticle::*)(void)) &ofxRParticle::getVel)
         .def("getAcc", (ofVec3f&(ofxRParticle::*)(void)) &ofxRParticle::getAcc)
         .def("getColor", (ofColor&(ofxRParticle::*)(void)) &ofxRParticle::getColor)
         .def("setColorAlpha", (void(ofxRParticle::*)(float)) &ofxRParticle::setColorAlpha)
         .def("getColorAlpha", (float(ofxRParticle::*)(void)) &ofxRParticle::getColorAlpha)
         .def("getRadius", (float(ofxRParticle::*)(void)) &ofxRParticle::getRadius)
         .def("getID", (int(ofxRParticle::*)(void)) &ofxRParticle::getID)
         .def("setID", (void(ofxRParticle::*)(int)) &ofxRParticle::setID)
         .def("getLifeTime", (float(ofxRParticle::*)(void)) &ofxRParticle::getLifeTime)
         .def("isDead", (bool(ofxRParticle::*)(void)) &ofxRParticle::isDead)
         .def("setParticleData", (void(ofxRParticle::*)(ofxRParticleData *)) &ofxRParticle::setParticleData),
         
         // ofxRParticleData
         class_<ofxRParticleData>("ofxRParticleData")
         .def(constructor<>()),
         
         // ofxRParticleGlowieRenderer
         class_<ofxRParticleGlowieRenderer>("ofxRParticleGlowieRenderer")
         .def(constructor<>())
         .def("setup", (void(ofxRParticleGlowieRenderer::*)(void)) &ofxRParticleGlowieRenderer::setup)
         .def("draw", (void(ofxRParticleGlowieRenderer::*)(void)) &ofxRParticleGlowieRenderer::draw)
         .def("setPointSize", (void(ofxRParticleGlowieRenderer::*)(float)) &ofxRParticleGlowieRenderer::setPointSize)
         .def("setAdditiveBlending", (void(ofxRParticleGlowieRenderer::*)(bool)) &ofxRParticleGlowieRenderer::setAdditiveBlending)
         
         .def("setAxisAngleOffsets", (void(ofxRParticleGlowieRenderer::*)(ofx1DExtruder,ofx1DExtruder,ofx1DExtruder)) &ofxRParticleGlowieRenderer::setAxisAngleOffsets)
         .def("setCamPtr", (void(ofxRParticleGlowieRenderer::*)(ofEasyCam)) &ofxRParticleGlowieRenderer::setCamPtr)
         .def("setGlowImage", (void(ofxRParticleGlowieRenderer::*)(ofImage)) &ofxRParticleGlowieRenderer::setGlowImage),
         
         // ofxRParticleRenderer
         class_<ofxRParticleRenderer>("ofxRParticleRenderer")
         .def(constructor<>())
         .def("setup", (void(ofxRParticleRenderer::*)(void)) &ofxRParticleRenderer::setup)
         .def("draw", (void(ofxRParticleRenderer::*)(void)) &ofxRParticleRenderer::draw)
         .def("setPointSize", (void(ofxRParticleRenderer::*)(float)) &ofxRParticleRenderer::setPointSize)
         .def("setAdditiveBlending", (void(ofxRParticleRenderer::*)(bool)) &ofxRParticleRenderer::setAdditiveBlending),
         
         // ofxRParticleSystem
         class_<ofxRParticleSystem>("ofxRParticleSystem")
         .def(constructor<>())
         .def("clear", (void(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::clear)
         .def("update", (void(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::update)
         .def("draw", (void(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::draw)
         .def("addBehavior", (void(ofxRParticleSystem::*)(ofxBehavior)) &ofxRParticleSystem::addBehavior)
         .def("addParticle", (void(ofxRParticleSystem::*)(ofxRParticle&)) &ofxRParticleSystem::addParticle)
         .def("setDt", (void(ofxRParticleSystem::*)(float)) &ofxRParticleSystem::setDt)
         .def("getDt", (float(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::getDt)
         .def("setDamping", (void(ofxRParticleSystem::*)(float)) &ofxRParticleSystem::setDamping)
         .def("getDamping", (float(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::getDamping)
         .def("setRestitution", (void(ofxRParticleSystem::*)(float)) &ofxRParticleSystem::setRestitution)
         .def("getRestitution", (float(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::getRestitution)
         .def("setVelocityLimit", (void(ofxRParticleSystem::*)(float)) &ofxRParticleSystem::setVelocityLimit)
         .def("getVelocityLimit", (float(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::getVelocityLimit)
         .def("setAccelerationLimit", (void(ofxRParticleSystem::*)(float)) &ofxRParticleSystem::setAccelerationLimit)
         .def("getAccelerationLimit", (float(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::getAccelerationLimit)
         .def("setCount", (void(ofxRParticleSystem::*)(int)) &ofxRParticleSystem::setCount)
         .def("getCount", (float(ofxRParticleSystem::*)(void)) &ofxRParticleSystem::getCount)
         .def("getParticle", (ofxRParticle&(ofxRParticleSystem::*)(int)) &ofxRParticleSystem::getParticle)
         .def("setRenderer", (void(ofxRParticleSystem::*)(ofxRParticleRenderer)) &ofxRParticleSystem::setRenderer)
         .def("setSolver", (void(ofxRParticleSystem::*)(ofxSolver)) &ofxRParticleSystem::setSolver)
         .def("randomize", (void(ofxRParticleSystem::*)(float)) &ofxRParticleSystem::randomize),
         
         // ofxSmartParticle
         class_<ofxSmartParticle>("ofxSmartParticle")
         .def(constructor<>())
         .def(constructor<ofVec3f>())
         .def("setBorders", (void(ofxSmartParticle::*)(float,float)) &ofxSmartParticle::setBorders)
         .def("update", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::update)
         .def("draw", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::draw)
         .def("drawVertex", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::drawVertex)
         .def("borders", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::borders)
         .def("elasticBorder", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::elasticBorder)
         .def("circleborders", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::circleborders)
         .def("setRadius", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::setRadius)
         .def("setPos", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::setPos)
         .def("setVel", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::setVel)
         .def("setAcc", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::setAcc)
         .def("setHome", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::setHome)
         .def("setHome", (void(ofxSmartParticle::*)(float,float,float)) &ofxSmartParticle::setHome)
         .def("setColor", (void(ofxSmartParticle::*)(ofColor)) &ofxSmartParticle::setColor)
         .def("setDamping", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::setDamping)
         .def("setAccerationLimit", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::setAccerationLimit)
         .def("setVelocityLimit", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::setVelocityLimit)
         .def("addExternalForce", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::addExternalForce)
         .def("addSpringForce", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::addSpringForce)
         .def("setFixed", (void(ofxSmartParticle::*)(bool)) &ofxSmartParticle::setFixed)
         .def("isFixed", (bool(ofxSmartParticle::*)(void)) &ofxSmartParticle::isFixed)
         .def("addForce", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::addForce)
         .def("getPos", (ofVec3f&(ofxSmartParticle::*)(void)) &ofxSmartParticle::getPos)
         .def("getHome", (ofVec3f&(ofxSmartParticle::*)(void)) &ofxSmartParticle::getHome)
         .def("getPpos", (ofVec3f&(ofxSmartParticle::*)(void)) &ofxSmartParticle::getPpos)
         .def("getVel", (ofVec3f&(ofxSmartParticle::*)(void)) &ofxSmartParticle::getVel)
         .def("getAcc", (ofVec3f&(ofxSmartParticle::*)(void)) &ofxSmartParticle::getAcc)
         .def("getColor", (ofColor&(ofxSmartParticle::*)(void)) &ofxSmartParticle::getColor)
         .def("setColorAlpha", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::setColorAlpha)
         .def("getColorAlpha", (float(ofxSmartParticle::*)(void)) &ofxSmartParticle::getColorAlpha)
         .def("getRadius", (float(ofxSmartParticle::*)(void)) &ofxSmartParticle::getRadius)
         .def("getID", (int(ofxSmartParticle::*)(void)) &ofxSmartParticle::getID)
         .def("setID", (void(ofxSmartParticle::*)(int)) &ofxSmartParticle::setID)
         .def("decay", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::decay)
         .def("getLifeTime", (float(ofxSmartParticle::*)(void)) &ofxSmartParticle::getLifeTime)
         .def("isDead", (bool(ofxSmartParticle::*)(void)) &ofxSmartParticle::isDead)
         
         .def("goSpherical", (ofVec3f(ofxSmartParticle::*)(void)) &ofxSmartParticle::goSpherical)
         .def("goHome", (ofVec3f(ofxSmartParticle::*)(void)) &ofxSmartParticle::goHome)
         .def("addDistortion", (ofVec3f(ofxSmartParticle::*)(void)) &ofxSmartParticle::addDistortion)
         .def("setCenterPos", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::setCenterPos)
         .def("setTargetHome", (void(ofxSmartParticle::*)(bool)) &ofxSmartParticle::setTargetHome)
         .def("toggleTargetHome", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::toggleTargetHome)
         .def("setTargetSphere", (void(ofxSmartParticle::*)(bool)) &ofxSmartParticle::setTargetSphere)
         .def("toggleTargetSphere", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::toggleTargetSphere)
         .def("setRandomizeVel", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::setRandomizeVel)
         .def("setRandomizeVel", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::setRandomizeVel)
         .def("setSphericalRadius", (void(ofxSmartParticle::*)(float)) &ofxSmartParticle::setSphericalRadius)
         .def("getSphericalRadius", (float(ofxSmartParticle::*)(void)) &ofxSmartParticle::getSphericalRadius)
         .def("setDistortion", (void(ofxSmartParticle::*)(bool)) &ofxSmartParticle::setDistortion)
         .def("toggleDistortion", (void(ofxSmartParticle::*)(void)) &ofxSmartParticle::toggleDistortion)
         .def("setDistortVector", (void(ofxSmartParticle::*)(ofVec3f)) &ofxSmartParticle::setDistortVector),
         
         // ofxSmartParticleSystem
         class_<ofxSmartParticleSystem>("ofxSmartParticleSystem")
         .def(constructor<>())
         .def("clear", (void(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::clear)
         .def("update", (void(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::update)
         .def("updateAndDecay", (void(ofxSmartParticleSystem::*)(float,float)) &ofxSmartParticleSystem::updateAndDecay)
         .def("setDamping", (void(ofxSmartParticleSystem::*)(float)) &ofxSmartParticleSystem::setDamping)
         .def("setVelocityLimit", (void(ofxSmartParticleSystem::*)(float)) &ofxSmartParticleSystem::setVelocityLimit)
         .def("setAccerationLimit", (void(ofxSmartParticleSystem::*)(float)) &ofxSmartParticleSystem::setAccerationLimit)
         .def("randomize", (void(ofxSmartParticleSystem::*)(float)) &ofxSmartParticleSystem::randomize)
         .def("draw", (void(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::draw)
         .def("addParticle", (void(ofxSmartParticleSystem::*)(ofxSmartParticle*)) &ofxSmartParticleSystem::addParticle)
         .def("getCount", (int(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::getCount)
         .def("getParticle", (ofxParticle*(ofxSmartParticleSystem::*)(int)) &ofxSmartParticleSystem::getParticle)
         
         .def("setCenter", (void(ofxSmartParticleSystem::*)(ofVec3f*)) &ofxSmartParticleSystem::setCenter)
         .def("setTargetHome", (void(ofxSmartParticleSystem::*)(bool)) &ofxSmartParticleSystem::setTargetHome)
         .def("getTargetHome", (bool(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::getTargetHome)
         .def("toggleTargetHome", (void(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::toggleTargetHome)
         .def("setTargetSphere", (void(ofxSmartParticleSystem::*)(bool)) &ofxSmartParticleSystem::setTargetSphere)
         .def("getTargetSphere", (bool(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::getTargetSphere)
         .def("toggleTargetSphere", (void(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::toggleTargetSphere)
         .def("setSphericalRadius", (void(ofxSmartParticleSystem::*)(float)) &ofxSmartParticleSystem::setSphericalRadius)
         .def("getSphericalRadius", (float(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::getSphericalRadius)
         .def("setRandomizeVel", (void(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::setRandomizeVel)
         .def("setRandomizeVel", (void(ofxSmartParticleSystem::*)(float)) &ofxSmartParticleSystem::setRandomizeVel)
         .def("toggleDistortion", (void(ofxSmartParticleSystem::*)(void)) &ofxSmartParticleSystem::toggleDistortion)
         .def("setDistortion", (void(ofxSmartParticleSystem::*)(bool)) &ofxSmartParticleSystem::setDistortion)
         .def("setDistortVector", (void(ofxSmartParticleSystem::*)(ofVec3f*)) &ofxSmartParticleSystem::setDistortVector),
         
         // ofxSolver
         class_<ofxSolver>("ofxSolver")
         .def(constructor<float>())
         .def("update", (void(ofxSolver::*)(ofxRParticle&)) &ofxSolver::update)
         .def("getDt", (float(ofxSolver::*)(void)) &ofxSolver::getDt),
         
         // ofxSphericalAttractionBehavior
         class_<ofxSphericalAttractionBehavior>("ofxSphericalAttractionBehavior")
         .def(constructor<>())
         .def("update", (void(ofxSphericalAttractionBehavior::*)(void)) &ofxSphericalAttractionBehavior::update)
         .def("actUpon", (void(ofxSphericalAttractionBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxSphericalAttractionBehavior::actUpon)
         .def("isEnabled", (bool(ofxSphericalAttractionBehavior::*)(void)) &ofxSphericalAttractionBehavior::isEnabled)
         .def("getMagnitude", (float(ofxSphericalAttractionBehavior::*)(void)) &ofxSphericalAttractionBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxSphericalAttractionBehavior::*)(float)) &ofxSphericalAttractionBehavior::setMagnitude)
         
         .def("setup", (void(ofxSphericalAttractionBehavior::*)(void)) &ofxSphericalAttractionBehavior::setup)
         .def("getPosition", (ofVec3f&(ofxSphericalAttractionBehavior::*)(void)) &ofxSphericalAttractionBehavior::getPosition)
         .def("setPosition", (void(ofxSphericalAttractionBehavior::*)(ofVec3f)) &ofxSphericalAttractionBehavior::setPosition)
         .def("getRadius", (float(ofxSphericalAttractionBehavior::*)(void)) &ofxSphericalAttractionBehavior::getRadius)
         .def("setRadius", (void(ofxSphericalAttractionBehavior::*)(float)) &ofxSphericalAttractionBehavior::setRadius),
         
         // ofxSpring
         class_<ofxSpring>("ofxSpring")
         .def(constructor<>())
         .def("update", (void(ofxSpring::*)(float)) &ofxSpring::update)
         .def("draw", (void(ofxSpring::*)(void)) &ofxSpring::draw)
         .def("getForce", (ofVec3f&(ofxSpring::*)(int)) &ofxSpring::getForce)
         .def("setRestDistance", (void(ofxSpring::*)(float)) &ofxSpring::setRestDistance)
         .def("getRestDistance", (float(ofxSpring::*)(void)) &ofxSpring::getRestDistance)
         .def("getK", (float(ofxSpring::*)(void)) &ofxSpring::getK)
         .def("setK", (void(ofxSpring::*)(float)) &ofxSpring::setK)
         .def("getPos", (ofVec3f&(ofxSpring::*)(int)) &ofxSpring::getPos)
         .def("setID", (void(ofxSpring::*)(int)) &ofxSpring::setID)
         .def("getID", (int(ofxSpring::*)(void)) &ofxSpring::getID)
         .def("getDelta", (float(ofxSpring::*)(void)) &ofxSpring::getDelta)
         .def("setColor", (void(ofxSpring::*)(ofColor)) &ofxSpring::setColor)
         .def("getColor", (ofColor&(ofxSpring::*)(void)) &ofxSpring::getColor)
         .def("setColorAlpha", (void(ofxSpring::*)(float)) &ofxSpring::setColorAlpha)
         .def("getColorAlpha", (float(ofxSpring::*)(void)) &ofxSpring::getColorAlpha),
         
         // ofxSpringSystem
         class_<ofxSpringSystem>("ofxSpringSystem")
         .def(constructor<>())
         .def("clear", (void(ofxSpringSystem::*)(void)) &ofxSpringSystem::clear)
         .def("update", (void(ofxSpringSystem::*)(float)) &ofxSpringSystem::update)
         .def("draw", (void(ofxSpringSystem::*)(void)) &ofxSpringSystem::draw)
         .def("addSpring", (void(ofxSpringSystem::*)(ofxSpring)) &ofxSpringSystem::addSpring)
         .def("getCount", (int(ofxSpringSystem::*)(void)) &ofxSpringSystem::getCount)
         .def("getSpring", (ofxSpring(ofxSpringSystem::*)(int)) &ofxSpringSystem::getSpring)
         .def("setRestDistance", (void(ofxSpringSystem::*)(float)) &ofxSpringSystem::setRestDistance),
         
         // ofxSuperShape
         class_<ofxSuperShape>("ofxSuperShape")
         .def(constructor<>())
         .def("update", (void(ofxSuperShape::*)(void)) &ofxSuperShape::update)
         .def("setVelocityLimit", (void(ofxSuperShape::*)(float)) &ofxSuperShape::setVelocityLimit)
         .def("setAccerationLimit", (void(ofxSuperShape::*)(float)) &ofxSuperShape::setAccerationLimit)
         .def("setDamping", (void(ofxSuperShape::*)(float)) &ofxSuperShape::setDamping)
         .def("setRadius", (void(ofxSuperShape::*)(float,bool)) &ofxSuperShape::setRadius)
         .def("setA", (void(ofxSuperShape::*)(float,bool)) &ofxSuperShape::setA)
         .def("setB", (void(ofxSuperShape::*)(float,bool)) &ofxSuperShape::setB)
         .def("setM", (void(ofxSuperShape::*)(float,bool)) &ofxSuperShape::setM)
         .def("setN1", (void(ofxSuperShape::*)(float,bool)) &ofxSuperShape::setN1)
         .def("setN2", (void(ofxSuperShape::*)(float,bool)) &ofxSuperShape::setN2)
         .def("setN3", (void(ofxSuperShape::*)(float,bool)) &ofxSuperShape::setN3)
         .def("reset", (void(ofxSuperShape::*)(void)) &ofxSuperShape::reset),
         
         // ofxSwarmBehavior
         class_<ofxSwarmBehavior>("ofxSwarmBehavior")
         .def(constructor<>())
         .def("update", (void(ofxSwarmBehavior::*)(void)) &ofxSwarmBehavior::update)
         .def("actUpon", (void(ofxSwarmBehavior::*)(ofxRParticle,ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofxSwarmBehavior::actUpon)
         .def("isEnabled", (bool(ofxSwarmBehavior::*)(void)) &ofxSwarmBehavior::isEnabled)
         .def("getMagnitude", (float(ofxSwarmBehavior::*)(void)) &ofxSwarmBehavior::getMagnitude)
         .def("setMagnitude", (void(ofxSwarmBehavior::*)(float)) &ofxSwarmBehavior::setMagnitude)
         
         .def("setup", (void(ofxSwarmBehavior::*)(void)) &ofxSwarmBehavior::setup),
         
         // ofxTrailParticle
         class_<ofxTrailParticle>("ofxTrailParticle")
         .def(constructor<>())
         .def(constructor<ofVec3f>())
         .def(constructor<ofVec3f,int>())
         .def("setBorders", (void(ofxTrailParticle::*)(float,float)) &ofxTrailParticle::setBorders)
         .def("update", (void(ofxTrailParticle::*)(void)) &ofxTrailParticle::update)
         .def("draw", (void(ofxTrailParticle::*)(void)) &ofxTrailParticle::draw)
         .def("drawVertex", (void(ofxTrailParticle::*)(int)) &ofxTrailParticle::drawVertex)
         .def("borders", (void(ofxTrailParticle::*)(void)) &ofxTrailParticle::borders)
         .def("elasticBorder", (void(ofxTrailParticle::*)(float)) &ofxTrailParticle::elasticBorder)
         .def("circleborders", (void(ofxTrailParticle::*)(void)) &ofxTrailParticle::circleborders)
         .def("setRadius", (void(ofxTrailParticle::*)(float)) &ofxTrailParticle::setRadius)
         .def("setPos", (void(ofxTrailParticle::*)(ofVec3f)) &ofxTrailParticle::setPos)
         .def("setVel", (void(ofxTrailParticle::*)(ofVec3f)) &ofxTrailParticle::setVel)
         .def("setAcc", (void(ofxTrailParticle::*)(ofVec3f)) &ofxTrailParticle::setAcc)
         .def("setHome", (void(ofxTrailParticle::*)(ofVec3f)) &ofxTrailParticle::setHome)
         .def("setHome", (void(ofxTrailParticle::*)(float,float,float)) &ofxTrailParticle::setHome)
         .def("setColor", (void(ofxTrailParticle::*)(ofColor)) &ofxTrailParticle::setColor)
         .def("setDamping", (void(ofxTrailParticle::*)(float)) &ofxTrailParticle::setDamping)
         .def("setAccerationLimit", (void(ofxTrailParticle::*)(float)) &ofxTrailParticle::setAccerationLimit)
         .def("setVelocityLimit", (void(ofxTrailParticle::*)(float)) &ofxTrailParticle::setVelocityLimit)
         .def("addExternalForce", (void(ofxTrailParticle::*)(ofVec3f)) &ofxTrailParticle::addExternalForce)
         .def("addSpringForce", (void(ofxTrailParticle::*)(ofVec3f)) &ofxTrailParticle::addSpringForce)
         .def("setFixed", (void(ofxTrailParticle::*)(bool)) &ofxTrailParticle::setFixed)
         .def("isFixed", (bool(ofxTrailParticle::*)(void)) &ofxTrailParticle::isFixed)
         .def("addForce", (void(ofxTrailParticle::*)(ofVec3f)) &ofxTrailParticle::addForce)
         .def("getPos", (ofVec3f&(ofxTrailParticle::*)(void)) &ofxTrailParticle::getPos)
         .def("getHome", (ofVec3f&(ofxTrailParticle::*)(void)) &ofxTrailParticle::getHome)
         .def("getPpos", (ofVec3f&(ofxTrailParticle::*)(void)) &ofxTrailParticle::getPpos)
         .def("getVel", (ofVec3f&(ofxTrailParticle::*)(void)) &ofxTrailParticle::getVel)
         .def("getAcc", (ofVec3f&(ofxTrailParticle::*)(void)) &ofxTrailParticle::getAcc)
         .def("getColor", (ofColor&(ofxTrailParticle::*)(void)) &ofxTrailParticle::getColor)
         .def("setColorAlpha", (void(ofxTrailParticle::*)(float)) &ofxTrailParticle::setColorAlpha)
         .def("getColorAlpha", (float(ofxTrailParticle::*)(void)) &ofxTrailParticle::getColorAlpha)
         .def("getRadius", (float(ofxTrailParticle::*)(void)) &ofxTrailParticle::getRadius)
         .def("getID", (int(ofxTrailParticle::*)(void)) &ofxTrailParticle::getID)
         .def("setID", (void(ofxTrailParticle::*)(int)) &ofxTrailParticle::setID)
         .def("decay", (void(ofxTrailParticle::*)(float)) &ofxTrailParticle::decay)
         .def("getLifeTime", (float(ofxTrailParticle::*)(void)) &ofxTrailParticle::getLifeTime)
         .def("isDead", (bool(ofxTrailParticle::*)(void)) &ofxTrailParticle::isDead),
         
         // ofxVerletSolver
         class_<ofxVerletSolver>("ofxVerletSolver")
         .def(constructor<float>())
         .def("update", (void(ofxVerletSolver::*)(ofxRParticle&)) &ofxVerletSolver::update)
         .def("getDt", (float(ofxVerletSolver::*)(void)) &ofxVerletSolver::getDt),
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXJITTERNETWORKSENDER --> extending ofxTCPClient
         class_<ofxJitterNetworkSender>("ofxJitterNetworkSender")
         .def(constructor<>())
         
         .def("setVerbose", (void(ofxJitterNetworkSender::*)(bool)) &ofxJitterNetworkSender::setVerbose)
         .def("setup", (bool(ofxJitterNetworkSender::*)(string,int,bool)) &ofxJitterNetworkSender::setup)
         .def("setMessageDelimiter", (void(ofxJitterNetworkSender::*)(string)) &ofxJitterNetworkSender::setMessageDelimiter)
         .def("close", (bool(ofxJitterNetworkSender::*)(void)) &ofxJitterNetworkSender::close)
         .def("send", (bool(ofxJitterNetworkSender::*)(string)) &ofxJitterNetworkSender::send)
         .def("sendRaw", (bool(ofxJitterNetworkSender::*)(string)) &ofxJitterNetworkSender::sendRaw)
         .def("getNumReceivedBytes", (int(ofxJitterNetworkSender::*)(void)) &ofxJitterNetworkSender::getNumReceivedBytes)
         .def("sendRawBytes", (bool(ofxJitterNetworkSender::*)(const char*, const int)) &ofxJitterNetworkSender::sendRawBytes)
         .def("receive", (string(ofxJitterNetworkSender::*)(void)) &ofxJitterNetworkSender::receive)
         .def("receiveRaw", (string(ofxJitterNetworkSender::*)(void)) &ofxJitterNetworkSender::receiveRaw)
         .def("receiveRawBytes", (int(ofxJitterNetworkSender::*)(const char*,int)) &ofxJitterNetworkSender::receiveRawBytes)
         .def("isConnected", (bool(ofxJitterNetworkSender::*)(void)) &ofxJitterNetworkSender::isConnected)
         .def("getPort", (int(ofxJitterNetworkSender::*)(void)) &ofxJitterNetworkSender::getPort)
         .def("getIP", (string(ofxJitterNetworkSender::*)(void)) &ofxJitterNetworkSender::getIP)
         .def("setup", (bool(ofxJitterNetworkSender::*)(int,bool)) &ofxJitterNetworkSender::setup)
         
         .def("sendFrame", (void(ofxJitterNetworkSender::*)(const ofPixelsRef)) &ofxJitterNetworkSender::sendFrame)
         .def("sendText", (void(ofxJitterNetworkSender::*)(const string&)) &ofxJitterNetworkSender::sendText),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXKINECT
         class_<ofxKinect>("ofxKinect")
         .def(constructor<>())
         .def("init", (bool(ofxKinect::*)(bool,bool,bool)) &ofxKinect::init)
         .def("clear", (void(ofxKinect::*)(void)) &ofxKinect::clear)
         .def("setRegistration", (void(ofxKinect::*)(bool)) &ofxKinect::setRegistration)
         .def("open", (bool(ofxKinect::*)(int)) &ofxKinect::open)
         .def("open", (bool(ofxKinect::*)(string)) &ofxKinect::open)
         .def("close", (void(ofxKinect::*)(void)) &ofxKinect::close)
         .def("isConnected", (bool(ofxKinect::*)(void)) &ofxKinect::isConnected)
         .def("isFrameNew", (bool(ofxKinect::*)(void)) &ofxKinect::isFrameNew)
         .def("update", (void(ofxKinect::*)(void)) &ofxKinect::update)
         .def("getDistanceAt", (float(ofxKinect::*)(int,int)) &ofxKinect::getDistanceAt)
         .def("getDistanceAt", (float(ofxKinect::*)(const ofPoint&)) &ofxKinect::getDistanceAt)
         .def("getWorldCoordinateAt", (ofVec3f(ofxKinect::*)(int,int)) &ofxKinect::getWorldCoordinateAt)
         .def("getWorldCoordinateAt", (ofVec3f(ofxKinect::*)(float,float,float)) &ofxKinect::getWorldCoordinateAt)
         .def("getColorAt", (ofColor(ofxKinect::*)(int,int)) &ofxKinect::getColorAt)
         .def("getColorAt", (ofColor(ofxKinect::*)(const ofPoint&)) &ofxKinect::getColorAt)
         .def("getRawAccel", (ofPoint(ofxKinect::*)(void)) &ofxKinect::getRawAccel)
         .def("getMksAccel", (ofPoint(ofxKinect::*)(void)) &ofxKinect::getMksAccel)
         .def("getAccelPitch", (float(ofxKinect::*)(void)) &ofxKinect::getAccelPitch)
         .def("getAccelRoll", (float(ofxKinect::*)(void)) &ofxKinect::getAccelRoll)
         .def("getPixels", (unsigned char*(ofxKinect::*)(void)) &ofxKinect::getPixels)
         .def("getDepthPixels", (unsigned char*(ofxKinect::*)(void)) &ofxKinect::getDepthPixels)
         .def("getRawDepthPixels", (unsigned short*(ofxKinect::*)(void)) &ofxKinect::getRawDepthPixels)
         .def("getDistancePixels", (float*(ofxKinect::*)(void)) &ofxKinect::getDistancePixels)
         .def("getPixelsRef", (ofPixels&(ofxKinect::*)(void)) &ofxKinect::getPixelsRef)
         .def("getDepthPixelsRef", (ofPixels&(ofxKinect::*)(void)) &ofxKinect::getDepthPixelsRef)
         .def("getRawDepthPixelsRef", (ofShortPixels&(ofxKinect::*)(void)) &ofxKinect::getRawDepthPixelsRef)
         .def("getDistancePixelsRef", (ofFloatPixels&(ofxKinect::*)(void)) &ofxKinect::getDistancePixelsRef)
         .def("getTextureReference", (ofTexture&(ofxKinect::*)(void)) &ofxKinect::getTextureReference)
         .def("getDepthTextureReference", (ofTexture&(ofxKinect::*)(void)) &ofxKinect::getDepthTextureReference)
         .def("enableDepthNearValueWhite", (void(ofxKinect::*)(bool)) &ofxKinect::enableDepthNearValueWhite)
         .def("isDepthNearValueWhite", (bool(ofxKinect::*)(void)) &ofxKinect::isDepthNearValueWhite)
         .def("setDepthClipping", (void(ofxKinect::*)(float,float)) &ofxKinect::setDepthClipping)
         .def("getNearClipping", (float(ofxKinect::*)(void)) &ofxKinect::getNearClipping)
         .def("getFarClipping", (float(ofxKinect::*)(void)) &ofxKinect::getFarClipping)
         .def("setCameraTiltAngle", (bool(ofxKinect::*)(float)) &ofxKinect::setCameraTiltAngle)
         .def("getCurrentCameraTiltAngle", (float(ofxKinect::*)(void)) &ofxKinect::getCurrentCameraTiltAngle)
         .def("getTargetCameraTiltAngle", (float(ofxKinect::*)(void)) &ofxKinect::getTargetCameraTiltAngle)
         .def("setLed", (void(ofxKinect::*)(ofxKinect::LedMode)) &ofxKinect::setLed)
         .def("setUseTexture", (void(ofxKinect::*)(bool)) &ofxKinect::setUseTexture)
         .def("draw", (void(ofxKinect::*)(float,float,float,float)) &ofxKinect::draw)
         .def("draw", (void(ofxKinect::*)(float,float)) &ofxKinect::draw)
         .def("draw", (void(ofxKinect::*)(const ofPoint&)) &ofxKinect::draw)
         .def("draw", (void(ofxKinect::*)(const ofRectangle&)) &ofxKinect::draw)
         .def("drawDepth", (void(ofxKinect::*)(float,float,float,float)) &ofxKinect::drawDepth)
         .def("drawDepth", (void(ofxKinect::*)(float,float)) &ofxKinect::drawDepth)
         .def("drawDepth", (void(ofxKinect::*)(const ofPoint&)) &ofxKinect::drawDepth)
         .def("drawDepth", (void(ofxKinect::*)(const ofRectangle&)) &ofxKinect::drawDepth)
         .def("getDeviceId", (int(ofxKinect::*)(void)) &ofxKinect::getDeviceId)
         .def("getSerial", (string(ofxKinect::*)(void)) &ofxKinect::getSerial)
         .def("getHeight", (float(ofxKinect::*)(void)) &ofxKinect::getHeight)
         .def("getWidth", (float(ofxKinect::*)(void)) &ofxKinect::getWidth)
         .def("listDevices", (void(ofxKinect::*)(void)) &ofxKinect::listDevices)
         .def("numTotalDevices", (int(ofxKinect::*)(void)) &ofxKinect::numTotalDevices)
         .def("numAvailableDevices", (int(ofxKinect::*)(void)) &ofxKinect::numAvailableDevices)
         .def("numConnectedDevices", (int(ofxKinect::*)(void)) &ofxKinect::numConnectedDevices)
         .def("isDeviceConnected", (bool(ofxKinect::*)(int)) &ofxKinect::isDeviceConnected)
         .def("isDeviceConnected", (bool(ofxKinect::*)(string)) &ofxKinect::isDeviceConnected)
         .def("nextAvailableId", (int(ofxKinect::*)(void)) &ofxKinect::nextAvailableId)
         .def("nextAvailableSerial", (string(ofxKinect::*)(void)) &ofxKinect::nextAvailableSerial),
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXMISSING
         def("ofxGetDateTimeAsString", (string(*)(string)) &getDateTimeAsString),
         def("ofxMD5", (string(*)(string)) &md5),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXOPTICALFLOWLK
         class_<ofxOpticalFlowLK>("ofxOpticalFlowLK")
         .def(constructor<>())
         .def("setup", (void(ofxOpticalFlowLK::*)(const ofRectangle&)) &ofxOpticalFlowLK::setup)
         .def("setup", (void(ofxOpticalFlowLK::*)(int,int)) &ofxOpticalFlowLK::setup)
         .def("setup", (void(ofxOpticalFlowLK::*)(int,int,double,int,int,int,int,double,bool,bool)) &ofxOpticalFlowLK::setup)
         .def("reset", (void(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::reset)
         .def("destroy", (void(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::destroy)
         .def("update", (void(ofxOpticalFlowLK::*)(ofImage&)) &ofxOpticalFlowLK::update)
         .def("update", (void(ofxOpticalFlowLK::*)(ofxCvColorImage&)) &ofxOpticalFlowLK::update)
         .def("update", (void(ofxOpticalFlowLK::*)(ofxCvGrayscaleImage&)) &ofxOpticalFlowLK::update)
         .def("update", (void(ofxOpticalFlowLK::*)(ofVideoPlayer&)) &ofxOpticalFlowLK::update)
         .def("update", (void(ofxOpticalFlowLK::*)(ofVideoGrabber&)) &ofxOpticalFlowLK::update)
         .def("update", (void(ofxOpticalFlowLK::*)(unsigned char* pixels,int,int,int)) &ofxOpticalFlowLK::update)
         .def("getVelAtNorm", (ofPoint(ofxOpticalFlowLK::*)(float,float)) &ofxOpticalFlowLK::getVelAtNorm)
         .def("getVelAtPixel", (ofPoint(ofxOpticalFlowLK::*)(int,int)) &ofxOpticalFlowLK::getVelAtPixel)
         .def("draw", (void(ofxOpticalFlowLK::*)(int,int,float,int)) &ofxOpticalFlowLK::draw)
         .def("drawColored", (void(ofxOpticalFlowLK::*)(int,int,float,int)) &ofxOpticalFlowLK::drawColored)
         .def("setMirror", (void(ofxOpticalFlowLK::*)(bool,bool)) &ofxOpticalFlowLK::setMirror)
         .def("isInitialized", (bool(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::isInitialized)
         .def("getPyramidScale", (double(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getPyramidScale)
         .def("getPyramidLevels", (int(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getPyramidLevels)
         .def("getWindowSize", (int(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getWindowSize)
         .def("getIterationsPerLevel", (int(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getIterationsPerLevel)
         .def("getExpansionArea", (int(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getExpansionArea)
         .def("getExpansionSigma", (double(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getExpansionSigma)
         .def("getFlowFeedback", (bool(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getFlowFeedback)
         .def("getGaussianFiltering", (bool(ofxOpticalFlowLK::*)(void)) &ofxOpticalFlowLK::getGaussianFiltering)
         .def("setPyramidScale", (void(ofxOpticalFlowLK::*)(double)) &ofxOpticalFlowLK::setPyramidScale)
         .def("setPyramidLevels", (void(ofxOpticalFlowLK::*)(int)) &ofxOpticalFlowLK::setPyramidLevels)
         .def("setWindowSize", (void(ofxOpticalFlowLK::*)(int)) &ofxOpticalFlowLK::setWindowSize)
         .def("setIterationsPerLevel", (void(ofxOpticalFlowLK::*)(int)) &ofxOpticalFlowLK::setIterationsPerLevel)
         .def("setExpansionArea", (void(ofxOpticalFlowLK::*)(int)) &ofxOpticalFlowLK::setExpansionArea)
         .def("setExpansionSigma", (void(ofxOpticalFlowLK::*)(double)) &ofxOpticalFlowLK::setExpansionSigma)
         .def("setFlowFeedback", (void(ofxOpticalFlowLK::*)(bool)) &ofxOpticalFlowLK::setFlowFeedback)
         .def("setGaussianFiltering", (void(ofxOpticalFlowLK::*)(bool)) &ofxOpticalFlowLK::setGaussianFiltering),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXPBO
         class_<ofxPBO>("ofxPBO")
         .def(constructor<>())
         .def("allocate", (void(ofxPBO::*)(ofTexture&,int)) &ofxPBO::allocate)
         .def("loadData", (void(ofxPBO::*)(const ofPixels&)) &ofxPBO::loadData)
         .def("updateTexture", (void(ofxPBO::*)(void)) &ofxPBO::updateTexture),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXPBOVIDEOPLAYER
         class_<ofxPBOVideoPlayer>("ofxPBOVideoPlayer")
         .def(constructor<>())
         .def("load", (void(ofxPBOVideoPlayer::*)(string)) &ofxPBOVideoPlayer::load)
         .def("play", (void(ofxPBOVideoPlayer::*)(void)) &ofxPBOVideoPlayer::play)
         .def("update", (void(ofxPBOVideoPlayer::*)(void)) &ofxPBOVideoPlayer::update)
         .def("draw", (void(ofxPBOVideoPlayer::*)(void)) &ofxPBOVideoPlayer::draw)
         .def("isFrameNew", (bool(ofxPBOVideoPlayer::*)(void)) &ofxPBOVideoPlayer::isFrameNew)
         .def_readwrite("player", &ofxPBOVideoPlayer::player),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXQRCODEGENERATOR
         class_<ofxQRCodeGenerator>("ofxQRCodeGenerator")
         .def(constructor<>())
         .def("generate",&QRgenerate),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXQTKITAVSCREENRECORDER
         class_<ofxQTKitAVScreenRecorder>("ofxQTKitAVScreenRecorder")
         .def(constructor<>())
         .def("setup", (void(ofxQTKitAVScreenRecorder::*)(string,string)) &ofxQTKitAVScreenRecorder::setup)
         .def("update", (void(ofxQTKitAVScreenRecorder::*)(void)) &ofxQTKitAVScreenRecorder::update)
         .def("exit", (void(ofxQTKitAVScreenRecorder::*)(void)) &ofxQTKitAVScreenRecorder::exit)
         .def("initAudio", (void(ofxQTKitAVScreenRecorder::*)(string,string)) &ofxQTKitAVScreenRecorder::initAudio)
         .def("initAVRecording", (void(ofxQTKitAVScreenRecorder::*)(string)) &ofxQTKitAVScreenRecorder::initAVRecording)
         .def("startNewRecording", (void(ofxQTKitAVScreenRecorder::*)(string)) &ofxQTKitAVScreenRecorder::startNewRecording)
         .def("finishMovie", (void(ofxQTKitAVScreenRecorder::*)(bool)) &ofxQTKitAVScreenRecorder::finishMovie)
         .def("addFrame", (void(ofxQTKitAVScreenRecorder::*)(ofPixels&)) &ofxQTKitAVScreenRecorder::addFrame)
         .def("listAudioDevices", (string*(ofxQTKitAVScreenRecorder::*)(void)) &ofxQTKitAVScreenRecorder::listAudioDevices)
         .def("listAudioCodecs", (string*(ofxQTKitAVScreenRecorder::*)(void)) &ofxQTKitAVScreenRecorder::listAudioCodecs)
         .def("getIsRecording", (bool(ofxQTKitAVScreenRecorder::*)(void)) &ofxQTKitAVScreenRecorder::getIsRecording),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXSLITSCAN
         class_<ofxSlitScan>("ofxSlitScan")
         .def(constructor<>())
         .def("setup", (void(ofxSlitScan::*)(int,int,int)) &ofxSlitScan::setup)
         .def("setup", (void(ofxSlitScan::*)(int,int,int,int)) &ofxSlitScan::setup)
         .def("isSetup", (bool(ofxSlitScan::*)(void)) &ofxSlitScan::isSetup)
         .def("setDelayMap", (void(ofxSlitScan::*)(ofImage)) &ofxSlitScan::setDelayMap)
         .def("addImage", (void(ofxSlitScan::*)(ofImage)) &ofxSlitScan::addImage)
         .def("addImage", (void(ofxSlitScan::*)(unsigned char*)) &ofxSlitScan::addImage)
         .def("getOutputImage", (ofImage*(ofxSlitScan::*)(void)) &ofxSlitScan::getOutputImage)
         .def("getDelayMap", (ofImage*(ofxSlitScan::*)(void)) &ofxSlitScan::getDelayMap)
         .def("pixelsForFrame", (void(ofxSlitScan::*)(int,unsigned char*)) &ofxSlitScan::pixelsForFrame)
         .def("setCapacity", (void(ofxSlitScan::*)(int)) &ofxSlitScan::setCapacity)
         .def("setTimeDelayAndWidth", (void(ofxSlitScan::*)(int,int)) &ofxSlitScan::setTimeDelayAndWidth)
         .def("setTimeDelay", (void(ofxSlitScan::*)(int)) &ofxSlitScan::setTimeDelay)
         .def("setTimeWidth", (void(ofxSlitScan::*)(int)) &ofxSlitScan::setTimeWidth)
         .def("setBlending", (int(ofxSlitScan::*)(bool)) &ofxSlitScan::setBlending)
         .def("toggleBlending", (void(ofxSlitScan::*)(void)) &ofxSlitScan::toggleBlending)
         .def("getTimeDelay", (int(ofxSlitScan::*)(void)) &ofxSlitScan::getTimeDelay)
         .def("getTimeWidth", (int(ofxSlitScan::*)(void)) &ofxSlitScan::getTimeWidth)
         .def("getWidth", (int(ofxSlitScan::*)(void)) &ofxSlitScan::getWidth)
         .def("getHeight", (int(ofxSlitScan::*)(void)) &ofxSlitScan::getHeight)
         .def("getCapacity", (int(ofxSlitScan::*)(void)) &ofxSlitScan::getCapacity)
         .def("getType", (int(ofxSlitScan::*)(void)) &ofxSlitScan::getType)
         .def("isBlending", (bool(ofxSlitScan::*)(void)) &ofxSlitScan::isBlending),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXSUBTITLES
         class_<ofxSubtitles>("ofxSubtitles")
         .def(constructor<>())
         .def("load", (void(ofxSubtitles::*)(const string&)) &ofxSubtitles::load)
         .def("save", (void(ofxSubtitles::*)(const string&)) &ofxSubtitles::save)
         .def("add", (void(ofxSubtitles::*)(float,string)) &ofxSubtitles::add)
         .def("add", (void(ofxSubtitles::*)(float,float,string)) &ofxSubtitles::add)
         .def("getHowMany", (int(ofxSubtitles::*)(float,float)) &ofxSubtitles::getHowMany)
         .def("getFirstSubN", (int(ofxSubtitles::*)(float)) &ofxSubtitles::getFirstSubN)
         .def("getLineAt", (string(ofxSubtitles::*)(float)) &ofxSubtitles::getLineAt)
         .def("isStringAt", (bool(ofxSubtitles::*)(string,float)) &ofxSubtitles::isStringAt)
         .def("replace", (void(ofxSubtitles::*)(string,string,float)) &ofxSubtitles::replace)
         .def("loadfont", (void(ofxSubtitles::*)(string,int)) &ofxSubtitles::loadfont)
         .def("setScreen", (void(ofxSubtitles::*)(int,int)) &ofxSubtitles::setScreen)
         .def("setColor", (void(ofxSubtitles::*)(int,int,int)) &ofxSubtitles::setColor)
         .def("setColor", (void(ofxSubtitles::*)(int,int,int,int)) &ofxSubtitles::setColor)
         .def("draw", (void(ofxSubtitles::*)(float)) &ofxSubtitles::draw)
         .def("draw", (void(ofxSubtitles::*)(int,int,float)) &ofxSubtitles::draw)
         .def("draw", (void(ofxSubtitles::*)(int,int,int,int,float)) &ofxSubtitles::draw),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXSYPHON
         class_<ofxSyphonClient>("ofxSyphonClient")
         .def(constructor<>())
         .def("setup", (void(ofxSyphonClient::*)(void)) &ofxSyphonClient::setup)
         .def("setServerName", (void(ofxSyphonClient::*)(string)) &ofxSyphonClient::setServerName)
         .def("getWidth", (float(ofxSyphonClient::*)(void)) &ofxSyphonClient::getWidth)
         .def("getHeight", (float(ofxSyphonClient::*)(void)) &ofxSyphonClient::getHeight)
         .def("draw", (void(ofxSyphonClient::*)(float,float)) &ofxSyphonClient::draw)
         .def("draw", (void(ofxSyphonClient::*)(float,float,float,float)) &ofxSyphonClient::draw),
         
         class_<ofxSyphonServer>("ofxSyphonServer")
         .def(constructor<>())
         .def("setName", (void(ofxSyphonServer::*)(string)) &ofxSyphonServer::setName)
         .def("getName", (string(ofxSyphonServer::*)(void)) &ofxSyphonServer::getName)
         .def("publishScreen", (void(ofxSyphonServer::*)(void)) &ofxSyphonServer::publishScreen)
         .def("publishTexture", (void(ofxSyphonServer::*)(ofTexture)) &ofxSyphonServer::publishTexture),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXTEXTSUITE
         class_<ofxTextBlock>("ofxTextBlock")
         .def(constructor<>())
         .def("init", (void(ofxTextBlock::*)(string,float)) &ofxTextBlock::init)
         .def("setText", (void(ofxTextBlock::*)(string)) &ofxTextBlock::setText)
		 .def("wrapTextX", (int(ofxTextBlock::*)(float)) &ofxTextBlock::wrapTextX)
         .def("wrapTextArea", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::wrapTextArea)
         .def("wrapTextForceLines", (bool(ofxTextBlock::*)(int)) &ofxTextBlock::wrapTextForceLines)
         .def("setLineHeight", (void(ofxTextBlock::*)(float)) &ofxTextBlock::setLineHeight)
         .def("setColor", (void(ofxTextBlock::*)(int,int,int,int)) &ofxTextBlock::setColor)
         .def("draw", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::draw)
         .def("drawLeft", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::drawLeft)
         .def("drawRight", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::drawRight)
         .def("drawCenter", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::drawCenter)
         .def("drawJustified", (void(ofxTextBlock::*)(float,float,float)) &ofxTextBlock::drawJustified)
         .def("forceScale", (void(ofxTextBlock::*)(float)) &ofxTextBlock::forceScale)
         .def("getWidth", (float(ofxTextBlock::*)(void)) &ofxTextBlock::getWidth)
		 .def("getHeight", (float(ofxTextBlock::*)(void)) &ofxTextBlock::getHeight),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXTHERMITRACK
         class_<ofxThermitrack>("ofxThermitrack")
         .def(constructor<>())
         .def("setup", (void(ofxThermitrack::*)(string,int,int)) &ofxThermitrack::setup)
         .def("update", (void(ofxThermitrack::*)(void)) &ofxThermitrack::update)
         .def("flushCameraBuffer", (void(ofxThermitrack::*)(void)) &ofxThermitrack::flushCameraBuffer)
         .def("getVersion", (void(ofxThermitrack::*)(void)) &ofxThermitrack::getVersion)
         .def("setBaudRate", (void(ofxThermitrack::*)(void)) &ofxThermitrack::setBaudRate)
         .def("factoryReset", (void(ofxThermitrack::*)(void)) &ofxThermitrack::factoryReset)
         .def("clearRequestedPacketTypes", (void(ofxThermitrack::*)(void)) &ofxThermitrack::clearRequestedPacketTypes)
         .def("addRequestedPacketType", (void(ofxThermitrack::*)(char,int)) &ofxThermitrack::addRequestedPacketType)
         .def("updateRequestedPacketTypeOnCamera", (void(ofxThermitrack::*)(void)) &ofxThermitrack::updateRequestedPacketTypeOnCamera)
         .def("setRequestedPacketTypeNone", (void(ofxThermitrack::*)(void)) &ofxThermitrack::setRequestedPacketTypeNone)
         .def("getStatus", (int(ofxThermitrack::*)(void)) &ofxThermitrack::getStatus)
         .def("isCamOK", (bool(ofxThermitrack::*)(void)) &ofxThermitrack::isCamOK)
         .def("isSerialOK", (bool(ofxThermitrack::*)(void)) &ofxThermitrack::isSerialOK)
         .def("setDefaultPacket", (void(ofxThermitrack::*)(thermitrackPacketList)) &ofxThermitrack::setDefaultPacket)
         .def("setDefaultPacketNone", (void(ofxThermitrack::*)(void)) &ofxThermitrack::setDefaultPacketNone)
         .def("setParameters", (void(ofxThermitrack::*)(int,int)) &ofxThermitrack::setParameters)
         .def("sendPacketType", (void(ofxThermitrack::*)(thermitrackPacketList)) &ofxThermitrack::sendPacketType)
         .def("reset", (void(ofxThermitrack::*)(void)) &ofxThermitrack::reset)
         .def("getPackets", (void(ofxThermitrack::*)(void)) &ofxThermitrack::getPackets)
         .def("waitForPackets", (void(ofxThermitrack::*)(void)) &ofxThermitrack::waitForPackets),
         
         class_<ofxThermitrackImage>("ofxThermitrackImage")
         .def(constructor<>())
         .def("setup", (void(ofxThermitrackImage::*)(int)) &ofxThermitrackImage::setup)
         .def("update", (void(ofxThermitrackImage::*)(ofxThermitrack*)) &ofxThermitrackImage::update)
         .def("draw", (void(ofxThermitrackImage::*)(int,int,int,int)) &ofxThermitrackImage::draw),
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXTRUETYPEFONTUC
         class_<ofxTrueTypeFontUC>("ofxTrueTypeFontUC")
         .def(constructor<>())
         .def("loadFont", &loadFont2UC)
		 .def("loadFont", &loadFont4UC)
         .def("loadFont", (bool(ofxTrueTypeFontUC::*)(string,int,bool,bool,float,int)) &ofxTrueTypeFontUC::loadFont)
		 .def("isLoaded", (bool(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::isLoaded)
         .def("isAntiAliased", (bool(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::isAntiAliased)
		 .def("getLineHeight", (float(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getLineHeight)
		 .def("setLineHeight", (void(ofxTrueTypeFontUC::*)(float)) &ofxTrueTypeFontUC::setLineHeight)
		 .def("getLetterSpacing", (float(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getLetterSpacing)
		 .def("setLetterSpacing", (void(ofxTrueTypeFontUC::*)(float)) &ofxTrueTypeFontUC::setLetterSpacing)
		 .def("getSpaceSize", (float(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getSpaceSize)
		 .def("setSpaceSize", (void(ofxTrueTypeFontUC::*)(float)) &ofxTrueTypeFontUC::setSpaceSize)
         .def("stringWidth", (float(ofxTrueTypeFontUC::*)(string)) &ofxTrueTypeFontUC::stringWidth)
		 .def("stringHeight", (float(ofxTrueTypeFontUC::*)(string)) &ofxTrueTypeFontUC::stringHeight)
         .def("getStringBoundingBox", (ofRectangle(ofxTrueTypeFontUC::*)(string,float,float)) &ofxTrueTypeFontUC::getStringBoundingBox)
         .def("drawString", (void(ofxTrueTypeFontUC::*)(string,float,float)) &ofxTrueTypeFontUC::drawString)
		 .def("drawStringAsShapes", (void(ofxTrueTypeFontUC::*)(string,float,float)) &ofxTrueTypeFontUC::drawStringAsShapes),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXTWITTER
         class_<ofxTwitter>("ofxTwitter")
         .def(constructor<>())
         .def("setup", (void(ofxTwitter::*)(void)) &ofxTwitter::setup)
         .def("startTwitterQuery", (void(ofxTwitter::*)(string,int,int)) &ofxTwitter::startTwitterQuery)
         .def("getResponse", (ofxTweet(ofxTwitter::*)(int)) &ofxTwitter::getResponse)
         .def("getTotalResponse", (int(ofxTwitter::*)(void)) &ofxTwitter::getTotalResponse)
         .def("clear", (void(ofxTwitter::*)(void)) &ofxTwitter::clear),
         
         class_<ofxTweet>("ofxTweet")
         .def(constructor<>())
         .def(constructor<string>())
         .def("getTitle", (string(ofxTweet::*)(void)) &ofxTweet::getTitle)
         .def("getLink", (string(ofxTweet::*)(void)) &ofxTweet::getLink)
         .def("getDate", (string(ofxTweet::*)(void)) &ofxTweet::getDate)
         .def("getUpdated", (string(ofxTweet::*)(void)) &ofxTweet::getUpdated)
         .def("getID", (string(ofxTweet::*)(void)) &ofxTweet::getID)
         .def("getLanguage", (string(ofxTweet::*)(void)) &ofxTweet::getLanguage)
         .def("getAuthorName", (string(ofxTweet::*)(void)) &ofxTweet::getAuthorName)
         .def("getAvatar", (string(ofxTweet::*)(void)) &ofxTweet::getAvatar)
         .def("getAuthorUrl", (string(ofxTweet::*)(void)) &ofxTweet::getAuthorUrl),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
         //////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXVECTORFIELD
         class_<ofxVectorField>("ofxVectorField")
         .def(constructor<>())
         .def("setup", (void(ofxVectorField::*)(int,int,int)) &ofxVectorField::setup)
         .def("deallocate", (void(ofxVectorField::*)(void)) &ofxVectorField::deallocate)
         .def("draw", (void(ofxVectorField::*)(void)) &ofxVectorField::draw)
         .def("setFromImage", (void(ofxVectorField::*)(ofImage&)) &ofxVectorField::setFromImage)
         .def("randomize", (void(ofxVectorField::*)(void)) &ofxVectorField::randomize)
         .def("animate", (void(ofxVectorField::*)(float)) &ofxVectorField::animate)
         .def("getVector", (ofVec2f(ofxVectorField::*)(int,int)) &ofxVectorField::getVector)
         .def("getVectorInterpolated", (ofVec2f(ofxVectorField::*)(int,int,int,int)) &ofxVectorField::getVectorInterpolated)
         .def("normalize", (void(ofxVectorField::*)(bool)) &ofxVectorField::normalize)
         .def("map", (void(ofxVectorField::*)(float,float,bool)) &ofxVectorField::map)
         .def("scale", (void(ofxVectorField::*)(float)) &ofxVectorField::scale)
         .def("bias", (void(ofxVectorField::*)(float)) &ofxVectorField::bias)
         .def("bias", (void(ofxVectorField::*)(float,float)) &ofxVectorField::bias)
         .def("blur", (void(ofxVectorField::*)(void)) &ofxVectorField::blur)
         .def("smudge", (void(ofxVectorField::*)(ofVec2f,ofVec2f)) &ofxVectorField::smudge)
         .def_readwrite("width", &ofxVectorField::width)
         .def_readwrite("height", &ofxVectorField::height),
         //////////////////////////////////////////////////////////////////////////////////////////////////
         
		//////////////////////////////////////////////////////////////
		///////////////////////////////
		/// gamuza core api wrapper
         ///////////////////////////////
		 // app section
         def("gaKey", &getKey),
         def("gaMouseX", &getMouseX),
		 def("gaMouseY", &getMouseY),
         def("gaSystem", &system),
         def("gaLog", (void(*)(string)) &gaLog),
         def("gaImportFile", (string(*)(string)) &gaGetLocalDataPath),
         def("gaDataPath", (string(*)(string)) &gaGetLocalDataPath),
         def("gaSendingOscTo", (string(*)(void)) &gaGetOSCSendingIP),
         def("gaGetFrameNum", (int(*)(void)) &gaGetFrameNum),
         
         ///////////////////////////////
		 // GUI section
         def("gaGuiLoadXML", (void(*)(void)) &gaLoadXmlGUI),
         def("gaGuiToggle", (void(*)(void)) &gaToggleGUI),
         def("gaGuiPrevPage", (void(*)(void)) &gaPrevPageGUI),
         def("gaGuiNextPage", (void(*)(void)) &gaNextPageGUI),
         def("gaGuiDraw", (void(*)(void)) &gaDrawGUI),
         def("gaGuiSetPage", (void(*)(int)) &gaSetPageGUI),
         def("gaGuiAddFPS", (void(*)(void)) &gaFPSCpunterGUI),
         def("gaGuiAddTitle", (void(*)(string)) &gaAddTitleGUI),
         def("gaGuiAddPage", (void(*)(string,string)) &gaAddPageGUI),
         def("gaGuiAddSliderInt", (void(*)(string,int,int)) &gaAddSliderIntGUI),
         def("gaGuiAddSliderFloat", (void(*)(string,float,float,float)) &gaAddSliderFloatGUI),
         def("gaGuiAddToggle", (void(*)(string)) &gaAddToggleGUI),
         def("gaGuiAddButton", (void(*)(string)) &gaAddButtonGUI),
         
         ///////////////////////////////
		 // string section
         def("gaStringReplace", (int(*)(string&,string,string)) &gaStringReplace),
         
		 ///////////////////////////////
		 // graphics section
		 def("gaBackground", (void(*)(float,float)) &gaBackground),
		 def("gaBackground", (void(*)(float,float,float,float)) &gaBackground),
		 def("gaCameraTexture", (ofTexture(*)(int)) &gaGetWebcamTexture),
         def("gaCameraPixels", (unsigned char*(*)(int)) &gaGetWebcamPixels),
         def("gaCameraPixelsRef", (ofPixelsRef(*)(int)) &gaGetWebcamPixelsRef),
         def("gaSaveFrame", (void(*)(string)) &gaSaveFrame),
         def("gaGetOutputPixels", (ofPixels(*)(void)) &gaGetOutputPixels),
         def("gaGetOutputTexture", (ofTexture(*)(void)) &gaGetOutputTexture),
         
         ///////////////////////////////
		 // 3D section
         def("gaDrawAxis", (void(*)(float,ofColor,bool)) &gaDrawAxis),
         def("gaDrawXAxis", (void(*)(float,ofColor,bool)) &gaDrawXAxis),
         def("gaDrawYAxis", (void(*)(float,ofColor,bool)) &gaDrawYAxis),
         def("gaDrawZAxis", (void(*)(float,ofColor,bool)) &gaDrawZAxis),
         
         ///////////////////////////////
         // MATH section
         def("gaGaussianFn", (float(*)(float,float,float,float)) &gaGaussianFn),
         
         /////////////////////////////// (TIMELINE Module)
		 // timeline section
         def("gaTimelineSetup", (void(*)(string,string)) &gaSetupTimeline),
         def("gaTimelineSetPageName", (void(*)(string)) &gaSetTimelinePageName),
         def("gaTimelineSetCurrentPage", (void(*)(string)) &gaSetTimelineCurrentPage),
         def("gaTimelinePlay", (void(*)(void)) &gaPlayTimeline),
         def("gaTimelineStop", (void(*)(void)) &gaStopTimeline),
         def("gaTimelineDurationInFrames", (void(*)(int)) &gaSetTimelineDurationInFrames),
         def("gaTimelineDurationInSeconds", (void(*)(int)) &gaSetTimelineDurationInSeconds),
         def("gaTimelineEnableKeySnap", (void(*)(bool)) &gaSetTimelineEnableSnap),
         def("gaTimelineSetLoopType", (void(*)(int)) &gaSetTimelineLoopType),
         def("gaTimelineSetFrameRate", (void(*)(int)) &gaTimelineSetFrameRate),
         def("gaTimelineSetBPM", (void(*)(int)) &gaTimelineSetBPM),
         def("gaTimelineEnableBPMSnap", (void(*)(bool)) &gaTimelineEnableSnapToBPM),
         def("gaTimelineShowBPMGrid", (void(*)(bool)) &gaTimelineSetShowBPMGrid),
         def("gaTimelineSetTimecontrolTrack", (void(*)(string)) &gaTimelineSetTimecontrolTrack),
         def("gaTimelineBringTrackToTop", (void(*)(string)) &gaTimelineBringTrackToTop),
         def("gaTimelineBringVideoTrackToTop", (void(*)(string)) &gaTimelineBringVideoTrackToTop),
         def("gaTimelineBringAudioTrackToTop", (void(*)(string)) &gaTimelineBringAudioTrackToTop),
         def("gaTimelineAddPage", (void(*)(string)) &gaTimelineAddPage),
         def("gaTimelineAddCurves", (void(*)(string,int,int)) &gaTimelineAddCurves),
         def("gaTimelineAddBangs", (void(*)(string)) &gaTimelineAddBangs),
         def("gaTimelineAddFlags", (void(*)(string)) &gaTimelineAddFlags),
         def("gaTimelineAddColors", (void(*)(string)) &gaTimelineAddColors),
         def("gaTimelineAddLFO", (void(*)(string)) &gaTimelineAddLFO),
         def("gaTimelineAddSwitches", (void(*)(string)) &gaTimelineAddSwitches),
         def("gaTimelineAddNotes", (void(*)(string)) &gaTimelineAddNotes),
         def("gaTimelineAddAudioTrack", (void(*)(string,string)) &gaTimelineAddAudioTrack),
         def("gaTimelineAddVideoTrack", (void(*)(string,string)) &gaTimelineAddVideoTrack),
         def("gaTimelineAddCameraTrack", (void(*)(string)) &gaTimelineAddCameraTrack),
         def("gaTimelineGetValue", (float(*)(string)) &gaTimelineGetValue),
         def("gaTimelineGetSwitch", (bool(*)(string)) &gaTimelineGetSwitch),
         def("gaTimelineGetNote", (bool(*)(string)) &gaTimelineGetNote),
         def("gaTimelineGetNotePitch", (int(*)(string)) &gaTimelineGetNotePitch),
         def("gaTimelineGetNoteVelocity", (float(*)(string)) &gaTimelineGetNoteVelocity),
         def("gaTimelineGetColor", (ofColor(*)(string)) &gaTimelineGetColor),
         def("gaTimelineGetBang", (string(*)(void)) &gaTimelineGetBang),
         def("gaTimelineGetINFrame", (int(*)(void)) &gaTimelineGetINFrame),
         def("gaTimelineSetINFrame", (void(*)(float)) &gaTimelineSetINFrame),
         def("gaTimelineGetOUTFrame", (int(*)(void)) &gaTimelineGetOUTFrame),
         def("gaTimelineSetOUTFrame", (void(*)(float)) &gaTimelineSetOUTFrame),
         def("gaTimelineClearINOUT", (void(*)(void)) &gaTimelineClearINOUT),
         def("gaTimelineGetVideoTrack", (ofxTLVideoTrack*(*)(string)) &gaTimelineGetVideoTrack),
         def("gaTimelineGetAudioTrack", (ofxTLAudioTrack*(*)(string)) &gaTimelineGetAudioTrack),
         def("gaTimelineGetCameraTrack", (ofxTLCameraTrack*(*)(string)) &gaTimelineGetCameraTrack),
         def("gaTimelineSetCameraTrackCamera", (void(*)(string,ofCamera&)) &gaTimelineSetCameraTrackCamera),
         def("gaTimelineGetAudioTrackDuration", (int(*)(string)) &gaTimelineGetAudioTrackDuration),
         def("gaTimelineGetAudioTrackFFTSize", (int(*)(string)) &gaTimelineGetAudioTrackFFTSize),
         def("gaTimelineGetAudioTrackFFTBin", (float(*)(string,int)) &gaTimelineGetAudioTrackFFTBin),
         def("gaTimelineGetVideoTrackPosition", (int(*)(string)) &gaTimelineGetVideoTrackPosition),
         def("gaTimelineGetVideoTrackDuration", (int(*)(string)) &gaTimelineGetVideoTrackDuration),
         def("gaTimelineGetVideoTrackNumFrames", (int(*)(string)) &gaTimelineGetVideoTrackNumFrames),
         def("gaTimelineGetVideoTrackCurrentFrame", (int(*)(string)) &gaTimelineGetVideoTrackCurrentFrame),
         def("gaTimelineVideoPlayerNextFrame", (void(*)(string)) &gaTimelineVideoPlayerNextFrame),
         def("gaTimelineVideoPlayerUpdate", (void(*)(string)) &gaTimelineVideoPlayerUpdate),
         def("gaTimelineVideoPlayerDraw", (void(*)(string)) &gaTimelineVideoPlayerDraw),
         
         /////////////////////////////// (AUDIO Module)
		 // audio input
		 def("gaGetVolume", (float(*)(int)) &gaGetVolume),
		 def("gaGetPitch", (float(*)(int)) &gaGetPitch),
		 def("gaGetBin", (float(*)(int,int)) &gaGetFFTBand),
		 def("gaGetFFT", (float(*)(int,int)) &gaGetFFTBin),
         def("gaGetInputBuffer", (float(*)(int,int)) &gaGetAudioInputBuffer),
         def("gaGetOutputBuffer", (float(*)(int)) &gaGetAudioOutputBuffer),
         def("gaGetSoundSpectrum", (float(*)(int,int)) &gaGetSoundGetSpectrum),
		 
		 ///////////////////////////////
		 // audio synth section
		 def("gaWave", &gaSetupOSC),
		 def("gaMonoWave", &gaSetupMonoOSC),
		 def("gaWaveVolume", &gaSetOscVolume),
		 def("gaWaveFrequency", &gaSetOscFrequency),
		 def("gaWaveType", &gaSetOscWaveType),
		 def("gaWaveTuning,", &gaSetOscTuning),
		 def("gaNToF", &gaNote),
         
         ///////////////////////////////
		 // audio input recording section
         def("gaStartRec", (void(*)(int)) &gaStartInputRecording),
         def("gaStopRec", (void(*)(void)) &gaStopInputRecording),
         def("gaRecSamplePlay", (void(*)(int)) &gaInputRecPlay),
         def("gaRecSampleStop", (void(*)(int)) &gaInputRecStop),
		 def("gaRecSampleVolume", (void(*)(int,float)) &gaSetInputRecVolume),
		 def("gaRecSampleLooping", (void(*)(int,bool)) &gaSetInputRecLooping),
		 def("gaRecSamplePaused", (void(*)(int,bool)) &gaSetInputRecPaused),
         def("gaRecSampleSpeed", (void(*)(int,float)) &gaSetInputRecSpeed),
         def("gaDrawRecHead", (void(*)(int,int,int,int,int)) &gaDrawInputRecHead),
         
         ///////////////////////////////
		 // midi section
         def("gaGetMidiChannel", (int(*)(void)) &gaGetMidiChannel),
         def("gaGetMidiByteOne", (int(*)(void)) &gaGetMidiByteOne),
         def("gaGetMidiByteTwo", (int(*)(void)) &gaGetMidiByteTwo),
         def("gaGetMidiPitch", (int(*)(void)) &gaGetMidiPitch),
         def("gaGetMidiVelocity", (int(*)(void)) &gaGetMidiVelocity),
         def("gaGetMidiValue", (float(*)(int,int)) &gaGetMidiValue),
         
         ///////////////////////////////
		 // OSC section
         def("gaGetOSCMessage", (void(*)(string,int)) &gaReceiveOSCMessage),
         def("gaGetOSCValue", (string(*)(string,int)) &gaGetOSCValue),
         def("gaGetOSCNumVars", (int(*)(string)) &gaGetOSCValueNumVar),
         def("gaSetOSCMessage", (void(*)(string,int)) &gaSendOSCMessage),
         def("gaSetOSCValue", (void(*)(string,string)) &gaSetOSCValue),
         def("gaSetOSCActive", (void(*)(string,bool)) &gaSetOSCActive),
         
         ///////////////////////////////
		 // PURE DATA section
         def("pdAddToSearchPath", (void(*)(string)) &pdAddToSearchPath),
         def("pdOpenPatch", (void(*)(string)) &pdOpenPatch),
         def("pdClosePatch", (void(*)(string)) &pdClosePatch),
         def("pdStart", (void(*)(void)) &pdStart),
         def("pdStop", (void(*)(void)) &pdStop),
         def("pdComputeAudio", (void(*)(bool)) &pdComputeAudio),
         def("pdSendBang", (void(*)(string)) &pdSendBang),
         def("pdSendFloat", (void(*)(string,float)) &pdSendFloat),
         def("pdSendSymbol", (void(*)(string,string)) &pdSendSymbol),
         def("pdStartMessage", (void(*)(void)) &pdStartMessage),
         def("pdAddFloat", (void(*)(float)) &pdAddFloat),
         def("pdAddSymbol", (void(*)(string)) &pdAddSymbol),
         def("pdFinishList", (void(*)(string)) &pdFinishList),
         def("pdFinishMessage", (void(*)(string,string)) &pdFinishMessage),
         def("pdSendNoteOn", (void(*)(int,int,int)) &pdSendNoteOn),
         def("pdSendControlChange", (void(*)(int,int,int)) &pdSendControlChange),
         def("pdSendProgramChange", (void(*)(int,int)) &pdSendProgramChange),
         def("pdSendPitchBend", (void(*)(int,int)) &pdSendPitchBend),
         def("pdSendAftertouch", (void(*)(int,int)) &pdSendAftertouch),
         def("pdSendPolyAftertouch", (void(*)(int,int,int)) &pdSendPolyAftertouch),
		 
         ///////////////////////////////
		 // AUDIO UNIT PLUGINS section
         def("auAddPlugin", (void(*)(string)) &auAddPlugin),
         def("auAddPluginFromPreset", (void(*)(string)) &auAddPluginFromPreset),
         def("auPluginSetParam", (void(*)(string,string,float)) &auPluginSetParam),
         def("auListPlugins", (void(*)(void)) &auListPlugins),
		 
		 /////////////////////////////// (COMPUTER VISION Module)
		 // webcam tracking
         /*
         def("captureBackground", (void(*)(int)) &gaCaptureBackground),
		 def("camMotionQ", (float(*)(int)) &gaCamMotionQ),
		 def("camMotionX", (float(*)(int)) &gaCamMotionX),
		 def("camMotionY", (float(*)(int)) &gaCamMotionY),
		 def("camBlobs", (int(*)(int)) &gaCamRunningBlob),
		 def("camBlobX", (float(*)(int,int)) &gaCamBlobX),
		 def("camBlobY", (float(*)(int,int)) &gaCamBlobY),
		 def("camBlobW", (float(*)(int,int)) &gaCamBlobW),
		 def("camBlobH", (float(*)(int,int)) &gaCamBlobH),
		 def("camBlobAngle", (float(*)(int,int)) &gaCamBlobAngle),
         def("camBlobContourSize", (int(*)(int,int)) &gaCamBlobContourSize),
         def("camBlobCPointX", (float(*)(int,int,int)) &gaCamBlobCPointX),
         def("camBlobCPointY", (float(*)(int,int,int)) &gaCamBlobCPointY),
		 def("camBlobGeometrySize", (int(*)(int,int)) &gaCamBlobGeometrySize),
         def("camBlobGLineX1", (float(*)(int,int,int)) &gaCamBlobGLineX1),
         def("camBlobGLineY1", (float(*)(int,int,int)) &gaCamBlobGLineY1),
         def("camBlobGLineX2", (float(*)(int,int,int)) &gaCamBlobGLineX2),
         def("camBlobGLineY2", (float(*)(int,int,int)) &gaCamBlobGLineY2),
		 def("camOpticalFlowX", (float(*)(int,int)) &gaCamOpticalFlowX),
         def("camOpticalFlowY", (float(*)(int,int)) &gaCamOpticalFlowY),
         def("camOpticalFlowVX", (float(*)(int,int)) &gaCamOpticalFlowVX),
         def("camOpticalFlowVY", (float(*)(int,int)) &gaCamOpticalFlowVY),
         def("camHaars", (int(*)(int)) &gaCamRunningHaar),
		 def("camHaarX", (float(*)(int,int)) &gaCamHaarX),
         def("camHaarY", (float(*)(int,int)) &gaCamHaarY),
         def("camHaarW", (float(*)(int,int)) &gaCamHaarW),
         def("camHaarH", (float(*)(int,int)) &gaCamHaarH),
		 def("camTrigger", (bool(*)(int,int)) &gaCamTrigger),*/
		 
		 /////////////////////////////// (ARDUINO Module)
		 // arduino
         def("gaSerialDevice", (string(*)(void)) &gaGetSerialDevName),
		 def("gaAnalogRead", (float(*)(int)) &gaGetAArduinoPin),
		 def("gaDigitalRead", (int(*)(int)) &gaGetDArduinoPin),
		 def("gaDigitalWrite", (void(*)(int,int)) &gaSetDArduinoPin),
         def("gaSetServoPin", (void(*)(int,bool)) &gaSetArduinoPinServo),
         def("gaServoWrite", (void(*)(int,int)) &gaSetArduinoPinServoValue)
		 
		 
		];
		//////////////////////////////////////////////////////////////
		
		///////////////////////////////
		/// \section CONSTANTS
		
		/// OF math constants		
		lua.doString("HALF_PI = "+ofToString(HALF_PI));
		lua.doString("PI = "+ofToString(PI));
		lua.doString("TWO_PI = "+ofToString(TWO_PI));
        lua.doString("FOUR_PI = "+ofToString(FOUR_PI));
        lua.doString("DEG_TO_RAD = "+ofToString(DEG_TO_RAD));
        lua.doString("RAD_TO_DEG = "+ofToString(RAD_TO_DEG));
        
        // OF key constants
        lua.doString("OF_KEY_RETURN = "+ofToString(OF_KEY_RETURN));
        lua.doString("OF_KEY_ESC = "+ofToString(OF_KEY_ESC));
        lua.doString("OF_KEY_F1 = "+ofToString(OF_KEY_F1));
        lua.doString("OF_KEY_F2 = "+ofToString(OF_KEY_F2));
        lua.doString("OF_KEY_F3 = "+ofToString(OF_KEY_F3));
        lua.doString("OF_KEY_F4 = "+ofToString(OF_KEY_F4));
        lua.doString("OF_KEY_F5 = "+ofToString(OF_KEY_F5));
        lua.doString("OF_KEY_F6 = "+ofToString(OF_KEY_F6));
        lua.doString("OF_KEY_F7 = "+ofToString(OF_KEY_F7));
        lua.doString("OF_KEY_F8 = "+ofToString(OF_KEY_F8));
        lua.doString("OF_KEY_F9 = "+ofToString(OF_KEY_F9));
        lua.doString("OF_KEY_F10 = "+ofToString(OF_KEY_F10));
        lua.doString("OF_KEY_F11 = "+ofToString(OF_KEY_F11));
        lua.doString("OF_KEY_F12 = "+ofToString(OF_KEY_F11));
        lua.doString("OF_KEY_LEFT = "+ofToString(OF_KEY_LEFT));
        lua.doString("OF_KEY_UP = "+ofToString(OF_KEY_UP));
        lua.doString("OF_KEY_RIGHT = "+ofToString(OF_KEY_RIGHT));
        lua.doString("OF_KEY_DOWN = "+ofToString(OF_KEY_DOWN));
        lua.doString("OF_KEY_PAGE_UP = "+ofToString(OF_KEY_PAGE_UP));
        lua.doString("OF_KEY_PAGE_DOWN = "+ofToString(OF_KEY_PAGE_DOWN));
        lua.doString("OF_KEY_HOME = "+ofToString(OF_KEY_HOME));
        lua.doString("OF_KEY_END = "+ofToString(OF_KEY_END));
        lua.doString("OF_KEY_INSERT = "+ofToString(OF_KEY_INSERT));
        lua.doString("OF_KEY_BACKSPACE = "+ofToString(OF_KEY_BACKSPACE));
        lua.doString("OF_KEY_DEL = "+ofToString(OF_KEY_DEL));
        
        // OF RECTMODES
        lua.doString("OF_RECTMODE_CENTER = "+ofToString(OF_RECTMODE_CENTER));
        lua.doString("OF_RECTMODE_CORNER = "+ofToString(OF_RECTMODE_CORNER));
        
        // OF loop constants
        lua.doString("OF_LOOP_NONE = "+ofToString(OF_LOOP_NONE));
        lua.doString("OF_LOOP_NORMAL = "+ofToString(OF_LOOP_NORMAL));
        lua.doString("OF_LOOP_PALINDROME = "+ofToString(OF_LOOP_PALINDROME));
        
        // OF pixel formats
        lua.doString("OF_PIXELS_MONO = "+ofToString(OF_PIXELS_MONO));
        lua.doString("OF_PIXELS_RGB = "+ofToString(OF_PIXELS_RGB));
        lua.doString("OF_PIXELS_RGBA = "+ofToString(OF_PIXELS_RGBA));
        lua.doString("OF_PIXELS_BGRA = "+ofToString(OF_PIXELS_BGRA));
        lua.doString("OF_PIXELS_RGB565 = "+ofToString(OF_PIXELS_RGB565));
        
        // OF gradient modes
        lua.doString("OF_GRADIENT_CIRCULAR = "+ofToString(OF_GRADIENT_CIRCULAR));
        lua.doString("OF_GRADIENT_LINEAR = "+ofToString(OF_GRADIENT_LINEAR));
        lua.doString("OF_GRADIENT_BAR = "+ofToString(OF_GRADIENT_BAR));
        
        // OF scale modes
        lua.doString("OF_SCALEMODE_FIT = "+ofToString(OF_SCALEMODE_FIT));
        lua.doString("OF_SCALEMODE_FILL = "+ofToString(OF_SCALEMODE_FILL));
        lua.doString("OF_SCALEMODE_CENTER = "+ofToString(OF_SCALEMODE_CENTER));
        lua.doString("OF_SCALEMODE_STRETCH_TO_FILL = "+ofToString(OF_SCALEMODE_STRETCH_TO_FILL));
        
        // ofFillFlag
        lua.doString("OF_OUTLINE = "+ofToString(OF_OUTLINE));
        lua.doString("OF_FILLED = "+ofToString(OF_FILLED));
        
        // ofAspectRatioMode
        lua.doString("OF_ASPECT_RATIO_IGNORE = "+ofToString(OF_ASPECT_RATIO_IGNORE));
        lua.doString("OF_ASPECT_RATIO_KEEP = "+ofToString(OF_ASPECT_RATIO_KEEP));
        lua.doString("OF_ASPECT_RATIO_KEEP_BY_EXPANDING = "+ofToString(OF_ASPECT_RATIO_KEEP_BY_EXPANDING));
        
        // ofAlignVert
        lua.doString("OF_ALIGN_VERT_IGNORE = "+ofToString(OF_ALIGN_VERT_IGNORE));
        lua.doString("OF_ALIGN_VERT_TOP = "+ofToString(OF_ALIGN_VERT_TOP));
        lua.doString("OF_ALIGN_VERT_BOTTOM = "+ofToString(OF_ALIGN_VERT_BOTTOM));
        lua.doString("OF_ALIGN_VERT_CENTER = "+ofToString(OF_ALIGN_VERT_CENTER));
        
        // ofAlignHorz
        lua.doString("OF_ALIGN_HORZ_IGNORE = "+ofToString(OF_ALIGN_HORZ_IGNORE));
        lua.doString("OF_ALIGN_HORZ_LEFT = "+ofToString(OF_ALIGN_HORZ_LEFT));
        lua.doString("OF_ALIGN_HORZ_RIGHT = "+ofToString(OF_ALIGN_HORZ_RIGHT));
        lua.doString("OF_ALIGN_HORZ_CENTER = "+ofToString(OF_ALIGN_HORZ_CENTER));
        
        // OF image type
        lua.doString("OF_IMAGE_GRAYSCALE = "+ofToString(OF_IMAGE_GRAYSCALE));
        lua.doString("OF_IMAGE_COLOR = "+ofToString(OF_IMAGE_COLOR));
        lua.doString("OF_IMAGE_COLOR_ALPHA = "+ofToString(OF_IMAGE_COLOR_ALPHA));
        lua.doString("OF_IMAGE_UNDEFINED = "+ofToString(OF_IMAGE_UNDEFINED));
        
        // OF image quality type
        lua.doString("OF_IMAGE_QUALITY_BEST = "+ofToString(OF_IMAGE_QUALITY_BEST));
        lua.doString("OF_IMAGE_QUALITY_HIGH = "+ofToString(OF_IMAGE_QUALITY_HIGH));
        lua.doString("OF_IMAGE_QUALITY_MEDIUM = "+ofToString(OF_IMAGE_QUALITY_MEDIUM));
        lua.doString("OF_IMAGE_QUALITY_LOW = "+ofToString(OF_IMAGE_QUALITY_LOW));
        lua.doString("OF_IMAGE_QUALITY_WORST = "+ofToString(OF_IMAGE_QUALITY_WORST));
        
        // OF image format
        lua.doString("OF_IMAGE_FORMAT_BMP = "+ofToString(OF_IMAGE_FORMAT_BMP));
        lua.doString("OF_IMAGE_FORMAT_ICO = "+ofToString(OF_IMAGE_FORMAT_ICO));
        lua.doString("OF_IMAGE_FORMAT_JPEG = "+ofToString(OF_IMAGE_FORMAT_JPEG));
        lua.doString("OF_IMAGE_FORMAT_JNG = "+ofToString(OF_IMAGE_FORMAT_JNG));
        lua.doString("OF_IMAGE_FORMAT_KOALA = "+ofToString(OF_IMAGE_FORMAT_KOALA));
        lua.doString("OF_IMAGE_FORMAT_LBM = "+ofToString(OF_IMAGE_FORMAT_LBM));
        lua.doString("OF_IMAGE_FORMAT_IFF = "+ofToString(OF_IMAGE_FORMAT_IFF));
        lua.doString("OF_IMAGE_FORMAT_MNG = "+ofToString(OF_IMAGE_FORMAT_MNG));
        lua.doString("OF_IMAGE_FORMAT_PBM = "+ofToString(OF_IMAGE_FORMAT_PBM));
        lua.doString("OF_IMAGE_FORMAT_PBMRAW = "+ofToString(OF_IMAGE_FORMAT_PBMRAW));
        lua.doString("OF_IMAGE_FORMAT_PCD = "+ofToString(OF_IMAGE_FORMAT_PCD));
        lua.doString("OF_IMAGE_FORMAT_PCX = "+ofToString(OF_IMAGE_FORMAT_PCX));
        lua.doString("OF_IMAGE_FORMAT_PGM = "+ofToString(OF_IMAGE_FORMAT_PGM));
        lua.doString("OF_IMAGE_FORMAT_PGMRAW = "+ofToString(OF_IMAGE_FORMAT_PGMRAW));
        lua.doString("OF_IMAGE_FORMAT_PNG = "+ofToString(OF_IMAGE_FORMAT_PNG));
        lua.doString("OF_IMAGE_FORMAT_PPM = "+ofToString(OF_IMAGE_FORMAT_PPM));
        lua.doString("OF_IMAGE_FORMAT_PPMRAW = "+ofToString(OF_IMAGE_FORMAT_PPMRAW));
        lua.doString("OF_IMAGE_FORMAT_RAS = "+ofToString(OF_IMAGE_FORMAT_RAS));
        lua.doString("OF_IMAGE_FORMAT_TARGA = "+ofToString(OF_IMAGE_FORMAT_TARGA));
        lua.doString("OF_IMAGE_FORMAT_TIFF = "+ofToString(OF_IMAGE_FORMAT_TIFF));
        lua.doString("OF_IMAGE_FORMAT_WBMP = "+ofToString(OF_IMAGE_FORMAT_WBMP));
        lua.doString("OF_IMAGE_FORMAT_PSD = "+ofToString(OF_IMAGE_FORMAT_PSD));
        lua.doString("OF_IMAGE_FORMAT_CUT = "+ofToString(OF_IMAGE_FORMAT_CUT));
        lua.doString("OF_IMAGE_FORMAT_XBM = "+ofToString(OF_IMAGE_FORMAT_XBM));
        lua.doString("OF_IMAGE_FORMAT_XPM = "+ofToString(OF_IMAGE_FORMAT_XPM));
        lua.doString("OF_IMAGE_FORMAT_DDS = "+ofToString(OF_IMAGE_FORMAT_DDS));
        lua.doString("OF_IMAGE_FORMAT_GIF = "+ofToString(OF_IMAGE_FORMAT_GIF));
        lua.doString("OF_IMAGE_FORMAT_HDR = "+ofToString(OF_IMAGE_FORMAT_HDR));
        lua.doString("OF_IMAGE_FORMAT_FAXG3 = "+ofToString(OF_IMAGE_FORMAT_FAXG3));
        lua.doString("OF_IMAGE_FORMAT_SGI = "+ofToString(OF_IMAGE_FORMAT_SGI));
        lua.doString("OF_IMAGE_FORMAT_EXR = "+ofToString(OF_IMAGE_FORMAT_EXR));
        lua.doString("OF_IMAGE_FORMAT_J2K = "+ofToString(OF_IMAGE_FORMAT_J2K));
        lua.doString("OF_IMAGE_FORMAT_JP2 = "+ofToString(OF_IMAGE_FORMAT_JP2));
        lua.doString("OF_IMAGE_FORMAT_PFM = "+ofToString(OF_IMAGE_FORMAT_PFM));
        lua.doString("OF_IMAGE_FORMAT_PICT = "+ofToString(OF_IMAGE_FORMAT_PICT));
        lua.doString("OF_IMAGE_FORMAT_RAW = "+ofToString(OF_IMAGE_FORMAT_RAW));
        
        // OF polyline winding mode
        lua.doString("OF_POLY_WINDING_ODD = "+ofToString(OF_POLY_WINDING_ODD));
        lua.doString("OF_POLY_WINDING_NONZERO = "+ofToString(OF_POLY_WINDING_NONZERO));
        lua.doString("OF_POLY_WINDING_POSITIVE = "+ofToString(OF_POLY_WINDING_POSITIVE));
        lua.doString("OF_POLY_WINDING_NEGATIVE = "+ofToString(OF_POLY_WINDING_NEGATIVE));
        lua.doString("OF_POLY_WINDING_ABS_GEQ_TWO = "+ofToString(OF_POLY_WINDING_ABS_GEQ_TWO));
        
        // OF primitives
        lua.doString("OF_PRIMITIVE_TRIANGLES = "+ofToString(OF_PRIMITIVE_TRIANGLES));
        lua.doString("OF_PRIMITIVE_TRIANGLE_STRIP = "+ofToString(OF_PRIMITIVE_TRIANGLE_STRIP));
        lua.doString("OF_PRIMITIVE_TRIANGLE_FAN = "+ofToString(OF_PRIMITIVE_TRIANGLE_FAN));
        lua.doString("OF_PRIMITIVE_LINES = "+ofToString(OF_PRIMITIVE_LINES));
        lua.doString("OF_PRIMITIVE_LINE_STRIP = "+ofToString(OF_PRIMITIVE_LINE_STRIP));
        lua.doString("OF_PRIMITIVE_LINE_LOOP = "+ofToString(OF_PRIMITIVE_LINE_LOOP));
        lua.doString("OF_PRIMITIVE_POINTS = "+ofToString(OF_PRIMITIVE_POINTS));
        
        // OF gl legacy
        lua.doString("OF_TRIANGLES_MODE = "+ofToString(OF_TRIANGLES_MODE));
        lua.doString("OF_TRIANGLE_STRIP_MODE = "+ofToString(OF_TRIANGLE_STRIP_MODE));
        lua.doString("OF_TRIANGLE_FAN_MODE = "+ofToString(OF_TRIANGLE_FAN_MODE));
        lua.doString("OF_LINES_MODE = "+ofToString(OF_LINES_MODE));
        lua.doString("OF_LINE_STRIP_MODE = "+ofToString(OF_LINE_STRIP_MODE));
        lua.doString("OF_LINE_LOOP_MODE = "+ofToString(OF_LINE_LOOP_MODE));
        lua.doString("OF_POINTS_MODE = "+ofToString(OF_POINTS_MODE));
        
        // OF mesh modes
        lua.doString("OF_MESH_POINTS = "+ofToString(OF_MESH_POINTS));
        lua.doString("OF_MESH_WIREFRAME = "+ofToString(OF_MESH_WIREFRAME));
        lua.doString("OF_MESH_FILL = "+ofToString(OF_MESH_FILL));
        
        // OF blending modes
        lua.doString("OF_BLENDMODE_DISABLED = "+ofToString(OF_BLENDMODE_DISABLED));
        lua.doString("OF_BLENDMODE_ALPHA = "+ofToString(OF_BLENDMODE_ALPHA));
        lua.doString("OF_BLENDMODE_ADD = "+ofToString(OF_BLENDMODE_ADD));
        lua.doString("OF_BLENDMODE_SUBTRACT = "+ofToString(OF_BLENDMODE_SUBTRACT));
        lua.doString("OF_BLENDMODE_MULTIPLY = "+ofToString(OF_BLENDMODE_MULTIPLY));
        lua.doString("OF_BLENDMODE_SCREEN = "+ofToString(OF_BLENDMODE_SCREEN));
        
        // OF bitmap draw modes
        lua.doString("OF_BITMAPMODE_SIMPLE = "+ofToString(OF_BITMAPMODE_SIMPLE));
        lua.doString("OF_BITMAPMODE_SCREEN = "+ofToString(OF_BITMAPMODE_SCREEN));
        lua.doString("OF_BITMAPMODE_VIEWPORT = "+ofToString(OF_BITMAPMODE_VIEWPORT));
        lua.doString("OF_BITMAPMODE_MODEL = "+ofToString(OF_BITMAPMODE_MODEL));
        lua.doString("OF_BITMAPMODE_MODEL_BILLBOARD = "+ofToString(OF_BITMAPMODE_MODEL_BILLBOARD));
        
        // OFXFX
        lua.doString("BLEND_NORMAL = "+ofToString(BLEND_NORMAL));
        lua.doString("BLEND_MULTIPLY = "+ofToString(BLEND_MULTIPLY));
        lua.doString("BLEND_AVERAGE = "+ofToString(BLEND_AVERAGE));
        lua.doString("BLEND_ADD = "+ofToString(BLEND_ADD));
        lua.doString("BLEND_SUBSTRACT = "+ofToString(BLEND_SUBSTRACT));
        lua.doString("BLEND_DIFFERENCE = "+ofToString(BLEND_DIFFERENCE));
        lua.doString("BLEND_NEGATION = "+ofToString(BLEND_NEGATION));
        lua.doString("BLEND_EXCLUSION = "+ofToString(BLEND_EXCLUSION));
        lua.doString("BLEND_SCREEN = "+ofToString(BLEND_SCREEN));
        lua.doString("BLEND_OVERLAY = "+ofToString(BLEND_OVERLAY));
        lua.doString("BLEND_SOFTLIGHT = "+ofToString(BLEND_SOFTLIGHT));
        lua.doString("BLEND_HARDLIGHT = "+ofToString(BLEND_HARDLIGHT));
        lua.doString("BLEND_COLORDODGE = "+ofToString(BLEND_COLORDODGE));
        lua.doString("BLEND_COLORBURN = "+ofToString(BLEND_COLORBURN));
        lua.doString("BLEND_LINEARLIGHT = "+ofToString(BLEND_LINEARLIGHT));
        lua.doString("BLEND_VIVIDLIGHT = "+ofToString(BLEND_VIVIDLIGHT));
        lua.doString("BLEND_PINLIGHT = "+ofToString(BLEND_PINLIGHT));
        lua.doString("BLEND_HARDMIX = "+ofToString(BLEND_HARDMIX));
        lua.doString("BLEND_REGLECT = "+ofToString(BLEND_REGLECT));
        lua.doString("BLEND_GLOW = "+ofToString(BLEND_GLOW));
        lua.doString("BLEND_PHOENIX = "+ofToString(BLEND_PHOENIX));
        lua.doString("BLEND_HUE = "+ofToString(BLEND_HUE));
        lua.doString("BLEND_SATURATION = "+ofToString(BLEND_SATURATION));
        lua.doString("BLEND_COLOR = "+ofToString(BLEND_COLOR));
        lua.doString("BLEND_LUMINOSITY = "+ofToString(BLEND_LUMINOSITY));
        
        // OFXKINECT
		lua.doString("LED_DEFAULT = "+ofToString(-1));
        lua.doString("LED_OFF = "+ofToString(0));
        lua.doString("LED_GREEN = "+ofToString(1));
        lua.doString("LED_RED = "+ofToString(2));
        lua.doString("LED_YELLOW = "+ofToString(3));
        lua.doString("LED_BLINK_GREEN = "+ofToString(4));
        lua.doString("LED_BLINK_YELLOW_RED = "+ofToString(6));
        
		// graphics
		lua.doString("OUTPUT_W = "+ofToString(gapp->projectionScreenW));
		lua.doString("OUTPUT_H = "+ofToString(gapp->projectionScreenH));
		lua.doString("CAPTURE_W = "+ofToString(gapp->workingW));
		lua.doString("CAPTURE_H = "+ofToString(gapp->workingH));
		lua.doString("CAPTURE_PIX = "+ofToString(gapp->totPixels));
        
        // OSC messages
        lua.doString("OSC_SENDING_PORT = "+ofToString(atoi(gapp->host_port.c_str())));
        lua.doString("OSC_RECEIVING_PORT = "+ofToString(atoi(gapp->server_port.c_str())));
        lua.doString("OSC_INT = "+ofToString(OFXOSC_TYPE_INT32));
		lua.doString("OSC_FLOAT = "+ofToString(OFXOSC_TYPE_FLOAT));
		lua.doString("OSC_STRING = "+ofToString(OFXOSC_TYPE_STRING));
		
		// video tracking
		lua.doString("MAX_BLOBS = "+ofToString(MAX_USERS_HARDLIMIT));
        lua.doString("OPTICAL_FLOW_GRID_X = "+ofToString((int)(gapp->workingW/OPTICAL_FLOW_COLS_STEP)));
        lua.doString("OPTICAL_FLOW_GRID_Y = "+ofToString((int)(gapp->workingH/OPTICAL_FLOW_ROWS_STEP)));
		
		// audio analysis
        lua.doString("AUDIO_INPUT_CHANNELS = "+ofToString(gapp->audioInputChannels));
        lua.doString("AUDIO_OUTPUT_CHANNELS = "+ofToString(gapp->audioOutputChannels));
        lua.doString("BUFFER_SIZE = "+ofToString(gapp->audioBufferSize));
		lua.doString("FFT_BANDS = "+ofToString(BARK_SCALE_CRITICAL_BANDS));
		
		// audio synth
		lua.doString("GA_SINE = "+ofToString(OSC_SINE_WAVE));
		lua.doString("GA_COSINE = "+ofToString(OSC_COSINE_WAVE));
		lua.doString("GA_SAW = "+ofToString(OSC_SAWTOOTH_WAVE));
		lua.doString("GA_TRI = "+ofToString(OSC_TRIANGLE_WAVE));
		lua.doString("GA_RECT = "+ofToString(OSC_RECT_WAVE));
		lua.doString("GA_NOISE = "+ofToString(OSC_WHITE_NOISE));
		lua.doString("GA_PINK = "+ofToString(OSC_PINK_NOISE));
		lua.doString("GA_BROWN = "+ofToString(OSC_BROWN_NOISE));
		lua.doString("GA_PHASOR = "+ofToString(OSC_PHASOR));
		lua.doString("GA_PULSE = "+ofToString(OSC_PULSE));
		// notes
		lua.doString("DO_0 = "+ofToString(DO_0));
		lua.doString("DOB_0 = "+ofToString(DOB0));
		lua.doString("RE_0 = "+ofToString(RE_0));
		lua.doString("REB_0 = "+ofToString(REB_0));
		lua.doString("MI_0 = "+ofToString(MI_0));
		lua.doString("FA_0 = "+ofToString(FA_0));
		lua.doString("FAB_0 = "+ofToString(FAB_0));
		lua.doString("SOL_0 = "+ofToString(SOL_0));
		lua.doString("SOLB_0 = "+ofToString(SOLB_0));
		lua.doString("LA_0 = "+ofToString(LA_0));
		lua.doString("LAB_0 = "+ofToString(LAB_0));
		lua.doString("SI_0 = "+ofToString(SI_0));
		lua.doString("DO_1 = "+ofToString(DO_1));
		lua.doString("DOB_1 = "+ofToString(DOB1));
		lua.doString("RE_1 = "+ofToString(RE_1));
		lua.doString("REB_1 = "+ofToString(REB_1));
		lua.doString("MI_1 = "+ofToString(MI_1));
		lua.doString("FA_1 = "+ofToString(FA_1));
		lua.doString("FAB_1 = "+ofToString(FAB_1));
		lua.doString("SOL_1 = "+ofToString(SOL_1));
		lua.doString("SOLB_1 = "+ofToString(SOLB_1));
		lua.doString("LA_1 = "+ofToString(LA_1));
		lua.doString("LAB_1 = "+ofToString(LAB_1));
		lua.doString("SI_1 = "+ofToString(SI_1));
		lua.doString("DO_2 = "+ofToString(DO_2));
		lua.doString("DOB_2 = "+ofToString(DOB2));
		lua.doString("RE_2 = "+ofToString(RE_2));
		lua.doString("REB_2 = "+ofToString(REB_2));
		lua.doString("MI_2 = "+ofToString(MI_2));
		lua.doString("FA_2 = "+ofToString(FA_2));
		lua.doString("FAB_2 = "+ofToString(FAB_2));
		lua.doString("SOL_2 = "+ofToString(SOL_2));
		lua.doString("SOLB_2 = "+ofToString(SOLB_2));
		lua.doString("LA_2 = "+ofToString(LA_2));
		lua.doString("LAB_2 = "+ofToString(LAB_2));
		lua.doString("SI_2 = "+ofToString(SI_2));
		lua.doString("DO_3 = "+ofToString(DO_3));
		lua.doString("DOB_3 = "+ofToString(DOB3));
		lua.doString("RE_3 = "+ofToString(RE_3));
		lua.doString("REB_3 = "+ofToString(REB_3));
		lua.doString("MI_3 = "+ofToString(MI_3));
		lua.doString("FA_3 = "+ofToString(FA_3));
		lua.doString("FAB_3 = "+ofToString(FAB_3));
		lua.doString("SOL_3 = "+ofToString(SOL_3));
		lua.doString("SOLB_3 = "+ofToString(SOLB_3));
		lua.doString("LA_3 = "+ofToString(LA_3));
		lua.doString("LAB_3 = "+ofToString(LAB_3));
		lua.doString("SI_3 = "+ofToString(SI_3));
		lua.doString("DO_4 = "+ofToString(DO_4));
		lua.doString("DOB_4 = "+ofToString(DOB4));
		lua.doString("RE_4 = "+ofToString(RE_4));
		lua.doString("REB_4 = "+ofToString(REB_4));
		lua.doString("MI_4 = "+ofToString(MI_4));
		lua.doString("FA_4 = "+ofToString(FA_4));
		lua.doString("FAB_4 = "+ofToString(FAB_4));
		lua.doString("SOL_4 = "+ofToString(SOL_4));
		lua.doString("SOLB_4 = "+ofToString(SOLB_4));
		lua.doString("LA_4 = "+ofToString(LA_4));
		lua.doString("LAB_4 = "+ofToString(LAB_4));
		lua.doString("SI_4 = "+ofToString(SI_4));
		lua.doString("DO_5 = "+ofToString(DO_5));
		lua.doString("DOB_5 = "+ofToString(DOB5));
		lua.doString("RE_5 = "+ofToString(RE_5));
		lua.doString("REB_5 = "+ofToString(REB_5));
		lua.doString("MI_5 = "+ofToString(MI_5));
		lua.doString("FA_5 = "+ofToString(FA_5));
		lua.doString("FAB_5 = "+ofToString(FAB_5));
		lua.doString("SOL_5 = "+ofToString(SOL_5));
		lua.doString("SOLB_5 = "+ofToString(SOLB_5));
		lua.doString("LA_5 = "+ofToString(LA_5));
		lua.doString("LAB_5 = "+ofToString(LAB_5));
		lua.doString("SI_5 = "+ofToString(SI_5));
		lua.doString("DO_6 = "+ofToString(DO_6));
		lua.doString("DOB_6 = "+ofToString(DOB6));
		lua.doString("RE_6 = "+ofToString(RE_6));
		lua.doString("REB_6 = "+ofToString(REB_6));
		lua.doString("MI_6 = "+ofToString(MI_6));
		lua.doString("FA_6 = "+ofToString(FA_6));
		lua.doString("FAB_6 = "+ofToString(FAB_6));
		lua.doString("SOL_6 = "+ofToString(SOL_6));
		lua.doString("SOLB_6 = "+ofToString(SOLB_6));
		lua.doString("LA_6 = "+ofToString(LA_6));
		lua.doString("LAB_6 = "+ofToString(LAB_6));
		lua.doString("SI_6 = "+ofToString(SI_6));
		lua.doString("DO_7 = "+ofToString(DO_7));
		lua.doString("DOB_7 = "+ofToString(DOB7));
		lua.doString("RE_7 = "+ofToString(RE_7));
		lua.doString("REB_7 = "+ofToString(REB_7));
		lua.doString("MI_7 = "+ofToString(MI_7));
		lua.doString("FA_7 = "+ofToString(FA_7));
		lua.doString("FAB_7 = "+ofToString(FAB_7));
		lua.doString("SOL_7 = "+ofToString(SOL_7));
		lua.doString("SOLB_7 = "+ofToString(SOLB_7));
		lua.doString("LA_7 = "+ofToString(LA_7));
		lua.doString("LAB_7 = "+ofToString(LAB_7));
		lua.doString("SI_7 = "+ofToString(SI_7));
		lua.doString("DO_8 = "+ofToString(DO_8));
		lua.doString("DOB_8 = "+ofToString(DOB8));
		lua.doString("RE_8 = "+ofToString(RE_8));
		lua.doString("REB_8 = "+ofToString(REB_8));
		lua.doString("MI_8 = "+ofToString(MI_8));
		lua.doString("FA_8 = "+ofToString(FA_8));
		lua.doString("FAB_8 = "+ofToString(FAB_8));
		lua.doString("SOL_8 = "+ofToString(SOL_8));
		lua.doString("SOLB_8 = "+ofToString(SOLB_8));
		lua.doString("LA_8 = "+ofToString(LA_8));
		lua.doString("LAB_8 = "+ofToString(LAB_8));
		lua.doString("SI_8 = "+ofToString(SI_8));
		
	}
	
	////////////////////////////////////////////////////////
	/// \section Function & Object Wrappers
	
	/// ofGraphics
	static void background(int brightness)                                  {ofBackground(brightness);}
	static void background(int r, int g, int b)                             {ofBackground(r, g, b);}
    static void setColor1(int gray)                                         {ofSetColor(gray,gray,gray);}
    static void setColor2(int gray, int alpha)                              {ofSetColor(gray,gray,gray,alpha);}
    static void map5(float v,float iMin,float iMax,float oMin,float oMax)   {ofMap(v,iMin,iMax,oMin,oMax,false);}
    
    /// ofTrueTypeFont
	static void loadFont2(ofTrueTypeFont* font, string filename, int fontsize) {
		font->loadFont(filename, fontsize);
	}
	static void loadFont4(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet);
	}
    static void loadFont5(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet,makeContours);
	}
    static void loadFont7(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmt, float dpi) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet,makeContours,simplifyAmt,dpi);
	}
    
    /// ofTrueTypeFontUC
	static void loadFont2UC(ofxTrueTypeFontUC* font, string filename, int fontsize) {
		font->loadFont(filename, fontsize,true,false,0.3,0);
	}
	static void loadFont4UC(ofxTrueTypeFontUC* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet,0.3,0);
	}
    
    /// ofxArcText
	static void loadArcFont2(ofxArcText* font, string filename, int fontsize) {
		font->loadFont(filename, fontsize);
	}
	static void loadArcFont4(ofxArcText* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet);
	}
    
    /// ofxDither
    static void ditherOrdered(ofxDither* d, ofImage& imageIn, ofImage& imageOut) {
        d->dither_ordered(imageIn,imageOut);
    }
    
    /// ofFile
    static void openFile(ofFile* file,string path){
        file->open(path);
    }
    
    // OFXQRCODEGENERATOR
    static ofImage QRgenerate(ofxQRCodeGenerator* gen, string _s, int _i){
        return gen->generate(_s,_i);
    }
    
    /// ofxOpenCv
    static void gaFindContours(ofxCvContourFinder* src,ofxCvGrayscaleImage& input,int minArea, int maxArea,int nConsidered, bool bFindHoles){
        src->findContours(input,minArea,maxArea,nConsidered,bFindHoles,true);
    }
    
    static void scaleIntoMeShort(ofxCvShortImage* src, ofxCvImage& img){
        src->scaleIntoMe(img);
    }
    
    static void scaleIntoMeFloat(ofxCvFloatImage* src, ofxCvImage& img){
        src->scaleIntoMe(img);
    }
    
    static void scaleIntoMeGray(ofxCvGrayscaleImage* src, ofxCvImage& img){
        src->scaleIntoMe(img);
    }
    
    static void scaleIntoMeColor(ofxCvColorImage* src, ofxCvImage& img){
        src->scaleIntoMe(img);
    }
    
    /// ofTexture
    static void loadDataOLD(ofTexture* tex, unsigned char* pix, int w, int h, int _type) {
		tex->loadData(pix, w, h, _type);
	}
	
	/// global mouse vars
	static float getMouseX() {return (float)gapp->scaledMouseX;}
	static float getMouseY() {return (float)gapp->scaledMouseY;}
    
    /// global key vars
    static int getKey() {return (int)gapp->liveKey;}

};