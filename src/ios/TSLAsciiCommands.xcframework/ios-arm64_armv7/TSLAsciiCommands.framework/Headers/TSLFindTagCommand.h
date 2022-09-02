//
//  TSLFindTagCommand.h
//
//  Copyright © 2020 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define USE_ENUM(e,p,s) e,

/// StartStop values
#define TSL_FOR_EACH_START_STOP(select)\
\
select( TSL_StartStop_NotSpecified = 0,  @"",       @"Not specified"   )\
select( TSL_StartStop_Start,             @"art",    @"Start"           )\
select( TSL_StartStop_Stop,              @"op",     @"Stop"            )

///
/// The Process Control type
///
typedef enum { TSL_FOR_EACH_START_STOP(USE_ENUM) } TSL_StartStop;

#undef USE_ENUM

///
/// A command to control the FindTag feature on 21xx series Readers
///
@interface TSLFindTagCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol, TSLAntennaParametersProtocol,TSLResponseParametersProtocol, TSLSelectMaskParametersProtocol, TSLVolumeParametersProtocol, TSLTransponderReceivedDelegate>

/// Control the inclusion of raw RSSI value in reader responses
@property (nonatomic, readwrite) TSL_TriState includeTransponderRssi;

/// Control the inclusion of percentage RSSI value in reader responses
@property (nonatomic, readwrite) TSL_TriState includeTransponderRssiPercent;

/// Control the inclusion of the EPC identifier value in reader responses
@property (nonatomic, readwrite) TSL_TriState includeEPC;

/// Control the Find Tag trigger override.
/// When started the primary trigger action is replaced by _find tag_. The find tag command (.ft) will be executed while the trigger is held.
/// When stopped the primary trigger action is restored to its configured value.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_StartStop_NotSpecified` - _The value has not been specified and the `triggerOverride` parameter will not be sent_
/// - `TSL_StartStop_Start` - _Start has been specified and is sent as `'art'. Start the find tag operation_
/// - `TSL_StartStop_Stop` - _Stop has been specified and is sent as `'op'. Stop the find tag operation_
///
/// When a command includes the '-p' option the `triggerOverride` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_StartStop triggerOverride;

/// Control indicating whether the EPC of a selected tag must match the select data exactly i.e. EPC length matches select length
/// This value only applies when the SelectBank is set to EPC
@property (nonatomic, readwrite) TSL_TriState matchExact;

/// Control indicating whether Visual feedback should be used
/// This value is only supported when the connected Reader has additional LEDs e.g. Antenna LEDs
@property (nonatomic, readwrite) TSL_TriState useVisualFeedback;

/// Controls whether Audible feedback is frequency-based or time-based
@property (nonatomic, readwrite) TSL_TriState useVariableToneFrequency;

/// The First Percentage threshold for audible feedback
@property (nonatomic, readwrite) int soundPercentageThresholdOne;

/// The Second Percentage threshold for audible feedback
@property (nonatomic, readwrite) int soundPercentageThresholdTwo;

/// The Third Percentage threshold for audible feedback
@property (nonatomic, readwrite) int soundPercentageThresholdThree;

///
/// The TSLTransponderDataReceivedBlock
///
/// All transponder responses will invoke this block even when no EPC response is present
/// which is something that the other Block and Delegate methods do not do.
///
@property (nonatomic, copy, nullable) TSLTransponderDataReceivedBlock transponderDataReceivedBlock;

/// @name Factory Methods

///
/// Returns a synchronous TSLFindTagCommand
///
+(TSLFindTagCommand *)synchronousCommand;


/// @name TSL_StartStop  helper Methods

///
/// Parse the given parameter value string and determine the corresponding TSL_StartStop
///
///@param value The parameter value as NSString
///@return The TSL_StartStop corresponding to the given string. Invalid parameter values return TSL_StartStop_NotSpecified
///
+(TSL_StartStop)actionForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_StartStop
///
///@param action The TSL_StartStop value to be converted
///@return The command parameter value for the given TSL_StartStop or nil if invalid
///
+(nullable NSString *)parameterValueForAction:(TSL_StartStop)action;

///
/// Get the description corresponding to the given TSL_StartStop
///
///@param action The TSL_StartStop value to be converted
///@return The user friendly name for the given TSL_StartStop or nil if invalid
///
+(nullable NSString *)descriptionForAction:(TSL_StartStop)action;

///
/// Test the given TSL_StartStop for validity
///
///@param action The TSL_StartStop value to be tested
///@return YES if the given TSL_StartStop is valid otherwise NO
///
+(BOOL)isValid:(TSL_StartStop)action;

@end

NS_ASSUME_NONNULL_END
