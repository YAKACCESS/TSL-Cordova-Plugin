//
//  TSLWriteSingleTransponderCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLTransponderMemoryCommandBase.h>
#import <TSLAsciiCommands/TSLAvailabilityMacros.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Protocol for objects wishing to receive asynchronous notification of each transponder received
///
@protocol TSLWriteSingleCommandTransponderReceivedDelegate <NSObject>

///
/// The transponder information received
///
/// @param epc the transponder identifier as hex-encoded, ascii string
/// @param crc the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param index the index value as unsigned short encoded in NSNumber or nil if none
/// @param wordsWritten the number of words successfully written to the transponder as int encoded in NSNumber or nil if none
/// @param moreAvailable YES if there are more transponders to be delivered
///
-(void)transponderReceivedFromWrite:(nullable NSString *)epc crc:(nullable NSNumber *)crc pc:(nullable NSNumber *)pc rssi:(nullable NSNumber *)rssi index:(nullable NSNumber *)index wordsWritten:(nullable NSNumber *)wordsWritten moreAvailable:(BOOL)moreAvailable;

@end


///
/// The block type to handle transponder information received
///
/// @param epc the transponder identifier as hex-encoded, ascii string
/// @param crc the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param index the index value as unsigned short encoded in NSNumber or nil if none
/// @param wordsWritten the number of words successfully written to the transponder as int encoded in NSNumber or nil if none
/// @param moreAvailable YES if there are more transponders to be delivered
typedef void(^TSLWriteSingleTransponderReceivedBlock)(NSString * _Nullable epc, NSNumber * _Nullable crc, NSNumber * _Nullable pc, NSNumber * _Nullable rssi, NSNumber * _Nullable index, NSNumber * _Nullable wordsWritten, BOOL moreAvailable);



///
/// A command to write data to the memory banks of a single transponder only
///
@interface TSLWriteSingleTransponderCommand : TSLTransponderMemoryCommandBase

/// @name Properties

/// The TSLWriteSingleCommandTransponderReceivedDelegate to inform when each transponder is received
@property (weak, nonatomic, readwrite, nullable) id<TSLWriteSingleCommandTransponderReceivedDelegate>transponderReceivedDelegate
TSL_DEPRECATED_MSG_ATTRIBUTE("Use the `transponderDataReceivedBlock` instead");

/// The Block invoked for each transponder received
@property (nonatomic, copy, nullable) TSLWriteSingleTransponderReceivedBlock transponderReceivedBlock
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

/// YES if a transponder responded to the write command. 
@property (nonatomic, readonly) BOOL didAnyTransponderRespond;


/// @name Factory Methods

///
/// Returns a synchronous TSLWriteSingleTransponderCommand
/// (with self as synchronous responder)
///
+(TSLWriteSingleTransponderCommand *)synchronousCommand;

@end

NS_ASSUME_NONNULL_END
