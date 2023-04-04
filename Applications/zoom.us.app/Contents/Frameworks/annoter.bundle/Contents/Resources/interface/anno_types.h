/*****************************************************************************
*
* Copyright (C) 2013, Zoom Video Communications, Inc
*
* History:
*	Nov 2013 - Created - ken.ding@zoom.us
*	
*****************************************************************************/

#ifndef __ANNO_TYPES_H__
#define __ANNO_TYPES_H__

#include <vector>
#include <string>

// ----------------------------------------------------------------------------
// Define macro switches for decroration
// ----------------------------------------------------------------------------

#ifndef IN
  #define IN
#endif

#ifndef OUT
  #define OUT
#endif

#ifndef OPTIONAL
  #define OPTIONAL
#endif

#ifndef singleton_static
  #define singleton_static static
#endif

#ifndef var_static
  #define var_static static
#endif

// ----------------------------------------------------------------------------
//	Turn it on to enable factor methods
// ----------------------------------------------------------------------------

#if defined USE_CLASS_INTERFACE && !defined ANNO_DLLEXPORT
  #define ANNO_DLLEXPORT __declspec(dllexport)
#else
  #define ANNO_DLLEXPORT
#endif

// ----------------------------------------------------------------------------
// Define primitive data types that are shared by this module and external
// applications
// ----------------------------------------------------------------------------

#ifndef Bool8
  typedef bool Bool8;
#endif

#ifndef UInt8
  typedef unsigned char UInt8;
#endif

#ifndef Int8
  typedef char Int8;
#endif

#ifndef UInt16
  typedef unsigned short UInt16;
#endif

#ifndef Int16
  typedef short Int16;
#endif

#ifndef UInt32
  #if __LP64__
    typedef unsigned int UInt32;
  #else
    typedef unsigned long UInt32;
  #endif
#endif

#ifndef Int32 
  typedef int Int32;
#endif

#ifndef Int64
  typedef long long Int64;
#endif

#ifndef Float32
  typedef float Float32;
#endif

#ifndef Double64
  typedef double Double64;
#endif

#ifndef NODEID
  typedef UInt32 NODEID;
#endif

#ifndef NULL_NODE_ID
  #define NULL_NODE_ID	0xffffffff
#endif

#ifndef BROADCAST_NODE_ID
  #define BROADCAST_NODE_ID		0x00000000
#endif

#ifndef INT_MAX
    #define INT_MAX		0xffffffff
#endif

#ifndef DOUBLE64_EPSILON
    #define DOUBLE64_EPSILON    2.2204460492503131E-16
#endif

#ifndef AnnoWnd
  typedef void *AnnoWnd;	// handle
#endif

#ifndef AnnoGc
  typedef void *AnnoGc;	// handle
#endif

#ifndef AnnoImage
  typedef void *AnnoImage;	// handle
#endif

#ifndef WPARAM
  #if defined (__IOS__) || defined (__MACOS__)
    typedef unsigned long WPARAM;
  #elif defined (__LINUX_CLIENT__)
    typedef unsigned long WPARAM;
  #elif defined _WIN64
	typedef unsigned __int64 WPARAM;
  #elif defined __aarch64__  || defined __x86_64__
	typedef unsigned long WPARAM;
  #else
    typedef unsigned int WPARAM;
  #endif
#endif

#ifndef LPARAM
  #if defined (__IOS__) || defined (__MACOS__) 
    typedef unsigned long LPARAM;
  #elif defined _WIN64
	typedef __int64 LPARAM;
  #else
    typedef long LPARAM;
  #endif
#endif

bool inline AnnoFloatEqual(float f1, float f2)
{
	float df = f1 - f2;
	return df > -1e-6 && df < 1e-6;
}

UInt32 inline AnnoAbs(int value)
{
	UInt32 absVlue = value > 0 ? value : -1 * value;
	return absVlue;
}

typedef struct tagAnnoPoint
{
    Int32	x;
    Int32	y;

    bool operator == (const tagAnnoPoint& point) const
    {
        return (x == point.x) && (y == point.y);
    }
    
    bool operator!= (const tagAnnoPoint& point) const
    {
        return (x != point.x) || (y != point.y);
    }

    bool operator< (const tagAnnoPoint& point) const
    {
        return x < point.x || ((x == point.x) && y < point.y);
    }

	tagAnnoPoint() : x(0), y(0)
	{
	}

	tagAnnoPoint(int __x, int __y) : x(__x), y(__y)
	{
	}
} AnnoPoint;

typedef AnnoPoint AnnoOffset;

typedef struct tagAnnoPointF
{
    Float32   x;
    Float32   y;

    tagAnnoPointF()
    {
        x = y = 0.0f;
    }

    tagAnnoPointF(Float32 __x, Float32 __y)
    {
        x = __x;
        y = __y;
    }

    bool operator== (const tagAnnoPointF& pointF) const
    {
        return AnnoFloatEqual(x, pointF.x) && AnnoFloatEqual(y, pointF.y);
    }
    
    bool operator!= (const tagAnnoPointF& pointF) const
    {
        return !AnnoFloatEqual(x, pointF.x) || !AnnoFloatEqual(y, pointF.y);
    }

    bool operator< (const tagAnnoPointF& pointF) const
    {
        return x < pointF.x || (AnnoFloatEqual(x, pointF.x) && y < pointF.y);
    }
} AnnoPointF;

typedef AnnoPointF AnnoOffsetF;

typedef struct tagAnnoSize
{
    Int32        width;
    Int32        height;

    bool IsEmpty() const
    {
        return (0 >= width) || (0 >= height);
    }

    bool operator== (const tagAnnoSize& size) const
    {
        return (width == size.width) && (height == size.height);
    }
    
    bool operator!= (const tagAnnoSize& size) const
    {
        return (width != size.width) || (height != size.height);
    }
} AnnoSize;

typedef struct tagAnnoSizeF
{
    Float32   width;
    Float32   height;

    bool IsEmpty() const
    {
        return (0 > width) || (0 > height);
    }

    bool operator== (const tagAnnoSizeF& sizeF) const
    {
        return AnnoFloatEqual(width, sizeF.width) && AnnoFloatEqual(height, sizeF.height);
    }
    
    bool operator!= (const tagAnnoSizeF& sizeF) const
    {
        return !AnnoFloatEqual(width, sizeF.width) || !AnnoFloatEqual(height, sizeF.height);
    }
} AnnoSizeF;

typedef struct tagAnnoRect
{
    Int32		left;
    Int32		top;
    Int32		right;
    Int32		bottom;

	tagAnnoRect()
	{
		left = top = right = bottom = 0;
	}

	tagAnnoRect( int l, int t, int r, int b)
	{
		left = l; top = t; right = r; bottom = b;
	}

    Int32 Width() const
    {
        return right - left;
    }

    Int32 Height() const
    {
        return bottom - top;
    }

    AnnoPointF CenterPoint() const
    {
        return AnnoPointF(static_cast<Float32>(left + (Width() / 2.0)), static_cast<Float32>(top + (Height() / 2.0)));
    }
	
    bool IsEmpty() const
    {
        return (left >= right) || (top >= bottom);
    }

    bool operator== (const tagAnnoRect& rect) const
    {
        return (left == rect.left) && (top == rect.top) && (right == rect.right) && (bottom == rect.bottom);
    }
    
    bool operator!= (const tagAnnoRect& rect) const
    {
        return (left != rect.left) || (top != rect.top) || (right != rect.right) || (bottom != rect.bottom);
    }
} AnnoRect;

typedef struct tagAnnoRectF
{
    Float32        left;
    Float32        top;
    Float32        right;
    Float32        bottom;

    tagAnnoRectF()
        : left(0)
        , top(0)
        , right(0)
        , bottom(0)
    {
    }
	
    tagAnnoRectF(Float32 __left, Float32 __top, Float32 __right, Float32 __bottom)
        : left(__left)
        , top(__top)
        , right(__right)
        , bottom(__bottom)
    {
    }
	
    AnnoPointF Origin() const
    {
        return AnnoPointF(left, top);
    }

    Float32 Width() const
    {
        return right - left;
    }
	
    Float32 Height() const
    {
        return bottom - top;
    }

    AnnoPointF CenterPoint() const
    {
        return AnnoPointF(static_cast<Float32>(left + (Width() / 2.0)), static_cast<Float32>(top + (Height() / 2.0)));
    }
	
    bool operator== (const tagAnnoRectF& rectF) const
    {
         bool bEqual = AnnoFloatEqual(left, rectF.left) && AnnoFloatEqual(top, rectF.top) &&
                        AnnoFloatEqual(right, rectF.right) && AnnoFloatEqual(bottom, rectF.bottom);
         return bEqual;
    }
    
    bool operator!= (const tagAnnoRectF& rectF) const
    {
        bool bEqual = AnnoFloatEqual(left, rectF.left) && AnnoFloatEqual(top, rectF.top) &&
        AnnoFloatEqual(right, rectF.right) && AnnoFloatEqual(bottom, rectF.bottom);
        return !bEqual;
    }
} AnnoRectF;

typedef struct tagAnnoWindow
{
    AnnoWnd		wndDrawing;		// the window on which drawing will be made, NULL means it's a whole or portion of monitor on sharer side
    AnnoRect	drawBounding;	// drawing bounding related to wndDrawing's client area, in pixel
    AnnoOffsetF	contentOffset;	// the x/y offset of content related to drawBounding before zooming takes effective
    Float32		zoomFactor;		// 100% = 1.0, 80% = 0.80
    tagAnnoWindow()
    {
        wndDrawing = NULL;
        zoomFactor = 1.0f;
    }

    AnnoRectF ComputeCanvasViewport()
    {
        // the viewport in canvas space taking zoom into account
        AnnoRectF canvasViewport;
        canvasViewport.left = 0.0f - contentOffset.x / zoomFactor;
        canvasViewport.top = 0.0f - contentOffset.y / zoomFactor;
        canvasViewport.right = canvasViewport.left + (drawBounding.Width() / zoomFactor);
        canvasViewport.bottom = canvasViewport.top + (drawBounding.Height() / zoomFactor);
        return canvasViewport;
    }
} AnnoWindow;

typedef struct tagAnnoWindowMultiMonitor
{
    AnnoRect	monitorRect;	// the rectangle of monitor on which the whole or portion of monitor is being shared
    AnnoRect	sharedRect;		// the rectangle of area beging shared
    Float32		dpiScaleOfMonitor;	// the DPI scale of the monitor on which the whole or portion of monitor is being shared
    tagAnnoWindowMultiMonitor()
    {
         dpiScaleOfMonitor = 0.0f;
    }
} AnnoWindowMultiMonitor;

// ----------------------------------------------------------------------------
//	Supported Annotation Mode, used by structure AnnoStartupInput
// ----------------------------------------------------------------------------

typedef enum tagAnnoMode
{
	ANNO_MODE_APPSHARE,
	ANNO_MODE_SCREENSHARE_WB,
	ANNO_MODE_DOCSHARE,
	ANNO_MODE_CHAT_SCREENSHOT,
	ANNO_MODE_NONE
} AnnoMode;

// ----------------------------------------------------------------------------
//	Supported annotation tool, used by AnnoBase::SetAnnoCursor, 
//		AnnoBase::SetAnnoTool, AnnoBase::GetAnnoTool
// ----------------------------------------------------------------------------

typedef enum tagAnnoToolType
{
	ANNO_TOOL_TYPE_NONE,
	ANNO_TOOL_TYPE_PEN,
	ANNO_TOOL_TYPE_HIGHLIGHTER,
	ANNO_TOOL_TYPE_SPOTLIGHT,
	ANNO_TOOL_TYPE_ARROW,
	ANNO_TOOL_TYPE_TEXTBOX,
	ANNO_TOOL_TYPE_PICTURE,
	ANNO_TOOL_TYPE_ERASER,
	ANNO_TOOL_TYPE_BRUSH_ERASER,
	ANNO_TOOL_TYPE_PICKER,
	ANNO_TOOL_TYPE_SELECTOR,
	ANNO_TOOL_TYPE_AUTO_LINE,
	ANNO_TOOL_TYPE_AUTO_ARROW1,
	ANNO_TOOL_TYPE_AUTO_ARROW2,
	ANNO_TOOL_TYPE_AUTO_RECTANGLE,
	ANNO_TOOL_TYPE_AUTO_RECTANGLE_SEMI_FILL,
	ANNO_TOOL_TYPE_AUTO_ROUNDEDRECTANGLE,
	ANNO_TOOL_TYPE_AUTO_ROUNDEDRECTANGLE_SEMI_FILL,
	ANNO_TOOL_TYPE_AUTO_ELLIPSE,
	ANNO_TOOL_TYPE_AUTO_ELLIPSE_SEMI_FILL,
	// added 3.6
	ANNO_TOOL_TYPE_AUTO_DOUBLE_ARROW,
	ANNO_TOOL_TYPE_AUTO_RECTANGLE_FILL,
	ANNO_TOOL_TYPE_AUTO_ROUNDEDRECTANGLE_FILL,
	ANNO_TOOL_TYPE_AUTO_ELLIPSE_FILL,
	ANNO_TOOL_TYPE_AUTO_DIAMOND,
	ANNO_TOOL_TYPE_AUTO_STAMP_ARROW,
	ANNO_TOOL_TYPE_AUTO_STAMP_CHECK,
	ANNO_TOOL_TYPE_AUTO_STAMP_X,
	// added for ZRT 2.0 Mar 2017
	ANNO_TOOL_TYPE_MULTI_FLAT_PEN,
	ANNO_TOOL_TYPE_MULTI_FLAT_ERASER,
	ANNO_TOOL_TYPE_MULTI_THICKNESS_PEN,
	// added June 2018 
	ANNO_TOOL_TYPE_AUTO_STAMP_STAR,
	ANNO_TOOL_TYPE_AUTO_STAMP_HEART,
	ANNO_TOOL_TYPE_AUTO_STAMP_QM,
	// added for ZRT Mar 2019
	ANNO_TOOL_TYPE_MULTI_SHAPE_DETECTOR,
	ANNO_TOOL_TYPE_MULTI_TEXT_DETECTOR,
    // added Feb 2021
    ANNO_TOOL_TYPE_FADE_PEN,
    ANNO_TOOL_TYPE_MOSAIC,
    ANNO_TOOL_TYPE_CIRCLE,
    ANNO_TOOL_TYPE_SQUARE,
    // added Nov 2021
    ANNO_TOOL_TYPE_STICKY_NOTE,
    // added Dec 2021
    ANNO_TOOL_TYPE_AUTO_TRIANGLE,
    ANNO_TOOL_TYPE_CONNECTOR,
    // added on June 20 2022
    ANNO_TOOL_TYPE_PAN,
    ANNO_TOOL_TYPE_AUTO_BUBBLE,
    ANNO_TOOL_TYPE_AUTO_BRACELEFT,
    ANNO_TOOL_TYPE_AUTO_BRACERIGHT,
    ANNO_TOOL_TYPE_AUTO_STAR,
    ANNO_TOOL_TYPE_AUTO_OFFPAGE,
    ANNO_TOOL_TYPE_AUTO_DATA,
    ANNO_TOOL_TYPE_AUTO_BARREL,
    ANNO_TOOL_TYPE_AUTO_DELAY,
    ANNO_TOOL_TYPE_AUTO_DISPLAY,
    ANNO_TOOL_TYPE_AUTO_DOCUMENT,
    ANNO_TOOL_TYPE_AUTO_MANUALINPUT,
    ANNO_TOOL_TYPE_AUTO_MERGE,
    ANNO_TOOL_TYPE_AUTO_MULTIDOC,
    ANNO_TOOL_TYPE_AUTO_TERMINATOR,
    ANNO_TOOL_TYPE_AUTO_PREDEFPROCESS,
    ANNO_TOOL_TYPE_AUTO_PREPARATION,
    ANNO_TOOL_TYPE_AUTO_CLOUD,
    ANNO_TOOL_TYPE_AUTO_ARROW_LEFT,
    ANNO_TOOL_TYPE_AUTO_ARROW_RIGHT,
    ANNO_TOOL_TYPE_AUTO_ARROW_LEFT_RIGHT,
    ANNO_TOOL_TYPE_AUTO_OCTAGON,
    ANNO_TOOL_TYPE_AUTO_HEXAGON,
    ANNO_TOOL_TYPE_AUTO_PENTAGON,
    ANNO_TOOL_TYPE_AUTO_HEART,
    // added on Sep 27 2022
    ANNO_TOOL_TYPE_AUTO_DECAGON,
    ANNO_TOOL_TYPE_AUTO_CUBE,
    ANNO_TOOL_TYPE_AUTO_CROSS,
    ANNO_TOOL_TYPE_AUTO_TRAPEZOID,
    ANNO_TOOL_TYPE_AUTO_OR,
    ANNO_TOOL_TYPE_AUTO_SUMMING_JUNCTION,
    ANNO_TOOL_TYPE_AUTO_MANUAL_OPERATION,
    ANNO_TOOL_TYPE_AUTO_CARD,
    ANNO_TOOL_TYPE_AUTO_HARD_DISK,
    ANNO_TOOL_TYPE_AUTO_INTERNAL_STORAGE,
    ANNO_TOOL_TYPE_AUTO_DISPLAY_NEW,
    ANNO_TOOL_TYPE_AUTO_LOOP_LIMIT,
    ANNO_TOOL_TYPE_AUTO_COLLATE,
    ANNO_TOOL_TYPE_AUTO_ACTOR,
    ANNO_TOOL_TYPE_AUTO_NOTE,
    ANNO_TOOL_TYPE_AUTO_PACKAGE,
    ANNO_TOOL_TYPE_AUTO_USE_CASE,
    ANNO_TOOL_TYPE_AUTO_SEND_SIGNAL,
    ANNO_TOOL_TYPE_AUTO_RECEIVE_SIGNAL,
    ANNO_TOOL_TYPE_AUTO_PLUS,
    ANNO_TOOL_TYPE_AUTO_MINUS,
    ANNO_TOOL_TYPE_AUTO_MULTIPLY,
    ANNO_TOOL_TYPE_AUTO_DIVIDE,
    ANNO_TOOL_TYPE_AUTO_EQUAL,
    ANNO_TOOL_TYPE_AUTO_NOT_EQUAL,
	NUMBER_OF_ANNO_TOOL_TYPE
} AnnoToolType;

typedef enum tagAnnoToolState
{
    ANNO_TOOL_STATE_IDLE,
    ANNO_TOOL_STATE_READY,
    ANNO_TOOL_STATE_EDITING_SHAPE,
    ANNO_TOOL_STATE_EDITING_TEXT
} AnnoToolState;

// ----------------------------------------------------------------------------
//	AnnoBase event type, used by AnnoBaseObserver::OnAnnoBaseNotify
// ----------------------------------------------------------------------------

typedef struct tagAnnoKeyboardInfo
{
    AnnoSize    keyboardSize;
    AnnoRect    textInputFrame;
} AnnoKeyboardInfo;

typedef enum tagAnnoWhiteboardEvent
{
	ANNO_WHITEBOARD_EVENT_WINDOW_CREATED,
	ANNO_WHITEBOARD_EVENT_WINDOW_SHOWN,
	ANNO_WHITEBOARD_EVENT_WINDOW_HIDDEN,
	ANNO_WHITEBOARD_EVENT_WINDOW_DESTROYED,
	ANNO_WHITEBOARD_EVENT_WINDOW_MOVED,
	ANNO_WHITEBOARD_EVENT_WINDOW_RESIZED,
	ANNO_WHITEBOARD_EVENT_WINDOW_TO_BE_CLOSED,
	ANNO_WHITEBOARD_EVENT_WINDOW_MINIMIZED,
	ANNO_WHITEBOARD_EVENT_WINDOW_SET_TITLE
} AnnoWhiteboardEvent;

typedef enum tagAnnoEventType
{
	//notify to session
	ANNO_EVENT_STARTED_UP				= 0x0000,		// to notify that annotation session has just started up
	ANNO_EVENT_SHUT_DOWN				= 0x0001,		// to notify that annotation session has just shut down
	ANNO_EVENT_ROOT_WND					= 0x0002,		// to notify that annotation windows has been created to ensure other windows to be on top of it
	ANNO_EVENT_TOOL_CHANGED				= 0x0003,		// to notify that current annotation tool has been changed (by mouse right click or whatever means that unknown to uppper layer)
	ANNO_EVENT_CAN_UNDO_REDO			= 0x0004,		// to notify if or not undo/redo are available so that UI can enable/disable menu/toolbar respondingly
	ANNO_EVENT_HAS_ANNOTATION			= 0x0005,		// to notify if or not current page has annotation so that UI can enable/disable menu/toolbar icon "Clear All"
	ANNO_EVENT_LOCAL_DRAWING_STATE		= 0x0006,		// to notify that local drawing has been started (ready to accpet local mouse or touch events to draw, or drawing is in progress, etc.) or stopped (not to accpet local mouse or touch events, for example "Mouse" mode)
	ANNO_EVENT_WB_WINDOW_STATE			= 0x0007,		// to notify that WB window has been showed up or hidden
	ANNO_EVENT_DRAW_CHANGED				= 0x0008,		// to notify that draw changed
	ANNO_EVENT_APPLE_STYLUS_DETECTED	= 0x0009,		// to notify that an stylus type input detected on IOS
	ANNO_EVENT_ZR_WINDOW_CHANGED		= 0x000A,		// to notify that ZR windows has been changed
	ANNO_EVENT_REQUEST_ANNOTATOR_NAME	= 0x000B,		// to notify that current drawing changed
	ANNO_EVENT_ZR_DRAW_ANNOTATE			= 0x000C,		// to notify that zr draw annotate
	ANNO_EVENT_PAGE_CHANGED				= 0x000D,		// to notify that page number has changed
	ANNO_EVENT_RECOGNIZE_CHANGED		= 0x000E,		// to notify that reconization text changed
	ANNO_EVENT_PENCIL_DOUBLETAP_PALETTE	= 0x000F,		// to notify that a double tap event has been detected to show color palette
	ANNO_EVENT_UPDATE_TOOLBAR_UI		= 0x0010,		// to notify that toobard ui need to changed
	ANNO_EVENT_RENDER_NOTIFY			= 0x0011,		// to notify that render asynchronous processing return(ios save content..)
	ANNO_EVENT_CONTENT_SAVING_STATE     = 0x0012,		// to notify that the pdfsaving start or the pdfsaving end;
	ANNO_EVENT_ZR_TAP_DETECTED			= 0x0013,		// to notify that tap detected from input and ZRT should show/hide the toolbar, zoom room only
	ANNO_EVENT_TOOL_STATE_CHANGED		= 0x0014,		// to notify that tool state has changed, this is used by VDI & ZR auto hide
	//notify to Media client manage module
	//...0x1000

	//notify to Nydus module
	ANNO_EVENT_SHARER_PROPERTY_CHANGED	= 0x0200,		// to notify Nydus module that remote sharer's doc property has been changed and need Nydus to reset annowindow

	//notify to AS module
	ANNO_EVENT_REMOTE_DRAWING_TO_START	= 0x0300,		// to notify AS module know that remote participants are going to add annotation to presenter's shared screen.
	ANNO_EVENT_REMOTE_DRAW_FINISHED		= 0x0301,		// to notify that a remote drawing command has been just executed on local so that uppper layer (AS) sampling program knows where to retrive the dirty region for best perofrmance
	ANNO_EVENT_CAPTURE_CHANGED			= 0x0302,		// to notify AS module that new difference of frame has been made and needs AS to refresh

    //this part needs to be cleaned and organized
    ANNO_EVENT_WB_TITLE_CHANGED,                        // to notify that whiteboard title has been changed.
	ANNO_EVENT_REQUEST_PAGE_PACKAGE,					// to request doc history data
    ANNO_EVENT_CHECK_REMOVE_ALL_BY_HOST,			    // to notify that this user want to clear all datas, we need to check is host/cohost
    ANNO_EVENT_CHECK_RESTORE_ALL_BY_HOST,			    // to notify that this user want to restore all datas, we need to check is host/cohost
    ANNO_EVENT_WB_CONTENT_CAPTURED,                     // to notify that whiteboard content captured
    ANNO_EVENT_REQUEST_IMAGE_DATA,						// to notify that session to return the image data.
    ANNO_EVENT_GET_USER_AVATAR,                         // to get the user avatar
    ANNO_EVENT_END_CLOUD_WB_LOADING,                    // to notify cloud wb load done
    ANNO_EVENT_WB_ASYNC_REQUEST,                        // to notify async req
    ANNO_EVENT_GET_WB_EXPORT_PATH,                      // to notify get wb export path
    ANNO_EVENT_WB_CHANGE_TEMP_USER_ROLE,                // to change temp role of meeting users
    ANNO_EVENT_WB_CURRENT_USER_ROLE,                    // to notify current wb user role
    ANNO_EVENT_WB_MAKE_PERMANENT,
    ANNO_EVENT_WB_DOC_OPENED,
    ANNO_EVENT_WB_SAVE_RECENTLY_SHAPES,
    ANNO_EVENT_WB_ZR_NOTIFY,
    ANNO_EVENT_WB_GET_HOST,
    ANNO_EVENT_GET_WB_TEMP_PATH,
    ANNO_EVENT_WB_MESSAGE_RECVED,
	NUMBER_OF_ANNO_EVENT_TYPE
} AnnoEventType;

// ----------------------------------------------------------------------------
//	AnnoBase input type: an abstraction of mouse, touch and keyboard input on 
//   all platforms
// ----------------------------------------------------------------------------

typedef enum tagAnnoInputType
{
	ANNO_INPUT_TYPE_NONE		= 0,

	ANNO_INPUT_TYPE_FOCUS		= 0x0007,	// WM_SETFOCUS
	ANNO_INPUT_TYPE_KILLFOCUS	= 0x0008,	// WM_KILLFOCUS
	ANNO_INPUT_TYPE_SETCURSOR	= 0x0020,	// WM_SETCURSOR

	ANNO_INPUT_TYPE_KEYDOWN		= 0x0100,	// WM_KEYDOWN
	ANNO_INPUT_TYPE_KEYUP		= 0x0101,	// WM_KEYUP
	ANNO_INPUT_TYPE_CHAR		= 0x0102,	// WM_CHAR
    ANNO_INPUT_TYPE_SYS_KEYDOWN = 0x0104,   // WM_SYSKEYDOWN

	ANNO_INPUT_TYPE_MOVE		= 0x0200,	// WM_MOUSEMOVE
	ANNO_INPUT_TYPE_LDOWN		= 0x0201,	// WM_LBUTTONDOWN
	ANNO_INPUT_TYPE_LUP			= 0x0202,	// WM_LBUTTONUP
	ANNO_INPUT_TYPE_LDCLICK		= 0x0203,	// WM_LBUTTONDBLCLK
	ANNO_INPUT_TYPE_RDOWN		= 0x0204,	// WM_RBUTTONDOWN
	ANNO_INPUT_TYPE_RUP			= 0x0205,	// WM_RBUTTONUP
	ANNO_INPUT_TYPE_RDCLICK		= 0x0206,	// WM_RBUTTONDBLCLK
	ANNO_INPUT_TYPE_MDOWN		= 0x0207,	// WM_MBUTTONDOWN
	ANNO_INPUT_TYPE_MUP			= 0x0208,	// WM_MBUTTONUP
	ANNO_INPUT_TYPE_MDCLICK		= 0x0209,	// WM_MBUTTONDBLCLK
    ANNO_INPUT_TYPE_MOUSEWHEEL  = 0x020A,   // WM_MOUSEWHEEL

	ANNO_INPUT_TYPE_POINTER_UPDATE			= 0x0245,
	ANNO_INPUT_TYPE_POINTER_DOWN			= 0x0246,
	ANNO_INPUT_TYPE_POINTER_UP				= 0x0247,
	ANNO_INPUT_TYPE_POINTER_ENTER			= 0x0249,
	ANNO_INPUT_TYPE_POINTER_LEAVE			= 0x024A,
	ANNO_INPUT_TYPE_POINTER_ACTIVATE		= 0x024B,
	ANNO_INPUT_TYPE_POINTER_CAPTURECHANGED	= 0x024C,
    ANNO_INPUT_TYPE_POINTER_DOUBLE_TAP      = 0x024D,
    
    ANNO_INPUT_TYPE_USER_BEGIN           = 0x0400 + 501,  // 0x400 = WM_USER
	ANNO_INPUT_TYPE_USER_LBUTTONDOWN,
	ANNO_INPUT_TYPE_USER_LBUTTONUP,
	ANNO_INPUT_TYPE_USER_MOUSEMOVE,
	ANNO_INPUT_TYPE_USER_RBUTTONDOWN,
	ANNO_INPUT_TYPE_USER_RBUTTONUP,
	ANNO_INPUT_TYPE_USER_END,

	ANNO_INPUT_TYPE_CANCEL			= 0x0500,
    
    ANNO_INPUT_TYPE_FLAGS_CHANGED   = 0x600, // Mac OSX flagsChanged
} AnnoInputType;

// ----------------------------------------------------------------------------
//the local File type
// ----------------------------------------------------------------------------
typedef enum tagAnnoFileType
{
	ANNO_FILE_TYPE_UNDEFINED			= 0x00,
	ANNO_FILE_TYPE_IMAGE_PNG			= 0x01,
	ANNO_FILE_TYPE_IMAGE_JPG			= 0x02,
	//ANNO_FILE_TYPE_SVG_NATIVE			= 3, // internal binary format
	NUMBER_OF_ANNO_FILE_TYPE
}AnnoFileType;

typedef enum tagAnnoVirtualKey
{
	ANNO_VIRTUAL_KEY_BACK		= 0x08,
	ANNO_VIRTUAL_KEY_SHIFT		= 0x10,
	ANNO_VIRTUAL_KEY_CONTROL	= 0x11,
	ANNO_VIRTUAL_KEY_ALT		= 0x12,
	ANNO_VIRTUAL_KEY_DELETE		= 0x2E,
    ANNO_VIRTUAL_KEY_Z          = 0x5A,
    ANNO_VIRTUAL_KEY_F1         = 0x70,
    ANNO_VIRTUAL_KEY_F2         = 0x71,
    ANNO_VIRTUAL_KEY_F3         = 0x72,
    ANNO_VIRTUAL_KEY_F4         = 0x73,
    ANNO_VIRTUAL_KEY_F5         = 0x74,
    ANNO_VIRTUAL_KEY_F6         = 0x75,
    ANNO_VIRTUAL_KEY_F7         = 0x76,
    ANNO_VIRTUAL_KEY_F8         = 0x77,
    ANNO_VIRTUAL_KEY_F9         = 0x78,
    ANNO_VIRTUAL_KEY_EQUAL      = 0xBB,
    ANNO_VIRTUAL_KEY_MINUS      = 0xBD,
    ANNO_VIRTUAL_KEY_END        = 0x23,
    ANNO_VIRTUAL_KEY_HOME       = 0x24,
    ANNO_VIRTUAL_KEY_LEFT       = 0x25,
    ANNO_VIRTUAL_KEY_UP         = 0x26,
    ANNO_VIRTUAL_KEY_RIGHT      = 0x27,
    ANNO_VIRTUAL_KEY_DOWN       = 0x28,
    ANNO_VIRTUAL_KEY_PERIOD     = 0xBE,
    ANNO_VIRTUAL_KEY_APOSTROPHE = 0xDE
} AnnoVirtualKey;

typedef enum tagAnnoFlagKey
{
    ANNO_FLAG_KEY_SHIFT         = 0x01,
    ANNO_FLAG_KEY_CONTROL       = 0x02,
    ANNO_FLAG_KEY_ALT           = 0x04
} AnnoFlagKey;

// ----------------------------------------------------------------------------
//	Type used by AnnoBase::SetAnnoColor
// ----------------------------------------------------------------------------

typedef enum tagAnnoColorIndex
{
	ANNO_COLOR_INDEX_ALL			= 0,
	ANNO_COLOR_INDEX_PEN			= 1,
	ANNO_COLOR_INDEX_HIGHLIGHTER	= 2,
	ANNO_COLOR_INDEX_ARROW			= 3,
	ANNO_COLOR_INDEX_SPOTLIGHT		= 4,
	ANNO_COLOR_INDEX_TEXT			= 5,
	ANNO_COLOR_INDEX_AUTO_RECTANGLE	= 6,
	ANNO_COLOR_INDEX_AUTO_ELLIPSE	= 7,
	ANNO_COLOR_INDEX_AUTO_ARROW1	= 8,
	ANNO_COLOR_INDEX_AUTO_ARROW2	= 9,
	NUMBER_OF_ANNO_COLOR_INDEX
} AnnoColorIndex;

// ----------------------------------------------------------------------------
//	Type used by all methods for return result
// ----------------------------------------------------------------------------

typedef enum tagAnnoError
{
    ANNO_SUCCEED    = 0x00000000,
    ANNO_OK         = ANNO_SUCCEED,

    ANNO_FAILED     = 0x00000001
} AnnoError;

static const uint32_t WB_ERROR_NO_BASE = 124000; // ERROR_NO_WHITEBOARD_BASE

typedef enum tagWbErrorCode
{
    WB_LOADING_SUCCEED = 0, // loading wb succeed once one wb page integrated
    WB_DOC_OPEN_TIMEOUT = WB_ERROR_NO_BASE + 1, // timeout: none invalid cloud wbinfo
    WB_DOC_JOIN_TIMEOUT, // timeout: none user join response from dcs
    WB_DOC_PAGE_PACKAGEIDS_TIMEOUT, // timeout: none kDocPagePackageIDs from dcs
    WB_EMPTY_ARCHIVED_DOC, // unexpected an empty archived doc
    WB_PAGE_PACKAGES_DOWNLOAD_FAILED, // all page packages download failed
    WB_PAGE_PACKAGES_DOWNLOAD_TIMEOUT, // timeout: download the page packages timeout
    WB_USER_CONNECTION_CLOSED, // wb user connection close by server
    WB_DELIVER_TO_SYSTEM_ADDTIONALLY // Some key down events need system process after our process
} WbErrorCode;

// ----------------------------------------------------------------------------
//	Type used by AnnoBase::AnnoStartup and AnnoBase::NewWhiteboard
// ----------------------------------------------------------------------------

typedef struct tagAnnoStartupInput
{
	AnnoMode		annoMode;
	bool			isPresenter;
	NODEID			appId;
	const wchar_t*	appName;		// NULL ended unicode string
	NODEID			sharerId;
	UInt16          undoLevel;

	tagAnnoStartupInput()
	{
		annoMode = ANNO_MODE_NONE;
		isPresenter = false;
		appId = 0;
		appName = NULL;
		sharerId = 0;
		undoLevel = 0;
	}
} AnnoStartupInput;

typedef struct tagAnnoInput
{
	AnnoInputType	inputType;
	WPARAM          wParam;
	LPARAM          lParam;

	tagAnnoInput()
	{
		inputType = ANNO_INPUT_TYPE_NONE;
		wParam = 0;
		lParam = 0;
	}
} AnnoInput;

// ----------------------------------------------------------------------------
//	Configurations
// ----------------------------------------------------------------------------

typedef enum tagWbConfigMask
{
    WB_CONFIG_NULL                              = 0x00000000,
	WB_CONFIG_NO_WINDOW_FRAME			        = 0x00000001,
	WB_CONFIG_ALWAYS_FULLSCREEN			        = 0x00000002,
	WB_CONFIG_NEEDS_VIRTUAL_KEYBOARD	        = 0x00000004,
	WB_CONFIG_TOPMOST_WINDOW			        = 0x00000008,
	WB_CONFIG_ENABLE_MULTI_TOUCH		        = 0x00000010,
    WB_CONFIG_ENABLE_SAVE                       = 0x00000020,
    WB_CONFIG_ENABLE_HARDWARE_ACCELERATION      = 0x00000040,
    WB_CONFIG_ENABLE_NAME_TAG                   = 0x00000080,
    WB_CONFIG_CLOUD_WHITEBOARD                   = 0x00000100
} WbConfigMask;

typedef UInt32 WbConfig;

typedef enum tagAnnoConfigMask
{
	ANNO_CONFIG_NULL					        = 0x00000000,
	ANNO_CONFIG_NEEDS_VIRTUAL_KEYBOARD	        = 0x00000001,
	ANNO_CONFIG_ENABLE_MULTI_TOUCH		        = 0x00000002,
	ANNO_CONFIG_DISABLE_DESKTOP_HOOK	        = 0x00000004,
	ANNO_CONFIG_DISABLE_ARROW_WINDOW	        = 0x00000008,
	ANNO_CONFIG_ENABLE_DIRTY_REFRESH	        = 0x00000010,
	ANNO_CONFIG_MOBILE_SHARE_WB			        = 0x00000020,
	ANNO_CONFIG_ENABLE_SHARE_ZOOM_WINDOW        = 0x00000040,
    ANNO_CONFIG_ENABLE_SAVE                     = 0x00000080,
    ANNO_CONFIG_ENABLE_HARDWARE_ACCELERATION    = 0x00000100,
    ANNO_CONFIG_ENABLE_NAME_TAG                 = 0x00000200
} AnnoConfigMask;

typedef UInt32 AnnoConfig;

typedef enum tagCloudWBConfigMask
{
    CLOUD_WB_CONFIG_NULL                            = 0x00000000,
    CLOUD_WB_CONFIG_ENABLE_SAVE                     = 0x00000001,
    CLOUD_WB_CONFIG_ENABLE_HARDWARE_ACCELERATION    = 0x00000002,
    CLOUD_WB_CONFIG_ENABLE_CLOUD_SAVING             = 0x00000004,
    CLOUD_WB_CONFIG_ENABLE_SHARING                  = 0x00000008,
    CLOUD_WB_CONFIG_ENABLE_SHARING_WITH_EX_ORG      = 0x00000010,
    CLOUD_WB_CONFIG_IS_WEBINAR                      = 0x00000020,
    CLOUD_WB_CONFIG_EMBED_WEB_WB                    = 0x00000040,
} CloudWBConfigMask;

typedef uint32_t CloudWBConfig;

// ----------------------------------------------------------------------------
//	The bitmap data storage format type
// ----------------------------------------------------------------------------
typedef enum tagAnnoBitmapFormat
{
	ANNO_BITMAP_FORMAT_NULL		= 0x0000,
	ANNO_BITMAP_FORMAT_BGRA32	= 0x0001,	// Windows DIB
	ANNO_BITMAP_FORMAT_RGBA32	= 0x0002,	// Mac CGContext
    ANNO_BITMAP_FORMAT_RGB24    = 0x0003,
    ANNO_BITMAP_FORMAT_RGB32    = 0x0004,
    ANNO_BITMAP_FORMAT_ARGB32   = 0x0005,
    ANNO_BITMAP_FORMAT_PARGB32  = 0x0006,
	ANNO_BITMAP_FORMAT_NUMBER
}AnnoBitmapFormat;


// ----------------------------------------------------------------------------
//	Page Operation Type used by AnnoEvent::ANNO_EVENT_PAGE_CHANGED
// ----------------------------------------------------------------------------
typedef enum tagAnnoPageOperation
{
	ANNO_PAGE_OPRATION_NONE		= 0x0000,
	ANNO_PAGE_OPRATION_ADD		= 0x0001,
	ANNO_PAGE_OPRATION_REMOVE	= 0x0002,
	ANNO_PAGE_OPRATION_RESTORE	= 0x0003,
	ANNO_PAGE_OPRATION_SWITCH	= 0x0004,
	ANNO_PAGE_OPRATION_NUMBER
}AnnoPageOperation;

typedef struct tagAnnoPageChangeInfo
{
	AnnoPageOperation	pageOp;
	NODEID				pageId;
	Int32				curPageIdx;
	Int32				totalPageNum;

	tagAnnoPageChangeInfo()
	{
		pageOp = ANNO_PAGE_OPRATION_NONE;
		pageId = NULL_NODE_ID;
		curPageIdx = totalPageNum = 0;
	}
}AnnoPageChangeInfo;

typedef enum tagAnnoSaveState
{
    ANNO_SAVE_END = 0,
    ANNO_SAVE_START = 1
} AnnoSaveState;

typedef enum tagAnnoSaveType
{
    ANNO_SAVE_NONE          = 0x00000000,
    ANNO_SAVE_PNG           = 0x00000001, 
    ANNO_SAVE_PDF           = 0x00000002,
    ANNO_SAVE_PNG_MEMORY    = 0x00000003,
    ANNO_SAVE_PDF_MEMORY    = 0x00000004,
    ANNO_SAVE_BITMAP_MEMORY = 0x00000005,
    ANNO_SAVE_JPEG          = 0x00000006,
    ANNO_SAVE_JPEG_MEMORY   = 0x00000007,
    ANNO_SAVE_TYPE_NUM
}AnnoSaveType;

// ----------------------------------------------------------------------------
//	Type used by AnnoBase::GetAnnoBitmapInfo
// ----------------------------------------------------------------------------
typedef struct tagAnnoBitmapInfo
{
    UInt8*			bmData;
    UInt32	        bmFormat;
    UInt32			bmWidth;
    UInt32			bmHeight;
    UInt32          bmPageIndex;
    UInt32          bmPageCount;
    UInt32          bmSize;

    tagAnnoBitmapInfo()
    {
        bmData		= 0;
        bmFormat	= ANNO_BITMAP_FORMAT_NULL;
        bmWidth		= 0;
        bmHeight	= 0;
        bmPageIndex = 0;
        bmPageCount = 0;
        bmSize      = 0;
    }

    void Release()
    {
        if(NULL != bmData)
        {
            delete[] bmData;
            bmData = NULL;
        }

        bmFormat	= ANNO_BITMAP_FORMAT_NULL;
        bmWidth		= 0;
        bmHeight	= 0;
        bmPageIndex = 0;
        bmPageCount = 0;
        bmSize      = 0;
    }
}AnnoBitmapInfo;

typedef struct tagAnnoSaveInfo
{
    Int32 saveState;
    Int32 saveType;
    Int32 savePageNum;
    Int32 shareType;
    bool isAutoSave;
    std::wstring savePath;
    std::wstring saveDirectory;
    void* bitmapDataFormNydus;  //attendee save
    std::vector<int> savePagesList; //all need save pages index
    std::vector<AnnoBitmapInfo> bitmaps; //memory of bitmaps

    tagAnnoSaveInfo()
    {
        saveState = ANNO_SAVE_END;
        saveType = ANNO_SAVE_PNG;
        savePageNum = 0;
        shareType = 0;
        isAutoSave = false;
        bitmapDataFormNydus = NULL;
    }

    void Release()
    {           
        savePagesList.clear();

        for(size_t i=0; i < bitmaps.size(); ++i)
        {
            bitmaps.at(i).Release();
        }
        
        bitmaps.clear();
    }
}AnnoSaveInfo;

typedef enum tagAnnoTranslateType
{
    ANNO_TRANSLATE_NONE                     = 0x0000,
    ANNO_TRANSLATE_WHITEBOARD_TITLE         = 0x0001,   //ZOOM-253664
}AnnoTranslateType;

struct AnnoTranslateInfo
{
    AnnoTranslateType translateType;
    std::wstring      translateText;
};

struct AnnoAndroidJniInfo
{
    long annoWindowJni;
    long feedbackRender;
    long contentRender;
    long annoUIControllerEventSink;
    long startbarHeight;
    bool bShareScreen;
    bool bHDpi;

    AnnoAndroidJniInfo()
    {
        annoWindowJni = 0;
        feedbackRender = 0;
        contentRender = 0;
        annoUIControllerEventSink = 0;
        startbarHeight = 0;
        bShareScreen = false;
        bHDpi = false;
    }
};

typedef struct tagWbPagePackageReq
{
  uint32_t req_id;
  std::string doc_id;
  uint64_t page_id;
  std::string package_id;
  std::string dcs_token;
  std::string host_dcsz_addr;

  tagWbPagePackageReq()
    : req_id(0)
    , page_id(0)
  {}
}WbPagePackageReq;

typedef enum tagRspCode
{
  RSP_SUCCEED,
  RSP_FAILED,
  RSP_TIMEOUT
}RspCode;

typedef struct tagWbPagePackageRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;

  uint8_t* data;
  uint32_t data_len;

  tagWbPagePackageRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
    , data(NULL)
    , data_len(0)
  {}
}WbPagePackageRsp;

typedef enum tagDocumentType
{
    ANNO_EMPTY_DOCUMENT = 0x00,
    ANNO_ARCHIVED_DOCUMENT = 0x01,
}DocumentType;

typedef struct tagCloudWhiteboardInfo
{
  uint32_t doc_sharer_id;
  std::string document_id;
  std::string user_id;
  std::string user_name;
  std::string user_email;
  uint32_t user_role;
  std::string user_avatar;

  DocumentType doc_type;
  CloudWBConfig cloud_wb_config;

  bool b_wb_loading;

  tagCloudWhiteboardInfo() 
  {
    doc_sharer_id = 0;
    user_role = 0;
    doc_type = ANNO_EMPTY_DOCUMENT;
    cloud_wb_config = CLOUD_WB_CONFIG_NULL;
    b_wb_loading = false;
  }
}CloudWhiteboardInfo;

typedef struct tagCloudWhiteboardViewPort
{
  tagCloudWhiteboardViewPort() {};
  std::string doc_id;
  std::string page_id;
  AnnoRectF rect;
} CloudWhiteboardViewPort;

typedef enum tagCloudWBAsyncReqType
{
    CLOUD_WB_ASYNC_REQ_TYPE_NULL,
    CLOUD_WB_ASYNC_REQ_TYPE_USER_AVATAR,
    CLOUD_WB_ASYNC_REQ_TYPE_USER_ADD,
    CLOUD_WB_ASYNC_REQ_TYPE_USER_LIST,
    CLOUD_WB_ASYNC_REQ_TYPE_USER_CHANGE_ROLE,
    CLOUD_WB_ASYNC_REQ_TYPE_USER_REMOVE,
    CLOUD_WB_ASYNC_REQ_TYPE_SHAER_LINK,
    CLOUD_WB_ASYNC_REQ_TYPE_SSR,
    CLOUD_WB_ASYNC_REQ_TYPE_DAS_IMAGE,
    CLOUD_WB_ASYNC_REQ_TYPE_CONTACTS,
    CLOUD_WB_ASYNC_REQ_TYPE_DELETE_WB,
    CLOUD_WB_ASYNC_REQ_TYPE_ALL_ROASTERS,
} CloudWBAsyncReqType;

typedef struct tagWbAsyncResponse
{
    CloudWBAsyncReqType reqType;
    void* rspData;
}WbAsyncResponse;

typedef enum tagAnnoImageDataFormat {
	ANNO_IMAGE_OBJECT_FORMAT_UNKNOWN = -1,
	ANNO_IMAGE_OBJECT_FORMAT_SVG = 0,
	ANNO_IMAGE_OBJECT_FORMAT_PNG = 1,
} AnnoImageDataFormat;

typedef struct tagAnnoImageDataReq
{
	std::string token;
	AnnoImageDataFormat format;
	uint64_t objId;
	std::string docId;
	std::string pageId;
	std::string elementData;
    CloudWBAsyncReqType reqType;

	tagAnnoImageDataReq()
	{
		objId = 0;
		format = ANNO_IMAGE_OBJECT_FORMAT_UNKNOWN;
	}
	
	bool operator< ( const struct tagAnnoImageDataReq& other ) const
	{
		// Ignore token
		return objId < other.objId || (objId == other.objId &&
			(format < other.format || (format == other.format &&
			(docId < other.docId || (docId == other.docId &&
			(pageId < other.pageId) || (reqType < other.reqType))))));
	}
	bool operator== ( const struct tagAnnoImageDataReq& other ) const
	{
		// Ignore token
		return objId == other.objId && format == other.format &&
			docId == other.docId && pageId == other.pageId &&
            reqType == other.reqType;
	}
} AnnoImageDataReq;

#define ANNO_IMAGE_DATA_ERROR_CODE__SUCCESS  0

typedef struct tagAnnoImageData
{
	AnnoImageDataReq request;
	int error_code;
	std::string data;
	AnnoRectF rect;

	tagAnnoImageData() : error_code(ANNO_IMAGE_DATA_ERROR_CODE__SUCCESS)
	{}

	tagAnnoImageData(const tagAnnoImageData& rhs)
	{
		request.format = rhs.request.format;
		request.objId = rhs.request.objId;
		request.docId = rhs.request.docId;
		request.pageId = rhs.request.pageId;
		error_code = rhs.error_code;
		data = rhs.data;
		rect = rhs.rect;
	}
} AnnoImageData;

// deprecated - delete 
typedef enum tagAnnoUserAccessLevel
{
    ANNO_USER_ACCESS_LEVEL_NULL,
    ANNO_USER_ACCESS_LEVEL_OWNER,
    ANNO_USER_ACCESS_LEVEL_EDITOR,
    ANNO_USER_ACCESS_LEVEL_COMMENTER,
    ANNO_USER_ACCESS_LEVEL_VIEWER,
} AnnoUserAccessLevel;

// deprecated - delete
typedef struct tagAnnoUserInfo
{
    int userId;
    bool isMeetingUser;
    std::wstring userName;
    std::wstring userAvatarPath;
    AnnoUserAccessLevel userAccessLevel;
} AnnoUserInfo;

typedef enum tagCloudWBUserRole
{
    CLOUD_WB_USER_ROLE_OWNER = 0,
    CLOUD_WB_USER_ROLE_COOWNER = 1,
    CLOUD_WB_USER_ROLE_EDITOR = 2,
    CLOUD_WB_USER_ROLE_COMMENTER = 3,
    CLOUD_WB_USER_ROLE_VIEWER = 4
} CloudWBUserRole;

typedef enum tagCloudWBUserType
{
    CLOUD_WB_USER_TYPE_SAME_ACCOUNT = 0,
    CLOUD_WB_USER_TYPE_EXTERNAL = 1,
    CLOUD_WB_USER_TYPE_CHANNEL = 2,
} CloudWBUserType;

typedef enum
{
    SHARE_SCOPE_DEFAULT = 0,
    SHARE_SCOPE_SAME_ACCOUNT = 1,
    SHARE_SCOPE_ANYONE = 2
} ShareScope;

typedef enum
{
    CHANNEL_TYPE_PRIVATE_MUC = 0,
    CHANNEL_TYPE_PUBLIC_MUC = 1,
    CHANNEL_TYPE_PRIVATE_CHANNEL = 2,
    CHANNEL_TYPE_PUBLIC_CHANNEL = 3,
} ChannelType;

typedef struct tagWbDASUser
{
    std::string user_id;
    std::string user_name;
    std::string user_email;
    CloudWBUserRole user_role;
    CloudWBUserType user_type;
    std::string user_avatar_url;
} CloudWBUser;

typedef struct tagCloudWBUserAvatarReq
{
  uint32_t req_id;
  std::string user_id;
  std::string avatar_url;

  tagCloudWBUserAvatarReq()
    : req_id(0)
  {}
} CloudWBUserAvatarReq;

typedef struct tagCloudWBUserAvatarRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;
  std::string user_id;
  std::wstring avatar_path;

  tagCloudWBUserAvatarRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
  {}
} CloudWBUserAvatarRsp;

typedef struct tagCloudWBUserAddReq
{
  uint32_t req_id;
  std::string doc_id;
  std::vector<CloudWBUser> users; //required: user_id, user_role, user_type

  tagCloudWBUserAddReq()
    : req_id(0)
  {}
} CloudWBUserAddReq;

typedef struct tagCloudWBUserAddRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;

  tagCloudWBUserAddRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
  {}
} CloudWBUserAddRsp;

typedef struct tagCloudWBUserListReq
{
  uint32_t req_id;
  std::string doc_id;

  tagCloudWBUserListReq()
    : req_id(0)
  {}
} CloudWBUserListReq;

typedef struct tagCloudWBUserListRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;
  std::string account_name;
  std::string share_link;
  ShareScope share_scope;
  uint32_t share_role;
  CloudWBUser owner;
  std::vector<CloudWBUser> user_list;

  tagCloudWBUserListRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
    , share_scope(SHARE_SCOPE_DEFAULT)
    , share_role(0)
  {}
} CloudWBUserListRsp;

typedef struct tagCloudWBUserChangeRoleReq
{
  uint32_t req_id;
  std::string doc_id;
  std::vector<CloudWBUser> users; //required: user_id, user_role, user_type

  tagCloudWBUserChangeRoleReq()
    : req_id(0)
  {}
} CloudWBUserChangeRoleReq;

typedef struct tagCloudWBUserChangeRoleRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;

  tagCloudWBUserChangeRoleRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
  {}
} CloudWBUserChangeRoleRsp;

typedef struct tagCloudWBUserRemoveReq
{
    uint32_t req_id;
    std::string doc_id;
    std::vector<CloudWBUser> users; //required: user_id, user_type

    tagCloudWBUserRemoveReq()
        : req_id(0)
    {}
} CloudWBUserRemoveReq;

typedef struct tagCloudWBUserRemoveRsp
{
    uint32_t req_id;
    RspCode rsp_code;

    tagCloudWBUserRemoveRsp()
        : req_id(0)
        , rsp_code(RSP_FAILED)
    {}
} CloudWBUserRemoveRsp;

typedef struct tagCloudWBShareLinkReq
{
  uint32_t req_id;
  std::string doc_id;
  ShareScope share_scope;
  uint32_t user_role;

  tagCloudWBShareLinkReq()
    : req_id(0)
    , share_scope(SHARE_SCOPE_DEFAULT)
    , user_role(0)
  {}
} CloudWBShareLinkReq;

typedef struct tagCloudWBShareLinkRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;
  std::string share_link;
  ShareScope share_scope;
  uint32_t user_role;

  tagCloudWBShareLinkRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
    , share_scope(SHARE_SCOPE_DEFAULT)
    , user_role(0)
  {}
} CloudWBShareLinkRsp;

typedef struct tagCloudWBDeleteReq
{
  uint32_t req_id;
  std::string doc_id;
  std::wstring doc_title;

  tagCloudWBDeleteReq()
    : req_id(0)
  {}
} CloudWBDeleteReq;

typedef struct tagCloudWBDeleteRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;

  tagCloudWBDeleteRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
  {}
} CloudWBDeleteRsp;

typedef struct tagCloudWBContactsReq
{
  uint32_t req_id;
  std::string key;
  tagCloudWBContactsReq()
    : req_id(0)
  {}
} CloudWBContactsReq;

struct CloudWBContactAdditionalInfo
{
  int32_t memberCount;
  ChannelType channelType;
};

struct CloudWBContact
{
  std::string id;
  std::string display_name;
  std::string email;
  int32_t role;
  int32_t type;
  CloudWBContactAdditionalInfo additionalInfo;
};

typedef struct tagCloudWBContactsRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;
  std::vector<CloudWBContact> contacts_list;

  tagCloudWBContactsRsp()
    : rsp_id(0)
  {}
} CloudWBContactsRsp;


typedef struct tagAnnoContent
{
    void*             data;
    size_t            dataLen;
    size_t            maxSize;

    AnnoBitmapFormat  dataFormat;
    uint32_t          bmWidth;
    uint32_t          bmHeight;
    uint32_t          bmStride;

    tagAnnoContent()
    {
        data = 0;
        dataLen = 0;
        maxSize = 0;
        
        dataFormat = ANNO_BITMAP_FORMAT_NULL;
        bmWidth = 0;
        bmHeight = 0;
        bmStride = 0;
    }
}AnnoContent;

typedef struct tagPagePackageInfo
{
  uint64_t page_id;
  uint32_t page_status;
  std::string page_package_id;
}PagePackageInfo;

typedef struct tagWbMonitorInfo
{
  uint32_t wb_app_id;
  // wb config
  uint32_t cloud_wb_config;
  // wb error code
  uint32_t error_code;
  // document info
  uint32_t doc_sharer_id;
  std::string doc_id;
  
  // previlege info
  std::string user_id;
  uint32_t user_idx;
  uint32_t user_role;
  uint32_t permission_whiteboard;
  uint32_t permission_collaborator;
  uint32_t permission_page;
  uint32_t permission_content;
  uint32_t permission_comment;
  uint32_t permission_version;
  uint32_t permission_sharedlink;
  
  std::string connection_id;
  // page info
  std::string host_dcsz_addr;
  uint32_t count_send_wb_message;
  uint32_t count_recv_wb_message;
  std::vector<PagePackageInfo> page_package_infos;
}WbMonitorInfo;

typedef enum
{
  CLOUD_WB_SETTING_UNKNOWN,
  CLOUD_WB_SETTING_HIDE_PROFILE_AVATAR, 
  CLOUD_WB_SETTING_RECENTLY_SHAPES,
  CLOUD_WB_SETTING_FEEDBACK,
  CLOUD_WB_SETTING_SHARE,
  CLOUD_WB_SETTING_EXPORT,
  CLOUD_WB_SETTING_ZR_SAVE,
  CLOUD_WB_SETTING_EXPORT_FLAG
}CloudWbSetting;

typedef uint64_t WBElemID;
typedef std::vector<WBElemID> WBElemIDList;

typedef enum tagWbPageStatus
{
  WB_PAGE_STATUS_UNKNOWN = 0x00,
  WB_PAGE_INTEGRATED = 0x01,
  WB_PAGE_IN_LOADING = 0x02,
  WB_PAGE_NOT_LOADED = 0x03
}WbPageStatus;

typedef struct tagWbPageInfo
{
  WBElemID pageId;
  WbPageStatus pageStatus;
}WbPageInfo;

enum WBCustomizeAttrType
{
	WB_CUSTOMIZE_ATTR_NONE,
	WB_CUSTOMIZE_ATTR_FEEDBACK,
	WB_CUSTOMIZE_ATTR_SHARE,
	WB_CUSTOMIZE_ATTR_LANGUAGE
};

struct WBCustomizeAttrData
{
	bool bValue;
	std::wstring strValue1;
	std::wstring strValue2;

	WBCustomizeAttrData()
	{
		bValue = true;
		strValue1 = L"";
		strValue2 = L"";
	}
};

typedef struct tagCloudWBAllRoastersReq
{
  uint32_t req_id;
  std::string doc_id;
  std::string dcs_token;
  tagCloudWBAllRoastersReq()
    : req_id(0)
  {}
} CloudWBAllRoastersReq;

typedef struct tagCloudWBAllRoastersRsp
{
  uint32_t rsp_id;
  RspCode rsp_code;

  uint8_t* data;
  uint32_t data_len;

  tagCloudWBAllRoastersRsp()
    : rsp_id(0)
    , rsp_code(RSP_FAILED)
    , data(NULL)
    , data_len(0)
  {}
}CloudWBAllRoastersRsp;

typedef struct tagAnnoViewerOffsetData
{
    tagAnnoViewerOffsetData()
        :viewLeft(0)
        ,viewTop(0)
        ,offsetX(0)
        ,offsetY(0)
    {

    }

    int viewLeft;
    int viewTop;
    int offsetX;
    int offsetY;
}AnnoViewerOffsetData;

typedef struct tagWbMessageData
{
  uint32_t sender_id;
  const uint8_t* p_data;
  size_t data_len;

  tagWbMessageData()
  {
    sender_id = 0;
    p_data = 0;
    data_len = 0;
  }
}WbMessageData;

#define ANNO_COLOR_32_PALETTE_YELLOW 0xFFFFBF39
#define ANNO_COLOR_32_PALETTE_ORANGE 0xFFFF8422
#define ANNO_COLOR_32_PALETTE_PURPLE 0xFFA477FF
#define ANNO_COLOR_32_PALETTE_GREEN 0xFF66CC84
#define ANNO_COLOR_32_PALETTE_BLUE 0xFF2D8CFF
#define ANNO_COLOR_32_PALETTE_RED 0xFFF46670
#define ANNO_COLOR_32_PALETTE_BLACK 0xFF252A30
#define ANNO_COLOR_32_PALETTE_WHITE 0xFFF7F9FA

#define ANNO_COLOR_32_PALETTE_STICKY_YELLOW 0xFFFFEB99
#define ANNO_COLOR_32_PALETTE_STICKY_ORANGE 0xFFFFC699
#define ANNO_COLOR_32_PALETTE_STICKY_PURPLE 0xFFCFB2FF
#define ANNO_COLOR_32_PALETTE_STICKY_GREEN 0xFFB8E0B8
#define ANNO_COLOR_32_PALETTE_STICKY_BLUE 0xFF99BEFF
#define ANNO_COLOR_32_PALETTE_STICKY_RED 0xFFF7A1A1
#define ANNO_COLOR_32_PALETTE_STICKY_BLACK 0xFF444B53
#define ANNO_COLOR_32_PALETTE_STICKY_WHITE 0xFFF5F5F5

#endif // __ANNO_TYPES_H__
