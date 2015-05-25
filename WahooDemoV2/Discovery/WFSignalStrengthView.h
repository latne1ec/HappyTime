//
//  WFProximityRangeView.h
//  UberFisica
//
//  Created by Benjamin Johnston on 27/11/2013.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface WFSignalStrengthView : UIView

@property (nonatomic, assign) double signalStrength;
@property (nonatomic, retain) UIColor* onColor;
@property (nonatomic, retain) UIColor* offColor;

@end
