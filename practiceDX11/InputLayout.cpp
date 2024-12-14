#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout(ComPtr<ID3D11Device> device)
	:_device(device){


}

InputLayout::~InputLayout()
{
}

void InputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc, ComPtr<ID3DBlob> blob)
{


	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	const int32 count = static_cast<int32> (desc.size());


	_device->CreateInputLayout(desc.data(), count, blob->GetBufferPointer(), blob->GetBufferSize(), _inputLayout.GetAddressOf());
	//3번째 인자가 쉐이더와 연관이 되어있기 때문에 쉐이더부터 만든다.
	//blob->쉐이더 연관.




}
