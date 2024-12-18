#include "stdafx.h"
#include "Pipeline.h"

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext):_deviceContext(deviceContext)
{





}

Pipeline::~Pipeline()
{
}

void Pipeline::UpdatePipeline(PipelineInfo info)
{
	//IA (setting?) 
	uint32 stride = sizeof(VertexTextureData);
	uint32 offset = 0;

	

	//_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	//_deviceContext->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetInputLayout(info.inputLayout->GetComPtr().Get());
	// topology?
	_deviceContext->IASetPrimitiveTopology(info.topology);
	// VS 
	if(info.vertexShader)
	_deviceContext->VSSetShader(info.vertexShader->GetComPtr().Get(), nullptr, 0);
	//_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer->GetComPtr().GetAddressOf());

	//RS
	// vs가넘겨준 삼각형 내부 픽셀판별
	if(info.rasterizerState)
	_deviceContext->RSSetState(info.rasterizerState->GetComPtr().Get());//bind? 



	//PS
	if(info.pixelShader)
	_deviceContext->PSSetShader(info.pixelShader->GetComPtr().Get(), nullptr, 0);
	//_deviceContext->PSSetShaderResources(0, 1, _texture1->GetComPtr().GetAddressOf());
	//_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
	//_deviceContext->PSSetSamplers(0, 1, _samplerState->GetComPtr().GetAddressOf());

	//리소스연결
	//OM
	if(info.blendState)
	_deviceContext->OMSetBlendState(info.blendState->GetComPtr().Get(), info.blendState->GetBlendFactor(), info.blendState->GetSampleMask());



	//_deviceContext->Draw(_vertices.size(),0);
	//_deviceContext->DrawIndexed(_geometry->GetIndices().size(), 0, 0);






}

void Pipeline::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	uint32 stride = buffer->GetStride();
	uint32 offset = buffer->GetOffset();

	_deviceContext->IASetVertexBuffers(0, 1, buffer->GetComPtr().GetAddressOf(), &stride, &offset);



}

void Pipeline::SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
{
	_deviceContext->IASetIndexBuffer(buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

}

void Pipeline::SetTexture(uint32 slot, uint32 scope, std::shared_ptr<Texture> texture)
{
	if(scope & SS_VertexShader)
	_deviceContext->VSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());

	if(scope & SS_PixelShader)
	_deviceContext->PSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
	

}

void Pipeline::SetSamplerState(uint32 slot, uint32 scope, std::shared_ptr<SamplerState> samplerState)
{
	if (scope & SS_VertexShader)
		_deviceContext->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

	if (scope & SS_PixelShader)
		_deviceContext->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

}

void Pipeline::Draw(uint32 vertexCount, uint32 startVertexLocation)
{
	_deviceContext->Draw(vertexCount,startVertexLocation);
	
}

void Pipeline::DrawIndexed(uint32 indexCount, uint32 startIntexLocation, uint32 baseVertexLocation)
{
	_deviceContext->DrawIndexed(indexCount, startIntexLocation, baseVertexLocation);
}
