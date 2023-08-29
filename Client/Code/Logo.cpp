#include "stdafx.h"
#include "..\Header\Logo.h"

#include "Export_System.h"
#include "Export_Utility.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);

	return S_OK;
}

_int CLogo::Update_Scene(const _float & fTimeDelta)
{
	_int	iExit = __super::Update_Scene(fTimeDelta);

	return iExit;
}

void CLogo::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CLogo::Render_Scene()
{
	__super::Render_Scene();

}

HRESULT CLogo::Ready_Prototype()
{
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TriCol", CTriCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcCol", CRcCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcTex", CRcTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Transform", CTransform::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LogoTexture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Logo/IU.jpg")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerTexture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Ma.jpg")), E_FAIL);

	return S_OK;
}

HRESULT CLogo::Ready_Layer_Environment(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// background
	pGameObject = CBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BackGround", pGameObject), E_FAIL);
	
	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo *	pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Logo Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLogo::Free()
{


	__super::Free();
}
