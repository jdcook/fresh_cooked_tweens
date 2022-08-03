// MIT License - Copyright (c) 2022 Jared Cook
#pragma once

template <class T>
class FCTWEEN_API FCTweenManager
{
	typedef typename TDoubleLinkedList<T*>::TDoubleLinkedListNode TNode;

private:
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

	~FCTweenManager()
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
			NodeToActivate->GetValue()->Start();
			TweensToActivate->RemoveNode(NodeToActivate, false);
			ActiveTweens->AddTail(NodeToActivate);
		}

		// update tweens
		CurNode = ActiveTweens->GetHead();
		while (CurNode != nullptr)
		{
			FCTweenInstance* CurTween = static_cast<FCTweenInstance*>(CurNode->GetValue());
			CurTween->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
			TNode* NextNode = CurNode->GetNextNode();
			if (!CurTween->bIsActive)
			{
				ActiveTweens->RemoveNode(CurNode, false);
				RecycleTween(CurNode);
			}
			CurNode = NextNode;
		}
	}

	void ClearActiveTweens()
	{
		TNode* CurNode = TweensToActivate->GetHead();
		while (CurNode != nullptr)
		{
			TNode* NodeToRecycle = CurNode;
			CurNode = CurNode->GetNextNode();

			NodeToRecycle->GetValue()->Destroy();
			TweensToActivate->RemoveNode(NodeToRecycle, false);
			RecycledTweens->AddTail(NodeToRecycle);
		}

		CurNode = ActiveTweens->GetHead();
		while (CurNode != nullptr)
		{
			TNode* NodeToRecycle = CurNode;
			CurNode = CurNode->GetNextNode();
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
