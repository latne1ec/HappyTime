//
//  ViewController.m
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "MenuTVC.h"
#import <WFConnector/WFConnector.h>

@interface MenuTVC () {
    
    CLLocationManager *locationManager;
    CLGeocoder *geocoder;
    CLPlacemark *placemark;
    
}



@property (weak, nonatomic) IBOutlet UITableViewCell *apiVersionCell;
@end

@implementation MenuTVC

- (void)viewDidLoad {
    [super viewDidLoad];
   
    locationManager = [[CLLocationManager alloc] init];
    geocoder = [[CLGeocoder alloc] init];
    
    
    
    
    CALayer *btn1 = [_syncButton layer];
    [btn1 setMasksToBounds:YES];
    [btn1 setCornerRadius:3.5f];
    
    CALayer *btn2 = [_myTripsButton layer];
    [btn2 setMasksToBounds:YES];
    [btn2 setCornerRadius:3.5f];
    
    
    
    self.apiVersionCell.detailTextLabel.text = [WFHardwareConnector sharedConnector].apiVersion;
}

-(void)viewWillAppear:(BOOL)animated {
    
    [self.navigationController.navigationBar setTranslucent:NO];
    [self getLocation:self];
    
}



- (IBAction)getLocation:(id)sender {
    
    [ProgressHUD show:nil];
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
    
    CLLocation *currentLocation = newLocation;
    
    NSNumber *lat = [NSNumber numberWithDouble:currentLocation.coordinate.latitude];
    NSNumber *lon = [NSNumber numberWithDouble:currentLocation.coordinate.longitude];
    NSDictionary *userLocation=@{@"lat":lat,@"long":lon};
    
    
    [[NSUserDefaults standardUserDefaults] setObject:userLocation forKey:@"userLocation"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    NSLog(@"User Location: %@", currentLocation);
    
    
 
    [locationManager stopUpdatingLocation];
    [self performSelector:@selector(dismissProgressView) withObject:nil afterDelay:0.7];
     
    
    // Reverse Geocoding
    NSLog(@"Resolving the Address");
    
        [geocoder reverseGeocodeLocation:currentLocation completionHandler:^(NSArray *placemarks, NSError *error) {
            NSLog(@"Found placemarks: %@, error: %@", placemarks, error);
            
                       
            if (error == nil && [placemarks count] > 0) {
                placemark = [placemarks lastObject];
                _addressLabel.text = [NSString stringWithFormat:@"%@ %@\n%@ %@, %@",
                                      placemark.subThoroughfare, placemark.thoroughfare,
                                      placemark.postalCode, placemark.locality,
                                      placemark.administrativeArea];
                
                
                
            } else {
                NSLog(@"%@", error.debugDescription);
            }
        } ];

}

-(void)dismissProgressView {
    
    [ProgressHUD dismiss];
    
}


@end
