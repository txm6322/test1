#include <iostream>
#include <map>
#include <type_traits>
using namespace std;

/*
void func(int a, int* b, int& c, int*& d int**e, int **& f){
    int tmp = 1234;
    b = &tmp;
    c =
}
*/

struct Backyard {};
struct Jungle {};
struct Cat { void pet();};
struct Tiger { void runAwayFrom();};
Cat findAnimal(Backyard);
Tiger findAnimal(Jungle);

/*
void foo(Jungle jungle, Backyard yard){ // C++98
    findAnimal(jungle).runAwayFrom();
    findAnimal(yard).pet(); // cdt can pop overload resolution
}
void cpp11(){ // c++11
    map<string, string> answers;
    auto result = answers.emplace("everything", "42");
    if(result.second){} // cdt popup correct hint
}
*/
constexpr int factorial(int n){
    if(n < 2)
        return 1;
    return factorial(n - 1) * n;
}

// C++ 14
auto f(int i) {  // return time deducde as int
    if(i==1) return 1;
    else return f(i - 1) + 2;
//    if(i!=1) return f(i-1)+2;  // this call fail as f is called too soon
//    else return i;
}
// put mouse here show calc'ed 3628800..
auto result = integral_constant<int, factorial(10)>();
int   i;
int&& f();
auto          x3a = i;     // decltype(x3a) is int
decltype(i)   x3d = i;     // decltype(x3d) is int
auto          x4a = (i);   // decltype(x4a) is int
decltype((i)) x4d = (i);   // decltype(x4d) is int&
//auto          x5a = f();   // decltype(x5a) is int
//decltype(f()) x5d = f();   // decltype(x5d) is int&&

auto const& fun1(int const& i){return i+1;}

template<class Category, class... Args>
decltype(auto) fun2(Category cat, Args&&... args){
    return cat(std::forward<Args>(args)...);
}

template<typename T>
constexpr T pi = T(3.141592653589793238462643383);

// Usual specialization rules apply:
template<>
constexpr const char* pi<const char*> = "pi";

// CDT fix is implemented as of Apri/2018, not in yet.
auto int1 = 1'000'000;
auto fp = 0.000'015'3;
auto binary_literal = 0b0100'1100'0110;
auto lambda = [](auto x, auto y) {return x + y;};
auto lambda1 = [value = 1] {return value*100;};



int main() {
    cout << "!Hello World1!" << endl;
    cout << result << endl;
    cout << "f(10):" << f(10) << endl;
    cout << "float:"<<fp <<" int:" << int1 << endl;
    cout << lambda(12,222)<< endl;
    cout << lambda1()<< endl;
    int m = 0;
    int n = 0;
    [&, n] (int a) mutable { m = ++n + a; }(4);
    cout << m << endl << n << endl;

    return 0;
}
