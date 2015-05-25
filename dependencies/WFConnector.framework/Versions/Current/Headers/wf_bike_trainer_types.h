//
//  wf_bike_trainer_types.h
//  WFConnector
//
//  Created by Michael Moore on 8/18/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#ifndef WFConnector_wf_bike_trainer_types_h
#define WFConnector_wf_bike_trainer_types_h


/** Describes the difficulty level of trainer progressive resistance while in Standard Mode. */
typedef enum
{
    /** Trainer level not specified. */
    WF_BIKE_TRAINER_LEVEL_NONE = 0,
    /** The least difficult progressive power curve. */
    WF_BIKE_TRAINER_LEVEL_1    = 1,
    /** Progressive resistance level 2 of 9. */
    WF_BIKE_TRAINER_LEVEL_2    = 2,
    /** Progressive resistance level 3 of 9. */
    WF_BIKE_TRAINER_LEVEL_3    = 3,
    /** Progressive resistance level 4 of 9. */
    WF_BIKE_TRAINER_LEVEL_4    = 4,
    /** Progressive resistance level 5 of 9. */
    WF_BIKE_TRAINER_LEVEL_5    = 5,
    /** Progressive resistance level 6 of 9. */
    WF_BIKE_TRAINER_LEVEL_6    = 6,
    /** Progressive resistance level 7 of 9. */
    WF_BIKE_TRAINER_LEVEL_7    = 7,
    /** Progressive resistance level 8 of 9. */
    WF_BIKE_TRAINER_LEVEL_8    = 8,
    /** The most difficult progressive power curve. */
    WF_BIKE_TRAINER_LEVEL_9    = 9,

    
} WFBikeTrainerLevel_t;

/** Describes the mode in which the trainer is currently running. */
typedef enum
{
    /** Trainer mode not specified. */
    WF_BIKE_TRAINER_MODE_NONE = 0,
    /** Standard Mode will mimic a typical fluid trainer's resistance curve. */
    WF_BIKE_TRAINER_MODE_STANDARD,
    /** Erg mode will maintain a constant target power output regardless of speed. */
    WF_BIKE_TRAINER_MODE_ERG,
    /** Sim mode will simulate real world riding conditions. */
    WF_BIKE_TRAINER_MODE_SIM,
    /** Resistance mode will allow direct control of the trainer's resistance. */
    WF_BIKE_TRAINER_MODE_RESISTANCE,
    /**
     * FTP mode will maintain a constant target power output regardless of speed,
     * where the target power is a percentage of FTP (Functional Threshold Power).
     */
    WF_BIKE_TRAINER_MODE_FTP,
    
} WFBikeTrainerMode_t;


// NEED_DOCS:
typedef enum
{
	WF_BIKE_TRAINER_MODE_PARAMS_NONE = 0,
	WF_BIKE_TRAINER_MODE_PARAMS_DEFAULT,
	WF_BIKE_TRAINER_MODE_PARAMS_SIM_WEIGHT,
	WF_BIKE_TRAINER_MODE_PARAMS_SIM_C,
	WF_BIKE_TRAINER_MODE_PARAMS_SIM_CRR,
	WF_BIKE_TRAINER_MODE_PARAMS_SIM_WIND_SPEED,
	WF_BIKE_TRAINER_MODE_PARAMS_SIM_GRADE,
	WF_BIKE_TRAINER_MODE_PARAMS_FTP_POWER,
	WF_BIKE_TRAINER_MODE_PARAMS_FTP_PERCENT,
    
} WFBikeTrainerModeParams_t;

// NEED_DOCS:
typedef enum
{
	WF_BIKE_TRAINER_FEATURE_INVALID = 0,
	WF_BIKE_TRAINER_FEATURE_CONSUME_ANT_CADENCE,
	WF_BIKE_TRAINER_FEATURE_REGULATE_POWER_FROM_ANT,
	WF_BIKE_TRAINER_FEATURE_ERG_MODE_SPEED_SIMULATION,
	WF_BIKE_TRAINER_FEATURE_SIMULATE_SPEED_FROM_DOWNHILL,
    
} WFBikeTrainerFeature_t;

// NEED_DOCS:
typedef enum
{
	WF_BIKE_TRAINER_PAIRED_ANT_CHANNEL_TYPE_NONE         = 0,
	WF_BIKE_TRAINER_PAIRED_ANT_CHANNEL_TYPE_BPS_TX       = 0x01,
	WF_BIKE_TRAINER_PAIRED_ANT_CHANNEL_TYPE_BPS_RX       = 0x02,
	WF_BIKE_TRAINER_PAIRED_ANT_CHANNEL_TYPE_BSS_TX       = 0x04,
	WF_BIKE_TRAINER_PAIRED_ANT_CHANNEL_TYPE_BCS_RX       = 0x08,
	WF_BIKE_TRAINER_PAIRED_ANT_CHANNEL_TYPE_CBSC_RX      = 0x10,
	WF_BIKE_TRAINER_PAIRED_ANT_CHANNEL_TYPE_KICKR_RX     = 0x20,
    
} WFBikeTrainerPairedAntChannelType_t;


typedef enum
{
	WF_BIKE_TRAINER_PAIRED_ANT_DEVICE_STATE_INVALID      = 0,
	WF_BIKE_TRAINER_PAIRED_ANT_DEVICE_STATE_CLOSED       = 1,
	WF_BIKE_TRAINER_PAIRED_ANT_DEVICE_STATE_SEARCHING    = 2,
	WF_BIKE_TRAINER_PAIRED_ANT_DEVICE_STATE_OPEN         = 3,
    
} WFBikeTrainerPairedAntDeviceState_t;


FOUNDATION_EXPORT NSString* const WFTrainerModeParamsLevelKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsTargetWattsKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsSpeedSimEnabledKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsWeightKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsWindResistanceKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsRollingResistanceKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsWindSpeedKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsGradeKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsResistanceKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsFTPPowerKey;
FOUNDATION_EXPORT NSString* const WFTrainerModeParamsFTPPercentageKey;

#endif  // WFConnector_wf_bike_trainer_types_h
