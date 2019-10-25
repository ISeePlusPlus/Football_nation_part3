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
		Node<T>* next;
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
		void setNext(Node<T>* next)
		{
			this->next = next;
		}
		T getValue() const
		{
			return value;
		}
		Node<T>* getNext() const
		{
			return next;
		}
	};

	Node<T>* start;

	Node<T>* getStart() const
	{
		return start;
	}

public:

	void insertToEnd(T& item)
	{
		Node<T> newNode(item);
		Node<T>* node = start;
		while (node->next != nullptr)
		{
			node = node->next;
		}
		node->next = &newNode;
	}



	LinkedList(T& item) : start(&Node<T>(item))
	{
	}

	LinkedList(const LinkedList& other) :
		start(other.node)
	{

	}

	friend ostream& operator<<(ostream& os, const LinkedList& list) // IMPORTANT!!! operator << must be implemented for T!
	{
		cout << list.getStart()->getValue();
		os << "Linked List: ";
		Node<T>* node = list.getStart();
		do
		{
			os << (node->getValue()) << " ---> ";
			node = node->getNext();
		} while (node != nullptr);
		os << endl;
		return os;
	}
};

#endif //__LINKEDLIST_H