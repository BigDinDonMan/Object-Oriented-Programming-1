#include "rcstring.h"

int main()
{
	rcstring a,b,c;
	a="10";
	b="ala ma kota";
	cout << a << " " << b << endl; // 10 ala ma ma kota
	c=a+b;
	cout << c<<endl; // 10ala ma kota
	c=a+rcstring(" ")+b;
	cout << c << endl; //10 ala ma kota
	rcstring d("a");
	cout << d <<endl; //a
	d+="ula";
	cout << d << endl; //aula
	d+="15";
	cout << d << endl; //aula15
	cout << d[3]<<endl; //a
	d[3]='b';
	cout << d << endl; //aulb15
	d[2]=d[1]=d[0];
	cout << d << endl; //aaab15
	rcstring num;
	num = "-";
	num += "15";
	rcstring upper = "ALA MA KOTA";
	rcstring temp = upper;
	cout << upper.toLower() << endl;
	cout << num.Atoi() << endl;
	cout << upper.Left(6) << endl;
	cout << temp << endl;
	cout << upper << endl;

	return 0;
}
