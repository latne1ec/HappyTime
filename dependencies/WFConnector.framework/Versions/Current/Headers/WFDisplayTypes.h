//
//  WFDisplayTypes.h
//  WFConnector
//
//  Created by Murray Hughes on 16/12/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#ifndef WFConnector_WFDisplayTypes_h
#define WFConnector_WFDisplayTypes_h


// Support hardware button gestures
#define WF_DISPLAY_BUTTON_SOUTH_WEST_TOUCHED_NAME    @"buttonSouthWestTouched"
#define WF_DISPLAY_BUTTON_NORTH_WEST_TOUCHED_NAME    @"buttonNorthWestTouched"
#define WF_DISPLAY_BUTTON_SOUTH_EAST_TOUCHED_NAME    @"buttonSouthEastTouched"
#define WF_DISPLAY_BUTTON_NORTH_EAST_TOUCHED_NAME    @"buttonNorthEastTouched"
#define WF_DISPLAY_BUTTON_FRONT_TOUCHED_NAME         @"buttonFrontTouched"
#define WF_DISPLAY_BUTTON_SCREEN_TOUCHED_NAME        @"buttonScreenTouched"



// Supported hardware button functions
#define WF_DISPLAY_BTNFN_PAGELEFT_KEY                @"hardwarePageLeft"
#define WF_DISPLAY_BTNFN_PAGERIGHT_KEY               @"hardwarePageRight"


// ====================================================
// ==== ENUMS
// ====================================================

// Colors, 2-bit color values. If only 1-bit is supported then
// Light-Gray can be treated as WHITE
// Dark-Gray can be treated as BLACK
typedef enum
{
    WF_DISPLAY_COLOR_BLACK          = 0x00,
    WF_DISPLAY_COLOR_DARK_GREY      = 0x01,
    WF_DISPLAY_COLOR_LIGHT_GREY     = 0x02,
    WF_DISPLAY_COLOR_WHITE          = 0x03,

    WF_DISPLAY_COLOR_NONE           = 0x04,

    WF_DISPLAY_COLOR_INVALID        = 0xFF,

} wf_display_color_e;

// -----------------------------------------------------------------------------
// Alignment (Text)

typedef enum
{
    WF_DISPLAY_ALIGNMENT_LEFT       = 0x00,
    WF_DISPLAY_ALIGNMENT_CENTER     = 0x01,
    WF_DISPLAY_ALIGNMENT_RIGHT      = 0x02,
    
    WF_DISPLAY_ALIGNMENT_INVALID    = 0xFF,

} wf_display_alignment_e;

// -----------------------------------------------------------------------------
// Font (Text)

typedef enum
{
    WF_DISPLAY_FONT_SYSTEM10        = 0x00,     // RFLKT, Dev1
    WF_DISPLAY_FONT_SYSTEM19        = 0x01,     // RFLKT
    WF_DISPLAY_FONT_SYSTEM26        = 0x02,     // RFLKT, Dev1
    WF_DISPLAY_FONT_SYSTEM33        = 0x03,     // RFLKT
    WF_DISPLAY_FONT_SYSTEM48        = 0x04,     // RFLKT
    
    
    WF_DISPLAY_FONT_SYSTEM12        = 0x05,     // Echo, Dev1
    WF_DISPLAY_FONT_SYSTEM14        = 0x06,     // Echo
    WF_DISPLAY_FONT_SYSTEM16        = 0x07,     // Echo
    WF_DISPLAY_FONT_SYSTEM18        = 0x13,     // Echo
    WF_DISPLAY_FONT_SYSTEM24        = 0x14,     // Echo
    WF_DISPLAY_FONT_SYSTEM30        = 0x15,     // Echo
    WF_DISPLAY_FONT_SYSTEM36        = 0x16,     // Echo
    WF_DISPLAY_FONT_SYSTEM42        = 0x17,     // Echo
    WF_DISPLAY_FONT_SYSTEM52        = 0x18,     // Echo
    WF_DISPLAY_FONT_SYSTEM62        = 0x19,     // Echo
    WF_DISPLAY_FONT_SYSTEM76        = 0x1A,     // Echo
    WF_DISPLAY_FONT_SYSTEM94        = 0x1B,     // Echo

    WF_DISPLAY_FONT_SYSTEM39        = 0x1C,     // Dev1

    
    WF_DISPLAY_FONT_INVALID         = 0xFF,

} wf_display_font_e;


// -----------------------------------------------------------------------------
// Element Property ID's

typedef enum
{
    WF_DISPLAY_PROPERTY_VALUE           = 0x00,
    WF_DISPLAY_PROPERTY_FRAME           = 0x01,
    WF_DISPLAY_PROPERTY_ALIGN           = 0x02,
    WF_DISPLAY_PROPERTY_FONT            = 0x03,
    WF_DISPLAY_PROPERTY_FORMAT          = 0x04,
    WF_DISPLAY_PROPERTY_MASK            = 0x05,
    WF_DISPLAY_PROPERTY_SCROLL          = 0x06,
    WF_DISPLAY_PROPERTY_DELAY           = 0x07,
    WF_DISPLAY_PROPERTY_ENABLED         = 0x08,
    WF_DISPLAY_PROPERTY_HIDDEN          = 0x09,
    
    WF_DISPLAY_PROPERTY_VALUE_UINT8     = 0x0A,
    WF_DISPLAY_PROPERTY_VALUE_DECIMAL8  = 0x0B,
    
} wf_display_property_e;


// -----------------------------------------------------------------------------

// Elements Types
typedef enum
{
    WF_DISPLAY_ELEMENT_PAGE = 0x01,

    WF_DISPLAY_ELEMENT_RECT = 0x03,
    WF_DISPLAY_ELEMENT_STRING = 0x04,
    WF_DISPLAY_ELEMENT_BITMAP = 0x06,

    WF_DISPLAY_ELEMENT_GLOBAL_SOUND  = 0x08,
    WF_DISPLAY_ELEMENT_GLOBAL_STRING = 0x09,
    WF_DISPLAY_ELEMENT_GLOBAL_BITMAP = 0x0A,

    
    // 0x0B
    
    WF_DISPLAY_ELEMENT_INVALID = 0xFF,
    
} wf_display_element_e;


// -----------------------------------------------------------------------------
// Location (Text)

typedef enum
{
    WF_DISPLAY_ELEMENT_LOCATION_CUSTOM              = 0x00,
    
    WF_DISPLAY_ELEMENT_LOCATION_PRIMARY             = 0x01,
    WF_DISPLAY_ELEMENT_LOCATION_SECONDARY           = 0x02,
    WF_DISPLAY_ELEMENT_LOCATION_TERTIARY            = 0x03,
    
    WF_DISPLAY_ELEMENT_LOCATION_INVALID             = 0xFF,
    
} wf_display_element_location_e;

// -----------------------------------------------------------------------------

// Date Formats
typedef enum
{
    WF_DISPLAY_DATE_FORMAT_YYYY_MM_DD   = 0x00, // YYYY-MM-DD
    WF_DISPLAY_DATE_FORMAT_MM_DD_YYYY   = 0x01, // MM/DD/YYYY
    WF_DISPLAY_DATE_FORMAT_DD_MM_YYYY   = 0x02, // DD-MM-YYYY
    WF_DISPLAY_DATE_FORMAT_DD_MM_YYYY_2 = 0x03, // DD/MM/YYYY
    
} wf_display_date_format_e;


// -----------------------------------------------------------------------------
// Time Formats
typedef enum
{
    WF_DISPLAY_TIME_FORMAT_HH_MM_SS_AM_PM   = 0x00, // 12H Clock
    WF_DISPLAY_TIME_FORMAT_HH_MM_SS         = 0x01, // 24H Clock
} wf_display_time_format_e;


// -----------------------------------------------------------------------------
// Days of Week
typedef enum
{
    WF_DISPLAY_DAY_SUNDAY       = 0,
    WF_DISPLAY_DAY_MONDAY       = 1,
    WF_DISPLAY_DAY_TUESDAY      = 2,
    WF_DISPLAY_DAY_WEDNESDAY    = 3,
    WF_DISPLAY_DAY_THURSDAY     = 4,
    WF_DISPLAY_DAY_FRIDAY       = 5,
    WF_DISPLAY_DAY_SATURDAY     = 6,
} wf_display_day_e;


// -----------------------------------------------------------------------------
// Watchface Style
typedef enum {
    
    WF_DISPLAY_WATCH_FACE_STYLE_DIGITAL = 0,
    WF_DISPLAY_WATCH_FACE_STYLE_ANAGLOG = 1,
} wf_display_watch_face_style_e;








#endif
