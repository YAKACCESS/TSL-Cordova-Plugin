var exec = require('cordova/exec');

var tslRFIDConnection = {};
    
tslRFIDConnection.getDeviceList = function(successCallback,failureCallback){
                         
    exec(successCallback, failureCallback, 'TSLRFIDConnection','getDeviceList', []);
};

tslRFIDConnection.connect = function(deviceType, deviceID,successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'connect', [deviceType, deviceID ]);
};

tslRFIDConnection.isConnected = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'isConnected', []);
};

tslRFIDConnection.disconnect = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'disconnect', []);
};

tslRFIDConnection.getDeviceInfo = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'getDeviceInfo', []);
};

tslRFIDConnection.scanRFIDs = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'scanRFIDs', []);
};

tslRFIDConnection.search = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'search', []);
};

tslRFIDConnection.setOutputPower = function(power,successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'setOutputPower', [ power ]);
};

tslRFIDConnection.search = function(tagId, successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'search', [ tagId ]);
};

tslRFIDConnection.stopSearch = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'stopSearch', []);
};

tslRFIDConnection.subscribeScanner = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'subscribeScanner', []);
};

tslRFIDConnection.unsubscribeScanner = function(successCallback, failureCallback) {
    exec(successCallback, failureCallback, 'TSLRFIDConnection', 'unsubscribeScanner', []);
};

module.exports = tslRFIDConnection;
