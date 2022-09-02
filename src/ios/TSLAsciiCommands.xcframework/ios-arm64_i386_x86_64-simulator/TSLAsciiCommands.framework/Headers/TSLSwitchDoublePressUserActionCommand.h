//
//  TSLSwitchDoublePressUserActionCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A command to configure the user-defined, single-press switch action
///
@interface TSLSwitchDoublePressUserActionCommand : TSLAsciiSelfResponderCommandBase

///
/// The ASCII command to be executed when the switch is double pressed as an NSString
///
/// Set this and actionCommand to nil (the default) to read the current action string.
/// This property can be set explicitly but is always set when the actionCommand is set
@property (nonatomic, readwrite, nullable) NSString *value;

/// The command to be executed when the switch is double pressed as an `id<TSLAsciiCommand>`.
///
/// Setting this will override any value that is in the value property.
/// This property is 'set-only' and is not affected by the reader's response.
@property (nonatomic, readwrite, nullable) id<TSLAsciiCommand> actionCommand;

/// @name Factory Methods

///
/// Returns a synchronous TSLSwitchDoublePressUserActionCommand
///
+(TSLSwitchDoublePressUserActionCommand *)synchronousCommand;

@end

NS_ASSUME_NONNULL_END
