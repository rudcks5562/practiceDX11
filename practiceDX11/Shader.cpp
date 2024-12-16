#include "stdafx.h"
#include "Shader.h"

Shader::Shader(ComPtr<ID3D11Device> device): _device(device)
{



}

Shader::~Shader()
{
}

void Shader::LoadShaderFromFile(const std::wstring& path, const std::string& name, const std::string& version)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	_path = path;
	_name = name;

	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		_blob.GetAddressOf(),
		nullptr
	);

	assert(SUCCEEDED(hr));




}



VertexShader::VertexShader(ComPtr<ID3D11Device> device) : Super(device)
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::Create(const std::wstring& path, const std::string& name, const std::string& version)
{
	LoadShaderFromFile(path, name, version);
	HRESULT hr = _device->CreateVertexShader(_blob->GetBufferPointer(),
		_blob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf()
	);

	assert(SUCCEEDED(hr));
}



PixelShader::PixelShader(ComPtr<ID3D11Device> device) : Super(device)
{
}

PixelShader::~PixelShader()
{
}

void PixelShader::Create(const std::wstring& path, const std::string& name, const std::string& version)
{
	LoadShaderFromFile(path, name, version);
	HRESULT hr = _device->CreatePixelShader(_blob->GetBufferPointer(),
		_blob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf()
	);

	assert(SUCCEEDED(hr));
}
