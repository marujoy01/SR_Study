#include "stdafx.h"
#include "..\Header\Terrain.h"

#include "Export_System.h"
#include "Export_Utility.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
}

CTerrain::CTerrain(const CTerrain & rhs)
	: Engine::CGameObject(rhs)
{
}

CTerrain::~CTerrain()
{
}

HRESULT CTerrain::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTerrainTex*>(Engine::Clone_Proto(L"Proto_TerrainTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_TerrainTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CTerrain * CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain *	pInstance = new CTerrain(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Terrain Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTerrain::Free()
{
	__super::Free();
}

HRESULT CTerrain::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CTerrain::Update_GameObject(const _float& fTimeDelta)
{
	Key_Input(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 	__super::Update_GameObject(fTimeDelta);
}

void CTerrain::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
}
void CTerrain::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	

	m_pTextureCom->Render_Textrue(0);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
void CTerrain::Key_Input(const _float & fTimeDelta)
{
	_vec3	vDir;

	m_pTransformCom->Get_Info(INFO_UP, &vDir);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		m_pTransformCom->Move_Pos(&vDir, fTimeDelta, 8.f);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		m_pTransformCom->Move_Pos(&vDir, fTimeDelta, -8.f);
	}

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_X, D3DXToRadian(90.f * fTimeDelta));
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_X, D3DXToRadian(-90.f * fTimeDelta));
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(90.f * fTimeDelta));
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(-90.f * fTimeDelta));
	}

	if (GetAsyncKeyState('E') & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(90.f * fTimeDelta));
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(-90.f * fTimeDelta));
	}
}

