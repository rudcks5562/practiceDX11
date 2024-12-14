#pragma once
class InputLayout
{
	// 쉐이더가 먼저 만들어저야 하는 조건이 필요
	//vs blob을 통해 
public:
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();
	
	ComPtr<ID3D11InputLayout> GetComPtr() { return _inputLayout; }
	//쉐이더와 레이아웃 그리고 정점 구조체간의 매핑이 되어야함.
	void Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc,ComPtr<ID3DBlob> blob);
private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11InputLayout> _inputLayout;




};

