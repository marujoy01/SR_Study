#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "Logo.h"

CMainApp::CMainApp()
	: m_pDeviceClass(nullptr), m_pGraphicDev(nullptr), m_pManagementClass(nullptr)
{
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{
	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);

// 	_matrix	matView, matProj;
// 
// 	D3DXMatrixLookAtLH(&matView, 
// 		&_vec3(0.f, 1.f, -10.f),
// 		&_vec3(0.f, 0.f, 1.f), 
// 		&_vec3(0.f, 1.f, 0.f));
// 
// 	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60.f), (float)WINCX / WINCY, 0.1f, 1000.f);
// 
// 	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
// 	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);


	return S_OK;
}

int CMainApp::Update_MainApp(const _float & fTimeDelta)
{
	m_pManagementClass->Update_Scene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
	Engine::LateUpdate_Scene();
}

void CMainApp::Render_MainApp()
{
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	Engine::Render_Scene(m_pGraphicDev);

	Engine::Render_End();
	

}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement ** ppManagement)
{
	Engine::CScene*		pScene = nullptr;

	pScene = CLogo::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagement), E_FAIL);
	(*ppManagement)->AddRef();

	FAILED_CHECK_RETURN((*ppManagement)->Set_Scene(pScene), E_FAIL);

	return S_OK;
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9 * ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(&m_pDeviceClass, g_hWnd, MODE_WIN), E_FAIL);
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp *		pInstance = new	 CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		MSG_BOX("MainApp Create Failed");
		Engine::Safe_Release(pInstance);

		return nullptr;
	}
	return pInstance;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pDeviceClass);

	Safe_Release(m_pManagementClass);

	Engine::Release_Utility();
	Engine::Release_System();
}
