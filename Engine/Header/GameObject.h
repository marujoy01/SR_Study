#pragma once

#include "Component.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	CComponent*		Find_Component(const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual HRESULT	Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject()PURE;

protected:
	map<const _tchar*, CComponent*>		m_mapComponent[ID_END];
	LPDIRECT3DDEVICE9					m_pGraphicDev;

public:
	virtual void			Free();
};

END