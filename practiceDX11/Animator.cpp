#include "stdafx.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Game.h"

Animator::Animator(): Super(ComponentType::Animator)
{

}

Animator::~Animator()
{

}

void Animator::Init()
{

}

void Animator::Update()
{
	shared_ptr<Animation> animation = GetCurrentAnimation();
	if (animation == nullptr) {
		return;
	}
	const keyFrame& keyframe = animation->GetKeyFrame(_currentKeyFrameIndex);
	float deltaTime = TIME->GetDeltaTime();
	_sumTime += deltaTime;
	if (_sumTime >= keyframe.time) {
		_currentKeyFrameIndex++;

		int32 totalCount = animation->GetKeyFrameCount();

		if (_currentKeyFrameIndex >= totalCount) {
			if (animation->isLoop()) {
				_currentKeyFrameIndex = 0;
			}
			else {
				_currentKeyFrameIndex = totalCount - 1;
			}
		}

		_sumTime = 0.f;
	}



}

std::shared_ptr<Animation> Animator::GetCurrentAnimation()
{
	return _currentAnimation;
}

const keyFrame& Animator::GetCurrentKeyFrame()
{


	return _currentAnimation->GetKeyFrame(_currentKeyFrameIndex);

}
