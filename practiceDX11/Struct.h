#pragma once

#include "Types.h"

struct Vertex {
	Vec3 position;// xyz
	//Color color;
	Vec2 uv;//float*2


};
struct TransformData {

	//Vec3 offset;
	//float dummy;// ������ ���� �����Ⱚ??

	Matrix matWorld = Matrix::Identity;
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;


};