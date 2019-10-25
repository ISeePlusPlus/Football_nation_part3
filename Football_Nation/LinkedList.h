#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

template<class T> // IMPORTANT: T is the type will be saved in the list. T must have operator<< AND copy C'tor!
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
		Node<T>* newNode = new Node<T>(item);
		Node<T>* node = start;
		while (node->getNext() != nullptr)
		{
			node = node->getNext();
		}
		node->setNext(newNode);
	}
	//NOTE: we didn't know which delete method to implement so we did both deleteEnd and deleteStart.
	void deleteEnd()
	{
		Node<T>* preceding;
		Node<T>* node = start;
		do
		{
			preceding = node;
			node = node->getNext();
		} while (node->getNext() != nullptr);
		delete node;
		preceding->setNext(nullptr);
	}

	void deleteStart()
	{
		Node<T>* temp = start;
		start = start->getNext();
		delete temp;
	}

	LinkedList(T& item)
	{
		Node<T>* node = new Node<T>(item);
		start = node;
	}

	LinkedList(const LinkedList& other) :
		start(other.node)
	{

	}

	~LinkedList()
	{
		Node<T>* node = start;
		do
		{
			Node<T>* next = node->getNext();
			delete node;
			node = next;
		} while (node->getNext() != nullptr);
	}

	friend ostream& operator<<(ostream& os, const LinkedList& list) // IMPORTANT!!! operator << must be implemented for T!
	{
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