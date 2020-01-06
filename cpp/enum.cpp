// for backward compatible with C, which does not have namespace, so enum has to be in the
// 1. global namespace.
enum B{a,b,c}; // a=0, b=1, c=2
enum SameValue{d=0,e,f=0); // can have same value for d,f, e = d+1
// 2. implicitly convert to int types
int k = a;
// 3. c++98: default underlying type is not defined
// 4. C++11: can forward declaration of enum, if specified a fixed underlying type
enum {ER=0, E1} va1; // unnamed enum
enum C: char {a1,b1}; // cannot define a
enum E: short int {k1=0x01, k3=0x100};
enum Days {Mon,Tue}; // unscoped. Mon, Tue is leaked:defined in global scope, cannot be redefined
Days day = Mon; // C++ way
enum Days day1; // C way, requires enum

if(day == Tue) ...

// trick to use scope:
struct Days1 { enum type {Mon, Tue}; };
Days1::type day1 = Days1::Mon;


enum Class Days2 {Mon, Tue}  // scoped enum. since C++11
Days2 day2;
if(day2 == Days2::Mon) ...

