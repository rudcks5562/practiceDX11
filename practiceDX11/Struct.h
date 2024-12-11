#pragma once

#include "Types.h"

struct Vertex {
	Vec3 position;// xyz
	//Color color;
	Vec2 uv;//float*2


};
struct TransformData {

	//Vec3 offset;
	//float dummy;// 정렬을 위한 쓰레기값??

	Matrix matWorld = Matrix::Identity;
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;


};