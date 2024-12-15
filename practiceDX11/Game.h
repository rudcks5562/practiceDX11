#pragma once
#include <string>
#include "Graphics.h"
class Game
{

public:
	Game();
	~Game();

public:
	void init(HWND hwnd);
	void update();
	void Render();


private:
	void CreateGeometry();
	void CreateInputLayout();
	
	void CreateVS();
	void CreatePS();

	void CreateSRV();
	void CreateConstantBuffer();
	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();

	void LoadShaderFromFile(const std::wstring& path, const std::string& name, const std::string& version, ComPtr<ID3DBlob>& blob);



private:
	HWND _hwnd;
	//shared_ptr<Graphics> _graphics;// precompileheader

	std::shared_ptr<Graphics> _graphics;// smart pointer
	//Graphics* _graphics;
	std::shared_ptr<Geometry<VertexTextureData>> _geometry;

private:
	//Geometry
	std::vector<Vertex> _vertices;
	// CPU<->RAM(memory) - GPU-VRAM
	//ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	std::shared_ptr<VertexBuffer>_vertexBuffer;
	

	std::vector<uint32> _indices;
	//ComPtr<ID3D11Buffer> _indexBuffer = nullptr;

	std::shared_ptr<IndexBuffer> _indexBuffer;

	//ComPtr<ID3D11InputLayout> _inputLayout = nullptr;// 버텍스 구조 묘사자.
	std::shared_ptr<InputLayout> _inputLayout;


	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	//RS
	ComPtr<ID3D11RasterizerState> _rasterizerState=nullptr;


	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	//shader로드는 파일로?
	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr;

	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;
private :
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };

};

