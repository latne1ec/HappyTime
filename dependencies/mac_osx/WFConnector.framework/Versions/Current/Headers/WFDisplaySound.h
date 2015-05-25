//
//  WFDisplaySound.h
//  WFConnector
//
//  Created by Murray Hughes on 28/06/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WFDisplayObject.h"

@interface WFDisplaySound : WFDisplayObject
{
    NSString* _key;
    NSString* _value;
}

@property (nonatomic, copy) NSString* key;
@property (nonatomic, copy) NSString* value;

- (NSArray*) tones;

@end
