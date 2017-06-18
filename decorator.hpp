#ifndef DECORATOR_HPP
#define DECORATOR_HPP
#include <iostream>
using namespace std;
class Widget // component
{
public:
    Widget();
    virtual void draw();

};

class TextField: public Widget // conComponent
{
    int width, height;
public:
    TextField(int w, int h) {
        width = w;
        height = h;
    }
    void draw() { cout << "TextField: " << width << ", " << height << 'n'; }

};

class Decorator: public Widget // Decorator
{
    Widget *wid;
public:
    Decorator(Widget *w) {wid = w;}
    void draw() {wid->draw();}
};

class BorderDecorator: public Decorator // Decorator A
{
public:
    BorderDecorator(Widget *w): Decorator(w) {}
    void draw() {Decorator::draw();cout << "BorderDecorator" << 'n';}

};


//Widget *aWidget = new BorderDecorator( new BorderDecorator( (new TextField(80, 24))));
//aWidget->draw();
#endif // DECORATOR_HPP
