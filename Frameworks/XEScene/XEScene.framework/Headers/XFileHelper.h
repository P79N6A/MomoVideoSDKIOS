/******************************************************************************

 @File         XFI.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  ��װ�����ļ���ص�һϵ�в���

 @HISTORY:

******************************************************************************/

#ifndef _XFILEHELPER_H_
#define _XFILEHELPER_H_

#include "XTypes.h"
#include "XString.h"

class XFileHelper
{
public:
	/*
	* ʹ���ļ���ع���֮ǰ���������ȵ��ñ�����
	* 
	* @notice	���ʹ��XFramework���򲻱ص���
	*
	* @param	szBaseDir �����Ŀ¼
	* @param	szLibraryDir �����Ŀ¼
	* @returns  ����xtrue
	*/
	static xbool		Init(const xchar* szBaseDir, const xchar* szDocuemnt, const xchar* szLibraryDir);
	
	/*
	* ʹ���ļ���ع���֮��ͨ���ǳ���ر�ʱ������
	*
	* @notice	���ʹ��XFramework���򲻱ص���
	*
	* @returns  ����xtrue
	*/
	static xbool		Close();
	
	/*
	* ֱ�����������Ŀ¼
	*
	* @param	szBaseDir �����Ŀ¼
	*/
	static void			SetBaseDir(const xchar* szBaseDir);

	/*
	* ��ȡ�����Ŀ¼
	*/
	static const xchar*	GetBaseDir();
	static const xchar*	GetLibraryDir();
    static const xchar* GetDocument();
	/*
	* ��һ��·������ȡ�ļ���
	*
	* @notice ����չ��
	*
	* @param	szFile ·��
	* @param	szTitle �ļ���
	*
	* @returns  �쳣��szFile��·���ָ���Ϊ��β�򷵻�xfalse����������xtrue
	*/
	static xbool 		GetFileTitle(const xchar* szFile, xchar* szTitle);
	static xbool 		GetFileTitle(const xchar* szFile, XString& strTitle);

	/*
	* ��һ��·������ȡ�ļ�����Ŀ¼
	*
	* @notice ��β����·���ָ���
	*
	* @param	szFile ·��
	* @param	szPath �ļ�Ŀ¼
	*
	* @returns  �쳣��szFile��·���ָ���Ϊ��β�򷵻�xfalse����������xtrue
	*/
	static xbool 		GetFilePath(const xchar* szFile, xchar* szPath);
	static xbool 		GetFilePath(const xchar* szFile, XString& strPath);

	/*
	* �ж��ļ�����չ���Ƿ�ƥ��
	*
	* @param	szFileName �ļ���
	* @param	szExtension ��չ��
	*
	* @returns  ƥ�䷵��true����ƥ�䷵��xfalse
	*/
	static xbool 		FileExtensionMatched(const xchar* szFileName, const xchar* szExtension);

	/*
	* �����ļ��ĺ�׺��
	*
	* @param	szFileName �ļ���
	* @param	szNewExtension �µ���չ��
	*
	* @returns  ����xtrue
	*/
	static xbool 		ChangeExtension(xchar* szFileName, const xchar* szNewExtension);
	static xbool 		ChangeExtension(XString& strFileName, const xchar* szNewExtension);

	/*
	* ����ļ��Ƿ����
	*
	* @param	szFileName �ļ���
	*
	* @returns  ���ڷ���xtrue�������ڷ���xfalse
	*/
	static xbool 		FileExisted(const xchar * szFileName);
	
	/*
	* �Ƴ��ļ���չ��
	*
	* @param	strFileName �ļ���
	*
	*/
	static void 		RemoveExtension(XString& strFileName);

	/*
	* �ļ�����׼����·���ָ�����Ϊ/
	*
	* @notice	IOSƽ̨��Ҫ��д��ĸ��·������˲�����ĸ�ĳ�Сд
	*
	* @param	szFileName �ļ���
	*
	*/
	static void 		Normalize(xchar* szFileName);
	static void 		Normalize(const xchar* szSrcFileName, xchar* szDstFileName);

	static void			GetRelativePathNoBase(const xchar* szFullpath, const xchar* szParentPath, xchar* szRelativepath);
	static void			GetRelativePathNoBase(const xchar* szFullpath, const xchar* szParentPath, XString& strRelativePath);
	static void			GetFullPathNoBase(xchar* szFullpath, const xchar* szBaseDir, const xchar* szFilename);
	static void			GetFullPathNoBase(XString& strFullpath, const xchar* szBaseDir, const xchar* szFilename);
	static void			GetFullPath(xchar* szFullPath, const xchar* szFolderName, const xchar* szFileName);
	static void			GetFullPath(xchar* szFullPath, const xchar* szFileName);
	static void			GetFullPath(XString& strFullPath, const xchar* szFolderName, const xchar* szFileName);
	static void			GetFullPath(XString& strFullPath, const xchar* szFileName);
	static void			GetFullPathWithUpdate(XString& strFullPath, const xchar* szFileName, bool bNoCheckFileExist = false);
	static void			GetFullPathWithDocument(XString& strFullPath, const xchar* szFileName, bool bNoCheckFileExist = false);
	static void			GetRelativePath(const xchar* szFullPath, const xchar* szFolderName, xchar* szRelativePath);
	static void			GetRelativePath(const xchar* szFullPath, xchar* szRelativePath);
	static void			GetRelativePath(const xchar* szFullPath, const xchar* szFolderName, XString& strRelativePath);
	static void			GetRelativePath(const xchar* szFullPath, XString& strRelativePath);
};

#endif

