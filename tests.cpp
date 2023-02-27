#include<iostream>
#include "vector.h"
#include "filter.h"

//template class vector<double,3>;

using namespace std;

void compare(vector<double> a , vector<double> c){

	if( c == a)
		cout<<"equal\n";
	else 
		cout<<"unequal\n";
}

int main (void){
	/*
	vector<double , 3 > a;
	vector<double , 3 > b(1,1,1);
	vector<double , 3 > c(a);


	compare(a , c);
	compare(b , a);

	c = b = a;

	compare(a,b);

	a.set(1,0,0);
	b.set(0,1,0);
	c.set(0,0,1);
	
	vector<double,3> d = a + b;
	vector<double,3> e = b + c;

	cout<<"dot product : "<<d.dotProduct(e)<<endl;	
	a = d*e;
	cout<<"dot product : "<<a.dotProduct(a)<<endl;	
	//cout<<"cross product : "<<d*e<<endl;	

	b = a/3.0;

	b.print();
	*/
	vector<double> n(5);
	vector<double> d(5);

	n[0] = 4.824e-3;
	n[1] = 1.927e-2;
	n[2] = 2.894e-2;
	n[3] = n[1];
	n[4] = n[0];

	d[0] = 1;
	d[1] = -2.3695;
	d[2] = 2.3140;
	d[3] = -1.0547;
	d[4] = 0.1874;
	
	Zfilter lowpass(5,n,5,d);

	double arr[180];
	double out[180];

	for(int i = 0 ; i < 180; i++){
		arr[i] = sin(i*3.14159/180);
		out[i] = lowpass.calcOut(arr[i]);
		cout<<out[i]<<endl;
	}

	
}
