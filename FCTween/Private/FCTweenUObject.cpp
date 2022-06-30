#include "FCTweenUObject.h"

UFCTweenUObject::UFCTweenUObject()
{
	Tween = nullptr;
}
void UFCTweenUObject::BeginDestroy()
{
	if (Tween != nullptr)
	{
		Tween->Destroy();
		Tween = nullptr;
	}
	UObject::BeginDestroy();
}

void UFCTweenUObject::SetTweenInstance(FCTweenInstance* InTween)
{
	this->Tween = InTween;
	// destroy when we are destroyed
	this->Tween->SetAutoDestroy(false);
}

void UFCTweenUObject::Destroy()
{
	this->Tween->Destroy();
	this->Tween = nullptr;
	ConditionalBeginDestroy();
}
