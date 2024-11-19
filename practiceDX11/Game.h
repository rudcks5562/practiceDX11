#pragma once

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
	//�ĸ���� ������.
	//misc ����Ʈ..?
	D3D11_VIEWPORT _viewport = {0};// ȭ��ũ�⿡ ������ ����ü.
	float _clearColor[4] = {0.5f,0.5f ,0.5f ,0.5f };


};

