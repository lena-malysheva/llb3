#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include <iostream>
#include <string>
using namespace std;

class Tlexeme 
{protected:
  int Size;
  string* mLexeme; 
  int* priority;   
  int Flag = -1;  
 public:
  Tlexeme(string a="0");
  ~Tlexeme();
  
  void Fill(string a); 
  int Check_correct(); 
  string Pol(); 
  double Calculation(int x=0); 
  
  friend istream& operator>>(istream& in, Tlexeme& l)
  { in >> l.mLexeme[0];
	string a = l.mLexeme[0];
	l.Size = (l.mLexeme[0]).length();
	l.mLexeme = new string[l.Size];
	l.priority = new int[l.Size];
	l. mLexeme[0] = a;
	return in;
   }
  friend ostream& operator<<(ostream& out, const Tlexeme& l)
  { for (int i = 0; i < l.Size; i++)
	{ out << l.mLexeme[i] << ' ';}
	cout << endl;
	return out;
   }
 private:
  void Divide(); 
  void Pol_1(); 
  int Check_brack();
  int Check_sign(); 
  int Check_point(); 
  int Check_variable();
  int Check_function();
};

#endif