//
//  WFProximityRangeView.m
//  UberFisica
//
//  Created by Benjamin Johnston on 27/11/2013.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import "WFSignalStrengthView.h"

#define BAR_0_FLOOR 0.1
#define BAR_1_FLOOR 0.2
#define BAR_2_FLOOR 0.3
#define BAR_3_FLOOR 0.5
#define BAR_4_FLOOR 0.7

#define BAR_0_ON_HEIGHT 0.6
#define BAR_1_ON_HEIGHT 0.7
#define BAR_2_ON_HEIGHT 0.8
#define BAR_3_ON_HEIGHT 0.9
#define BAR_4_ON_HEIGHT 1.0
#define BAR_OFF_HEIGHT 0.2

#define BAR_COUNT 5
#define BAR_GAP 2

@interface WFSignalStrengthView()

@property (nonatomic, retain) NSArray* bars;

@end

@implementation WFSignalStrengthView

- (void)awakeFromNib
{
    self.backgroundColor = [UIColor clearColor];
    
    //initialise the bar views
    NSMutableArray* mutableBars = [NSMutableArray array];
    double barwidth = (self.frame.size.width - BAR_GAP * (BAR_COUNT - 1)) / BAR_COUNT;
    for(int barIndex = 0; barIndex <= 4; barIndex++)
    {
        UIView* bar = [[UIView alloc] initWithFrame:CGRectMake(barIndex * (barwidth + BAR_GAP), 0 , barwidth, BAR_OFF_HEIGHT)];
        [mutableBars addObject:bar];
        [self addSubview:bar];
        
        [self configureForNewRange];
    }
    self.bars = mutableBars;
}

- (void)layoutSubviews
{
    [self configureForNewRange];
}

#pragma mark - Property Accessors

- (void)setSignalStrength:(double)signalStrength
{
    _signalStrength = signalStrength;
    
    [self configureForNewRange];
}

- (UIColor*)onColor
{
    if(!_onColor)
    {
        _onColor = [UIColor greenColor];
    }
    return _onColor;
}

- (UIColor*)offColor
{
    if(!_offColor)
    {
        _offColor = [UIColor lightGrayColor];
    }
    return _offColor;
}


#pragma mark - Private Functions

- (void)configureForNewRange
{
    if(self.signalStrength < BAR_0_FLOOR)
    {
        for(UIView* bar in self.bars)
        {
            [self setBarHeight:BAR_OFF_HEIGHT forBar:bar];
            bar.backgroundColor = self.offColor;
        }
    }
    
    else
    {
        for(UIView* bar in self.bars)
        {
            [self setBarHeight:BAR_OFF_HEIGHT forBar:bar];
            bar.backgroundColor = self.onColor;
        }
        
        [self setBarHeight:BAR_0_ON_HEIGHT forBar:self.bars[0]];
        
        if(self.signalStrength >= BAR_1_FLOOR)
        {
            [self setBarHeight:BAR_1_ON_HEIGHT forBar:self.bars[1]];
        }
        
        if(self.signalStrength >= BAR_2_FLOOR)
        {
            [self setBarHeight:BAR_2_ON_HEIGHT forBar:self.bars[2]];
        }
        
        if(self.signalStrength >= BAR_3_FLOOR)
        {
            [self setBarHeight:BAR_3_ON_HEIGHT forBar:self.bars[3]];
        }
        
        if(self.signalStrength >= BAR_4_FLOOR)
        {
            [self setBarHeight:BAR_4_ON_HEIGHT forBar:self.bars[4]];
        }
        
    }
}


- (void)setBarHeight:(double)height forBar:(UIView*)bar
{
    CGRect frame = bar.frame;
    frame.size.height = self.frame.size.height * height;
    frame.origin.y = self.frame.size.height - frame.size.height;
    bar.frame = frame;
}


@end
