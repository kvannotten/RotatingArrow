/*
 *  IRenderingEngine.hpp
 *  HelloArrow
 *
 *  Created by Kristof Vannotten on 2/10/10.
 *  Copyright 2010 Kristof Projects. All rights reserved.
 *
 */

//physical orientation of the iphone
enum DeviceOrientation {
	DeviceOrientationUnkown,
	DeviceOrientationPortrait,
	DeviceOrientationPortraitUpsideDown,
	DeviceOrientationLandscapeLeft,
	DeviceOrientationLandscapeRight,
	DeviceOrientationFaceUp,
	DeviceOrientationFaceDown
};

//create instance of renderer and sets up various opengl states
struct IRenderingEngine* CreateRenderer1();
struct IRenderingEngine* CreateRenderer2();

//interface to the opengl es renderer
struct IRenderingEngine{
	virtual void Initialize(int width, int height) = 0;
	virtual void Render() const = 0;
	virtual void UpdateAnimation(float timeStep) = 0;
	virtual void OnRotate(DeviceOrientation newOrientation) = 0;
	virtual ~IRenderingEngine(){}
};