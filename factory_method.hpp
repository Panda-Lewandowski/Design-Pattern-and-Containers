#ifndef FACTORY_METHOD_HPP
#define FACTORY_METHOD_HPP
#include <string>
#include <iostream>

using namespace std;

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
  Product* GetProduct();
protected:
  virtual Product* CreateProduct() = 0;
private:
  Product* prod = nullptr;
};

template <typename tprod>
class ConcreteCreator : public Creator
{
protected:
  virtual Product* CreateProduct()
  {
    return new tprod;
  }

};

Product* Creator::GetProduct()
{
  if(prod == nullptr)
    prod = CreateProduct();

  return prod;
}
#endif // FACTORY_METHOD_HPP
