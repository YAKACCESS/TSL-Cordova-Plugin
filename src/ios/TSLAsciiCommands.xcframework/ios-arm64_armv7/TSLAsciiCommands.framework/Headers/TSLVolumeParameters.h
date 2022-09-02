//
//  TSLVolumeParameters.h
//
//  Copyright © 2020 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TSLAsciiCommands/TSLParametersProtocol.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define USE_ENUM(e,p,s) e,

/// Volume values
#define TSL_FOR_EACH_VOLUME(select)\
\
select( TSL_Volume_NotSpecified = 0,  @"",       @"Not specified"   )\
select( TSL_Volume_Low,               @"low",    @"Low"             )\
select( TSL_Volume_Medium,            @"med",    @"Medium"          )\
select( TSL_Volume_High,              @"hig",    @"High"            )

///
/// The Volume type
///
typedef enum { TSL_FOR_EACH_VOLUME(USE_ENUM) } TSL_Volume;

#undef USE_ENUM

///
/// Parameters for Volume Control operations in commands and responses
///
@protocol TSLVolumeParametersProtocol <NSObject>

/// Specify the volume
///
/// The `TSL_Volume` enum is used to specify values for the `volume` parameter.
///
/// When issuing a command to the reader the values are interpreted as follows:
///
/// - `TSL_Volume_NOT_SPECIFIED` - _The value has not been specified and the `volume` parameter will not be sent_
/// - `TSL_Volume_Low` - _a low tone has been specified and is sent as `'low'`_
/// - `TSL_Volume_Medium` - _a medium tone has been specified and is sent as `'med'`_
/// - `TSL_Volume_High` - _a high tone has been specified and is sent as `'hig'`_
///
/// When a command includes the '-p' option the `volume` parameter will be set to the reader's current value
///
@property (nonatomic, readwrite) TSL_Volume volume;

@end

///
/// Helper class for implementing TSLVolumeParametersProtocol
///
@interface TSLVolumeParameters : NSObject <TSLParametersProtocol>

//
/// @name Volume methods
//

///
/// Parse the given parameter value string and determine the corresponding TSL_Volume
///
///@param value The parameter value as NSString
///@return The TSL_Volume corresponding to the given string. Invalid parameter values return TSL_Volume_NotSpecified
///
+(TSL_Volume)volumeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_Volume
///
///@param volume The TSL_Volume value to be converted
///@return The command parameter value for the given TSL_Volume or nil if invalid
///
+(nullable NSString *)parameterValueForVolume:(TSL_Volume)volume;

///
/// Get the description corresponding to the given TSL_Volume
///
///@param volume The TSL_Volume value to be converted
///@return The user friendly name for the given TSL_Volume or nil if invalid
///
+(nullable NSString *)descriptionForVolume:(TSL_Volume)volume;

///
/// Test the given TSL_Volume for validity
///
///@param volume The TSL_Volume value to be tested
///@return YES if the given TSL_Volume is valid otherwise NO
///
+(BOOL)isValidVolume:(TSL_Volume)volume;

@end


NS_ASSUME_NONNULL_END
