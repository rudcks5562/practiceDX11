#include "stdafx.h"
#include "RenderManager.h"
#include "Pipeline.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Game.h"
#include "Mesh.h"
#include "Animator.h"
#include "GameObject.h"

RenderManager::RenderManager(ComPtr<ID3D11Device>device, ComPtr<ID3D11DeviceContext>deviceContext)
	:_device(device),_deviceContext(deviceContext)
{

}

void RenderManager::Init()
{
	_pipeline = std::make_shared<Pipeline>(_deviceContext);
	//shared from this 조사하기
	_transformBuffer = std::make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_transformBuffer->Create();

	_cameraBuffer = std::make_shared<ConstantBuffer<CameraData>>(_device, _deviceContext);
	_cameraBuffer->Create();

	_animationBuffer = make_shared<ConstantBuffer<AnimationData>>(_device, _deviceContext);
	_animationBuffer->Create();


	_rasterizerState = std::make_shared<RasterizerState>(_device);
	_rasterizerState->Create();

	_blendState = std::make_shared<BlendState>(_device);
	_blendState->Create();

	_samplerState = std::make_shared<SamplerState>(_device);
	_samplerState->Create();

}

void RenderManager::Update(std::shared_ptr<Graphics>graphics)
{
	graphics->RenderBegin();

	PushCameraData();
	GatherRenderableObjects();
	RenderObjects();


	graphics->RenderEnd();
}

void RenderManager::PushCameraData()
{
	_cameraData.matView = Camera::S_MatView;//static 관리
	_cameraData.matProjection = Camera::S_MatProjection;
	//렌더매니저에서 카메라도 같이 여러개 관리할거면
	//카메라중 하나를 골라서 구현하도록한다.
	_cameraBuffer->CopyData(_cameraData);

}

void RenderManager::PushTransformData()
{
	_transformBuffer->CopyData(_transformData);
		//물체마다 상이


}

void RenderManager::PushAnimationData()
{

	_animationBuffer->CopyData(_animationData);
}

void RenderManager::GatherRenderableObjects()
{

	_renderObjects.clear();

	auto& GameObjects = SCENE->GetActiveScene()->GetGameObjects();
	for (const std::shared_ptr<GameObject>& gameObject : GameObjects) {

		std::shared_ptr<MeshRenderer> MeshRenderer = gameObject->GetMeshRenderer();
		if (MeshRenderer) {


			_renderObjects.push_back(gameObject);
		}
		//바로처리?
		//한 프레임 안에서 여러번 쓸 수 있어서 분리?
	}




}

void RenderManager::RenderObjects()
{
	for (const std::shared_ptr<GameObject>& gameObject : _renderObjects) {

		std::shared_ptr<MeshRenderer> MeshRenderer = gameObject->GetMeshRenderer();
		if (MeshRenderer == nullptr) {
			continue;
		}

		std::shared_ptr<Transform> transform = gameObject->GetTransform();
		if (transform == nullptr) {
			continue;
		}
		//srt
		_transformData.matWorld = transform->GetWorldMatrix();
		PushTransformData();

		// animation

		shared_ptr<Animator>animator = gameObject->GetAnimator();
		if (animator) {
			const keyFrame& keyFrame = animator->GetCurrentKeyFrame();
			_animationData.spriteOffset = keyFrame.offset;
			_animationData.spriteSize = keyFrame.size;
			_animationData.textureSize = animator->GetCurrentAnimation()->GetTextureSize();
			_animationData.useAnimation = 1.f;
			PushAnimationData();

			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, animator->GetCurrentAnimation()->GetTexture());

		}
		else {
			_animationData.spriteOffset = Vec2(0.f, 0.f);
			_animationData.spriteSize = Vec2(0.f, 0.f);
			_animationData.textureSize = Vec2(0.f, 0.f);
			_animationData.useAnimation = 1; 
			PushAnimationData();
		}


		PipelineInfo info;
		info.inputLayout =  MeshRenderer-> GetInputLayout();
		info.vertexShader = MeshRenderer->GetVertexShader();
		info.pixelShader =  MeshRenderer->GetPixelShader();
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;

		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(MeshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetIndexBuffer(MeshRenderer->GetMesh()->GetIndexBuffer());
		_pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer);
		_pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);

		//_pipeline->SetTexture(0, SS_PixelShader, MeshRenderer->GetTexture());
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
		_pipeline->DrawIndexed(MeshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);




	}

}
