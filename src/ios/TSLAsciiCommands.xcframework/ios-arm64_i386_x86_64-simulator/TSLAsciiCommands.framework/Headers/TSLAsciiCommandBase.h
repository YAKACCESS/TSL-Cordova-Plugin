//
//  TSLAsciiCommandBase.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TSLAsciiCommands/TSLAsciiCommand.h>
#import <TSLAsciiCommands/TSLAsciiCommandResponder.h>

NS_ASSUME_NONNULL_BEGIN


///
/// Base Class for all library TSLAsciiCommands
///
@interface TSLAsciiCommandBase : NSObject <TSLAsciiCommand>

/// Initialise and set the commandName property
///
/// @param name The command name e.g. `'.iv'` for Inventory
///
-(id)initWithCommandName:(NSString *)name;

///
/// Initialise with the given commandName and responder
///
/// Designated initialiser
///
/// This will create a synchronous command
///
/// @param name The command name e.g. `'.iv'` for Inventory
/// @param responder The object to handle synchronous responses for this command
///
-(id)initWithCommandName:(NSString *)name responder:(nullable id<TSLAsciiCommandResponder>) responder;

@end

NS_ASSUME_NONNULL_END
