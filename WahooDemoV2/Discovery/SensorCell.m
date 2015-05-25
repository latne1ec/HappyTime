//
//  SensorCell.m
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "SensorCell.h"
#import "WFSignalStrengthView.h"
#import "ImageHelper.h"
#import "UIColor+WFHelpers.h"
#import "SensorConnectionHelper.h"

@interface SensorCell ()

@property (weak, nonatomic) IBOutlet UIImageView *iconImageView;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *manufactureLabel;
@property (weak, nonatomic) IBOutlet UIImageView *networkImageView;
@property (weak, nonatomic) IBOutlet WFSignalStrengthView *signalStrengthView;
@property (weak, nonatomic) IBOutlet UILabel *connectionStatusLabel;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *connectionActivityIndicator;



@property (strong, nonatomic) NSTimer* updateTimer;

@end


@implementation SensorCell

- (void)awakeFromNib {
    // Initialization code
    
    // Theme the Cell
    self.signalStrengthView.onColor = [UIColor wahooGreenColor];
    self.signalStrengthView.offColor = [UIColor lightGrayColor];
    self.iconImageView.tintColor = [UIColor lightGrayColor];
    
    self.updateTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(updateTimerFired:) userInfo:nil repeats:YES];
}

- (void)dealloc
{
    [_updateTimer invalidate];
}


- (void) updateTimerFired:(NSTimer*) timer
{
    [self updateConnectionUI];
}

- (void)setDeviceInformation:(WFDeviceInformation *)deviceInformation
{
    if(deviceInformation!=_deviceInformation)
    {
        _deviceInformation = deviceInformation;
        [self updateCell];
    }
}

- (void) setSensorConnections:(NSArray *)sensorConnections
{
    _sensorConnections = sensorConnections;
    [self updateConnectionUI];
}


//updates the UI activity indicator and status label
- (void) updateCell
{
    if(self.deviceInformation)
    {
        self.nameLabel.text = self.deviceInformation.name;
        self.manufactureLabel.text = self.deviceInformation.manufacturer;
        
        self.iconImageView.image = [ImageHelper imageForDeviceInformation:self.deviceInformation smallSize:(self.iconImageView.frame.size.height > 50 ? NO : YES)];
        self.networkImageView.image = [ImageHelper imageLogoForNetworkType:self.deviceInformation.networkType];

        
        CALayer *btn1 = [self.startTripButton layer];
        [btn1 setMasksToBounds:YES];
        [btn1 setCornerRadius:3.5f];
        
        
     
        [self updateConnectionUI];
    }
}

- (void) updateConnectionUI
{
    // In order to show the connection status, we need to look at the combined connection status for all sensor connections related to this sensor/device.
    // This is becuase some devices like TICKR X have multiple WFSensorConnections.
    
    if(!self.sensorConnections) {
        self.connectionStatusLabel.text = @"";
        if(self.connectionActivityIndicator.isAnimating) {
            [self.connectionActivityIndicator stopAnimating];
        }
    }
    else
    {
        WFSensorConnectionStatus_t status = [SensorConnectionHelper combindedSensorStatusFromConnections:self.sensorConnections];
        
        // force the device information to be updated.
        self.deviceInformation = [[self.sensorConnections firstObject] deviceInformation];
        
        // Start/Stop the acitivity spinner
        if(status==WF_SENSOR_CONNECTION_STATUS_CONNECTED && self.connectionActivityIndicator.isAnimating) {
            [self.connectionActivityIndicator stopAnimating];
            self.connectionActivityIndicator.hidden = YES;
        } else if(status!=WF_SENSOR_CONNECTION_STATUS_CONNECTED && !self.connectionActivityIndicator.isAnimating){
            [self.connectionActivityIndicator startAnimating];
            self.connectionActivityIndicator.hidden = NO;
        }
        
        switch ( status )
        {
            case WF_SENSOR_CONNECTION_STATUS_CONNECTED:
                self.connectionStatusLabel.text = @"Connected";
                break;
                
            case WF_SENSOR_CONNECTION_STATUS_CONNECTING:
                self.connectionStatusLabel.text = @"Connecting";
                break;
                
            case WF_SENSOR_CONNECTION_STATUS_DISCONNECTING:
                self.connectionStatusLabel.text = @"Disconnecting";
                break;
                
            case WF_SENSOR_CONNECTION_STATUS_INTERRUPTED:
                self.connectionStatusLabel.text = @"Interrupted";
                break;
                
            case WF_SENSOR_CONNECTION_STATUS_IDLE:
            default:
                self.connectionStatusLabel.text = @"Waiting..";
                break;
        }
    }
    
    
    self.signalStrengthView.signalStrength = self.deviceInformation.signalStrength;
}

@end
