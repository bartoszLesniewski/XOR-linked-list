#pragma once
#include "Node.h"

class XorLinkedList
{
private:
	Node* begin;
	Node* end;;
	Node* actual;
	Node* prev;
	Node* next;

public:
	enum printOption
	{
		FORWARD,
		BACKWARD
	};

	XorLinkedList();
	~XorLinkedList();

	Node* xorPointers(Node* n1, Node* n2) const;
	void updateActualAfterAdd(Node* newNode);
	void updateActualAfterDel();
	void addBeg(int newValue);
	void addEnd(int newValue);
	void addAct(int newValue);
	void delBeg();
	void delEnd();
	void delAct();
	void delNode(Node** tmp, Node** previousNode, Node** currentNode);
	void delVal(int n);
	void print(printOption opt) const;
	void getActual() const;
	void getNext();
	void getPrev();
};