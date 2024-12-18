#pragma once

struct PipelineInfo {// 물체별이 아닌 공용의 성격이 강한것 모음

	std::shared_ptr<InputLayout> inputLayout;
	std::shared_ptr<VertexShader> vertexShader;
	std::shared_ptr<PixelShader> pixelShader;
	std::shared_ptr<RasterizerState> rasterizerState;
	std::shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


};



class Pipeline
{

public:

	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info);



	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer);

	template<typename T>
	void SetConstantBuffer(uint32 slot,uint32 scope,std::shared_ptr<ConstantBuffer<T>> buffer) {
		//shader scope
		if(scope & SS_VertexShader)
		_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
		if(scope & SS_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

	}

	void SetTexture(uint32 slot, uint32 scope, std::shared_ptr<Texture> texture);
	void SetSamplerState(uint32 slot, uint32 scope, std::shared_ptr<SamplerState> samplerState);
	 


	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 indexCount, uint32 startIntexLocation, uint32 baseVertexLocation);


private:
	ComPtr<ID3D11DeviceContext> _deviceContext;







};

