#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;

	// TODO~ 
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewPort();




}

void Game::update()
{
}

void Game::Render()
{

	RenderBegin();// ��ȭ�� ����
	// ������Ʈ ����




	RenderEnd();// ��� ���� 

}
void Game::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1,_renderTargetView.GetAddressOf(),nullptr);// �ĸ���ۿ� �׷��޶�� ��û
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(),_clearColor);// ��ȭ�� ���� �ʱ�ȭ 
	_deviceContext->RSSetViewports(1, &_viewport);


}
void Game::RenderEnd()
{

	HRESULT hr = _swapChain->Present(1, 0);// ����. ȭ�鿡 ����Ͻÿ���� �� 
	assert(SUCCEEDED(hr));
}
void Game::CreateDeviceAndSwapChain() {

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc)); {

		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
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


	HRESULT hr=::D3D11CreateDeviceAndSwapChain(
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
void Game::CreateRenderTargetView() {

	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	// ���뵵 ����ʿ�
	_device->CreateRenderTargetView(backBuffer.Get(),nullptr,_renderTargetView.GetAddressOf());
	assert(SUCCEEDED(hr));
	// ����ü���� ���� �ĸ���ۿ� �ؽ��ĸ� �ְ� cr����Ÿ�ٺ並 ���� gpu������ϱ�.

}
void Game::SetViewPort() {

	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;// ��� ���� ��ǥ�� ���� 
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;// ����? 


}



