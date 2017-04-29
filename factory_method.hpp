#ifndef FACTORY_METHOD_HPP
#define FACTORY_METHOD_HPP

#include <string>
#include <iostream>

class Product {
public:
    virtual string getName() = 0;
    virtual ~Product() {}
};

class ConcreteProductA: public Product {
public:
    string getName() {return "ConcreteProductA";}
};

class ConcreteProductB: public Product {
public:
    string getName() {return "ConcreteProductB";}
};

class Creator {
public:
    virtual Product* factoryMethod() = 0;
};

class ConcreteCreatorA: public Creator {
public:
    Product* factoryMethod() {return new ConcreteProductA();}
};

class ConcreteCreatorB: public Creator {
public:
    Product* factoryMethod() {return new ConcreteProductB();}
};

#endif // FACTORY_METHOD_HPP
