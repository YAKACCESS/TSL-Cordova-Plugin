//
//  TSLLoggerResponder.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommandResponderBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// The block type to handle each received line
///
/// @param line - the received line
///
typedef void(^TSLLoggerBlock)(NSString *line);


///
/// A simple responder that inserts every line it sees, preceded by '>', into the standard log file
/// or invokes a custom action block
///
@interface TSLLoggerResponder : TSLAsciiCommandResponderBase

/// @name Factory Methods

/// @return a TSLLoggerResponder with default configuration
+(TSLLoggerResponder *)defaultResponder;

/// @return a shared TSLLoggerResponder with default configuration
+(TSLLoggerResponder *)sharedResponder;

/// The Block invoked for each response line
@property (nonatomic, copy, nullable) TSLLoggerBlock lineReceivedBlock;

@end

NS_ASSUME_NONNULL_END
