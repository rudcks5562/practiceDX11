#include "stdafx.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(ComPtr<ID3D11Device> device):_device(device)
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()// 인자로 모드 옵션지정하려면 추가할것.
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;// wireframe option은 외곽?삼각형만 보여줌.
	desc.CullMode = D3D11_CULL_BACK;// 컬링->스킵 (후면인식시 그리지않겠다),프론트
	desc.FrontCounterClockwise = false;// 이걸로 전후면 판단(앞방향이 반시계인지 묻는 것)


	HRESULT hr =
		_device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());

	assert(SUCCEEDED(hr));


}
