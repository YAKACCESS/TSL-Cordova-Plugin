//
//  TSLAsciiCommandExecutorBase.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TSLAsciiCommands/TSLAsciiCommandExecuting.h>
#import <TSLAsciiCommands/TSLAsciiCommandResponderDelegate.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A base class that implements the responder chain management
///
@interface TSLAsciiCommandExecutorBase : NSObject <TSLAsciiCommandExecuting, TSLAsciiCommandResponderDelegate>

/// Test for presence of the synchronous command responder in the responder chain
@property (nonatomic, readonly) BOOL hasSynchronousResponder;

@end

NS_ASSUME_NONNULL_END
