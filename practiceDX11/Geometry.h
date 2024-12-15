#pragma once


template<typename T> // vertex ����ü ���� �پ缺
class Geometry// �������� ���� 
{

public:

	Geometry() {};
	~Geometry() {};// ä���. 

	uint32 GetVertexCount() { return static_cast<uint32>(_vertices.size()); }
	void* GetVertexData() { return _vertices.data(); }
	const std::vector<T>& GetVertices() { return _vertices; }

	uint32 GEtIndexCount() { return static_case<uint32>(_indices.size()); }
	void* GetIndexData() { return _indices.data(); }
	const std::vector<uint32>& GetVertices() { return _indices; }


	void AddVertex(const T& vertex) { _vertices.push_back(vertex); }
	void AddVertices(const std::vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const std::vector<T>& vertices) { _vertices = vertices; }

	void AddIndex(uint32 index) { _indices.push_back(index); }
	void AddIndices(const std::vector<uint32>& indices) { _indices.insert(_indices.end(), indices.begin(), indices.end()); }
	void SetIndices(const std::vector<uint32>& indices) { _indices = indices; }





private:


	std::vector<T> _vertices;// template�� ���� ������ ���⼭ �ϴ°� ����.(�ζ��� ���簡)
	std::vector<uint32> _indices;








};

