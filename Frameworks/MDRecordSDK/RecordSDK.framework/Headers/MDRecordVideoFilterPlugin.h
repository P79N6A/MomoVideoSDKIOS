//
//  MDVideoFilterPlugin.h
//  RecordSDK
//
//  Created by sunfei on 2018/11/30.
//  Copyright © 2018 sunfei. All rights reserved.
//

@import Foundation;
@import MLMediaFoundation;
#import "MDProcessImageProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface MDRecordVideoFilterPlugin : NSObject <MLPlayerVideoFilterPlugin>

- (instancetype)initWithFilter:(id<MDProcessImageProtocol>)filter;

@end

NS_ASSUME_NONNULL_END
