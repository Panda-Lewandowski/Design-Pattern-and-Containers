#ifndef SINGLETON_HPP
#define SINGLETON_HPP
template <typename T>
class Singleton
{
public:
  static T& instance()
  {
    if(myInstance == nullptr)
      myInstance = new T;
      return *myInstance;
  }
private:
  static T* myInstance;
  Singleton() = delete;
  Singleton(const Singleton<T>&) = delete;
};

template <typename T>
T* Singleton::myInstance = nullptr;

#endif // SINGLETON_HPP
