//
//  WFBTLEFootpodData.h
//  WFConnector
//
//  Created by Michael Moore on 11/8/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFFootpodData.h>
#import "wf_btle_types.h"

@class WFBTLECommonData;


/**
 * Represents the data available from the BTLE Running Speed and Cadence sensor.
 *
 * BTLE sensors send data in multiple packets.  The WFBTLEFootpodData
 * combines the most commonly used of this data into a single entity.  The data
 * represents the latest of each data type sent from the sensor.
 *
 * @note The WFBTLEFootpodData is an extension of the WFFootpodData
 * class.  This class is specific to the data available from the BTLE footpod
 * sensors.  Much of the data is the same as that available from the
 * ANT+ footpod sensors.
 */
@interface WFBTLEFootpodData : WFFootpodData
{
	/** \cond InterfaceDocs */
	
    BOOL hasFeatures;
    
    WFBTLECommonData* btleCommonData;
    
    float instStrideLength;
    
    WFBTLERSCFeatures_t stFeatures;
    WFBTLESensorLocation_t eSensorLocation;
    
	/** \endcond */
}


/** Gets the metadata for the BTLE device. */
@property (nonatomic, retain) WFBTLECommonData* btleCommonData;
/** Gets the instantaneous stride length in meters, when available. */
@property (nonatomic, assign) float instStrideLength;
/**
 * Gets a pointer to a ::WFBTLERSCFeatures_t structure which contains information
 * about the device features.
 *
 * @note If the sensor does not report features, this property will be <c>nil</c>.
 */
@property (nonatomic, readonly) WFBTLERSCFeatures_t* pstFeatures;
/** Gets a ::WFBTLESensorLocation_t which describes the sensor location. */
@property (nonatomic, assign) WFBTLESensorLocation_t eSensorLocation;


/** \cond InterfaceDocs */
/**
 * Initializes a new WFSensorData instance with the specified timestamps.
 *
 * @note This method is for internal use.
 *
 * @param dataTime The data timestamp.
 * @param bFeatures A boolean value indicating whether the features are available.
 *
 * @return The new WFSensorData instance.
 */
- (id)initWithTime:(NSTimeInterval)dataTime hasFeatures:(BOOL)bFeatures;
/** \endcond */


@end
