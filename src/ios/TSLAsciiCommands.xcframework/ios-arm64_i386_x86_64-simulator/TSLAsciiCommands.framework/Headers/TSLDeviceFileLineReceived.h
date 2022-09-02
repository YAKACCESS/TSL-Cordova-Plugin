//
//  TSLDeviceFileLineReceived.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

///
/// The block type to handle device file information received as CRLF delimited lines
///
/// Commands will also invoke this block with line = nil and moreAvailable = NO
/// upon command completion
///
/// @param line - the line received from the device (without line end delimiters) or nil
/// @param moreAvailable - YES if there are more lines coming immediately
///
typedef void(^TSLFileLineReceivedBlock)(NSString * _Nullable line, BOOL moreAvailable);


NS_ASSUME_NONNULL_END
