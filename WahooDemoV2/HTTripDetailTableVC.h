//
//  TripDetailTableViewController.h
//  HappyTime
//
//  Created by Evan Latner on 5/23/15.
//  Copyright (c) 2015 happytime. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

#import "PNChartDelegate.h"
#import "PNChart.h"
#import "HTTripInfo.h"



@interface HTTripDetailTableVC : UITableViewController <MKMapViewDelegate, PNChartDelegate>

@property (weak, nonatomic) IBOutlet UITableViewCell *cellOne;
@property (weak, nonatomic) IBOutlet UITableViewCell *cellTwo;

@property (weak, nonatomic) IBOutlet UITableViewCell *cellThree;

@property (nonatomic) PNBarChart * barChart;
@property (nonatomic) PNCircleChart * circleChart;

@property (nonatomic) PNPieChart *pieChart;

@property (nonatomic, strong) NSDictionary *tripInfo;

@property (weak, nonatomic) IBOutlet MKMapView *mapview;

@property (weak, nonatomic) IBOutlet UIView *circleView;

@property (weak, nonatomic) IBOutlet UIView *chartView;

@property (nonatomic, strong) HTTripInfo *theTripInfo;



@end
