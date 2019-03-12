#ifndef _IXRIGIDACTOR_H_
#define _IXRIGIDACTOR_H_

#include "XMath3D.h"

class IXPhysicsRes;
class XBaseCoordSpace;
enum RigidActorType
{
	// ��̬��ֻ��Ӱ���������壬�����ᱻӰ��
	RAT_STATIC,
	// ��̬��Ӱ���������壬����Ҳ�ᱻӰ��
	RAT_DYNAMIC,
	// future, ����ѧ����̬��һ���������ͣ���������������������Ӱ�죬����������̬Actor��KINEMATIC Actor��ײ
	// RAT_KINEMATIC,
};

/****************************************/
/* ������״�������						*/
/********************** *****************/
struct XShapeMaterial
{
	XShapeMaterial(xfloat32 sf, xfloat32 df, xfloat32 r)
		: fStaticFriction(sf)
		, fDynamicFriction(df)
		, fRestitution(r){}
	/**
	* ��Ħ��ϵ��
	*
	* @range [0, X_MAX_FLT32]
	*/
	xfloat32	fStaticFriction;

	/**
	* ��Ħ��ϵ��
	*
	* @range [0, X_MAX_FLT32]
	*/
	xfloat32	fDynamicFriction;

	/**
	* ����ϵ��
	* Խ����Խ��
	* @range [0, 1]
	*/
	xfloat32	fRestitution;
};

/****************************************/
/* ������								*/
/********************** *****************/
class IXRigidBody : public XMemBase
{
public:
	virtual						~IXRigidBody(){}
	
	/**
	* Ϊ�����һ��������Դ
	* @note ����ɹ�����������Դ�����ü�����1
	*
	* @param pRes ������Դ
	* @param bReplace �Ƿ��滻,���Ϊxtrue,����滻ԭ����Դ,���Ϊxfalse,δ�����,�Ѱ��򲻰�
	* @return �ɹ�����xtrue,ʧ�ܷ���xfalse
	*/
	virtual xbool				BindPhysicsRes(IXPhysicsRes* pRes, xbool bReplace = xfalse) = 0;

	/*
	* Get
	*/
	virtual XBaseCoordSpace*	GetBaseCoordSpace() = 0;

	/*
	* ��������ģ������
	*/
	virtual xbool				IsSimulate() const = 0;
	virtual void				SetSimulate(xbool bSet) = 0;

	/*
	* ��������
	*/
	virtual RigidActorType 		GetType() const = 0;
	virtual void				SetType(RigidActorType eType) = 0;
	
	/*
	* ������״�����������
	*/
	virtual XShapeMaterial		GetMaterial() const = 0;
	virtual void				SetMaterial(const XShapeMaterial& mat) = 0;

	/*
	* ������ײ�¼�����
	* @note ������������ڸ�����������������ײʱ����IXPhysicalSceneEventListener::OnContact
	*/
	virtual xbool				IsNotifyContact() const = 0;
	virtual void				SetNotifyContact(xbool bSet) = 0;

	/*
	* �Ƿ�����Ӱ��
	*/
	virtual xbool				IsGravityEnabled() const = 0;
	virtual void				SetGravityEnabled(xbool bSet) = 0;


	// ���º�������TypeΪDynamicʱ��Ч
	
	/*
	* ����CCD����
	* @note ��������Ӧ����CCD��������ЧӦ
	*/
	virtual xbool				IsCCDEnabled() const = 0;
	virtual void				SetCCDEnabled(xbool bSet) = 0;
	
	/*
	* ����������������λkg
	* @note 0������������
	* @range [0, X_MAX_FLT32]
	*/
	virtual xfloat32			GetMass() const = 0;
	virtual void				SetMass(xfloat32 f) = 0;

	/**
	* �����ٶȺͽ��ٶ�����
	* @note ���δ����ģ��,��Ч
	*/
	virtual XVECTOR3			GetLinearVelocity() const = 0;
	virtual void				SetLinearVelocity(const XVECTOR3& vVelocity) = 0;	
	virtual XVECTOR3			GetAngularVelocity() const = 0;
	virtual void				SetAngularVelocity(const XVECTOR3& vAngle) = 0;

	/*
	* �ٶ�����ϵ���ͽ��ٶ�����ϵ��
	*
	* @range [0, X_MAX_FLT32]
	*/
	virtual xfloat32			GetLinearDamping() const = 0;
	virtual void				SetLinearDamping(xfloat32 fLinearDamping) = 0;
	virtual xfloat32			GetAngularDamping() const = 0;
	virtual void				SetAngularDamping(xfloat32 fAngularDamping) = 0;
};

#endif
