#ifndef COMPOSITE_CPP
#define COMPOSITE_CPP

class Unit { // component
    public:
    //virtual int getStrength() = 0;  
    virtual int getSila() { throw UnsupportedOperation(); }
    virtual void addUnit(Unit* p) { throw UnsupportedOperation(); }
    virtual void removeUnit(Unit* p) { throw UnsupportedOperation(); }
    virtual Iterator createIterator() { throw UnsupportedOperation(); }
    virtual ~Unit() {}
};

class Archer: public Unit {
    // leaf
public:
    virtual int getStrength() {return 1;}
};

class Infantryman: public Unit { // leaf
public:
    virtual int getStrength() {return 2;}
};

class CompositeUnit: public Unit { // composite
public:
    int getStrength() // mojno ostavit, no lushe viesti etot podschet v otdelinyu klass ili funkciuy
    {
        int total = 0;
        for (int i = 0; i < c.size(); ++i)
            total += c[i]->getStrength();
        return total;
    }
    
    void addUnit(Unit* p) {c.push_back(p);}
    
    void removeUnit(Unit* p) {TipaUdalenie(p);}
    
    virtual Iterator createIterator() { return c.iterator_begin(); }  // xz kak tam pravilno
     
    ~CompositeUnit()
    {
        //for(int i = 0; i< c.size(); ++i)
        //delete c[i];
        vector sam 4istit vse objekti - problemi s pamyatiu

    }
private:
    std::vector<Unit*> c;
};


CompositeUnit* createLegion() {
    CompositeUnit* legion = new CompositeUnit;
    for (int i = 0; i < 3000; ++i)
        legion->addUnit(new Infantryman);
    for (int i = 0; i < 1200; ++i)
        legion->addUnit(new Archer); return legion;
}

#endif // COMPOSITE_CPP
