#pragma once

template <class T>
class SingleListNode
{
private:
	SingleListNode* next;
	T data;

public:
	inline SingleListNode() : next(nullptr){}
	inline SingleListNode(const T& item) : next(nullptr), data(item){}
	inline SingleListNode(const SingleListNode<T> &node)
	{
		next = node.next;
		data = node.data;
	}

	inline SingleListNode* getNext() const { return next; }
	inline void setNext(SingleListNode* node) { next = node; }

	inline T getData() const { return data; }
	inline void setData(const T& item) { data = item; }
};

template <class T>
class SinglyLinkedList
{
private:
	SingleListNode<T>* head;
	SingleListNode<T>* tail;
	int count;

public:
	SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
	SinglyLinkedList(const SinglyLinkedList<T> &list)
	{
		SingleListNode<T>* node = list.head;
		if (node != nullptr)
		{
			head = new SingleListNode<T>(node->getData());
			tail = head;
			node = node->getNext();
			while (node != nullptr)
			{
				SingleListNode<T>* n = new SingleListNode<T>(node->getData());
				tail->setNext(n);
				tail = n;
				node = node->getNext();
			}
		}
	}

	inline int getCount() const { return count; }

	inline SingleListNode<T>* getHead() { return head; }

	inline SingleListNode<T>* getTail() { return tail; }

	void insertAfter(SingleListNode<T>* node, const T& data)
	{
		if (count == 0)
			return insert(data);

		SingleListNode<T>* next = node->getNext();
		SingleListNode<T>* n = new SingleListNode<T>(data);


		n->setNext(next);
		node->setNext(n);

		if (node == tail)
			tail = n;

		count++;
	}

	void insertAtFront(const T& data)
	{
		SingleListNode<T>* n = new SingleListNode<T>(data);
		if (count == 0)
		{
			head = n;
			tail = n;
		}
		else
		{
			n->setNext(head);
			head = n;
		}
		count++;
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

		SingleListNode<T>* n = head->getNext();
		T val = head->getData();
		delete head;
		head = n;
		count--;

		return val;
	}

	T removeNext(SingleListNode<T>* node)
	{
		if (count == 0)
			return nullptr;

		if (count == 1)
			return removeHead();

		SingleListNode<T>* next = node->getNext();
		if (next == nullptr) return nullptr;

		T val = next->getData();

		delete next;

		if (node == head)
			head = next;

		count--;

		return val;
	}

	void clear()
	{
		if (count == 0) return;

		while (head != nullptr)
		{
			SingleListNode<T>* next = head->getNext();
			delete head;
			head = next;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	inline T* toArray()
	{
		T* data = new T[count];
		SingleListNode<T>* node = head;
		for (int i = 0; i < count; i++)
		{
			data[i] = node->getData();
			node = node->getNext();
		}
		return data;
	}

	~SinglyLinkedList(){ clear(); }

private:
	inline void insert(const T& data)
	{
		head = new SingleListNode<T>(data); //ERROR HERE
		tail = head;
		count++;
	}
};
