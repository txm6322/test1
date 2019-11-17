#include <iostream>
#include <sstream>
#include <cstdlib>


using namespace std;

string i2s(int i){stringstream ss; ss << i; return ss.str();}

void say(const string& msg){
    static int step = 0;
    cout << ++step << ":" << msg << endl;
}

class A {
public:
    A(int i=0):d_id(i2s(id++)),d_data(i){say("default c'tor: id:" + d_id);} // default c'tor
    A(const A& o){ d_data=o.d_data;d_id=i2s(id++);say("c'tor: id:" + d_id);} // copy c'tor
    ~A(){say("d'tor: id:" + d_id);}
    friend ostream& operator <<(ostream&, A o);
private:
    static int id;
    string d_id;
    int d_data;
};
int A::id = 0;
ostream& operator <<(ostream& out, A o){
    out << "id:" << o.d_id << ":" << o.d_data;
    return out;
}
/* a Copy Constructor may be called in following cases:
1. is returned by value.
2. is passed by value.
3. from another object.
4. When the compiler generates a temporary object.
*/

A fun1(A a){ // (2)
    say("fun1:before");
    A b = a; // (3)
    say("fun1:after");
    b = 1;
    return b; // (1)
};

int main() {
    say("before b");
    A b;
    say("after b");
    A c =fun1(b);
    say("after c");
    cout << c << endl;
}
