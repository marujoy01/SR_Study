#include "..\..\Header\VIBuffer.h"


CVIBuffer::CVIBuffer()
	: m_pVB(nullptr), m_pIB(nullptr), m_dwVtxCnt(0), m_dwTriCnt(0), m_dwVtxSize(0), m_dwFVF(0), m_dwIdxSize(0)
{
}

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev), m_pVB(nullptr), m_pIB(nullptr),
	m_dwVtxCnt(0), m_dwTriCnt(0), m_dwVtxSize(0), m_dwFVF(0), m_dwIdxSize(0)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwFVF(rhs.m_dwFVF)
	, m_dwIdxSize(rhs.m_dwIdxSize)
	, m_IdxFmt(rhs.m_IdxFmt)
{
	m_pVB->AddRef();
	m_pIB->AddRef();
}

CVIBuffer::~CVIBuffer()
{
}

HRESULT CVIBuffer::Ready_Buffer()
{
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize,	// ������ ������ ũ��
															0,		// �����ϰ��� �ϴ� ���ؽ� ������ ����(0�� ��� ���� ����, D3DUSAGE_DYNAMIC)
															m_dwFVF,	// ���ؽ� �Ӽ� �ɼ�
															D3DPOOL_MANAGED,	// �޸� Ǯ ���(���� ������ ��� MANAGED)
															&m_pVB,				// ��� �� ��ü
															NULL), E_FAIL);

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateIndexBuffer(m_dwTriCnt * m_dwIdxSize,	// ������ ������ ũ��
															0,		// �����ϰ��� �ϴ� �ε��� ������ ����(0�� ��� ���� ����, D3DUSAGE_DYNAMIC)
															m_IdxFmt,	// �ε��� �Ӽ� �ɼ�
															D3DPOOL_MANAGED,	// �޸� Ǯ ���(���� ������ ��� MANAGED)
															&m_pIB,				// ��� �� ��ü
															NULL), E_FAIL);

	return S_OK;
}

void CVIBuffer::Render_Buffer()
{
	// ����̽� ��ġ�� ��ũ��Ű���� ���۸� �����ϴ� �Լ�

	// 1���� : �� �� ��Ʈ���� ���۸� ������ ���ΰ�
	// 2���� : � ����� ����̽� ��ġ�� ��ũ ��ų ���ΰ�
	// 3���� : ��𼭺��� ������ ���ΰ�
	// 4���� : � ũ��� ������ ���ΰ�
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	// �� �����Ӹ��� ������ �Ӽ� ���� ��ġ���� ����
	m_pGraphicDev->SetFVF(m_dwFVF);
	
	m_pGraphicDev->SetIndices(m_pIB);
	
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
	// 1. �ﰢ���� �׸��� ���
	// 2. ���ؽ��� �ε��� ��(�� �� �ε����� �������� �׸� ���ΰ�)
	// 3. ���ؽ� ���ۿ� �� �ִ� ������ �� �� ��° ���� �׸� ���ΰ�
	// 4. ���� ����ϰ����ϴ� ���ؽ��� ����
	// 5. �ε��� ���ۿ� �� �ִ� �ε��� �� �� �������� �׸� ���ΰ�
	// 6. �׸����� �ﰢ�� ����



	// ���� �׸��� �Լ�
	// 1���� : �ﰢ���� �׸��� ���
	// 2���� : �� ��° ���ؽ����� �׸� ���ΰ�
	// 3���� : �׸����� �ﰢ�� ����

	//m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
}

void CVIBuffer::Free()
{
	Safe_Release(m_pIB);
	Safe_Release(m_pVB);

	CComponent::Free();
}
