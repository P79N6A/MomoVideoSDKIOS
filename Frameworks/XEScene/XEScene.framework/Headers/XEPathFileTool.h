/******************************************************************************

@File         XEPathFunc.h

@Version       1.0

@Created      2017, 6, 14

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_PATHFUNC_H_
#define _XE_PATHFUNC_H_

#include <vector>
#include <string>
#include "XPlatform.h"

using std::vector;
using std::string;

//will not actually operate the files.
namespace XEPathFileTool
{
#if X_PLATFORM_WIN_DESKTOP
	// [WINDOWS ONLY]�ж��ļ����У��Ƿ���� 
	bool IsFileOrDirExist(const char* pathname);
	// [WINDOWS ONLY]��ȡ��������·����ָ����׺���ļ�
	std::vector<std::string> GetFileWithExt(const char* path, const char* ext);
	// [WINDOWS ONLY]ʹ��ϵͳ����ɾ���ļ���,��QT��������QT������ʹ��XEFileHelper::removePath
	bool DeleteDir(const char* pathname);
	// [WINDOWS ONLY]ʹ��ϵͳ����ɾ���ļ�����QT��������QT������ʹ��XEFileHelper::removePath
	bool Deletefile(const string &strFilePath);
	void GetAllFormatFiles(string fileFolderPath, vector<string>& files, string fileExtension);
	// [WINDOWS ONLY]ʹ��ϵͳ������ļ�����QT���� ����QT������ʹ��XEFileHelper::CopyFileToPath
	bool Copyfile(const string &strFromPath, const string &strToPath);
	// [WINDOWS ONLY]
	bool CreateFolderByPath(const char* path);
#endif
	//���reverseΪtrue��ת��Ϊ/(��б��)������Ϊ\(б�ܣ�Windows������ʶ�𣬲�ʶ��/)
	void NormalPath(string& strFullName, bool reverse = true);
	void NormalPath(char *pFullName, bool reverse = true);
	//����/����·��
	void EncodePath(const string &strKey, string &strpath);
	void DecodePath(const string &strKey, string &strpath);
	// ��ȡӦ�ó���Ŀ¼·��,Androidƽ̨��֧��!��ʹ��JNI AssetManager������������ȡ
	string GetAppPath();
	// ������·���еõ�Ŀ¼����
	string GetPathDir(const string &strFullName);
	// �������������еõ�����(����׺��)
	string GetFileName(const string& strFullName);
	// ��ȡ��׺��
	string GetFileExt(const std::string &strName);
	// ȥ����׺��
	string GetFilePathExceptExt(const std::string &strName);
	// ��ȡ���·��
	bool GetRaletivePath(const string &strFullPath, const string &strParentPath, string &strRelativePath);
	// �ж����·��
	bool IsRaletivePath(const string &strFullPath, const string &strParentPath);
	//��·��,�罫root/bb/../aa ��Ϊroot/aa 
	void ExpandPath(string &strPath);
	//�����ַ���
	void SplitString(const string &str, const string &mak, vector<string> &vstr);
	//ȥ�����˿հ��ַ�
	const string& Strtrim(string &s);

};

#endif


