#include <iostream>
#include <vector>
using namespace std;

template <class T> 
class queue 
{
protected:
	T *q;
	int start, end;
	int size;
	int pos;
public:
	queue(int n = 0);
	void push (T x);
	T front ();
	void pop ();
	bool IsFull();
	bool IsEmpty();
};

template <class T>
queue<T>::queue(int n)
{
	if (n < 0) throw ("Error");
	start = end = 0;
	size = n;
	pos = 0;
	q = new T[n];
}

template <class T> 
void queue<T>::push(T x)
{
	if (this->IsFull())
	{
		throw("Error");
	}
	q[end % size] = x;
	end++;
	end = (end % (size));
	pos++;
}

template <class T> 
void queue<T>::pop()
{
	if (this->IsEmpty())
	{
		throw("Error");
	}
	start++;
	start = (start % (size));
	pos--;
}

template <class T>
T queue<T>::front()
{
	return q[start % size];
}

template <class T>
bool queue<T>::IsEmpty()
{
	return pos == 0;
}

template <class T> 
bool queue<T>::IsFull()
{
	return pos == size;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector <vector <int> > e;
	e.resize(n + 1);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		--x, --y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	queue <int> q(n + 1);
	q.push(0);
	vector <int> d(n, -1);
	d[0] = 0;
	while (q.IsEmpty() == false)
	{
		int v = q.front();
		q.pop();
		for (int i = 0; i < e[v].size(); i++)
		{
			int to = e[v][i];
			if (d[to] == -1)
			{
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}
	cout << d[n - 1];
	/*queue <int> q(3);
	q.push(1);
	q.push(2);
	q.push(3);
	q.pop();
	q.pop();
	q.push(1);
	q.push(1);
	if (q.IsFull() == true) cout << "YES";*/
	return 0;
}

