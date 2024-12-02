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

	CreateSRV();
	CreateConstantBuffer();

}

void Game::update()
{

	_transformData.offset.x += 0.003f;
	_transformData.offset.y += 0.003f;


	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(subResource));


	_deviceContext->Map(_constantBuffer.Get(),0, D3D11_MAP_WRITE_DISCARD, 0,&subResource);
	::memcpy(subResource.pData, &_transformData, sizeof(_transformData));
	_deviceContext->Unmap(_constantBuffer.Get(), 0);

}

void Game::Render()
{

	RenderBegin();// 도화지 갱신
	// 오브젝트 생성
	// IA- VS- RS- PS- OM
	{
		//IA (setting?) 
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(),&stride,&offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT,0);
		_deviceContext->IASetInputLayout(_inputLayout.Get());
		// topology?
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VS 
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0,1,_constantBuffer.GetAddressOf());

		//RS

		//PS
		_deviceContext->PSSetShader(_pixelShader.Get(),nullptr, 0);
		_deviceContext->PSSetShaderResources(0,1,_shaderResourceView.GetAddressOf());
		_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		//리소스연결
		//OM

		//_deviceContext->Draw(_vertices.size(),0);
		_deviceContext->DrawIndexed(_indices.size(), 0, 0);
		// IDX buff 추가까지는 잘됨.



	}






	RenderEnd();// 결과 제출 

}
void Game::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1,_renderTargetView.GetAddressOf(),nullptr);// 후면버퍼에 그려달라고 요청
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(),_clearColor);// 도화지 배경색 초기화 
	_deviceContext->RSSetViewports(1, &_viewport);


}
void Game::RenderEnd()
{

	HRESULT hr = _swapChain->Present(1, 0);// 제출. 화면에 출력하시오라는 뜻 
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
		nullptr,// featurelevel 결과값? 필요없다함.
		_deviceContext.GetAddressOf()
	);// device와 컨텍스트 그리고 스왑체인을 채워줌.



	assert(SUCCEEDED(hr));// crash유도 


}
void Game::CreateRenderTargetView() {

	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	// 사용용도 명시필요
	_device->CreateRenderTargetView(backBuffer.Get(),nullptr,_renderTargetView.GetAddressOf());
	assert(SUCCEEDED(hr));
	// 스왑체인을 통해 후면버퍼에 텍스쳐를 넣고 cr렌더타겟뷰를 만들어서 gpu사용케하기.

}
void Game::SetViewPort() {

	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;// 상단 왼쪽 좌표는 무한 
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;// 깊이? 

}
void Game::CreateGeometry() {// 삼각형 데이터 형성.

	//13
	//02


	_vertices.resize(4);// 삼각형이므로 점 3개
	_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	_vertices[0].uv = Vec2(0.f,1.f);
	//_vertices[0].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA

	_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
	//_vertices[1].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA
	_vertices[1].uv = Vec2(0.f, 0.f);

	_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	//_vertices[2].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA
	_vertices[2].uv = Vec2(1.f, 1.f);

	_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
	//_vertices[3].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA
	_vertices[3].uv = Vec2(1.f, 0.f);



	// vertex buffer 

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE; // 용도 immutable-> read only gpu!!
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(Vertex) * _vertices.size();// 정점1개크기* 구성개수

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data,sizeof(data));
	data.pSysMem = _vertices.data();// 첫번째 시작주소 전달


	HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());

	assert(SUCCEEDED(hr));
	//idx 

	{
		_indices = { 0,1,2,2,1,3 };
		 


	}
	//idx buff
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // 용도 immutable-> read only gpu!!
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = (uint32) (sizeof(uint32) * _indices.size());// 정점1개크기* 구성개수

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _indices.data();// 첫번째 시작주소 전달


		HRESULT hr= _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());

		assert(SUCCEEDED(hr));

	}



}
void Game::CreateInputLayout() {// uv추가과정 

	D3D11_INPUT_ELEMENT_DESC layout[] = {
	
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		//{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}// uv = float*2 이므로 r32g32로


	};// float = 4byte, 3*float = 12byte, 12 offset

	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	_device->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3번째 인자가 쉐이더와 연관이 되어있기 때문에 쉐이더부터 만든다.
	//blob->쉐이더 연관.


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

void Game::CreateSRV()
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	HRESULT hr=::LoadFromWICFile(L"Golem.png", WIC_FLAGS_NONE, &md, img);// img load
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
	assert(SUCCEEDED(hr));
	//sec srv2

	 hr = ::LoadFromWICFile(L"123.png", WIC_FLAGS_NONE, &md, img);// img load
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView2.GetAddressOf());
	assert(SUCCEEDED(hr));

}

void Game::CreateConstantBuffer()
{

	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC;//cpu wr+ gpu read
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// 용도적시 
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
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



