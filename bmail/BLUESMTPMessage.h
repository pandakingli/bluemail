

#import <CFNetwork/CFNetwork.h>

enum 
{
    kBLUESMTPIdle = 0,
    kBLUESMTPConnecting,
    kBLUESMTPWaitingEHLOReply,
    kBLUESMTPWaitingTLSReply,
    kBLUESMTPWaitingLOGINUsernameReply,
    kBLUESMTPWaitingLOGINPasswordReply,
    kBLUESMTPWaitingAuthSuccess,
    kBLUESMTPWaitingFromReply,
    kBLUESMTPWaitingToReply,
    kBLUESMTPWaitingForEnterMail,
    kBLUESMTPWaitingSendSuccess,
    kBLUESMTPWaitingQuitReply,
    kBLUESMTPMessageSent
};
typedef NSUInteger BLUESMTPState;
    
// Message part keys
extern NSString *kBLUESMTPPartContentDispositionKey;
extern NSString *kBLUESMTPPartContentTypeKey;
extern NSString *kBLUESMTPPartMessageKey;
extern NSString *kBLUESMTPPartContentTransferEncodingKey;

// Error message codes
#define kBLUESMPTErrorConnectionTimeout -5
#define kBLUESMTPErrorConnectionFailed -3
#define kBLUESMTPErrorConnectionInterrupted -4
#define kBLUESMTPErrorUnsupportedLogin -2
#define kBLUESMTPErrorTLSFail -1
#define kBLUESMTPErrorNonExistentDomain 1
#define kBLUESMTPErrorInvalidUserPass 535
#define kBLUESMTPErrorInvalidMessage 550
#define kBLUESMTPErrorNoRelay 530

@class BLUESMTPMessage;

@protocol BLUESMTPMessageDelegate
@required

-(void)messageSent:(BLUESMTPMessage *)message;
-(void)messageFailed:(BLUESMTPMessage *)message error:(NSError *)error;

@end

@interface BLUESMTPMessage : NSObject <NSCopying, NSStreamDelegate>
{
    NSString *login;
    NSString *pass;
    NSString *relayHost;
    NSArray *relayPorts;
    
    NSString *subject;
    NSString *fromEmail;
    NSString *toEmail;
	NSString *ccEmail;
	NSString *bccEmail;
    NSArray *parts;
    
    NSOutputStream *outputStream;
    NSInputStream *inputStream;
    
    BOOL requiresAuth;
    BOOL wantsSecure;
    BOOL validateSSLChain;
    
    BLUESMTPState sendState;
    BOOL isSecure;
    NSMutableString *inputString;
    
    // Auth support flags
    BOOL serverAuthCRAMMD5;
    BOOL serverAuthPLAIN;
    BOOL serverAuthLOGIN;
    BOOL serverAuthDIGESTMD5;
    
    // Content support flags
    BOOL server8bitMessages;
    
    __weak id <BLUESMTPMessageDelegate> delegate;
    
    NSTimeInterval connectTimeout;
    
    NSTimer *connectTimer;
    NSTimer *watchdogTimer;
}

@property(nonatomic, retain) NSString *login;
@property(nonatomic, retain) NSString *pass;
@property(nonatomic, retain) NSString *relayHost;

@property(nonatomic, retain) NSArray *relayPorts;
@property(nonatomic, assign) BOOL requiresAuth;
@property(nonatomic, assign) BOOL wantsSecure;
@property(nonatomic, assign) BOOL validateSSLChain;

@property(nonatomic, retain) NSString *subject;
@property(nonatomic, retain) NSString *fromEmail;
@property(nonatomic, retain) NSString *toEmail;
@property(nonatomic, retain) NSString *ccEmail;
@property(nonatomic, retain) NSString *bccEmail;
@property(nonatomic, retain) NSArray *parts;

@property(nonatomic, assign) NSTimeInterval connectTimeout;

@property(nonatomic, weak) id <BLUESMTPMessageDelegate> delegate;

- (BOOL)send;

@end
