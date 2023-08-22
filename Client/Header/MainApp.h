#pragma once

#include "Base.h"

class CMainApp : public CBase
{
private:		// ������, �Ҹ���
	explicit CMainApp();
	virtual ~CMainApp();

public:			// �Ϲ����� �Լ�, ����
	HRESULT		Ready_MainApp();
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

protected:		// ��Ӱ��� �Լ�, ����
private:		// ������ �ּ�ȭ�ϴ� �Լ�, ����

// ���� �Լ�
public:
	static		CMainApp*		Create();
// �Ҹ� �Լ�
private:
	virtual		void			Free();
};

