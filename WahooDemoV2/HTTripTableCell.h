//
//  HTTripTableCell.h
//  WahooDemoV2
//
//  Created by Evan Latner on 5/24/15.
//  Copyright (c) 2015 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface HTTripTableCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *tripImage;

@property (weak, nonatomic) IBOutlet UILabel *tripNameLabel;

@property (weak, nonatomic) IBOutlet UILabel *tripTimeLabel;

@end
