//
//  TSLSleepCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAllParameters.h>
#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define TSL_FOR_EACH_RECONNECTION_MODE(select)\
\
select( TSL_ReconnectionMode_NotSpecified = 0,    @"",        @"Not specified"            )\
select( TSL_ReconnectionMode_None,                @"off",     @"No reconnection"  )\
select( TSL_ReconnectionMode_Rfcomm,              @"rfc",     @"Reconnect using RFCOMM"  )\
select( TSL_ReconnectionMode_Iap,                 @"iap",     @"Reconnect using iAP"  )


#define USE_ENUM(e,p,s) e,

///
/// The reconnection mode types
///
typedef enum { TSL_FOR_EACH_RECONNECTION_MODE(USE_ENUM) } TSL_ReconnectionMode;

#undef USE_ENUM



///
/// A command to send the reader to sleep as soon as it has responded to this command
///
/// *Note:* this will disconnect the reader from the iOS device
///
@interface TSLSleepCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol>

/// @name Properties

/// When set to `TSL_TriState_YES` the Reader will attempt to reconnect when waking
/// Only _None and _Iap supported
@property (nonatomic, readwrite) TSL_TriState autoReconnect;

/// The connection mode
///
/// The `TSL_ReconnectionMode` enum is used to specify values for the `connectionMode` parameter.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_ReconnectionMode_NotSpecified` - _The value has not been specified and the `connectionMode` parameter will not be sent_
/// - `TSL_ReconnectionMode_None - _no reconnection has been specified and is sent as `'off'`_
/// - `TSL_ReconnectionMode_Rfcomm - _reconnection to an RFCOMM device has been specified and is sent as `'rfc'`_
/// - `TSL_ReconnectionMode_Iap - _reconnection to an iOS device has been specified and is sent as `'iap'`_
///
/// When a command includes the '-p' option the `connectionMode` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_ReconnectionMode connectionMode;

/// The Bluetooth MAC address the Reader should re-connect to
@property (nonatomic, readwrite, nullable) NSString *macAddress;

/// When set to `TSL_TriState_YES` the Reader will reboot (21xx series only)
@property (nonatomic, readwrite) TSL_TriState reboot;


/// @name Factory Methods

///
/// Returns a synchronous TSLDateCommand
///
+(TSLSleepCommand *)synchronousCommand;


/// @name TSL_ReconnectionMode Helper methods

///
/// Test the given TSL_ReconnectionMode for validity
///
///@param mode The TSL_ReconnectionMode value to be tested
///@return YES if the given TSL_ReconnectionMode is valid otherwise NO
///
-(BOOL)isValidReconnectionMode:(TSL_ReconnectionMode)mode;

///
/// Parse the given parameter value string and determine the corresponding TSL_ReconnectionMode
///
///@param value The parameter value as NSString
///@return The TSL_ReconnectionMode corresponding to the given string. Invalid parameter values return TSL_ReconnectionMode_NotSpecified
///
-(TSL_ReconnectionMode)reconnectionModeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_ReconnectionMode
///
///@param mode The TSL_ReconnectionMode value to be converted
///@return The command parameter value for the given TSL_ReconnectionMode or nil if invalid
///
-(nullable NSString *)parameterValueForReconnectionMode:(TSL_ReconnectionMode)mode;

///
/// Get the description corresponding to the given TSL_ReconnectionMode
///
///@param mode The TSL_ReconnectionMode value to be converted
///@return The user friendly name for the given TSL_ReconnectionMode  or nil if invalid
///
-(nullable NSString *)descriptionForReconnectionMode:(TSL_ReconnectionMode)mode;

@end

NS_ASSUME_NONNULL_END
