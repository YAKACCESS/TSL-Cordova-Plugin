//
//  TSLShowRegionCommand.h
//
//  Copyright © 2020 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>

NS_ASSUME_NONNULL_BEGIN

//
// A command to determine the Reader's Region
//
@interface TSLShowRegionCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol>

/// The maximum output power for the Reader in dBm
@property (nonatomic, readonly) int maximumOutputPower;

/// The minimum output power for the Reader in dBm
@property (nonatomic, readonly) int minimumOutputPower;

/// The regulatory region identifier
@property (nonatomic, readwrite, nullable) NSString *regionIdentifier;

/// The password (Factory use only)
@property (nonatomic, readwrite, nullable) NSString *password;

///
/// Returns a synchronous TSLShowRegionCommand
///
+(TSLShowRegionCommand *)synchronousCommand;

@end

NS_ASSUME_NONNULL_END
