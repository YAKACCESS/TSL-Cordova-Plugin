//
//  TSLSwitchSinglePressCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>

NS_ASSUME_NONNULL_BEGIN


///
/// A command to programmatically press the device switch
///
@interface TSLSwitchSinglePressCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol>

/// The duration for the switch press action (0 - maximumDuration)
/// Non-zero values are the time in seconds that the switch press will be maintained
/// Zero is an infinite press - use the TSLAbort command to cancel
@property (nonatomic, readwrite) int duration;

///@name Factory methods

///
/// Returns a synchronous TSLSwitchSinglePressCommand
///
+(TSLSwitchSinglePressCommand *)synchronousCommand;

///
/// Returns a synchronous TSLSwitchSinglePressCommand configured for the given duration
/// @param duration The duration for the switch press action (0-99)
///
+(TSLSwitchSinglePressCommand *)synchronousCommandWithDuration:(int)duration;


///@name Class methods

///
///@return the maximum valid value for the duration parameter
///
+(int)maximumDuration;


@end

NS_ASSUME_NONNULL_END
