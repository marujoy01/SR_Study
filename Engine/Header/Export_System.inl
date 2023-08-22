LPDIRECT3DDEVICE9		Get_GraphicDev() 
{ 
	return CGraphicDev::GetInstance()->Get_GraphicDev(); 
}
HRESULT		Ready_GraphicDev(CGraphicDev** ppGraphicClass, HWND hWnd, WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY)
{
	return CGraphicDev::GetInstance()->Ready_GraphicDev(ppGraphicClass, hWnd, eMode, iSizeX, iSizeY);
}
void		Render_Begin(D3DXCOLOR Color)
{
	return CGraphicDev::GetInstance()->Render_Begin(Color);
}
void		Render_End()
{
	CGraphicDev::GetInstance()->Render_End();
}

_float			Get_TimeDelta(const _tchar* pTimerTag)
{
	CTimerMgr::GetInstance()->Get_TimeDelta(pTimerTag);
}
void				Set_TimeDelta(const _tchar* pTimerTag)
{
	CTimerMgr::GetInstance()->Set_TimeDelta(pTimerTag);
}
HRESULT			Ready_Timer(const _tchar*	pTimerTag)
{
	return CTimerMgr::GetInstance()->Ready_Timer(pTimerTag);
}

void	Release_System()
{
	CTimerMgr::GetInstance()->DestroyInstance();
	CGraphicDev::GetInstance()->DestroyInstance();
}