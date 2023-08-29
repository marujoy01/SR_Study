#include "stdafx.h"
#include "..\Header\Player.h"

#include "Export_System.h"
#include "Export_Utility.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
}

CPlayer::CPlayer(const CPlayer & rhs)
	: Engine::CGameObject(rhs)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_PlayerTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer *	pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();
}

HRESULT CPlayer::Ready_GameObject()
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_pTransformCom->m_vScale.x = 2.f;


	return S_OK;
}

Engine::_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
		__super::Update_GameObject(fTimeDelta);

	Key_Input(fTimeDelta);

	return 0;
}

void CPlayer::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
}
void CPlayer::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pTextureCom->Render_Textrue(0);

	m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
void CPlayer::Key_Input(const _float & fTimeDelta)
{
	_vec3	vDir;

	m_pTransformCom->Get_Info(INFO_UP, &vDir);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		m_pTransformCom->Move_Pos(&vDir, fTimeDelta, 5.f);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		m_pTransformCom->Move_Pos(&vDir, fTimeDelta, -5.f);
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(90.f * fTimeDelta));
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(-90.f * fTimeDelta));
	}

}

//D3DXMatrixRotationAxis();	// 임의의 축회전 함수(결과 행렬, 임의의 축, 회전 각도)