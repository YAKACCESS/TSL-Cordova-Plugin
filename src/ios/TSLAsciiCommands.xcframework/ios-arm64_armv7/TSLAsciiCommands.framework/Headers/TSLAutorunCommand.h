//
//  TSLAutorunCommand.h
//
//  Copyright © 2020 Technology Solutions UK Ltd. All rights reserved.
//
#import <TSLAsciiCommands/TSLAsciiCommands.h>

#import <TSLAsciiCommands/TSLCommandParameters.h>
#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

/// The permitted file index values
typedef enum
{
    /// The index for internal Autorun file - limited to 256 bytes, if available
    TSL_FileIndex_Internal = 0,

    /// The index for SD Card Autorun storage, if fitted
    TSL_FileIndex_SdCard,

    TSL_FileIndex_MaxIndex
}
TSL_FileIndex;

///
/// A command to manipulate the device's autorun files
///
/// File commands require that they are the first responder in the chain to consume lines
/// So, to run this command synchronously requires that the Synchronous responder is the first (consuming) responder in the chain
/// (e.g. TSLLoggerResponder can come before it as it does NOT consume the lines it sees)
///
/// @warning The lines received from the device are not accumulated in the response property
/// and must be handled via the fileLineReceivedBlock
///
@interface TSLAutorunCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol>

/// @name Properties

/// The TSL_FileIndex of the autorun file that is affected by this command
@property (nonatomic, readwrite) int fileIndex;

/// Indicates whether the current Autorun file will be read
@property (nonatomic, readwrite) TSL_TriState readAutorun;

/// Indicates whether the current Autorun file will be executed
@property (nonatomic, readwrite) TSL_TriState executeAutorun;

/// Set to TSL_DeleteConfirmation_YES to delete the log file from the device
@property (nonatomic, readwrite) TSL_DeleteConfirmation deleteFile;

/// The block executed for each file line received
@property (nonatomic, copy, nullable) TSLFileLineReceivedBlock fileLineReceivedBlock;

/// If set then this will be written to the current Autorun file UNLESS the autorunCommand property has been set
/// Also, if set this will prevent the Read and Execute operations
@property (nonatomic, readwrite, nullable) NSString *value;

///
/// The ASCII command to be added to the autorun file as an `id<TSLAsciiCommand>`
///
/// If set then this will be written to the current Autorun file even if the Value property has been set
/// Also, if set this will prevent the Read and Execute operations
@property (nonatomic, readwrite, nullable) id<TSLAsciiCommand> autorunCommand;




///
/// Returns a synchronous TSLAutorunCommand
///
+(TSLAutorunCommand *)synchronousCommand;



@end

NS_ASSUME_NONNULL_END
