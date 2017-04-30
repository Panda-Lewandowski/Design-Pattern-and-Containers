#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

class Meal {
public:
    virtual ~Meal();
    virtual void eat() = 0;
    virtual Meal *clone() const = 0;
    // ...
};

class Spaghetti : public Meal {
public:
    Spaghetti( const Spaghetti & );
    void eat();
    Spaghetti *clone() const { return new Spaghetti( *this ); }
    //...
};

#endif // PROTOTYPE_HPP
