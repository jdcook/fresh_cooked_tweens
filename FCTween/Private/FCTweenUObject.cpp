#include "FCTweenUObject.h"

UFCTweenUObject::UFCTweenUObject()
{
	TweenInstance = nullptr;
}
void UFCTweenUObject::BeginDestroy()
{
	if (TweenInstance != nullptr)
	{
		TweenInstance->Destroy();
		TweenInstance = nullptr;
	}
	UObject::BeginDestroy();
}

void UFCTweenUObject::SetTweenInstance(FCTweenInstance* InTweenInstance)
{
	this->TweenInstance = InTweenInstance;
	// destroy when we are destroyed
	this->TweenInstance->SetAutoDestroy(false);
}

void UFCTweenUObject::Destroy()
{
	this->TweenInstance->Destroy();
	this->TweenInstance = nullptr;
	ConditionalBeginDestroy();
}
