#pragma once


template<typename T> // vertex ����ü ���� �پ缺
class Geometry
{

public:

	Geometry();
	~Geometry();// ä���. 

	uint32 GetVertexCount() { return static_cast<uint32>(_vertices.size()); }

	void AddVertex(const T& vertex) { _vertices.push_back(vertex); }
	void AddVertices(const std::vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const std::vector<T>& vertices) { _vertices = vertices; }

	void AddIndex(uint32 index) { _indices.push_back(index); }
	void AddIndices(const std::vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
	void SetIndices(const std::vector<T>& vertices) { _vertices = vertices; }





private:


	std::vector<T> _vertices;// template�� ���� ������ ���⼭ �ϴ°� ����.(�ζ��� ���簡)
	std::vector<uint32> _indices;








};

