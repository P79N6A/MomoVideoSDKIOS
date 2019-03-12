/******************************************************************************

@File         XBlendShapeTarget.h

@Version       1.0

@Created      2017, 4, 16

@Description

@HISTORY:

******************************************************************************/

#ifndef _X_BLENDSHAPE_TARGET_H_
#define _X_BLENDSHAPE_TARGET_H_

#include "XMemBase.h"
#include "XArray.h"
#include "XString.h"
#include "XSkinData.h"
#include "XBlendShapeManager.h"
#include <utility>

#define UPDATEBLENDSHAPE_ASYNC 0

#if UPDATEBLENDSHAPE_ASYNC
#include <future>
#endif

struct XBlendShapeTarget : public XMemBase
{
							XBlendShapeTarget() = default;
	xbool					DoSave(XFileBase* pFile) const;
	xbool					DoLoad(XFileBase* pFile);

	/*
	* BlendShape������Ϣ
	*
	* @param	vPositionDelta   �����Դλ�Ƶ�ƫ��
	* @param	vTangentZDelta   �����Դ���ߵ�ƫ��
	* @param	nMeshVertexIndex ��mesh�еĶ�������
	*/
	struct BlendShapeVertex
	{
		XVECTOR3			  vPositionDelta;
		XVECTOR3			  vTangentZDelta;
		xint32				  nMeshVertexIndex;
	};

	XString                   strBShpTargetName;
	XArray<BlendShapeVertex>  aBShpVertices;
	xint32                    nTargetMeshVertexNum;			// ��ǰδʹ��
	xint32                    nTargetMeshVertexStartIndex;		// ��ǰδʹ��
};

struct XBlendShapeChannel : public XMemBase
{
								XBlendShapeChannel() = default;
	xbool						DoSave(XFileBase* pFile) const;
	xbool						DoLoad(XFileBase* pFile, xuint32 loadVersion);

	struct TargetPair
	{
		xint32 index;
		xfloat32 value;
	};
	XString						strChannelName;
	xfloat32					defaultValue = 0.0f;
	XArray<TargetPair>			aTargets;	
};

struct XMeshBlendShapeTarget : public XMemBase
{	
										XMeshBlendShapeTarget() = default;
	xbool								DoSave(XFileBase* pFile) const;
	xbool								DoLoad(XFileBase* pFile, xuint32 loadVersion);

	XString								strTargetMeshName;

	/*
	* ��Ӧԭʼ���������	
	* @notice ԭʼ������fbxת��ʱ�����ܻ��ֳɶ�����񡣴������������¼�Ŵ������Ӧ��ԭʼ�������Ǹ���
	*/
	xint32								nOriginalMeshIndex = -1;		
	XArray<XBlendShapeTarget>			aTargets;
	XArray<XBlendShapeChannel>			aChannels;	
};


class XSkinBlendShapeWeight
{
	friend class XSkinBlendShapeTarget;
public:
	/*
	* Ȩ�ض�Ӧ���������
	*
	* @notice һ��Ȩ�ص��ڶ��ǻ���fbx�е��������Է������������OriginalMesh����
	*
	* @param	RawMesh		��Ӧת��ģ��ʱ���������
	* @param	OriginalMesh   ��Ӧfbx�е�ԭʼ����  
	*/
	enum MeshWeightType
	{
		RawMesh,
		OriginalMesh,
	};
public:
                                        XSkinBlendShapeWeight() : m_pTargetBlendShapeTarget(NULL), m_eMeshWeightType(MeshWeightType::OriginalMesh) {}
                                        XSkinBlendShapeWeight(XSkinBlendShapeWeight&& other);
	XSkinBlendShapeWeight&				operator=(const XSkinBlendShapeWeight& other);
	XSkinBlendShapeWeight&				operator=(XSkinBlendShapeWeight&& other);

	MeshWeightType						GetMeshWeightType() const { return m_eMeshWeightType; }

	const XSkinBlendShapeTarget*		m_pTargetBlendShapeTarget;
	MeshWeightType						m_eMeshWeightType;
	/*
	* @notice ������������ [mesh index][morph channel index]
	*/
	XArray<XArray<xfloat32>>				m_afWeights;
	
};

class XModel;
struct XSkinModelBlendShapeWeight
{
public:
                                        XSkinModelBlendShapeWeight();
                                        XSkinModelBlendShapeWeight(const XModel* pTargetSkinModel, XSkinBlendShapeWeight::MeshWeightType meshType = XSkinBlendShapeWeight::MeshWeightType::OriginalMesh);
                                        
                                        XSkinModelBlendShapeWeight(const XSkinModelBlendShapeWeight& other);
                                        XSkinModelBlendShapeWeight(XSkinModelBlendShapeWeight&& other);
	XSkinModelBlendShapeWeight&			operator=(const XSkinModelBlendShapeWeight& other);
	XSkinModelBlendShapeWeight&			operator=(XSkinModelBlendShapeWeight&& other);

	xbool                               IsEmpty() const { return m_aWeights.Num() == 0; }

	void                                AdditiveBlendFrom(const XSkinModelBlendShapeWeight& morphWeights, xfloat32 fBlendWeight);
	void                                LerpBlendFrom(const XSkinModelBlendShapeWeight& morphWeights, xfloat32 fBlendWeight);
	void                                OverrideFrom(const XSkinModelBlendShapeWeight& morphWeights);
	void                                ClearValueToZero();

	friend xbool                        operator==(const XSkinModelBlendShapeWeight& left, const XSkinModelBlendShapeWeight& right);
	friend xbool                        operator!=(const XSkinModelBlendShapeWeight& left, const XSkinModelBlendShapeWeight& right) { return !(left == right); }	

#if UPDATEBLENDSHAPE_ASYNC
	void								SetInUseByBlendShapeInstance(xbool inUse) const;

	mutable std::atomic<xbool>			m_bInUseByBShpInstance;	
#endif	
	const XModel*						m_pTargetSkinModel = NULL;
	/*
	* @notice ������������ [skin index][morph target index]
	*/
	XArray<XArray<XSkinBlendShapeWeight>>	m_aWeights;

private:
	void								MultiplyWeight(xfloat32 fBlendWeight);    
};

class XThreadMutex;

struct BlendShapeWeightBufferWithMutex
{
     BlendShapeWeightBufferWithMutex(const XSkinModelBlendShapeWeight& weights, XThreadMutex* pBShpWeightMutex)
          : weights(weights), pBShpWeightMutex(pBShpWeightMutex) {}

	const XSkinModelBlendShapeWeight&        weights;
	XThreadMutex*							 pBShpWeightMutex;
};

class XSkinBlendShapeTarget : public IBlendShapeAsset
{
public:
	struct RangePair
	{
		xint32 e1;
		xint32 e2;
	};
public:
                                             XSkinBlendShapeTarget() = default;
                                             ~XSkinBlendShapeTarget();
                                             XSkinBlendShapeTarget(XSkinBlendShapeTarget const& other) = delete;
                                             XSkinBlendShapeTarget(XSkinBlendShapeTarget&& other);
	XSkinBlendShapeTarget&                   operator =(XSkinBlendShapeTarget const& other) = delete;
	XSkinBlendShapeTarget&                   operator =(XSkinBlendShapeTarget&& other);

	void                                     Release();

	static const XString&                    FileExtension() { static XString strExtension = ".mph"; return strExtension; }

	xint32                                   GetMeshBShpTargetNum() const { return m_aMeshBShpTargets.Num(); }
	xint32	                                 GetOriginalMeshNum() const { return m_anOriginalMeshIndexToRawMeshStartIndex.Num() - 1; }
	
	/*
	* ��ȡ�����BlendShapeTarget
	*
	* @param	nMeshIndex ��Ӧת��ģ�ͺ��ֵ���������
	*/
	const XMeshBlendShapeTarget*			GetMeshBShpTarget(xint32 nMeshIndex) const { return m_aMeshBShpTargets[nMeshIndex]; }

	const XString&							GetOriginalMeshName(xint32 nOriginalMeshIndex) const { return m_astrOriginalMeshNames[nOriginalMeshIndex]; }
	RangePair								GetOriginalMeshToRawMeshRange(xint32 nOriginalMeshIndex) const { return { m_anOriginalMeshIndexToRawMeshStartIndex[nOriginalMeshIndex], m_anOriginalMeshIndexToRawMeshStartIndex[nOriginalMeshIndex + 1] }; }
	
	XArray<XString>&						GetOriginalMeshNames() { return m_astrOriginalMeshNames; }
	const XArray<XString>&					GetOriginalMeshNames() const { return m_astrOriginalMeshNames; }

	/*
	* ��ȡԭʼ�����뵼��������Ķ�Ӧ��ϵ����
	*/
	const XArray<xint32>&                    GetOriginalMeshIndexToRawMeshStartIndexMapping() const { return m_anOriginalMeshIndexToRawMeshStartIndex; }

	/*
	* @notice ���ص��޸�m_anOriginalMeshIndexToRawMeshStartIndex��ֵ
	*/
	XArray<xint32>&                          GetOriginalMeshIndexToRawMeshStartIndexMapping() { return m_anOriginalMeshIndexToRawMeshStartIndex; }	

	/*
	* ��ȡԭʼ��������Ⱦ����֮��Ķ�Ӧ��ϵ����
	*
	* @notice ���������Ӧ��ͷ�������ƣ�������Ի��ֳɸ��������(fix flk��ǰת�������������˹�ͷ�Ĺ�����������һ�㲻����Ϊ��ͷ�ٲ��)
	*/
	const XArray<xint32>&                    GetOriginalMeshIndexToRenderMeshStartIndexMapping() const { return m_anOriginalMeshIndexToRenderMeshStartIndex; }

	/*
	* @notice ���ص��޸�m_anOriginalMeshIndexToRenderMeshStartIndex��ֵ
	*/
	XArray<xint32>&                          GetOriginalMeshIndexToRenderMeshStartIndexMapping() { return m_anOriginalMeshIndexToRenderMeshStartIndex; }

	/*
	* �����SkinData��Blendshape�Ƿ�ƥ��
	*
	* @notice ����SkinData������һ������һͬ���ɵ�Blendshape����ƥ�䣬ֻҪ�˺�������Ϊtrue����˵���������С�
	*/
	xbool                                    IsTargetMatch(XSkinData& targetSkinData) const;

	virtual xbool                            DoSave(XFileBase* pFile) const override;
	virtual xbool                            DoLoad(XFileBase* pFile) override;

	XSkinBlendShapeWeight                    CreateBlendShapeWeightBuffer(XSkinBlendShapeWeight::MeshWeightType eMeshType) const;

	/*
	* ���� m_anOriginalMeshIndexToRenderMeshStartIndex ��Ӧ��ϵ
	*
	* @notice ���ص�ʱ��ᱻ����
	*/
	xbool								     BuildRuntimeMeshMapping(const XSkinData& buildTo);

	
	const XArray<XMeshBlendShapeTarget*>&    GetData() const { return m_aMeshBShpTargets; }
	XArray<XMeshBlendShapeTarget*>&		     GetData() { return m_aMeshBShpTargets; }

protected:
	virtual void						     OnReload() override;


	/*
	* �������BlendShapeTarget
	*
	* @notice	 �����е�˳�򣬶�Ӧת��ģ��ʱ���������
	*/
	XArray<XMeshBlendShapeTarget*>           m_aMeshBShpTargets;

	XArray<XString>                          m_astrOriginalMeshNames;

	/*
	* ԭʼ�����뵼����������Ŀ�ʼ������Ӧ��ϵ����
	*
	* @notice	��Ӧ��ϵ���� . ��ԭʼ������3���� ����ԭʼ����1������3���������Ӧ��ϵ����Ϊ[0,1,4,5]
	*		����ԭʼ����1��Ӧ��raw����ʼ����Ϊ1, ԭʼ����2��Ӧ��raw����ʼ����Ϊ4,��1��4֮���[1,2,3]���Ƕ�Ӧԭʼ����1�ġ�
	*/
	XArray<xint32>                           m_anOriginalMeshIndexToRawMeshStartIndex;

	/*
	* ԭʼ��������Ⱦ�����������Ӧ��ϵ����
	*
	* @notice ��Ӧ��������������ƣ� �˴�����Ϊ�����Ӧ��ͷ�������ƣ�
	*		������Ի��ֳɸ������Ⱦ����	(fix flk��ǰת�������������˹�ͷ�Ĺ�����������һ�㲻����Ϊ��ͷ�ٲ�֣� �������Ⱦ����Ҳ��skin�е���Ⱦ����ͬ��)
	*/
	XArray<xint32>                           m_anOriginalMeshIndexToRenderMeshStartIndex;

	XString                                  m_strTargetSkinDatXFile;
};


class XBlendShapeInstance
{
public:
	enum VertexType { Local,	Skin, Count };
	struct SkinBlendShapePack
	{
		struct BlendShapeVertexDefinePack
		{
            BlendShapeVertexDefinePack() : m_pVertexDefBShp(NULL) {}
            ~BlendShapeVertexDefinePack()	{ X_SAFEDELETE(m_pVertexDefBShp); }
			XVertexDesc*      m_pVertexDefBShp;
			VertexType        m_eVertexType = VertexType::Count;
		};

        SkinBlendShapePack() : m_pBShpLocalDynamicVB(NULL), m_pBShpSkinDynamicVB(NULL) {}
        ~SkinBlendShapePack() { Clear(); }
        SkinBlendShapePack(SkinBlendShapePack const& other) = delete;
        SkinBlendShapePack& operator=(SkinBlendShapePack const& other) = delete;
		void             Clear();

		XBlendShapeVertexVB* m_pBShpLocalDynamicVB;
		XBlendShapeVertexVB* m_pBShpSkinDynamicVB;
		XArray<BlendShapeVertexDefinePack> m_XBShpMeshVertexDefinePack; // [render mesh index]
	};

#if UPDATEBLENDSHAPE_ASYNC
	struct ResultGetter
	{
		ResultGetter() = default;
		ResultGetter(std::future<void> result);
		ResultGetter(ResultGetter&& other);
		ResultGetter& operator=(ResultGetter&& other);
		void Wait() const { if (result.valid()) result.wait(); }

		std::future<void> result;
	};
#endif

public:

                                   XBlendShapeInstance();
                                   ~XBlendShapeInstance();
                                   XBlendShapeInstance(const XModel* pSkinModel);
                                   XBlendShapeInstance(XBlendShapeInstance const& other) = delete;
                                   XBlendShapeInstance operator=(XBlendShapeInstance const& other) = delete;
                                   XBlendShapeInstance(XBlendShapeInstance&& other);
	XBlendShapeInstance&           operator=(XBlendShapeInstance&& other);

	void                           UpdateBlendShapeVertexBuffer(BlendShapeWeightBufferWithMutex BShpWeightBuffer, xbool& dirtyFlag);
#if UPDATEBLENDSHAPE_ASYNC
    void                           UpdateBlendShapeVertexBufferAsync(BlendShapeWeightBufferWithMutex BShpWeightBuffer, XBlendShapeInstance::ResultGetter& result, xbool& dirtyFlag);
#endif

	/*
	* �ύ��GPU����
	*
	* @notice ��Render��ᱻ����
	*/
	void                           CommitGPUBuffers();
	const XBlendShapeInstance::SkinBlendShapePack::BlendShapeVertexDefinePack* GetBlendShapeVertexDefinePack(xint32 nSkinIndex, xint32 nMeshIndex) const { return &m_apSkinBShpPacks[nSkinIndex]->m_XBShpMeshVertexDefinePack[nMeshIndex]; }

	void                           Clear() { m_apSkinBShpPacks.Clear(false); }

	XBlendShapeVertexVB*           GetBlendShapeVB(xint32 nSkinIndex, xint32 nMeshIndex);

private:

	void                           DoUpdateBlendShapeVertexBuffer(BlendShapeWeightBufferWithMutex BlendShapeWeightBuffer);
	void                           CreateVertexDefine(const XSkinData* pSkinData, xint32 nSkinIndex, xint32 nMeshIndex);

	XArray<SkinBlendShapePack*>    m_apSkinBShpPacks; // [skin index]
	const XModel*                  m_pTargetSkinModel = nullptr;

#if UPDATEBLENDSHAPE_ASYNC
	std::atomic<bool>              m_bUpdating;
#endif
};

#endif

