#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

template<class T> //T is the type will be saved in the list
class LinkedList
{
private:
	template<class T>
	class Node
	{
	private:
		T value;
		Node* next;
	public:
		Node(T& value)
		{
			this->value = value;
			this->next = nullptr;
		}
		void setValue(T& value)
		{
			this->value = value;
		}
		void setNext(Node* next)
		{
			this->next = next;
		}
		T& getValue()
		{
			return value;
		}
		Node* getNext()
		{
			return next;
		}
	};

Node*<T> start;

public:

	insertToEnd(T& item)
	{
		Node<T> newNode(item);
		Node<T>* node = start;
		while (node->next != nullptr)
		{
			node = node->next;
		}
		node->next = &newNode;
	}

	LinkedList(T& item) : start(Node(item))
	{

	}

	LinkedList(const LinkedList& other) :
		node(other.node)
	{

	}
};

#endif //__LINKEDLIST_H