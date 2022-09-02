//
//  TSLWriteTransponderCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommands.h>

#import <TSLAsciiCommands/TSLTransponderMemoryCommandBase.h>
#import <TSLAsciiCommands/TSLAvailabilityMacros.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Write mode
///
/// Use macro to allow the creation of enum, command parameter and descriptive strings that are always in sync
///
#define TSL_FOR_EACH_WRITE_MODE(select)\
\
select( TSL_WriteMode_NotSpecified = 0,  @"",          @""                 )\
select( TSL_WriteMode_single,            @"s",         @"Single"           )\
select( TSL_WriteMode_block,             @"b",         @"Block"            )


#define USE_ENUM(e,p,s) e,

///
/// The types of Write Modes
///
typedef enum { TSL_FOR_EACH_WRITE_MODE(USE_ENUM) } TSL_WriteMode;

#undef USE_ENUM


///
/// Impinj Extensions: Block write mode
///
/// Use macro to allow the creation of enum, command parameter and descriptive strings that are always in sync
///
#define TSL_FOR_EACH_IMPINJ_BLOCK_WRITE_MODE(select)\
\
select( TSL_ImpinjBlockWriteMode_NotSpecified  = 0, @"",          @""               )\
select( TSL_ImpinjBlockWriteMode_auto,              @"a",         @"Auto"           )\
select( TSL_ImpinjBlockWriteMode_force1,            @"1",         @"Force 1"        )\
select( TSL_ImpinjBlockWriteMode_force2,            @"2",         @"Force 2"        )


#define USE_ENUM(e,p,s) e,

///
/// The types of Impinj Block Write Modes
///
typedef enum { TSL_FOR_EACH_IMPINJ_BLOCK_WRITE_MODE(USE_ENUM) } TSL_ImpinjBlockWriteMode;

#undef USE_ENUM





///
/// Protocol for objects wishing to receive asynchronous notification of each transponder received
///
@protocol TSLWriteCommandTransponderReceivedDelegate <NSObject>

///
/// The transponder information received
///
/// @param epc the transponder identifier as hex-encoded, ascii string
/// @param crc the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param index the index value as unsigned short encoded in NSNumber or nil if none
/// @param aErrorCode the access error code as NSString or nil if none
/// @param bErrorCode the backscatter error code as NSString or nil if none
/// @param wordsWritten the number of words successfully written to the transponder as int encoded in NSNumber or nil if none
/// @param moreAvailable YES if there are more transponders to be delivered
///
-(void)transponderReceivedFromWrite:(nullable NSString *)epc crc:(nullable NSNumber *)crc pc:(nullable NSNumber *)pc rssi:(nullable NSNumber *)rssi index:(nullable NSNumber *)index accessErrorCode:(nullable NSString *)aErrorCode backscatterErrorCode:(nullable NSString *)bErrorCode wordsWritten:(nullable NSNumber *)wordsWritten moreAvailable:(BOOL)moreAvailable;

@end

///
/// The block type to handle transponder information received
///
/// @param epc the transponder identifier as hex-encoded, ascii string
/// @param crc the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param index the index value as unsigned short encoded in NSNumber or nil if none
/// @param accessErrorCode the access error code as NSString or nil if none
/// @param backscatterErrorCode the backscatter error code as NSString or nil if none
/// @param wordsWritten the number of words successfully written to the transponder as int encoded in NSNumber or nil if none
/// @param moreAvailable YES if there are more transponders to be delivered
typedef void(^TSLWriteTransponderReceivedBlock)(NSString * _Nullable epc, NSNumber * _Nullable crc, NSNumber * _Nullable pc, NSNumber * _Nullable rssi, NSNumber * _Nullable index, NSString * _Nullable accessErrorCode, NSString * _Nullable backscatterErrorCode,  NSNumber * _Nullable wordsWritten, BOOL moreAvailable);


///
/// A command to write data to the memory banks of multiple transponders
///
@interface TSLWriteTransponderCommand : TSLTransponderMemoryCommandBase  <TSLQAlgorithmParametersProtocol, TSLQueryParametersProtocol, TSLQtModeParametersProtocol>

/// @name Properties

/// When set to `TSL_TriState_YES` the Select operation is NOT performed
@property (nonatomic, readwrite) TSL_TriState inventoryOnly;

///
/// The write mode to use
///
/// Note: Not all transponders support block write
///
/// The `TSL_WriteMode` enum is used to specify values for the `writeMode` parameter.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_WriteMode_NotSpecified` - _The value has not been specified and the `writeMode` parameter will not be sent_
/// - `TSL_WriteMode_single` - _Single has been specified and is sent as `'s'`_
/// - `TSL_WriteMode_block` - _Block has been specified and is sent as `'b'`_
///
/// When a command includes the '-p' option the `writeMode` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_WriteMode writeMode;

///
/// The block write mode to use when writing to supported transponders
/// (Impinj specific extension)
///
///
/// The `TSL_ImpinjBlockWriteMode` enum is used to specify values for the `impinjBlockWriteMode` parameter.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_ImpinjBlockWriteMode_NotSpecified` - _The value has not been specified and the `duration` parameter will not be sent_
/// - `TSL_ImpinjBlockWriteMode_auto` - _Auto has been specified and is sent as `'a'`_
/// - `TSL_ImpinjBlockWriteMode_force1` - _Force 1 has been specified and is sent as `'1'`_
/// - `TSL_ImpinjBlockWriteMode_force2` - _Force 2 has been specified and is sent as `'2'`_
///
/// When a command includes the '-p' option the `impinjBlockWriteMode` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_ImpinjBlockWriteMode impinjBlockWriteMode;

/// The TSLWriteSingleCommandTransponderReceivedDelegate to inform when each transponder is received
@property (weak, nonatomic, readwrite, nullable) id<TSLWriteCommandTransponderReceivedDelegate>transponderReceivedDelegate
TSL_DEPRECATED_MSG_ATTRIBUTE("Use the `transponderDataReceivedBlock` instead");


/// The Block invoked for each transponder received
@property (nonatomic, copy, nullable) TSLWriteTransponderReceivedBlock transponderReceivedBlock
TSL_DEPRECATED_MSG_ATTRIBUTE("Use the `transponderDataReceivedBlock` instead");

///
/// The TSLTransponderDataReceivedBlock
///
/// All transponder responses will invoke this block even when no EPC response is present
/// which is something that the other Block method does not do.
///
/// Warning: When a TSLTransponderDataReceivedBlock is supplied this prevents any TSLLockTransponderReceivedBlock
/// from being invoked
///
@property (nonatomic, copy, nullable) TSLTransponderDataReceivedBlock transponderDataReceivedBlock;

/// YES if any transponder responded to the write command
@property (nonatomic, readonly) BOOL didAnyTransponderRespond;


/// @name Factory Methods

///
/// Returns a synchronous TSLWriteTransponderCommand
/// (with self as synchronous responder)
///
+(TSLWriteTransponderCommand *)synchronousCommand;


/// @name TSL_WriteMode Helper methods

///
/// Test the given TSL_WriteMode for validity
///
///@param mode The TSL_WriteMode value to be tested
///@return YES if the given TSL_WriteMode is valid otherwise NO
///
+(BOOL)isValidWriteMode:(TSL_WriteMode)mode;

///
/// Parse the given parameter value string and determine the corresponding TSL_WriteMode
///
///@param value The parameter value as NSString
///@return The TSL_WriteMode corresponding to the given string. Invalid parameter values return TSL_WriteMode_NotSpecified
///
+(TSL_WriteMode)writeModeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_WriteMode
///
///@param mode The TSL_WriteMode value to be converted
///@return The command parameter value for the given TSL_WriteMode or nil if invalid
///
+(nullable NSString *)parameterValueForWriteMode:(TSL_WriteMode)mode;

///
/// Get the description corresponding to the given TSL_WriteMode
///
///@param mode The TSL_WriteMode value to be converted
///@return The user friendly name for the given TSL_WriteMode or nil if invalid
///
+(nullable NSString *)descriptionForWriteMode:(TSL_WriteMode)mode;


/// @name TSL_ImpinjBlockWriteMode Helper methods

///
/// Test the given TSL_ImpinjBlockWriteMode for validity
///
///@param mode The TSL_ImpinjBlockWriteMode value to be tested
///@return YES if the given TSL_ImpinjBlockWriteMode is valid otherwise NO
///
+(BOOL)isValidImpinjBlockWriteMode:(TSL_ImpinjBlockWriteMode)mode;

///
/// Parse the given parameter value string and determine the corresponding TSL_ImpinjBlockWriteMode
///
///@param value The parameter value as NSString
///@return The TSL_ImpinjBlockWriteMode corresponding to the given string. Invalid parameter values return TSL_ImpinjBlockWriteMode_NotSpecified
///
+(TSL_ImpinjBlockWriteMode)impinjBlockWriteModeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_ImpinjBlockWriteMode
///
///@param mode The TSL_ImpinjBlockWriteMode value to be converted
///@return The command parameter value for the given TSL_ImpinjBlockWriteMode or nil if invalid
///
+(nullable NSString *)parameterValueForImpinjBlockWriteMode:(TSL_ImpinjBlockWriteMode)mode;

///
/// Get the description corresponding to the given TSL_ImpinjBlockWriteMode
///
///@param mode The TSL_ImpinjBlockWriteMode value to be converted
///@return The user friendly name for the given TSL_ImpinjBlockWriteMode or nil if invalid
///
+(nullable NSString *)descriptionForImpinjBlockWriteMode:(TSL_ImpinjBlockWriteMode)mode;




@end

NS_ASSUME_NONNULL_END
