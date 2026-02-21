// MIT License - Copyright 2026 Jared Cook
#pragma once
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"

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
	bool bInitialized = false;

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void FinishDestroy() override;

	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsAllowedToTick() const override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual bool IsTickableInEditor() const override;
};
