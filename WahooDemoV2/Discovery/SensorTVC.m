//
//  SensorTVC.m
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "SensorTVC.h"
#import "SensorCell.h"


@interface SensorTVC () {
    
    CLLocationManager *locationManager;
    CLGeocoder *geocoder;
    CLPlacemark *placemark;
    
}

@property (strong, nonatomic) NSDictionary* sensorConnectionLookup;

@property (strong, nonatomic) NSTimer* dataUpdateTimer;

@property (weak, nonatomic) IBOutlet SensorCell *sensorCell;

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


@property (weak, nonatomic) IBOutlet UILabel *bpmLabel;
@property (weak, nonatomic) IBOutlet UIImageView *heartPic;
@property (weak, nonatomic) IBOutlet UIButton *endTripButton;
@property (weak, nonatomic) IBOutlet UILabel *timerLabel;
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;

@property (weak, nonatomic) CLLocation *currentLocation;
@property (weak, nonatomic) CLLocation *oldLocation;


@property (nonatomic, strong) NSDate *timeStamp;
@property (nonatomic, strong) NSNumber *currentBpm;

@property (readwrite) CLLocationDegrees currentLat;
@property (readwrite) CLLocationDegrees currentLon;


@property (nonatomic, strong) NSMutableArray *tripDataArray;
@property (nonatomic, strong) UITextField *tripName;



- (IBAction)cancelTrip:(id)sender;




@end

@implementation SensorTVC

int timeSec = 0;
int timeMin = 0;
NSTimer *timer;
NSTimer *timeStampTimer;


- (void)viewDidLoad {
    [super viewDidLoad];
    self.sensorCell.deviceInformation = self.deviceInformation;
    self.sensorCell.sensorConnections = self.sensorConnectionLookup.allValues;
    self.dataUpdateTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(updateCells) userInfo:nil repeats:YES];
    
    CALayer *btn1 = [self.endTripButton layer];
    [btn1 setMasksToBounds:YES];
    [btn1 setCornerRadius:3.5f];
    
    ////////////Trip timer
    timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(timerTick:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
    
    
    ///////////Time Stamp timer
    timeStampTimer = [NSTimer timerWithTimeInterval:5 target:self selector:@selector(saveTrip) userInfo:nil repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:timeStampTimer forMode:NSDefaultRunLoopMode];
    
    
    self.tripDataArray = [[NSMutableArray alloc] init];
    
    
    locationManager = [[CLLocationManager alloc] init];
    geocoder = [[CLGeocoder alloc] init];
    
    [self getLocation:self];
    [self setupDataCells];
}


-(void)saveTrip {
    
    
    
    _timeStamp = [NSDate date];
    
    if (_currentBpm == nil) {
        
    }
    else {
        
        NSLog(@"Here");
        NSDictionary *tripItemDict = @{
                                       @"time_stamp":_timeStamp,
                                       @"bpm": _currentBpm,
                                       @"latitude":[NSNumber numberWithDouble: _currentLat],
                                       @"longitude":[NSNumber numberWithDouble: _currentLon]
                                       };
        
        if (self.tripDataArray != nil) {
            
            [self.tripDataArray addObject:tripItemDict];
        }
    }
    
}

-(void)viewWillAppear:(BOOL)animated {
    
    [self bounce];
    
    self.navigationItem.hidesBackButton = YES;
    
    
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
                WFHeartrateConnection* connection = self.sensorConnectionLookup[sensorTypeNumber];
                WFHeartrateData* data = [connection getHeartrateData];
                
                self.bpmLabel.text = [data formattedHeartrate:YES] ?: @"0 BPM";
                
                NSString *string = [data formattedHeartrate:NO] ?: @"";
                
                
                
                NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
                f.numberStyle = NSNumberFormatterDecimalStyle;
                NSNumber *myNumber = [f numberFromString:string];
                
                _currentBpm = myNumber;
                
                //NSLog(@"Current Bpm: %@", _currentBpm);
                
                
                
                self.heartrateCell.detailTextLabel.text = [data formattedHeartrate:YES] ?: @"Syncing";
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
        
        if (indexPath.section == 0) {
            
            return 50;
        }
        
        else {
            
            
            return 500;
        }
    }
}

- (IBAction)bounce {
    
    CAAnimationGroup *animationGroup = [CAAnimationGroup animation];
    animationGroup.duration = 1.0;
    animationGroup.repeatCount = 7;
    
    CAMediaTimingFunction *easeOut = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    CABasicAnimation *pulseAnimation = [CABasicAnimation animationWithKeyPath:@"transform"];
    pulseAnimation.toValue = [NSValue valueWithCATransform3D:CATransform3DMakeScale(1.1, 1.1, 1.0)];
    pulseAnimation.duration = .10;
    pulseAnimation.timingFunction = easeOut;
    pulseAnimation.autoreverses = YES;
    animationGroup.animations = @[pulseAnimation];
    [self.heartPic.layer addAnimation:animationGroup forKey:@"animateTranslation"];
    
}

//Event called every time the NSTimer ticks.
- (void)timerTick:(NSTimer *)timer
{
    timeSec++;
    if (timeSec == 60)
    {
        timeSec = 0;
        timeMin++;
    }
    NSString* timeNow = [NSString stringWithFormat:@"Trip Time: %02d:%02d", timeMin, timeSec];
    _timerLabel.text= timeNow;
    
    [self getLocation:self];
    
}

- (void) StopTimer
{
    [timer invalidate];
    timeSec = 0;
    timeMin = 0;
    NSString* timeNow = [NSString stringWithFormat:@"%02d:%02d", timeMin, timeSec];
    _timerLabel.text= timeNow;
}


////////LOCATION

- (IBAction)getLocation:(id)sender {
    
    locationManager.delegate = self;
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    [locationManager startUpdatingLocation];
    [locationManager requestAlwaysAuthorization];
    
}



- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    NSLog(@"didFailWithError: %@", error);
    UIAlertView *errorAlert = [[UIAlertView alloc]
                               initWithTitle:@"Error" message:@"Failed to Get Your Location" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [errorAlert show];
}

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    
    NSDictionary *userLoc = [[NSUserDefaults standardUserDefaults] objectForKey:@"userLocation"];
    NSNumber *lat = (NSNumber *) [userLoc objectForKey:@"lat"];
    NSNumber *lon = (NSNumber *) [userLoc objectForKey:@"long"];
    CLLocation *firstLocation = [[CLLocation alloc] initWithLatitude:[lat doubleValue] longitude:[lon doubleValue]];
    
    CLLocationDistance distance = [newLocation distanceFromLocation:firstLocation];
    CLLocationDistance distanceTwo = distance/1609.34;
    
    self.distanceLabel.text = [NSString stringWithFormat:@"Distance: %f", distanceTwo];
    
    
    
    
    if (newLocation != nil) {
        
        _currentLat = newLocation.coordinate.latitude;
        _currentLon = newLocation.coordinate.longitude;
        
        
    }
    
    
    [locationManager stopUpdatingLocation];
    
}

- (IBAction)endTrip:(id)sender {
    
    [timer invalidate];
    [timeStampTimer invalidate];
    
    [self disconnect];
    
    UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"Trip Name" message:@"Please enter a name for this trip:" delegate:self cancelButtonTitle:@"Continue" otherButtonTitles:nil];
    alert.alertViewStyle = UIAlertViewStylePlainTextInput;
    self.tripName = [alert textFieldAtIndex:0];
    self.tripName.keyboardType = UIKeyboardAppearanceDefault;
    self.tripName.placeholder = @"Enter name";
    
    [alert show];
    
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    
    NSString *buttonTitle=[alertView buttonTitleAtIndex:buttonIndex];
    if([buttonTitle isEqualToString:@"Continue"]) {
        
        
        NSDictionary *trip = [[NSDictionary alloc] init];
        NSDate *currentTime = [NSDate date];
        trip = @{@"trip_name": self.tripName.text,
                 @"trip_data": self.tripDataArray,
                 @"trip_creationTime": currentTime};
        
        NSString *key = [NSString stringWithFormat:@"%@%@%@", @"happy_time", [NSDate date], self.tripName.text];
        [[NSUserDefaults standardUserDefaults] setObject:trip forKey:key];
        [[NSUserDefaults standardUserDefaults] synchronize];
        
        [self StopTimer];
        
        [CATransaction begin];
        [CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];
        CATransition *transition = [CATransition animation];
        [transition setType:kCATransitionFade];
        [self.navigationController.view.layer addAnimation:transition forKey:@"someAnimation"];
        [self.navigationController popToRootViewControllerAnimated:NO];

        [CATransaction commit];
        
    }
}
- (IBAction)cancelTrip:(id)sender {
    
    [timer invalidate];
    [timeStampTimer invalidate];
    [self disconnect];
    [self StopTimer];
    [self.navigationController popToRootViewControllerAnimated:NO];
    
}
@end

