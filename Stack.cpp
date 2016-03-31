#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template<typename T>
class Stack
{
private:
	T* _array;
	unsigned int _size;
	unsigned int Index;
public:
	Stack();
	Stack(unsigned int size);
	~Stack();
	bool Add(T data);
	bool Del();
	T Get();
};

/** Stack<T>::Stack() */
template<typename T>
Stack<T>::Stack()
{
	_size = Index = 0;
	_array = nullptr;
}

/** Stack<T>::Stack(unsigned int size) */
template<typename T>
Stack<T>::Stack(unsigned int size)
{
	_size = size;
	Index = 0;
	_array = new T[size];
	for (int i = 0; i < size; i++)
		_array[i] = 0;
}

/** Stack<T>::~Stack() */
template<typename T>
Stack<T>::~Stack()
{
	delete[]_array;
}

/** bool Stack<T>::Add(T data) */
template<typename T>
bool Stack<T>::Add(T data)
{
	if (Index >= _size)
		return false;
	_array[Index] = data;
	Index++;
	return true;
}

/** bool Stack<T>::Del() */
template<typename T>
bool Stack<T>::Del()
{
	if (Index <= 0)
		return false;
	_array[--Index] = 0;
	return true;
}

/** T Stack<T>::Get() */
template<typename T>
T Stack<T>::Get()
{
	int temp = 0;
	if (Index != 0)
		temp = Index - 1;
	return _array[temp];
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
	cout << "Size of stack = ";
	cin >> maxSize;
	Stack<int> stack(maxSize);
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
				if (!stack.Add(stoi(expressions[1])))
				{
					cout << "Stack os full. Try again\n";
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
				if (!stack.Del())
				{
					cout << "Stack is empty. Try again\n";
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
				cout << stack.Get() << endl;
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