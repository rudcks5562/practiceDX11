#include "stdafx.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> geometry)
{
	std::vector<VertexTextureData> _vertices;
	_vertices.resize(4);// 삼각형이므로 점 3개
	_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	_vertices[0].uv = Vec2(0.f, 1.f);
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

	geometry->SetVertices(_vertices);// 버텍스버퍼 생성될 것임

	std::vector<uint32> _indices = { 0,1,2,2,1,3 };
	geometry->SetIndices(_indices);



}

void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	std::vector<VertexColorData> _vertices;


	_vertices.resize(4);// 삼각형이므로 점 3개
	_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	//_vertices[0].uv = Vec2(0.f, 1.f);
	_vertices[0].color = color;// RGBA

	_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
	_vertices[1].color = color;// RGBA
	//_vertices[1].uv = Vec2(0.f, 0.f);

	_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	_vertices[2].color = color;// RGBA
	//_vertices[2].uv = Vec2(1.f, 1.f);

	_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
	_vertices[3].color = color;// RGBA
	//_vertices[3].uv = Vec2(1.f, 0.f);

	geometry->SetVertices(_vertices);

	std::vector<uint32> _indices = {0,1,2,2,1,3};
	geometry->SetIndices(_indices);

}
