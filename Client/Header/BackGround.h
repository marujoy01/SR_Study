#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class CRcCol;
class CTransform;

END

class CBackGround : public Engine::CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBackGround(const CBackGround& rhs);
	virtual ~CBackGround();
	
public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

private:
	HRESULT					Add_Component();
	void					Key_Input(const _float& fTimeDelta);

private:
	CRcCol*				m_pBufferCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;

public:
	static CBackGround*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free();


};

