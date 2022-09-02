//
//  TSLSwitchDoublePressCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A command to programmatically double press the device switch
///
@interface TSLSwitchDoublePressCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol>

/// The duration for the switch press action (0-99).
/// Non-zero values are the time in seconds that the switch press will be maintained.
/// Zero is an infinite press - use the TSLAbort command to release the switch.
@property (nonatomic, readwrite) int duration;

/// @name Factory Methods

///
/// Returns a synchronous TSLSwitchDoublePressCommand
///
+(TSLSwitchDoublePressCommand *)synchronousCommand;

///
/// Returns a synchronous TSLSwitchDoublePressCommand configured for the given duration
/// @param duration The duration for the switch press action (0-99)
///
+(TSLSwitchDoublePressCommand *)synchronousCommandWithDuration:(int)duration;

/// @name Class Methods

///
///@return the maximum valid value for the duration parameter
///
+(int)maximumDuration;


@end

NS_ASSUME_NONNULL_END
