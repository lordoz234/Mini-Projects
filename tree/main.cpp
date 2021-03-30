#include <iostream>

using namespace std;

template <typename T>
class MyArray {
public:
    class iterator;
    T* arr;
    int _n;
    MyArray (int n = 1) :_n(n) {
        arr = new T[n];
    }
    T&operator[](int index) {
            return arr[index];
    };

    iterator begin() { return arr;}
    iterator end() { return arr + _n; }


    class iterator {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        T *cur;
        iterator(T* first) : cur(first)
        {}
        T&operator++ (int) { return *cur++;}
        T&operator++ () { return ++(*cur);}
        bool operator == (const iterator& it) {
            return cur == it.cur;
        }
        bool operator != (const iterator& it) {
            return cur != it.cur;
        }
        T&operator* () { return *cur;}
    };

};

int main () {
    MyArray <int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    MyArray<int>::iterator it = MyArray<int>::iterator(a.begin());
    for (auto i = MyArray<int>::iterator(a.begin()); i != MyArray<int>::iterator(a.end()); i++) {
       cout << *i << " ";
    }
    return 0;
}
