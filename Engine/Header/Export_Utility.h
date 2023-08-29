#include "Management.h"

#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"

#include "Texture.h"
#include "Transform.h"

#include "ProtoMgr.h"


BEGIN(Engine)

// Management
inline CComponent*	Get_Component(COMPONENTID eID, const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag);

inline HRESULT		Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppManagementInstance);

inline HRESULT		Set_Scene(CScene* pScene);
inline _int			Update_Scene(const _float& fTimeDelta);
inline void			LateUpdate_Scene();
inline void			Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

// ProtoMgr
inline HRESULT			Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent);
inline CComponent*		Clone_Proto(const _tchar* pProtoTag);

inline void			Release_Utility();

#include "Export_Utility.inl"

END