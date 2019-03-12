//
//  MDProcessImageProtocol.h
//  CXBeautyKit
//
//  Created by sunfei on 2018/11/26.
//

@import Foundation;
@import CoreMedia;

NS_ASSUME_NONNULL_BEGIN

@protocol MDProcessImageProtocol <NSObject>

- (void)processPixelBuffer:(CVPixelBufferRef)pixelBuffer
                    atTime:(CMTime)time
                completion:(void(^)(CVPixelBufferRef _Nullable, NSError * _Nullable))completion;

@end

NS_ASSUME_NONNULL_END
