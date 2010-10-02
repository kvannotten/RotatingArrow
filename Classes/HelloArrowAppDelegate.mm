//
//  HelloArrowAppDelegate.m
//  HelloArrow
//
//  Created by Kristof Vannotten on 2/10/10.
//  Copyright 2010 Kristof Projects. All rights reserved.
//

#import "HelloArrowAppDelegate.h"

@implementation HelloArrowAppDelegate


- (void)applicationDidFinishLaunching:(UIApplication*)application {    
    
    // Override point for customization after application launch.
    
	CGRect screenBounds = [[UIScreen mainScreen]bounds];
	
	window = [[UIWindow alloc]initWithFrame:screenBounds];
	m_view = [[GLView alloc]initWithFrame:screenBounds];
	
	[window addSubview:m_view];
	
    [window makeKeyAndVisible];

}

- (void)dealloc {
	[m_view release];
    [window release];
    [super dealloc];
}


@end
