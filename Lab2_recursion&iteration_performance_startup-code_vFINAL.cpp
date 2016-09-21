/*
  COSC2436 Lab 2, Instructor: Thayer
  Name:
  Semester:
  Topic: Recursion and Iteration, comparing performance
*/
#include <string>
#include <iostream>
#include <iomanip> // setw()
#include <limits>
using namespace std;

unsigned long long rdtsc() { // intel / AMD clock ticks, Read Time-Stamp Counter
  unsigned int low, high;
  __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
  return ((unsigned long long)high << 32) | low;
}

template <typename T>
void add(int iterations, T a=123, T b=456) {  // T + T operation, timing
  T c;
  for (int n=0; n<iterations; ++n)
    c=a+b; // throw away result, this is just to test performance
}

const int MAX_ITERATIONS=501;
const int SKIP_ITERATIONS=100;
template <typename T>
void do_add_timing(string type_name, T a=123, T b=456) {
  for (int iterations = 0; iterations<MAX_ITERATIONS; iterations+=SKIP_ITERATIONS) {
    auto rdtsc_clocks_start=rdtsc();
    add<T>(iterations, a, b);
    auto rdtsc_clocks_stop=rdtsc();
    auto duration=rdtsc_clocks_stop-rdtsc_clocks_start;
    cout<<"cpu clocks during add<"<<type_name<<">("<<setw(3)<<iterations<<")="<<setw(4)<<duration<<endl;
  }
}

// factorial, iterative and recursive (provided by instructor)
int factorial_iterative(int n) {
  int answer=1;
  for (int factor=1; factor<=n; ++factor) {
    answer*=factor;
  }
  return answer;
}

int factorial_recursive(int n) { // textbook, chapter 2, section 2.2.1, page 52 (7ed), modified
  if (n<=1) return 1;
  return n*factorial_recursive(n-1);
}

// fibonacci, iterative and recursive (provided by instructor)
int fibonacci_iterative(int n) {  // textbook, chapter 2, section 2.7, page 87 (7ed)
  int previous=1, current=1, next=1;
  for (int i=3; i<=n; ++i) {
    next=current+previous;
    previous=current;
    current=next;
  }
  return next;
}

int fibonacci_recursive(int n) { // textbook, chapter 2, section 2.6.1, page 81 (7ed)
  if (n<=2) return 1;
  return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}

void do_recursive_timing(string function_name, int(function)(int), int max_iterations=1) {
  // the 2nd parameter, int(function)(int), is a function that returns int and has 1 int parameter
  // estimate overhead incurred by calling rdtsc(). Don't include this in timing
  auto rdtsc_clocks_start=rdtsc();
  auto rdtsc_clocks_stop=rdtsc();
  auto overhead=rdtsc_clocks_stop-rdtsc_clocks_start;
  
  for (int n=0; n<max_iterations; ++n) {
    rdtsc_clocks_start=rdtsc();
    function(n); // call function being timed
    rdtsc_clocks_stop=rdtsc();
    auto duration=rdtsc_clocks_stop-rdtsc_clocks_start;
    cout<<function_name<<"("<<setw(2)<<n<<") cpu clocks="
        <<((duration>overhead)?(duration-overhead):0)<<endl;
  }
}

int main () {
  auto rdtsc_clocks_start=rdtsc();
  auto rdtsc_clocks_stop=rdtsc();
  auto overhead=rdtsc_clocks_stop-rdtsc_clocks_start;
  cout<<"cpu clocks between calls to rdtsc()="<<overhead<<endl<<endl;
  
  do_add_timing<int>("int");         cout<<endl;
  do_add_timing<float>("float");     cout<<endl;
  do_add_timing<double>("double");   cout<<endl;
  do_add_timing<long long>("long long");  cout<<endl;
  do_add_timing<string>("string", "hello", "there");  cout<<endl;
  
  for (int n=0; n<10; ++n) { // verify iterative and recursive implementation has same result
    cout<<"factorial_iterative("<<n<<")="<<setw(7)<<factorial_iterative(n)<<"   "
        <<"factorial_recursive("<<n<<")="<<setw(7)<<factorial_recursive(n)<<endl;
  }
  cout<<endl;
  
  // compare timing between iterative and recursive implementation
  do_recursive_timing("factorial_iterative", factorial_iterative, 15);  cout<<endl;
  do_recursive_timing("factorial_recursive", factorial_recursive, 15);  cout<<endl;

  for (int n=1; n<12; ++n) { // verify iterative and recursive implementation has same result
    cout<<"fibonacci_iterative("<<setw(2)<<n<<")="<<setw(5)<<fibonacci_iterative(n)<<"   "
        <<"fibonacci_recursive("<<setw(2)<<n<<")="<<setw(5)<<fibonacci_recursive(n)<<endl;
  }
  cout<<endl;
  
  // compare timing between iterative and recursive implementation
  do_recursive_timing("fibonacci_iterative", fibonacci_iterative, 15);  cout<<endl;
  do_recursive_timing("fibonacci_recursive", fibonacci_recursive, 15);  cout<<endl;
}

/* Extra credit Q answers:

*/

/* test output:
cpu clocks between calls to rdtsc()=111

cpu clocks during add<int>(  0)= 768
cpu clocks during add<int>(100)=2097
cpu clocks during add<int>(200)=1821
cpu clocks during add<int>(300)=2607
cpu clocks during add<int>(400)=3514
cpu clocks during add<int>(500)=4313

cpu clocks during add<float>(  0)= 349
cpu clocks during add<float>(100)= 994
cpu clocks during add<float>(200)=1778
cpu clocks during add<float>(300)=2607
cpu clocks during add<float>(400)=3436
cpu clocks during add<float>(500)=4289

cpu clocks during add<double>(  0)= 398
cpu clocks during add<double>(100)= 998
cpu clocks during add<double>(200)=1815
cpu clocks during add<double>(300)=3007
cpu clocks during add<double>(400)=3606
cpu clocks during add<double>(500)=4633

cpu clocks during add<long long>(  0)= 179
cpu clocks during add<long long>(100)=1035
cpu clocks during add<long long>(200)=1832
cpu clocks during add<long long>(300)=2598
cpu clocks during add<long long>(400)=3424
cpu clocks during add<long long>(500)=4254

cpu clocks during add<string>(  0)=2398
cpu clocks during add<string>(100)=116982
cpu clocks during add<string>(200)=155941
cpu clocks during add<string>(300)=284016
cpu clocks during add<string>(400)=306429
cpu clocks during add<string>(500)=382365

factorial_iterative(0)=      1   factorial_recursive(0)=      1
factorial_iterative(1)=      1   factorial_recursive(1)=      1
factorial_iterative(2)=      2   factorial_recursive(2)=      2
factorial_iterative(3)=      6   factorial_recursive(3)=      6
factorial_iterative(4)=     24   factorial_recursive(4)=     24
factorial_iterative(5)=    120   factorial_recursive(5)=    120
factorial_iterative(6)=    720   factorial_recursive(6)=    720
factorial_iterative(7)=   5040   factorial_recursive(7)=   5040
factorial_iterative(8)=  40320   factorial_recursive(8)=  40320
factorial_iterative(9)= 362880   factorial_recursive(9)= 362880

factorial_iterative( 0) cpu clocks=28
factorial_iterative( 1) cpu clocks=136
factorial_iterative( 2) cpu clocks=111
factorial_iterative( 3) cpu clocks=39
factorial_iterative( 4) cpu clocks=46
factorial_iterative( 5) cpu clocks=166
factorial_iterative( 6) cpu clocks=178
factorial_iterative( 7) cpu clocks=192
factorial_iterative( 8) cpu clocks=214
factorial_iterative( 9) cpu clocks=207
factorial_iterative(10) cpu clocks=215
factorial_iterative(11) cpu clocks=229
factorial_iterative(12) cpu clocks=235
factorial_iterative(13) cpu clocks=260
factorial_iterative(14) cpu clocks=264

factorial_recursive( 0) cpu clocks=50
factorial_recursive( 1) cpu clocks=67
factorial_recursive( 2) cpu clocks=334
factorial_recursive( 3) cpu clocks=856
factorial_recursive( 4) cpu clocks=916
factorial_recursive( 5) cpu clocks=484
factorial_recursive( 6) cpu clocks=550
factorial_recursive( 7) cpu clocks=599
factorial_recursive( 8) cpu clocks=572
factorial_recursive( 9) cpu clocks=405
factorial_recursive(10) cpu clocks=607
factorial_recursive(11) cpu clocks=809
factorial_recursive(12) cpu clocks=556
factorial_recursive(13) cpu clocks=984
factorial_recursive(14) cpu clocks=523

fibonacci_iterative( 1)=    1   fibonacci_recursive( 1)=    1
fibonacci_iterative( 2)=    1   fibonacci_recursive( 2)=    1
fibonacci_iterative( 3)=    2   fibonacci_recursive( 3)=    2
fibonacci_iterative( 4)=    3   fibonacci_recursive( 4)=    3
fibonacci_iterative( 5)=    5   fibonacci_recursive( 5)=    5
fibonacci_iterative( 6)=    8   fibonacci_recursive( 6)=    8
fibonacci_iterative( 7)=   13   fibonacci_recursive( 7)=   13
fibonacci_iterative( 8)=   21   fibonacci_recursive( 8)=   21
fibonacci_iterative( 9)=   34   fibonacci_recursive( 9)=   34
fibonacci_iterative(10)=   55   fibonacci_recursive(10)=   55
fibonacci_iterative(11)=   89   fibonacci_recursive(11)=   89

fibonacci_iterative( 0) cpu clocks=103
fibonacci_iterative( 1) cpu clocks=106
fibonacci_iterative( 2) cpu clocks=105
fibonacci_iterative( 3) cpu clocks=114
fibonacci_iterative( 4) cpu clocks=150
fibonacci_iterative( 5) cpu clocks=77
fibonacci_iterative( 6) cpu clocks=113
fibonacci_iterative( 7) cpu clocks=123
fibonacci_iterative( 8) cpu clocks=121
fibonacci_iterative( 9) cpu clocks=175
fibonacci_iterative(10) cpu clocks=191
fibonacci_iterative(11) cpu clocks=317
fibonacci_iterative(12) cpu clocks=379
fibonacci_iterative(13) cpu clocks=368
fibonacci_iterative(14) cpu clocks=455

fibonacci_recursive( 0) cpu clocks=91
fibonacci_recursive( 1) cpu clocks=126
fibonacci_recursive( 2) cpu clocks=149
fibonacci_recursive( 3) cpu clocks=309
fibonacci_recursive( 4) cpu clocks=291
fibonacci_recursive( 5) cpu clocks=442
fibonacci_recursive( 6) cpu clocks=647
fibonacci_recursive( 7) cpu clocks=1045
fibonacci_recursive( 8) cpu clocks=1428
fibonacci_recursive( 9) cpu clocks=1651
fibonacci_recursive(10) cpu clocks=2772
fibonacci_recursive(11) cpu clocks=4567
fibonacci_recursive(12) cpu clocks=5682
fibonacci_recursive(13) cpu clocks=9069
fibonacci_recursive(14) cpu clocks=15703
*/
