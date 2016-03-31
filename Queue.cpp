#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
class Queue
{
private:
	T* _array;
	int _head;
	int _tail;
	int _size;
	int _counter;
public:
	Queue();
	Queue(int size);
	~Queue();
	bool Add(T data);
	T Get();
	bool Del();
};

/** Queue<T>::Queue() */
template<typename T>
Queue<T>::Queue()
{
	_size = _head = _counter = _tail = 0;
	_array = nullptr;
}

/** Queue<T>::Queue(int size) */
template <typename T>
Queue<T>::Queue(int size)
{
	_size = size;
	_array = new T[size];
	for (int i = 0; i < _size; i++)
		_array[i] = 0;
	_head = _counter = _tail = 0;
}

/** Queue<T>::~Queue() */
template <typename T>
Queue<T>::~Queue()
{
	delete[] _array;
}

/** bool Queue<T>::Add(T data) */
template <typename T>
bool Queue<T>::Add(T data)
{
	if (_counter == _size)
		return false;
	if (_tail >= _size)
		_tail = 0;
	_array[_tail] = data;
	_counter++;
	_tail++;
	return true;
}

/** T Queue<T>::Get() */
template <typename T>
T Queue<T>::Get()
{
	return _array[_head];
}

/** bool Queue<T>::Del() */
template <typename T>
bool Queue<T>::Del()
{
	if (_counter == 0)
		return false;
	_array[_head] = 0;
	_head++;
	if (_head >= _size)
		_head = 0;
	_counter--;
	return true;
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

/** vector<string> split(const string &s, char delim) */
vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

/** int main(int argc, char* argv[]) */
int main(int argc, char* argv[])
{
	unsigned int maxSize;
	cout << "Size of queue = ";
	cin >> maxSize;
	Queue<int> queue(maxSize);
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
			if (size == 2)
			{
				if (!queue.Add(stoi(expressions[1])))
				{
					cout << "Queue is full. Try again.\n";
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
			if (size == 1)
			{
				if (!queue.Del())
				{
					cout << "Queue is empty. Try again.\n";
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
			if (size == 1)
				cout << queue.Get() << endl;
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