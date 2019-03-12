//
//  MDObjectDetectorContext.h
//  CXBeautyKit
//
//  Created by sunfei on 2018/11/27.
//

@import Foundation;
@import MomoCV;
#import "MDImageDetectorProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface MDObjectDetectorContext : NSObject <MDImageDetectorProtocol>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)makeDetector;
+ (void)asyncAutoMakeDetector:(void(^)(MDObjectDetectorContext *))completed;

@property (nonatomic, readonly) MMObjectDetectionResult *result;

@end

NS_ASSUME_NONNULL_END
