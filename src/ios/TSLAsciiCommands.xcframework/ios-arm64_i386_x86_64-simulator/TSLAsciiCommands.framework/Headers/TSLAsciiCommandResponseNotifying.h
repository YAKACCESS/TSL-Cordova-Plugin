//
//  TSLAsciiCommandResponseNotifying.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

///
/// The Block type for response lifecycle event handlers
///
typedef void(^TSLCommandResponseLifecycleBlock)(void);



///
/// The protocol for notifying the command response lifecycle events
///
@protocol TSLAsciiCommandResponseNotifying <NSObject>

/// Invoked when the command response began
@property (nonatomic, copy, nullable) TSLCommandResponseLifecycleBlock responseBeganBlock;

/// Invoked when the command response ended
@property (nonatomic, copy, nullable) TSLCommandResponseLifecycleBlock responseEndedBlock;


@end

NS_ASSUME_NONNULL_END
