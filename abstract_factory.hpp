#ifndef ABSTRACT_FACTORY_HPP
#define ABSTRACT_FACTORY_HPP
#include <iostream>
#include <vector>

using namespace std;

// Абстрактные базовые классы графических примитивов
class Ellipse
{
public:
    virtual void info() = 0;
    virtual ~Ellipse() {}
};

class Line
{
public:
    virtual void info() = 0;
    virtual ~Line() {}
};

class Polygon
{
public:
    virtual void info() = 0;
    virtual ~Polygon() {}
};

// Классы граф. примитивов для двух разных библиотек
class EllipseA: public Ellipse
{
public:
    void info() {
        cout << "Ellipse from lib A" << endl;
    }
};

class LineA: public Line {
public:
    void info() {
        cout << "Line from lib A" << endl;
    }
};

class PolygonA: public Polygon {
public:
    void info() {
        cout << "Polygon from lib A" << endl;
    }
};

class EllipseB: public Ellipse
{
public:
    void info() {
        cout << "Ellipse from lib B" << endl;
    }
};

class LineB: public Line {
public:
    void info() {
        cout << "Line from lib B" << endl;
    }
};

class PolygonB: public Polygon {
public:
    void info() {
        cout << "Polygon from lib B" << endl;
    }
};


// Абстрактная фабрика для производства примитивов
class GrafFactory
{
public:
    virtual Ellipse* createEllipse() = 0;
    virtual Line* createLine() = 0;
    virtual Polygon* createPolygon() = 0;
    virtual ~GrafFactory() {}
};

// Фабрика для создания воинов Римской армии
class GrafAFactory: public GrafFactory
{
public:
    Ellipse* createEllipse() {return new EllipseA; }
    Line* createLine() {return new LineA;  }
    Polygon* createPolygon() {return new PolygonA; }
};

// Фабрика для создания воинов армии Карфагена
class GrafBFactory: public GrafFactory
{
public:
    Ellipse* createEllipse() {return new EllipseB; }
    Line* createLine() {return new LineB;  }
    Polygon* createPolygon() {return new PolygonB; }
};

// Класс, содержащий всех воинов той или иной армии
class Graf {
public:
    ~Graf() {
        size_t i;
        for(i=0; i<vi.size(); ++i) delete vi[i];
        for(i=0; i<va.size(); ++i) delete va[i];
        for(i=0; i<vh.size(); ++i) delete vh[i];
    }
    void info() {
        size_t i;
        for(i=0; i<vi.size(); ++i) vi[i]->info();
        for(i=0; i<va.size(); ++i) va[i]->info();
        for(i=0; i<vh.size(); ++i) vh[i]->info();
    }
    vector<Ellipse*> vi;
    vector<Line*> va;
    vector<Polygon*> vh;
};

// Здесь создается армия той или иной стороны
class Scene
{
public:
    Graf* createGraf( GrafFactory& factory ) {
        Graf* p = new Graf;
        p->vi.push_back( factory.createEllipse());
        p->va.push_back( factory.createLine());
        p->vh.push_back( factory.createPolygon());
        return p;
}
};

#endif // ABSTRACT_FACTORY_HPP
