#pragma once
#include "FCTweenInstance.h"

#include "FCTweenUObject.generated.h"

/**
 * @brief Use this to wrap an FCTweenInstance inside a UObject, so that it's destroyed when its outer object is destroyed
 */
UCLASS()
class UFCTweenUObject : public UObject
{
	GENERATED_BODY()

public:
	FCTweenInstance* TweenInstance;

	UFCTweenUObject();
	virtual void BeginDestroy() override;

	void SetTweenInstance(FCTweenInstance* InTweenInstance);
	/**
	 * @brief Stop the tween immediately and mark this object for destruction
	 */
	void Destroy();
};
