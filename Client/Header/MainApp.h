#pragma once

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CGraphicDev;

END

class CMainApp : public CBase
{
private:		// ������, �Ҹ���
	explicit CMainApp();
	virtual ~CMainApp();

public:			// �Ϲ����� �Լ�, ����
	HRESULT		Ready_MainApp();
	int			Update_MainApp(const _float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

protected:		// ��Ӱ��� �Լ�, ����
private:		// ������ �ּ�ȭ�ϴ� �Լ�, ����
	Engine::CGraphicDev*		m_pDeviceClass;
	LPDIRECT3DDEVICE9			m_pGraphicDev;

// ���� �Լ�
public:
	static		CMainApp*		Create();
// �Ҹ� �Լ�
private:
	virtual		void			Free();
};

