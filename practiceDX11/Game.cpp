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


	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();


}

void Game::update()
{
}

void Game::Render()
{

	RenderBegin();// ��ȭ�� ����
	// ������Ʈ ����
	// IA- VS- RS- PS- OM
	{
		//IA (setting?) 
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(),&stride,&offset);
		_deviceContext->IASetInputLayout(_inputLayout.Get());
		// topology?
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VS 
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		//RS

		//PS
		_deviceContext->PSSetShader(_pixelShader.Get(),nullptr, 0);

		//OM

		_deviceContext->Draw(_vertices.size(),0);




	}






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
void Game::CreateGeometry() {// �ﰢ�� ������ ����.

	_vertices.resize(3);// �ﰢ���̹Ƿ� �� 3�� 
	_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	_vertices[0].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA

	_vertices[1].position = Vec3(0.f, 0.5f, 0.f);
	_vertices[1].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA

	_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	_vertices[2].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA

	// vertex buffer 

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE; // �뵵 immutable-> read only gpu!!
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(Vertex) * _vertices.size();// ����1��ũ��* ��������

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data,sizeof(data));
	data.pSysMem = _vertices.data();// ù��° �����ּ� ����


	_device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
}
void Game::CreateInputLayout() {

	D3D11_INPUT_ELEMENT_DESC layout[] = {
	
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}

	};// float = 4byte, 3*float = 12byte, 12 offset

	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	_device->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3��° ���ڰ� ���̴��� ������ �Ǿ��ֱ� ������ ���̴����� �����.



}

void Game::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0",_vsBlob);

	HRESULT hr=_device->CreateVertexShader(_vsBlob->GetBufferPointer(),
		_vsBlob->GetBufferSize(),nullptr,_vertexShader.GetAddressOf()
		);

	assert(SUCCEEDED(hr));
}

void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);

	HRESULT hr = _device->CreatePixelShader(_psBlob->GetBufferPointer(),
		_psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf()
	);
	assert(SUCCEEDED(hr));


}

void Game::LoadShaderFromFile(const std::wstring& path, const std::string& name, const std::string& version, ComPtr<ID3DBlob>& blob)
{

	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;



	HRESULT hr=::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr
	);

	assert(SUCCEEDED(hr));

}



