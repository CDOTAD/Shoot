#ifndef _Iterator_H_
#define _Iterator_H_
#include<vector>
using namespace std;

template<class Item>
class Iterator
{
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual Item currentItem() = 0;
	virtual int current() = 0;
	virtual bool isDone() = 0;
	virtual ~Iterator() {}
};

template<class Item>
class ConcreteAggregate;

template<class Item>
class ConcreteIterator :public Iterator<Item>
{
private:
	ConcreteAggregate<Item>* aggr;
	int cur;
public:
	ConcreteIterator(ConcreteAggregate<Item>*a) :aggr(a), cur(0) {}
	void first()
	{
		cur = 0;
	}
	void next()
	{
		if (cur < aggr->getLength())
		{
			cur++;
		}
	}
	Item currentItem()
	{
		if (cur < aggr->getLength())
		{
			return aggr->Pop(cur);
		}
		else
			return NULL;
	}
	int current()
	{
		return cur;
	}
	bool isDone()
	{
		if (cur >= aggr->getLength())
		{
			return true;
		}
		else
			return false;
	}
};

template<class Item>
class Aggregate
{
public:
	virtual Iterator<Item>* createIterator() = 0;
	virtual ~Aggregate() {}
};

template<class Item>
class ConcreteAggregate :public Aggregate<Item>
{
public:
	//vector<Item> data;
	Item* data;
	int length;
public:
	ConcreteAggregate<Item>(int length)
	{
		this->data = new Item[length];
		this->length = length;
	}
	~ConcreteAggregate<Item>()
	{

	}
	Iterator<Item>* createIterator()
	{
		return new ConcreteIterator<Item>(this);
	}
	//Item& operator[](int index);
	int getLength()
	{
		//return data.size();
		return length;
	}
	void Push(Item item,int index)
	{
		//data.push_back(item);
		if (index < length)
		{
			data[index] = item;
		}
		
	}
	Item& Pop(int index)
	{
		return data[index];
	}
};

#endif
