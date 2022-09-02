//
//  TSLAbortCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A command to terminate the current command and any pending commands. It also stops any software switch presses that are in progress.
///
@interface TSLAbortCommand : TSLAsciiSelfResponderCommandBase

/// @name Factory Methods

///
/// Returns a synchronous TSLAbortCommand
///
+(TSLAbortCommand *)synchronousCommand;

@end

NS_ASSUME_NONNULL_END
