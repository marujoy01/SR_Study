#pragma once

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CGraphicDev;

END

class CMainApp : public CBase
{
private:		// 생성자, 소멸자
	explicit CMainApp();
	virtual ~CMainApp();

public:			// 일반적인 함수, 변수
	HRESULT		Ready_MainApp();
	int			Update_MainApp(const _float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

protected:		// 상속관련 함수, 변수
private:		// 접근을 최소화하는 함수, 변수
	Engine::CGraphicDev*		m_pDeviceClass;
	LPDIRECT3DDEVICE9			m_pGraphicDev;

// 생성 함수
public:
	static		CMainApp*		Create();
// 소멸 함수
private:
	virtual		void			Free();
};

