#ifndef FLYWEIGHT_HPP
#define FLYWEIGHT_HPP

//работа с символами
#include <map>
//базовый класс:
class Character
{
protected:
    char Symbol;
    int Size;
public:
    virtual void view() = 0; //если 0 не написать, то метод нужно будет реализовать хотя бы где-нибудь
};

class CharacterFactory
{
private:
    std::map<char,Character*> Characters; //связка ключ_символ - значение_ОбъектСимвола
    int size;
public:
    Character& GetCharacter(char key)
    {
        /*std::map<char,Character*>::iterator*/Characters::iterator it = Characters.find(key);
        if (Characters.end() == it)
        {
            Character* ch = new ConCharacter(key,size);
            Characters[key] = ch;
            return *ch;
        }
        else
        {
            return *it->second; //приспособленец или возвращает новый объект, или указатель на существующий
        }
    }
};


#endif // FLYWEIGHT_HPP
