//
//  TSLExecuteAutorunFileCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>
#import <TSLAsciiCommands/TSLAvailabilityMacros.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A command to execute the Autorun file
///
TSL_DEPRECATED_MSG_ATTRIBUTE("Use `TSLAutorunCommand` instead")
@interface TSLExecuteAutorunFileCommand : TSLAsciiSelfResponderCommandBase

///
/// Returns a synchronous TSLExecuteAutorunFileCommand
///
+(TSLExecuteAutorunFileCommand *)synchronousCommand;

@end

NS_ASSUME_NONNULL_END
