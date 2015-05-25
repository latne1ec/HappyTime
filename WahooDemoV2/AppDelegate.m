//
//  AppDelegate.m
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "AppDelegate.h"
#import <WFConnector/WFConnector.h>

#define UIColorFromRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

@interface AppDelegate () <WFHardwareConnectorDelegate>

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    
    //Setup the Wahoo Hardware Connector
    [[WFHardwareConnector sharedConnector] enableBTLE:YES];
    [[WFHardwareConnector sharedConnector] setSampleTimerDataCheck:YES];
    
    [WFHardwareConnector sharedConnector].delegate = self;
    [WFHardwareConnector sharedConnector].sampleRate = 0.5;  // sample rate 500 ms, or 2 Hz.
    [WFHardwareConnector sharedConnector].settings.useMetricUnits = [[[NSLocale currentLocale] objectForKey:NSLocaleUsesMetricSystem] boolValue];
    
    
    
    [[UINavigationBar appearance] setTintColor:UIColorFromRGB(0xeb5858)];
    [[UITabBar appearance] setTintColor:[UIColor colorWithRed:0.922 green:0.345 blue:0.345 alpha:1]];
    
    
    NSShadow *shadow = [[NSShadow alloc] init];
    shadow.shadowColor = [UIColor clearColor];
    shadow.shadowOffset = CGSizeMake(0, .0);
    [[UINavigationBar appearance] setTitleTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:
                                                          [UIColor colorWithRed:0.247 green:0.231 blue:0.227 alpha:1], NSForegroundColorAttributeName,
                                                          shadow, NSShadowAttributeName,
                                                          [UIFont fontWithName:@"AvenirNext-Medium" size:18.5], NSFontAttributeName, nil]];
    
    
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


#pragma mark -
#pragma mark HardwareConnectorDelegate Implementation

//--------------------------------------------------------------------------------
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector connectedSensor:(WFSensorConnection*)connectionInfo
{
    NSLog(@"hardwareConnector:connectedSensor: %@", connectionInfo);
}

//--------------------------------------------------------------------------------
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector didDiscoverDevices:(NSSet*)connectionParams searchCompleted:(BOOL)bCompleted
{
    NSLog(@"hardwareConnector:didDiscoverDevices:searchCompleted: %d \n%@", bCompleted, connectionParams);
}

//--------------------------------------------------------------------------------
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector disconnectedSensor:(WFSensorConnection*)connectionInfo
{
    NSLog(@"hardwareConnector:disconnectedSensor: %@", connectionInfo);
}

//--------------------------------------------------------------------------------
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector stateChanged:(WFHardwareConnectorState_t)currentState
{
    NSLog(@"hardwareConnector:stateChanged: 0x%04X", currentState);
}

//--------------------------------------------------------------------------------
- (void)hardwareConnectorHasData
{
    
}

//--------------------------------------------------------------------------------
- (void) hardwareConnector:(WFHardwareConnector*)hwConnector hasFirmwareUpdateAvailableForConnection:(WFSensorConnection*)connectionInfo
                  required:(BOOL)required
    withWahooUtilityAppURL:(NSURL *)wahooUtilityAppURL
{

}



@end
