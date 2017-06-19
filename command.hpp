#ifndef COMMAND_HPP
#define COMMAND_HPP
class Command //базовый класс команды
{
public:
    virtual bool execute() = 0;
protected:
  Command() {}
};

template<typename Reciever>
class SimpleCommand: public Command
{
private:
    typedef bool (Reciever::*Action)();
    Reciever* rec; //указатель на объект
    Action act; //указатель на метод

public:
    SimpleCommand(Reciever* r, Action a); //конструктор
    bool execute() //экзекутор
    {
        return (rec->*act)();
    }
};
#endif // COMMAND_HPP
