#ifndef SET_TXT
#define SET_TXT

#include "Exceptions.h"
#include "SetIterator.h"
#include <iostream>

namespace myset
{

class BasicSet
{
public:
        bool isEmpty() const {return len==0;}
        int cardinality() const {return len;}
        BasicSet(int n = 0) : len(n) {}
        //virtual ~BasicSet();
protected:
        int len;
};

template<class T>
class Set: public BasicSet
{
public:
        Set();
        Set(int n);
        Set(T *start, T *finish);
        Set(Set<T> const& ob2);
        ~Set();

        Set<T>& operator=(Set<T> const& ob2);
        void clear();

        // функци€ сравнени€ элементов типа “
        typedef bool (*FnCmp)(T const &element1, T const &element2);
        FnCmp compare;

        // —равнение множеств
        bool operator ==(Set<T> const& ob2);
        bool operator !=(Set<T> const& ob2);

        // ѕринадлежность множеству
        bool has(T const &element);
        bool operator >(T const &element);

        // ƒобавить элемент
        Set<T>& operator +=(T const &element);
        Set<T> operator +(T const &element) const;
        void addToSet(T const &element);

        // ”далить элемент
        Set<T>& operator -=(T const &element);
        Set<T> operator -(T const &element) const;
        void removeFromSet(T const &element);

        // ќбъединение
        Set<T>& operator +=(Set<T> const& ob2);
        Set<T> operator +(Set<T> const& ob2) const;

        // ѕересечение
        Set<T>& operator *=(Set<T> const& ob2);
        Set<T> operator *(Set<T> const& ob2) const;

        // –азность
        Set<T>& operator -=(Set<T> const& ob2);
        Set<T> operator -(Set<T> const& ob2) const;

        // —имметрическа€ разность
        Set<T>& operator %=(Set<T> const& ob2);
        Set<T> operator %(Set<T> const& ob2) const;

        // »тераторы
        typedef myset::SetIterator<T> iterator;
        iterator begin() {T *temp = elements; return temp;}
        iterator end() {T *temp = elements; return temp+len-1;}
private:
        static const int sizeOfSegment=50;
        T *elements;
        int find(T element) const;
        void checkMemory();
        void constructor(int n);
};

template<class T>
Set<T> unionOfSets(Set<T> const& ob1, Set<T> const& ob2)
{
        return ob1+ob2;
}

template<class T>
Set<T> intersectionOfSets(Set<T> const& ob1, Set<T> const& ob2)
{
        return ob1*ob2;
}

template<class T>
Set<T> differenceOfSets(Set<T> const& ob1, Set<T> const& ob2)
{
        return ob1-ob2;
}

template<class T>
Set<T> symmetricDifferenceOfSets(Set<T> const& ob1, Set<T> const& ob2)
{
        return ob1 % ob2;
}

template<typename T>
istream& operator>> (istream &in, Set<T> &ob)
{
        T temp;

        if (in)
        {
                in>>temp;
                ob += temp;
        }
        return in;
}

template<typename T>
ostream& operator<< (ostream &out, Set<T> &ob)
{
        for(Set<T>::iterator it = ob.begin(); it!= ob.end(); ++it)
                out<<it<<' ';
        out<<endl;
        return out;
}

template<typename T>
bool defaultFnCompare(T const &element1, T const &element2)
{
        return element1 == element2;
}

#endif // SET_TXT
