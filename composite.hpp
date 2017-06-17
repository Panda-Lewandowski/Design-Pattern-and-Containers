#ifndef COMPOSITE_CPP
#define COMPOSITE_CPP

class Unit { // component
    public:
    virtual int getStrength() = 0;
    virtual void addUnit(Unit* p) {}
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
    int getStrength()
    {
        int total = 0;
        for (int i = 0; i < c.size(); ++i)
            total += c[i]->getStrength();
        return total;
    }
    void addUnit(Unit* p) {c.push_back(p);}
    ~CompositeUnit()
    {
        for(int i = 0; i< c.size(); ++i)
        delete c[i];

    }
private:
    std::vector<Unit*> c;
};


CompositeUnit* createLegion() {
    CompositeUnit* legion = new CompositeUnit;
    for (int i = 0; i < 3000; ++i)
        legion->addUnit(new Infantryman);
    for (int i = 0; i < 1200; ++i)
        ыlegion->addUnit(new Archer); return legion;
}

#endif // COMPOSITE_CPP
