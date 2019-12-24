#include <iostream>
#include <vector>
#include <alorithm>
using namespace std

bool isOdd(const int v){ return v % 2 == 1;}

struct Predicate{ // Predicate functor
    Predicate(int v):n(v){}
    bool operator()(int v) const {return v % n == 0;}
    int n;
};

void process(int v) {cout << v << ""; }

int main() {
    
   vector<int> v={4, 2, 3, 1, 2, 5, 111, 222};
   typedef vector<int>::iterator VIT
   // find_if(): find with a fuction/functor
   {
      for(VIT it = begin(v); (it = find_if(it, end(v), isOdd)) != end(v);++it)
          cout << *it << endl;
      for(VIT it = begin(v); (it = find_if(it, end(v), Predicate(111))) != end(v);++it)
          cout << *it << endl;    
         
      VIT it = begin(v);
      while(true){
          if((it = find_if(it, end(v), isOdd)) == end(v))
              break;
          cout << *it << endl;   
          it++;
      }
    }
    
    {
       // find(), find a single value
       for(VIT it = begin(v);(it = find(it, end(v), 2)) != end(v);++it)
           cout << *it << endl;
    }

    // remove_if()
    VIT p_end = remove_if(begin(v), end(v), Predicate(500));
    for_each(begin(v), p_end, process);

    // remove_if moves all pred=false elem to the front and return the last+1
    // size cannot be changed.
    //
    // remove_copy_if() original is untouched
    vector<int> lefts(v.size()); // should reserve enough size
    VIT p_end = remove_copy_if(begin(v), end(v), begin(lefts), Predicate(500));
    if(p_end == begin(lefts))
	cout << "nothing left";
    for_each(begin(lefts), end(lefts), process);
    // if all removed, p_end is begin()

    // partition(): true true,.. border(false), false..
    VIT border = partition(begin(v), end(v), isOdd);
    // partitioned into true,true,..., false, false..
    for_each(begin(v), border, process); // odd
    for_each(border, end(v), process); // even

}
