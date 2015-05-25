//
//  SensorIcons.m
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "ImageHelper.h"

@implementation ImageHelper

+ (NSDictionary*) deviceImageLookup
{
    
    return
    @{
      WFProductKeyWahooFitnessBlueHR          : @"WFSilBlueHR",
      WFProductKeyWahooFitnessBlueSC          : @"WFSilBlueSC",
      WFProductKeyWahooFitnessTICKR           : @"WFSilTICKR",
      WFProductKeyWahooFitnessTICKRRun        : @"WFSilTICKR",
      WFProductKeyWahooFitnessTICKRX          : @"WFSilTICKR",
      WFProductKeyWahooFitnessKICKR           : @"WFSilKICKR",
      WFProductKeyWahooFitnessRPM             : @"WFSilRPM",
      WFProductKeyWahooFitnessRFLKT           : @"WFSilRFLKT",
      WFProductKeyWahooFitnessRFLKTPlus       : @"WFSilRFLKT",
      WFProductKeyWahooFitnessCasioSTB1000    : @"WFSilCasioSTB1000",
      WFProductKeyWahooFitnessBalanceScale    : @"WFSilBalance",
      WFProductKeyMagellanEcho                : @"WFSilEcho",
      WFProductKeyMagellanEchoFit             : @"WFSilEcho",
      WFProductKeyStagesPower                 : @"WFSilPowerStages",
      WFProductKeyTimexM054                   : @"WFSilTimex",
      WFProductKeyKineticInRide               : @"",
      WFProductKeyMIOGlobalAlpha              : @"",
      WFProductKeyPolarRUN                    : @"",
      WFProductKeyBeetsBLU                    : @"WFSilBlueHR",
      WFProductKeyCateyeHR                    : @"",
      WFProductKeyCateyeCSC                   : @"",
      WFProductKeyMiCoachHRM                  : @"",
      WFProductKeyPowerBeamProBT              : @"",
      WFProductKeyPowerCalBT                  : @"WFSilPowerHub",
      WFProductKeyPowerTapBT                  : @"WFSilPowerHub",
      WFProductKeyPEARHRM                     : @"WFSilBlueHR",
      WFProductKey4iiiiViiiiva                : @"WFSilBlueHR",
      WFProductKeyScoscheSpeedCadence         : @"",
      WFProductKeyScoscheHRM                  : @"",
      WFProductKeySleepRateHR                 : @"",
      WFProductKeySmartEaseHR                 : @"",
      WFProductKeySpreeFitnessMonitor         : @"",
      WFProductKeyWahooFitnessPROTKT          : @"WFSilPROTKT",
      WFProductKeyWahooFitnessANTKey          : @"WFSilFisicaKey",
      WFProductKeyLookPolarKeoPower           : @"WFSilPowerPedal",
      };
}

+ (NSDictionary*) defaultImages
{
    return @{
             @(WF_SENSORTYPE_HEARTRATE) : @"WFSilGenericHR",
             @(WF_SENSORTYPE_BIKE_POWER) : @"WFSilGenericPower",
             @(WF_SENSORTYPE_BIKE_SPEED_CADENCE) : @"WFSilGenericCadence",
             @(WF_SENSORTYPE_BIKE_SPEED) : @"WFSilGenericSpeed",
             @(WF_SENSORTYPE_BIKE_CADENCE) : @"WFSilGenericCadence",
             @(WF_SENSORTYPE_FOOTPOD) : @"WFSilGenericFootpod",
             };
}


+ (UIImage*) imageForProductKey:(NSString*) productKey smallSize:(BOOL) small
{
    UIImage* retVal = nil;
    
    NSString* imageName = [self deviceImageLookup][productKey];
    if([imageName isEqualToString:@""]) {
        imageName = nil;
    }
    
    if(imageName)
    {
        if(small) imageName = [imageName stringByAppendingString:@"-30"];
        retVal = [[UIImage imageNamed:imageName] imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    }
    
    return retVal;
}


+ (UIImage*) imageForDeviceInformation:(WFDeviceInformation*) deviceInformation smallSize:(BOOL)small
{
    UIImage* retVal = [self imageForProductKey:deviceInformation.productKey smallSize:small];
    
    if(!retVal)
    {
        if(deviceInformation.supportedSensorTypes.count)
        {
            NSNumber* sensorType = [deviceInformation.supportedSensorTypes firstObject];
            NSString* imageName = [self defaultImages][sensorType];
            if(!imageName) imageName = @"WFSilGenericSensor";
            if(small) imageName = [imageName stringByAppendingString:@"-30"];
            retVal = [[UIImage imageNamed:imageName] imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
        }
    }
    
    return retVal;
}


+ (UIImage *)imageLogoForNetworkType:(WFNetworkType_t)networkType
{
    if(networkType == WF_NETWORKTYPE_BTLE) {
        return [UIImage imageNamed:@"WFBtleLogo"];
    } else {
        return [UIImage imageNamed:@"WFANT+.logo.png"];
    }
}

@end
