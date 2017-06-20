#ifndef OBSERVER_HPP
#define OBSERVER_HPP
delegate void EventHandler(Object^ source, double a);

public ref class Manager //издатель
{
public:
    event EventHandler^ OnHandler;
    void method()
    {
        OnHandler(this, 10.);
    }
}
public ref class Watcher //подписчик
{
public:
    Watcher(Manager^ m)
    {
        m->OnHandler += gcnew EventHandler(this, &Watcher::f) //& - потомучто метод класса
    }
    void f(Object^ source, double a) //подписали метод f на возникновение события. 
       ///Когда начнёт выполняться method, будут выполняться методы классов, подписанных на возникновение события
    {
    //...
    }
}
}
#endif // OBSERVER_HPP
/*
ref - память распределяется только динамически под объект
^ - замена * - ук-ль на управляемую кучу
+= - т.к. на 1 событие можно подписываться много раз
*/
