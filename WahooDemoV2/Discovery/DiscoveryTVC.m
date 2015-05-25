//
//  DiscoveryTableViewController.m
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "DiscoveryTVC.h"
#import "SensorCell.h"
#import "SensorTVC.h"
#import <WFConnector/WFConnector.h>

@interface DiscoveryTVC () <WFDiscoveryManagerDelegate>

@property (nonatomic,strong) WFDiscoveryManager* discoveryManager;
@property (nonatomic,strong) NSMutableArray* discoveredDevices;

@end

@implementation DiscoveryTVC



#pragma mark -
#pragma mark Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.tableView.tableFooterView = [UIView new];
    
    [ProgressHUD show:nil];
}


- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

    // Startip the Discovery process
    [self startDiscovery];
}

- (void) viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [ProgressHUD dismiss];
    
    // Cancel the discovery
    [self cancelDiscovery];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    NSIndexPath* indexPath = [self.tableView indexPathForCell:sender];
    
    if([segue.identifier isEqualToString:@"sensorSegue"])
    {
        SensorTVC* sensorTVC = segue.destinationViewController;
        sensorTVC.deviceInformation = [self.discoveredDevices objectAtIndex:indexPath.row];
    }
}

#pragma mark -
#pragma mark Discovery

- (NSArray*) sensorTypes
{
    // Return nil for wildcard discovery
    return nil;
    
    // Or and array of sensor types you would like to find
    // return @[@(WF_SENSORTYPE_BIKE_POWER),@(WF_SENSORTYPE_HEARTRATE)];
}

- (void) startDiscovery
{
    NSLog(@"startDiscovery");
    
    // Remove any old devices we had cached
    if(self.discoveredDevices.count || !self.discoveredDevices) {
        self.discoveredDevices = [NSMutableArray new];
        [self.tableView reloadData];
    }
    
    // Setup the discovery manager
    if(self.discoveryManager==nil) {
        self.discoveryManager = [WFDiscoveryManager new];
        self.discoveryManager.delegate = self;
    }
    
    // Start discovery on both ANT+ and BTLE, only networks that are ready will start.
    [self.discoveryManager discoverSensorTypes:[self sensorTypes] onNetwork:WF_NETWORKTYPE_ANY];
}

- (void) cancelDiscovery
{
    NSLog(@"cancelDiscovery");
    
    [self.discoveryManager cancelDiscovery];
}

#pragma mark -
#pragma mark  WFDiscoveryManagerDelegate

- (void)discoveryManager:(WFDiscoveryManager*)discoveryManager didDiscoverDevice:(WFDeviceInformation*)deviceInformation
{
    if([self.discoveredDevices containsObject:deviceInformation]==NO)
    {
        [self.discoveredDevices addObject:deviceInformation];
        
        NSLog(@"Got device");
        
        [ProgressHUD dismiss];
        
        self.title = @"Device Found";
        
        
        [self.tableView beginUpdates];
        [self.tableView insertRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:self.discoveredDevices.count-1 inSection:0]] withRowAnimation:UITableViewRowAnimationAutomatic];
        [self.tableView endUpdates];
    }
}

- (void)discoveryManager:(WFDiscoveryManager*)discoveryManager didLooseDevice:(WFDeviceInformation*)deviceInformation
{
    NSInteger index = [self.discoveredDevices indexOfObject:deviceInformation];
    
    if(index!=NSNotFound)
    {
        [self.discoveredDevices removeObject:deviceInformation];
        
        [self.tableView beginUpdates];
        [self.tableView deleteRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:index inSection:0]] withRowAnimation:UITableViewRowAnimationAutomatic];
        [self.tableView endUpdates];
    }
}

#pragma mark -
#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.discoveredDevices.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    SensorCell*cell = (SensorCell*)[tableView dequeueReusableCellWithIdentifier:@"SensorCell" forIndexPath:indexPath];
    
    WFDeviceInformation* deviceInformation = [self.discoveredDevices objectAtIndex:indexPath.row];
    
    // Configure the cell...
    cell.deviceInformation = deviceInformation;
    
    return cell;
    
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return 488;
    
}


@end
