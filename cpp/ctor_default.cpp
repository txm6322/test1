#include <iostream>
#include <sstream>
#include <cstdlib>
/*
 - compiler implicitely declares a default c'tor if there's none,  will define it when in need.
 - compiler does not create a default c'tor if we write any c'tor even if it is copy c'tor.
 - compiler create a default copy c'tor even if we write other c'tors
 - required to do cerain initaliation of class intenals
 - no touch the data members or plain old data types(like array, struct,..)

*/


using namespace std;

string i2s(int i){stringstream ss; ss << i; return ss.str();}
void say(const string& msg){
    static int step = 0;
    cout << ++step << ":" << msg << endl;
}

class A {
public:
    // compiler "declares" default c'tor
};
class B {
public:
    B(){say("B default c'tor");}
};

class C: public B {
public:
	// compiler defines default c'tor, and inserts stub to call B c'tor
	// no initialize any data of B
};
class D: public B {
public:
	D(){
		// compiler inserts stub to call B's c'tor
		say("D default c'tor");
		// no initialize any data of B
	}
};

class Foo {
public:
    // default c'tor
    Foo(int i=0):d_id(i2s(id++)),d_data(i){say("default c'tor: id:" + d_id);}
    // copy c'tor
    Foo(const Foo& o){ d_data=o.d_data;d_id=i2s(id++);say("copy c'tor: id:" + d_id);}
    Foo& operator=(const Foo&); // assignment operator
    ~Foo(){say("      d'tor: id:" + d_id);}
    friend ostream& operator <<(ostream&, Foo o);
private:
    static int id;
    string d_id;
    int d_data;
};
int Foo::id = 0;

Foo& Foo::operator=(const Foo&o){d_data = o.d_data; say("assignment operator: id:" + d_id); return *this;}

ostream& operator <<(ostream& out, Foo o){
    out << "id:" << o.d_id << ":" << o.d_data;
    return out;
}
/* a Copy Constructor may be called in following cases:
1. When an object of the class is returned by value.
2. When an object of the class is passed (to a function) by value as an argument.
3. When an object is constructed based on another object of the same class.
4. When the compiler generates a temporary object.
*/

Foo fun1(Foo o){ // (2)
    say("fun1:before ===========");
    Foo a, b(10); // default c'tor
    say("fun1:after 1 ===========");
    a = b;  // assignment operator: a is created already
    say("fun1:after 2 ===========");
    Foo c = b; // (3)
    say("fun1:after 3 ===========");
    Foo fun2(); // declare a function
    Foo d = fun2(); // default c'tor, (4) with -fno-elide-constructors
    say("fun1:after 4 ===========");
    a = 3;b = 3; d = c;// delay d'tors
    return o; // (1)
};
Foo fun2(){return Foo();}

int main() {
    say("before b");
    Foo b;
    say("after b");
    Foo c =fun1(b);
    say("after c");
    cout << c << endl;
}
