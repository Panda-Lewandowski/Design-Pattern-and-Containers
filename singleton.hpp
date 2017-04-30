#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T>
class singleton {
public:
    static T& instance() {
        if(!myInstance)
            myInstance = new T;
        return *myInstance;
    }

private:
    static T* myInstance;
    singleton (const singleton&){}
};

#endif // SINGLETON_HPP
