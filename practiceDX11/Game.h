#pragma once
#include <string>

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
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView(); 
	void SetViewPort();


private:
	void CreateGeometry();
	void CreateInputLayout();
	
	void CreateVS();
	void CreatePS();

	void CreateSRV();
	void CreateConstantBuffer();

	void LoadShaderFromFile(const std::wstring& path, const std::string& name, const std::string& version, ComPtr<ID3DBlob>& blob);


private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	//dx and swapchain
	//ID3D11Device* _device;
	//ID3D11DeviceContext* _deviceContext;
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;
	//후면버퍼 묘사자.
	//misc 뷰포트..?
	D3D11_VIEWPORT _viewport = {0};// 화면크기에 연관된 구조체.
	float _clearColor[4] = {0.5f,0.5f ,0.5f ,0.5f };


private:
	//Geometry
	std::vector<Vertex> _vertices;
	// CPU<->RAM(memory) - GPU-VRAM
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;

	std::vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;

	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;// 버텍스 구조 묘사자.
	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	//shader로드는 파일로?
	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr;

private :
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

};

