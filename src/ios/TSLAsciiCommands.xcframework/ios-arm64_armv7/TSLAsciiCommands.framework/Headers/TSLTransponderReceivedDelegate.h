//
//  TSLTransponderReceivedDelegate.h
//
//  Copyright © 2016 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TSLAsciiCommands/TSLTransponderData.h>

NS_ASSUME_NONNULL_BEGIN

///
/// The protocol for classes that provide a per-transponder response using TSLTransponderData instances
///
@protocol TSLTransponderReceivedDelegate <NSObject>

///
/// Delegate method invoked for each transponder received
///
/// Note: this method will be called on a non-UI thread
///
/// @param transponder - a transponder response (from an Inventory, Read, Write, Lock or Kill command)
/// @param moreAvailable - NO if there are no more transponders in the command response
///
-(void)transponderReceived: (TSLTransponderData *)transponder moreAvailable:(BOOL) moreAvailable;

@end

NS_ASSUME_NONNULL_END
