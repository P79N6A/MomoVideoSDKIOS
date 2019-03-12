#ifndef _PHYSICAL_MANAGER_H_
#define _PHYSICAL_MANAGER_H_

#include "XMath3D.h"
#include "XArray.h"
#include "XPhysicalInterface.h"
#include "IXRigidBody.h"
#include "IXPhysicsRes.h"
#include "IXSkeletalPhysicsInstance.h"

class IXCloth;
class XBaseCoordSpace;
class IXPhysicsScene;

class IXPhysicalManager : public IXPhysicalManagerBase
{
public:
	virtual					~IXPhysicalManager() {};

	/**
	* ��ʼ�����ͷ�
	*/
	virtual xbool			Init() = 0;
	virtual void			Release() = 0;
	
	/**
	* ����һ��������
	* @note ����󳡾���������
	*		������delete
	*
	* @param szSceneName ��������
	* @return ����ָ�룬����ʧ�ܷ���NULL
	*/
	virtual IXPhysicsScene*	CreateScene(const xchar* szSceneName) = 0;

	/*---------------------------*/
	/*------Cloth Interface------*/
	/*---------------------------*/

	/**
	* ��һ��ģ��ʵ����ĳ��Mesh�ϻ�ȡ����ʵ��
	*
	* @param pInstance ģ��ʵ����ָ��
	* @param szMeshName mesh������
	* @return ����ʵ����ָ��, ���û�а󶨲��Ϸ��ؿ�ָ��
	*/
	virtual IXCloth*		GetCloth(IXModelInstance* pInstance, const xchar* szMeshName) = 0;
	
	/**
	* ��һ��ģ��ʵ����ȡ���еĲ���ʵ��
	*
	* @param pInstance ģ��ʵ����ָ��
	* @param aCloth Cloth����
	* @return 
	*/
	virtual void			GetCloth(IXModelInstance* pInstance, XArray<IXCloth*>& aCloth) = 0;

	/**
	* ��ȡ���д����ϵ�mesh����
	*
	* @param pInstance ģ��ʵ����ָ��
	* @param out aMeshName �󶨲��ϵ�mesh��������
	* @return 
	*/
	virtual void			GetMeshNameWithCloth(IXModelInstance* pInstance, XArray<XString>& aMeshName) const = 0;

	/**
	* ��Ӳ���ϼ���һ������ʵ��
	* @note ��Դ�������������AddCloth��ӵ�ģ�ͳɹ����������ֶ��ͷţ�������Ҫ������Release
	* 
	* @param szPath ���ϵ�·��
	* @return ����ʵ����ָ��, ���ʧ�ܷ��ؿ�ָ��
	*/
	virtual IXCloth*		CreateCloth(const xchar* szPath) = 0;

	/**
	* �Զ�������ʵ����ģ�Ͱ󶨣����ݲ���������ƥ��
	*
	* @param pInstance ģ��ʵ��ָ��
	* @param pCloth ����ʵ��ָ��
	*/
	virtual xbool			AddCloth(IXModelInstance* pInstance, xint32 nSkinIndex, IXCloth* pCloth) = 0;
	
	/**
	* �Ƴ�ģ��ʵ��ĳ��mesh�����в���
	* @note �����Ƴ����ֱ��Release������Դ,�Ժ���ܻ��޸�
	*
	* @param pInstance ģ��ʵ��ָ��
	*/
	virtual void			RemoveCloth(IXModelInstance* pInstance) = 0;


	// ͣ��
	/**
	* ������ʵ����ģ�͵�ĳ��mesh��
	*
	* @param pInstance ģ��ʵ��ָ��
	* @param szMeshName ģ��mesh����
	* @param pCloth ����ʵ��ָ��
	* @return ʧ�������mesh�Ѱ�/cloth�Ѱ�/meshNameδ�ҵ�/�������Ʋ�ƥ���.
	*/
	virtual xbool			AddCloth(IXModelInstance* pInstance, xint32 nSkinIndex, const xchar* szMeshName, IXCloth* pCloth) = 0;

	/**
	* �Ƴ�ģ��ʵ��ĳ��mesh�Ĳ���
	* @note �����Ƴ����ֱ��Release������Դ,�Ժ���ܻ��޸�
	*
	* @param pInstance ģ��ʵ��ָ��
	* @param szMeshName ģ��mesh����
	*/
	virtual void			RemoveCloth(IXModelInstance* pInstance, const xchar* szMeshName) = 0;
	// ͣ��


	/**
	* ��ģ��ʵ����ǰ�Ĳ�����Ϣ���õ�Skin��
	* @note ����ʹ��,����Skin��Saveǰ����,���򽫲������ģ�͵Ĳ�����Ϣ
	* 
	* @param pInstance ģ��ʵ��ָ��
	*/
	virtual void			SetClothInfoToSkin(IXModelInstance* pInstance) = 0;
	
	/**
	* ���沼���ļ�
	* @note ��ǰ���Ա����ֻ�в�����Ϣ
	*
	* @param pInstance ģ��ʵ��ָ��
	*/
	virtual xbool			SaveCloth(const xchar* szFile, IXCloth* pCloth) = 0;

	/*-------------------------------*/
	/*------RigidBody Interface------*/
	/*-------------------------------*/

	/**
	* ����һ������
	* @note ������delete
	*
	* @param eType ��������
	* @param pBindObject һ��BaseCoordSpace��,��ǰ��ģ�ͺ���Ч
	*/
	virtual IXRigidBody*	CreateRigidBody(RigidActorType eType, XBaseCoordSpace* pBindObject) = 0;
	
	/**
	* ��Ӳ���ϼ���һ��������Դ(��ײ��)
	* @note ������Release
	*
	* @param szPath phy��·��
	* @param bReload �Ƿ��ؼ���
	* @return ������Դ��ָ��, ���ʧ�ܷ��ؿ�ָ��
	*/
	virtual IXPhysicsRes*	LoadPhysicsRes(const xchar* sz, xbool bReload = xfalse) = 0;	

	/**
	* �ӹ���������Դ������������ʵ��
	*
	* @param szSkeletalPhysicsRes ����������Դ��·��
	* @return ��������ʵ����ָ��, ���ʧ�ܷ��ؿ�ָ��
	*/
	virtual IXSkeletalPhysicsInstance* CreateSkeletalPhysicsInstance(const xchar* szSkeletalPhysicsRes, IXModelInstance* pModelInstance, IXPhysicsScene* pOwningScene) = 0;

	/**
	* ȫ�ַ�Ч
	*/
	virtual void			SetWindSpeed(xfloat32 fWindSpeed) = 0;
	virtual xfloat32		GetWindSpeed() const = 0;
	virtual void			SetWindDir(const XVECTOR3& vDir) = 0;
	virtual const XVECTOR3&	GetWindDir() const = 0;

	/**
	* ���º������������ڲ�����
	*/
	virtual IXCloth*		LoadClothText(const xchar* szPath) = 0;
	virtual IXPhysicsRes*	CreatePhysicsRes(PhysicsResourceType eType, const xchar* szName = NULL) = 0;
	virtual xbool			SavePhysicsRes(const xchar* szFile, IXPhysicsRes* pRes) = 0;
};

extern IXPhysicalManager* g_pIXPhysicalManager;

#endif