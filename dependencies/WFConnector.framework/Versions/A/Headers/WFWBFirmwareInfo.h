//
//  WFWBFirmwareInfo.h
//  WFConnector
//
//  Created by Michael Moore on 8/10/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/hardware_connector_types.h>

typedef struct
{
    USHORT usProductId;
	UCHAR  ucVendorId;
    UCHAR  ucHardwareVersion;
    USHORT usModelNumber;
    USHORT usDeviceCapabilities;
	ULONG  ulBootloaderVersion;
    UCHAR  ucWahooBluePlatform;
    
} WFWBDeviceInfo_t;


@interface WFWBFirmwareInfo : NSObject
{
    UCHAR ucVendor;
    UCHAR ucMajor;
    UCHAR ucMinor;
    UCHAR ucBuild;
    char chFormat;
}


@property (nonatomic, assign) UCHAR ucVendor;
@property (nonatomic, assign) UCHAR ucMajor;
@property (nonatomic, assign) UCHAR ucMinor;
@property (nonatomic, assign) UCHAR ucBuild;
@property (nonatomic, readonly) NSString* versionString;


- (id)initWithFormat:(char)chFormat_;

@end
