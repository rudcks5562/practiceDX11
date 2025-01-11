#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics(HWND hwnd)
{
	_hwnd= hwnd;

	//���漱��? (�����ʿ�)
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewPort();


}

Graphics::~Graphics()
{
}

void Graphics::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);// �ĸ���ۿ� �׷��޶�� ��û
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);// ��ȭ�� ���� �ʱ�ȭ 
	_deviceContext->RSSetViewports(1, &_viewport);

}

void Graphics::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);// ����. ȭ�鿡 ����Ͻÿ���� �� 
	assert(SUCCEEDED(hr));
}

void Graphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc)); {
		desc.BufferDesc.Width = GWinSizeX;
		desc.BufferDesc.Height = GWinSizeY;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}
	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,// featurelevel �����? �ʿ������.
		_deviceContext.GetAddressOf()
	);// device�� ���ؽ�Ʈ �׸��� ����ü���� ä����.
	assert(SUCCEEDED(hr));// crash���� 
}

void Graphics::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	// ���뵵 ����ʿ�
	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	assert(SUCCEEDED(hr));
	// ����ü���� ���� �ĸ���ۿ� �ؽ��ĸ� �ְ� cr����Ÿ�ٺ並 ���� gpu������ϱ�.

}

void Graphics::SetViewPort()
{
	_viewport.TopLeftX = 0.0f;
	_viewport.TopLeftY = 0.0f;// ��� ���� ��ǥ�� ���� 
	_viewport.Width = static_cast<float>(GWinSizeX);
	_viewport.Height = static_cast<float>(GWinSizeY);
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;// ����? 

}
