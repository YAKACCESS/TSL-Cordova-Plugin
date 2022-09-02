//
//  TSLTransponderMemoryCommandBase.h
//
//  Copyright (c) 2013 Technology Solutions UK Ltd. All rights reserved.
//

#import <TSLAsciiCommands/TSLAllParameters.h>
#import <TSLAsciiCommands/TSLTransponderReceivedDelegate.h>

#import <TSLAsciiCommands/TSLAsciiSelfResponderCommandBase.h>

NS_ASSUME_NONNULL_BEGIN


///
/// A base class for read/write commands
///
/// This provides common behaviour, properties and parameters for the read and write commands. Many properties are defined in the parameter protocols this class implements
///
@interface TSLTransponderMemoryCommandBase : TSLAsciiSelfResponderCommandBase <TSLCommandParametersProtocol, TSLDataBankParametersProtocol, TSLAntennaParametersProtocol, TSLResponseParametersProtocol, TSLSelectControlParametersProtocol, TSLSelectMaskParametersProtocol, TSLTransponderParametersProtocol, TSLTransponderReceivedDelegate>

/// @name Properties

///
/// Clears the data from the last transponder seen
///
/// Override this method to clear additional data from derived classes.
/// Ensure that the super class implementation is also called
///
-(void)clearLastTransponder;

@end

NS_ASSUME_NONNULL_END
