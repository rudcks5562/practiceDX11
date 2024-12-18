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





private:
	HWND _hwnd;
	//shared_ptr<Graphics> _graphics;// precompileheader

	std::shared_ptr<Graphics> _graphics;// smart pointer
	std::shared_ptr<Pipeline> _pipeline;

	//Graphics* _graphics;
	std::shared_ptr<Geometry<VertexTextureData>> _geometry;

private:
	//Geometry
	//std::vector<Vertex> _vertices;
	// CPU<->RAM(memory) - GPU-VRAM
	//ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	std::shared_ptr<VertexBuffer>_vertexBuffer;
	
	//std::vector<uint32> _indices;
	//ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
	std::shared_ptr<IndexBuffer> _indexBuffer;

	//ComPtr<ID3D11InputLayout> _inputLayout = nullptr;// ���ؽ� ���� ������.
	std::shared_ptr<InputLayout> _inputLayout;

	// VS
	std::shared_ptr<VertexShader> _vertexShader;
	
	//RS
	std::shared_ptr<RasterizerState> _rasterizerState;


	// PS
	std::shared_ptr<PixelShader> _pixelShader;
	

	//shader�ε�� ���Ϸ�?
	// SRV

	std::shared_ptr<Texture> _texture1;
	//std::shared_ptr<Texture> _texture2;


	std::shared_ptr<SamplerState> _samplerState;
	std::shared_ptr<BlendState> _blendState;
private :
	TransformData _transformData;
	//ComPtr<ID3D11Buffer> _constantBuffer;
	std::shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;



	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };

};

