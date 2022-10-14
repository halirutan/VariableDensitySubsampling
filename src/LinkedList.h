#pragma once

class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();

	Point data;
	LinkedList* next{};

	static void insertElement(const Point& newPoint, LinkedList *&anchor, int &nElements);
	static void deleteElement(int position, LinkedList *&anchor, int &nElements);
	static Point showElement(int position, LinkedList *anchor, int nElements);
};
