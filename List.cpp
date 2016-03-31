#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
struct ListItem
{
	T Data;
	int Index;
	ListItem * Next;
	ListItem(int index, int data, ListItem * next = NULL)
	{
		Index = index;
		Data = data;
		Next = next;
	}
};

template <typename T>
class List
{
private:
	int _itemsCount;
	ListItem<T> * _first;
	ListItem<T> * _last;
public:
	List();
	~List();
	bool Add(int index, T data);
	ListItem<T>* Get(int index);
	bool Del(int index);
	bool DelFirst();
	bool DelLast();
	void AddLast(T data);
	void AddFirst(T data);
	void ChangeIndex(ListItem<T>* item, bool plus);
};

/** List::List() */
template <typename T>
List<T>::List()
{
	_itemsCount = 0;
	_first = _last = NULL;
}

/** List::~List() */
template <typename T>
List<T>::~List()
{
	ListItem<T> * current = NULL;
	ListItem<T> * next = _first;
	while (next)
	{
		current = next;
		next = next->Next;
		delete current;
	}
}

/** bool List::Add(int index, int data) */
template <typename T>
bool List<T>::Add(int index, T data)
{
	if (index < 0 || index > _itemsCount)
		return false;
	if (index == 0)
		AddFirst(data);
	else if (index == _itemsCount)
		AddLast(data);
	else
	{
		ListItem<T> * prev = Get(index - 1);
		ListItem<T> * newItem = new ListItem<T>(index, data, prev->Next);
		prev->Next = newItem;
		_itemsCount++;
		ChangeIndex(newItem->Next, true);
	}
	return true;
}

/** ListItem* List::Get(int index) */
template <typename T>
ListItem<T>* List<T>::Get(int index)
{
	if (index < 0 || index >= _itemsCount)
		throw "Bad index";

	ListItem<T> *current = _first;
	while (current->Index < index)
		current = current->Next;

	return current;
}

/** bool List::Del(int index) */
template <typename T>
bool List<T>::Del(int index)
{
	if (index < 0 || index >= _itemsCount)
		return false;

	if (index == 0)
		DelFirst();
	else if (index == _itemsCount - 1)
		DelLast();
	else
	{
		ListItem<T> * prev = Get(index - 1);
		ListItem<T> * next = prev->Next->Next;
		delete prev->Next;
		prev->Next = next;
		_itemsCount--;
		ChangeIndex(next, false);
	}
	return true;
}

/** bool List::DelFirst() */
template <typename T>
bool List<T>::DelFirst()
{
	if (_first == NULL)
		return false;

	if (_itemsCount == 1)
	{
		delete _first;
		_first = NULL;
		_last = NULL;
	}
	else
	{
		ListItem<T> * current = _first;
		_first = _first->Next;
		delete current;
		ChangeIndex(_first, false);
	}
	_itemsCount--;
	return true;
}

/** bool List::DelLast() */
template <typename T>
bool List<T>::DelLast()
{
	if (_last == NULL)
		return false;

	if (_itemsCount == 1)
	{
		delete _first;
		delete _last;
		_first = _last = NULL;
	}
	else
	{
		_last = Get(_itemsCount - 2);
		delete _last->Next;
		_last->Next = NULL;
	}
	_itemsCount--;
	return true;
}

/** void List::AddFirst(int data) */
template <typename T>
void List<T>::AddFirst(T data)
{
	if (_first == NULL)
		_first = _last = new ListItem<T>(0, data);
	else
	{
		_first = new ListItem<T>(0, data, _first);
		ChangeIndex(_first->Next, true);
	}
	_itemsCount++;
}

/** void List::AddLast(int data) */
template <typename T>
void List<T>::AddLast(T data)
{
	if (_first == NULL)
		_first = _last = new ListItem<T>(0, data);
	else
	{
		_last->Next = new ListItem<T>(_last->Index + 1, data);
		_last = _last->Next;
		_last->Next = NULL;
	}
	_itemsCount++;
}

/** void List::ChangeIndex(ListItem* item, bool plus) */
template <typename T>
void List<T>::ChangeIndex(ListItem<T>* item, bool plus)
{
	if (plus)
		while (item)
		{
			item->Index++;
			item = item->Next;
		}
	else
		while (item)
		{
			item->Index--;
			item = item->Next;
		}
}

/** vector<string> &split(const string &s, char delim, vector<string> &elems) */
vector<string> &split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}

/** vector<string> &split(const string &s, char delim, vector<string> &elems) */
vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}


/** int main(int argc, char* argv[]) */
int main(int argc, char* argv[])
{
	List<int> list;
	int N;
	cout << "N = ";
	cin >> N;
	vector<string> expressions;
	string expression;
	int i = 0;
	int size;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (i < N && i >= 0)
	{
		cout << i + 1 << ">>";
		getline(cin, expression);
		expressions = split(expression, ' ');
		size = expressions.size();
		if (size == 0)
		{
			cout << "The expression is not correct. Try again.\n";
			i--;
		}
		else if (expressions[0] == "add")
		{
			if (size == 3)
			{
				if (!list.Add(stoi(expressions[1]), stoi(expressions[2])))
				{
					cout << "Bad index. Try again\n";
					i--;
				}
			}
			else
			{
				cout << "The expression is not correct. Try again.\n";
				i--;
			}
		}
		else if (expressions[0] == "del")
		{
			if (size == 2)
			{
				if (!list.Del(stoi(expressions[1])))
				{
					cout << "Bad index. Try again\n";
					i--;
				}
			}
			else
			{
				cout << "The expression is not correct. Try again.\n";
				i--;
			}
		}
		else if (expressions[0] == "get")
		{
			if (size == 2)
			{
				try
				{
					cout << list.Get(stoi(expressions[1]))->Data << endl;
				}
				catch (char* message)
				{
					cout << message << ". Try again\n";
					i--;
				}
			}
			else
			{
				cout << "The expression is not correct. Try again.\n";
				i--;
			}
		}
		else
		{
			cout << "The operation is not correct. Try again.\n";
			i--;
		}
		i++;
	}
	system("pause");
	return 0;
}