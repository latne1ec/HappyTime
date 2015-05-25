//
//  TripTableCell.m
//  WahooDemoV2
//
//  Created by Evan Latner on 5/23/15.
//  Copyright (c) 2015 Wahoo Fitness. All rights reserved.
//

#import "TripTableCell.h"
#import "WFSignalStrengthView.h"
#import "ImageHelper.h"
#import "UIColor+WFHelpers.h"
#import "SensorConnectionHelper.h"

@interface TripTableCell ()

@property (weak, nonatomic) IBOutlet UIImageView *iconImageView;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *manufactureLabel;
@property (weak, nonatomic) IBOutlet UIImageView *networkImageView;
@property (weak, nonatomic) IBOutlet WFSignalStrengthView *signalStrengthView;
@property (weak, nonatomic) IBOutlet UILabel *connectionStatusLabel;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *connectionActivityIndicator;

@property (strong, nonatomic) NSTimer* updateTimer;

@end



@implementation TripTableCell

- (void)awakeFromNib {
    // Initialization code
    
    // Theme the Cell
    self.signalStrengthView.onColor = [UIColor wahooGreenColor];
    self.signalStrengthView.offColor = [UIColor lightGrayColor];
    self.iconImageView.tintColor = [UIColor lightGrayColor];
    
    self.updateTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(updateTimerFired:) userInfo:nil repeats:YES];
    
    
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
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
