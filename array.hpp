#ifndef ARRAY_HPP
#define ARRAY_HPP
class BaseArray
{
    public:
        BaseArray(){}
        virtual ~BaseArray(){}
};

template <typename T>
class Array: public BaseArray
{
    private:
        int capacity;
        int length;
        T** array;

    public:
        Array();
        Array(int);
        Array(const Array<T> &);
        ~Array();

        void Show() const;
        int Length() const;
        int Search(const T&) const;
        void Add(const T&);
        void Del(int);
        T& operator [] (int) const;
        T** Resize(int);
};
template <typename T>
Array<T>::Array()
{
    if( (array = (T**)calloc(FIRST_SIZE, sizeof(T*))) == NULL )
        throw MemoryError(0);

    capacity = FIRST_SIZE;
    length = 0;
}

//-------------------------------------------------------------
template <typename T>
Array<T>::Array(int size)
{
    if( (array = (T**)calloc(size, sizeof(T*))) == NULL )
        throw MemoryError(0);

    capacity = size;
    length = 0;
}

//-------------------------------------------------------------

template <typename T>
Array<T>::Array(const Array<T>& elem_arr)
{
    if( (array = (T**)calloc(elem_arr.capacity, sizeof(T*))) == NULL )
        throw MemoryError(0);

    length = elem_arr.Length();
    capacity = elem_arr.capacity;

    for(int i = 0; i < length; i++)
        array[i] = new T(elem_arr[i]);
}

//-------------------------------------------------------------

template <typename T>
Array<T>::~Array()
{
    for (int i = 0; i < length; i++)
        free(array[i]);
    free(array);
}

//-------------------------------------------------------------

template <typename T>
void Array<T>::Show() const
{
    for(int i = 0; i < length; i++)
    {
        cout << *array[i] << "  ";
    }
    cout << endl;
}

//-------------------------------------------------------------

template <typename T>
int Array<T>::Length() const
{
    return length;
}

//-------------------------------------------------------------

template <typename T>
T** Array<T>::Resize(int size)
{
    if( (array = (T**)realloc(array, sizeof(T*)*size)) == NULL )
        throw MemoryError(0);
    capacity = size;

    return array;
}

//-------------------------------------------------------------

template <typename T>
void Array<T>::Add(const T& elem)
{
    if (length == capacity)
        array = Resize(capacity + ADD_MEM);

    array[length++] = new T(elem);
}

//-------------------------------------------------------------

template <typename T>
int Array<T>::Search(const T& elem) const
{
    int i;
    for (i = 0; i < length && *array[i] != elem; i++);

    return i < length ? i : NO_RESULTS;
}

//-------------------------------------------------------------

template <typename T>
void Array<T>::Del(int Pos)
{
    if(Pos < 0 || Pos >= length)
        throw RangeError(Pos);

    length--;
    T temp = array[Pos];

    array[Pos] = array[length];
    delete temp;
}

//-------------------------------------------------------------

template <typename T>
T& Array<T>::operator [] (int Pos) const
{
    if(Pos < 0 || Pos >= length)
        throw RangeError(Pos);

    return *array[Pos];
}

#endif // ARRAY_HPP
