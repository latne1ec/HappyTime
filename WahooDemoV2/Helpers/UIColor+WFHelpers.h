//
//  UIColor+WFHelpers.h
//  UberFisica
//
//  Created by Benjamin Johnston on 17/08/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIColor (WFHelpers)

// Create color using RGB Hex value, eg 0x009922
+ (UIColor*) colorWithRGB:(uint32_t) rgbValue;

+ (UIColor*) colorWithRGB:(uint32_t)rgbValue alpha:(float) alpha;

+ (UIColor*) colorWithRGBArray:(NSArray*) rgb;

+ (UIColor*) colorWithRGBArray:(NSArray*)rgb alpha:(CGFloat) alpha;

+ (UIColor*) colorWithColor:(UIColor*)color alpha:(CGFloat) alpha;

+(UIColor*)wahooDarkBlueColor;
+(UIColor*)wahooDarkBlueColorAlpha:(CGFloat) alpha;
+(UIColor*)wahooLightBlueColor;
+(UIColor*)wahooYellowColor;
+(UIColor*)wahooGreenColor;
+(UIColor*)wahooDarkGreenColor;
+(UIColor*)wahooRedColor;
+(UIColor*)wahooDarkRedColor;
+(UIColor*)wahooDarkGreyColor;

+(UIColor*)wahooDarkBurnColor;
+(UIColor*)wahooDarkBurstColor;
+(UIColor*)wahooLightBurnColor;
+(UIColor*)wahooLightBurstColor;
@end
