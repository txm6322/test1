#include <iostream>
#include <sstream>
#include <cstdlib>
/*
 default c'tor: c'tor that either has no parm, or has parms, all have default values

  we create only when shallow copy is not good enough 
   or need allocation of resource 
    like(file handle, network connection...)
  not necessary if there's no resource related initialization.
*/

/*
class A {
 // compiler generates one only if no other c'tors are provided
 // other includes copy c'tor
 A() 

// auto provided if needed even if other c'tors are defined
 A(const A&o):i(o.i),d(o.d){..}
 A& operator=(const A&){..; return *this;}
};
*/
T foo(T obj) { // T's copy c'tor
    T x(obj); // T's copy c'tor
    T b = bar(); // fail if no copy c'tor() with const
                 // bar() creates tmp obj, copies to b
		 // the tmp can be const only
    T c;
    c = bar();   // this works even if c'tor with no const
    return x;    // copy c'tor becaue needs T
                 // return value optimization might omit this
};


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

Foo& Foo::operator=(const Foo&o){
    d_data = o.d_data; say("assignment operator: id:" + d_id); return *this;
}
ostream& operator <<(ostream& out, Foo o){
    out << "id:" << o.d_id << ":" << o.d_data;
    return out;
}

/*
 a Copy Constructor may be called in following cases:
   1. return by value. // no Return value Optimization
   2. passed as parm by value
   3. constructed based on another object of the same class.
   4. generates a temporary object. // no Return value Optimization
                                    // with -fno-elide-constructors
*/

Foo fun1(Foo o){ // (2)
    say("fun1:before ===========");
    Foo a, b(10); // default c'tor
    say("fun1:after 1 ===========");
    a = b;  // assignment operator: a has been created already
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
