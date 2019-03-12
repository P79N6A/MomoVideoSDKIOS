/******************************************************************************

@File         XEOutlineComponent.cpp

@Version       1.0

@Created      2018, 11, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_OUTLINE_COMPONENT_H_
#define _XE_OUTLINE_COMPONENT_H_

#include "XEAnimatableModelComponent.h"


/*
	���ڶ�ģ����ߵ�ר�����

	@notice :
	��ģ�������Ҫ����pass,һ������Ⱦ�����ߣ�һ�������Ⱦ����ǰ���治֧�ֶ�pass,���Դ˴���Ҫ��һ��Componentר��������Ⱦ�����ߡ�
	����Ϊ��ǰ���治֧����ģ��ʵ����,�����޸Ĳ������ԣ�ʵ��skin��Ӧ�����޸ģ���ͬʱӰ������ͬģ���ʵ���������Դ˴������ض���Component
	��������Щ�߼��� ���֮�󲻹�������㣬����XECore�㣬֧���˲��ʵĵ����༭�����߿��Կ���ȥ����Component��Ҳ���߿���ʹ���ϵķ��㣬��������
	Component;
	��ǰ��component����ߣ�֧�ֹ���������ͬ������
*/
class XEOutlineComponent : public XEAnimatableModelComponent
{
public:
	XE_COMPONENT_CAST(XEOutlineComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEOutlineComponent)
											XEOutlineComponent();
	virtual									~XEOutlineComponent();

	static const XString					COMPONENT_TYPENAME;
	virtual void							Initialize(XEActor* pWorld) override;
	virtual void							Release() override;
	virtual XMLElement*						Serialize(XMLElement* pEleParent) override;
	virtual void							Deserialize(const XMLElement* pEleComponent) override;
	virtual void							Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void							Render(XEViewport* pViewport) override;

	xbool									UpdateOutline();
	void									SetOutlineWidth(xfloat32 fLineWidth, xbool bApplyToMtl = xtrue);
	xfloat32								GetOutlineWidth() const { return m_fOutlineWidth; }
	void									SetOutlineColor(const XCOLORBASE &color, xbool bApplyToMtl = xtrue);
	const XCOLORBASE&						GetOutlineColor() const { return m_clrOutline; }

protected:

	virtual xbool                           LoadAsset(const xchar* pPath) override { return xfalse; }

#if X_PLATFORM_WIN_DESKTOP
	virtual void                            GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif

	xbool									GenerateOutlineModel();
	xbool									ReleaseOutlineModel();
	void									SynOutlineToRootModel();
	void									SynchBoneToRootModel(const IXModelInstance *pRootModelIns, const XSkinData::XRenderMesh *pOriginRenderMesh,
																const IXModelInstance *pOutlineModelIns, XSkinData::XRenderMesh *pOutlineRenderMesh);
	void									SynchMorphToRootModel();


	XModel*									EmbedRootModel(XModel *pSourceModel);
	//XSkin*									EmbedSkin(XSkin *pSourceSkin, xbool bSetMaterail = xtrue);
	void									SynParamToMaterialIns();


	xbool									m_bGenerated;
	xfloat32								m_fOutlineWidth;
	XCOLORBASE								m_clrOutline;
};

#endif

