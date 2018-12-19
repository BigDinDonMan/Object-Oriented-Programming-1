#ifndef __RCSTRING_H__
#define __RCSTRING_H__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <ctype.h>
using namespace std;

/*
klasa ta działa na zasadzie zliczania odwołań, np. dwa stringi wskazują na ten sam obszar w pamięci, lecz dealokowany jest 
dopiero wraz z momentem wyzerowania licznika referencji
licznik referencji zwiększany jest w momencie przypisania
nowy string ma ustawiany licznik odniesień na 1 w momencie alokacji
funkcja detach zmniejsza licznik referencji do danego napisu o 1 i alokuje pamięć na jego kopię, tworząc nową instancję tego napisu, jeśli licznik jest równy 1 to zwraca na[os]
*/



class rcstring{
struct rctext;
rctext* data;
public:
    class Range{};
    class Cref;

    rcstring();
    rcstring(const char*);
    rcstring(const rcstring&);
    ~rcstring();

    rcstring& operator=(const char*);
    rcstring& operator=(const rcstring&);
    rcstring& operator+=(const rcstring &);
    rcstring operator+(const rcstring &) const;

    int Atoi() const;
    rcstring& toLower();
    rcstring Left(int n) const;

    friend ostream& operator<<(ostream&, const rcstring&);
    void check (unsigned int i) const;
    char read(unsigned int i) const;
    void write(unsigned int i, char c);
    char operator[](unsigned int i) const;
    Cref operator[](unsigned int i);
};

struct rcstring::rctext
{
    char* s;
    unsigned int size;
    unsigned int n;

  rctext(unsigned int nsize, const char* p)
  {
      n = 1;
      size = nsize;
      s = new char[size + 1];
      strncpy(s, p, size);
      s[size] = '\0';
  };
  ~rctext()
  {
    delete [] s;
  };
  rctext* detach()//funkcja "odpina" napis (służy do utworzenia własnej kopii napisu jeśli mamy zmodyfikować pierwotny)
  {
      if(n == 1)//jeśli n jest == 1 to po prostu zwracamy ten obiekt
        return this;
      rctext* t = new rctext(size, s);//tworzymy nowy rctext o długośći size i kopiujemy tam napis s
      n--;//zmniejszamy licznik referencji
      return t;//zwracamy obiekt typu rctext
  };
  void assign(unsigned int nsize, const char *p)
  {
    if(size != nsize) //jeśli size nie jest nsize, to alokujemy pamięć na nowy napis i kopiujemy tam napis p
    {
      char* ns = new char[nsize + 1];
      size = nsize;
      strncpy(ns, p, size);
      delete [] s;
      s = ns;
    }
    else
      strncpy(s, p, size);//w innym przypadku po prostu kopiujemy

    s[size] = '\0';
  }

private:
  rctext(const rctext&);
  rctext& operator=(const rctext&);
};

class rcstring::Cref //klasa Cref przechowuje "referencję" do znaku z obiektu rcstring spod indeksu i
{
  friend class rcstring;
  rcstring& s;//referencja do obiektu klasy rcstring
  int i;//index do rzutowania na char (zwraca wartość spod i)
  Cref (rcstring& ss, unsigned int ii): s(ss), i(ii) {};
public:
  operator char() const//operator służący do rzutowania Cref na char
  {
    cout << "operator char() const"<<endl;
    return s.read(i);//zwraca wartość spod indeksu i
  }
  rcstring::Cref& operator = (char c)
  {
    cout << "void operator = (char c)"<<endl;
    s.write(i,c);//wpisuje wartość c pod indeks i
    return *this;
  }
  rcstring::Cref& operator = (const Cref& ref)
  {
    return operator= ((char)ref);
  }
};
inline rcstring::rcstring()
  {
    data = new rctext(0,"");//bazowy tekst ("pusty string")
  }

inline rcstring::rcstring(const rcstring& x)//konstruktor kopiujący zwiększający ilość odniesień o 1
  {
    x.data->n++;//zwiększenie licznika odniesień
    data=x.data;//przypisanie wskaźnika
  }
inline rcstring::~rcstring()
{
  if(--data->n==0)//jeśli ilość odniesień jest równa 0 to zwalniamy pamięć
    delete data;
}

rcstring& rcstring::operator=(const rcstring & x)//operator przypisania
{
  x.data->n++;//zwiększamy ilość odniesień w obiekcie x
  if(--data->n == 0)//zmniejszamy ilość odniesień w obecnym obiekcie i zwalniamy jeśli jest równa 0
    delete data;
  data=x.data;//"przepinamy" wskaźnik
  return *this;
}

rcstring::rcstring(const char* s)
{
 data=new rctext(strlen(s),s);//kopiowanie napisu s o długości strlen(s)
}

rcstring& rcstring::operator=(const char* s)
{
  if(data->n==1)
    data->assign(strlen(s),s);//jeśli licznik referencji jest równy 1 to wywołujemy assign
  else
  {
    rctext* t = new rctext(strlen(s),s); //w przeciwnym przypadku tworzymy nowy obiekt rctext i nadpisujemy data nowym obiektem
    data->n--;
    data= t;
  };
  return *this;
}

ostream& operator << (ostream& o, const rcstring& s)
{
  return o<<s.data->s;
}

rcstring& rcstring::operator+=(const rcstring & s)
{
    unsigned int newsize=data->size+s.data->size;
    rctext *newdata=new rctext(newsize,data->s);
    strcat(newdata->s,s.data->s);//konkatenacja stringów
    if(--data->n==0)
      delete data;
    data = newdata;
    return *this;
}

rcstring rcstring::operator+(const rcstring & s) const
{
  return rcstring(*this)+=s;//operator + używa operatora +=
}

inline void rcstring::check (unsigned int i) const
{
if(data->size<=i)//jeśli i jest spoza zasięgu to rzucamy wyjątkiem
  throw Range();
}
inline char rcstring::read(unsigned int i) const
{
 return data->s[i];//zwracamy element spod indeksu i
}
inline void rcstring::write(unsigned int i, char c)
{
  data = data->detach();
  data->s[i] = c;
}

char rcstring::operator[](unsigned int i) const
{
  cout << "char rcstring::operator[](unsigned int i) const"<<endl;
  check(i);
  return data->s[i];//zwracamy element spod indeksu i
}

rcstring::Cref rcstring::operator[](unsigned int i)
{
  cout << "Cref rcstring::operator[](unsigned int i)"<<endl;
  check(i);//sprawdzamy czy i nie jest poza zasięgiem
  return Cref(*this,i);//zwracamy obiekt klasy Cref
}

int rcstring::Atoi() const {
  return atoi(this->data->s);
}
rcstring& rcstring::toLower() {
  this->data = data->detach();
  for (int i = 0; this->data->s[i]; ++i) {
    this->data->s[i] = tolower(this->data->s[i]);
  }
  return *this;
}
rcstring rcstring::Left(int n) const {
  if (n < 0 || n > (int)this->data->size) throw Range();
  string temp;
  for (int i = 0; i < n; temp += this->data->s[i], ++i);
  return rcstring(temp.c_str());
}


#endif /* __RCSTRING_H__ */
