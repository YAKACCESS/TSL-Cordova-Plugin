//
//  TSLAsciiCommandLibraryResponderBase.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAsciiCommandResponderBase.h>

NS_ASSUME_NONNULL_BEGIN


///
/// Base class for library commands
///
/// This is identical to TSLAsciiCommandResponderBase except, by default, it will only
/// respond to commands containing the TSL_LibraryCommandId
///
@interface TSLAsciiCommandLibraryResponderBase : TSLAsciiCommandResponderBase

/// Enable/disable capture of non-library responses
@property BOOL captureNonLibraryResponses;

@end

NS_ASSUME_NONNULL_END
