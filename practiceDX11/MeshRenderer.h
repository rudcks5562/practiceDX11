#pragma once
#include "Component.h"
#include "Material.h"
#include "Shader.h"

class Mesh;
class Material;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();



	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetShader(shared_ptr<Shader> shader) { _material->SetShader(shader); }
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetTexture(shared_ptr<Texture> texture) { _material->SetTexture(texture); };

	auto GetMaterial() { return _material; }
	auto GetVertexShader() { return GetMaterial()->GetShader()->GetVertexShader(); }
	auto GetInputLayout() { return GetMaterial()->GetShader()->GetInputLayout(); }
	auto GetPixelShader() { return GetMaterial()->GetShader()->GetPixelShader(); }

	shared_ptr<Mesh> GetMesh() { return _mesh; }
	shared_ptr<Texture> GetTexture() { return GetMaterial()->GetTexture(); }


private:



private:

	friend class RenderManager;


	ComPtr<ID3D11Device> _device;

	//mesh
	std::shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;




	std::shared_ptr<Texture> _texture1;
	//shader로드는 파일로?
	// SRV
	//std::shared_ptr<Pipeline> _pipeLine;

private:


	//std::shared_ptr<Transform> _transform = std::make_shared<Transform>();

	//std::shared_ptr<Transform> _parent = std::make_shared<Transform>();





};

