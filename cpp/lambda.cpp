/*
 [capture](param)  mutable [exception] -> ret { statements;}
 |         |       |                    |        \- lambda body, can return or no return
 |         |       |                    \- optional return type, can be void
 |         |       \- optional mark the lambda as mutal lambda
 |         \- optional parms
 \-captures 
default capture mode: [=] or [&]
  all available locals(include this)
 []          capture nothing
 [&]         capture all by ref
 [=]         capture all by making a copy
 [=, &foo]   capture all by making a copy, but foo with ref
 [&, foo]    capture all by ref, but foo with making a copy
 [foo]       capture foo by make a copy, nothing else
 [this]      capture the this pointer of the enclosing class
 [a]: a is const, or use "[a] mutable" to modify a(actually modify the lambda itself)
 https://stackoverflow.com/questions/5501959/why-does-c11s-lambda-require-mutable-keyword-for-capture-by-value-by-defau
*/

    int x = 10;
    auto lamb = [=]() mutable {cout << x++ << endl;}; // need to have "() mutable"
    x = 100; // not captured
    lamb(); // 10, x inside=11
    lamb(); // 11, out x has no impact

    int count = 0;
    [&count](char c){if(isupper(c)) count++;}
    sort(p_float, p_float+n, [](float a, float b){return abs(a) < abs(b);}



template<typename Func>
string findOne(vector<string>& vec, Func func){
   for(auto item:vec){
      if(func(item))
	 return item;
   }
   return "";
}
f1 = [](const string& str) { return str.find("abc") != string::npos;}
string x= findOne(vec, f1);

string this_time_str = "123";
f1 = [&](const string& str) { return str.find(this_time_str) != string::npos;}
string y= findOne(vec, f1);

int min_len = 10;
f1 = [&](const string& str) { return str.length() >= min_len;}
string z= findOne(vec, f1);

f1 = [](int v){cout << v;}
for_each(v.begin(), v.end(), f1);

[out=std::ref(std::cout << "hello ")]        { out.get() << "world\n"; }();
[out=std::ref(std::cout << "hello ")]()->void{ out.get() << "world\n"; }();
[out=std::ref(std::cout << "hello ")](auto obj)->void{ out.get() << "world1" << obj << endl; }(" again");
// = std:ref  #include <functional>  only with C++14


