#pragma once
class Graphics
{
public:
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:

	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewPort();





private:
	HWND _hwnd = {};
	uint32 _width = 800;
	uint32 _height = 600;

private:
	//dx and swapchain
	//ID3D11Device* _device;
	//ID3D11DeviceContext* _deviceContext;
	ComPtr<ID3D11Device> _device=nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext=nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;
	//�ĸ���� ������.
	//misc ����Ʈ..?
	D3D11_VIEWPORT _viewport = { 0 };// ȭ��ũ�⿡ ������ ����ü.
	float _clearColor[4] = { 0.5f,0.5f ,0.5f ,0.5f };









};

