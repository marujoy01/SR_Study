#pragma once

#include "Scene.h"

#include "TriCol.h"

class CLogo : public Engine::CScene
{
private:
	explicit CLogo(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLogo();

public:
	virtual HRESULT		Ready_Scene();
	virtual _int		Update_Scene(const _float& fTimeDelta);
	virtual void		LateUpdate_Scene();
	virtual void		Render_Scene();

private:
	HRESULT				Ready_Layer_Environment(const _tchar* pLayerTag);
	HRESULT				Ready_Layer_GameLogic(const _tchar* pLayerTag)	{ return S_OK; }
	HRESULT				Ready_Layer_UI(const _tchar* pLayerTag)			{ return S_OK; }

private:
	Engine::CTriCol*		m_pTriCol;

public:
	static CLogo*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void		Free();
};

