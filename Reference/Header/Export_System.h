#include "GraphicDev.h"
#include "TimerMgr.h"
#include "FrameMgr.h"

BEGIN(Engine)

// GraphicDev
inline LPDIRECT3DDEVICE9		Get_GraphicDev();
inline HRESULT		Ready_GraphicDev(CGraphicDev** ppGraphicClass, HWND hWnd, WINMODE eMode, const _uint& iSizeX = WINCX, const _uint& iSizeY = WINCY);
inline void		Render_Begin(D3DXCOLOR Color);
inline void		Render_End();

// TimerMgr
inline _float			Get_TimeDelta(const _tchar* pTimerTag);
inline void				Set_TimeDelta(const _tchar* pTimerTag);
inline HRESULT			Ready_Timer(const _tchar*	pTimerTag);
inline void				Release_System();

// FrameMgr
inline _bool			IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);
inline HRESULT			Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);

#include "Export_System.inl"

END