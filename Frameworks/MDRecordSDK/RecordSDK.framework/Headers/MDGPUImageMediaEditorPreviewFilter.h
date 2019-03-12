//
//  MDGPUImageMediaEditorPreviewFilter.h
//  RecordSDK
//
//  Created by sunfei on 2018/12/18.
//  Copyright © 2018 sunfei. All rights reserved.
//

@import Foundation;
@import FaceDecorationKit;
@import FaceDecorationKitGPUImage;
#import "MDRecordFilter.h"

NS_ASSUME_NONNULL_BEGIN

@interface MDGPUImageMediaEditorPreviewFilter : GPUImageFilterGroup <FDKDecorationFilterUpdating>

- (instancetype)init;
- (instancetype)initWithFDKDecorationFilterOptions:(FDKDecorationFilterOptions *)options;

@property (nonatomic, strong) FDKDecoration *decoration;
@property (nonatomic, assign) float audioVolume;

- (void)udpateBeautySetting:(FDKBeautySettings *)beautySettings;

@property (nonatomic, copy) MDRecordFilter *slidingMDFilterA;
@property (nonatomic, copy) MDRecordFilter *slidingMDFilterB;
@property (nonatomic, assign) float slidingOffset;

@end

NS_ASSUME_NONNULL_END
