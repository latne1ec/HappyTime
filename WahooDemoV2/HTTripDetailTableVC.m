//
//  TripDetailTableViewController.m
//  HappyTime
//
//  Created by Evan Latner on 5/23/15.
//  Copyright (c) 2015 happytime. All rights reserved.
//

#import "HTTripDetailTableVC.h"


@interface HTTripDetailTableVC () <MKMapViewDelegate>{
    NSString *bpm1;
    NSString *bpm2;
    NSString *bpm3;
    NSString *bpm4;
    NSString *bpm5;
    NSString *bpm6;
    NSMutableArray *gpsLoc1;
    NSMutableArray *gpsLoc2;
    NSMutableArray *gpsLoc3;
    NSMutableArray *gpsLoc4;
    NSMutableArray *gpsLoc5;
    NSMutableArray *gpsLoc6;
}

@property (nonatomic, retain) MKPolyline *routeLine; //your line
@property (nonatomic, retain) MKPolylineView *routeLineView; //overlay view
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (weak, nonatomic) IBOutlet UILabel *timeLabel;
@property (weak, nonatomic) IBOutlet UILabel *tripNameLabel;

@end

@implementation HTTripDetailTableVC

@synthesize cellOne,cellTwo, cellThree;

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.mapview.delegate = self;
    
    [self setupCircles];
    [self setupCircleChart];
    
    _tripNameLabel.text = [NSString stringWithFormat:@"Trip: %@", [_tripInfo objectForKey:@"trip_name"]];
    
    
    
    
    
    
    
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // Return the number of rows in the section.
    return 3;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (indexPath.row == 0) return cellOne;
    if (indexPath.row == 1) return cellTwo;
    if (indexPath.row == 2) return cellThree;
    
    return nil;
}

#pragma mark - User Defined

- (void)setupCircles {
    
    self.circleChart = [[PNCircleChart alloc] initWithFrame:CGRectMake(-100,15.0, SCREEN_WIDTH, 75.0)
                                                      total:@100
                                                    current:@60
                                                  clockwise:YES];
    
    self.circleChart.backgroundColor = [UIColor clearColor];
    
    [self.circleChart setStrokeColor:[UIColor clearColor]];
    [self.circleChart setStrokeColorGradientStart:[UIColor blueColor]];
    [self.circleChart strokeChart];
}

-(void)setupCircleChart {
    
    [self plotMapLine];
    [self analyzeData];
    
    NSArray *items = @[[PNPieChartDataItem dataItemWithValue:10 color:PNStarYellow description:bpm1],
                       [PNPieChartDataItem dataItemWithValue:10 color:PNYellow description:bpm2],
                       [PNPieChartDataItem dataItemWithValue:10 color:PNLightGreen description:bpm3],
                       [PNPieChartDataItem dataItemWithValue:10 color:PNFreshGreen description:bpm4],
                       [PNPieChartDataItem dataItemWithValue:10 color:PNLightBlue description:bpm5],
                       [PNPieChartDataItem dataItemWithValue:10 color:PNBlue description:bpm6]];
    
    self.pieChart = [[PNPieChart alloc] initWithFrame:CGRectMake(SCREEN_WIDTH /2.0 - 100, 10, 200.0, 200.0) items:items];
    self.pieChart.descriptionTextColor = [UIColor whiteColor];
    self.pieChart.descriptionTextFont  = [UIFont fontWithName:@"Avenir-Medium" size:11.0];
    self.pieChart.descriptionTextShadowColor = [UIColor clearColor];
    self.pieChart.showAbsoluteValues = NO;
    self.pieChart.showOnlyValues = NO;
    [self.pieChart strokeChart];
    self.pieChart.legendStyle = PNLegendItemStyleStacked;
    self.pieChart.legendFont = [UIFont boldSystemFontOfSize:12.0f];
    
    UIView *legend = [self.pieChart getLegendWithMaxWidth:200];
    [legend setFrame:CGRectMake(0, 375, legend.frame.size.width, legend.frame.size.height)];
    //[self.view addSubview:legend];
    
    self.pieChart.delegate = self;
    [self.chartView addSubview:self.pieChart];
    //self.changeValueButton.hidden = YES;
    
}

- (void) plotMapLine {
    NSDictionary *tInfo = self.tripInfo;
    NSArray *tripDataItems = [tInfo objectForKey:@"trip_data"];
    
    CLLocationCoordinate2D coordinateArray[tripDataItems.count];
    int i = 0;
    
    for (NSDictionary *dataItem in tripDataItems) {
        NSDate *timeStamp = [dataItem objectForKey:@"time_stamp"];
        int bpm = [[dataItem objectForKey:@"bpm"] intValue];
        double latitude = [[dataItem objectForKey:@"latitude"] doubleValue];
        double longitude = [[dataItem objectForKey:@"longitude"] doubleValue];
        
        //NSLog(@"Data Item: %@ %d %f %f", timeStamp, bpm, latitude, longitude);
        coordinateArray[i++] = CLLocationCoordinate2DMake(latitude, longitude);
    }
    
    self.routeLine = [MKPolyline polylineWithCoordinates:coordinateArray count:tripDataItems.count];
    [self.mapview setVisibleMapRect:[self.routeLine boundingMapRect]]; //If you want the route to be visible
    [self.mapview addOverlay:self.routeLine];
    
    // Get distance
    CLLocation *loc1 = [[CLLocation alloc]initWithLatitude:coordinateArray[0].latitude longitude:coordinateArray[0].longitude];
    CLLocation *loc2 = [[CLLocation alloc]initWithLatitude:coordinateArray[tripDataItems.count-1].latitude longitude:coordinateArray[tripDataItems.count-1].longitude];
    CLLocationDistance dist = [loc1 distanceFromLocation:loc2];
    double distanceMiles = (dist / 1609.344);
    self.distanceLabel.text = [NSString stringWithFormat:@"Distance: %.2f miles", distanceMiles];
    
    // Get time traveled
    NSDictionary *firstTimeStamp = tripDataItems[0];
    NSDictionary *lastTimeStamp = tripDataItems [tripDataItems.count-1];
    
    NSDate *beginningTime = [firstTimeStamp objectForKey:@"time_stamp"];
    NSDate *endingTime = [lastTimeStamp objectForKey:@"time_stamp"];
    
    NSTimeInterval timeDifference = [endingTime timeIntervalSinceDate:beginningTime];
    
    NSLog(@"Total Time: %.2f", timeDifference/3600);
    
    self.timeLabel.text = [NSString stringWithFormat:@"Time: %.2f hours", timeDifference/3600];
}

- (void) analyzeData {
    gpsLoc1 = [NSMutableArray new];
    gpsLoc2 = [NSMutableArray new];
    gpsLoc3 = [NSMutableArray new];
    gpsLoc4 = [NSMutableArray new];
    gpsLoc5 = [NSMutableArray new];
    gpsLoc6 = [NSMutableArray new];
    
    NSDictionary *tInfo = self.tripInfo;
    NSArray *tripDataArray = [tInfo objectForKey:@"trip_data"];
    
    if (tripDataArray.count < 1) {
        NSLog(@"Not enough data - Display error");
    }
    
    NSDictionary *startingData = [tripDataArray objectAtIndex:0];
    NSDictionary *endingData = [tripDataArray objectAtIndex:tripDataArray.count-1];
    
    NSDate *startingTime = [startingData objectForKey:@"time_stamp"];
    NSDate *endingTime = [endingData objectForKey:@"time_stamp"];
    
    NSLog(@"Start Time: %@", startingTime);
    NSLog(@"Ending Time: %@", endingTime);
    
    float tripTotalTime = [endingTime timeIntervalSinceDate:startingTime];
    float tripInterval = tripTotalTime/6;
    NSLog(@"Time Difference: %f", [endingTime timeIntervalSinceDate:startingTime]);
    
    // Time Interval 1:
    NSDate *st = startingTime;
    NSDate *et = [startingTime dateByAddingTimeInterval:tripInterval];
    
    // Add all the bpm's within this interval
    int bpmTotal = 0;
    int bpmCount = 0;
    
    // This could be more efficient...but in the interest of time...
    for (NSDictionary *td in tripDataArray) {
        NSDate *ts = [td objectForKey:@"time_stamp"];
        if (([ts compare:st]==NSOrderedDescending || [ts compare:st]==NSOrderedSame)&&(([ts compare:et]==NSOrderedAscending)||[ts compare:et]==NSOrderedSame)) {
            bpmTotal += [[td objectForKey:@"bpm"]intValue];
            bpmCount++;
            [gpsLoc1 addObject:@{@"latitude":[td objectForKey:@"latitude"], @"longitude":[td objectForKey:@"longitude"]}];
        }
    }
    
    if (bpmCount < 1) {
        NSLog(@"Nothing found ERROR with Range 1");
    } else {
        bpm1 = [NSString stringWithFormat:@"%d BPM", bpmTotal/bpmCount];
        NSLog(@"Range 1 Average st: %@ - et: %@: %@", st, et, bpm1);
    }
    
    
    // Time Interval 2:
    st = et;
    et = [startingTime dateByAddingTimeInterval:tripInterval*2];
    
    // Add all the bpm's within this interval
    bpmTotal = 0;
    bpmCount = 0;
    
    // This could be more efficient...but in the interest of time...
    for (NSDictionary *td in tripDataArray) {
        NSDate *ts = [td objectForKey:@"time_stamp"];
        if (([ts compare:st]==NSOrderedDescending || [ts compare:st]==NSOrderedSame)&&(([ts compare:et]==NSOrderedAscending)||[ts compare:et]==NSOrderedSame)) {
            bpmTotal += [[td objectForKey:@"bpm"]intValue];
            bpmCount++;
            [gpsLoc2 addObject:@{@"latitude":[td objectForKey:@"latitude"], @"longitude":[td objectForKey:@"longitude"]}];
        }
    }
    
    if (bpmCount < 1) {
        NSLog(@"Nothing found ERROR with Range 2");
    } else {
        bpm2 = [NSString stringWithFormat:@"%d BPM", bpmTotal/bpmCount];
        NSLog(@"Range 2 Average st: %@ - et: %@: %@", st, et, bpm2);
    }
    
    // Time Interval 3:
    st = et;
    et = [startingTime dateByAddingTimeInterval:tripInterval*3];
    
    // Add all the bpm's within this interval
    bpmTotal = 0;
    bpmCount = 0;
    
    // This could be more efficient...but in the interest of time...
    for (NSDictionary *td in tripDataArray) {
        NSDate *ts = [td objectForKey:@"time_stamp"];
        if (([ts compare:st]==NSOrderedDescending || [ts compare:st]==NSOrderedSame)&&(([ts compare:et]==NSOrderedAscending)||[ts compare:et]==NSOrderedSame)) {
            bpmTotal += [[td objectForKey:@"bpm"]intValue];
            bpmCount++;
            [gpsLoc3 addObject:@{@"latitude":[td objectForKey:@"latitude"], @"longitude":[td objectForKey:@"longitude"]}];
        }
    }
    
    if (bpmCount < 1) {
        NSLog(@"Nothing found ERROR with Range 3");
    } else {
        bpm3 = [NSString stringWithFormat:@"%d BPM", bpmTotal/bpmCount];
        NSLog(@"Range 3 Average st: %@ - et: %@: %@", st, et, bpm3);
    }
    
    // Time Interval 4:
    st = et;
    et = [startingTime dateByAddingTimeInterval:tripInterval*4];
    
    // Add all the bpm's within this interval
    bpmTotal = 0;
    bpmCount = 0;
    
    // This could be more efficient...but in the interest of time...
    for (NSDictionary *td in tripDataArray) {
        NSDate *ts = [td objectForKey:@"time_stamp"];
        if (([ts compare:st]==NSOrderedDescending || [ts compare:st]==NSOrderedSame)&&(([ts compare:et]==NSOrderedAscending)||[ts compare:et]==NSOrderedSame)) {
            bpmTotal += [[td objectForKey:@"bpm"]intValue];
            bpmCount++;
            [gpsLoc4 addObject:@{@"latitude":[td objectForKey:@"latitude"], @"longitude":[td objectForKey:@"longitude"]}];
        }
    }
    
    if (bpmCount < 1) {
        NSLog(@"Nothing found ERROR with Range 4");
    } else {
        bpm4 = [NSString stringWithFormat:@"%d BPM", bpmTotal/bpmCount];
        NSLog(@"Range 4 Average st: %@ - et: %@: %@", st, et, bpm4);
    }
    
    
    // Time Interval 5:
    st = et;
    et = [startingTime dateByAddingTimeInterval:tripInterval*5];
    
    // Add all the bpm's within this interval
    bpmTotal = 0;
    bpmCount = 0;
    
    // This could be more efficient...but in the interest of time...
    for (NSDictionary *td in tripDataArray) {
        NSDate *ts = [td objectForKey:@"time_stamp"];
        if (([ts compare:st]==NSOrderedDescending || [ts compare:st]==NSOrderedSame)&&(([ts compare:et]==NSOrderedAscending)||[ts compare:et]==NSOrderedSame)) {
            bpmTotal += [[td objectForKey:@"bpm"]intValue];
            bpmCount++;
            [gpsLoc5 addObject:@{@"latitude":[td objectForKey:@"latitude"], @"longitude":[td objectForKey:@"longitude"]}];
        }
    }
    
    if (bpmCount < 1) {
        NSLog(@"Nothing found ERROR with Range 5");
    } else {
        bpm5 = [NSString stringWithFormat:@"%d BPM", bpmTotal/bpmCount];
        NSLog(@"Range 5 Average st: %@ - et: %@: %@", st, et, bpm5);
    }
    
    // Time Interval 6:
    st = et;
    et = [startingTime dateByAddingTimeInterval:tripInterval*6];
    
    // Add all the bpm's within this interval
    bpmTotal = 0;
    bpmCount = 0;
    
    // This could be more efficient...but in the interest of time...
    for (NSDictionary *td in tripDataArray) {
        NSDate *ts = [td objectForKey:@"time_stamp"];
        if (([ts compare:st]==NSOrderedDescending || [ts compare:st]==NSOrderedSame)&&(([ts compare:et]==NSOrderedAscending)||[ts compare:et]==NSOrderedSame)) {
            bpmTotal += [[td objectForKey:@"bpm"]intValue];
            bpmCount++;
            [gpsLoc6 addObject:@{@"latitude":[td objectForKey:@"latitude"], @"longitude":[td objectForKey:@"longitude"]}];
        }
    }
    
    if (bpmCount < 1) {
        NSLog(@"Nothing found ERROR with Range 6");
    } else {
        bpm6 = [NSString stringWithFormat:@"%d BPM", bpmTotal/bpmCount];
        NSLog(@"Range 6 Average st: %@ - et: %@: %@", st, et, bpm6);
    }
}

-(void)userClickedOnPieIndexItem:(NSInteger)pieIndex {
    
    NSLog(@"Click on pie %@", @(pieIndex));
    
    if (pieIndex == 0) {
        
        int i = 0;
        CLLocationCoordinate2D coordinateArray[gpsLoc1.count];
        for (NSDictionary *coords in gpsLoc1) {
            coordinateArray[i++].latitude = [[coords objectForKey:@"latitude"] doubleValue];
            coordinateArray[i++].longitude = [[coords objectForKey:@"longitude"] doubleValue];
            NSLog(@"latitude: %f", [[coords objectForKey:@"latitude"] doubleValue]);
            NSLog(@"longitude: %f", [[coords objectForKey:@"longitude"] doubleValue]);
            
        }
        
        self.routeLine = [MKPolyline polylineWithCoordinates:coordinateArray count:gpsLoc1.count];
        [self.mapview setVisibleMapRect:[self.routeLine boundingMapRect]]; //If you want the route to be visible
        
        [self.mapview addOverlay:self.routeLine];
    }
    
    if (pieIndex == 1) {
        
        int i = 0;
        CLLocationCoordinate2D coordinateArray[gpsLoc2.count];
        for (NSDictionary *coords in gpsLoc2) {
            coordinateArray[i++].latitude = [[coords objectForKey:@"latitude"] doubleValue];
            coordinateArray[i++].longitude = [[coords objectForKey:@"longitude"] doubleValue];
            NSLog(@"latitude: %f", [[coords objectForKey:@"latitude"] doubleValue]);
            NSLog(@"longitude: %f", [[coords objectForKey:@"longitude"] doubleValue]);
            
        }
        
        self.routeLine = [MKPolyline polylineWithCoordinates:coordinateArray count:gpsLoc2.count];
        [self.mapview setVisibleMapRect:[self.routeLine boundingMapRect]]; //If you want the route to be visible
        
        [self.mapview addOverlay:self.routeLine];
    }
    
    if (pieIndex == 2) {
        
        int i = 0;
        CLLocationCoordinate2D coordinateArray[gpsLoc3.count];
        for (NSDictionary *coords in gpsLoc3) {
            coordinateArray[i++].latitude = [[coords objectForKey:@"latitude"] doubleValue];
            coordinateArray[i++].longitude = [[coords objectForKey:@"longitude"] doubleValue];
            NSLog(@"latitude: %f", [[coords objectForKey:@"latitude"] doubleValue]);
            NSLog(@"longitude: %f", [[coords objectForKey:@"longitude"] doubleValue]);
            
        }
        
        self.routeLine = [MKPolyline polylineWithCoordinates:coordinateArray count:gpsLoc3.count];
        [self.mapview setVisibleMapRect:[self.routeLine boundingMapRect]]; //If you want the route to be visible
        
        [self.mapview addOverlay:self.routeLine];
    }
    
    if (pieIndex == 3) {
        
        int i = 0;
        CLLocationCoordinate2D coordinateArray[gpsLoc4.count];
        for (NSDictionary *coords in gpsLoc4) {
            coordinateArray[i++].latitude = [[coords objectForKey:@"latitude"] doubleValue];
            coordinateArray[i++].longitude = [[coords objectForKey:@"longitude"] doubleValue];
            NSLog(@"latitude: %f", [[coords objectForKey:@"latitude"] doubleValue]);
            NSLog(@"longitude: %f", [[coords objectForKey:@"longitude"] doubleValue]);
            
        }
        
        self.routeLine = [MKPolyline polylineWithCoordinates:coordinateArray count:gpsLoc4.count];
        [self.mapview setVisibleMapRect:[self.routeLine boundingMapRect]]; //If you want the route to be visible
        
        [self.mapview addOverlay:self.routeLine];
    }
    
    if (pieIndex == 4) {
        
        int i = 0;
        CLLocationCoordinate2D coordinateArray[gpsLoc5.count];
        for (NSDictionary *coords in gpsLoc5) {
            coordinateArray[i++].latitude = [[coords objectForKey:@"latitude"] doubleValue];
            coordinateArray[i++].longitude = [[coords objectForKey:@"longitude"] doubleValue];
            NSLog(@"latitude: %f", [[coords objectForKey:@"latitude"] doubleValue]);
            NSLog(@"longitude: %f", [[coords objectForKey:@"longitude"] doubleValue]);
            
        }
        
        self.routeLine = [MKPolyline polylineWithCoordinates:coordinateArray count:gpsLoc5.count];
        [self.mapview setVisibleMapRect:[self.routeLine boundingMapRect]]; //If you want the route to be visible
        
        [self.mapview addOverlay:self.routeLine];
    }
    
    if (pieIndex == 5) {
        
        int i = 0;
        CLLocationCoordinate2D coordinateArray[gpsLoc6.count];
        for (NSDictionary *coords in gpsLoc6) {
            coordinateArray[i++].latitude = [[coords objectForKey:@"latitude"] doubleValue];
            coordinateArray[i++].longitude = [[coords objectForKey:@"longitude"] doubleValue];
            NSLog(@"latitude: %f", [[coords objectForKey:@"latitude"] doubleValue]);
            NSLog(@"longitude: %f", [[coords objectForKey:@"longitude"] doubleValue]);
            
        }
        
        self.routeLine = [MKPolyline polylineWithCoordinates:coordinateArray count:gpsLoc6.count];
        [self.mapview setVisibleMapRect:[self.routeLine boundingMapRect]]; //If you want the route to be visible
        
        [self.mapview addOverlay:self.routeLine];
    }
}

- (void)userClickedOnBarAtIndex:(NSInteger)barIndex {
    
    NSLog(@"Click on bar %@", @(barIndex));
    
    PNBar * bar = [self.barChart.bars objectAtIndex:barIndex];
    CABasicAnimation *anim = [CABasicAnimation animationWithKeyPath:@"transform"];
    anim.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    anim.duration = 0.105;
    anim.repeatCount = 1;
    anim.autoreverses = YES;
    anim.removedOnCompletion = YES;
    anim.toValue = [NSValue valueWithCATransform3D:CATransform3DMakeScale(1.15, 1.15, 1.0)];
    [bar.layer addAnimation:anim forKey:nil];
}

-(MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id<MKOverlay>)overlay
{
    if(overlay == self.routeLine)
    {
        if(nil == self.routeLineView)
        {
            self.routeLineView = [[MKPolylineView alloc] initWithPolyline:self.routeLine];
            self.routeLineView.fillColor = [UIColor redColor];
            self.routeLineView.strokeColor = [UIColor redColor];
            self.routeLineView.lineWidth = 5;
            
        }
        
        return self.routeLineView;
    }
    
    return nil;
}
@end
