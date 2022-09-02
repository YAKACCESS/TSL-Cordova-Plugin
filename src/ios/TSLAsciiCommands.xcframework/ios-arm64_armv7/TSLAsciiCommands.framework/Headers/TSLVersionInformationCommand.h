//
//  TSLVersionInformationCommand.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN

///
/// A command to query the reader for version information
///
@interface TSLVersionInformationCommand : TSLAsciiSelfResponderCommandBase

/// @name Properties

/// The Manufacturer name retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *manufacturer;

/// The Unit Serial number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *serialNumber;

/// The Unit Firmware version number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *firmwareVersion;

/// The Unit bootloader version number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *bootloaderVersion;

/// The Radio Serial number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *radioSerialNumber;

/// The Radio Firmware version number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *radioFirmwareVersion;

/// The UHF API version number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *uhfApiVersion;

/// The Radio Bootloader version number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *radioBootloaderVersion;

/// The Antenna Serial number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *antennaSerialNumber;

/// The Protocol version number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *asciiProtocol;

/// The Bluetooth address retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *bluetoothAddress;

/// The Bluetooth Firmware Version retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *bluetoothFirmwareVersion;

/// The Power Handle Bootloader version number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *powerHandleBootloaderVersion;

/// The Power Handle Firmware Version retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *powerHandleFirmwareVersion;

/// The Power Handle Serial number retrieved from the reader
@property (nonatomic, readonly, nullable) NSString *powerHandleSerialNumber;



/// @name Factory Methods

///
/// Returns a synchronous TSLVersionInformationCommand with a default TSLVersionInformationCommandResponder
///
+(TSLVersionInformationCommand *)synchronousCommand;



@end

NS_ASSUME_NONNULL_END
