#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Init()
{
}

void Transform::Update()
{
}
Vec3 ToEulerAngles(DirectX::SimpleMath::Quaternion q)
{
	Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}
void Transform::UpdateTransform()
{
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);


	_matLocal = matScale * matRotation * matTranslation;

	if (HasParent()) {

		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else {
		_matWorld = _matLocal;
	}
	Vec3 scale;
	DirectX::SimpleMath::Quaternion quat;//rotation
	Vec3 position;

	_matWorld.Decompose(_scale, quat, _position);


	_rotation = ToEulerAngles(quat);
	//노말 단위벡터?

	_right = Vec3::Transform(Vec3::Right, _matWorld);
	_up = Vec3::Transform(Vec3::Up, _matWorld);
	_look = Vec3::Transform(Vec3::Right, _matWorld);
	//오른손 좌표계 왼손 좌표계 주의하기

	for (const std::shared_ptr<Transform>& child : _children) {
		child->UpdateTransform();
	}
}
