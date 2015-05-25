//
//  HTTripData.h
//  HappyTime
//
//  Created by Mervyn Sharaf on 5/23/15.
//  Copyright (c) 2015 happytime. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HTTripData : NSObject

@property (nonatomic, strong) NSDate *timeStamp;
@property (nonatomic, assign) int bpm;
@property (nonatomic, assign) double latitude;
@property (nonatomic, assign) double longitude;

@end
