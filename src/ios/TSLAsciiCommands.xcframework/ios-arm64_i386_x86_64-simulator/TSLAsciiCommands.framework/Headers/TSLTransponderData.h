//
//  TSLTransponderData.h
//
//  Copyright © 2016 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TSLAsciiCommands/TSLTransponderAccessErrorCode.h>
#import <TSLAsciiCommands/TSLTransponderBackscatterErrorCode.h>

NS_ASSUME_NONNULL_BEGIN


///
/// A class to represent the data received from a Transponder response
///
@interface TSLTransponderData : NSObject

/// The timestamp from the reader
/// Note: the timezone is set to the device's local time zone
@property (nonatomic, readonly, nullable) NSDate *timestamp;

/// The transponder EPC
@property (nonatomic, readonly, nullable) NSString *epc;
/// The transponder CRC
@property (nonatomic, readonly, nullable) NSNumber *crc;
/// The transponder index
@property (nonatomic, readonly, nullable) NSNumber *index;
/// The transponder PC Word
@property (nonatomic, readonly, nullable) NSNumber *pc;
/// The transponder RSSI
@property (nonatomic, readonly, nullable) NSNumber *rssi;
/// The transponder RSSI percentage
@property (nonatomic, readonly, nullable) NSNumber *rssiPercent;
/// The transponder TID data (Impinj fast ID transponders only)
@property (nonatomic, readonly, nullable) NSData *fastTidData;
/// The transponder data from a read command
@property (nonatomic, readonly, nullable) NSData *readData;
/// The transponder QT response (Impinj QT transponders only)
@property (nonatomic, readonly, nullable) NSNumber *qt;
/// The transponder Lock Success response
@property (nonatomic, readonly) BOOL didLock;
/// The transponder Kill Success response
@property (nonatomic, readonly) BOOL didKill;
/// The transponder access error code
@property (nonatomic, readonly) TSL_TransponderAccessErrorCode accessErrorCode;
/// The transponder backscatter error code
@property (nonatomic, readonly) TSL_TransponderBackscatterErrorCode backscatterErrorCode;
/// The number of words written to the transponder from a write command
@property (nonatomic, readonly, nullable) NSNumber *wordsWritten;
/// The transponder phase
@property (nonatomic, readonly, nullable) NSNumber *phase;
/// The transponder channel frequency
@property (nonatomic, readonly, nullable) NSNumber *channelFrequency;
/// The transponder duplicate response
@property (nonatomic, readonly) BOOL isDuplicate;


///
/// Initialises a new instance of the TSLTransponderData class
///
/// @param timestamp - the time when the transponder was seen based on the responses timestamp
/// @param epc - the transponder identifier as hex-encoded, ascii string or nil if none
/// @param crc - the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param index - the index of the transponder as unsigned short encoded in NSNumber or nil if none
/// @param pc - the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi - the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param rssiPercent - the transponders RSSI value as a percentage encoded in NSNumber or nil if none
/// @param fastTidData - the transponders TID bank as NSData or nil if none (Impinj only - requires transponder support)
/// @param readData - the data read from the tag as NSData or nil if none
/// @param qt - the QT response nil if none (Impinj only - requires transponder support)
/// @param didLock - YES if the transponder is the result of a succesful Lock command
/// @param didKill - YES if the transponder is the result of a succesful Kill command
/// @param accessErrorCode - the Access error code
/// @param backscatterErrorCode - the Backscatter error code
/// @param wordsWritten - the number of words successfully written encoded in NSNumber or nil if none
///
/// @param phase - the phase in degrees
/// @param channelFrequency - the channel frequency in Hz
/// @param isDuplicate - YES if the reader reports this transponder as a duplicate

-(TSLTransponderData *) initWithTimestamp:(nullable NSDate *)timestamp
                                      epc:(nullable NSString *)epc
                                      crc:(nullable NSNumber *)crc
                                    index:(nullable NSNumber *)index
                                       pc:(nullable NSNumber *)pc
                                     rssi:(nullable NSNumber *)rssi
                              rssiPercent:(nullable NSNumber *)rssiPercent
                              fastTidData:(nullable NSData *)fastTidData
                                 readData:(nullable NSData *)readData
                                       qt:(nullable NSNumber *)qt
                                  didLock:(BOOL)didLock
                                  didKill:(BOOL)didKill
                          accessErrorCode:(TSL_TransponderAccessErrorCode)accessErrorCode
                     backscatterErrorCode:(TSL_TransponderBackscatterErrorCode)backscatterErrorCode
                             wordsWritten:(nullable NSNumber *)wordsWritten
                                    phase:(nullable NSNumber *)phase
                         channelFrequency:(nullable NSNumber *)channelFrequency
                              isDuplicate:(BOOL)isDuplicate
;

@end


///
/// The block type to handle transponder information received
///
/// @param transponder - the transponder information provided as a TSLTransponderData instance
/// @param moreAvailable - YES if there are more transponders to be delivered
///
typedef void(^TSLTransponderDataReceivedBlock)(TSLTransponderData *transponder, BOOL moreAvailable);

NS_ASSUME_NONNULL_END
