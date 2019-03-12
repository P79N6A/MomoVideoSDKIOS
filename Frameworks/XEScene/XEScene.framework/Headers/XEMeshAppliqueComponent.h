/******************************************************************************

@File         XEMeshAppliqueComponent.h

@Version       1.0

@Created      2018, 10, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/


#ifndef _XE_MESH_APPLIQUE_COMPONENT_H_
#define _XE_MESH_APPLIQUE_COMPONENT_H_

#include "XEModelComponent.h"
// #include "XSkin.h"
// #include "XSkinData.h"
#include "XModelInstance.h"


class XEMeshAppliqueComponent : public XEActorComponent
{
public:

	enum XEPasteType
	{
		XE_APLQ_PT_UV = 0,
		XE_APLQ_PT_NUM
	};


	/*
	@param
	strAppliqueModelFile	:	����ģ��·��
	strOriginSkin			:	ԭģ�ͱ�����skin���� ������·����
	strOriginMeshName		:	ԭģ�ͱ�����mesh
	eType					:	������ʽ�� XE_APLQ_PT_UV�� ͨ��UVƥ��
	vPosToUVOffset			:	λ��תUV��ƫ�ƣ�ֻ���� eType == XE_APLQ_PT_UVʱ��Ч
	fUVMatchDevi			:	ƥ��UVʱ����Χ����Ϊ��ƥ��ʱ�п���ƥ��ʧ�ܣ����Դ�ֵ���Ϊ��СUV�����һ��; (ֻ���� eType == XE_APLQ_PT_UVʱ��Ч)��
	fExpansionMesh			:	��������ÿ����������λ�ƾ��룬�������ϲ��������ԭģ�ͻ���ȫ���������ǿ������ڼ�����
	                            ������΢С�ļ�϶�����ֵ�Z��ͻ����ֵΪ���ȷ�����ԭģ��Ϊ��̬ģ��ʱ����״�ǲ���Ҫ��ֵ��

	@notice
	1. UV����ģ��������ʽ������ԭģ��UVչ��ͼ������ͬ����״�Ĳ�������ʹ��������Ķ����λ��ֵxy������ԭģ�Ͷ����uvֵ��
	2. ������ʽ��Ҫ�󲹶�ģ�Ͳ����Դ��ڲ�֣������߼�����ڸ��ӡ�
	3. UV������ʽ����uv����Ҫ��ܸߣ����Ծ�����Ҫ��UVչ��ͼ�ϳ��־���̫�����㣻	
	4. ����ģ�͵�λ�ã����˰�ԭģ��UVչ��ͼ�����⣻��Ҫ����������ĸ�������ȫ���ϣ����ڶ���һһ��Ӧ��ǰ���£�������Ϊ����ı���˳��һ�������������������߲���Ӧ����
	*/
	struct XEAppliqueInfo
	{
		XString strAppliqueModelFile;
		XString strOriginSkin;
		XString strOriginMeshName;
		XEPasteType eType;
		XVECTOR2 vPosToUVOffset;
		xfloat32 fPosToUVScale;
		xfloat32 fUVMatchDevi;
		xfloat32 fExpansionMesh;
		XEAppliqueInfo() : strAppliqueModelFile(""), strOriginSkin(""), strOriginMeshName(""), eType(XE_APLQ_PT_UV),
			vPosToUVOffset(0.0f), fPosToUVScale(1.0f), fUVMatchDevi(0.005f), fExpansionMesh(0.002f){}
	};



	struct XEMeshAppliqueOperater
	{
		//XSkinData::XRenderMesh *pRefRenderMesh;
		xint32 nRefRenderMeshIndex;
		xint32 nOriginRenderMeshIndex;
		XArray<xint32> vToOriginVertexIndexs;

		XEMeshAppliqueOperater() : /*pRefRenderMesh(NULL), */nRefRenderMeshIndex(-1){}
		void Release();
	};
	struct XEAppliqueOperater
	{
		XEAppliqueInfo inputInfo;
		xint32 nOriginSkinIndex;
		xint32 nOriginRawMeshIndex;

		XEModelComponent *pRefModelComponent;
// 		IXModelInstance *pRefModelIns;
// 		XSkin *pRefSkin;
		XString strRefSkin;
		xint32 nRefSkinIndex;
		XArray<XEMeshAppliqueOperater*> vMeshAppliqueOperaters;

		XEAppliqueOperater() : nOriginSkinIndex(-1), nOriginRawMeshIndex(-1), pRefModelComponent(NULL), strRefSkin(""), /*pRefModelIns(NULL), pRefSkin(NULL),*/ nRefSkinIndex(-1){}
		void Release();
	};

public:
	XE_COMPONENT_CAST(XEMeshAppliqueComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEMeshAppliqueComponent)
											XEMeshAppliqueComponent();
	virtual									~XEMeshAppliqueComponent();

	static const XString					COMPONENT_TYPENAME;
	virtual void							Initialize(XEActor* pWorld) override;
	virtual void							Release() override;
	virtual XMLElement*						Serialize(XMLElement* pEleParent) override;
	virtual void							Deserialize(const XMLElement* pEleComponent) override;
	virtual void							Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void							Render(XEViewport* pViewport) override;


	const XEAppliqueOperater*				PasteMeshApplique(const XEAppliqueInfo &info);
	xbool									RemoveMeshApplique(const XEAppliqueOperater *pAppliqueOper);
	xbool									RemoveMeshApplique(xint32 nIndex);
	const XArray<XEAppliqueOperater*>&		GetAppliqueOperaters() const { return m_vAppliqueOperater; }

protected:

// 	struct XEAppliqueOperater;
// 	struct XEMeshAppliqueOperater;
	struct XESplitSubMeshBuff;
	xbool						GenerateAppliqueOperate(const XSkin *pOriginSkin, const XSkin *pAppqSkin, const XArray<XSkinData::XRenderMesh*> &vOriginRenderMesh,
		const XArray<xint32> &vOriginRenderMeshIndex, XEAppliqueOperater *pOperater);
	xbool						GenerateMeshAppliqueOperate(const XSkinData::XRenderMesh &OriginRenderMesh, const XEAppliqueInfo &inputInfo,
		const XArray<xbool> &vFilterVertex, XSkinData::XRenderMesh &DestRMesh, XArray<xint32> &vToOriginVertexIndexs);
	xbool						GenerateSkinDataOfMeshType(XSkinData *pOldSkinData, XSkinData::XMeshType eMeshType, xbool bBlendshape, XSkinData *pSkinData);
	xbool						CopySkinDataVB(XSkinData *pOldSkinData, XSkinData *pNewSkinData);
	xbool						MatchMeshUVOfVertexBuff(const XArray<const XSkinData::XRenderMesh*> &vOriginRenderMesh, const XEAppliqueInfo &inputInfo, const XSkinData::XRenderMesh *pDestRMesh,
		const XArray<xbool> &vFilterVertex, XArray<const XBaseVertex*> &vOriginVerTex, XArray<xint32> &vToOriginVertexIndexs);
	xbool						CreateNewModelAndSkinData(const XString &strModelIns, const XString &strSkeleton, const XString &strSkinData, XModel *&pModel, XSkinData *&pSkinData);
	xbool						SetMaterialInsToNewSkin(const XSkin *pApplique, xint32 nAppliRawMeshIndex, XSkin *pNewApplique);
	xbool						GenerateSkinBlendShapeTarget(XSkin *pNewAppLiqueSkin);

	template<class V, class E>
	xbool						SplitRenderMeshByOrigin(const XSkinData::XRenderMesh *pDestRMesh, const XArray<xint32> &vToOriginVertexIndex, XESplitSubMeshBuff &SplitSubBuf,
		XArray<xbool> &vFilterVertex, XArray<xint32> &vSubToOrigin);


	void						SynchPasteModelToOrigin(XEAppliqueOperater &AppliqueOperater);
	void						SynchPasteMeshToOrigin(IXModelInstance *pOriginModelIns, IXModelInstance *pRefModelIns, XSkin *pRefSkin, XEAppliqueOperater &AppliqueOperater, XEMeshAppliqueOperater &MeshAppliqueOperate);
	void						SynchSkeletonToOrigin(const XSkeleton &OriSkeIns, XSkeleton &SkeIns);

	virtual void				DeserializeApplique(const XMLElement* pAppliqueInfos);
	virtual void				SerializeApplique(XMLElement* pAppliqueInfos);

	void						DelayAppliqueOfDeserialize();


	// ��Ƭģ�ͣ�modelins\skin�����½��ģ�����Ҫ����Ƕ�룬�˴�ֱ����Ӽ�¼ ��Ӧ��������ҵ�񣬱���Ӧ�ô��ڣ�
	void						EmbedAppliqueDispose(XEModelComponent *pModelComponent);

	struct XESplitSubMeshBuff
	{
		IXVertexBuffer* pDataVB;
		IXIndexBuffer* pDataIB;
		XArray<XSkinData::XRenderMesh*> vSubMeshes;
		xbool bInited;
		XESplitSubMeshBuff(XSkinData::XMeshType eMeshType, xbool bDynamicVB, xint32 nInitVertexSize, xint32 nGrowSizeVB,
			xint32 nIndexStride, xbool bDynamicIB, xint32 nInitIndexSize, xint32 nGrowSizeIB);
		~XESplitSubMeshBuff() { Release(); }
		void Release();
	};


	XArray<XEAppliqueInfo>		 m_vDelayAppliqueOfDeserialize;
	XArray<XEAppliqueOperater*>  m_vAppliqueOperater;


};

#endif