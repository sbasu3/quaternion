#include<iostream>
#include "vector.cpp"

//template class vector<int,3>;

using namespace std;

void compare(vector<int,3> a , vector<int,3> c){

	if( c == a)
		cout<<"equal\n";
	else 
		cout<<"unequal\n";
}

int main (void){

	vector<int , 3 > a;
	vector<int , 3 > b(1,1,1);
	vector<int , 3 > c(a);


	compare(a , c);
	compare(b , a);

	c = b = a;

	compare(a,b);

	a.set(1,0,0);
	b.set(0,1,0);
	c.set(0,0,1);

	vector<int,3> d = a + b;
	vector<int,3> e = b + c;

	cout<<"dot product : "<<d.dotProduct(e)<<endl;	
	a = d*e;
	cout<<"dot product : "<<a.dotProduct(a)<<endl;	
	//cout<<"cross product : "<<d*e<<endl;	


}
