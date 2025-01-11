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
struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;
	float useAnimation;
	float padding;//16byte맞춰줘야함. float2개가 부족? -> 조사

};

