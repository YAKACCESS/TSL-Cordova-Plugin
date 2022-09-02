//
//  TSLTimeCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A command to obtain or set the time of the reader's real-time clock
///
///  @see `TSLDateTimeCommand`, `TSLDateCommand`
///
@interface TSLTimeCommand : TSLAsciiSelfResponderCommandBase

/// @name Properties

///
/// Set time to nil to read the device's time
/// Set time to a valid NSDate to set the device's time
///
/// Default value is nil
///
/// *Warning:* Only the time section of the NSDate object is valid
///
@property (nonatomic, readwrite, nullable) NSDate *time;

/// @name Factory Methods

///
/// Returns a synchronous TSLTimeCommand
///
+(TSLTimeCommand *)synchronousCommand;

///
/// Returns a synchronous TSLTimeCommand set to the time of the given NSDate
///
/// @param date The value for the command's `time` property - only the time is used
///
+(TSLTimeCommand *)synchronousCommandWithDate:(NSDate *)date;

@end

NS_ASSUME_NONNULL_END
