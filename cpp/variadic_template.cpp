main.t.cpp  hello world
IS_GTEST_MAIN=yes  

variadic template:
  template that can have any #of type parm of any type
  allow us to create data structures such as tuples
  allow us to create typesafe varargs functions

template<typename... Ts>
struct CustType {};
 CustType<> a;
 CustType<int> b;
 CustType<int, char> c;
 CustType<int, Foo<>, char> d;

// typically a recursive process
template<typename T>
T add(T head){ return head;}

template<typename T, typename... Ts>
T add(T head, Ts... tail){ return head + add(tail...);}
  std::cout << __PRETTY_FUNCTION__ << "\n"; // to see more info
  typename... Ts: template parameter pack
  Ts... tail: function parameter pack

template <typename T>
void variadicPrint(const T& head)
{
    std::cout << head << '-';
}

template <typename T, typename... Ts>
void variadicPrint(const T& head, const Ts&... tail)
{
    std::cout << head << ' ';
    variadicPrint(tail...);
}
int main()
{
    variadicPrint("helo", "world", 1, 2);
}
