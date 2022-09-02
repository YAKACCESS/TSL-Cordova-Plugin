//
//  TSLSwitchActionCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLTriState.h>
#import <TSLAsciiCommands/TSLCommandParameters.h>
#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, command parameter and descriptive strings that are always in sync
///
/// off/rd/wr/inv/bar/usr
#define TSL_FOR_EACH_SWITCH_ACTION(select)\
\
select( TSL_SwitchAction_NO_CHANGE = 0,     @"",          @""                 )\
select( TSL_SwitchAction_off,               @"off",       @"Off"              )\
select( TSL_SwitchAction_read,              @"rd",        @"Read"             )\
select( TSL_SwitchAction_write,             @"wr",        @"Write"            )\
select( TSL_SwitchAction_inventory,         @"inv",       @"Inventory"        )\
select( TSL_SwitchAction_barcode,           @"bar",       @"Barcode"          )\
select( TSL_SwitchAction_user,              @"usr",       @"User Defined"     )\
select( TSL_SwitchAction_antennaDefault,    @"ad",        @"Antenna Default"  )\
select( TSL_SwitchAction_findTag,           @"ft",        @"Find Tag"         )


#define USE_ENUM(e,p,s) e,

///
/// The `TSL_SwitchAction` enum is used to specify values for the `singlePressAction` and `doublePressAction` parameters
///
typedef enum { TSL_FOR_EACH_SWITCH_ACTION(USE_ENUM) } TSL_SwitchAction;

#undef USE_ENUM

///
/// A command to set the action of the reader's switch
///

@interface TSLSwitchActionCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol>

/// @name Properties

///
/// Set to `TSL_TriState_YES` to start the generation of asynchronous switch status reports
/// Set to `TSL_TriState_NO` to stop the generation of asynchronous switch status reports
/// Set to `TSL_TriState_NOT_SPECIFIED` to leave the asynchronous reporting state unchanged
///
/// if `readParameters` is specified then after execution this property will reflect the current state
///
@property (nonatomic, readwrite) TSL_TriState asynchronousReportingEnabled;

/// Set the Single press action - the values are interpreted as follows:
///
/// - `TSL_SwitchAction_NO_CHANGE` - _The value has not been specified and the parameter will not be sent_
/// - `TSL_SwitchAction_off` - _'do nothing' has been specified and is sent as `'off'`_
/// - `TSL_SwitchAction_read` - _'.rd' command has been specified and is sent as `'rd'`_
/// - `TSL_SwitchAction_write` - _'.wr' command has been specified and is sent as `'wr'`_
/// - `TSL_SwitchAction_inventory` - _'.iv' command has been specified and is sent as `'inv'`_
/// - `TSL_SwitchAction_barcode` - _'.bc' command has been specified and is sent as `'bar'`_
/// - `TSL_SwitchAction_user` - _a 'user-defined' command has been specified and is sent as `'usr'`_
/// - `TSL_SwitchAction_antennaDefault` - _the antenna default command has been specified and is sent as `'ad'`_
/// - `TSL_SwitchAction_findTag` - _a 'find tag' command has been specified and is sent as `'ft'`_
///
/// When a command includes the '-p' option the `singlePressAction` parameter will be set to the reader's current values
///
@property (nonatomic, readwrite) TSL_SwitchAction singlePressAction;

/// Set the Double press action - the values are interpreted as follows:
///
/// - `TSL_SwitchAction_NO_CHANGE` - _The value has not been specified and the parameter will not be sent_
/// - `TSL_SwitchAction_off` - _'do nothing' has been specified and is sent as `'off'`_
/// - `TSL_SwitchAction_read` - _'.rd' command has been specified and is sent as `'rd'`_
/// - `TSL_SwitchAction_write` - _'.wr' command has been specified and is sent as `'wr'`_
/// - `TSL_SwitchAction_inventory` - _'.iv' command has been specified and is sent as `'inv'`_
/// - `TSL_SwitchAction_barcode` - _'.bc' command has been specified and is sent as `'bar'`_
/// - `TSL_SwitchAction_user` - _a 'user-defined' command has been specified and is sent as `'usr'`_
/// - `TSL_SwitchAction_antennaDefault` - _the antenna default command has been specified and is sent as `'ad'`_
/// - `TSL_SwitchAction_findTag` - _a 'find tag' command has been specified and is sent as `'ft'`_
///
/// When a command includes the '-p' option the `doublePressAction` parameter will be set to the reader's current values
///
@property (nonatomic, readwrite) TSL_SwitchAction doublePressAction;

/// The minimum delay, in the range [1-999], before the single press trigger action repeats
/// Negative values are ignored and the delay is not set (the default value)
@property (nonatomic, readwrite) int singlePressRepeatDelay;

/// The minimum delay, in the range [1-999], before the double press trigger action repeats
/// Negative values are ignored and the delay is not set (the default value)
@property (nonatomic, readwrite) int doublePressRepeatDelay;

///
/// Set to `TSL_TriState_YES` to enable the haptic feedback
/// Set to `TSL_TriState_NO` to disable the haptic feedback
/// Set to `TSL_TriState_NOT_SPECIFIED` to leave the state unchanged
///
/// if `readParameters` is specified then after execution this property will reflect the current state
///
@property (nonatomic, readwrite) TSL_TriState hapticFeedbackEnabled;


/// @name Factory Methods

///
/// Returns a synchronous TSLSwitchActionCommand
///
+(TSLSwitchActionCommand *)synchronousCommand;


/// @name Class methods

///
///@return the minimum valid value for the repeat delay parameter
///
+(int)minimumRepeatDelay;

///
///@return the maximum valid value for the repeat delay parameter
///
+(int)maximumRepeatDelay;

///
/// @name TSL_SwitchAction Helper methods
///

///
/// Parse the given parameter value string and determine the corresponding TSL_SwitchAction
///
///@param value The parameter value as NSString
///@return The TSL_SwitchAction corresponding to the given string. Invalid parameter values return TSL_SwitchAction_NO_CHANGE
///
+(TSL_SwitchAction)switchActionForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_SwitchAction
///
///@param action The TSL_SwitchAction value to be converted
///@return The command parameter value for the given TSL_SwitchAction or nil if invalid
///
+(nullable NSString *)parameterValueForSwitchAction:(TSL_SwitchAction)action;

///
/// Get the description corresponding to the given TSL_SwitchAction
///
///@param action The TSL_SwitchAction value to be converted
///@return The user friendly name for the given TSL_SwitchAction or nil if invalid
///
+(nullable NSString *)descriptionForSwitchAction:(TSL_SwitchAction)action;

///
/// Test the given TSL_SwitchAction for validity
///
///@param action The TSL_SwitchAction value to be tested
///@return YES if the given TSL_SwitchAction is valid otherwise NO
///
+(BOOL)isValidSwitchAction:(TSL_SwitchAction)action;

@end

NS_ASSUME_NONNULL_END
