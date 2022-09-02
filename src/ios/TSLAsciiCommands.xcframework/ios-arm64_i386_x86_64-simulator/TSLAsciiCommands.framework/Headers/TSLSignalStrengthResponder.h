//
//  TSLSignalStrengthResponder.h
//
//  Copyright © 2020 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommandResponder.h>

NS_ASSUME_NONNULL_BEGIN

///
/// The block type invoked for each signal strength value received
/// The units for this value are specified by the implementation
///
/// @param level - the new signal strength or nil if nothing read this time
///
typedef void(^TSLSignalStrengthReceivedBlock)(NSNumber * _Nullable level);

///
/// Class to capture signal strength responses asynchronously
///
@interface TSLSignalStrengthResponder : NSObject <TSLAsciiCommandResponder>

/// The delegate block for the raw signal strength responses in dBm
/// Note: This method will be called on a non-UI thread
@property (nonatomic, readwrite, nullable) TSLSignalStrengthReceivedBlock rawSignalStrengthReceivedBlock;

/// The delegate block for the percentage signal strength responses in the range 0 - 100%
/// Note: This method will be called on a non-UI thread
@property (nonatomic, readwrite, nullable) TSLSignalStrengthReceivedBlock percentageSignalStrengthReceivedBlock;

@end

NS_ASSUME_NONNULL_END
