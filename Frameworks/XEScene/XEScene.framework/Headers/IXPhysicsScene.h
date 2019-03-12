#ifndef _IXPHYSICSSCENE_H_
#define _IXPHYSICSSCENE_H_

#include "XArray.h"
#include "XMath3D.h"

class IXCloth;
class IXRigidBody;
class IXWorld;
class IXSkeletalPhysicsInstance;

/****************************************/
/* �������¼�������						*/
/********************** *****************/
class IXPhysicalSceneEventListener : public XMemBase
{
public:
	/**
	* ��������ײʱ�ص�
	*
	* @param ��ײ������Actor
	*/
	virtual void OnContact(IXRigidBody* pBody0, IXRigidBody* pBody1) = 0;
};

/********************************************************/
/* ��������											*/
/* �����������ӵ��������е���Դ,�������ϡ����塢��������	*/
/********************** *********************************/
class IXPhysicsScene : public XMemBase
{
public:
	virtual ~IXPhysicsScene(){}

	/**
	* ��ȡ����������
	*/
	virtual const xchar*		GetName() = 0;
	
	/**
	* ��������ӵ�������
	*
	* @param  pCloth ����ָ��
	* @return ʧ���������������ӵ���������
	*/
	virtual xbool				AddCloth(IXCloth* pCloth) = 0;
	
	/**
	* ��һ�鲼����ӵ�������
	* @note	������Ӹ����ϣ������һ��ʧ�ܣ�����ִ��֮��Ĳ���
	* @param  aCloth ��������
	* @return ����һ���������ʧ�ܷ���xfalse
	*/
	virtual xbool				AddCloth(const XArray<IXCloth*>& aCloth) = 0;
	
	/**
	* �����ϴӳ������Ƴ�
	*
	* @param  pCloth ����ָ��
	*/
	virtual void				RemoveCloth(IXCloth* pCloth) = 0;

	/**
	* ��һ��������ӵ�������
	* 
	* @param  pRigidBody ����ָ��
	* @return ʧ���������������ӵ���������
	*/
	virtual xbool				AddRigidBody(IXRigidBody* pRigidBody) = 0;
	
	/**
	* ������ӳ������Ƴ�
	*
	* @param  pRigidBody ����ָ��
	*/
	virtual void				RemoveRigidBody(IXRigidBody* pRigidBody) = 0;

	/*
	* Tick
	*/
	virtual void				Tick(xfloat32 fTime) = 0;
	/*
	* Render�����еĲ���
	*/
	virtual void				Render(IXWorld* pScene) = 0;

	/*
	* Ϊ������Ӽ�����
	*/
	virtual void				AddEventListener(IXPhysicalSceneEventListener* pListener) = 0;
	/*
	* �Ƴ�������
	*/
	virtual void				RemoveEventListener(IXPhysicalSceneEventListener* pListener) = 0;

	/*
	* ���ó�����������
	*/
	virtual XVECTOR3			GetGravity() = 0;
	virtual void				SetGravity(const XVECTOR3& vGravity) = 0;
};

#endif
