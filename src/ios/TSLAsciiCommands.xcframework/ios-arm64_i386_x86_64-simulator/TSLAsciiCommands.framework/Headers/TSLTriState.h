//
//  TSLTriState.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/// The TSL_TriState enum is used to specify values for TSLAsciiCommand parameters.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_TriState_NOT_SPECIFIED` - _The value has not been specified and the corresponding parameter will not be sent_
/// - `TSL_TriState_YES` - _The value has been specified and is sent as `'on'`_
/// - `TSL_TriState_NO` - _The value has been specified and is sent as `'off'`_
///
/// When a command includes the '-p' option TSLAsciiCommand responses will set corresponding parameters as follows:
///
/// - `TSL_TriState_YES` - _The parameter is `'on'`_
/// - `TSL_TriState_NO` - _The parameter is `'off'`_
///
typedef enum
{
    TSL_TriState_NOT_SPECIFIED = 0,
    TSL_TriState_YES,
    TSL_TriState_NO,
}
TSL_TriState;

///
/// Helper class for TSL_TriState enum
///
@interface TSLTriState : NSObject

///
/// @name TSL_TriState helper methods
///

///
/// Parse the given parameter value string and determine the corresponding TSL_TriState
///
///@param value The parameter value as NSString
///@return The TSL_TriState corresponding to the given string. Invalid parameter values return TSL_TriState_NOT_SPECIFIED
///
+(TSL_TriState)stateForParameterValue:(nullable NSString *)value;


///
/// Get the parameter value corresponding to the given TSL_TriState
///
///@param state The TSL_TriState value to be converted
///@return The command parameter value for the given state
///
+(nullable NSString *)parameterValueForState:(TSL_TriState)state;


///
/// Get the description corresponding to the given TSL_TriState
///
///@param state The TSL_TriState value to be converted
///@return The user friendly name for the given TSL_TriState
///
+(nullable NSString *)descriptionForState:(TSL_TriState)state;

@end

NS_ASSUME_NONNULL_END
