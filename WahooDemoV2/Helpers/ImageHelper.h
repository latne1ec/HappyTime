//
//  SensorIcons.h
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WFConnector/WFConnector.h>

@interface ImageHelper : NSObject

+ (UIImage*) imageForProductKey:(NSString*) productKey smallSize:(BOOL) small;

+ (UIImage*) imageForDeviceInformation:(WFDeviceInformation*) deviceInformation smallSize:(BOOL)small;

+ (UIImage*) imageLogoForNetworkType:(WFNetworkType_t) networkType;


@end
