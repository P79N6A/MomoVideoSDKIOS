/******************************************************************************

@File         XEWorldProperty.h

@Version      1.0

@Created      2017, 6, 2

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_WORLD_PROPERTY_H_
#define _XE_WORLD_PROPERTY_H_

#include "XMemBase.h"
#include "XMath3D.h"
#include "tinyxml2_XEngine.h"
#include "XConsoleManager.h"

enum EAAMethod
{
	AA_NOAA = 0, // NOTE!! by zhouyifan, ��Ҫ�޸�Ĭ��ֵ
	AA_FXAA,
	AA_SSAA
};

class XEWorld;
class XEWorldParam : public XMemBase
{
public:
	XEWorldParam();
	virtual									~XEWorldParam(){}
	virtual void							Init(XEWorld* pWorld);
	virtual void							Release();
	virtual void							Deserialize(tinyxml2_XEngine::XMLElement* pEleScene);
	virtual tinyxml2_XEngine::XMLElement*	Serialize(tinyxml2_XEngine::XMLElement* pEleParent);

	inline void								SetWorldPropertyModified(xbool bIsModified){ m_bIsWorldPropertyModified = bIsModified; }
	inline xbool							IsWorldPropertyModified(){ return m_bIsWorldPropertyModified; }
	inline void								SetOverrideGravity(xbool bIsOverrideGravity){ m_bIsOverrideGravity = bIsOverrideGravity; }
	inline xbool							IsOverrideGravity(){ return m_bIsOverrideGravity; }
	void									SetGlobalGravity(XVECTOR3 vGravity);
	XVECTOR3								GetGlobalGravity();
	void									SetWindSpeed(xfloat32 fSpeed);
	xfloat32								GetWindSpeed();
	void									SetWindDir(XVECTOR3 vDir);
	XVECTOR3								GetWindDir();
	void									SetAAMethod(EAAMethod eAAMethod);
	EAAMethod								GetAAMethod() const{ return m_eAAMethod; }

	void									SetDrawPhysics(xbool bDrawPhysics);
	xbool									IsDrawPhysics();
	void									SetQIT(bool bQIT);
	xbool									IsQIT();
	void									SetQITLayerNum(xint32 nNum);
	xint32									GetQITLayerNum();
	void									SetShadow(xbool bShadow);
	xbool									IsShadow();
	void									SetShadowMapResolution(xint32 nData);
	xint32									GetShadowMapResolution();
	void									SetShadowDistance(xfloat32 nDistance);
	xfloat32								GetShadowDistance();
	void									SetShadowCascadeNum(xint32 nNum);
	xint32									GetShadowCascadeNum();
	void									SetShadowDepth(xfloat32 fDepth);
	xfloat32								GetShadowDepth();
	void									SetShadowSoftness(xfloat32 fSoftness);
	xfloat32								GetShadowSoftness();
	void									SetBloomEnable(xbool bBoolm);
	inline xbool							GetBloomEnable(){ return m_bBloomEnable; }
	void									SetBloomColorThreshold(xfloat32 fvalue);
	inline xfloat32							GetBloomColorThreshold(){ return m_fBloomColorThreshold; }
	void									SetBloomSamplerScale(xfloat32 fvalue);
	inline xfloat32							GetBloomSamplerScale(){ return m_fBloomSamplerScale; }
	void									SetFogEnable(xbool bFog);
	inline xbool							GetFogEnable(){ return m_bFogEnable; }
	void									SetFogStart(xfloat32 fvalue);
	inline xfloat32							GetFogStart(){ return m_fFogStart; }
	void									SetFogEnd(xfloat32 fvalue);
	inline xfloat32							GetFogEnd(){ return m_fFogEnd; }
	void									SetFogDensity(xfloat32 fvalue);
	inline xfloat32							GetFogDensity(){ return m_fFogDensity; }
	void									SetFogColorUpper(XVECTOR4 vValue);
	inline XVECTOR4							GetFogColorUpper(){ return m_vFogColorUpper; }
	void									SetFogColorLower(XVECTOR4 vValue);
	inline XVECTOR4							GetFogColorLower(){ return m_vFogColorLower; }

	void									SetBlendShapeNormalMethod(XBlendShapeNormalMethod eType);

	X_FORCEINLINE XBlendShapeNormalMethod	GetBlendShapeNormalMethod() { return m_eBlendshapeNormalMethod; }

	void									InitParams();
	void									UpdateParams();
private:
	void                                    UpdatePostProcessState();
private:
	XEWorld*								m_pWorld;
	xbool									m_bIsWorldPropertyModified;
	xbool									m_bIsOverrideGravity;
	EAAMethod								m_eAAMethod;
	XBlendShapeNormalMethod					m_eBlendshapeNormalMethod;
	// add these params, to differentiate main editor and sub editors world settings. --ylj
	xfloat32								m_fWindSpeed;
	XVECTOR3								m_vWindDir;
	xbool									m_bDrawPhysics;
	xbool									m_bQIT;
	xint32									m_nQITLayerNum;
	xbool									m_bShadow;
	xint32									m_nShadowMapResolution;
	xfloat32								m_fShadowDistance;
	xint32									m_nShadowCascadeNum;
	xfloat32								m_fShadowDepth;
	xfloat32								m_fShadowSoftness;
	xbool									m_bBloomEnable;//����Bloom
	xfloat32								m_fBloomColorThreshold; //bloom��ֵ
	xfloat32								m_fBloomSamplerScale; // bloom�����뾶
	xbool									m_bFogEnable;//������Ч
	xfloat32								m_fFogStart;//��Ч��ʼ����
	xfloat32								m_fFogEnd;//��Ч��������
	xfloat32								m_fFogDensity;//��ȫ���ܶ�
	XVECTOR4								m_vFogColorUpper;//�ϲ�����ɫ
	XVECTOR4								m_vFogColorLower;//�ϲ�����ɫ


};

#endif//_XE_WORLD_PROPERTY_H_