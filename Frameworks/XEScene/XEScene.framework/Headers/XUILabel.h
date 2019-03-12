/******************************************************************************

@File         UILabel.h

@Version       1.0

@Created      2018, 6, 13

@Description  

@HISTORY:

******************************************************************************/

#ifndef _XUI_LABEL_H_
#define _XUI_LABEL_H_

#include "XUIWidget.h"
#include <string>

class IXUIFontTexture;
class XUIFontSprite;
class IXUIFontSysTexture;
struct XUISysFontDef;

#ifdef DEBUG
	#define _X_FontDebug 0
#endif // DEBUG

enum XUITextVAlignment
{
	XUI_TV_TOP,
	XUI_TV_CENTER,
	XUI_TV_BOTTOM
};

enum XUITextHAlignment
{
	XUI_TH_LEFT,
	XUI_TH_CENTER,
	XUI_TH_RIGHT
};

enum XUIGlyphCollection {
	XUI_GC_DYNAMIC,
	XUI_GC_CUSTOM
};

struct XUITTFConfig
{
	explicit XUITTFConfig(const XString& _strFilePath = "", xfloat32 _fontPointSize = 12, xint32 _nOutline = 0,
		const XUIGlyphCollection& _eGlyphCollection = XUIGlyphCollection::XUI_GC_DYNAMIC, const xchar *_pCustomGlyphCollection = NULL)
		: strFontFilePath(_strFilePath)
		, fontPointSize(_fontPointSize)
		, eGlyphs(_eGlyphCollection)
		, pCustomGlyphs(_pCustomGlyphCollection)
		, nOutlineSize(_nOutline)
	{}

	XString				strFontFilePath;		// �����ļ�·��
	xfloat32			fontPointSize;			// ���������С   

	XUIGlyphCollection	eGlyphs;				// ��������
	const xchar			*pCustomGlyphs;			// �Զ�������ʱ��Ԥ���ɵ��ַ�
	xint32				nOutlineSize;			// ����߽��߿� 

	// 	xbool				bItalics;				// б��
	//  xbool				bUnderline;				// �»���
	// 	xbool				bStrikethrough;			// ɾ����
};



class XUILabel : public XUIWidget
{
public:
	X_CLASS_DEF(XUILabel)

	enum XUIELabelEffect {
		XUI_NORMAL,
		XUI_OUTLINE
	};

public:

	static XUILabel*				CreateWithTTF();

	static XUILabel*				CreateWithTTF(const XUITTFConfig& ttfConfig, const XString& strUtf8Text, xint32 nLineWidth = 0,
										XUITextHAlignment hAlignment = XUI_TH_LEFT, XUITextVAlignment vAlignment = XUI_TV_TOP);

	static XUILabel*				CreateWithTTF(const XString& strUtf8Text, const XString& strFontFilePath, xfloat32 fontPointSize, xint32 nLineWidth = 0,
										XUITextHAlignment hAlignment = XUI_TH_LEFT, XUITextVAlignment vAlignment = XUI_TV_TOP);

	static XUILabel*				CreateWithSystemFont();
	static XUILabel*				CreateWithSystemFont(const XString& strUtf8Text, const XString& fontName, xfloat32 fontPointSize,
										XUITextHAlignment hAlignment = XUI_TH_LEFT, XUITextVAlignment vAlignment = XUI_TV_TOP);

public:
									XUILabel(XUITextHAlignment hAlignment = XUI_TH_LEFT,	XUITextVAlignment vAlignment = XUI_TV_TOP);
	virtual							~XUILabel();		
	virtual	const XVECTOR2&			GetContentSize() const override;
	virtual void					Visit(IXWorld* pWorld, const XMATRIX4& matParentTransform, xuint32 unParentFlags) override;
	virtual void					Draw(IXWorld* pWorld, xuint32 unParentFlags) override;

	/*
		Ӧ������
	*/	
	void							UpdateImmediately();

	/*
		���������С
	*/
	void							SetTextPointSize(xfloat32 fPointSize);
	X_FORCEINLINE xfloat32			GetTextPointSize() const { return m_fOriginalFontSize; }

	/*
		��������
	*/
	void							SetTTFFontPath(const XString &strPath);
	X_FORCEINLINE const XString&	GetTTFFontPath() const { return m_strFontPath; }


	/*
		�����ı�����
	*/
	void							SetString(const XString &strUtf8Text);
	const XString&					GetString() const { return m_utf8Text; }
	xint32							GetStringCount() const { return (xint32)(m_utf32Text.length()); }

	/*
		�����ı����뷽ʽ�� hAlign �� ˮƽ���룬 vAlign ��ֱ����
	*/

	void							SetAlignment(XUITextHAlignment hAlign, XUITextVAlignment vAlign);
	void							SetHAlignMent(XUITextHAlignment hAlign);
	void							SetVAlignMent(XUITextVAlignment vAlign);
	X_FORCEINLINE XUITextHAlignment	GetHAlignment() { return m_eHAlignment; }
	X_FORCEINLINE XUITextVAlignment	GetVAlignment() { return m_eVAlignment; }

	/*
		�����ı�����, 
		@ fWidth��fHeightΪ С�ڵ��� 0.0�����ʾ��С�Զ���Ӧ�� ��Label�Ŀ�Ⱥ͸߶ȣ�������������Ⱥ͸߶��Զ�����
		  ��fWidth > 0.0���������п�ȳ���fWidth�������ʱ�Զ�����Ϊtrue�����Զ�����; Ϊfalse����ضϱ���
		  ��fHeight >0.0���������ܸ߶ȳ���fHeight����ض����֡�
	*/
	void							SetDimensions(xfloat32 fWidth, xfloat32 fHeight);
	XVECTOR2						GetDimensions() const { return XVECTOR2(m_fTextAreaWidth, m_fTextAreaHeight); }

	/* 
		�����ı���ɫ
	*/
	void							SetTextColor(const XCOLORBASE &clr);
	X_FORCEINLINE const XCOLORBASE&	GetTextColor() const { return m_TexColor; }

	/*
		�����ı����ּ��, ��TTF����֧��
	*/
	void							SetAdditionalKerning(xfloat32 fAdditionalKerning);
	X_FORCEINLINE xfloat32			GetAdditionalKerning() const { return m_fAdditionalKerning; }

	/*
		�����ı����м��, ��TTF����֧��
	*/
	void							SetLineSpacing(xfloat32 fLineSpacing);
	X_FORCEINLINE xfloat32			GetLineSpacing() const { return m_fLineSpacing; }

	/*
		�����Ƿ��Զ�����	
		@ Ĭ��true��Ϊfalseʱ��Ҫ��m_fLabelWidth > 0.0f���Ż�����Զ����д���
	*/
	void							SetEnableWrap(xbool bEnableWrap);
	X_FORCEINLINE xbool				GetEnableWrap() const { return m_bEnableWrap; }
	
	/*
		�����Ƿ����������ĵ����л���, ��TTF����֧��
	*/
	void							SetBreakOfWesternWord(xbool bBreakOfWesternWord);
	X_FORCEINLINE xbool				GetBreakOfWesternWord() const { return m_bBreakOfWesternWord; }
	
	/*
		����ϵͳ��������
	*/
	void							SetSystemFontName(const XString &strFontName);
	X_FORCEINLINE const XString&	GetSystemFontName() const {	return m_strSystemFontName; }

	/*
		�л���ϵͳ����
	*/
	void							ChangeToSystemFont();

	virtual xbool					SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;

	static const XString&			GetDefaultTTFPath() { return s_strDefaultTTFPath; }
	static void						SetDefaultTTFPath(const XString &strTemp) { s_strDefaultTTFPath = strTemp; }

protected:

	virtual XUINode*				CreateClonedInstance() override;
	virtual void					CopyProperties(XUINode* pNode) override;

	void							Reset();
	void							ClearData();
	void							ReleaseTTF();
	void							ReleaseSystemFInfo();

	xbool							UpdateContent();
	xbool							GenerateSpriteBuff(xint32 nSpriteNum);

// TTF
	xbool							InitWithTTF(const XUITTFConfig& ttfConfig, const XString& strText, xint32 nLabelWidth = 0);
	xbool							SetTTFConfiImpl(const XUITTFConfig& ttfConfig);
	xbool							ChangeFontTexture(IXUIFontTexture *pTexture, xbool bDistanceFieldEnabled);
	xbool							UpdateContentWithFontTexture();

	xbool							ComputeHorizontalKernings(const std::u32string& stringToRender);
	void							UpdateAlignmentOffet();
	void							UpdateFontSprite();
#if _X_FontDebug
	void							ShowTextureTest();
#endif

	xbool							ComputeMultilineTextWrap();
	void							ComputeAlignmentOffset();

	void							AddPlaceholderInfo(xint32 letterIndex, char32_t utf32Char);
	void							AddLetterInfo(const XVECTOR2& vPoint, char32_t utf32Char, xint32 nletterIndex, xint32 nlineIndex);

	xint32							GetFirstWordLen(const std::u32string& utf32Text, xint32 nStartIndex, xint32 nTextLen);
// ----

// System Font
	void							GetSysFontDef(XUISysFontDef *pDef) const;
	xbool							UpdateContentWithSystemFont();

// ----

	
	enum ELabelType 
	{
		XUIL_TTF = 0,
		XUIL_SYSTEMF,
	};

	struct LetterInfo
	{
		char32_t	utf32Char;
		xbool		valid;
		xfloat32	positionX;
		xfloat32	positionY;
		xint32		lineIndex;
	};

	ELabelType					m_eCurLabelType;
	xbool						m_bContentDirty;
	std::u32string				m_utf32Text;
	XString						m_utf8Text;
	
	xfloat32					m_fOutlineSize;
	//xbool						m_bUseDistanceField;
	xfloat32					m_fOriginalFontSize;

	XUIELabelEffect				m_eCurrLabelEffect;

	// align
	xfloat32					m_fTextAreaWidth;					
	xfloat32					m_fTextAreaHeight;
	XUITextHAlignment			m_eHAlignment;
	XUITextVAlignment			m_eVAlignment;	
	xfloat32					m_fAdditionalKerning;			// ���ӵ��ּ��
	xfloat32					m_fLineSpacing;					// ���ӵ��м��
	xfloat32					m_fLineHeight;					// �и�
	xbool						m_bEnableWrap;					// �Ƿ��Զ����У�Ĭ��true��Ϊfalseʱ��Ҫ��m_fLabelWidth > 0.0f���Ż�����Զ����д���
	xbool						m_bBreakOfWesternWord;			// �Ƿ����������ĵ����л���	

	// ---------------------------------TTF Draw buffer--------------------------------------------
	XString						m_strFontPath;
	XUITTFConfig				m_FontConfig;

	// align buf
	XArray<xint32>				m_vhorizontalKernings;

	//xint32						m_nLengthOfString;
	xfloat32					m_fTextDesiredHeight;
	XArray<xfloat32>			m_vLineWidth;
	XArray<xfloat32>			m_vlinesOffsetX;				// ���п�ʼƫ�� �ɶ����ϵ����
	xfloat32					m_fLetterOffsetY;				// ���о��붥��ƫ��
	xint32						m_nNumberOfLines;

	// draw
	XCOLORBASE					m_TexColor;
	IXUIFontTexture*			m_pFontTexture;
	XArray<LetterInfo>			m_vLettersInfo;
	
	XArray<XUIFontSprite*>		m_vFontSpriteBuf;
	XArray<XUIFontSprite*>		m_vDrawFontSprite;
	// -----------------------------------------end------------------------------------------------


	// -------------------------------------System font draw buffer---------------------------------
	IXUIFontSysTexture*			m_pSystempFontTexture;
	XString						m_strSystemFontName;


	// -----------------------------------------end-------------------------------------------------


	static XString				s_strDefaultTTFPath;
	
};



#endif
