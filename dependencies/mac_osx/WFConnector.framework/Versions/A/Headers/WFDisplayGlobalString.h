//
//  WFDisplayGlobalString.h
//  WFConnector
//
//  Created by Murray Hughes on 28/06/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFDisplayObject.h>


@interface WFDisplayGlobalString : WFDisplayObject
{
    NSString* _key;
    NSString* _value;
    BOOL _constant;
    NSInteger _maxLength;
}

@property (nonatomic, copy) NSString* key;
@property (nonatomic, copy) NSString* value;

@property (nonatomic, assign, getter = isConstant) BOOL constant;
@property (nonatomic, assign) NSInteger maxLength;

@end
