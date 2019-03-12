#ifndef _XFACERIG_ANIM_H_
#define _XFACERIG_ANIM_H_

#include "XHashTable.h"
#include "XXMLExtendTool.h"
#include "XBlendShapeAnim.h"
#include "XBoneController.h"
#include "XBlendShapeAnim.h"

struct xFaceRigBoneControl
{
	XString strBoneName;
	xfloat32 fWeight;
};


class XFaceRigSetting
{
public:
	XFaceRigSetting(){}
	~XFaceRigSetting(){}

	xbool Load(const XString &strFilePath);

	// ʶ��״̬��channel�Ķ�Ӧ, channel = skinname-morphtargetname-meshtargetname-channelname
	XHashTable<XString, XString> m_mStateToChannel;

	// ֡�����ļ�
	//XArray<XString> m_vSeq;

	// Ҫ�������Ϊ���ӹ�ϵ�� ������˳��Ϊ�� �� / �θ� / �δθ�	
	XArray<xFaceRigBoneControl> m_vControlBone;

protected:

	void Clear();
	xbool LoadVersion0(tinyxml2_XEngine::XMLElement* pRootNode);
};

struct FaceRigParam
{
	XHashTable<XString, xfloat32>  mStateWeight;
	XVECTOR3					   vEuler;
};

struct xFaceRigControllerInfo
{
	xFaceRigControllerInfo() : strBoneName(""), fWeight(0.0f), pController(NULL)  {}
	XString					  strBoneName;
	xfloat32				  fWeight;
	XBoneWorldRotController	  *pController;	
};

class XFaceRigAnim : public XBlendShapeAnim
{
public:
									XFaceRigAnim(IXModelInstance *pIns);
	virtual							~XFaceRigAnim();

	void							LoadSettingFile(const XString &strFileName);
	void							TickFaceRigParam(const FaceRigParam &param, xbool bClearAllBeforeApply = xtrue);

	/* ��������morph weight ����������Ϣ����channel��Ӧ��ϵ
	   ��ǰģ��skin����ɾ��ʱ��weight��channel�ȼ�¼��Ҫ�������ɣ�
	*/
	void							ReGenerateFaceRigInfo(xbool bGenerateWeight = xtrue, xbool bGenerateChannelIndexBySetting = xtrue);

	inline void						SetFaceRigBlendWeight(xfloat32 fBlendWeight) { m_fFaceRigBlendWeight = fBlendWeight; }
	inline xfloat32					GetFaceRigBlendWeight() { return m_fFaceRigBlendWeight; }

	/*�Ը��ǵķ�ʽ������ǰanim�����ģ���ͷ���ƣ��󶨵��Ǽ��ϡ�
	*/
	xbool						    ReBindBoneControllerToSkinmodelInsSkeleton();
	/*����FaceRigParam����
	*/
	void							ReSetFaceRigParam();

	/* ȥ����ͷ����������skinmodel�������
	*/
	void						    UnbingBoneController();

	/* ��û�����ù�ͷʱ�����Ұڶ����Ƿ�ֱ�Ӱڶ�ģ��
	*/
	X_FORCEINLINE void				SetRotateModelOfNoBoneControl(xbool bEnable) { m_bRotateModelOfNoBoneControl = bEnable; }
	X_FORCEINLINE xbool				GetRotateModelOfNoBoneControl() const { return m_bRotateModelOfNoBoneControl; }

protected:
	virtual	void					MergeUserMorphAndBone() override;
	void							GenerateChannelIndexBySetting();
	void							MergeFaceRigSke();
	void							MergeFaceRigMorphWeight();
	void							ReleaseController(xbool bUnbindOfBone = xfalse);

	XSkinModelBlendShapeWeight		m_CurrentFaceRigMorphWeights;
	XVECTOR3					    m_vFaceRigEuler;
	xfloat32						m_fFaceRigBlendWeight;
	/* ��û�����ù�ͷ�������Ұڶ�ʱ���Ƿ�ֱ�Ӱڶ�ģ��
	*/
	xbool							m_bRotateModelOfNoBoneControl;

	// Ȩ��������
	struct ChannelKey
	{
		xint32 nSkiIndex;
		xint32 nSkinMorphTargetIndex;
		xint32 nMeshMorphTargetIndex;
		xint32 nChannelIndex;
	};
	XHashTable<XString, ChannelKey>	 m_mStateToChannelIndex;
	XArray<xFaceRigControllerInfo>	 m_vControlBoneController;

	XString							m_strSettingFile;
	XFaceRigSetting					m_Setting;
};

#endif


