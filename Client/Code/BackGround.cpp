#include "stdafx.h"
#include "..\Header\BackGround.h"

#include "Export_System.h"
#include "Export_Utility.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
}

CBackGround::CBackGround(const CBackGround & rhs)
	: Engine::CGameObject(rhs)
{
}

CBackGround::~CBackGround()
{
}

HRESULT CBackGround::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_LogoTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBackGround *	pInstance = new CBackGround(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("BackGround Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();
}

HRESULT CBackGround::Ready_GameObject()
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CBackGround::Update_GameObject(const _float& fTimeDelta)
{
	
	Engine::Add_RenderGroup(RENDER_UI, this);

	__super::Update_GameObject(fTimeDelta);
	
	return 0;
}

void CBackGround::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
}
void CBackGround::Render_GameObject()
{

	m_pTextureCom->Render_Textrue(0);

	m_pBufferCom->Render_Buffer();

}

//D3DXMatrixRotationAxis();	// 임의의 축회전 함수(결과 행렬, 임의의 축, 회전 각도)