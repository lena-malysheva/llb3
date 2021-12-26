#include "../include/arithmetic.h"
#include "../include/stack.h"
#include <cmath>
#include <cstdlib>

int PR(string a)
{  if(a=="(") {return(0);}
   if(a=="+") {return(1);}
   if(a=="-") {return(1);}
   if(a=="*") {return(2);}
   if(a=="/") {return(2);}
   if(a=="^") {return(3);}
}

double Convert(string a)
{  string::size_type sz = 0;  
   string a1 = a;
   double res = stoll (a1, &sz, 0);
   a1 = a1.substr(sz);
   if (!a1.empty())
   { a1 = a1.substr(1);
     res = res + (stoll(a1, NULL)) / (pow(10, a1.length()));
   }
   return res;
}
   
Tlexeme::Tlexeme(string a)
{ Size = a.length();
  mLexeme = new string[Size];
  priority = new int[Size];
  TStack <char> S1;
  for (int i = 0; i < Size; i++)
  { mLexeme[i] = ' ';	
    priority[i] = -1;
  }
  mLexeme[0] = a;
}

Tlexeme::~Tlexeme()
{ delete[] mLexeme;
  delete[] priority;
}

void Tlexeme::Fill(string a)
{ Size = a.length();
  mLexeme = new string[Size];
  priority = new int[Size];
  TStack <char> S1;
  for (int i = 0; i < Size; i++)
  { mLexeme[i] = ' ';
    priority[i] = -1;
  }
  mLexeme[0] = a;
  Flag = -1;
}

void Tlexeme::Divide()
{ string a = mLexeme[0];
  int j=0;
  string S1="";
  string* mLexeme1= new string[Size];
  int* priority1 = new int[Size];
  for (int i = 0; i < Size; i++)
    { 
      if((a[i]=='+')|| (a[i] == '*')|| (a[i] == '/')|| (a[i] == '^'))
      { if(S1 != ""){ mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = "";}
        mLexeme1[j] = a[i]; 
	    priority1[j] = 1; j++;}
      else 
      { if(a[i] == '-')
        { if((i==0)||(((priority1[j-1]==4)||(priority1[j-1]==1)))&&(S1 == "")){ S1=S1+'-';}
          else { if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = ""; }
                 mLexeme1[j] = a[i];
                 priority1[j] = 1; j++;}}
        else 
        { if((a[i]=='(')||(a[i] == ')'))
          { if(S1 != ""){ mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = "";}
            mLexeme1[j] = a[i]; 
	        priority1[j] = 4; j++;}
          else 
          { if((a[i]=='s')&&(a[i+1]=='i')&&(a[i+2]=='n'))
          { if(S1 != ""){ mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = "";}
            mLexeme1[j] = "sin"; i = i + 2;
	        priority1[j] = 5; j++;}
            else 
            { if(((a[i]>='A')&&(a[i]<='Z'))||((a[i] >= 'a') && (a[i] <= 'z')))
              { if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = ""; }
                mLexeme1[j] = a[i];
                priority1[j] = 3; j++;}
              else 
              { if(((a[i] >= '0') && (a[i] <= '9'))||(a[i]=='.'))
                {S1=S1+a[i];}
              else { Flag = 0; } 
              }
            }
          }
        }
      }
    }
  if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; S1 = ""; j++; }
  Size=j;
  mLexeme = new string[Size];
  priority = new int[Size];
  for (int i = 0; i < Size; i++)
  { mLexeme[i] = mLexeme1[i]; 
    priority[i] = priority1[i];
  }
  if(Flag==-1){Flag=1;}
}
int Tlexeme::Check_correct()
{  if(Flag==2){return 1;}
   if(Flag==-1){Divide();}
   if (Flag == 0) { cout << "\tInput error: incorrect character is entered" <<  endl;}
   int a = -1;
   a = Check_brack(); 
   if (a != -1) {Flag = 0; }
   a = Check_sign();
   if (a != -1) {Flag = 0;}
   a = Check_point();
   if (a != -1) {Flag = 0; }
   a = Check_variable();
   if (a != -1) {Flag = 0; }
   a = Check_function();
   if (a != -1) {Flag = 0;}
  return  Flag;
}

int Tlexeme::Check_brack()
{ 
  int a = -1, i = 0;
  while ((i < Size) && (a == -1))
  { if ((mLexeme[i]=="(")&&(mLexeme[i+1]!="(")&&(mLexeme[i+ 2]=="(")) { a = i; } 
    if ((mLexeme[i] == ")") && (mLexeme[i + 1] != ")") && (mLexeme[i + 2] == ")")) { a = i; }
    i++;}
  if (a == -1)
  { TStack <int> S1; i=0;
    while ((i < Size) && (a == -1))
    { if(priority[i]==4)
      { if(mLexeme[i]=="("){ S1.Push(1); }
        else 
        { if(S1.Empty()){a=i;}
          else {S1.Pop();}
        } 
      } i++;
    }
    if(!(S1.Empty())){a=11;} 
  }
  
  return a;
}
int Tlexeme::Check_sign() 
{ int a=-1, i = 1;
  if (priority[0] == 1){a =0; } 
  while ((i<Size)&&(a==-1))
  { if(priority[i]== 1)
    { if((priority[i+1] == 1)||(mLexeme[i-1]=="(")||(mLexeme[i + 1] == ")")) { a = i; }
    } 
    i++;
  }
  if (mLexeme[0] == "-") { a = 0;}
  return a;
}
int Tlexeme::Check_point()
{ int a=-1, i = 0;
  while ((i<Size)&&(a==-1))
  { if(priority[i]== 2) 
    { string f = mLexeme[i];
      int k = count(f.begin(), f.end(), '.');
      if (k > 1) {  a = i; }
    } i++;}
  return a;
}
int Tlexeme::Check_variable()
{ int a=-1, i = 0;
  while ((i<Size)&&(a==-1))
  { if((priority[i]== 3)&&(priority[i+1] == 3)){ a = i; } 
    i++;}
  return a;
}
int Tlexeme::Check_function()
{ int a=-1, i = 0;
  while ((i<Size)&&(a==-1))
  { if((priority[i]== 5)&&(priority[i+1] == 1)){ a = i; } 
    if((priority[i]== 5)&&(priority[i-1] == 3)){ a = i; } 
    if ((priority[i] == 5) && (priority[i - 1] == 2)) { a = i; }
    if ((priority[i] == 5) && (i == Size-1)) { a = i; }
    i++;}
  return a;
}
void Tlexeme::Pol_1()
{ if (!Check_correct()) { throw 1; } else{
  if(Flag!=2)
  { int Nbrack=0;
    for (int i = 0; i < Size; i++)
  { if (priority[i] == 4) { Nbrack++; };
    if (priority[i] == 5) { priority[i] = 1; };   
  }
    string* mLexeme1; mLexeme1 = mLexeme; mLexeme = new string[Size- Nbrack];
    int* priority1; priority1 = priority; priority = new int[Size- Nbrack];
    TStack <int> S1;
    int j=0;
    for (int i = 0; i < Size; i++)
    {
      if ((priority1[i]==2)||(priority1[i] == 3))
      { mLexeme[j] = mLexeme1[i]; 
        priority[j] = priority1[i]; 
        j++;}
     else
      { if (priority1[i]==1)
        { if (S1.Empty()) { S1.Push(i); } 
          else
          { int pr1 = PR(mLexeme1[i]), pr2= PR(mLexeme1[S1.Top()]);
            if (pr1>pr2) { S1.Push(i); }
            else
            { while ((pr1<=pr2)&&(!S1.Empty()))
              { int q=S1.Pop();  
                mLexeme[j] = mLexeme1[q]; 
                priority[j] = priority1[q];
                j++;
                if(!S1.Empty()){ pr2= PR(mLexeme1[S1.Top()]);}
              } S1.Push(i);
            }
          }
        } 
        else 
        { if (mLexeme1[i] == "(") { S1.Push(i); }
          else
          { if (mLexeme1[i] == ")")
            { int w = 0; 
              while ((!S1.Empty()) && (w == 0))
              { int q = S1.Top();
                if (mLexeme1[q] == "(") { w = 1; }
                else
                { q = S1.Pop();
                  mLexeme[j] = mLexeme1[q];
                  priority[j] = priority1[q]; 
                  j++;
                 }
              } S1.Pop();
            }
          }
        }
      }
    }  
    while (!S1.Empty())
    { int q = S1.Pop(); mLexeme[j] = mLexeme1[q]; priority[j] = priority1[q]; j++;}
    Size = Size - Nbrack;  
    Flag = 2;
  }}
}
string Tlexeme::Pol()
{ Pol_1();
  if(Flag==2)
  { string a;
    for (int i = 0; i < Size; i++)
    { a= a +mLexeme[i]+" ";}
    return a;
  }
}
double Tlexeme::Calculation(int x)
{ if(Flag!=2){Pol_1(); }
  TStack <double> S1;
  int s = Size, j=0;
  double* M1 = new double[Size];;
  string* M2 = new string[Size];
  for (int i = 0; i < Size; i++)
  { if (priority[i]==2){ S1.Push(Convert(mLexeme[i])); }
    if (priority[i]==3)
    { int w=0,f=-1;
      while((w<j)&&(f==-1))
      { if (M2[j] == mLexeme[i]) { f = i; S1.Push(f);} w++;}
      if(f==-1)
      { double q;
        cout<<"\tEnter the value of the variable "<< mLexeme[i]<<":\n\t";
        if (x == 0) { cin >> q; }else{q=x;} S1.Push(q); M1[j] = q; M2[j] = mLexeme[i];
      }
    }
    if (priority[i]==1)
    { double x,y;
      x=S1.Pop();
      if(mLexeme[i]=="sin"){S1.Push(sin(x));}
      else
      { y=S1.Pop();
        if(mLexeme[i]=="+"){ S1.Push(x+y); }
        if(mLexeme[i]=="-"){ S1.Push(y-x); }
        if(mLexeme[i]=="*"){ S1.Push(x*y); }
        if(mLexeme[i]=="/"){ S1.Push(y/x); }
        if(mLexeme[i]=="^"){ S1.Push(pow(y,x)); }
      }
    }
  }
  delete[] M1;
  delete[] M2;
  return S1.Pop();
}