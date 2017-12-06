
#import <CFNetwork/CFNetwork.h>
#import <Foundation/NSStream.h>

@interface NSStream (BLUESMTPExtensions)

+ (void)getStreamsToHostNamed:(NSString *)hostName port:(NSInteger)port inputStream:(NSInputStream * __strong *)inputStream outputStream:(NSOutputStream * __strong *)outputStream;

@end
