#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();
	
public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

private:
	HRESULT					Add_Component();
	void					Key_Input(const _float& fTimeDelta);

private:
	CRcTex*				m_pBufferCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free();


};

