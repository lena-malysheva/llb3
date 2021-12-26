#ifndef TSTACK_H
#define TSTACK_H
#define STACK_SIZE (1000)
#include <vector>

template <class T>
class TStack
{protected:
  int Head;
  int Size;
  T* s;
  void Overcrowded();     
 public:
  TStack();
  ~TStack();
  void Push(T i); 
  T Pop();        
  T Top();        
  bool Empty();           
  int Count();           
  void Clear();          
};
   
template <class T>
TStack<T>::TStack()
{ Head = 0;
  Size = STACK_SIZE;
  s = new T[Size];
}

template <class T>
TStack<T>::~TStack()
{
    delete[] s;
}

template <class T> 
void TStack<T>::Push(T i)
{ Overcrowded();
  s[Head] = i; 
  Head++;
}

template <class T> 
T TStack<T>::Pop()
{ if (!Empty())
  { Head--; return s[Head];}
  else { throw 1; }
}

template <class T>
T TStack<T>::Top()
{ if (!Empty()) { return s[Head - 1]; }
  else { throw 1; }
}

template <class T> 
bool TStack<T>::Empty()
{ if (Head == 0) { return 1; }
  else { return 0; }
}

template <class T> 
int TStack<T>::Count()
{ return Head;}

template <class T> 
void TStack<T>::Clear()
{ Head = 0;}

template <class T> 
void TStack<T>::Overcrowded()
{ if (Head == Size)
  { T* s1;
    s1 = s;
    Size = Size * 2;
    s= new T[Size];
    for (int i = 0; i < Size / 2; i++)
    { s[i] = s1[i];}
  }
}
#endif