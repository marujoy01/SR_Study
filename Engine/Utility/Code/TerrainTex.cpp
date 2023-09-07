#include "..\..\Header\TerrainTex.h"

CTerrainTex::CTerrainTex()
{
}

CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
	, m_pPos(nullptr)
{
}

CTerrainTex::CTerrainTex(const CTerrainTex & rhs)
	: CVIBuffer(rhs)
	, m_hFile(rhs.m_hFile)
	, m_fH(rhs.m_fH)
	, m_iH(rhs.m_iH)
	, m_pPos(rhs.m_pPos)
{
}

CTerrainTex::~CTerrainTex()
{
}

HRESULT CTerrainTex::Ready_Buffer(const _ulong& dwCntX,
								const _ulong& dwCntZ,
								const _ulong& dwVtxItv)
{

	//LPDIRECT3DTEXTURE9			pTexture = nullptr;

	//D3DXCreateTexture(m_pGraphicDev, 129, 129, 1, 
	//	0,		// D3DUSAGE_RENDERTARGET
	//	D3DFMT_A8R8G8B8, 
	//	D3DPOOL_MANAGED, 
	//	&pTexture);

	//D3DLOCKED_RECT			LockRect;

	//pTexture->LockRect(0, &LockRect, nullptr, 0);

	//for (int i = 0; i < 129; ++i)
	//{
	//	for (int j = 0; j < 129; ++j)
	//	{
	//		int iIndex = i * 129 + j;

	//		*(((_ulong*)LockRect.pBits) + iIndex) = D3DCOLOR_ARGB(255, 0, 0, 255);
	//	}
	//}
	//
	//pTexture->UnlockRect(0);

	//D3DXSaveTextureToFile(L"../Bin/Resource/Texture/Terrain/139.bmp", D3DXIFF_BMP, pTexture, nullptr);


	m_dwFVF = FVF_TEX;
	m_dwVtxCnt = dwCntX * dwCntZ;

	m_dwTriCnt = (dwCntX - 1) * (dwCntZ - 1) * 2;
	m_dwVtxSize = sizeof(VTXTEX);

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	m_pPos = new _vec3[m_dwVtxCnt];

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	m_hFile = CreateFile(L"../Bin/Resource/Texture/Terrain/Height.bmp", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	_ulong dwByte = 0;

	ReadFile(m_hFile, &m_fH, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);
	ReadFile(m_hFile, &m_iH, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	_ulong*		pPixel = new _ulong[m_iH.biWidth * m_iH.biHeight];

	ReadFile(m_hFile, pPixel, sizeof(_ulong) * m_iH.biWidth * m_iH.biHeight, &dwByte, nullptr);
		
	CloseHandle(m_hFile);


	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	_ulong	dwIndex(0);

	for (_ulong i = 0; i < dwCntZ; ++i)
	{
		for (_ulong j = 0; j < dwCntX; ++j)
		{
			dwIndex = i * dwCntX + j;

			pVertex[dwIndex].vPosition	= { _float(j) * dwVtxItv,
				_float(pPixel[dwIndex] & 0x000000ff) / 20.f, 
				_float(i) * dwVtxItv };

			m_pPos[dwIndex] = pVertex[dwIndex].vPosition;

			pVertex[dwIndex].vTexUV		= { _float(j) / (dwCntX - 1) * 20.f,
											_float(i) / (dwCntZ - 1) * 20.f };
		}
	}	
	
	m_pVB->Unlock();


	Safe_Delete_Array(pPixel);

	INDEX32*		pIndex = nullptr;

	_ulong		dwTriIdx(0);

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (_ulong i = 0; i < dwCntZ - 1; ++i)
	{
		for (_ulong j = 0; j < dwCntX - 1; ++j)
		{
			dwIndex = i  * dwCntX + j;

			// 오른쪽 위
			pIndex[dwTriIdx]._0 = dwIndex + dwCntX;
			pIndex[dwTriIdx]._1 = dwIndex + dwCntX + 1;
			pIndex[dwTriIdx]._2 = dwIndex + 1;
			dwTriIdx++;

			// 왼쪽 아래 삼각형
			pIndex[dwTriIdx]._0 = dwIndex + dwCntX;
			pIndex[dwTriIdx]._1 = dwIndex + 1;
			pIndex[dwTriIdx]._2 = dwIndex;
			dwTriIdx++;
		}
	}
	
	m_pIB->Unlock();

	return S_OK;
}

void CTerrainTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CTerrainTex * CTerrainTex::Create(LPDIRECT3DDEVICE9 pGraphicDev,
	const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	CTerrainTex *	pInstance = new CTerrainTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(dwCntX, dwCntZ, dwVtxItv)))
	{
		Safe_Release(pInstance);
		MSG_BOX("TerrainTex Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CTerrainTex::Clone(void)
{
	return new CTerrainTex(*this);
}

void CTerrainTex::Free(void)
{
	if(false == m_bClone)
		Safe_Delete_Array(m_pPos);

	CVIBuffer::Free();
}
