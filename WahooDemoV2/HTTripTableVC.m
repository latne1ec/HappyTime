//
//  HTTripTableVC.m
//  HappyTime
//
//  Created by Mervyn Sharaf on 5/23/15.
//  Copyright (c) 2015 happytime. All rights reserved.
//

#import "HTTripTableVC.h"
#import "HTTripDetailTableVC.h"
#import "HTTripInfo.h"
#import "HTTripData.h"
#import "DateTools.h"

@interface HTTripTableVC () {
    
    NSMutableArray *tripList;
}

@end

@implementation HTTripTableVC

- (void)viewDidLoad {
    [super viewDidLoad];
//    [self createSampleData];
    
    [self getTripData];
    
    self.title = @"My trips";
    
    self.tableView.tableFooterView = [UIView new];
}

-(void)viewWillAppear:(BOOL)animated {
    
    NSIndexPath *tableSelection = [self.tableView indexPathForSelectedRow];
    [self.tableView deselectRowAtIndexPath:tableSelection animated:NO];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    
    if ([[segue identifier] isEqualToString:@"SegueToTripDetailView"]) {
        HTTripDetailTableVC *dtvc = (HTTripDetailTableVC *)[segue destinationViewController];
        dtvc.tripInfo = sender;
    }
}


#pragma mark - User defined

- (void) getTripData {
    tripList = [NSMutableArray new];
    
    NSArray *allKeys = [[[NSUserDefaults standardUserDefaults] dictionaryRepresentation] allKeys];
    for (NSString *key in allKeys) {
        if ([key hasPrefix:@"happy_time"]) {
            NSLog(@"Key: %@", key);
            [self getDataForKey:key];
        }
    }
    
}

- (void) getDataForKey: (NSString *)key {
    
    NSDictionary *tripDict = [[NSUserDefaults standardUserDefaults]objectForKey:key];
    [tripList addObject:tripDict];
}


#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return tripList.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *cellIdentifier = @"Cell";
    
    HTTripTableCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier forIndexPath:indexPath];

    if (cell == nil) {
        cell = [[HTTripTableCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    
    NSDictionary *tripDict = [tripList objectAtIndex:indexPath.row];
    
    cell.tripImage.image = [UIImage imageNamed:@"blurPix"];
    cell.tripImage.layer.cornerRadius = 4;
    cell.tripImage.clipsToBounds = YES;
    
    cell.tripNameLabel.text = [tripDict objectForKey:@"trip_name"];
    
    NSDate *date = [tripDict objectForKey:@"trip_creationTime"];
    
    
    NSString *ago = [date timeAgoSinceNow];
    

    cell.tripTimeLabel.text = ago;
    
    return cell;
    
    
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    [self performSegueWithIdentifier:@"SegueToTripDetailView" sender:[tripList objectAtIndex:indexPath.row]];

}


/*
 // Override to support conditional editing of the table view.
 - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the specified item to be editable.
 return YES;
 }
 */

/*
 // Override to support editing the table view.
 - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
 if (editingStyle == UITableViewCellEditingStyleDelete) {
 // Delete the row from the data source
 [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
 } else if (editingStyle == UITableViewCellEditingStyleInsert) {
 // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
 }
 }
 */

/*
 // Override to support rearranging the table view.
 - (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
 }
 */

/*
 // Override to support conditional rearranging of the table view.
 - (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the item to be re-orderable.
 return YES;
 }
 */

/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

//- (void)createSampleData {
//    // Init Trip list Array
//    tripList = [NSMutableArray new];
//    // Data
//    NSMutableArray *tripDataArray = [NSMutableArray new];
//    HTTripInfo *trip = [[HTTripInfo alloc]init];
//    HTTripData *dataItem1 = [[HTTripData alloc]init];
//    HTTripData *dataItem2 = [[HTTripData alloc]init];
//    HTTripData *dataItem3 = [[HTTripData alloc]init];
//    HTTripData *dataItem4 = [[HTTripData alloc]init];
//    HTTripData *dataItem5 = [[HTTripData alloc]init];
//    HTTripData *dataItem6 = [[HTTripData alloc]init];
//    HTTripData *dataItem7 = [[HTTripData alloc]init];
//    HTTripData *dataItem8 = [[HTTripData alloc]init];
//    HTTripData *dataItem9 = [[HTTripData alloc]init];
//    HTTripData *dataItem10 = [[HTTripData alloc]init];
//
//
//    NSDate *currentTime;
//    NSDate *oldTime = [NSDate date];
//
//    // Create Trip
//    // Info
//    trip = [[HTTripInfo alloc]init];
//    trip.tripName = @"Drive in the Country";
//    trip.tripDescription = @"My Monday Trip";
//    oldTime = [oldTime dateByAddingTimeInterval:60.0*60.0*60.0];
//
//    // Data
//    tripDataArray = [NSMutableArray new];
//
//    dataItem1 = [[HTTripData alloc]init];
//    dataItem1.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//    dataItem1.bpm = 72;
//    dataItem1.latitude = 37.667660;
//    dataItem1.longitude = -122.081981;
//    [tripDataArray addObject:dataItem1];
//
//    dataItem2 = [[HTTripData alloc]init];
//    dataItem2.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//    dataItem2.bpm = 73;
//    dataItem2.latitude = 37.662226;
//    dataItem2.longitude = -122.084635;
//    [tripDataArray addObject:dataItem2];
//
//    dataItem3 = [[HTTripData alloc]init];
//    dataItem3.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//    dataItem3.bpm = 74;
//    dataItem3.latitude = 37.656624;
//    dataItem3.longitude = -122.087551;
//    [tripDataArray addObject:dataItem3];
//
//    dataItem4 = [[HTTripData alloc]init];
//    dataItem4.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//    dataItem4.bpm = 75;
//    dataItem4.latitude = 37.650276;
//    dataItem4.longitude = -122.090569;
//    [tripDataArray addObject:dataItem4];
//
//    dataItem5 = [[HTTripData alloc]init];
//    dataItem5.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem5.bpm = 76;
//    dataItem5.latitude = 37.642641;
//    dataItem5.longitude = -122.094002;
//    [tripDataArray addObject:dataItem5];
//
//    trip.data = tripDataArray;
//
//    [tripList addObject:trip];
//
//    [self persistATrip:trip];
//
//    /*********************************************************/
//
//    // Create Trip
//    // Info
//    trip = [[HTTripInfo alloc]init];
//    trip.tripName = @"Groceries";
//    trip.tripDescription = @"My Monday Trip";
//    oldTime = [oldTime dateByAddingTimeInterval:60.0*60.0*60.0];
//    tripDataArray = [NSMutableArray new];
//
//    dataItem1 = [[HTTripData alloc]init];
//    dataItem1.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem1.bpm = 72;
//    dataItem1.latitude = -37.759600;
//    dataItem1.longitude = -122.43095;
//    [tripDataArray addObject:dataItem1];
//
//    dataItem2 = [[HTTripData alloc]init];
//    dataItem2.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem2.bpm = 72;
//    dataItem2.latitude = -37.759600;
//    dataItem2.longitude = -122.43095;
//    [tripDataArray addObject:dataItem2];
//
//    dataItem3 = [[HTTripData alloc]init];
//    dataItem3.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem3.bpm = 72;
//    dataItem3.latitude = -37.759600;
//    dataItem3.longitude = -122.43095;
//    [tripDataArray addObject:dataItem3];
//
//    dataItem4 = [[HTTripData alloc]init];
//    dataItem4.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem4.bpm = 72;
//    dataItem4.latitude = -37.759600;
//    dataItem4.longitude = -122.43095;
//    [tripDataArray addObject:dataItem4];
//
//    dataItem5 = [[HTTripData alloc]init];
//    dataItem5.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem5.bpm = 72;
//    dataItem5.latitude = -37.759600;
//    dataItem5.longitude = -122.43095;
//    [tripDataArray addObject:dataItem5];
//
//    trip.data = tripDataArray;
//
//
//
//    [tripList addObject:trip];
//
//    [self persistATrip:trip];
//
//    /*********************************************************/
//
//    // Create Trip
//    // Info
//    trip = [[HTTripInfo alloc]init];
//    trip.tripName = @"Trip to ex-girlfriends to get my stuff.";
//    trip.tripDescription = @"My Monday Trip";
//    oldTime = [oldTime dateByAddingTimeInterval:60.0*60.0*60.0];
//    tripDataArray = [NSMutableArray new];
//
//    dataItem1 = [[HTTripData alloc]init];
//    dataItem1.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem1.bpm = 72;
//    dataItem1.latitude = -37.759600;
//    dataItem1.longitude = -122.43095;
//    [tripDataArray addObject:dataItem1];
//
//    dataItem2 = [[HTTripData alloc]init];
//    dataItem2.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem2.bpm = 72;
//    dataItem2.latitude = -37.759600;
//    dataItem2.longitude = -122.43095;
//    [tripDataArray addObject:dataItem2];
//
//    dataItem3 = [[HTTripData alloc]init];
//    dataItem3.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem3.bpm = 72;
//    dataItem3.latitude = -37.759600;
//    dataItem3.longitude = -122.43095;
//    [tripDataArray addObject:dataItem3];
//
//    dataItem4 = [[HTTripData alloc]init];
//    dataItem4.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem4.bpm = 72;
//    dataItem4.latitude = -37.759600;
//    dataItem4.longitude = -122.43095;
//    [tripDataArray addObject:dataItem4];
//
//    dataItem5 = [[HTTripData alloc]init];
//    dataItem5.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem5.bpm = 72;
//    dataItem5.latitude = -37.759600;
//    dataItem5.longitude = -122.43095;
//    [tripDataArray addObject:dataItem5];
//
//    trip.data = tripDataArray;
//
//    [tripList addObject:trip];
//
//    [self persistATrip:trip];
//
//    /*********************************************************/
//
//    // Create Trip
//    // Info
//    trip = [[HTTripInfo alloc]init];
//    trip.tripName = @"Trip to new girlfriend's house";
//    trip.tripDescription = @"My Monday Trip";
//    oldTime = [oldTime dateByAddingTimeInterval:60.0*60.0*60.0];
//    tripDataArray = [NSMutableArray new];
//
//    dataItem1 = [[HTTripData alloc]init];
//    dataItem1.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem1.bpm = 72;
//    dataItem1.latitude = -37.759600;
//    dataItem1.longitude = -122.43095;
//    [tripDataArray addObject:dataItem1];
//
//    dataItem2 = [[HTTripData alloc]init];
//    dataItem2.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem2.bpm = 72;
//    dataItem2.latitude = -37.759600;
//    dataItem2.longitude = -122.43095;
//    [tripDataArray addObject:dataItem2];
//
//    dataItem3 = [[HTTripData alloc]init];
//    dataItem3.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem3.bpm = 72;
//    dataItem3.latitude = -37.759600;
//    dataItem3.longitude = -122.43095;
//    [tripDataArray addObject:dataItem3];
//
//    dataItem4 = [[HTTripData alloc]init];
//    dataItem4.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem4.bpm = 72;
//    dataItem4.latitude = -37.759600;
//    dataItem4.longitude = -122.43095;
//    [tripDataArray addObject:dataItem4];
//
//    dataItem5 = [[HTTripData alloc]init];
//    dataItem5.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//    NSDictionary *trip = @{@"
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem5.bpm = 72;
//    dataItem5.latitude = -37.759600;
//    dataItem5.longitude = -122.43095;
//    [tripDataArray addObject:dataItem5];
//
//    trip.data = tripDataArray;
//
//    [tripList addObject:trip];
//
//    [self persistATrip:trip];
//
//    /*********************************************************/
//
//    // Create Trip
//    // Info
//    trip = [[HTTripInfo alloc]init];
//    trip.tripName = @"Trip to parents.";
//    trip.tripDescription = @"My Monday Trip";
//    oldTime = [oldTime dateByAddingTimeInterval:60.0*60.0*60.0];
//    tripDataArray = [NSMutableArray new];
//
//    dataItem1 = [[HTTripData alloc]init];
//    dataItem1.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem1.bpm = 72;
//    dataItem1.latitude = -37.759600;
//    dataItem1.longitude = -122.43095;
//    [tripDataArray addObject:dataItem1];
//
//    dataItem2 = [[HTTripData alloc]init];
//    dataItem2.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem2.bpm = 72;
//    dataItem2.latitude = -37.759600;
//    dataItem2.longitude = -122.43095;
//    [tripDataArray addObject:dataItem2];
//
//    dataItem3 = [[HTTripData alloc]init];
//    dataItem3.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem3.bpm = 72;
//    dataItem3.latitude = -37.759600;
//    dataItem3.longitude = -122.43095;
//    [tripDataArray addObject:dataItem3];
//
//    dataItem4 = [[HTTripData alloc]init];
//    dataItem4.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem4.bpm = 72;
//    dataItem4.latitude = -37.759600;
//    dataItem4.longitude = -122.43095;
//    [tripDataArray addObject:dataItem4];
//
//    dataItem5 = [[HTTripData alloc]init];
//    dataItem5.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem5.bpm = 72;
//    dataItem5.latitude = -37.759600;
//    dataItem5.longitude = -122.43095;
//    [tripDataArray addObject:dataItem5];
//
//    trip.data = tripDataArray;
//
//    [tripList addObject:trip];
//
//    [self persistATrip:trip];
//
//    /*********************************************************/
//
//    // Create Trip
//    // Info
//    trip = [[HTTripInfo alloc]init];
//    trip.tripName = @"Monday Work.";
//    trip.tripDescription = @"My Monday Trip";
//    oldTime = [oldTime dateByAddingTimeInterval:60.0*60.0*60.0];
//    tripDataArray = [NSMutableArray new];
//
//    dataItem1 = [[HTTripData alloc]init];
//    dataItem1.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem1.bpm = 72;
//    dataItem1.latitude = -37.759600;
//    dataItem1.longitude = -122.43095;
//    [tripDataArray addObject:dataItem1];
//
//    dataItem2 = [[HTTripData alloc]init];
//    dataItem2.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem2.bpm = 72;
//    dataItem2.latitude = -37.759600;
//    dataItem2.longitude = -122.43095;
//    [tripDataArray addObject:dataItem2];
//
//    dataItem3 = [[HTTripData alloc]init];
//    dataItem3.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem3.bpm = 72;
//    dataItem3.latitude = -37.759600;
//    dataItem3.longitude = -122.43095;
//    [tripDataArray addObject:dataItem3];
//
//    dataItem4 = [[HTTripData alloc]init];
//    dataItem4.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem4.bpm = 72;
//    dataItem4.latitude = -37.759600;
//    dataItem4.longitude = -122.43095;
//    [tripDataArray addObject:dataItem4];
//
//    dataItem5 = [[HTTripData alloc]init];
//    dataItem5.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem5.bpm = 72;
//    dataItem5.latitude = -37.759600;
//    dataItem5.longitude = -122.43095;
//    [tripDataArray addObject:dataItem5];
//
//    trip.data = tripDataArray;
//
//    [tripList addObject:trip];
//    [self persistATrip:trip];
//
//    /*********************************************************/
//
//    // Create Trip
//    // Info
//    trip = [[HTTripInfo alloc]init];
//    trip.tripName = @"Road trip.";
//    trip.tripDescription = @"My Monday Trip";
//    oldTime = [oldTime dateByAddingTimeInterval:60.0*60.0*60.0];
//    tripDataArray = [NSMutableArray new];
//
//    dataItem1 = [[HTTripData alloc]init];
//    dataItem1.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem1.bpm = 72;
//    dataItem1.latitude = -37.759600;
//    dataItem1.longitude = -122.43095;
//    [tripDataArray addObject:dataItem1];
//
//    dataItem2 = [[HTTripData alloc]init];
//    dataItem2.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem2.bpm = 72;
//    dataItem2.latitude = -37.759600;
//    dataItem2.longitude = -122.43095;
//    [tripDataArray addObject:dataItem2];
//
//    dataItem3 = [[HTTripData alloc]init];
//    dataItem3.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem3.bpm = 72;
//    dataItem3.latitude = -37.759600;
//    dataItem3.longitude = -122.43095;
//    [tripDataArray addObject:dataItem3];
//
//    dataItem4 = [[HTTripData alloc]init];
//    dataItem4.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem4.bpm = 72;
//    dataItem4.latitude = -37.759600;
//    dataItem4.longitude = -122.43095;
//    [tripDataArray addObject:dataItem4];
//
//    dataItem5 = [[HTTripData alloc]init];
//    dataItem5.timeStamp = currentTime = [oldTime dateByAddingTimeInterval:60.0*5];
//
//
//    oldTime = [currentTime dateByAddingTimeInterval:60.0*5];
//
//    dataItem5.bpm = 72;
//    dataItem5.latitude = -37.759600;
//    dataItem5.longitude = -122.43095;
//    [tripDataArray addObject:dataItem5];
//
//    trip.data = tripDataArray;
//
//    [tripList addObject:trip];
//    [self persistATrip:trip];
//
//    /*********************************************************/
//
//}
//
//- (void)persistATrip:(HTTripInfo *)trip {
//    NSString *tripName = trip.tripName;
//    NSString *tripDescription = trip.tripDescription;
//
//    NSArray *tripDataArray = trip.data;
//    NSMutableArray *tripDataDictArray = [NSMutableArray new];
//    for (HTTripData *tripDataItem in tripDataArray) {
//        NSDate *timeStamp = tripDataItem.timeStamp;
//        int bpm = tripDataItem.bpm;
//        double latitude = tripDataItem.latitude;
//        double longitude = tripDataItem.longitude;
//
//        NSDictionary *tripItemDict = @{
//                                       @"time_stamp":timeStamp,
//                                       @"bpm": [NSNumber numberWithInt: bpm],
//                                       @"latitude":[NSNumber numberWithDouble: latitude],
//                                       @"longitude":[NSNumber numberWithDouble: longitude]
//                                       };
//
//        [tripDataDictArray addObject:tripItemDict];
//
//
//        NSLog(@"Trip: %@, Trip Description: %@, TimeStamp: %@, bpm: %d, longitude: %f, latitude: %f", tripName, tripDescription, timeStamp, bpm, latitude, longitude);
//    }
//
//    NSDictionary *tripDict = @{
//                               @"trip_name": tripName,
//                               @"trip_description": tripDescription,
//                               @"trip_data": tripDataDictArray
//                               };
//
//    NSString *key = [NSString stringWithFormat:@"%@%@%@", @"happy_time", [NSDate date], tripName];
//    [[NSUserDefaults standardUserDefaults] setObject:tripDict forKey:key];
//
//}

@end
