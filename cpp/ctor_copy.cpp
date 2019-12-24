#include <iostream>
#include <sstream>
#include <cstdlib>
/*
 - create default copy c'tor or assignment operator even if other c'tors are defined
 - not necessary if there's no resource related initialization.
 A() // compiler generates one only if no other c'tors are provided
 A(..)
 A(const A&) // auto provided if needed
    // we create only when shallow copy is not good enough or need allocation of resource 
    //   like(file handle, network connection...)
 A& operator=(const A&){..; return *this;} // auto provided if needed

*/


using namespace std;
string i2s(int i){stringstream ss; ss << i; return ss.str();}
void say(const string& msg){
    static int step = 0;
    cout << ++step << ":" << msg << endl;
}

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
1. return by value. // no Return value Optimization
2. passed as parm by value
3. constructed based on another object of the same class.
4. generates a temporary object. // no Return value Optimization
     with -fno-elide-constructors
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
}


const char param[] = "bar";
    a = 3;b = 3; d = c;// delay d'tors
    return o; // (1)
};

void foo(char[] str) { printf(str); }

Foo fun2(){return Foo();}

int main() {
    say("before b");
    Foo b;
    say("after b");
    Foo c =fun1(b);
    say("after c");
    cout << c << endl;
}
