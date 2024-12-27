#include "stdafx.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;


Camera::Camera():Super(ComponentType::Camera)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();


}

void Camera::UpdateMatrix()
{
	Vec3 eyePosition = GetTransform()->GetPosition();
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	Vec3 upDirection = GetTransform()->GetUp();
	S_MatView=::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	// 또는 월드행렬의 역행렬


	S_MatView = Matrix::Identity;

	if (_type == ProjectionType::Perspective) {
		::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);

	}
	else {
		::XMMatrixOrthographicLH(800, 600, 0.f, 1.f);
	}


}
