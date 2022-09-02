//
//  TSLAlertCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLCommandParameters.h>
#import <TSLAsciiCommands/TSLVolumeParameters.h>
#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define USE_ENUM(e,p,s) e,

/// Alert duration values
#define TSL_FOR_EACH_ALERT_DURATION(select)\
\
select( TSL_AlertDuration_NotSpecified = 0,  @"",       @"Not specified"   )\
select( TSL_AlertDuration_Short,             @"sho",    @"Short"           )\
select( TSL_AlertDuration_Medium,            @"med",    @"Medium"          )\
select( TSL_AlertDuration_Long,              @"lon",    @"Long"            )

///
/// The Alert duration type
///
typedef enum { TSL_FOR_EACH_ALERT_DURATION(USE_ENUM) } TSL_AlertDuration;

/// Alert tone values
#define TSL_FOR_EACH_BUZZER_TONE(select)\
\
select( TSL_BuzzerTone_NotSpecified = 0,  @"",       @"Not specified"   )\
select( TSL_BuzzerTone_Low,               @"low",    @"Low"             )\
select( TSL_BuzzerTone_Medium,            @"med",    @"Medium"          )\
select( TSL_BuzzerTone_High,              @"hig",    @"High"            )

///
/// The Alert tone type
///
typedef enum { TSL_FOR_EACH_BUZZER_TONE(USE_ENUM) } TSL_BuzzerTone;

#undef USE_ENUM



///
/// A command to configure and query the reader's alert options
///
@interface TSLAlertCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol, TSLVolumeParametersProtocol>

/// @name Properties

/// Turn the buzzer on or off
@property (nonatomic, readwrite) TSL_TriState enableBuzzer;

/// Set the Buzzer & Vibrator duration
///
/// The `TSL_AlertDuration` enum is used to specify values for the `duration` parameter.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_AlertDuration_NOT_SPECIFIED` - _The value has not been specified and the `duration` parameter will not be sent_
/// - `TSL_AlertDuration_Short` - _a short duration has been specified and is sent as `'sho'`_
/// - `TSL_AlertDuration_Medium` - _a medium duration has been specified and is sent as `'med'`_
/// - `TSL_AlertDuration_Long` - _a long duration has been specified and is sent as `'lon'`_
///
/// When a command includes the '-p' option the `duration` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_AlertDuration duration;

/// Set the Buzzer tone
///
/// The `TSL_BuzzerTone` enum is used to specify values for the `tone` parameter.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_BuzzerTone_NOT_SPECIFIED` - _The value has not been specified and the `tone` parameter will not be sent_
/// - `TSL_BuzzerTone_Low` - _a low tone has been specified and is sent as `'low'`_
/// - `TSL_BuzzerTone_Medium` - _a medium tone has been specified and is sent as `'med'`_
/// - `TSL_BuzzerTone_High` - _a high tone has been specified and is sent as `'hig'`_
///
/// When a command includes the '-p' option the `tone` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_BuzzerTone tone;

/// Turn the vibrator on or off
@property (nonatomic, readwrite) TSL_TriState enableVibrator;

/// Turn the Visuals (e.g. antenna LEDs) on or off
@property (nonatomic, readwrite) TSL_TriState enableVisuals;

/// Turn the Find Me tone on or off
@property (nonatomic, readwrite) TSL_TriState findMe;


/// @name Factory Methods

///
/// Returns a synchronous TSLAlertCommand
///
+(TSLAlertCommand *)synchronousCommand;


///
/// @name TSL_AlertDuration helper methods
///

///
/// Parse the given parameter value string and determine the corresponding TSL_AlertDuration
///
///@param value The parameter value as NSString
///@return The TSL_AlertDuration corresponding to the given string. Invalid parameter values return TSL_AlertDuration_NotSpecified
///
+(TSL_AlertDuration)alertDurationForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_AlertDuration
///
///@param duration The TSL_AlertDuration value to be converted
///@return The command parameter value for the given TSL_AlertDuration or nil if invalid
///
+(nullable NSString *)parameterValueForAlertDuration:(TSL_AlertDuration)duration;


///
/// Get the description corresponding to the given TSL_AlertDuration
///
///@param duration The TSL_AlertDuration value to be converted
///@return The user friendly name for the given TSL_AlertDuration or nil if invalid
///
+(nullable NSString *)descriptionForAlertDuration:(TSL_AlertDuration)duration;

///
/// Test the given TSL_AlertDuration for validity
///
///@param duration The TSL_AlertDuration value to be tested
///@return YES if the given TSL_AlertDuration is valid otherwise NO
///
+(BOOL)isValidAlertDuration:(TSL_AlertDuration)duration;


///
/// @name TSL_BuzzerTone helper methods
///

///
/// Parse the given parameter value string and determine the corresponding TSL_BuzzerTone
///
///@param value The parameter value as NSString
///@return The TSL_BuzzerTone corresponding to the given string. Invalid parameter values return TSL_BuzzerTone_NotSpecified
///
+(TSL_BuzzerTone)buzzerToneForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_BuzzerTone
///
///@param tone The TSL_BuzzerTone value to be converted
///@return The command parameter value for the given TSL_BuzzerTone or nil if invalid
///
+(nullable NSString *)parameterValueForBuzzerTone:(TSL_BuzzerTone)tone;


///
/// Get the description corresponding to the given TSL_BuzzerTone
///
///@param tone The TSL_BuzzerTone value to be converted
///@return The user friendly name for the given TSL_BuzzerTone or nil if invalid
///
+(nullable NSString *)descriptionForBuzzerTone:(TSL_BuzzerTone)tone;

///
/// Test the given TSL_BuzzerTone for validity
///
///@param tone The TSL_BuzzerTone value to be tested
///@return YES if the given TSL_BuzzerTone is valid otherwise NO
///
+(BOOL)isValidBuzzerTone:(TSL_BuzzerTone)tone;


@end

NS_ASSUME_NONNULL_END
