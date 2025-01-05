#pragma once
#include "RenderHelper.h"


class RenderManager
{
public:
	RenderManager(ComPtr<ID3D11Device>device, ComPtr<ID3D11DeviceContext>deviceContext);
	
	void Init();
	void Update(std::shared_ptr<Graphics>graphics);
	//render begin 가져온거

private:
	void PushCameraData();
	void PushTransformData();

	void GatherRenderableObjects();
	void RenderObjects();

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	std::shared_ptr<Pipeline> _pipeline;


public:
	CameraData _cameraData;
	std::shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;
	TransformData _transformData;//srt
	//ComPtr<ID3D11Buffer> _constantBuffer;
	std::shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;


private:


	std::shared_ptr<RasterizerState> _rasterizerState;
	std::shared_ptr<SamplerState> _samplerState; 
	std::shared_ptr<BlendState> _blendState;

	std::vector<std::shared_ptr<GameObject>> _renderObjects;

};

