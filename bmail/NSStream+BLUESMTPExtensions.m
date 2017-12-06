
#import "NSStream+BLUESMTPExtensions.h"


@implementation NSStream (BLUESMTPExtensions)

+ (void)getStreamsToHostNamed:(NSString *)hostName port:(NSInteger)port inputStream:(NSInputStream * __strong *)inputStream outputStream:(NSOutputStream * __strong *)outputStream
{
    CFHostRef           host;
    CFReadStreamRef     readStream;
    CFWriteStreamRef    writeStream;
    
    readStream = NULL;
    writeStream = NULL;
    
    host = CFHostCreateWithName(NULL, (CFStringRef) CFBridgingRetain(hostName));
    if (host != NULL) 
    {
        (void) CFStreamCreatePairWithSocketToCFHost(NULL, host, port, &readStream, &writeStream);
        CFRelease(host);
    }
    
    if (inputStream == NULL) 
    {
        if (readStream != NULL) 
        {
            CFRelease(readStream);
        }
    } 
    else 
    {
        *inputStream = (NSInputStream *) CFBridgingRelease(readStream) ;
    }
    if (outputStream == NULL) 
    {
        if (writeStream != NULL) 
        {
            CFRelease(writeStream);
        }
    } 
    else 
    {
        *outputStream = (NSOutputStream *) CFBridgingRelease(writeStream) ;
    }
}

@end
