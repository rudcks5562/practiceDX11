#pragma once


enum ShaderScope {
	SS_None = 0,
	SS_VertexShader = (1 << 0),
	SS_PixelShader = (1 << 1),
	SS_Both = SS_VertexShader|SS_PixelShader
};


class ShaderBase
{

public:
	ShaderBase(ComPtr<ID3D11Device> device);
	virtual ~ShaderBase();

	virtual void Create(const std::wstring& path, const std::string& name,
		const std::string& version) abstract;

	ComPtr<ID3DBlob>GetBlob() { return _blob; }

protected:
	std::wstring _path;
	std::string _name;
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3DBlob> _blob ;

protected:
	void LoadShaderFromFile(const std::wstring& path, const std::string& name,
		const std::string& version);

};


class VertexShader :public ShaderBase{
	using Super = ShaderBase;
public:
	VertexShader(ComPtr<ID3D11Device> device);
	~VertexShader();

	ComPtr<ID3D11VertexShader> GetComPtr() {
		return _vertexShader;
	}
	virtual void Create(const std::wstring& path, const std::string& name,
		const std::string& version) override;

protected:
	ComPtr<ID3D11VertexShader> _vertexShader;
};

class PixelShader : public ShaderBase {
	using Super = ShaderBase;
public:
	PixelShader(ComPtr<ID3D11Device> device);
	~PixelShader();

	ComPtr<ID3D11PixelShader> GetComPtr() {
		return _pixelShader;
	}
	virtual void Create(const std::wstring& path, const std::string& name,
		const std::string& version) override;

protected:
	ComPtr<ID3D11PixelShader> _pixelShader;
};

