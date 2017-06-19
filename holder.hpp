#ifndef HOLDER_HPP
#define HOLDER_HPP
using namespace std;

template <typename T>
class Holder;

template <typename T>
class Trule //TRansfer capsULE //используется только для передачи; чтобы при передачи в метод функции или возврата функции из метода, не возникло утечки
{
private:
    T* ptr;
public:
    Trule(Holder<T>&h)
    {
        ptr = h.release();
    }
    ~Trule() //при передаче параметров также возможна отработка исключений; необходимо позаботиться об уничтожении труля
    {
        delete ptr;
    }
private:
    Trule(Trule<T>&);
    Trule<T>& operator = (Trule<T>&);
    friend class Holder<T>; //для простоты обращения
};

template <typename T>
class Holder
{
private:
    T* ptr;
public:
    Holder(): ptr(0) {} //когда создаётся холдер указателя, он не должен принимать указатель откуда-то извне - это может привести к тому, что холдер может держать указатель на уже освобождённую память
    explicit Holder(T* p): ptr(p) {} //нужен явный вызов конструктора, явное создание объекта
    ~Holder()
    {
        delete ptr;
    }
    //холдер должен быть прозрачен: черзе него мы должны мочь обратиться ко всему что он держит
    T* operator ->() const
    {return ptr;}

    //также нужна и работа со ссылкой на объект
    T& opetator *() const {return *ptr;}

    //обмен
    void exchange(Holder<T>& h)
    {
        swap(ptr, h.ptr); }

    }
    //холдер берёт на себя указатель капсулы
    Holder(Trule<T> const& t)
    {
        ptr = t.ptr;
        //т.птр - константа, поэтому приходится извращаться
        const_cast<Trule<T>&>(t).ptr = 0;
    }

    //присваивание
    Holder<T>& operator = (Trule<T> const& t)
    {
        delete ptr;
        ptr = t.ptr;
        const_cast<Trule<T>&>(t).ptr = 0;
        return *this;
    }
    T* release()
    {
        T* p = ptr;
        ptr = 0;
        return p;
    }
    //также нужны ещё конструктор копирования и оператор присванивания(холдер холдер)
    //при передаче объектов в функцию мы будем использовать трул
};

#endif // HOLDER_HPP
