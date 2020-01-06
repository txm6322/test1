// default initialization
T a; or T*a=new T;
T *a = new T(); // until C03

shared_ptr<T>(new T); // make_shared<T>(); // reference shared
      new T// not good, control +data not together

unique_ptr<T>(new T) // can not copy <memory>
make_unique<T>();

weak_ptr<T> = shared_ptr<T>

stl:
   more expressive
     raise abstraction
   avoid mistake
     off-by-one
     empty loops
     naive complexity
   used by lots of people
     common vacabulary
     whatever compiler


for_each
transformer
heap: max top
  make_heap(begin(numbers), end(numbers))
  push_heap(beg,end, value)
  pop_heap(beg,end)

sort
  sort
  partial_sort
  nth_element


1. python bcos publisher(should be simple, use sample code)
2. python mapper to json to publish(any bcos json->class?)
3. python bbnumber->figi(index->figi, use static python)
4. python index->figi(use static python)
5. what's schedule date, find a sample with multi dates and ask
     (cannot have multi sample)
     (only one sample)

