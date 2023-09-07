#include "stdafx.h"
#include "..\Header\SkyBox.h"

#include "Export_System.h"
#include "Export_Utility.h"

CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
}

CSkyBox::CSkyBox(const CSkyBox & rhs)
	: Engine::CGameObject(rhs)
{
}

CSkyBox::~CSkyBox()
{
}

HRESULT CSkyBox::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"Proto_CubeTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_SKyBoxTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Calculator", pComponent });

	return S_OK;
}

CSkyBox * CSkyBox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkyBox *	pInstance = new CSkyBox(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SkyBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkyBox::Free()
{
	__super::Free();
}

HRESULT CSkyBox::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->m_vScale = { 40.f, 40.f, 40.f };

	return S_OK;
}

Engine::_int CSkyBox::Update_GameObject(const _float& fTimeDelta)
{

	Engine::Add_RenderGroup(RENDER_PRIORITY, this);

	return 	__super::Update_GameObject(fTimeDelta);
}

void CSkyBox::LateUpdate_GameObject()
{
	_matrix	matCamWorld;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);
	D3DXMatrixInverse(&matCamWorld, nullptr, &matCamWorld);

	m_pTransformCom->Set_Pos(matCamWorld._41, matCamWorld._42 + 3.f, matCamWorld._43);
}
void CSkyBox::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	
	m_pTextureCom->Render_Textrue(3);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}



