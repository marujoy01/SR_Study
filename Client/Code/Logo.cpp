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
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);

	m_pTriCol = Engine::CTriCol::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pTriCol, E_FAIL);

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

	m_pTriCol->Render_Buffer();
}

HRESULT CLogo::Ready_Layer_Environment(const _tchar * pLayerTag)
{
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

	Safe_Release(m_pTriCol);

	__super::Free();
}
