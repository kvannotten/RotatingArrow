/*
 *  RenderingEngine1.cpp
 *  HelloArrow
 *
 *  Created by Kristof Vannotten on 2/10/10.
 *  Copyright 2010 Kristof Projects. All rights reserved.
 *
 */

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "IRenderingEngine.hpp"

static const float RevolutionPerSecond = 1;

class RenderingEngine1: public IRenderingEngine {
public:
	RenderingEngine1();
	void Initialize(int width, int height);
	void Render() const;
	void UpdateAnimation(float timestep);
	void OnRotate(DeviceOrientation newOrientation);
private:
	GLuint m_framebuffer;
	GLuint m_renderbuffer;
	float m_currentAngle;
	float RotationDirection() const;
	float m_desiredAngle;
};

IRenderingEngine* CreateRenderer1(){
	return new RenderingEngine1();
}

struct Vertex {
	float Position[2];
	float Color[4];
};

//maak de pijl
const Vertex Vertices[] = {
	{{-0.5, -0.866},	{1, 1, 0.5f, 1}},
	{{0.5, -0.866},		{1, 1, 0.5f, 1}},
	{{0, 1},			{1, 1, 0.5f, 1}},
	{{-0.5, -0.866},	{0.5f, 0.5f, 0.5f}},
	{{0.5, -0.866},		{0.5f, 0.5f, 0.5f}},
	{{0, -0.4f},		{0.5f, 0.5f, 0.5f}}
};

RenderingEngine1::RenderingEngine1(){
	glGenRenderbuffersOES(1, &m_renderbuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderbuffer);
}

void RenderingEngine1::Initialize(int width, int height){
	//create framebuffer object and attach the colour buffer
	glGenFramebuffersOES(1, &m_framebuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_framebuffer);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, m_renderbuffer);
	
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	
	//init de projection matrix
	const float maxX = 2;
	const float maxY = 3;
	glOrthof(-maxX, +maxX, -maxY, +maxY, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	
	//init rotation animation state
	OnRotate(DeviceOrientationPortrait);
	m_currentAngle = m_desiredAngle;
}

void RenderingEngine1::Render() const{
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	glRotatef(m_currentAngle, 0, 0, 1);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &Vertices[0].Position[0]);
	glVertexPointer(4, GL_FLOAT, sizeof(Vertex), &Vertices[0].Color[0]);
	
	GLsizei vertexCount = sizeof(Vertices) / sizeof(Vertex);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY); 
	
	glPopMatrix();
}

void RenderingEngine1::OnRotate(DeviceOrientation orientation){
	float angle = 0;
	
	switch (orientation) {
		case DeviceOrientationLandscapeLeft:
			angle=270;
			break;
		case DeviceOrientationPortraitUpsideDown:
			angle=180;
			break;
		case DeviceOrientationLandscapeRight:
			angle=90;
			break;
	}
	m_desiredAngle = angle;
}

float RenderingEngine1::RotationDirection() const{
	float delta = m_desiredAngle - m_currentAngle;
	if (delta==0) {
		return 0;
	}
	
	bool counterclockwise = ((delta > 0 && delta <=180) || (delta < -180));
	return counterclockwise ? +1 : -1;
}

void RenderingEngine1::UpdateAnimation(float timeStep){
	float direction = RotationDirection();
	if (direction == 0) {
		return;
	}
	
	float degrees = timeStep * 360 * RevolutionPerSecond;
	m_currentAngle += degrees * direction;
	
	//angle blijft tussen 0..360
	if (m_currentAngle >=360) {
		m_currentAngle -= 360;
	}else if (m_currentAngle < 0) {
		m_currentAngle +=360;
	}
	
	if (RotationDirection() != direction) {
		m_currentAngle = m_desiredAngle;
	}
}