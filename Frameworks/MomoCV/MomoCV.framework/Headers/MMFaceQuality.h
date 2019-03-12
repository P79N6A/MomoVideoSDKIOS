//
//  MMCVFaceQualityState.h
//  Pods
//
//  Created by Yu Ao on 14/03/2018.
//

typedef NS_ENUM(NSInteger, MMFaceQuality) {
    MMFaceQualityUnknown = 0,
    MMFaceQualityGood = 1,      //合格
    MMFaceQualityBadBrightness = 2,  //太暗或太亮
    MMFaceQualityBadClarity = 3,     //模糊
    MMFaceQualityBadContrast = 4,     //对比
};
