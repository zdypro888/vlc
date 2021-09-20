// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build darwin && !ios

#include "_cgo_export.h"
#include <pthread.h>
#include <stdio.h>

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
 
uint64 threadID() {
	uint64 id;
	if (pthread_threadid_np(pthread_self(), &id)) {
		abort();
	}
	return id;
}

void onRuning(void *);

void runApp(void) {
	[NSAutoreleasePool new];
	[NSApplication sharedApplication];
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

	NSRect rect = NSMakeRect(0, 0, 600, 800);
	NSWindowStyleMask style = NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
	NSWindow* window = [[[NSWindow alloc] initWithContentRect:rect
			styleMask:style
			backing:NSBackingStoreBuffered
			defer:NO]
		autorelease];
	window.title = @"VLC";
	[window cascadeTopLeftFromPoint:NSMakePoint(20,20)];

	NSView * customView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 0, 0)];
	[window setContentView:customView];
	onRuning((__bridge void *)customView);
	//如下没有这句话，会导致窗口不会显示出来
	[window makeKeyAndOrderFront:nil];
	//使得应用打开时就获取到用户焦点
	[NSApp activateIgnoringOtherApps:YES];

	[NSApp run];
}

void stopApp(void) {
	[NSApp terminate:nil];
}
