// for backward compatible with C, which does not have namespace, so enum has to be in the
// global namespace.
enum Days {Mon,Tue}; // unscoped. Mon, Tue is leaked/:defined in global scope, cannot be redefined
Days day = Mon; // C++ way
enum Days day1; // C way, requires enum

if(day == Tue) ...

// trick to use scope:
struct Days1 { enum type {Mon, Tue}; };
Days1::type day1 = Days1::Mon;


enum Class Days2 {Mon, Tue}  // scoped enum. since C++11
Days2 day2;
if(day2 == Days2::Mon) ...

