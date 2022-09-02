//
//  TSLBatteryHealthData.h
//
//  Copyright © 2021 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

///
/// Health Data record for a Reader's battery
///
@interface TSLBatteryHealthData : NSObject

/// The raw ASCII protocol Health Data string
@property (nullable, nonatomic, readwrite) NSString *rawValue;

/// Gets the battery style (the type of battery)
///
/// Known types include:
///   - PH  - _Battery is a Power Handle_
///   - SB  - _1166 battery_
///   - XL  - _Standard Varta XL battery (e.g. 1128 / IH21)_
@property (nullable, nonatomic, readwrite) NSString *batteryStyle;

/// Gets the reported battery voltage in mV or nil if not available
@property (nullable, nonatomic, readwrite) NSNumber *voltage;

/// Gets the number of times the battery has been charged or nil if not available
@property (nullable, nonatomic, readwrite) NSNumber *cycleCount;

/// Gets the (original) design capacity of the battery in mAh or nil if not available
@property (nullable, nonatomic, readwrite) NSNumber *designCapacity;

/// Gets the predicted capacity of the battery when fully charged in mAh or nil if not available
@property (nullable, nonatomic, readwrite) NSNumber *fullyChargedCapacity;

/// Gets the remaining capacity of the current charge of the battery in mAh or nil if not available
///
/// To calculate remaining charge as a percentage use:
///   100 * (RemainingCapacity / FullyChargedCapacity)
@property (nullable, nonatomic, readwrite) NSNumber *remainingCapacity;

/// Gets the state of health (%) of the battery or nil if not available
@property (nullable, nonatomic, readwrite) NSNumber *stateOfHealth;

/// Parses the given raw ASCII protocol Health Data string into a TSLBatteryHealthData instance
+(TSLBatteryHealthData *) parse:(NSString *)value;


@end

NS_ASSUME_NONNULL_END
