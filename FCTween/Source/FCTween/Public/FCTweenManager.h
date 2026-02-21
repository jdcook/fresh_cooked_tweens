// MIT License - Copyright 2026 Jared Cook
#pragma once
#pragma warning(push)
#pragma warning(disable : 4946)
#include "FCTweenInstance.h"

template <class T>
class FCTWEEN_API FCTweenManager
{
protected:
	typedef typename TDoubleLinkedList<T*>::TDoubleLinkedListNode TNode;

	TDoubleLinkedList<T*>* ActiveTweens;
	TDoubleLinkedList<T*>* RecycledTweens;
	// tweens to activate on the next update
	TDoubleLinkedList<T*>* TweensToActivate;

public:
	FCTweenManager(int Capacity)
	{
		ActiveTweens = new TDoubleLinkedList<T*>();
		RecycledTweens = new TDoubleLinkedList<T*>();
		TweensToActivate = new TDoubleLinkedList<T*>();
		for (int i = 0; i < Capacity; ++i)
		{
			RecycledTweens->AddTail(new T());
		}
	}

	virtual ~FCTweenManager()
	{
		TNode* CurNode = RecycledTweens->GetHead();
		while (CurNode != nullptr)
		{
			delete CurNode->GetValue();
			CurNode = CurNode->GetNextNode();
		}
		delete RecycledTweens;

		CurNode = ActiveTweens->GetHead();
		while (CurNode != nullptr)
		{
			delete CurNode->GetValue();
			CurNode = CurNode->GetNextNode();
		}
		delete ActiveTweens;

		CurNode = TweensToActivate->GetHead();
		while (CurNode != nullptr)
		{
			delete CurNode->GetValue();
			CurNode = CurNode->GetNextNode();
		}
		delete TweensToActivate;
	}

	void EnsureCapacity(int Num)
	{
		int NumExistingTweens = ActiveTweens->Num() + TweensToActivate->Num() + RecycledTweens->Num();
		for (int i = NumExistingTweens; i < Num; ++i)
		{
			RecycledTweens->AddTail(new T());
		}
	}

	int GetCurrentCapacity()
	{
		return ActiveTweens->Num() + TweensToActivate->Num() + RecycledTweens->Num();
	}

	void Update(float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused)
	{
		// add pending tweens
		TNode* CurNode = TweensToActivate->GetHead();
		while (CurNode != nullptr)
		{
			TNode* NodeToActivate = CurNode;
			CurNode = CurNode->GetNextNode();
			StartNode(NodeToActivate);
			TweensToActivate->RemoveNode(NodeToActivate, false);
			ActiveTweens->AddTail(NodeToActivate);
		}

		// update tweens
		CurNode = ActiveTweens->GetHead();
		while (CurNode != nullptr)
		{
			bool bShouldRemove = UpdateCurrentNode(CurNode, UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
			TNode* NextNode = CurNode->GetNextNode();
			if (bShouldRemove)
			{
				ActiveTweens->RemoveNode(CurNode, false);
				RecycleTween(CurNode);
			}
			CurNode = NextNode;
		}
	}

	virtual bool UpdateCurrentNode(TNode* Node, float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused)
	{
		FCTweenInstance* Tween = reinterpret_cast<FCTweenInstance*>(Node->GetValue());
		Tween->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
		return !Tween->bIsActive;
	}

	virtual void StartNode(TNode* Node)
	{
		FCTweenInstance* Tween = reinterpret_cast<FCTweenInstance*>(Node->GetValue());
		Tween->Start();
	}

	virtual void DestroyNode(TNode* Node)
	{
		FCTweenInstance* Tween = reinterpret_cast<FCTweenInstance*>(Node->GetValue());
		Tween->Destroy();
	}

	void ClearActiveTweens()
	{
		TNode* CurNode = TweensToActivate->GetHead();
		while (CurNode != nullptr)
		{
			TNode* NodeToRecycle = CurNode;
			CurNode = CurNode->GetNextNode();

			DestroyNode(NodeToRecycle);
			TweensToActivate->RemoveNode(NodeToRecycle, false);
			RecycledTweens->AddTail(NodeToRecycle);
		}

		CurNode = ActiveTweens->GetHead();
		while (CurNode != nullptr)
		{
			TNode* NodeToRecycle = CurNode;
			CurNode = CurNode->GetNextNode();

			DestroyNode(NodeToRecycle);
			ActiveTweens->RemoveNode(NodeToRecycle, false);
			RecycledTweens->AddTail(NodeToRecycle);
		}
	}

	T* CreateTween()
	{
		TNode* NewTween = GetNewTween();
		TweensToActivate->AddTail(NewTween);
		return NewTween->GetValue();
	}

private:
	TNode* GetNewTween()
	{
		TNode* Node = RecycledTweens->GetHead();
		if (Node != nullptr)
		{
			RecycledTweens->RemoveNode(Node, false);
			return Node;
		}
		return new TNode(new T());
	}

	void RecycleTween(TNode* ToRecycle)
	{
		RecycledTweens->AddTail(ToRecycle);
	}
};

#pragma warning(pop)