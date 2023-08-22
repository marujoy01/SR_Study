#pragma once

#include "Base.h"

class CMainApp : public CBase
{
private:		// 생성자, 소멸자
	explicit CMainApp();
	virtual ~CMainApp();

public:			// 일반적인 함수, 변수
	HRESULT		Ready_MainApp();
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

protected:		// 상속관련 함수, 변수
private:		// 접근을 최소화하는 함수, 변수

// 생성 함수
public:
	static		CMainApp*		Create();
// 소멸 함수
private:
	virtual		void			Free();
};

