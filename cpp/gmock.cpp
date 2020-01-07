========= check ==========
https://github.com/google/googletest/blob/master/googlemock/docs/cheat_sheet.md#CardinalityList

========= for dummies ==========
https://github.com/google/googletest/blob/master/googlemock/docs/for_dummies.md
========= Cookbook ==========
https://github.com/google/googletest/blob/master/googlemock/docs/cook_book.md

https://github.com/google/googletest/blob/master/googletest/docs/advanced.md

ASSERT/ExPECT_THROW
ASSERT/ExPECT_ANY_THROW
ASSERT/ExPECT_NO_THROW

ASSERT/EXPECT_PRED1(pred1, val1)  // pred1(val1) is true
ASSERT/EXPECT_PRED2(pred2, v1, v2)  // pred2(v1, v2) is true
ASSERT/EXPECT_PREDn(predn, v1, v2, .., vn)  // predn(v1, v2, ...) is true


EXPECT_CALL(mock, foo(matcher))
  .Times(AnyNumber()) 
  .WillOnce(Return(1))
  .WillOnce(Return(1))
  .WillRepeatedly(Return(1))

EXPECT_CALL(mock, foo(_));   // #1
EXPECT_CALL(mock, foo(10))   // #2
  .Times(2);
// 3 foo(10) failes at 3 as #2 is saturated after 2
// 2 foo(10) and 1 foo(20) works: last foo(20) matches foo(_)

// common: start a catch-all expectation
EXPECT_CALL(mock, foo(_))   // catch all
   .Times(AnyNumber());


// occur in a strict order
{
  InSequence seq;
  EXPECT_CALL(mock, f1());
  EXPECT_CALL(mock, f2(100));
  ...
}
for(int i=n; i>0; i--){ // returns 10, 20, 30, .. n*10
   EXPECT_CALL(mock, foo())
      .WillOnce(Return(10*i))
      .RetiresOnSaturation();
}

// AnyNumber(), AtLeast(n) AtMost(n), Between(m, n), Exactly(n) or n
WillOnce   WillRepeatedly()
  no         no                 => Times(1)
  n>=1       no                 => Times(n)
  n>=0       one                => TImes(Atleast(n))

Matcher:
  Eq(v) or v           arg == v
  Gt/Ge/Le/Lt/Ne(v)    arg > / >= /<= /< / != v
  IsFalse/True/Null()
  IsFalse/True/Null()
  NotNull()
  Optional(m)  // optional<> 
  VariantWith<T>(m)
  Ref<variable>  // arg is a reference to var
  TypedEq<type(value)  // arg has type and is equal to value

  Double/FloatEq(a_double/a_float) two NaNs as unequal
  NanSensitiveDouble/FLoatEq(a_double/a_float) two Nans as equal
  IsNan()
  Double/FloatNear(a_double/a_float, max_abs_error)
  NanSensiiveDouble/FloatNear(a_double/a_float, max_abs_error)

  ContainsRegex(reg)
  MatchesRegex(reg)  // start to end
  StartsWith/EndsWith(prefix/suffix)
  HasSubstr(sub)
  StrCaseEq/Ne(str)  eq or not eq, ignoring case
  StrEq/Ne(str)  eq or not eq


  ==== container ====
  BeginEndDistanceIs(m)/SizeIs(m)  // like SizeIs(Lt(2))
  ...
	 


#include<gmock/gmock.h>
class A {
    static int foo(int a) { return a+10;}
};

class B {
    static int bar(int b) {
        return A::foo(b);
    }
};

// how to test bar???
// 1. change B into a template
template<typename T=A>
class B {
    static int bar(int b) {
        return T::foo(b);
    }
};

// 2. create a mock
class MockA {
public:
   static MockCalc *mock;
   static int bar(int b) {
      return mock->foo(a);
   }
};

class MockCalc {
public:
   MOCK_METHOD1(foo, int(int));
}

// 3. test
MockCalc mock;
MockA::mock = &mock;

class MockA: public A {
public: // every mocked methods should be in public even not in A's public
    MOCK_METHOD(return_t, foo, (args...)[,(Specs...)]);
};
Specs:  const 
        override - for virtual
        noexcept - override noexcept
        Calltype(...) - used in Windows
if type has comma like std::map<int, int>
   a.  use brackets like (std::map<int,int>)
   b.  define alias
        using IntAndInt = std::pair<int, int>;
        MOCK_METHOD(IntAndInt, GetPair, ());

MOCK_METHOD(void, foo, (override, const));

class A {
public:
   virtual ~A(); // must be virtual
   // overloaded
   virtual int foo(int a);
   virtual int foo(int a, int b);

   // overloaded on const-ness
   virtual B& getB();
   virtual const B& getB() const;
};

class MockA: public A {
   // no need to mock all, warning unless:
   using A::foo; 
   MOCK_METHOD(int, foo, (int), (override));
   using A::getB; 
   MOCK_METHOD(B&, getB, (), (const, override));
};
================== mock template class ==============
template <typename T>
class B {
public:
   virtual ~B();
};

template<typename T>
class MockB: public B<T> {
public:
  MOCK_METHOD(void, push, (const T& x), (override));
};

================== mock non vitual class ==============
class C {
public:
   void foo();
   int bar(int);
};


class MockC { // no inherite
public:
   MOCK_METHOD(void, foo, ());
   // bar is not mocked as long as bar is not called
};

=== change fun to template
template <class T=C> void createX(T* s){}

==== in prod =
   C c;
   createX(&c);
==== in test
    MockC c;
   createX<MockC>(&c);

=======mock free function
class FileI {
public:
   virtual bool Open()=0;
};

class File: public FileI{
public:
   virtual bool Open() {
     return OpenFile(..); // this is the function to test
   }
};


using ::testing::NiceMock

MockFoo mock1;
EXPECT_CALL(mock1, foo1());
             // if foo2 is called, get warning
EXPECT_CALL(mock_foo, foo1());

NiceMock<MockFoo> mock2; // subclass of MockFoo
EXPECT_CALL(mock2, foo1());
             // if foo2 is called, warning is supressed

StrictMock<MockFoo> mock3; // subclass of MockFoo
EXPECT_CALL(mock3, foo1());
            // uninterested calls failures


EXPECT_*   - continue with the run if an assertion fails
ASSERT_*   - abort the program execution if an assertion fails
_TRUE(condition)
_NE(val1, val2)
_EQ(expected, f)
_FLOAT_EQ
_DOUBLE_EQ
_NEAR(expected, actual, absolute_range)
double f(){
   exit(-1);
}

ASSERT_EXIT(f(), ::testing::ExitedWithCode(-1), "Error: Wrong Input")

