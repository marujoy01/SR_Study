#include "..\..\Header\Calculator.h"



CCalculator::CCalculator(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}


CCalculator::~CCalculator()
{
}

HRESULT CCalculator::Ready_Calculator()
{
	return S_OK;
}

_float CCalculator::Compute_HeightOnTerrain(const _vec3 * pPos, const _vec3 * pTerrainVtxPos, const _ulong & dwCntX, const _ulong & dwCntZ, const _ulong& dwVtxItv)
{

	_ulong	dwIndex = _ulong(pPos->z / dwVtxItv) * dwCntX + _ulong(pPos->x / dwVtxItv);

	_float	fRatioX = _float(pPos->x - pTerrainVtxPos[dwIndex + dwCntX].x) / dwVtxItv;
	_float	fRatioZ = _float(pTerrainVtxPos[dwIndex + dwCntX].z - pPos->z ) / dwVtxItv;

	D3DXPLANE	Plane;

	// 오른쪽 상단 삼각형
	if (fRatioX > fRatioZ)
	{
		D3DXPlaneFromPoints(&Plane,
			&pTerrainVtxPos[dwIndex + dwCntX],
			&pTerrainVtxPos[dwIndex + dwCntX + 1],
			&pTerrainVtxPos[dwIndex + 1]);
	}

	else
	{
		D3DXPlaneFromPoints(&Plane,
			&pTerrainVtxPos[dwIndex + dwCntX],
			&pTerrainVtxPos[dwIndex + 1],
			&pTerrainVtxPos[dwIndex]);
	}

	// ax + by + cz + d
	// by = -ax - cz - d
	// y = (-ax - cz - d) / b

	return (-Plane.a * pPos->x - Plane.c * pPos->z - Plane.d) / Plane.b;
}

CCalculator * CCalculator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCalculator *		pInstance = new CCalculator(pGraphicDev);

	if (FAILED(pInstance->Ready_Calculator()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Calculator Create Failed");
		return nullptr;
	}
	
	return pInstance;
}

CComponent * CCalculator::Clone()
{
	return new CCalculator(*this);
}

void CCalculator::Free()
{
	CComponent::Free();
}
