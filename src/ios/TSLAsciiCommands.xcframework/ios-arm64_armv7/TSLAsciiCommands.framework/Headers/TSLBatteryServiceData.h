//
//  TSLBatteryServiceData.h
//
//  Copyright © 2021 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Service Data record for a Reader's battery
///
@interface TSLBatteryServiceData : NSObject

/// The raw ASCII protocol Service Data string
@property (nullable, nonatomic, readwrite) NSString *rawValue;

/// The date the battery was fitted (DD/MM/YY) or nil if not available
@property (nullable, nonatomic, readwrite) NSString *dateFitted;

/// The date of the manufacture of the battery (as week/year) or nil if not available
@property (nullable, nonatomic, readwrite) NSString *dateManufactured;

/// The batch number of the battery or nil if not available
@property (nullable, nonatomic, readwrite) NSString *batchNumber;

/// The serial number of the battery or nil if not available
@property (nullable, nonatomic, readwrite) NSString *serialNumber;

/// Parses the given raw ASCII protocol Service Data string into a TSLBatteryServiceData instance
+( TSLBatteryServiceData *) parse:(NSString *)value;

@end

NS_ASSUME_NONNULL_END

