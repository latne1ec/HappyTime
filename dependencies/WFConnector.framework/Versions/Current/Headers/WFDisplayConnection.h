//
//  WFDisplayConnection.h
//  WFConnector
//
//  Created by Murray Hughes on 23/05/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorConnection.h>
#import "WFDisplayConnectionDelegate.h"
#import "WFDisplayMemoryCalculator.h"
#import "WFDisplayData.h"
#import "WFDisplayTypes.h"


// RELEASE_TODO:  clean up and document.

@class WFDisplaySensorConfiguration;

/**
 * Represents a connection to an detatched display (bike computer / watch)
 */
@interface WFDisplayConnection : WFSensorConnection 
{
    id<WFDisplayConnectionDelegate> _displayConnectionDelegate;
    
    
    int currentPage;
    NSMutableArray* updateQueue;
    WFDisplaySensorConfiguration* configuration;

    float _lastLoadingProgress;
    BOOL didSendConfigWithDelegate;
}


@property (nonatomic, assign) id<WFDisplayConnectionDelegate> displayConnectionDelegate;

- (NSString*) currentPageKey;

// Returns a list of page keys that the API recomends for element updates 
- (NSArray*) recomendedPageKeysToUpdate;

- (WFDisplayData*) getDisplayData;

// Load a new configuation
- (void) loadConfiguration:(WFDisplayConfiguration*) configuation;

// Begin a group of updates
- (void) beginUpdates;

// Begin a group of updates that are sent regardless of the current page.
// Used mostly for hidden pages
- (void) beginForcedUpdates;

// End group updates
- (void) endUpdates;

- (void) endUpdatesCompletion:(void (^)(void)) completionBlock;


// Updates a element with a new value. Currently only applies to strings
- (BOOL) setValue:(id)value forElementWithKey:(NSString *)key;

// Updates the element's frame
- (BOOL) setFrame:(CGRect)frame forElementWithKey:(NSString *)key;

// Hide/Show the element with key
- (BOOL) setHidden:(BOOL)hidden forElementWithKey:(NSString *)key;

// Plays sound/beep with given key
- (BOOL) playSoundWithKey:(NSString*) key;



/**
 * Sets the current Page being displayed
 *
 * @param pageKey As defined in the configuration file.
 *
 * @param timeout Optional timeout value to automatically go pack to the previous page
 *                  Set to 0 if you do not want it to go back.
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
- (BOOL) setPageVisibleWithKey:(NSString*) pageKey timeout:(NSTimeInterval) timeout;


/**
 * DEPRECATED: Use setPageVisibleWithKey:timeout: (Spelling Error)
 */
 - (BOOL) setPageVisableWithKey:(NSString*) pageKey timeout:(NSTimeInterval) timeout DEPRECATED_ATTRIBUTE;



/** 
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
- (BOOL) setBacklightOn:(UCHAR)ucPercentOn;

- (BOOL) setBacklightOn:(UCHAR)ucPercentOn withTimeout:(NSTimeInterval) timeout;


/**
 * Inverts the colors on the display
 * 
 * @param inverted YES if display shoudl invert colors as defined in confg file
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
- (BOOL) setDisplayInverted:(BOOL) inverted;
- (BOOL) getDisplayInverted;

/**
 * Enables and sets delay for auto page scrolling. Setting this to a positive delay
 * will automatically cycle through each of the visable pages in the config
 *
 * @param delay Period that each page is displayed on the screen
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
- (BOOL) setAutoPageScrollWithDelay:(NSTimeInterval) delay;

/**
 * Disabled auto page scrolling.
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
- (BOOL) setAutoPageScrollDisabled;


/**
 * Sets the behaviour of the device when intentionally disconnecting the display
 * Default behaviour is for the device to always go back into advertising mode,
 * although if the app is calling disconnect, it would be prefered that the 
 * display goes directly to sleep, if the user wants to reconnect, they need
 * to wake up the device again.
 *
 * In some devices, 'sleep' may be an alternative disconnected mode. eg Watch mode
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
- (BOOL) setShouldSleepOnDisconnect:(BOOL) sleepOnDisconnect;


/**
 * Sets the standard pressure for the altimeter which is used to calculate
 * the absolute elevation of the device.  Setting a pressure <= 0 will use
 * mean sea level atmospheric pressure (101325 pascals)
 *
 * @param pressure Current atmospheric pressure (at sea level) in pascals.
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
-(BOOL)setAltimeterStandardPressure:(double)pressure;

/**
 * Sets the standard pressure for the altimeter by using a known elevation and a
 * measured pressure from the device's barometer.
 *
 * @param elevation Current elevation in meters.
 *
 * @return <c>TRUE</c> if the value is sent, otherwise <c>FALSE</c>.
 */
-(BOOL)setAltimeterCurrentElevation:(double)elevation;

@end