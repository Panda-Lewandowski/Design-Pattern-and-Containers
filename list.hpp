#ifndef LIST_HPP
#define LIST_HPP
#include "Exeptions.h"
#include "ListIterator.h"


namespace List_model
{
template<typename T>
struct ListElem
{
    T value;
    ListElem *next;
    ListElem *prev;
};

class ListBase
{
public:
    bool is_empty() const {return size>0 ? false:true;}
    int get_size() const {return size;}
    ListBase(int n = 0): size(n) {}
    virtual ~ListBase() = 0{}
protected:
    int size;
};

template<typename T>
class List: public ListBase
{
public:
    typedef ListIterator<T> iterator;
public:
    List(): ListBase(), head(nullptr), tail(nullptr) {}
    List(T * arr, int n);
    List(const List &old_list);
    ~List();
    T get(int n) const;
    T get_head() const {if is_empty() throw EmptyListAccessExeption("get_head"); return head->value;}
    T get_end() const {if is_empty() throw EmptyListAccessExeption("get_end");ListElem<T> *wrk = head; while(wrk->next != nullptr) wrk = wrk->next; return wrk->value;}
    void set(T const& new_value, int n);
    void push_end(T const& value);
    void push_begin(T const& value);
    void push_after(T const& value, int n);
    T delete_begin();
    T delete_index(int n);
    T delete_end();
    iterator begin() {return head;}
    iterator end() {return tail;}
    void clear();
    void swap(int n1, int n2);
    void sort();
    void show();
    int find(T const& value);
    List<T> operator + (List &obj);
    List<T> operator = (List &obj);
private:
    ListElem<T> *head, *tail;
};

template<typename T>
istream& operator>> (istream &is, List<T> &lst)
{
    T temp;
    lst.clear();
    while(is.good())
    {
        is>>temp;
        lst.push_end(temp);
    }
    return is;
}

template<typename T>
ostream& operator<< (ostream &os, List<T> &lst)
{
    for(List<T>::iterator it = lst.begin(); it!=nullptr; ++it)
        os<<it<<' ';
    os<<endl;
    return os;
}


template<typename T>
List<T>::List(T * arr, int n)
{
    ListElem<T> *prev, *cur;
    if (!(head = new(std::nothrow) ListElem<T>))
        throw OutOfMemoryListExeption("constructor");
    head->value = arr[0];
    head->next = nullptr;
    head->prev = nullptr;
    size = 1;
    prev = head;
    for (int i = 1; i<n; ++i)
    {
        if(!(cur = new(std::nothrow) ListElem<T>))
        {
            this->~List();
            throw OutOfMemoryListExeption("constructor");
        }
        cur->value = arr[i];
        cur->next = nullptr;
        cur->prev = prev;
        prev->next = cur;
        prev = cur;
        ++size;
    }
    tail = cur;
}

template<typename T>
List<T>::List(const List<T> &old_list)
{
    if (old_list.is_empty())
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    else
    {
        ListElem<T> *prev, *cur;
        if (!(head = new(std::nothrow) ListElem<T>))
            throw OutOfMemoryListExeption("constructor");
        head->value = old_list.get(0);
        head->next = nullptr;
        head->prev = nullptr;
        size = 1;
        prev = head;
        for(int i = 1; i<old_list.get_size(); ++i)
        {
            if(!(cur = new(std::nothrow) ListElem<T>))
                throw OutOfMemoryListExeption("constructor");
            cur->value = old_list.get(i);
            cur->next = nullptr;
            cur->prev = prev;
            prev->next = cur;
            prev = cur;
        }
        tail = cur;
        size = old_list.get_size();
    }
}

template<typename T>
List<T>::~List()
{
    ListElem<T> *wrk;
    while(head != nullptr)
    {
        wrk = head->next;
        delete head;
        head = wrk;
    }
}

template<typename T>
T List<T>::get(int n) const
{
    if (is_empty())
        throw EmptyListAccessExeption("get");
    if((n>=0)&&(n<size))
    {
        ListElem<T> *wrk = head;
        for(int i = 0; i<n; ++i)
            wrk = wrk->next;
        return wrk->value;
    }
    else
        throw OutOfRangeListExeption("get");
}

template<typename T>
void List<T>::set(T const& new_value, int n)
{
    if((n<0)||(n>size))
        throw OutOfRangeListExeption("set");
    ListElem<T> *wrk = head;
    for(int i = 0; i<n; ++i)
        wrk = wrk->next;
    wrk->value = new_value;
}

template<typename T>
void List<T>::push_begin(T const& value)
{
    ListElem<T> *wrk = new ListElem<T>;
    wrk->value = value;
    wrk->next = head;
    wrk->prev = nullptr;
    head = wrk;
    ++size;
    if(size == 1)
        tail = head;
}

template<typename T>
void List<T>::push_end(T const& value)
{
    ListElem<T> *wrk = new ListElem<T>;
    wrk->value = value;
    wrk->next = nullptr;
    if (is_empty())
    {
        head = wrk;
        head->prev = nullptr;
        tail = head;
        ++size;
        return;
    }
    tail->next = wrk;
    wrk->prev = tail;
    tail = wrk;
    ++size;
}

template<typename T>
void List<T>::push_after(T const& value, int n)
{
    if ((n<0)||(n>=size))
        throw OutOfRangeListExeption("push_after");
    if((n>=0)&&(n<size - 1))
    {
        ListElem<T> *wrk = new ListElem<T>;
        wrk->value = value;
        ListElem<T> *it = head;
        for(int i = 0; i<n; ++i)
            it = it->next;
        wrk->next = it->next;
        it->next = wrk;
        wrk->prev = it;
        it = wrk->next;
        it->prev = wrk;
        ++size;
    }
    else
        push_end(value);
}

template<typename T>
inline T List<T>::delete_begin()
{
    if(size == 0)
        throw EmptyListAccessExeption("delete_begin");
    T value;
    ListElem<T> *wrk = head;
    value = wrk->value;
    head = head->next;
    if (head)
        head->prev = nullptr;
    delete wrk;
    --size;
    return value;
}

template<typename T>
T List<T>::delete_end()
{
    if (size == 0)
        EmptyListAccessExeption("delete_end");
    T value;
    ListElem<T> *wrk = tail;
    value = tail->value;
    tail = tail->prev;
    tail->next = nullptr;
    delete wrk;
    --size;
    return value;
}

template<typename T>
void List<T>::clear()
{
    while(size>0)
        delete_begin();
}

template<typename T>
T List<T>::delete_index(int n)
{
    if (is_empty())
        throw EmptyListAccessExeption("delete_index");
    if ((n<0)||(n>=size))
        throw OutOfRangeListExeption("delete_index");
    if((n>0)&&(n<size-1))
    {
        int i;
        ListElem<T> *wrk1 = head, *wrk2 = head;
        for(i = 0; i<n-1; ++i)
        {
            wrk1 = wrk1->next;
            wrk2 = wrk2->next;
        }
        wrk1 = wrk1->next;
        wrk2->next = wrk1->next;
        wrk1->next->prev = wrk2;
        delete wrk1;
        --size;
    }
    else
        if(n == 0)
            delete_begin();
        else
            delete_end();
}

template<typename T>
int List<T>::find(T const& value)
{
    int i;
    ListElem<T> *wrk = head;
    for(i = 0; i<size; ++i)
        if (get(i) == value)
            return i+1;
    return -1;
}

template<typename T>
void List<T>::show()
{
    T wrk;
    for(int i = 0; i<size; ++i)
    {
        wrk = get(i);
        cout << wrk << " ";
    }
    cout <<"\n";
}

template<typename T>
inline void List<T>::swap(int n1, int n2)
{
    T temp = get(n1);
    set(get(n2), n1);
    set(temp, n2);
}

template<typename T>
void List<T>::sort()
{
    ListElem<T> *wrk1;
    T temp;
    int num;
    wrk1 = head;
    int i, j;
    for(i = 0; i<size-1; ++i)
    {
        temp = get(i);
        num = i;
        for (j = i; j<size; j++)
        {
            if (temp>get(j))
            {
                temp = get(j);
                num = j;
            }
        }
        if (num!=i)
            swap(i, num);
    }
}

template<typename T>
List<T> List<T>::operator+(List<T> &obj)
{
    for(int i = 0; i<obj.size; ++i)
        this->push_end(obj.get(i));
    return *this;
}

template<typename T>
List<T> List<T>::operator =(List<T> &obj)
{
    clear();
    List<T> *wrk = new List<T>(obj);
    this->head = wrk->head;
    this->tail = wrk->tail;
    this->size = wrk->size;
    return *this;
}
}

#endif // LIST_HPP
