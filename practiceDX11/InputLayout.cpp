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
	//3��° ���ڰ� ���̴��� ������ �Ǿ��ֱ� ������ ���̴����� �����.
	//blob->���̴� ����.




}
