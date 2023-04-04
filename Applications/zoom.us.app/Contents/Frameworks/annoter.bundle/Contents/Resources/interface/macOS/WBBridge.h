//
//  WBBridge.h
//  whiteboard
//
//  Created by Lester Gong on 2022/5/31.
//  Copyright © 2022 Lester Gong. All rights reserved.
//

#ifndef WBBridge_h
#define WBBridge_h


#define WB_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif


int WB_EXPORT WBBridgeFunc(void*&WBHandle/*, eWBBridge bCreate*/);


#ifdef __cplusplus
}
#endif




@interface WBBridge : NSObject

+ (NSView*)createContainerView;
+ (void)destroyContainerView:(NSView*)containerView;

+ (void*)loadMainProxy;
+ (void)releaseMainProxy:(void*)mainProxy;

@end

#endif /* WBBridge_h */
