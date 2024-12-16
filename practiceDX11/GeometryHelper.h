#pragma once
#include "VertexData.h"
#include "Geometry.h"
class GeometryHelper// 정적인 도형을 쉽게 만들어주기 위한 클래스
{
public:
	static void CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> geometry);

	static void CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry,Color color);

	 


};

