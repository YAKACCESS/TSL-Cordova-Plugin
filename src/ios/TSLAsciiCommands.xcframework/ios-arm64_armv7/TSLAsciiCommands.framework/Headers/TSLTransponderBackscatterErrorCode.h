//
//  TSLTransponderBackscatterErrorCode.h
//
//  Copyright © 2016 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Use macro to allow the creation of enum, parameter value and descriptive strings that are always in sync
///
#define USE_ENUM(e,p,s) e,

/// Access Error values
#define TSL_FOR_EACH_TRANSPONDER_BACKSCATTER_ERROR_CODE(select)\
\
select( TSL_TransponderBackscatterErrorCode_NotSpecified = 0,                                @"",       @"Not specified"  )\
select( TSL_TransponderBackscatterErrorCode_GeneralError,                                    @"000",    @"General error"  )\
select( TSL_TransponderBackscatterErrorCode_MemoryDoesNotExistOrThePcValueIsNotSupported,    @"003",    @"Memory does not exist or the PC value is not supported"  )\
select( TSL_TransponderBackscatterErrorCode_MemoryIsLockOrPermalocked,                       @"004",    @"Memory is locked or permalocked"  )\
select( TSL_TransponderBackscatterErrorCode_TransponderHasInsufficientPower,                 @"011",    @"Transponder has insufficient power"  )\
select( TSL_TransponderBackscatterErrorCode_TransponderDoesNotSupportErrorSpecificCodes,     @"015",    @"Transponder does not support error specific codes"  )\


///
/// The TransponderBackscatterErrorCode type
///
/// When receiving a response from the reader the values are interpreted as follows:
///
/// - `TSL_TransponderBackscatterErrorCode_NotSpecified` - _The value has not been specified_
/// - `TSL_TransponderBackscatterErrorCode_GeneralError` - _a "General error" error has occurred and has code value `'000'`_
/// - `TSL_TransponderBackscatterErrorCode_MemoryDoesNotExistOrThePcValueIsNotSupported` - _a "Memory does not exist or the PC value is not supported" has occurred and has code value `'003'`_
/// - `TSL_TransponderBackscatterErrorCode_MemoryIsLockOrPermalocked` - _a "Memory is locked or permalocked" error has occurred and has code value `'004'`_
/// - `TSL_TransponderBackscatterErrorCode_TransponderHasInsufficientPower` - _a "Transponder has insufficient power" error has occurred and has code value `'011'`_
/// - `TSL_TransponderBackscatterErrorCode_TransponderDoesNotSupportErrorSpecificCodes` - _a "Transponder does not support error specific codes" error has occurred and has code value `'015'`_
///
typedef enum { TSL_FOR_EACH_TRANSPONDER_BACKSCATTER_ERROR_CODE(USE_ENUM) } TSL_TransponderBackscatterErrorCode;


#undef USE_ENUM


///
/// A helper class for the Backscatter error enum
///
@interface TSLTransponderBackscatterErrorCode : NSObject

///
/// Parse the given parameter value string and determine the corresponding TSL_TransponderBackscatterErrorCode
///
///@param value The parameter value as NSString
///@return The TSL_TransponderBackscatterErrorCode corresponding to the given string. Invalid parameter values return TSL_TransponderBackscatterErrorCode_NotSpecified
///
+(TSL_TransponderBackscatterErrorCode)transponderBackscatterErrorCodeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_TransponderBackscatterErrorCode
///
///@param errorCode The TSL_TransponderBackscatterErrorCode value to be converted
///@return The command parameter value for the given TSL_TransponderBackscatterErrorCode or nil if invalid
///
+(nullable NSString *)parameterValueForTransponderBackscatterErrorCode:(TSL_TransponderBackscatterErrorCode)errorCode;


///
/// Get the description corresponding to the given TSL_TransponderBackscatterErrorCode
///
///@param errorCode The TSL_QuerySelect value to be converted
///@return The user friendly name for the given TSL_QuerySelect or nil if invalid
///

+(nullable NSString *)descriptionForTransponderBackscatterErrorCode:(TSL_TransponderBackscatterErrorCode)errorCode;

///
/// Test the given TSL_TransponderBackscatterErrorCode for validity
///
///@param errorCode The TSL_TransponderBackscatterErrorCode value to be tested
///@return YES if the given TSL_TransponderBackscatterErrorCode is valid otherwise NO
///
+(BOOL)isValidTransponderBackscatterErrorCode:(TSL_TransponderBackscatterErrorCode)errorCode;


@end

NS_ASSUME_NONNULL_END
