#ifndef CHAIN_OF_RESPONSIBILITY_HPP
#define CHAIN_OF_RESPONSIBILITY_HPP
#include <iostream>
/**
* Вспомогательный класс, описывающий некоторое преступление */
class CriminalAction {
    friend class Policeman;
    int complexity;
    const char* description;
public:
// Полицейские имеют доступ к материалам следствия // Сложность дела
// Краткое описание преступления
    CriminalAction(int complexity, const char* description): complexity(complexity), description(description) {}
};


/**
* Абстрактный полицейский, который может заниматься расследованием преступлений */
class Policeman {
protected:
    int deduction; // дедукция (умение распутывать сложные дела) у данного полицейского
    Policeman* next; // более умелый полицейский, который получит дело, если для текущего оно слишком сложное
    virtual void investigateConcrete(const char* description) {} // собственно расследование
public:
    Policeman(int deduction): deduction(deduction) {}
    virtual ~Policeman() { if (next) { delete next; }}
    /*
    * Добавляет в цепочку ответственности более опытного полицейского, который сможет
    принять на себя
     * расследование, если текущий не справится
     */
    Policeman* setNext(Policeman* policeman) {
                 next = policeman;
            return next;
    }

    /*
    * Полицейский начинает расследование или, если дело слишком сложное, передает ее
    более опытному коллеге */
    void investigate(CriminalAction* criminalAction)
    {
        if (deduction < criminalAction->complexity)
        {
            if (next)
            {
                next->investigate(criminalAction);
            }
            else
            {
                std::cout << "Это дело не раскрыть никому." << std::endl;
            }
        }
        else
        {
            investigateConcrete(criminalAction->description);
        }
    }
};


class MartinRiggs: public Policeman {
protected:
    void investigateConcrete(const char* description) {
        std::cout << "Расследование по делу \""   << description << "\" ведет сержант Мартин Риггс"<< std::endl;
    }
public:
    MartinRiggs(int deduction): Policeman(deduction) {}

};

class JohnMcClane: public Policeman {
protected:
    void investigateConcrete(const char* description) {
            std::cout << "Расследование по делу \"" << description << "\" ведет детектив Джон Макклейн" << std::endl;
    }
public:
    JohnMcClane(int deduction): Policeman(deduction) {}
};

class VincentHanna: public Policeman {
protected:
    void investigateConcrete(const char* description) {
        std::cout << "Расследование по делу \""  << description << "\" ведет лейтенант Винсент Ханна" << std::endl;
    }
public:
    VincentHanna(int deduction): Policeman(deduction) {}
};


#endif // CHAIN_OF_RESPONSIBILITY_HPP
