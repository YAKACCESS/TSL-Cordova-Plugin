//
//  "TSLConstants.h"
//
//  Copyright (c) 2012 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


// These are the limits of the changes that can be made to the power output but not all Readers support the full range
#define TSL_MIN_CARRIER_POWER 2
#define TSL_MAX_CARRIER_POWER 30

/// This string is inserted into every command issued by the library
extern NSString *TSL_LibraryCommandId;

/// The key for the last accessory used by the app
extern NSString * const TSL_lastAccessorySerialNumberKey;

NS_ASSUME_NONNULL_END

