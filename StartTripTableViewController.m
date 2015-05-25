//
//  StartTripTableViewController.m
//  WahooDemoV2
//
//  Created by Evan Latner on 5/23/15.
//  Copyright (c) 2015 Wahoo Fitness. All rights reserved.
//

#import "StartTripTableViewController.h"
#import "TripTableCell.h"


@interface StartTripTableViewController ()


@property (strong, nonatomic) NSDictionary* sensorConnectionLookup;

@property (strong, nonatomic) NSTimer* dataUpdateTimer;

@property (weak, nonatomic) IBOutlet TripTableCell *sensorCell;

@property (strong, nonatomic) IBOutletCollection(UITableViewCell) NSArray *dataCells;
@property (weak, nonatomic) IBOutlet UITableViewCell *heartrateCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *speedDistanceCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *cadenceCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *strideRateCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *powerCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *altitudeCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *temperatureCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *motionAnalysisCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *weightCell;

@end

@implementation StartTripTableViewController




- (void)viewDidLoad {
    [super viewDidLoad];
    self.sensorCell.deviceInformation = self.deviceInformation;
    self.sensorCell.sensorConnections = self.sensorConnectionLookup.allValues;
    self.dataUpdateTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(updateCells) userInfo:nil repeats:YES];
    
    [self setupDataCells];
}

- (void) viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self disconnect];
}


- (void)setDeviceInformation:(WFDeviceInformation *)deviceInformation
{
    _deviceInformation = deviceInformation;
    [self connect];
    self.sensorCell.deviceInformation = deviceInformation;
    self.sensorCell.sensorConnections = self.sensorConnectionLookup.allValues;
    
}


- (void) setupDataCells
{
    // Hide all by default
    for (UITableViewCell* cell in self.dataCells) {
        cell.hidden = YES;
    }
    
    for (NSNumber* sensorTypeNumber in self.deviceInformation.supportedSensorTypes) {
        WFSensorType_t sensorType = (WFSensorType_t)[sensorTypeNumber integerValue];
        
        switch (sensorType) {
            case WF_SENSORTYPE_BIKE_POWER:
                self.powerCell.hidden = NO;
                self.speedDistanceCell.hidden = NO;
                self.cadenceCell.hidden = NO;
                break;
            case WF_SENSORTYPE_BIKE_SPEED:
                self.speedDistanceCell.hidden = NO;
                break;
            case WF_SENSORTYPE_BIKE_CADENCE:
                self.cadenceCell.hidden = NO;
                break;
            case WF_SENSORTYPE_BIKE_SPEED_CADENCE:
                self.speedDistanceCell.hidden = NO;
                self.cadenceCell.hidden = NO;
                break;
            case WF_SENSORTYPE_FOOTPOD:
                self.speedDistanceCell.hidden = NO;
                self.strideRateCell.hidden = NO;
                break;
            case WF_SENSORTYPE_HEARTRATE:
                self.heartrateCell.hidden = NO;
                break;
            case WF_SENSORTYPE_WEIGHT_SCALE:
                self.weightCell.hidden = NO;
                break;
            case WF_SENSORTYPE_DISPLAY:
                
                if([self.deviceInformation.productKey isEqualToString:WFProductKeyWahooFitnessRFLKTPlus]) {
                    self.altitudeCell.hidden = NO;
                    self.temperatureCell.hidden = NO;
                }
                
                break;
                
            default:
                break;
        }
    }
    
    self.heartrateCell.detailTextLabel.text = @"--";
    self.speedDistanceCell.detailTextLabel.text = @"--";
    self.cadenceCell.detailTextLabel.text = @"--";
    self.strideRateCell.detailTextLabel.text = @"--";
    self.powerCell.detailTextLabel.text = @"--";
    self.altitudeCell.detailTextLabel.text = @"--";
    self.temperatureCell.detailTextLabel.text = @"--";
    self.motionAnalysisCell.detailTextLabel.text = @"--";
    self.weightCell.detailTextLabel.text = @"--";
}

- (void) updateCells
{
    
    for (NSNumber* sensorTypeNumber in self.deviceInformation.supportedSensorTypes) {
        WFSensorType_t sensorType = (WFSensorType_t)[sensorTypeNumber integerValue];
        
        switch (sensorType) {
                
                
                //---------------------------------------------------------------------------------------
                //---- Bike Speed and/or Cadence
                //---- Including KICKR, inRide and other power meters
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_BIKE_POWER:
            {
                WFBikePowerConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFBikePowerData* data = [connection getBikePowerData];
                self.powerCell.detailTextLabel.text = [data formattedPower:YES] ?: @"N/A";
                self.speedDistanceCell.detailTextLabel.text = [data formattedSpeed:YES] ?: @"N/A";
                self.cadenceCell.detailTextLabel.text = [data formattedCadence:YES] ?: @"N/A";
                break;
            }
                
                //---------------------------------------------------------------------------------------
                //---- Bike Speed and/or Cadence
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_BIKE_SPEED_CADENCE:
            {
                WFBikeSpeedCadenceConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFBikeSpeedCadenceData* data = [connection getBikeSpeedCadenceData];
                self.cadenceCell.detailTextLabel.text = [data formattedCadence:YES] ?: @"N/A";
                self.speedDistanceCell.detailTextLabel.text = [data formattedSpeed:YES] ?: @"N/A";
                break;
            }
                
                
                //---------------------------------------------------------------------------------------
                //---- Foodpods / Running Speed & Cadence sensors
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_FOOTPOD:
            {
                WFFootpodConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFFootpodData* data = [connection getFootpodData];
                self.strideRateCell.detailTextLabel.text = [data formattedCadence:YES] ?: @"N/A";
                self.speedDistanceCell.detailTextLabel.text = [data formattedSpeed:YES] ?: @"N/A";
                break;
            }
                
                //---------------------------------------------------------------------------------------
                //---- Heartrate
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_HEARTRATE:
            {
                NSLog(@"Called hereeee");
                WFHeartrateConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFHeartrateData* data = [connection getHeartrateData];
                self.heartrateCell.detailTextLabel.text = [data formattedHeartrate:YES] ?: @"N/A";
                break;
                
                
            }
                
                //---------------------------------------------------------------------------------------
                //---- Weight Scale
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_WEIGHT_SCALE:
            {
                WFWeightScaleConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFWeightScaleData* data = [connection getWeightScaleData];
                self.weightCell.detailTextLabel.text = [data formattedWeight:YES] ?: @"N/A";
                break;
            }
                
                //---------------------------------------------------------------------------------------
                //---- Display / RFLKT / Echo / Timex
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_DISPLAY:
            {
                WFDisplayConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFDisplayData* data = [connection getDisplayData];
                self.temperatureCell.detailTextLabel.text = [NSString stringWithFormat:@"%f",data.temperature];
                self.altitudeCell.detailTextLabel.text = [NSString stringWithFormat:@"%f",data.elevation];
                break;
            }
                
                //---------------------------------------------------------------------------------------
                //---- ANT+ Speed Only
                //---- All BTLE Speed and/or Cadence sensors use the Bike Speed and Cadence Profile
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_BIKE_SPEED:
            {
                WFBikeSpeedConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFBikeSpeedData* data = [connection getBikeSpeedData];
                self.speedDistanceCell.detailTextLabel.text = [data formattedSpeed:YES] ?: @"N/A";
                break;
            }
                
                //---------------------------------------------------------------------------------------
                //---- ANT+ Cadence Only
                //---- All BTLE Speed and/or Cadence sensors use the Bike Speed and Cadence Profile
                //---------------------------------------------------------------------------------------
            case WF_SENSORTYPE_BIKE_CADENCE:
            {
                WFBikeCadenceConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFBikeCadenceData* data = [connection getBikeCadenceData];
                self.cadenceCell.detailTextLabel.text = [data formattedCadence:YES] ?: @"N/A";
                break;
            }
                
            default:
                break;
                
        }
    }
    
    
    
}

- (void) connect
{
    NSLog(@"WFSensorTVC::connect");
    
    NSArray* connectionParams = [self.deviceInformation connecitonParamsForAllSupportSensorTypes];
    NSMutableDictionary* connectionLookup = [NSMutableDictionary new];
    
    for (WFConnectionParams* params in connectionParams) {
        
        NSError* error = nil;
        
        WFSensorConnection* sensorConnection = [[WFHardwareConnector sharedConnector] requestSensorConnection:params withProximity:WF_PROXIMITY_RANGE_DISABLED error:&error];
        
        if(error)
        {
            NSLog(@"ERROR: Failed to create sensor connection! \n%@", error);
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [self connect];
            });
        }
        else
        {
            [connectionLookup setObject:sensorConnection forKey:@(params.sensorType)];
        }
        
    }
    
    
    self.sensorConnectionLookup = connectionLookup;
    self.sensorCell.sensorConnections = self.sensorConnectionLookup.allValues;
}

- (void) disconnect
{
    [self.sensorConnectionLookup.allValues makeObjectsPerformSelector:@selector(disconnect)];
}



/// Bit of a hack to hide table view cells when using a static table view controller :-)
- (CGFloat) tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell* cell = [self tableView:tableView cellForRowAtIndexPath:indexPath];
    if(cell.hidden)
    {
        return 0;
    }
    else
    {
        return cell.frame.size.height;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
