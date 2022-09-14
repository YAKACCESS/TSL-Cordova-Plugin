/********* BluetoothScanner.m Cordova Plugin Implementation *******/

#import "TSLScanner.h"



@implementation TSLScanner

    static NSString *const DEVICE_IS_ALREADY_CONNECTED = @"Device is already connected.";
    static NSString *const DEVICE_IS_NOT_CONNECTED = @"Device is not connected.";

    TSLBarcodeCommand *_barcodeResponder;
    TSLInventoryCommand *_inventoryResponder;
    TSLInventoryCommand *_inventorySearchResponder;

    CDVInvokedUrlCommand *_asyncCommand;

    CDVPluginResult *_asyncPluginResult = nil;
    CDVPluginResult *_asyncSearchPluginResult = nil;

    NSObject<CDVCommandDelegate>* subsCmdDelegate;

- (TSLAsciiCommander*) getCommander
{
	if (self.commander == nil){
		self.commander = [[TSLAsciiCommander alloc] init];
	}
	return self.commander;
}

- (void)connect:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
    CDVPluginResult* pluginResult = nil;
    NSString* deviceName = [command.arguments objectAtIndex:1];

    if (![deviceName isKindOfClass:[NSNull class]] && ((deviceName != nil) && [deviceName length] > 0)) {
			  EAAccessory *accessory = nil;
		  	TSLAsciiCommander* commander = [self getCommander];
				NSString* connectionMsg = @"";

				if([commander isConnected]){

						accessory = commander.connectedAccessory;
						if([deviceName isEqualToString:accessory.name] || [deviceName isEqualToString:accessory.serialNumber]){
                            connectionMsg = DEVICE_IS_ALREADY_CONNECTED;
						}
						else{
							connectionMsg = [@"Already another device is in use, please disconnect first " stringByAppendingString:deviceName];
						}
                    
						pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:connectionMsg];
				}
				
                if(![commander isConnected]){
								
                    NSArray* _currentAccessories = [[EAAccessoryManager sharedAccessoryManager] connectedAccessories];
                    for (EAAccessory *obj in _currentAccessories)
                    {
                        if([deviceName isEqualToString:obj.name] || [deviceName isEqualToString:obj.serialNumber]){
                            accessory = obj;
                        }
                    }
					
                    if(!accessory){
                        connectionMsg = [@"Device not found " stringByAppendingString:deviceName];
                        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:connectionMsg];
                    }
					
                    if(accessory){
                        self.scanPower = -1;
                        NSString* echo = [commander connect:accessory] ? @"true" : @"false";
										 connectionMsg = echo;//[@"Trying to connect " stringByAppendingString:deviceName];
										 // BOOL connected = [commander isConnected];
										 // echo = connected ? @"CONNECTED" : @"NOT-CONNECTED";
                     
                    if([commander isConnected]){
                        [self removeAsyncAndAddSyncResponder];
                        TSLVersionInformationCommand* versionInformationCommand = [TSLVersionInformationCommand synchronousCommand];
                        [commander executeCommand:versionInformationCommand];
                        
                        NSString *connectedDevice = versionInformationCommand.manufacturer;
                       
                        if( ([connectedDevice rangeOfString:@"TSL" options:NSCaseInsensitiveSearch].length > 0) || ([connectedDevice rangeOfString:@"Technology Solutions" options:NSCaseInsensitiveSearch].length  >0 )){
                         
                            TSLInventoryCommand *invCommand = [TSLInventoryCommand synchronousCommand];;
                            invCommand.takeNoAction = TSL_TriState_YES;
                            invCommand.includeEPC = TSL_TriState_YES;
                            invCommand.includeTransponderRSSI = TSL_TriState_YES;
                            [commander executeCommand:invCommand];
                            [self removeSyncAndAddAsyncResponder];
                            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:connectionMsg];
                        }else{
                            [commander disconnect];
                            connectionMsg =@"Not a recognised device";
                            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR  messageAsString:connectionMsg];
                        }
                    }
                }
            }
     } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)isConnected:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
    CDVPluginResult* pluginResult = nil;
    NSString* echo = @"n/a";
    if (command != nil) {
        TSLAsciiCommander* commander = [self getCommander];
        echo = [commander isConnected] ? @"true" : @"false";
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
    }
    else{
        echo = @"false";
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
    }

    [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)disconnect:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
    CDVPluginResult* pluginResult = nil;
    NSString* disconnectMsg = @"n/a";
    TSLAsciiCommander* commander = [self getCommander];
    if (command != nil && [commander isConnected]) {
        [self removeAsyncResponder];
        _inventoryResponder = nil;
        _barcodeResponder = nil;
        _asyncPluginResult=nil;
        _asyncCommand = nil;
        [commander disconnect];
        self.scanPower = -1;
        disconnectMsg = @"true";
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:disconnectMsg];
    }
    else {
        disconnectMsg = @"No connection exist to disconnect.";
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:disconnectMsg];
    }
    [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getDeviceInfo:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
		CDVPluginResult* pluginResult = nil;

		if (command != nil) {
            
			TSLAsciiCommander* commander = [self getCommander];
			[self removeAsyncAndAddSyncResponder];
			EAAccessory *accessory = nil;
			NSString *status = @"true";
			NSString *errorMsg = @"";

			if([commander isConnected]){
                TSLVersionInformationCommand* versionInformationCommand = [TSLVersionInformationCommand synchronousCommand];
                [commander executeCommand:versionInformationCommand];

                TSLBatteryStatusCommand* batteryStatusCommand = [TSLBatteryStatusCommand synchronousCommand];
                [commander executeCommand:batteryStatusCommand];

                TSLInventoryCommand* invCommand = [TSLInventoryCommand synchronousCommand];
                invCommand.takeNoAction = TSL_TriState_YES;
                invCommand.includeEPC = TSL_TriState_YES;
                invCommand.includeTransponderRSSI = TSL_TriState_YES;
                invCommand.captureNonLibraryResponses = YES;
                invCommand.readParameters = YES;
                [commander executeCommand:invCommand];

                accessory = commander.connectedAccessory;

                NSMutableDictionary *infoDict = [[NSMutableDictionary alloc] init];
                [infoDict setObject:versionInformationCommand.serialNumber forKey:@"deviceName"];

                [infoDict setObject:[NSNumber numberWithInt:[batteryStatusCommand batteryLevel]] forKey:@"batteryLevel"];
                [infoDict setObject:@"n/a" forKey:@"batteryStatus"];
                [infoDict setObject:accessory.hardwareRevision forKey:@"hardwareVersion"];
                [infoDict setObject:versionInformationCommand.firmwareVersion forKey:@"firmwareVersion"];
                [infoDict setObject:versionInformationCommand.manufacturer forKey:@"manufacturer"];
                [infoDict setObject:versionInformationCommand.serialNumber forKey:@"serialNumber"];
                [infoDict setObject:[NSNumber numberWithInt:[TSLInventoryCommand minimumOutputPower]] forKey:@"antennaMin"];
                [infoDict setObject:[NSNumber numberWithInt:[TSLInventoryCommand maximumOutputPower]] forKey:@"antennaMax"];
                [infoDict setObject:[NSNumber numberWithInt:self.scanPower] forKey:@"pScanPower"];
                [infoDict setObject:[NSNumber numberWithInt:invCommand.outputPower] forKey:@"dScanPower"];
                
                NSDictionary *dict = @{@"data" : infoDict, @"errorMsg" : errorMsg, @"status" : status};
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
			}
			else {
				status = @"false";
				errorMsg = @"Device not connected.";
				NSDictionary *dict = @{@"data" : [[NSMutableArray alloc] init], @"errorMsg" : errorMsg, @"status" : status};

                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:dict];
			}
		}
		[delegate sendPluginResult:pluginResult callbackId:command.callbackId];
		[self removeSyncAndAddAsyncResponder];
}

- (void)scanRFIDs:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
    __block CDVPluginResult* pluginResult = nil;
    bool useAscii = FALSE;//[[command.arguments objectAtIndex:0] boolValue];

    TSLAsciiCommander* commander = [self getCommander];
    NSString *status = @"true";
    NSString *errorMsg = @"";
    if ([commander isConnected]) {
            
        [self removeAsyncAndAddSyncResponder];

        // Add the inventory responder to the commander's responder chain
        TSLInventoryCommand *invCommand = [TSLInventoryCommand synchronousCommand];
  
        invCommand.includeDateTime = TSL_TriState_YES;
        invCommand.includeEPC = TSL_TriState_YES;
        invCommand.includeIndex = TSL_TriState_YES;
        invCommand.includePC = TSL_TriState_YES;
        invCommand.includeChecksum = TSL_TriState_YES;
        invCommand.includeTransponderRSSI = TSL_TriState_YES;

        invCommand.takeNoAction = TSL_TriState_NO;
        //invCommand.includeEPC = TSL_TriState_YES;
        //invCommand.includeTransponderRSSI = TSL_TriState_YES;
        //invCommand.useFastId = self.fastIdSwitch.isOn ? TSL_TriState_YES : TSL_TriState_NO;

        if(self.scanPower > -1) {
            invCommand.outputPower = self.scanPower;
        }
    
        // Pulling the Reader trigger will generate inventory responses that are not from the library.
        // To ensure these are also seen requires explicitly requesting handling of non-library command responses
        invCommand.captureNonLibraryResponses = YES;
    
        NSMutableArray *dataArray = [[NSMutableArray alloc] init];

        invCommand.transponderDataReceivedBlock = ^(TSLTransponderData *transponder, BOOL moreAvailable)
        {
            NSString* epcVal = transponder.epc;
            if(useAscii){
                epcVal = [self getAscii:epcVal];
            }
            NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
            [resultMessage setObject:@"rfid" forKey:@"type"];
            [resultMessage setObject:epcVal forKey:@"id"];
            [resultMessage setObject:(transponder.rssi == nil ) ? @"n/a" : [NSString stringWithFormat:@"%3d", transponder.rssi.intValue] forKey:@"RSSI"];
            [dataArray addObject:resultMessage];
        };
        
        [commander executeCommand:invCommand];

        NSDictionary *dict = @{@"data" : dataArray, @"errorMsg" : errorMsg, @"status" : status};
        
//#define _SHOWJSON
#ifdef _SHOWJSON //used so we can print out the json for debugging if needed.
        NSError *error = nil;
        NSString *jsonMsg = nil;
        if ([NSJSONSerialization isValidJSONObject:dict])
        {
            NSData *json = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:&error];
            if (json != nil && error == nil)
            {
                jsonMsg = [[NSString alloc] initWithData:json encoding:NSASCIIStringEncoding];
            }
        }
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:jsonMsg];
         
#else
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
#endif
    }
    else {
            
        status = @"false";
        errorMsg = @"Device not connected.";
        NSDictionary *dict = @{@"data" : [[NSMutableArray alloc] init], @"errorMsg" : errorMsg, @"status" : status};
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:dict];
    }
        
    [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
    [self removeSyncAndAddAsyncResponder];

}

- (void)search:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
    NSString* tagID = [command.arguments objectAtIndex:0];
    bool useAscii = FALSE;//[[command.arguments objectAtIndex:1] boolValue];

    __block CDVPluginResult* pluginResult = nil;
    TSLAsciiCommander* commander = [self getCommander];
    NSString *status = @"true";
    NSString *errorMsg = @"";
 
    if (tagID != nil && [tagID length] > 0 && [commander isConnected]) {
        
        [self removeAsyncAndAddSyncResponder];
        // Add the inventory responder to the commander's responder chain
        TSLInventoryCommand *invCommand = [TSLInventoryCommand synchronousCommand];;
        invCommand.includeDateTime = TSL_TriState_YES;
        invCommand.includeEPC = TSL_TriState_YES;
        invCommand.includeIndex = TSL_TriState_YES;
        invCommand.includePC = TSL_TriState_YES;
        invCommand.includeChecksum = TSL_TriState_YES;
        invCommand.includeTransponderRSSI = TSL_TriState_YES;

        invCommand.takeNoAction = TSL_TriState_NO;

        if(self.scanPower > -1) {
            invCommand.outputPower = self.scanPower;
        }

        // Add self as the transponder delegate
        invCommand.captureNonLibraryResponses = YES;

        NSMutableArray *dataArray = [[NSMutableArray alloc] init];
        invCommand.transponderDataReceivedBlock = ^(TSLTransponderData *transponder, BOOL moreAvailable)
        {
            NSString* epcVal = transponder.epc;
            if(useAscii){
                epcVal = [self getAscii:epcVal];
            }
        
            if ([epcVal isEqualToString:tagID])
            {
                NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
                [resultMessage setObject:@"rfid" forKey:@"type"];
                [resultMessage setObject:epcVal forKey:@"id"];
                [resultMessage setObject:(transponder.rssi == nil ) ? @"n/a" : [NSString stringWithFormat:@"%3d", transponder.rssi.intValue] forKey:@"RSSI"];
                [dataArray addObject:resultMessage];
            }
        };

        [commander executeCommand:invCommand];
        NSDictionary *dict = @{@"data" : dataArray, @"errorMsg" : errorMsg, @"status" : status};
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
     
    }
    else {
        status = @"false";
        errorMsg = @"Device not connected.";
        NSDictionary *dict = @{@"data" : [[NSMutableArray alloc] init], @"errorMsg" : errorMsg, @"status" : status};
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:dict];
    }
    
    [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
    [self removeSyncAndAddAsyncResponder];
}

- (void)setOutputPower:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
    CDVPluginResult* pluginResult = nil;
    int newPower = [[command.arguments objectAtIndex:0] intValue];
    
    NSLog(@" me called setOutputPower");
	TSLAsciiCommander* commander = [self getCommander];
	
    NSMutableString *msg = [NSMutableString stringWithFormat:@""];
	
    if([commander isConnected]){
      int minPower = [TSLInventoryCommand minimumOutputPower];
      int maxPower = [TSLInventoryCommand maximumOutputPower];
      [self removeAsyncAndAddSyncResponder];
      if(newPower >= minPower && newPower <= maxPower){
        
          int oldPowerVal = self.scanPower;
          self.scanPower = newPower;
        
          TSLInventoryCommand* invCommand = [TSLInventoryCommand synchronousCommand];
          invCommand.takeNoAction = TSL_TriState_YES;
          invCommand.includeEPC = TSL_TriState_YES;
          invCommand.includeTransponderRSSI = TSL_TriState_YES;
          invCommand.captureNonLibraryResponses = YES;
          invCommand.outputPower = (int)newPower;
          NSLog(@" me called setOutputPower new power %d",(int)newPower);
          [commander executeCommand:invCommand];
        
          [msg appendFormat:@"Scan power set from %d", (int)oldPowerVal];
          [msg appendFormat:@" to %d",newPower];
      }else {
          [msg appendFormat:@"Scan power %d",newPower];
          [msg appendFormat:@" is not in device range  %d",[TSLInventoryCommand minimumOutputPower]];
          [msg appendFormat:@" to  %d",[TSLInventoryCommand maximumOutputPower]];
      }
			
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:msg];
	}
    else{
		  [msg stringByAppendingString:@"Device is not connected."];
		  pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:msg];
	}
	[delegate sendPluginResult:pluginResult callbackId:command.callbackId];
  [self removeSyncAndAddAsyncResponder];
}

//The following methods convert HEX to ASCII
- (NSString *)getAscii:(NSString *) hexString
{
    // The hex codes should all be two characters.
    if (([hexString length] % 2) != 0){
        return nil;
    }
	    
    NSMutableString *string = [NSMutableString string];

    for (NSInteger i = 0; i < [hexString length]; i += 2) {

        NSString *hex = [hexString substringWithRange:NSMakeRange(i, 2)];
        int decimalValue = 0;
        sscanf([hex UTF8String], "%x", &decimalValue);
        [string appendFormat:@"%c", (int)decimalValue];
    }
    
    return string;
}

- (void)subscribeScanner:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate
{
    bool useAscii = FALSE;//[[command.arguments objectAtIndex:0] boolValue];
    subsCmdDelegate = delegate;
    TSLAsciiCommander* commander = [self getCommander];

    __block NSString* status = @"subscribing";
    NSString *errorMsg = @"";

    if ([commander isConnected] && _asyncCommand == nil) {
        NSLog(@" me called subscribeScanner - _asyncCommand nil");
        _asyncCommand = command;
        _inventoryResponder = [[TSLInventoryCommand alloc] init];
        _inventoryResponder.includeEPC = TSL_TriState_YES;
        _inventoryResponder.includeTransponderRSSI = TSL_TriState_YES;

        if(self.scanPower > -1) {
            _inventoryResponder.outputPower = [self scanPower];
        }

        //_inventoryResponder.transponderReceivedDelegate = self;
        _inventoryResponder.captureNonLibraryResponses = YES;

        NSMutableArray *dataArray = [[NSMutableArray alloc] init];

        _inventoryResponder.transponderDataReceivedBlock = ^(TSLTransponderData *transponder, BOOL moreAvailable)
	    {
            //this is what is hit if say a trigger pull reads EPCs, so will call the OnSuccess over in js with new status
            NSString* epcVal = transponder.epc;
            if(useAscii){
                epcVal = [self getAscii:epcVal];
            }
			
            NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
            [resultMessage setObject:@"rfid" forKey:@"type"];
            [resultMessage setObject:epcVal forKey:@"id"];
  			[resultMessage setObject:(transponder.rssi == nil ) ? @"n/a" : [NSString stringWithFormat:@"%3d", transponder.rssi.intValue] forKey:@"RSSI"];
            [dataArray addObject:resultMessage];

            if(!moreAvailable) {
                status = @"subscribed";
                NSDictionary *dict = @{@"data" : dataArray, @"errorMsg" : errorMsg, @"status" : status};
                
                _asyncPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
      
                // here we tell Cordova not to cleanup the callback id after sendPluginResult()
                [_asyncPluginResult setKeepCallbackAsBool:YES];
                [delegate sendPluginResult:_asyncPluginResult callbackId:_asyncCommand.callbackId];
                [dataArray removeAllObjects];
            }
        };

        _barcodeResponder = [[TSLBarcodeCommand alloc] init];
        _barcodeResponder.barcodeReceivedDelegate = self;
        _barcodeResponder.captureNonLibraryResponses = YES;
        [self removeSyncAndAddAsyncResponder];

        _asyncPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Scanner subscribed"];
        [_asyncPluginResult setKeepCallbackAsBool:YES];
        [delegate sendPluginResult:_asyncPluginResult callbackId:_asyncCommand.callbackId];

    } else if([commander isConnected] && _asyncCommand != nil){
				
         status = @"true";
        errorMsg = @"DEVICE IS ALREADY SUBSCRIBED";
        NSDictionary *dict = @{@"data" : [[NSMutableArray alloc] init], @"errorMsg" : errorMsg, @"status" : status};
		
         _asyncPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:dict];
        [_asyncPluginResult setKeepCallbackAsBool:YES];
        [delegate sendPluginResult:_asyncPluginResult callbackId:_asyncCommand.callbackId];
    }
    else {
        status = @"false";
        errorMsg = @"DEVICE IS NOT CONNECTED.";
        NSDictionary *dict = @{ @"data" : [[NSMutableArray alloc] init], @"errorMsg" : errorMsg, @"status" : status};

       _asyncPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:dict];
        [_asyncPluginResult setKeepCallbackAsBool:YES];
        [delegate sendPluginResult:_asyncPluginResult callbackId:_asyncCommand.callbackId];
    }
}

- (void) unsubscribeScanner:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate{
    CDVPluginResult* unsubscribePluginResult = nil;
		
    if([self.commander isConnected] && _asyncPluginResult != nil) {
        [self removeAsyncResponder];
        _inventoryResponder = nil;
        _barcodeResponder = nil;
        _asyncPluginResult=nil;
        _asyncCommand = nil;

        unsubscribePluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Responders removed"];
        [unsubscribePluginResult setKeepCallbackAsBool:NO];
	    [delegate sendPluginResult:unsubscribePluginResult callbackId:command.callbackId];
    }
}

-(void) startSearch:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate {
    
    TSLAsciiCommander* commander = [self getCommander];
    NSString* tagID = [command.arguments objectAtIndex:0];
    bool useAscii = [[command.arguments objectAtIndex:1] boolValue];
    __block NSString* status = @"subscribing";
    NSString *errorMsg = @"";

    if ([commander isConnected]) {
         [self removeAsyncResponder];
         if(_inventorySearchResponder == nil){
           _inventorySearchResponder = [[TSLInventoryCommand alloc] init];
           _inventorySearchResponder.takeNoAction = TSL_TriState_NO;
           _inventorySearchResponder.includeTransponderRSSI = TSL_TriState_YES;

           if(self.scanPower > -1) {
                _inventorySearchResponder.outputPower = [self scanPower];
           }
             
           _inventorySearchResponder.inventoryOnly = TSL_TriState_YES;
           _inventorySearchResponder.queryTarget = TSL_QueryTarget_B;
           _inventorySearchResponder.querySession = TSL_QuerySession_S0;
           _inventorySearchResponder.selectAction = TSL_SelectAction_DeassertSetB_AssertSetA;
           _inventorySearchResponder.selectTarget = TSL_SelectTarget_S0;
           _inventorySearchResponder.selectBank = TSL_DataBank_ElectronicProductCode;

           NSString* tagIDTemp = tagID;
           if(useAscii){
                tagIDTemp = [self getAscii:tagID];
           }
           _inventorySearchResponder.selectData = tagIDTemp;
           _inventorySearchResponder.selectOffset = 0020;
           _inventorySearchResponder.selectLength = 40;
           _inventorySearchResponder.captureNonLibraryResponses = YES;

           //_inventorySearchResponder.transponderReceivedDelegate = self;

           [self.commander addResponder:_inventorySearchResponder];
           NSMutableArray *dataArray = [[NSMutableArray alloc] init];
                 //[self removeSyncAndAddAsyncResponder];
           _inventorySearchResponder.transponderDataReceivedBlock = ^(TSLTransponderData *transponder, BOOL moreAvailable){
                     
                NSString* epcVal = transponder.epc;
                if(useAscii){
                   epcVal = [self getAscii:epcVal];
                }
              
               if ([epcVal isEqualToString:tagID]) {
                   
                   NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
                   [resultMessage setObject:@"rfid" forKey:@"type"];
                   [resultMessage setObject:epcVal forKey:@"id"];
                   [resultMessage setObject:(transponder.rssi == nil ) ? @"n/a" : [NSString stringWithFormat:@"%3d", transponder.rssi.intValue] forKey:@"RSSI"];
                   [dataArray addObject:resultMessage];
               }
               
               if(!moreAvailable) {
                    NSDictionary *dict = @{@"data" : dataArray, @"errorMsg" : errorMsg, @"status" : status};
                    
                    _asyncSearchPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
                     
                    // here we tell Cordova not to cleanup the callback id after sendPluginResult()
                    [_asyncSearchPluginResult setKeepCallbackAsBool:YES];
                    [delegate sendPluginResult:_asyncSearchPluginResult callbackId:command.callbackId];
                    [dataArray removeAllObjects];
                }
           };}
            
        _asyncSearchPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [_asyncSearchPluginResult setKeepCallbackAsBool:YES];

        [delegate sendPluginResult:_asyncSearchPluginResult callbackId:command.callbackId];
        }
        else if([commander isConnected] && _inventorySearchResponder != nil){
              status = @"false";
              errorMsg = @"SEARCH IS ALREADY ACTIVATED.";
              NSDictionary *dict = @{@"data" : [[NSMutableArray alloc] init], @"errorMsg" : errorMsg, @"status" : status};

            _asyncSearchPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:dict];
        }
        else {
            status = @"false";
            errorMsg = DEVICE_IS_NOT_CONNECTED;
            NSDictionary *dict = @{@"data" : [[NSMutableArray alloc] init], @"errorMsg" : errorMsg, @"status" : status};

            _asyncSearchPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:dict];
        }
    
    [_asyncSearchPluginResult setKeepCallbackAsBool:YES];
    [delegate sendPluginResult:_asyncSearchPluginResult callbackId:command.callbackId];
}

-(void) stopSearch:(CDVInvokedUrlCommand*)command commandDelegate:(NSObject<CDVCommandDelegate>*)delegate{
    
    TSLAsciiCommander* commander = [self getCommander];
    CDVPluginResult* pluginResult = nil;
    if ([commander isConnected]) {
        
        if(_inventorySearchResponder != nil) {
            [self.commander removeResponder:_inventorySearchResponder];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"REMOVING SEARCH RESPONDER"];
            [pluginResult setKeepCallbackAsBool:YES];
            [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
        }
        
        _inventorySearchResponder = nil;
        _asyncSearchPluginResult = nil;
        [self addAsyncResponder];

        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"SEARCH DEACTIVATED"];
        [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
    else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:DEVICE_IS_NOT_CONNECTED];
        [delegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)removeAsyncAndAddSyncResponder {
    
    NSLog(@" me called removeAsyncAndAddSyncResponder");
    [self removeAsyncResponder];
    [self.commander addSynchronousResponder];
}

- (void)removeSyncAndAddAsyncResponder {
    
    NSLog(@" me called removeSyncAndAddAsyncResponder");
	[self.commander removeSynchronousResponder];
	[self addAsyncResponder];
}

- (void)removeAsyncResponder {
    NSLog(@" me called removeAsyncResponder");
    if(_inventoryResponder != nil) {
        [self.commander removeResponder:_inventoryResponder];
    }
     
    if(_barcodeResponder != nil){
        [self.commander removeResponder:_barcodeResponder];
    }
}

- (void)addAsyncResponder {
    NSLog(@" me called addAsyncResponder");
    if(_inventoryResponder != nil) {
        [self.commander addResponder:_inventoryResponder];
    }
     
    if(_barcodeResponder != nil) {
        [self.commander addResponder:_barcodeResponder];
    }
}

-(void)barcodeReceived:(NSString *)data
{
    NSLog(@" me called barcodeReceived");
  
    __block NSString* status = @"subscribing";
    NSString *errorMsg = @"";
    
    if(data){
    
        NSMutableArray *bcDataArray = [[NSMutableArray alloc] init];
        NSMutableDictionary *bcResultMessage = [[NSMutableDictionary alloc] init];
        [bcResultMessage setObject:@"barcode" forKey:@"type"];
        [bcResultMessage setObject:data forKey:@"id"];
        [bcDataArray addObject:bcResultMessage];

        NSDictionary *bcDict = @{@"data" : bcDataArray, @"errorMsg" : errorMsg, @"status" : status};
        if ([NSJSONSerialization isValidJSONObject:bcDict])
        {
          _asyncPluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:bcDict];
         [_asyncPluginResult setKeepCallbackAsBool:YES];
         [subsCmdDelegate sendPluginResult:_asyncPluginResult callbackId:_asyncCommand.callbackId];
         [bcDataArray removeAllObjects];
      }
    }
}

@end


