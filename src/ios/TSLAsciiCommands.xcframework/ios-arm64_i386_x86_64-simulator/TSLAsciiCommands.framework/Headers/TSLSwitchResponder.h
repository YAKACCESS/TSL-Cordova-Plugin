//
//  TSLSwitchResponder.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>
#import <TSLAsciiCommands/TSLSwitchStateCommand.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Protocol for objects wishing to receive asynchronous notification of changes in switch state
///
@protocol TSLSwitchResponderStateReceivedDelegate <NSObject>

///
/// Invoked each time switch state information has been received
///
/// This will be invoked from a non-UI thread
///
///@param state The TSL_SwitchState received from the reader
-(void)switchStateReceived:(TSL_SwitchState)state;

@end

///
/// A Responder for asynchronous switch status reports from the reader.
///
/// Switch status reports are controlled using the TSLSwitchActionCommand's asynchronousReportingEnabled parameter.
///
@interface TSLSwitchResponder : TSLAsciiCommandResponderBase

/// The most recently reported switch state
@property (nonatomic, readonly) TSL_SwitchState state;

/// The delegate for new switch state information
@property (weak, nonatomic, readwrite, nullable) id<TSLSwitchResponderStateReceivedDelegate> switchStateReceivedDelegate;

/// @return a TSLSwitchResponder with default configuration
+(TSLSwitchResponder *)defaultResponder;

@end

NS_ASSUME_NONNULL_END
