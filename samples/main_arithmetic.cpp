// реализация пользовательского приложения
#include <iostream>
#include <string>
#include "../include/arithmetic.h"
#include "../include/stack.h"
using namespace std;

void menu()
{
 cout << "1. калькулятор" << endl;
 cout << "0. выход" << endl;
}

int main()
{
  int m = 1;

  setlocale(LC_ALL, "Russian");
  while (m == 1)
  {
    Tlexeme A;
    switch (m)
  {
  case 1:{
    cin >> A;
    if (A.Check_correct())
    cout << A.Calculation();
  break;}
  
  default:
    break;
  }
  }
  return 0;
}
