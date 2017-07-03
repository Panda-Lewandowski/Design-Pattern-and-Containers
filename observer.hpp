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
    void f(Object^ source, double a) //подписали метод f на возникновение события. Когда начнёт выполняться method, будут выполняться методы классов, подписанных на возникновение события
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


class lift
{
    int floor;  // текущий этаж
    doors* door;
public:
    lift(); //конструктор лифта

public slots:
    void go_up();  //топать вверх
    void go_down(); //топать вниз
    void open_doors();  //открыть двери
    void close_doors(); //закрыть двери
    void wait_here();   //ждать столько то секунд

signals:
    void opening_doors();
    void closing_doors();
    void arrived();  //приехал
    void up(); //едет вверх
    void down();  //едет вниз
};


class doors
{
public:
    doors(); //конструктор дверей

public slots:
  void open();    //открыть
  void close();   //закрыть
  void start_open();    //начать открывать
  void start_close();   //начать закрывать

signals:
  void opening();     //двери открыты
  void closing();    //двери закрыты

};

doors::doors()
{
    connect(this, SIGNAL(opening()), this, SLOT(start_open()));
    connect(this, SIGNAL(closing()), this, SLOT(start_close()));

}


lift::lift()
{
    this->floor = 1;
    this->door = new doors;
    connect(this, SIGNAL(arrived()), this->door, SLOT(open()));
    connect(this, SIGNAL(opening_doors()), this, SLOT(open_doors()));
    connect(this, SIGNAL(closing_doors()), this, SLOT(close_doors()));
    connect(this, SIGNAL(up()), this, SLOT(go_up()));
    connect(this, SIGNAL(down()), this, SLOT(go_down()));
    connect(this, SIGNAL(up()), this->door, SLOT(close()));
    connect(this, SIGNAL(down()), this->door, SLOT(close()));

}

void lift::open_doors()
{
    emit this->door->opening();
}


void lift::close_doors()
{
    emit this->door->closing();
}
