#include "..\..\Header\VIBuffer.h"


CVIBuffer::CVIBuffer()
	: m_pVB(nullptr), m_dwVtxCnt(0), m_dwTriCnt(0), m_dwVtxSize(0), m_dwFVF(0)
{
}

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev), m_pVB(nullptr),
	m_dwVtxCnt(0), m_dwTriCnt(0), m_dwVtxSize(0), m_dwFVF(0)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwFVF(rhs.m_dwFVF)
{
	m_pVB->AddRef();
}

CVIBuffer::~CVIBuffer()
{
}

HRESULT CVIBuffer::Ready_Buffer()
{
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize,	// 생성할 버퍼의 크기
															0,		// 생성하고자 하는 버텍스 버퍼의 종류(0인 경우 정적 버퍼, D3DUSAGE_DYNAMIC)
															m_dwFVF,	// 버텍스 속성 옵션
															D3DPOOL_MANAGED,	// 메모리 풀 방식(정적 버퍼인 경우 MANAGED)
															&m_pVB,				// 결과 컴 객체
															NULL), E_FAIL);


	return S_OK;
}

void CVIBuffer::Render_Buffer()
{
	// 디바이스 장치와 링크시키려는 버퍼를 지정하는 함수

	// 1인자 : 몇 번 스트림에 버퍼를 전송할 것인가
	// 2인자 : 어떤 대상을 디바이스 장치와 링크 시킬 것인가
	// 3인자 : 어디서부터 전달할 것인가
	// 4인자 : 어떤 크기로 전달할 것인가
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	// 매 프레임마다 정점을 속성 값을 장치에게 전달
	m_pGraphicDev->SetFVF(m_dwFVF);

	// 실제 그리기 함수
	// 1인자 : 삼각형을 그리는 방식
	// 2인자 : 몇 번째 버텍스부터 그릴 것인가
	// 3인자 : 그리려는 삼각형 개수

	m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
}

void CVIBuffer::Free()
{
	Safe_Release(m_pVB);

	CComponent::Free();
}
