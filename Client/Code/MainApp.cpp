#include "stdafx.h"
#include "..\Header\MainApp.h"



CMainApp::CMainApp()
	: m_pDeviceClass(nullptr), m_pGraphicDev(nullptr)
{
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(&m_pDeviceClass, g_hWnd, MODE_WIN), E_FAIL);


	return S_OK;
}

int CMainApp::Update_MainApp(const _float & fTimeDelta)
{
	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
}

void CMainApp::Render_MainApp()
{
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	Engine::Render_End();
	

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
	//m_pDeviceClass->DestroyInstance();

	Engine::Release_System();
}
