#pragma once

struct TransformData {

	//Vec3 offset;
	//float dummy;// 정렬을 위한 쓰레기값??

	Matrix matWorld = Matrix::Identity;



};
struct CameraData {

	//Vec3 offset;
	//float dummy;// 정렬을 위한 쓰레기값??


	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;


};

