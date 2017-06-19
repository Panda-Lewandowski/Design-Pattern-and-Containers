#ifndef ITERATOR_HPP
#define ITERATOR_HPP
struct Node
{
  Type Info;
  node* next;
};

struct list
{
  node* first, *last;
  node *current; //->
};

struct Iterator
{
  node* current;
};
#endif // ITERATOR_HPP
