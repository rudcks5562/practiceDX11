#pragma once

struct TransformData {

	//Vec3 offset;
	//float dummy;// ������ ���� �����Ⱚ??

	Matrix matWorld = Matrix::Identity;



};
struct CameraData {

	//Vec3 offset;
	//float dummy;// ������ ���� �����Ⱚ??


	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;


};

