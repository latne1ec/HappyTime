//
//  WFDisplayPage.h
//  WFConnector
//
//  Created by Murray Hughes on 16/12/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFDisplayElement.h>
#import <WFConnector/_WFDisplayPage.h>


@interface WFDisplayPage : _WFDisplayPage <NSCopying>
{
    NSString* _key;
    BOOL _hidden;
    NSString* _comment;
    NSArray* _elements;
    NSString* _soundKey;
}

// Key used to identify the page. This value must be unique to all other pages.
@property (nonatomic, copy) NSString* key;

// Sets if the page is hidden from normal page toggling function. Page can be manually shown via the API.
@property (nonatomic, assign, getter = isHidden) BOOL hidden;

// String that can be used to store anything you want, not used internally
@property (nonatomic, copy) NSString* comment;


// Array of dictionaries representing elements.
@property (nonatomic, readonly) NSArray* elements;

@property (nonatomic, copy) NSString* soundKey;


// Add element tot the display page
- (void) addElement:(WFDisplayElement*) element;
- (void) removeElement:(WFDisplayElement*) element;
- (void) removeAllElements;

@end