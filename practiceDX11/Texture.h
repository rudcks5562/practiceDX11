#pragma once

class Texture
{


public:
	Texture(ComPtr<ID3D11Device> device);

	~Texture();

	ComPtr<ID3D11ShaderResourceView> GetComPtr() { return _shaderResourceView; }

	void Create(const std::wstring& path);


private:

	ComPtr<ID3D11Device> _device;


	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr;



};

