#import <Cordova/CDV.h>
#import "TSLScanner.h"

@interface TSLRFIDConnection : CDVPlugin {
}
+ (id)sharedTSLInstance;

- (void)getDeviceList:(CDVInvokedUrlCommand*)command;
- (void)connect:(CDVInvokedUrlCommand*)command;
- (void)isConnected:(CDVInvokedUrlCommand*)command;
- (void)disconnect:(CDVInvokedUrlCommand*)command;
- (void)getDeviceInfo:(CDVInvokedUrlCommand*)command;
- (void)scanRFIDs:(CDVInvokedUrlCommand*)command;
- (void)search:(CDVInvokedUrlCommand*)command;
- (void)setOutputPower:(CDVInvokedUrlCommand*)command;
- (void)subscribeScanner:(CDVInvokedUrlCommand*)command;
- (void)unsubscribeScanner:(CDVInvokedUrlCommand*)command;
- (void)startSearch:(CDVInvokedUrlCommand*)command;
- (void)stopSearch:(CDVInvokedUrlCommand*)command;

@end

