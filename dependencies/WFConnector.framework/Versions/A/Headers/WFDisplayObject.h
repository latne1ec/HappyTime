//
//  WFDisplayObject.h
//  WFConnector
//
//  Created by Murray Hughes on 2/07/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/_WFDisplayObject.h>


@interface WFDisplayObject : _WFDisplayObject
{
    NSMutableDictionary* _undefinedKeys;
}

@property (nonatomic, readonly, retain) NSMutableDictionary* undefinedKeys;


@end
