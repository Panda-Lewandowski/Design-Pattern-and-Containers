#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "Errors.h"
#include <iostream>
using std::istream;
using std::ostream;
class ArrayBase {
public:
    ArrayBase () { }
    virtual ~ArrayBase () { }

    int getsize() const {
        return _size;
    }


protected:
    int _size;
    static const int DefaultSize = 20;
};


template <typename T>
class ArrayT : public ArrayBase {
public:

    //  онструкторы
    ArrayT ( int n = DefaultSize );
    ArrayT ( const T*, int sz );
    ArrayT ( const ArrayT<T>& );

    // ƒеструктор
    ~ArrayT ( );

    //  опирование массива
    ArrayT<T>& operator= ( const ArrayT<T>& );

    // ѕерегрузка операторов сравнени€
    bool operator == ( const ArrayT<T>& ) const;
    bool operator != ( const ArrayT<T>& ) const;
static	bool is_equal ( const ArrayT<T>&, const ArrayT<T>& );

    // ќбъединение массивов
static	ArrayT<T>& concat( const ArrayT<T>&, const ArrayT<T>&);

    // ”меньшение длины массива
static	ArrayT<T>& split_array ( const ArrayT<T>&, int pos, int num );

    // ѕрибавление одного и того же числа ко всем элементам массива
    ArrayT<T>& operator += ( const T& );
    ArrayT<T>& add_value ( const T& );
    ArrayT<T>& operator -= ( const T& );
    ArrayT<T>& subst_value ( const T& );

    // ”множение всех элементов массива на одно и то же число
    ArrayT<T>& operator *= ( const T& );
    ArrayT<T>& operator /= ( const T& );
    ArrayT<T>& mult_value ( const T& );
    ArrayT<T>& div_value ( const T& );

    // —ложение массивов
    ArrayT<T>& operator += ( const ArrayT<T>& );
    ArrayT<T>& add_array ( const ArrayT<T>& );

    // ¬ычитание массивов
    ArrayT<T>& operator -= ( const ArrayT<T>& );
    ArrayT<T>& subst_array ( const ArrayT<T>& );

    // —ортировка массива
    void QuickSortArr (  );
    void QuickSortArr ( int st, int en );

    // ѕерегрузка оператора []
    T& operator [] ( int n ) {
        if (n<_size)
            return _arr[n];
        else
            throw RangeError(1);
    };
    const T& operator [] ( int n ) const {
        if (n<_size)
            return _arr[n];
        else
            throw RangeError(1);
    };

    // ѕоиск элементов в массиве
    T arr_min( int& );
    T arr_max( int& );
    int FindEl( T );


    // ќбмен
    void arr_swap( int, int );


    // ѕерегрузка потоков ввода-вывода
    template <typename V>
    friend istream& operator >> ( istream&, ArrayT<V>& );
    template <typename V>
    friend ostream& operator << ( ostream&, ArrayT<V>& );


private:
    T* _arr;
    void arr_resize( int );
};
template <typename T>
istream& operator >> ( istream&, ArrayT<T>& );
template <typename T>
ostream& operator << ( ostream&, ArrayT<T>& );


#endif // VECTOR_HPP
