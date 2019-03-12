//
//  MMFacialExpressionDetectorContext.h
//  CXBeautyKit
//
//  Created by sunfei on 2018/11/27.
//

@import Foundation;
@import MomoCV;
#import "MDImageDetectorProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface MDFacialExpressionDetectorContext : NSObject <MDImageDetectorProtocol>

- (instancetype)init;

@property (nonatomic, readonly) NSArray<MMFacialExpression *> *result;

@end

NS_ASSUME_NONNULL_END
