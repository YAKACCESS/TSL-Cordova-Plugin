//
//  TSLWriteAutorunFileCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAvailabilityMacros.h>
#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN


///
/// A command to write commands to the device's autorun file
///
/// This command does not use the library marker and command index because they
/// would be interpreted as part of the command to be added to the autorun file.
/// So, by default, this command will capture non-library responses to allow
/// synchronous commands to execute correctly.
///
TSL_DEPRECATED_MSG_ATTRIBUTE("Use `TSLAutorunCommand` instead")
@interface TSLWriteAutorunFileCommand : TSLAsciiSelfResponderCommandBase

/// @name Properties

///
/// The ASCII command to be added to the autorun file as an NSString
///
/// This property can be set explicitly but is always set when the autorunCommand is set
@property (nonatomic, readwrite, nullable) NSString *value;

///
/// The ASCII command to be added to the autorun file as an `id<TSLAsciiCommand>`
///
/// Setting this will override any value that is in the value property
/// This property is 'set-only' and is not affected by the reader's response
@property (nonatomic, readwrite, nullable) id<TSLAsciiCommand> autorunCommand;


/// @name Factory Methods

///
/// Returns a synchronous TSLWriteAutorunFileCommand
///
+(TSLWriteAutorunFileCommand *)synchronousCommand;

@end

NS_ASSUME_NONNULL_END
