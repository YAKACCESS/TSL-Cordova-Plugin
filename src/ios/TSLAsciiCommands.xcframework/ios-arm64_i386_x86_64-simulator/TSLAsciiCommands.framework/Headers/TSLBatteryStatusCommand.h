//
//  TSLBatteryStatusCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>
#import <TSLAsciiCommands/TSLCommandParameters.h>
#import <TSLAsciiCommands/TSLBatteryServiceData.h>
#import <TSLAsciiCommands/TSLBatteryHealthData.h>

NS_ASSUME_NONNULL_BEGIN


///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define USE_ENUM(e,p,s) e,

/// Charge State values
#define TSL_FOR_EACH_CHARGE_STATE(select)\
\
select( TSL_ChargeState_NotSpecified = 0,  @"",            @"Not specified"                     )\
select( TSL_ChargeState_Off,               @"Off",         @"The battery is not being charged"  )\
select( TSL_ChargeState_Charging,          @"Charging",    @"The battery is charging"           )\
select( TSL_ChargeState_Complete,          @"Complete",    @"Battery charging is complete"      )\
select( TSL_ChargeState_Error,             @"Error",       @"There is a battery charging error" )

///
/// The Charge State type
///
typedef enum { TSL_FOR_EACH_CHARGE_STATE(USE_ENUM) } TSL_ChargeState;

#undef USE_ENUM


///
/// A command to query the reader for battery status information
///
@interface TSLBatteryStatusCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol>

/// @name Properties

/// The battery level retrieved from the reader
@property (nonatomic, readonly) int batteryLevel;

/// Get the charge status
///
/// The TSL_ChargeState enum is used to indicate values for `chargeStatus` parameter.
///
/// When a `TSLBatteryStatusCommand` has been issued to the reader, the response values are interpreted as follows:
///
/// - `TSL_ChargeState_NotSpecified` - _The value has not been specified_
/// - `TSL_ChargeState_Off` - _The battery is not being charged_
/// - `TSL_ChargeState_Charging` - _The battery is charging_
/// - `TSL_ChargeState_Complete` - _Battery charging is complete_
/// - `TSL_ChargeState_Error` - _There is a battery charging error_
///
@property (nonatomic, readonly) TSL_ChargeState chargeStatus;

/// Set to `TSL_TriState_YES` to read battery health and service data
@property (nonatomic, readwrite) TSL_TriState readBatteryData;

/// The battery health data
@property (nonatomic, readonly, nullable) TSLBatteryHealthData *healthData;

/// The battery service data
@property (nonatomic, readonly, nullable) TSLBatteryServiceData *serviceData;


///
/// Set to `TSL_TriState_YES` to start the generation of asynchronous battery status reports
/// Set to `TSL_TriState_NO` to stop the generation of asynchronous battery status reports
/// Set to `TSL_TriState_NOT_SPECIFIED` to leave the asynchronous reporting state unchanged
///
@property (nonatomic, readwrite) TSL_TriState asynchronousReportingEnabled;

/// @name Factory Methods

///
/// Returns a synchronous TSLBatteryStatusCommand
///
+(TSLBatteryStatusCommand *)synchronousCommand;


@end

NS_ASSUME_NONNULL_END
