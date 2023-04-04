//
//  anno_cursor_center.h
//  annoter
//
//  Created by Lester Gong on 2022/4/21.
//  Copyright © 2022 Ken Ding. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "anno_types.h"

#define ANNO_CURSOR_ARROW_NAME  @"ANNO_CURSOR_ARROW_NAME"

NS_ASSUME_NONNULL_BEGIN


#pragma mark - NSCursor

@interface NSCursor (anno_utilities)

@property (class, assign, readonly) BOOL isSetByAnno;
@property (class, assign) NSCursor* visualCursor;

@end

#pragma mark - CAnnoCursorCenter
@interface CAnnoCursorCenter : NSObject

- (instancetype)initWithCanvasView:(NSView*)canvasView
                       andAnnoMode:(AnnoMode)annoMode;

- (int)setIntrinsicAndVisible:(AnnoToolType)annoToolType;
- (int)makeIntrinsicVisible;

- (void)setVisibleCursorToArrow:(BOOL)flagArrow;

- (void)observeShapeEditing;

@end

NS_ASSUME_NONNULL_END
