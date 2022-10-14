#include "SubsampleMain.h"


LinkedList::LinkedList()
	: next(nullptr)
{}
LinkedList::~LinkedList() = default;

void LinkedList::insertElement(const Point &newPoint, LinkedList *&anchor, int &nElements)
{
	// list is empty
	if (anchor == nullptr) {
		LinkedList *element = new LinkedList();
		element->data = newPoint;
		element->next = nullptr;
		anchor = element;
	}
		// list is not empty
	else {
		LinkedList *element = anchor;
		LinkedList *newElement = new LinkedList();
		while (element->next != nullptr)
			element = element->next;
		newElement->data = newPoint;
		newElement->next = nullptr;
		element->next = newElement;
	}
	nElements++;
}

void LinkedList::deleteElement(int position, LinkedList *&anchor, int &nElements)
{
	if (position < nElements) {
		// delete first element in list
		if (position == 0) {
			LinkedList *del = anchor;
			anchor = anchor->next;
			delete del;
		}
			// iterate to desired position and delete element
		else {
			LinkedList *thisElement = anchor;
			LinkedList *elementBefore = anchor;
			for (int i = 0; i < position; i++) {
				elementBefore = thisElement;
				thisElement = thisElement->next;
			}
			LinkedList *elementBehind = thisElement->next;
			elementBefore->next = elementBehind;
			delete thisElement;
		}
		nElements--;
	}
	else {
		cout << "error" << endl << endl;
		system("PAUSE");
		exit(1);
	}
}

Point LinkedList::showElement(int position, LinkedList *anchor, int nElements)
{
	if (position < nElements) {
		Point showThis;
		LinkedList *thisElement = anchor;

		for (int i = 0; i < position; i++) {
			thisElement = thisElement->next;
		}
		if (thisElement != nullptr)
			showThis = thisElement->data;

		return showThis;
	}
	else {
		cout << "error" << endl << endl;
		system("PAUSE");
		exit(1);
	}
}
