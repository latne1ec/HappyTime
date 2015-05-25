//
//  UIColor+WFHelpers.m
//  UberFisica
//
//  Created by Benjamin Johnston on 17/08/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import "UIColor+WFHelpers.h"

@implementation UIColor (WFHelpers)


+ (UIColor *) colorWithRGB:(uint32_t)rgbValue alpha:(float) alpha
{
    return [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0
                           green:((float)((rgbValue & 0xFF00) >> 8))/255.0
                            blue:((float)(rgbValue & 0xFF))/255.0
                           alpha:alpha];
}


+ (UIColor *)colorWithRGB:(uint32_t)rgbValue {
    return [UIColor colorWithRGB:rgbValue alpha:1.0];
}


+(UIColor*)colorWithRGBArray:(NSArray *)rgb
{
    CGFloat red = [rgb[0] floatValue];
    CGFloat green = [rgb[1] floatValue];
    CGFloat blue = [rgb[2] floatValue];

    return [UIColor colorWithRed:red/255.0 green:green/255.0 blue:blue/255.0 alpha:1.0];
}

+(UIColor*)colorWithRGBArray:(NSArray *)rgb alpha:(CGFloat) alpha
{
    CGFloat red = [rgb[0] floatValue];
    CGFloat green = [rgb[1] floatValue];
    CGFloat blue = [rgb[2] floatValue];
    
    return [UIColor colorWithRed:red/255.0 green:green/255.0 blue:blue/255.0 alpha:alpha];
}

+(UIColor*)wahooDarkBlueColor
{
    return [UIColor colorWithRGBArray:@[@3,@81,@123]];
}

+(UIColor*)wahooDarkBlueColorAlpha:(CGFloat) alpha
{
    return [UIColor colorWithRGBArray:@[@3,@81,@123] alpha:alpha];
}

+(UIColor*)wahooLightBlueColor
{
    return [UIColor colorWithRGBArray:@[@0,@191,@243]];//@[@7,@165,@198]];
}

+(UIColor*)wahooYellowColor
{
    return [UIColor colorWithRGBArray:@[@244,@214,@18]];
}


+(UIColor*)wahooGreenColor
{
    return [UIColor colorWithRGBArray:@[@110,@174,@46]];
}

+(UIColor*)wahooDarkGreenColor
{
    return [UIColor colorWithRGBArray:@[@0,@88,@38]];
}

+(UIColor*)wahooRedColor
{
    return [UIColor redColor];
}

+(UIColor*)wahooDarkRedColor
{
    return [UIColor colorWithRGBArray:@[@130,@26,@26]];
}

+(UIColor*)wahooDarkGreyColor
{
    return [UIColor colorWithRGBArray:@[@59,@59,@59]];
}

+(UIColor*)wahooDarkBurnColor
{
    return [UIColor colorWithRGBArray:@[@241,@139,@40]];
}

+(UIColor*)wahooDarkBurstColor
{
    return [UIColor colorWithRGBArray:@[@139,@26,@13]];
}

+(UIColor*)wahooLightBurnColor
{
    return [UIColor colorWithRGBArray:@[@242,@215,@49]];
}

+(UIColor*)wahooLightBurstColor
{
    return [UIColor colorWithRGBArray:@[@228,@64,@46]];
}


+(UIColor *)colorWithColor:(UIColor *)color alpha:(CGFloat)alpha
{
    CGFloat red = 0.0, green = 0.0, blue = 0.0, a =0.0;
    [color getRed:&red green:&green blue:&blue alpha:&a];
    return [UIColor colorWithRed:red green:green blue:blue alpha:alpha];
}

@end
