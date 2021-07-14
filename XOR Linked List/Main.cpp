#include <iostream>
#include <string>
#include "XorLinkedList.h"

void chooseCommand(XorLinkedList list)
{
	int n;
	std::string command;

	while (std::cin >> command)
	{
		if (command == "ACTUAL")
			list.getActual();
		else if (command == "NEXT")
			list.getNext();
		else if (command == "PREV")
			list.getPrev();
		else if (command == "ADD_BEG")
		{
			std::cin >> n;
			list.addBeg(n);
		}
		else if (command == "ADD_END")
		{
			std::cin >> n;
			list.addEnd(n);
		}
		else if (command == "ADD_ACT")
		{
			std::cin >> n;
			list.addAct(n);
		}
		else if (command == "DEL_BEG")
			list.delBeg();
		else if (command == "DEL_END")
			list.delEnd();
		else if (command == "DEL_VAL")
		{
			std::cin >> n;
			list.delVal(n);
		}
		else if (command == "DEL_ACT")
			list.delAct();
		else if (command == "PRINT_FORWARD")
			list.print(XorLinkedList::FORWARD);
		else if (command == "PRINT_BACKWARD")
			list.print(XorLinkedList::BACKWARD);

	}
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	XorLinkedList list;
	chooseCommand(list);
}