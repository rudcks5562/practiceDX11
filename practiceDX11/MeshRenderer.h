#pragma once
#include "Component.h"
class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext,std::shared_ptr<Pipeline>pipeLine);
	virtual ~MeshRenderer();

	virtual void Update() override;

private:

	void Render(std::shared_ptr<Pipeline> pipeline);

private:

	ComPtr<ID3D11Device> _device;
	std::shared_ptr<Pipeline> _pipeLine;
	//Geometry 
	std::shared_ptr<Geometry<VertexTextureData>> _geometry;
	//std::shared_ptr<Geometry<VertexColorData>> _geometry;
	//std::vector<Vertex> _vertices;
	// CPU<->RAM(memory) - GPU-VRAM
	//ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	std::shared_ptr<VertexBuffer>_vertexBuffer;
	//std::vector<uint32> _indices;
	//ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
	std::shared_ptr<IndexBuffer> _indexBuffer;
	//ComPtr<ID3D11InputLayout> _inputLayout = nullptr;// 버텍스 구조 묘사자.
	std::shared_ptr<InputLayout> _inputLayout;


	// VS
	std::shared_ptr<VertexShader> _vertexShader;
	//RS
	std::shared_ptr<RasterizerState> _rasterizerState;
	// PS
	std::shared_ptr<PixelShader> _pixelShader;

	//shader로드는 파일로?
	// SRV
	std::shared_ptr<Texture> _texture1;
	std::shared_ptr<SamplerState> _samplerState;
	std::shared_ptr<BlendState> _blendState;
private:
	CameraData _cameraData;
	std::shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;
	TransformData _transformData;
	//ComPtr<ID3D11Buffer> _constantBuffer;
	std::shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;

	//std::shared_ptr<Transform> _transform = std::make_shared<Transform>();

	//std::shared_ptr<Transform> _parent = std::make_shared<Transform>();





};

