// ======== in C:
// 3-char string is a size=4 array
const char *c="abc";
// use strcpy to copy

// ======== in C++:
//  can use char*
//  better use string from basic_string template
//   with char datatype
// or basic_string template with wchar_t

// string to char* conversion
// strlen, strcpy... size
/*
 * char array:
 *   in stack, always occupy 256 bytes - no matter how long the txt is contains
 *   copy >256 chars to char array, may hve assertion error
 *   in heap, actual size, overhead, need to delete[]
 *   across DLL boundaries, require same compiler and runtime implementation
 */
#include <string.h> // or <cstring> in c++
const char *str = "123"; // ok
char *s = "123"; // deprecated conversion from string const to 'char *'
int size = strlen(s); // 3
sizeof(s); // 8
char *s = new char[size+1];
strcpy(s, str);
...
delete[] s;


string s = "abc";
const char *b = s.c_str();
strlen(b) // 3
s.size() // 3
sizeof(s) // 8 or 32 depends on which string
char c[s.length()+1];
strcpy(c, s.c_str());

char c[3] = "abc";
strlen(c); // 3
sizeof(c); // 12

char a[3] = {0}; // 0,0,0
char a[3] = {'a'}; // 'a',0,0
char a[2] = "a"; // a,\0
char a[2] = {'a','\0'};// if all separately, need to have '\0'

char n1[3] = "abc";// illegal
char n1[3];
n1  =  "abc"; // illegal



