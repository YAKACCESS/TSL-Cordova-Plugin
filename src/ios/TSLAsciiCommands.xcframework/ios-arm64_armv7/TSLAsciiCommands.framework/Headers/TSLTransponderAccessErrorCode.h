//
//  TSLTransponderAccessErrorCode.h
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
#define TSL_FOR_EACH_TRANSPONDER_ACCESS_ERROR_CODE(select)\
\
select( TSL_TransponderAccessErrorCode_NotSpecified = 0,                @"",       @"Not specified"                     )\
select( TSL_TransponderAccessErrorCode_HandleMismatch,                  @"001",    @"Handle Mismatch"                   )\
select( TSL_TransponderAccessErrorCode_CrcErrorOnTransponderResponse,   @"002",    @"CRC error on transponder response" )\
select( TSL_TransponderAccessErrorCode_NoTransponderReply,              @"003",    @"No transponder reply"              )\
select( TSL_TransponderAccessErrorCode_InvalidPassword,                 @"004",    @"Invalid password"                  )\
select( TSL_TransponderAccessErrorCode_ZeroKillPassword,                @"005",    @"Kill password is zero"             )\
select( TSL_TransponderAccessErrorCode_TransponderLost,                 @"006",    @"Transponder lost"                  )\
select( TSL_TransponderAccessErrorCode_CommandFormatError,              @"007",    @"Command format error"              )\
select( TSL_TransponderAccessErrorCode_ReadCountInvalid,                @"008",    @"Read count invalid"                )\
select( TSL_TransponderAccessErrorCode_OutOfRetries,                    @"009",    @"Out of retries"                    )\
select( TSL_TransponderAccessErrorCode_OperationFailed,                 @"255",    @"Operation failed"                  )\


///
/// The TransponderAccessErrorCode type
///
/// When receiving a response from the reader the values are interpreted as follows:
///
/// - `TSL_TransponderAccessErrorCode_NotSpecified` - _The value has not been specified_
/// - `TSL_TransponderAccessErrorCode_HandleMismatch` - _a "Handle Mismatch" error has occurred and has code value `'001'`_
/// - `TSL_TransponderAccessErrorCode_CrcErrorOnTransponderResponse` - _a "CRC error on transponder response" has occurred and has code value `'002'`_
/// - `TSL_TransponderAccessErrorCode_NoTransponderReply` - _a "No transponder reply" error has occurred and has code value `'003'`_
/// - `TSL_TransponderAccessErrorCode_InvalidPassword` - _an "Invalid password" error has occurred and has code value `'004'`_
/// - `TSL_TransponderAccessErrorCode_ZeroKillPassword` - _a "Kill password is zero" error has occurred and has code value `'005'`_
/// - `TSL_TransponderAccessErrorCode_TransponderLost` - _a "Transponder lost" error has occurred and has code value `'006'`_
/// - `TSL_TransponderAccessErrorCode_CommandFormatError` - _a "Command format" error error has occurred and has code value `'007'`_
/// - `TSL_TransponderAccessErrorCode_ReadCountInvalid` - _a "Read count invalid" error has occurred and has code value `'008'`_
/// - `TSL_TransponderAccessErrorCode_OutOfRetries` - _an "Out of retries" error has occurred and has code value `'009'`_
/// - `TSL_TransponderAccessErrorCode_OperationFailed` - _a "Operation failed" error has occurred and has code value `'255'`_
///
typedef enum { TSL_FOR_EACH_TRANSPONDER_ACCESS_ERROR_CODE(USE_ENUM) } TSL_TransponderAccessErrorCode;


#undef USE_ENUM


///
/// A helper class for the Access error enum
///
@interface TSLTransponderAccessErrorCode : NSObject

///
/// @name TSL_TransponderAccessErrorCode helper methods
///

///
/// Parse the given parameter value string and determine the corresponding TSL_TransponderAccessErrorCode
///
///@param value The parameter value as NSString
///@return The TSL_TransponderAccessErrorCode corresponding to the given string. Invalid parameter values return TSL_TransponderAccessErrorCode_NotSpecified
///
+(TSL_TransponderAccessErrorCode)transponderAccessErrorCodeForParameterValue:(nullable NSString *)value;

///
/// Get the parameter value corresponding to the given TSL_TransponderAccessErrorCode
///
///@param errorCode The TSL_TransponderAccessErrorCode value to be converted
///@return The command parameter value for the given TSL_TransponderAccessErrorCode or nil if invalid
///
+(nullable NSString *)parameterValueForTransponderAccessErrorCode:(TSL_TransponderAccessErrorCode)errorCode;


///
/// Get the description corresponding to the given TSL_TransponderAccessErrorCode
///
///@param errorCode The TSL_QuerySelect value to be converted
///@return The user friendly name for the given TSL_QuerySelect or nil if invalid
///

+(nullable NSString *)descriptionForTransponderAccessErrorCode:(TSL_TransponderAccessErrorCode)errorCode;

///
/// Test the given TSL_TransponderAccessErrorCode for validity
///
///@param errorCode The TSL_TransponderAccessErrorCode value to be tested
///@return YES if the given TSL_TransponderAccessErrorCode is valid otherwise NO
///
+(BOOL)isValidTransponderAccessErrorCode:(TSL_TransponderAccessErrorCode)errorCode;



@end

NS_ASSUME_NONNULL_END
