#include <iostream>
#include<string.h>
using namespace std;
class String {
public:
	String() { p = NULL; }
	String(char *str);
	String(string s);
	friend bool operator>(String &string1, String &string2);
	void display();
private:
	char *p;
};
String::String(char *str) {
	p = str;
}
String::String(string s) {
	p = (char*)s.c_str();
}
void String::display() {
	cout << p;
}
bool operator>(String &string1, String &string2) {
	if (strcmp(string1.p, string2.p) > 0)
		return true;
	else
	{
		return false;
	}
}
int main() {
	string s1 = "Hello", s2 = "Book";
	String string1((char*)s1.c_str());
	String string2((char*)s2.c_str());
	cout << (string1 > string2) << endl;
	String string3(s1);
	String string4(s2);
	cout << (string3 > string4) << endl;
	return 0;
}
