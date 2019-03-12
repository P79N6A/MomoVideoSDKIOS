//
//  MDRecordApi.h
//  CXBeautyKit
//
//  Created by sunfei on 2019/2/19.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface MDRecordApi : NSObject

+ (void)registerToken:(NSString *)appId;

+ (void)fetchConfig:(NSString *)token;

@end

NS_ASSUME_NONNULL_END
