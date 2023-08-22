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

void	Release_System()
{
	CGraphicDev::GetInstance()->DestroyInstance();
}