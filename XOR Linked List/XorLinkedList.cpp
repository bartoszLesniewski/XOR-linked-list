#include <iostream>
#include "XorLinkedList.h"

XorLinkedList::XorLinkedList()
{
	begin = nullptr;
	end = nullptr;
	actual = nullptr;
	prev = nullptr;
	next = nullptr;
}

XorLinkedList::~XorLinkedList()
{
	while (begin != nullptr)
		delBeg();
}

Node* XorLinkedList::xorPointers(Node* n1, Node* n2) const
{
	return (Node*)((uintptr_t)n1 ^ (uintptr_t)n2);
}

void XorLinkedList::updateActualAfterAdd(Node* newNode)
{
	if (actual == begin)
	{
		prev = end;
		next = begin->xorPtr;
	}
	else if (actual == end)
	{
		prev = end->xorPtr;
		next = begin;
	}
	else
	{
		if (newNode->xorPtr == actual && newNode == begin)
			prev = newNode;
		else if (newNode->xorPtr == actual && newNode == end)
			next = newNode;
	}
}

void XorLinkedList::addBeg(int newValue)
{
	if (begin == nullptr)
	{
		begin = new Node;
		begin->xorPtr = nullptr;
		begin->value = newValue;
		end = actual = prev = next = begin;
	}

	else
	{
		Node* tmp = new Node;
		tmp->xorPtr = begin;
		tmp->value = newValue;
		begin->xorPtr = xorPointers(tmp, begin->xorPtr);
		begin = tmp;
		updateActualAfterAdd(tmp);
	}
}

void XorLinkedList::addEnd(int newValue)
{
	if (end == nullptr)
		addBeg(newValue);
	else
	{
		Node* tmp = new Node;
		tmp->xorPtr = end;
		tmp->value = newValue;
		end->xorPtr = xorPointers(tmp, end->xorPtr);
		end = tmp;
		updateActualAfterAdd(tmp);
	}
}

void XorLinkedList::addAct(int newValue)
{
	if (prev == end) // actual jest pierwszym lub jedynym wêz³em na liœcie
		addBeg(newValue);

	else
	{
		Node* tmp = new Node;
		tmp->value = newValue;
		tmp->xorPtr = xorPointers(prev, actual);

		// je¿eli actual jest ostatnim wêz³em, to xorPtr wskazuje bezpoœrednio na nowo dodany wêze³ (xor tmp z 0)
		if (actual == end)
			actual->xorPtr = tmp;
		else
			actual->xorPtr = xorPointers(tmp, next);

		prev->xorPtr = xorPointers(xorPointers(prev->xorPtr, actual), tmp);
		prev = tmp;
	}
}

// aktualizuje aktualny wêze³ po usuniêciu w przypadku, gdy by³ on równy jednemu ze skrajnych wêz³ów (begin lub end)
void XorLinkedList::updateActualAfterDel()
{
	if (begin == end) // jeœli pozosta³ tylko jeden lub zero wêz³ów
		actual = next = prev = end;
	else
	{
		actual = end;
		next = begin;
		prev = end->xorPtr;
	}
}

void XorLinkedList::delBeg()
{
	if (begin != nullptr)
	{
		Node* tmp = begin;
		begin = begin->xorPtr;

		if (begin != nullptr)
			begin->xorPtr = xorPointers(tmp, begin->xorPtr);

		if (end == tmp)
			end = begin;

		if (prev == tmp)
			prev = end;

		if (next == tmp)
			next = begin;

		if (actual == tmp)
			updateActualAfterDel();

		delete tmp;
	}
}

void XorLinkedList::delEnd()
{
	if (end != nullptr)
	{
		Node* tmp = end;
		end = end->xorPtr;

		if (end != nullptr)
			end->xorPtr = xorPointers(tmp, end->xorPtr);

		if (begin == tmp)
			begin = end;

		if (prev == tmp)
			prev = end;

		if (next == tmp)
			next = begin;

		if (actual == tmp)
			updateActualAfterDel();

		delete tmp;
	}
}

void XorLinkedList::delAct()
{
	if (actual != nullptr)
	{
		if (actual == begin)
			delBeg();

		else if (actual == end)
			delEnd();

		else
		{
			Node* tmp = actual;

			actual = prev;
			next->xorPtr = xorPointers(xorPointers(next->xorPtr, tmp), actual);

			if (actual == begin)
			{
				prev = end;
				actual->xorPtr = next;
			}

			else
			{
				prev = xorPointers(prev->xorPtr, tmp);
				actual->xorPtr = xorPointers(prev, next);
			}

			delete tmp;
		}
	}
}

// usuwa wêze³ wyszukany podczas iteracji w funkcji delVal i odpowiednio aktualizuje s¹siadów
void XorLinkedList::delNode(Node** tmp, Node** previousNode, Node** currentNode)
{
	Node* nodeToDelete = *tmp;
	Node* nextNode = xorPointers(nodeToDelete->xorPtr, *previousNode);
	*tmp = *previousNode;
	*previousNode = xorPointers((*previousNode)->xorPtr, nodeToDelete);
	(*tmp)->xorPtr = xorPointers(*previousNode, nextNode);
	nextNode->xorPtr = xorPointers(xorPointers(nextNode->xorPtr, nodeToDelete), *tmp);
	*currentNode = *tmp;

	if (nodeToDelete == prev)
		prev = *tmp;
	if (nodeToDelete == next)
		next = nextNode;

	delete nodeToDelete;
}

void XorLinkedList::delVal(int n)
{
	Node* previousNode = nullptr, * currentNode = begin, * tmp = begin;

	while (tmp != nullptr)
	{
		if (tmp->value == n)
		{
			if (tmp == begin)
			{
				delBeg();
				tmp = begin;
				currentNode = begin;
				previousNode = nullptr;
			}
			else if (tmp == end)
			{
				delEnd();
				tmp = end;
				currentNode = end;
				previousNode = end->xorPtr;
			}
			else if (tmp == actual)
			{
				delAct();
				tmp = actual;
				currentNode = actual;
				previousNode = prev;
			}
			else
				delNode(&tmp, &previousNode, &currentNode);
		}
		else
		{
			tmp = xorPointers(previousNode, tmp->xorPtr);
			previousNode = currentNode;
			currentNode = tmp;
		}
	}
}

void XorLinkedList::print(printOption opt) const
{
	Node* previousNode = nullptr, * currentNode, * tmp;

	if (opt == FORWARD)
	{
		currentNode = begin;
		tmp = begin;
	}
	else
	{
		currentNode = end;
		tmp = end;
	}

	if (tmp == nullptr)
		std::cout << "NULL";

	else
	{
		while (tmp != nullptr)
		{
			std::cout << tmp->value << " ";
			tmp = xorPointers(previousNode, tmp->xorPtr);
			previousNode = currentNode;
			currentNode = tmp;
		}
	}

	std::cout << std::endl;
}

void XorLinkedList::getActual() const
{
	if (actual == nullptr)
		std::cout << "NULL" << std::endl;
	else
		std::cout << actual->value << std::endl;
}

void XorLinkedList::getNext()
{
	if (next != nullptr)
	{
		std::cout << next->value << std::endl;

		if (begin == end)
			actual = next = prev = begin;
		else
		{
			prev = actual;
			actual = next;

			if (actual == end)
				next = begin;
			else if (actual == begin)
				next = begin->xorPtr;
			else
				next = xorPointers(next->xorPtr, prev); // w tym miejscu prev = poprzedni adres actual
		}
	}
	else
		std::cout << "NULL" << std::endl;
}

void XorLinkedList::getPrev()
{
	if (prev != nullptr)
	{
		std::cout << prev->value << std::endl;

		if (begin == end) // jest tylko jeden wêze³ (lub 0)
			actual = next = prev = begin;
		else
		{
			next = actual;
			actual = prev;

			if (actual == begin)
				prev = end;
			else if (actual == end)
				prev = end->xorPtr;
			else
				prev = xorPointers(prev->xorPtr, next); // w tym miejscu next = poprzedni adres actual
		}
	}
	else
		std::cout << "NULL" << std::endl;
}