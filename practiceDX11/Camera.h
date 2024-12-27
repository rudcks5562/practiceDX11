#pragma once
#include "Component.h"
enum class ProjectionType {

	Perspective,// 원근
	Orthographic// 직교투영
};



class Camera : public Component
{

	using Super = Component;

public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	void SetProjectionType(ProjectionType type) { _type = type; }
	ProjectionType GetProjectionType() { return _type; }

	void UpdateMatrix();

private:
	ProjectionType _type = ProjectionType::Orthographic;// 2d

public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;


};

