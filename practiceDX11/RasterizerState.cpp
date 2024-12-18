#include "stdafx.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(ComPtr<ID3D11Device> device):_device(device)
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()// ���ڷ� ��� �ɼ������Ϸ��� �߰��Ұ�.
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;// wireframe option�� �ܰ�?�ﰢ���� ������.
	desc.CullMode = D3D11_CULL_BACK;// �ø�->��ŵ (�ĸ��νĽ� �׸����ʰڴ�),����Ʈ
	desc.FrontCounterClockwise = false;// �̰ɷ� ���ĸ� �Ǵ�(�չ����� �ݽð����� ���� ��)


	HRESULT hr =
		_device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());

	assert(SUCCEEDED(hr));


}
