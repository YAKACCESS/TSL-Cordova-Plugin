//
//  TSLInventoryCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLCommandParameters.h>
#import <TSLAsciiCommands/TSLTransponderParameters.h>
#import <TSLAsciiCommands/TSLResponseParameters.h>
#import <TSLAsciiCommands/TSLAntennaParameters.h>
#import <TSLAsciiCommands/TSLQueryParameters.h>
#import <TSLAsciiCommands/TSLQAlgorithmParameters.h>
#import <TSLAsciiCommands/TSLSelectMaskParameters.h>
#import <TSLAsciiCommands/TSLSelectControlParameters.h>
#import <TSLAsciiCommands/TSLTransponderReceivedDelegate.h>
#import <TSLAsciiCommands/TSLTransponderData.h>

#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>
#import <TSLAsciiCommands/TSLAvailabilityMacros.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define USE_ENUM(e,p,s) e,

/// Duplicate removal mode values
#define TSL_FOR_EACH_DUPLICATE_REMOVAL_MODE(select)\
\
select( TSL_DuplicateRemovalMode_NotSpecified = 0,  @"",       @"Not specified" )\
select( TSL_DuplicateRemovalMode_Off,               @"off",    @"duplicate removal is off" )\
select( TSL_DuplicateRemovalMode_On,                @"on",     @"duplicate removal is on" )\
select( TSL_DuplicateRemovalMode_Round,             @"rnd",    @"duplicate removal is on and applies only to each inventory round" )\
select( TSL_DuplicateRemovalMode_Report,            @"rep",    @"duplicates are recognised, but not removed, only reported" )\
select( TSL_DuplicateRemovalMode_Clear,             @"clr",    @"The duplicate cache will be cleared" )

///
/// The Duplicate removal mode type
///
typedef enum { TSL_FOR_EACH_DUPLICATE_REMOVAL_MODE(USE_ENUM) } TSL_DuplicateRemovalMode;


/// Audible Alert Mode values
#define TSL_FOR_EACH_AUDIBLE_ALERT_MODE(select)\
\
select( TSL_AudibleAlertMode_NotSpecified = 0,  @"",       @"Not specified" )\
select( TSL_AudibleAlertMode_Per_Round,         @"off",    @"alert sound for each round returning tags" )\
select( TSL_AudibleAlertMode_Per_Tag,           @"on",     @"alert sound for each tag returned" )

///
/// The Audible Alert Mode type
///
typedef enum { TSL_FOR_EACH_AUDIBLE_ALERT_MODE(USE_ENUM) } TSL_AudibleAlertMode;


#undef USE_ENUM

///
/// Protocol for objects wishing to receive asynchronous notification of each transponder received
///
@protocol TSLInventoryCommandTransponderReceivedDelegate <NSObject>

///
/// The transponder information received
///
/// @param epc - the transponder identifier as hex-encoded, ascii string
/// @param crc - the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc - the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi - the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param fastId - the transponders TID bank as NSData or nil if none (Impinj Only - requires transponder support)
/// @param moreAvailable - YES if there are more transponders to be delivered
///
-(void)transponderReceived:(nullable NSString *)epc crc:(nullable NSNumber *)crc pc:(nullable NSNumber *)pc rssi:(nullable NSNumber *)rssi fastId:(nullable NSData *)fastId moreAvailable:(BOOL)moreAvailable;

@end

///
/// The block type to handle transponder information received
///
/// @param epc - the transponder identifier as hex-encoded, ascii string
/// @param crc - the transponder CRC as unsigned short encoded in NSNumber or nil if none
/// @param pc - the transponder program control word as unsigned short encoded in NSNumber or nil if none
/// @param rssi - the transponders RSSI value (in dBm) as int encoded in NSNumber or nil if none
/// @param fastId - the transponders TID bank as NSData or nil if none (Impinj Only - requires transponder support)
/// @param moreAvailable - YES if there are more transponders to be delivered
///
typedef void(^TSLInventoryTransponderReceivedBlock)(NSString * _Nullable epc, NSNumber * _Nullable crc, NSNumber * _Nullable pc, NSNumber * _Nullable rssi, NSData * _Nullable fastId, BOOL moreAvailable);


///
/// A command to perform an inventory
///
/// Configure this command using the properties defined in the parameter protocols this class implements
///
@interface TSLInventoryCommand : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol,TSLAntennaParametersProtocol,TSLTransponderParametersProtocol, TSLResponseParametersProtocol, TSLQueryParametersProtocol, TSLQAlgorithmParametersProtocol, TSLSelectMaskParametersProtocol, TSLSelectControlParametersProtocol, TSLTransponderReceivedDelegate>

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

/// When set to `TSL_TriState_YES`
/// Impinj Only - requires transponder support
@property (nonatomic, readwrite) TSL_TriState useFastId;

/// When set to `TSL_TriState_YES`
/// Impinj Only - requires transponder support
@property (nonatomic, readwrite) TSL_TriState useTagFocus;

/// Indicates the type of duplicate removal to use, if any - supported devices only
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_DuplicateRemovalMode_NotSpecified` - _The value has not been specified and the `duplicateRemoval` parameter will not be sent_
/// - `TSL_DuplicateRemovalMode_Off` - _Off has been specified and is sent as `'off'. Duplicate removal is off_
/// - `TSL_DuplicateRemovalMode_On` - _On has been specified and is sent as `'on'. Duplicate removal is on_
/// - `TSL_DuplicateRemovalMode_Round` - _Round has been specified and is sent as `'rnd'. Duplicate removal is on and applies only to each inventory round_
/// - `TSL_DuplicateRemovalMode_Report` - _Report has been specified and is sent as `'rep'. Duplicates are recognised, but not removed, only reported_
/// - `TSL_DuplicateRemovalMode_Clear` - _Clear has been specified and is sent as `'clr'. Clear the duplicate cache_
///
/// When a command includes the '-p' option the `duplicateRemoval` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_DuplicateRemovalMode duplicateRemoval;

/// the type of Audible alerts to use, if any - supported devices only
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_AudibleAlertMode_NotSpecified` - _The value has not been specified and the `audibleAlertMode` parameter will not be sent_
/// - `TSL_AudibleAlertMode_Per_Round` - _Per Round has been specified and is sent as `'off'. An alert sound is played for each round returning tags_
/// - `TSL_AudibleAlertMode_Per_Tag` - _Per Tag has been specified and is sent as `'on'. An alert sound is played for each tag returned (unless sound already playing)_
///
/// When a command includes the '-p' option the `audibleAlertMode` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_AudibleAlertMode audibleAlertMode;

/// Indicates whether duplicate removal visuals are shown - supported devices only
@property (nonatomic, readwrite) TSL_TriState useDuplicateVisuals;


/// Convenience property returning the 'query session' parameter
@property (nonatomic, readonly, nullable) NSString *sessionModeDescription;

/// The TSLInventoryCommandTransponderReceivedDelegate to inform after each transponder is received
///
/// @see `transponderDataReceivedBlock`
@property (weak, nonatomic, readwrite, nullable) id<TSLInventoryCommandTransponderReceivedDelegate>transponderReceivedDelegate
    TSL_DEPRECATED_MSG_ATTRIBUTE("Use the `transponderDataReceivedBlock` instead");

/// The TSLTransponderReceivedBlock
@property (nonatomic, copy, nullable) TSLInventoryTransponderReceivedBlock transponderReceivedBlock
    TSL_DEPRECATED_MSG_ATTRIBUTE("Use the `transponderDataReceivedBlock` instead");

///
/// The TSLTransponderDataReceivedBlock
///
/// All transponder responses will invoke this block even when no EPC response is present
/// which is something that the other Block and Delegate methods do not do.
///
/// Warning: When a TSLTransponderDataReceivedBlock is supplied this prevents any TSLInventoryTransponderReceivedBlock
/// or the TSLInventoryCommandTransponderReceivedDelegate from being invoked
///
@property (nonatomic, copy, nullable) TSLTransponderDataReceivedBlock transponderDataReceivedBlock;


/// @name Factory Methods

///
/// Returns a synchronous TSLInventoryCommand
///
+(TSLInventoryCommand *)synchronousCommand;

/// @name Enumeration Helper Methods

///
/// Test the given TSL_DuplicateRemovalMode for validity
///
///@param mode The TSL_DuplicateRemovalMode value to be tested
///@return YES if the given TSL_DuplicateRemovalMode is valid otherwise NO
///
-(BOOL)isValidDuplicateRemovalMode:(TSL_DuplicateRemovalMode)mode;

///
/// Parse the given parameter value string and determine the corresponding TSL_DuplicateRemovalMode
///
///@param value The parameter value as NSString
///@return The TSL_DuplicateRemovalMode corresponding to the given string. Invalid parameter values return TSL_DuplicateRemovalMode_NotSpecified
///
-(TSL_DuplicateRemovalMode)duplicateRemovalModeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_DuplicateRemovalMode
///
///@param mode The TSL_DuplicateRemovalMode value to be converted
///@return The command parameter value for the given TSL_DuplicateRemovalMode or nil if invalid
///
-(nullable NSString *)parameterValueForDuplicateRemovalMode:(TSL_DuplicateRemovalMode)mode;

///
/// Get the description corresponding to the given TSL_DuplicateRemovalMode
///
///@param mode The TSL_DuplicateRemovalMode value to be converted
///@return The user friendly name for the given TSL_DuplicateRemovalMode or nil if invalid
///
-(nullable NSString *)descriptionForDuplicateRemovalMode:(TSL_DuplicateRemovalMode)mode;


///
/// Test the given TSL_AudibleAlertMode for validity
///
///@param mode The TSL_AudibleAlertMode value to be tested
///@return YES if the given TSL_AudibleAlertMode is valid otherwise NO
///
-(BOOL)isValidAudibleAlertMode:(TSL_AudibleAlertMode)mode;

///
/// Parse the given parameter value string and determine the corresponding TSL_AudibleAlertMode
///
///@param value The parameter value as NSString
///@return The TSL_AudibleAlertMode corresponding to the given string. Invalid parameter values return TSL_AudibleAlertMode_NotSpecified
///
-(TSL_AudibleAlertMode)audibleAlertModeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_AudibleAlertMode
///
///@param mode The TSL_AudibleAlertMode value to be converted
///@return The command parameter value for the given TSL_AudibleAlertMode or nil if invalid
///
-(nullable NSString *)parameterValueForAudibleAlertMode:(TSL_AudibleAlertMode)mode;

///
/// Get the description corresponding to the given TSL_AudibleAlertMode
///
///@param mode The TSL_AudibleAlertMode value to be converted
///@return The user friendly name for the given TSL_AudibleAlertMode or nil if invalid
///
-(nullable NSString *)descriptionForAudibleAlertMode:(TSL_AudibleAlertMode)mode;

@end

NS_ASSUME_NONNULL_END
