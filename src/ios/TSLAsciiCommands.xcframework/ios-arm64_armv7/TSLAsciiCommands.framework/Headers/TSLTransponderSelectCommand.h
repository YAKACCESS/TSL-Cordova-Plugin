//
//  TSLTransponderSelectCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A command to set the state of transponders
///
/// Notes:
///  - See protocols for properties
///  - This command is for use with persistent session targets only
///  - 1128 Reader only
///
@interface TSLTransponderSelectCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol, TSLAntennaParametersProtocol, TSLSelectControlParametersProtocol, TSLSelectMaskParametersProtocol>


/// @name Factory Methods

///
/// Returns a synchronous TSLTransponderSelectCommand
///
+(TSLTransponderSelectCommand *)synchronousCommand;


@end

NS_ASSUME_NONNULL_END
