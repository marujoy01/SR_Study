#include "..\..\Header\FontMgr.h"


CFontMgr::CFontMgr()
{
}


CFontMgr::~CFontMgr()
{
	Free();
}

HRESULT CFontMgr::Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pFontTag, const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	return S_OK;
}

void CFontMgr::Render_Font(const _tchar * pFontTag, const _tchar * pString, const _vec2 * pPos, D3DXCOLOR Color)
{
}

CMyFont * CFontMgr::Find_Font(const _tchar * pFontTag)
{
	return nullptr;
}

void CFontMgr::Free()
{
}
