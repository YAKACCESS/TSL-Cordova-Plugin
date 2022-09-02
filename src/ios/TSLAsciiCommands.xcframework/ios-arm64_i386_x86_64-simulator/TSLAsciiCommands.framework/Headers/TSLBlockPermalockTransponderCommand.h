//
//  TSLBlockPermalockTransponderCommand.h
//
//  Copyright © 2020 Technology Solutions UK Ltd. All rights reserved.
//
#import <TSLAsciiCommands/TSLAllParameters.h>
#import <TSLAsciiCommands/TSLTransponderReceivedDelegate.h>

#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define TSL_FOR_EACH_BLOCK_PERMALOCK_MODE(select)\
\
select( TSL_BlockPermalockMode_NotSpecified = 0,    @"",        @"Not specified"            )\
select( TSL_BlockPermalockMode_Read,                @"rd",     @"The operation will read the Block Permalock state"  )\
select( TSL_BlockPermalockMode_Write,               @"wr",     @"The operation will write the Block Permalock state"  )


#define USE_ENUM(e,p,s) e,

///
/// The mode types
///
typedef enum { TSL_FOR_EACH_BLOCK_PERMALOCK_MODE(USE_ENUM) } TSL_BlockPermalockMode;

#undef USE_ENUM

///
/// A command to perform memory bank locking of one or more transponders
///
@interface TSLBlockPermalockTransponderCommand : TSLAsciiSelfResponderCommandBase <TSLAntennaParametersProtocol, TSLCommandParametersProtocol, TSLQAlgorithmParametersProtocol, TSLQueryParametersProtocol, TSLResponseParametersProtocol, TSLSelectControlParametersProtocol, TSLSelectMaskParametersProtocol, TSLTransponderParametersProtocol, TSLTransponderReceivedDelegate>

/// @name Properties

/// When set to `TSL_TriState_YES` the Select operation is NOT performed
@property (nonatomic, readwrite) TSL_TriState inventoryOnly;

/// The mode of operation
///
/// The `TSL_BlockPermalockMode` enum is used to specify values for the mode parameter.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_BlockPermalockMode_NotSpecified` - _The value has not been specified and the `mode` parameter will not be sent_
/// - `TSL_BlockPermalockMode_Read` - _The operation will read the Block Permalock state_
/// - `TSL_BlockPermalockMode_Write` - _The operation will write the Block Permalock state_
///
@property (nonatomic, readwrite) TSL_BlockPermalockMode mode;

/// The mask indicating the blocks that are (or will be) perma-locked
@property (nonatomic, readwrite, nullable) NSData *mask;

/// The starting address for the mask data, in units of 16 manufacturer defined blocks
@property (nonatomic, readwrite) int offset;

/// Length in words of the data to read or write
@property (nonatomic, readwrite) int length;


///
/// The TSLTransponderDataReceivedBlock
///
/// All transponder responses will invoke this block even when no EPC response is present
///
@property (nonatomic, copy, nullable) TSLTransponderDataReceivedBlock transponderDataReceivedBlock;


/// @name Factory Methods

///
/// Returns a synchronous TSLBlockPermalockTransponderCommand
///
+(TSLBlockPermalockTransponderCommand *)synchronousCommand;


/// @name TSL_BlockPermalockMode helper Methods

///
/// Test the given TSL_BlockPermalockMode for validity
///
///@param mode The TSL_BlockPermalockMode value to be tested
///@return YES if the given TSL_BlockPermalockMode is valid otherwise NO
///
-(BOOL)isValidMode:(TSL_BlockPermalockMode)mode;

///
/// Parse the given parameter value string and determine the corresponding TSL_BlockPermalockMode
///
///@param value The parameter value as NSString
///@return The TSL_BlockPermalockMode corresponding to the given string. Invalid parameter values return TSL_BlockPermalockMode_NotSpecified
///

-(TSL_BlockPermalockMode)modeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_BlockPermalockMode
///
///@param mode The TSL_BlockPermalockMode value to be converted
///@return The command parameter value for the given TSL_BlockPermalockMode or nil if invalid
///
-(nullable NSString *)parameterValueForMode:(TSL_BlockPermalockMode)mode;

///
/// Get the description corresponding to the given TSL_BlockPermalockMode
///
///@param mode The TSL_BlockPermalockMode value to be converted
///@return The user friendly name for the given TSL_BlockPermalockMode or nil if invalid
///
-(nullable NSString *)descriptionForMode:(TSL_BlockPermalockMode)mode;

@end

NS_ASSUME_NONNULL_END
