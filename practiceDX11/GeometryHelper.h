#pragma once
class GeometryHelper// ������ ������ ���� ������ֱ� ���� Ŭ����
{
public:
	static void CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> geometry);

	static void CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry,Color color);

	 


};

