#pragma once

template <class T>
class DoubleListNode
{
private:
	DoubleListNode* previous;
	DoubleListNode* next;
	T data;

public:
	inline DoubleListNode(const T& item) : previous(NULL), next(NULL), data(item){}

	inline DoubleListNode* getPrevious() const { return previous; }
	inline void setPrevious(DoubleListNode* node) { previous = node; }

	inline DoubleListNode* getNext() const { return next; }
	inline void setNext(DoubleListNode* node) { next = node; }

	inline T getData() const { return data; }
	inline void setData(const T& item) { data = item; }
};

template <class T>
class DoublyLinkedList
{
private:
	DoubleListNode<T>* head;
	DoubleListNode<T>* tail;
	int count;

public:
	inline DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

	inline int getCount() const { return count; }

	inline DoubleListNode<T>* getHead() { return head; }

	inline DoubleListNode<T>* getTail() { return tail; }

	void insertBefore(DoubleListNode<T>* node, const T& data)
	{
		if (count == 0)
			return insert(data);

		DoubleListNode<T> prev = node->getPrevious();
		DoubleListNode<T> n = new DoubleListNode<T>(data);

		n->setPrevious(prev);
		n->setNext(node);

		node->setPrevious(n);
		if (prev != null)
			prev->setNext(n);

		if (node == head)
			head = n;

		count++;
	}

	void insertAfter(DoubleListNode<T>* node, const T& data)
	{
		if (count == 0)
			return insert(data);

		DoubleListNode<T> next = node->getNext();
		DoubleListNode<T> n = new DoubleListNode<T>(data);

		n->setPrevious(node);
		n->setNext(next);

		node->setNext(n);
		if (next != nullptr)
			next->setPrevious(n);

		if (node == tail)
			tail = n;

		count++;
	}

	void insertAtFront(const T& data)
	{
		insertBefore(head, data);
	}

	void insertAtEnd(const T& data)
	{
		insertAfter(tail, data);
	}

	T removeHead()
	{
		if (count == 0)
			return nullptr;

		if (count == 1)
		{
			T val = head->getData();
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return val;
		}

		DoubleListNode<T>* n = head->getNext();
		T val = head->getData();
		delete head;
		head = n;
		count--;

		return val;
	}

	T removeTail()
	{
		if (count == 0)
			return nullptr;

		if (count == 1)
		{
			T val = head->getData();
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return val;
		}

		DoubleListNode<T>* n = tail->getPrevious();
		T val = head->getData();
		delete tail;
		tail = n;
		count--;
	}

	T remove(DoubleListNode<T>* node)
	{
		if (count == 0)
			return nullptr;

		if (count == 1)
			return removeHead();

		DoubleListNode<T>* prev = node->getPrevious();
		DoubleListNode<T>* next = node->getNext();

		T val = node->getData();

		delete node;

		if (prev != nullptr)
			prev->setNext(next);

		if (next != nullptr)
			next->setPrevious(prev);

		if (node == head)
			head = next;

		if (node == tail)
			tail = prev;

		count--;

		return val;
	}

	void clear()
	{
		if (count == 0) return;

		while (head != nullptr)
		{
			DoubleListNode<T>* next = head->getNext();
			delete head;
			head = next;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	~DoublyLinkedList(){ clear(); }

private:
	inline void insert(const T& data)
	{
		head = new DoubleListNode<T>(data);
		tail = head;
		count++;
	}
};

