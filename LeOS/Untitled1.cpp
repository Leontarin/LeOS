#include <cstdio>
#include <iostream>
#include <string>
#include <windows.h>
#include <locale> 
using namespace std;

class Color{
	public:
	enum color{RED,GREEN,BLUE};
	enum color c;
	Color(enum color c): c(c){
		
	}
	
	~Color(){
		
	}
	operator int(){
		switch(c){
			case RED: return 0x0C;
			case GREEN: return 0x0A;
			case BLUE: return 0x0B;
		}
	} 
};

//writer of myString
class myString:public string{
	//operations on myString
	public:
	myString(const char* c):string(c){
		
	}
	void toLower(){
		for(int i=0;i<this->length();++i){
			if(this->at(i)<='A'&&this->at(i)<='Z')
			this->at(i)-=32;
		}
	}
};

//user
int main(){
	myString s= "LEO FeLDmaN";
	int x = s.length();
	cout<<x<<endl;
	auto offset = 'a' - 'A';
	cout<<offset<<endl;
	s.toLower();
	cout<<s<<endl;
	return 0;
}
