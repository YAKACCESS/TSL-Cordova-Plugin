//
//  TSLSynchronousDispatchResponder.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TSLAsciiCommands/TSLAsciiCommandResponder.h>
#import <TSLAsciiCommands/TSLAsciiCommandResponseNotifying.h>

NS_ASSUME_NONNULL_BEGIN

///
/// This is a special TSLAsciiCommandResponder that is inserted into the responder chain to handle synchronous commands
///
/// This responder uses its `synchronousCommandDelegate` to find the currently executing synchronous command.
/// If such a command exists then this responder forwards calls to `processReceivedLine:moreLinesAvailable:` to
/// the synchronous command's `synchronousCommandResponder`
///
@interface TSLSynchronousDispatchResponder : NSObject <TSLAsciiCommandResponder, TSLAsciiCommandResponseNotifying>

@end

NS_ASSUME_NONNULL_END
