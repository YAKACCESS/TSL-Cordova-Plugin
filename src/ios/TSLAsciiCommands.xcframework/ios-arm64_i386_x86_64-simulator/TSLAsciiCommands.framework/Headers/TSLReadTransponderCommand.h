//
//  TSLReadTransponderCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAllParameters.h>

#import <TSLAsciiCommands/TSLTransponderMemoryCommandBase.h>
#import <TSLAsciiCommands/TSLAvailabilityMacros.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Protocol for objects wishing to receive asynchronous notification of each transponder received
///
@protocol TSLReadCommandTransponderReceivedDelegate <NSObject>

///
/// The transponder information received
///
/// @param epc - the transponder identifier as hex-encoded, ascii string
/// @param crc - the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc - the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi - the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param index - the index value as unsigned short encoded in NSNumber or nil if none
/// @param data - the data retrieved from the transponder or nil if none
/// @param moreAvailable - YES if there are more transponders to be delivered
///
-(void)transponderReceivedFromRead:(nullable NSString *)epc crc:(nullable NSNumber *)crc pc:(nullable NSNumber *)pc rssi:(nullable NSNumber *)rssi index:(nullable NSNumber *)index data:(nullable NSData *)data moreAvailable:(BOOL)moreAvailable;

@end

///
/// The block type to handle transponder information received
///
/// @param epc - the transponder identifier as hex-encoded, ascii string
/// @param crc - the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc - the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi - the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param index - the index value as unsigned short encoded in NSNumber or nil if none
/// @param data - the data retrieved from the transponder or nil if none
/// @param moreAvailable - YES if there are more transponders to be delivered
///
typedef void(^TSLReadTransponderReceivedBlock)(NSString * _Nullable epc, NSNumber * _Nullable crc, NSNumber * _Nullable pc, NSNumber * _Nullable rssi, NSNumber * _Nullable index, NSData * _Nullable data, BOOL moreAvailable);



///
/// A command to read data from the memory banks of one or more transponders
///
@interface TSLReadTransponderCommand : TSLTransponderMemoryCommandBase <TSLQAlgorithmParametersProtocol, TSLQueryParametersProtocol, TSLQtModeParametersProtocol>

/// @name Properties

/// When set to `TSL_TriState_YES` the Select operation is NOT performed
@property (nonatomic, readwrite) TSL_TriState inventoryOnly;

/// When set to `TSL_TriState_YES` only the tag with the strongest response is returned
@property (nonatomic, readwrite) TSL_TriState filterStrongest;

/// Control the inclusion of the EPC identifier value in reader responses
@property (nonatomic, readwrite) TSL_TriState includeEPC;

/// Control the inclusion of the phase value in reader responses
@property (nonatomic, readwrite) TSL_TriState includePhase;

/// Control the inclusion of the channel frequency value in reader responses
@property (nonatomic, readwrite) TSL_TriState includeChannelFrequency;

/// The TSLReadCommandTransponderReceivedDelegate to inform when each transponder is received
@property (nonatomic, readwrite, nullable) id<TSLReadCommandTransponderReceivedDelegate>transponderReceivedDelegate
TSL_DEPRECATED_MSG_ATTRIBUTE("Use the `transponderDataReceivedBlock` instead");

/// The Block invoked for each transponder received
@property (nonatomic, copy, nullable) TSLReadTransponderReceivedBlock transponderReceivedBlock
TSL_DEPRECATED_MSG_ATTRIBUTE("Use the `transponderDataReceivedBlock` instead");

///
/// The TSLTransponderDataReceivedBlock
///
/// All transponder responses will invoke this block even when no EPC response is present
/// which is something that the other Block method does not do.
///
/// Warning: When a TSLTransponderDataReceivedBlock is supplied this prevents any other delegate or block methods
/// from being invoked
///
@property (nonatomic, copy, nullable) TSLTransponderDataReceivedBlock transponderDataReceivedBlock;


/// @name Factory Methods

///
/// Returns a synchronous TSLReadTransponderCommand
///
+(TSLReadTransponderCommand *)synchronousCommand;


@end

NS_ASSUME_NONNULL_END
