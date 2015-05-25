//
//  WFDisplayConfiguration.h
//  WFConnector
//
//  Created by Murray Hughes on 16/12/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WFDisplayPage;

@interface WFDisplayConfiguration : NSObject <NSCopying>
{
    NSMutableArray* _buttons;
    NSMutableArray* _mutablePages;
    NSMutableArray* _errors;

    NSString* _configurationID;
    NSArray* _pages;
    NSString* _comment;

    NSMutableArray* _sounds;
    NSMutableArray* _strings;

@private
    int _type;
    NSString* _passwordHash;
    BOOL assignedBinaryKeys;
    BOOL hasHardwareNextPageButton;
    BOOL hasHardwarePreviousPageButton;
}


// String that can be used to ID the config file, not used internally
@property (nonatomic, copy) NSString* configurationID;

// Array of all the pages in the config.
@property (nonatomic, readonly) NSArray* pages;

// Array of all the sounds in the config
@property (nonatomic, retain) NSMutableArray* sounds;

// Array of all the sounds in the config
@property (nonatomic, retain) NSMutableArray* strings;

// Array of all the button in the config
@property (nonatomic, retain) NSMutableArray* buttons;

// String that can be used to store anything you want, not used internally
@property (nonatomic, copy) NSString* comment;

// Loads the display config from a dictionary representation
+ (id)instanceFromDictionary:(NSDictionary *)aDictionary;

// Loads the display config directly from a json file at the path
+ (id) instanceWithContentsOfFile:(NSString*) filepath;

// Saves the JSON represesntation to a given filepath
- (NSInteger) writeToFile:(NSString*) filepath error:(NSError**) error;

// Returns a dictionary represenstation of the conf
- (NSDictionary *)dictionaryRepresentation;

// manage display pages
- (void) addPage:(WFDisplayPage*) page;
- (void) insertPage:(WFDisplayPage*)page atIndex:(NSUInteger)index;
- (void) removePage:(WFDisplayPage*)page;
- (void) removePageAtIndex:(NSUInteger)index;
- (void) removeAllPages;

// returns the page for a given config
- (WFDisplayPage*) pageForKey:(NSString*) key;

// return all elements in the display pages with a given key
- (NSArray*) elementsForKey:(NSString*) key;

- (NSString*) functionForButtonGestureNamed:(NSString*) buttonGestureName;

- (void) setFunction:(NSString*)function forButtonGestureNamed:(NSString*) buttonGestureName;


@end



