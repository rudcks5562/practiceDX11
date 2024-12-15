#pragma once


struct VertexTextureData {
	Vec3 position = {0,0,0};// xyz
	//Color color;
	Vec2 uv = {0,0};//float*2

	static std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
};
struct VertexColorData {
	Vec3 position = {0,0,0};// xyz
	Color color = {0,0,0,0};//float4
	//Vec2 uv;//float*2
	static std::vector<D3D11_INPUT_ELEMENT_DESC> descs;

};
// 동일한 아이디에 대한 텍스쳐아이디->인풋레이아웃, 키값?









