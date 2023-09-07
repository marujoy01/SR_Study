#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CCalculator;

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
	void					Height_On_Terrain();

private:
	CRcTex*				m_pBufferCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free();


};

// 뷰스페이스 변환 행렬 함수 lookatlh
// 원근 투영 행렬 함수 perspectiveFovLh

// 직접 구현하기