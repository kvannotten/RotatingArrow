//
//  GLView.h
//  HelloArrow
//
//  Created by Kristof Vannotten on 2/10/10.
//  Copyright 2010 Kristof Projects. All rights reserved.
//

#import "IRenderingEngine.hpp"
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>


@interface GLView : UIView {
@private
	EAGLContext* m_context;
	IRenderingEngine* m_renderingEngine;
	float m_timestamp;
}

-(void)drawView: (CADisplayLink*)displayLink;
-(void)didRotate: (NSNotification*)notification;

@end
