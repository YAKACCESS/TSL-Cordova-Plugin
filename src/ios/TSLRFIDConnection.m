
#import "TSLRFIDConnection.h"

@implementation TSLRFIDConnection
  
+ (id)sharedTSLInstance {
    static TSLScanner *sharedTSLInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedTSLInstance = [[TSLScanner alloc] init];
    });
    return sharedTSLInstance;
}

- (void)getDeviceList:(CDVInvokedUrlCommand*)command{
    
    NSLog(@"getDeviceList in Scanner");
    
    CDVPluginResult* pluginResult = nil;
    if (command != nil) {
        NSArray* _currentAccessories = [[EAAccessoryManager sharedAccessoryManager] connectedAccessories];
 
        NSMutableArray *dataArray = [[NSMutableArray alloc] init];
        NSMutableDictionary *accessories = nil;
        
        for (EAAccessory *obj in _currentAccessories)
        {
            accessories = [[NSMutableDictionary alloc] init];
            [accessories setObject:obj.name forKey:@"name"];
            [accessories setObject:obj.serialNumber forKey:@"deviceID"];
            [dataArray addObject:accessories];
        }
        //NSError *error = nil;
        NSString *status = @"true";
        NSString *errorMsg = @"";
        //NSString *jsonMsg = nil;
        if (!dataArray || !dataArray.count){
              status = @"false";
                errorMsg = @"Bluetooth connection is not enabled or device is not paired.";
        }
                
        NSDictionary *dict = @{@"data" : dataArray, @"errorMsg" : errorMsg, @"status" : status};
      
        /*if ([NSJSONSerialization isValidJSONObject:dict])
        {
            NSData *json = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:&error];
            if (json != nil && error == nil)
            {
                jsonMsg = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
            }
        }*/
          
        //pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:jsonMsg];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
    } else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)connect:(CDVInvokedUrlCommand*)command{
    NSLog(@"getDeviceList in TSLRFIDConnection tsl");
    [[TSLRFIDConnection sharedTSLInstance] connect:command commandDelegate:self.commandDelegate];
}

- (void)isConnected:(CDVInvokedUrlCommand*)command{
     NSLog(@"isConnected in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] isConnected:command commandDelegate:self.commandDelegate];
}

- (void)disconnect:(CDVInvokedUrlCommand*)command{
     NSLog(@"disconnect in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] disconnect:command commandDelegate:self.commandDelegate];
}

- (void)getDeviceInfo:(CDVInvokedUrlCommand*)command{
     NSLog(@"getDeviceInfo in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] getDeviceInfo:command commandDelegate:self.commandDelegate];
}

- (void)scanRFIDs:(CDVInvokedUrlCommand*)command{
     NSLog(@"scanRFIDs in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] scanRFIDs:command commandDelegate:self.commandDelegate];
}

- (void)search:(CDVInvokedUrlCommand*)command{
     NSLog(@"search in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] search:command commandDelegate:self.commandDelegate];
}

- (void)setOutputPower:(CDVInvokedUrlCommand*)command{
     NSLog(@"setOutputPower in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] setOutputPower:command commandDelegate:self.commandDelegate];
}

- (void)subscribeScanner:(CDVInvokedUrlCommand*)command{
     NSLog(@"subscribe in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] subscribeScanner:command commandDelegate:self.commandDelegate];
}

- (void)unsubscribeScanner:(CDVInvokedUrlCommand*)command{
     NSLog(@"unsubscribe in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] unsubscribeScanner:command commandDelegate:self.commandDelegate];
}

- (void)startSearch:(CDVInvokedUrlCommand*)command{
     NSLog(@"startSearch in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] startSearch:command commandDelegate:self.commandDelegate];
}

- (void)stopSearch:(CDVInvokedUrlCommand*)command{

    NSLog(@"stopSearch in TSLRFIDConnection tsl");
     [[TSLRFIDConnection sharedTSLInstance] stopSearch:command commandDelegate:self.commandDelegate];
}

@end
