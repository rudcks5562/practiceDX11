#pragma once
#include "Component.h"

class Mesh;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();

	virtual void Update() override;

	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	std::shared_ptr<Mesh> GetMesh() { return _mesh; }
	//모양 외부에서 정할 수 있게-> 내부에선 겟메쉬로 응용?

private:



private:

	friend class RenderManager;


	ComPtr<ID3D11Device> _device;

	//mesh
	std::shared_ptr<Mesh> _mesh;



	//Material
	 std::shared_ptr<InputLayout> _inputLayout;
	// VS


	std::shared_ptr<VertexShader> _vertexShader;
	//RS
	// PS
	std::shared_ptr<PixelShader> _pixelShader;

	std::shared_ptr<Texture> _texture1;
	//shader로드는 파일로?
	// SRV
	//std::shared_ptr<Pipeline> _pipeLine;

private:


	//std::shared_ptr<Transform> _transform = std::make_shared<Transform>();

	//std::shared_ptr<Transform> _parent = std::make_shared<Transform>();





};

