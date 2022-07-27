// MIT License - Copyright (c) 2022 Jared Cook
#pragma once
#include "FCTweenSubsystem.generated.h"

UCLASS()
class FCTWEEN_API UFCTweenSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	uint64 LastTickedFrame;
	UPROPERTY()
	float LastRealTimeSeconds;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual bool IsTickableInEditor() const override;
};
