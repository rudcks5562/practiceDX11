#pragma once


template<typename T> // vertex 구조체 종류 다양성
class Geometry// 기하학적 도형 
{

public:

	Geometry() {};
	~Geometry() {};// 채우기. 

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


	std::vector<T> _vertices;// template을 쓰면 구현은 여기서 하는게 좋다.(인라인 쓰든가)
	std::vector<uint32> _indices;








};

