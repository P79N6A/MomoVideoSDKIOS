/******************************************************************************

@File         XEEngine.h

@Version       1.0

@Created      2017, 6, 2

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_ENDGINE_H_
#define _XE_ENDGINE_H_

#include "XSys.h"
#include "XEngineRoot.h"
#include "XArray.h"

// Online version number, Maximum four segments of the number, the maximum number of each is 99.
#define ENGINE_CURR_VERSION "1.1.9"   

class XEEngine
{
public:
	class XEFrameListener
	{
	public:
		         XEFrameListener(){}
		virtual ~XEFrameListener(){}
	public:
		virtual void             OnPreFrame(){}
		virtual void             OnPostFrame(){}
		virtual void             OnFrameSizeChanged(){}
	};	                  
	virtual					    ~XEEngine();

	static XEEngine*		     GetInstance();
	static const XString		 GetEngineVersion();
	static xint32				 GetEngineVersionValue();
	static xint32				 ConverVersionStringToValue(const XString &strVersion);

	/*
		pBaseDir: indicated the directory of the engine working environment.
		pLibDir: indicated the directory of the project-related environment.
		typedef void 			(*FDebugOutput)(const char*);
	*/
	void					     Init(const xchar* pBaseDir = NULL, const xchar* pLibDir = NULL, const xchar* pDocumentDir = NULL, pOutputInfoFunction debugOutputFunc = NULL);
	void					     Release();
	void					     Frame();
	void                         AddFrameListener(XEFrameListener* pListener);
	void                         RemoveListener(XEFrameListener* pListener);	
	inline const XString&	     GetEngineBaseDir() { return m_strEngineResDir; }
	inline const XString&        GetAppProjectResDir(){ return m_strAppProjectResDir; }
	inline void                  SetAppProjectResDir(const xchar* pAppResDir){ if (pAppResDir) m_strAppProjectResDir = pAppResDir; }
	void					     Resize3DDrawWindow(IXPlatformWindow *pWindow);	
	/*
	  �л���ǰ��Ⱦ����(��ǰδ���жര��ͬʱ��Ⱦ��֧�֣�����ֻ֧�ֵ�ǰ��Ⱦ�����л���������ÿ֡Ƶ���л����л������п���)
	  @param bForce xtrue : ǿ��ִ���л������� xfalse : ���pWindow Ϊ��ǰ��Ⱦ���ڣ��������л�
	*/
	void						 SwitchCurrent3DDrawWindow(IXPlatformWindow *pWindow, xbool bForce = xfalse);
	// �������ڲ���������Ӧ����Ⱦ����
	xbool						 Create3DDrawWindow(IXPlatformWindow *pWindow);
	// ���������ڲ���Ӧ����Ⱦ����
	xbool						 Destroy3DDrawWindow(IXPlatformWindow *pWindow);
	IXPlatformWindow*		     GetCurrentDrawWindow();
	X_FORCEINLINE xbool          IsInit(){ return m_bInited; }
protected:
	XEEngine();
	void						 StartUp();
	void						 ShutDown();
	void                         ChangeFrameSize();
	void                         PreFrame();
	void                         PostFrame();
	xbool						 Create3DDrawWindowImpl(IXPlatformWindow *pWindow);
	xbool				         m_bInited;
	XString				         m_strEngineResDir;
	XString                      m_strAppProjectResDir;
	XArray<XEFrameListener*>     m_FrameListenerList;
};

#endif


