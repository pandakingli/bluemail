//
//  ViewController.m
//  mailTest
//
//  Created by lining on 2017/11/16.
//  Copyright © 2017年 biubiublue. All rights reserved.
//

#import "ViewController.h"
#import <bluemail/BLUESMTPMessage.h>
#import <bluemail/NSData+Base64Additions.h>

@interface ViewController ()<BLUESMTPMessageDelegate>

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor redColor];
    [self statrUpLoad];
}

-(void)statrUpLoad
{
    BLUESMTPMessage *testSend = [[BLUESMTPMessage alloc]init];
    
    testSend.fromEmail = @"xxx@sina.com";//发送邮件xxx@sina.com
    testSend.toEmail   = @"xxx@qq.com";//目标邮件xxx@qq.com
    testSend.relayHost = @"smtp.sina.com";//smtp
    testSend.requiresAuth = YES;
    
    testSend.login   = @"xxx@sina.com";//发送邮件xxx@sina.com
    testSend.pass    = @"xxx";//登录密码
    
    //主题
    testSend.subject = [NSString stringWithCString:"TestMailFromiOS" encoding:NSUTF8StringEncoding];
    //testSend.ccEmail   = @"抄送邮件";
    testSend.wantsSecure = YES;
    testSend.delegate    = self;
    
    //邮件内容
    NSString *msg = [NSString stringWithFormat:@"iOS 测试 %@",[self getDateString]];
    
    NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithCapacity:3];
    [dic setObject:@"text/plain" forKey:kBLUESMTPPartContentTypeKey];
    [dic setObject:msg forKey:kBLUESMTPPartMessageKey];
    [dic setObject:@"8bit" forKey:kBLUESMTPPartContentTransferEncodingKey];

    testSend.parts = @[dic];
    [testSend send];//发送

}

-(void)messageSent:(BLUESMTPMessage *)message
{
    NSLog(@"message = %@",message);
}

-(void)messageFailed:(BLUESMTPMessage *)message error:(NSError *)error
{
    NSLog(@"message = %@",message);
    NSLog(@"error = %@",error);
}

-(NSString*)getDateString
{
    NSDateFormatter *f = [[NSDateFormatter alloc]init];
    [f setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSString *s = [f stringFromDate:[NSDate dateWithTimeIntervalSinceNow:0]];
    return s;
}
@end
