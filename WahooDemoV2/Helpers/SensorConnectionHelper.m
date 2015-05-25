//
//  SensorConnectionHelper.m
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "SensorConnectionHelper.h"

@implementation SensorConnectionHelper


+ (WFSensorConnectionStatus_t) combindedSensorStatusFromConnections:(NSArray*) connections
{
    WFSensorConnectionStatus_t combinedStatus = WF_SENSOR_CONNECTION_STATUS_CONNECTED;
    
    if(!connections.count) {
        combinedStatus = WF_SENSOR_CONNECTION_STATUS_IDLE;
    }
    
    //find the combined status for all WFSensors on the UBERSensor
    for(WFSensorConnection* connection in connections)
    {
        
        WFSensorConnectionStatus_t connState = connection.connectionStatus;
        
        switch ( connState )
        {
            case WF_SENSOR_CONNECTION_STATUS_CONNECTED:
            {
                break;
            }
                
            case WF_SENSOR_CONNECTION_STATUS_CONNECTING:
            {
                combinedStatus = WF_SENSOR_CONNECTION_STATUS_CONNECTING;
                break;
            }
                
            case WF_SENSOR_CONNECTION_STATUS_DISCONNECTING:
            {
                combinedStatus = WF_SENSOR_CONNECTION_STATUS_DISCONNECTING;
                break;
            }
            case WF_SENSOR_CONNECTION_STATUS_INTERRUPTED:
            {
                combinedStatus = WF_SENSOR_CONNECTION_STATUS_INTERRUPTED;
                break;
            }
            case WF_SENSOR_CONNECTION_STATUS_IDLE:
            default:
            {
                combinedStatus = WF_SENSOR_CONNECTION_STATUS_IDLE;
                break;
            }
        }
    }
    
    return combinedStatus;
}

@end
