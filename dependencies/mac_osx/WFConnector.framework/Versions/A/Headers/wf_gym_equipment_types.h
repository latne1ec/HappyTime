//
//  wf_gym_equipment_types.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#ifndef _WF_GYM_EQUIPMENT_TYPES_H_
#define _WF_GYM_EQUIPMENT_TYPES_H_


///////////////////////////////////////////////////////////////////////////////
//
// treadmill-specific definitions.
//
///////////////////////////////////////////////////////////////////////////////


/** Describes a response to a Gym Equipment command. */
typedef enum
{
    /** Unspecified. */
    WF_TMCP_RESPONSE_TO_NONE                = 0x0000,
    /** Response to the Set Mode command. */
    WF_TMCP_RESPONSE_TO_SET_MODE            = 0x0001,
    /** Response to the Read Mode command. */
    WF_TMCP_RESPONSE_TO_READ_MODE           = 0x0002,
    /** Response to the Set Incline command. */
    WF_TMCP_RESPONSE_TO_SET_INCLINE         = 0x0004,
    /** Response to the Read Incline command. */
    WF_TMCP_RESPONSE_TO_READ_INCLINE        = 0x0008,
    /** Response to the Set Workout Time command. */
    WF_TMCP_RESPONSE_TO_SET_WORKOUT_TIME    = 0x0010,
    /** Response to the Read Workout Time command. */
    WF_TMCP_RESPONSE_TO_READ_WORKOUT_TIME   = 0x0020,
    /** Response to the Set Workout Type command. */
    WF_TMCP_RESPONSE_TO_SET_WORKOUT_TYPE    = 0x0040,
    /** Response to the Read Workout Type command. */
    WF_TMCP_RESPONSE_TO_READ_WORKOUT_TYPE   = 0x0080,
    
} WFTreadmillResponseToCommand_t;

/** Describes the status of a Gym Equipment command. */
typedef enum
{
    /** The command succeeded. */
    WF_TREADMILL_STATUS_SUCCESS             = 0x00,
    /** The command failed with an unspecified error. */
    WF_TREADMILL_STATUS_UNSPECIFIED_ERROR   = 0x01,
    /** The treadmill is in the wrong mode for the attempted command. */
    WF_TREADMILL_STATUS_WRONG_MODE          = 0x02,
    
} WFTreadmillStatus_t;

/** Describes the operational mode of the treadmill. */
typedef enum
{
    /** The treadmill is currently stopped with no active workout. */
    WF_TREADMILL_MODE_STOP                  = 0x00,
    /** The treadmill is currently running an active workout. */
    WF_TREADMILL_MODE_RUN                   = 0x01,
    /** The treadmill has an active workout which has been paused. */
    WF_TREADMILL_MODE_PAUSE                 = 0x02,
    
} WFTreadmillMode_t;

/** Describes a treadmill workout type. */
typedef enum
{
    /** The workout type is not specified. */
    WF_TREADMILL_WORKOUT_TYPE_UNSPECIFIED   = 0x00,
    /** The Running workout type. */
    WF_TREADMILL_WORKOUT_TYPE_RUNNING       = 0x01,
    
} WFTreadmillWorkoutType_t;

#endif  // _WF_GYM_EQUIPMENT_TYPES_H_
