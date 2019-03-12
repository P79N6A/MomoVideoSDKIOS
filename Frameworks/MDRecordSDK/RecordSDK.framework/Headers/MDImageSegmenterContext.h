//
//  MMImageSegmenterContext.h
//  CXBeautyKit
//
//  Created by sunfei on 2018/11/27.
//

@import Foundation;
@import MomoCV;
#import "MDImageDetectorProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface MDImageSegmenterContext : NSObject <MDImageDetectorProtocol>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)makeDetector;
+ (void)asyncAutoMakeDetector:(void(^)(MDImageSegmenterContext *))completed;

@property (nonatomic, readonly) MMImageSegmentationResult *result;

@end

NS_ASSUME_NONNULL_END
