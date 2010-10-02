//
//  GLView.mm
//  HelloArrow
//
//  Created by Kristof Vannotten on 2/10/10.
//  Copyright 2010 Kristof Projects. All rights reserved.
//

#import <OpenGLES/EAGLDrawable.h>
#import "GLView.h"
#import "mach/mach_time.h"
#import <OpenGLES/ES2/gl.h> // for GL_RENDERBUFFER only


const bool ForceES1 = false;

@implementation GLView

+(Class)layerClass{
	return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame {
	
    if ((self = [super initWithFrame:frame])) {
		CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
		eaglLayer.opaque = YES;
		
		EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
		m_context = [[EAGLContext alloc] initWithAPI:api];
		
		if (!m_context || ForceES1) {
			api = kEAGLRenderingAPIOpenGLES1;
			m_context = [[EAGLContext alloc] initWithAPI:api];
		}
		
		if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
			[self release];
			return nil;
		}
		
		if (api== kEAGLRenderingAPIOpenGLES1) {
			NSLog(@"Using opengles 1.1");
			m_renderingEngine = CreateRenderer1();
		} else {
			NSLog(@"Using opengl es 2.0");
			m_renderingEngine = CreateRenderer2();
		}

		
		[m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
		
		m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
		
		[self drawView: nil];
		m_timestamp = CACurrentMediaTime();
		
		CADisplayLink* displayLink;
		displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
		
		[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		
		[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
		
		[[NSNotificationCenter defaultCenter] 
			addObserver:self
			selector:@selector(didRotate:)
			name:UIDeviceOrientationDidChangeNotification
			object:nil];
    }
    return self;
}

-(void)didRotate:(NSNotification *)notification{
	UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
	m_renderingEngine->OnRotate((DeviceOrientation)orientation);
	[self drawView:nil];
}

-(void)drawView:(CADisplayLink*)displayLink{
	if (displayLink != nil) {
		float elapsedSeconds = displayLink.timestamp - m_timestamp;
		m_timestamp = displayLink.timestamp;
		m_renderingEngine->UpdateAnimation(elapsedSeconds);
	}
	
	m_renderingEngine->Render();
	[m_context presentRenderbuffer:GL_RENDERBUFFER];
}


- (void)dealloc {
	if ([EAGLContext currentContext] == m_context) {
		[EAGLContext setCurrentContext:nil];
	}
	[m_context release];
    [super dealloc];
}


@end
