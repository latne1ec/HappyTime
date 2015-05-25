//
//  WFDisplayButton.h
//  WFConnector
//
//  Created by Murray Hughes on 28/06/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WFDisplayObject.h"

@interface WFDisplayButton : WFDisplayObject
{
    NSString* _key;
    NSString* _action;
    NSString* _sound;
}

@property (nonatomic, copy) NSString* key;
@property (nonatomic, copy) NSString* action;
@property (nonatomic, copy) NSString* sound;

@end
