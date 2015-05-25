//
//  WFDisplayConnectionDelegate.h
//  WFConnector
//
//  Created by Murray Hughes on 23/05/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WFDisplayTypes.h"

@class WFDisplayConnection, WFDisplayConfiguration;

@protocol WFDisplayConnectionDelegate <NSObject>

/**
 * Delegate method called when the conneciton is ready to receive a configuation file.
 * If nil, the display will display "No Config"
 " If the configation matches the one loaded on the device, it doesn't bother reloading it.
 */
- (WFDisplayConfiguration*) configurationForDisplayConnection:(WFDisplayConnection*) connection;

/**
 * Delegate method when a button is pressed down. Always called regardless of configuration
 */
- (void) displayConnection:(WFDisplayConnection*) connection didButtonDown:(int) buttonIndex;

/**
 * Delegate method when a button is release. Always called regardless of configuration
 */
- (void) displayConnection:(WFDisplayConnection*) connection didButtonUp:(int) buttonIndex;

/**
 * Delegate method when the visable page is changed by the user or the iOS device
 */
- (void) displayConnection:(WFDisplayConnection*) connection visablePageChanged:(NSString*) visablePageKey;

/**
 * Delegate methods for config loading progress and errors
 */

- (void) displayConnectionDidStartConfigurationLoading:(WFDisplayConnection*) connection;

- (void) displayConnection:(WFDisplayConnection*) connection didProgressConfigurationLoading:(float) progress;

- (void) displayConnectionDidFinishConfigurationLoading:(WFDisplayConnection*) connection;

- (void) displayConnection:(WFDisplayConnection*) connection didFailConfigurationLoadingWithError:(NSError*) error;


/** 
 * Delegate methods for settings
 *
 * Most settings have a GET and SET method, either will result in the same 'Responsd' callback
 *
 * If unsuccessful, "error" is set with the encountered failure.
 *
 */

@optional

- (void) displayConnection:(WFDisplayConnection*) connection didRespondBacklightOn:(BOOL) backlightOn error:(NSError*) error;

- (void) displayConnection:(WFDisplayConnection*) connection didRespondDisplayInverted:(BOOL) inverted error:(NSError*) error;

- (void) displayConnection:(WFDisplayConnection*) connection didRespondPageVisableWithKey:(NSString*) pageKey error:(NSError*) error;

- (void) displayConnection:(WFDisplayConnection*) connection didRespondDate:(NSDate*) date timeZone:(NSTimeZone*) timeZone error:(NSError*) error;

- (void) displayConnection:(WFDisplayConnection*) connection didRespondAutoPageScrollWithDelay:(NSTimeInterval) delay error:(NSError*) error;

- (void) displayConnection:(WFDisplayConnection*) connection didRespondDateFormat:(wf_display_date_format_e) dateFormat timeFormat:(wf_display_time_format_e) timeFormat startDayOfWeek:(wf_display_day_e) startDayOfWeek watchfaceStyle:(wf_display_watch_face_style_e) watchfaceStyle error:(NSError*) error;

- (void) displayConnection:(WFDisplayConnection*) connection didRespondShouldSleepOnDisconnect:(BOOL) sleepOnDisconnect error:(NSError*) error;



@end
