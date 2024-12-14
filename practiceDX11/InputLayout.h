#pragma once
class InputLayout
{
	// ���̴��� ���� ��������� �ϴ� ������ �ʿ�
	//vs blob�� ���� 
public:
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();
	
	ComPtr<ID3D11InputLayout> GetComPtr() { return _inputLayout; }
	//���̴��� ���̾ƿ� �׸��� ���� ����ü���� ������ �Ǿ����.
	void Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc,ComPtr<ID3DBlob> blob);
private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11InputLayout> _inputLayout;




};

