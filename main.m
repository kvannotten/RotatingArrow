//
//  main.m
//  HelloArrow
//
//  Created by Kristof Vannotten on 2/10/10.
//  Copyright 2010 Kristof Projects. All rights reserved.
//

#import <UIKit/UIKit.h>

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"HelloArrowAppDelegate");
    [pool release];
    return retVal;
}
