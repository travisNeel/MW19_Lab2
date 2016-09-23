/*
 COSC2436 Lab 2, Instructor: Thayer
 Name: Travis Neel
 Semester: MW19 BLUE
 Topic: Recursion and Iteration, comparing performance
 */
#include <string>
#include <iostream>
#include <iomanip> // setw()
#include <limits>
using namespace std;

int test_array[100];
int medium_array[1000];
int big_array[100000];
int biggest_array[1000000];

string small_str="cat";
string medium_str="day6integration to society";
string big_str="day 231: the earthlings still havent noticed that im not one of them. ";
string biggest_str="day 747: i was discovered today, but thankfully nobody belived the poor schmuck since im running for president. \n bla blah blah maing string longer";



unsigned long long rdtsc() {                                          // intel / AMD clock ticks, Read Time-Stamp Counter
    unsigned int low, high;
    __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
    return ((unsigned long long)high << 32) | low;
}
    
void  writeStringBackwards_Recursive(string str){                         // recursive string reverse
    
    auto length=str.length();
        
    if (length>0){
        // cout<<str.substr(length-1, 1);                           // uncomment to display results.
        writeStringBackwards_Recursive(str.substr(0, length-1));
    }
}

void writeStringBackwards_Iterative(string str){                          // iterative string reverse
    
    long length=str.length();
    string temp=""; // used to build a reverse string
    
    for (int i=0; i<length+1; i++) temp+=str[length-i];
    //cout<<temp;                                                 // uncomment to print results.
}


int binarySearch_Recursive(int arr[], int size, int key){                // recursive binary search

    size-=1;
    
    if (size==0) return 0;                                 // not found
    else if (arr[size]==key)return 1;                      // found
    return binarySearch_Recursive(arr, size, key);
    
}

void binarySearch_Iterative(int arr[], int size, int key) {            // iterative binary search
    for (int i=0; i<size; ++i)
        if (arr[i]==key){
            //cout<<"Found!\n"; return key;
        }
    //cout<<"Not found!\n"; return -1;
}

void timing(unsigned long long start_time, string size, string type){
 
    auto start=start_time;
    auto finish=rdtsc();
    auto total=finish-start;
    cout<<"Clock ticks took to complete "<<left<<setw(7)<<size<<" "<<type<<" : "<<total<<"\n";
}

int main (){
    
    auto rdtsc_clocks_start=rdtsc();
    auto rdtsc_clocks_stop=rdtsc();
    auto rdtsc_clocks_total=rdtsc();
    auto overhead=rdtsc_clocks_stop-rdtsc_clocks_start;
    cout<<"cpu clocks between calls to rdtsc()="<<overhead<<endl<<endl;
    
    rdtsc_clocks_start=rdtsc();
    for (int i=0; i<10; i++) test_array[i]=i; // fills array with sorted numbers 1-100
    for (int i=0; i<1000; i++) medium_array[i]=i; // fills array with sorted numbers 1-1000
    for (int i=0; i<10000; i++) big_array[i]=i; // fills array with sorted numbers 1-10000
    for (int i=0; i<100000; i++) biggest_array[i]=i; // fills array with sorted numbers 1-100000
    rdtsc_clocks_stop=rdtsc(); rdtsc_clocks_total=rdtsc_clocks_stop-rdtsc_clocks_start;
    cout<<"cpu clocks to fill arrays = "<<rdtsc_clocks_total-overhead<<endl<<endl;
    
    /*~~~~~~~~TESTING~~~~~~~~~*/
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Recursive(small_str);
    timing(rdtsc_clocks_start,"small", "recursive swap");
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Recursive(medium_str);
    timing(rdtsc_clocks_start,"medium", "recursive swap");
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Recursive(big_str);
    timing(rdtsc_clocks_start,"big", "recursive swap");
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Recursive(biggest_str);
    timing(rdtsc_clocks_start,"biggest", "recursive swap");
    cout<<"\n";
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Iterative(small_str);
    timing(rdtsc_clocks_start,"small", "iterative swap");
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Iterative(medium_str);
    timing(rdtsc_clocks_start,"medium", "iterative swap");
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Iterative(big_str);
    timing(rdtsc_clocks_start,"big", "iterative swap");
    
    rdtsc_clocks_start=rdtsc();
    writeStringBackwards_Iterative(biggest_str);
    timing(rdtsc_clocks_start,"biggest", "Iterative swap");
    cout<<"\n";
    
    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Iterative(test_array, 10, -1);
    timing(rdtsc_clocks_start, "small", "Iterative search");
    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Iterative(medium_array, 1000, -1);
    timing(rdtsc_clocks_start, "medium", "Iterative search");
    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Iterative(big_array, 10000, -1);
    timing(rdtsc_clocks_start, "big", "Iterative search");
    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Iterative(biggest_array, 100000, -1);
    timing(rdtsc_clocks_start, "biggest", "Iterative search");
    cout<<"\n";

    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Recursive(test_array, 10, -1);
    timing(rdtsc_clocks_start, "small", "Recursive search");
    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Recursive(medium_array, 1000, -1);
    timing(rdtsc_clocks_start, "medium", "Recursive search");
    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Recursive(big_array, 10000, -1);
    timing(rdtsc_clocks_start, "big", "Recursive search");
    
    rdtsc_clocks_start=rdtsc();
    binarySearch_Recursive(biggest_array, 100000, -1);
    timing(rdtsc_clocks_start, "biggest", "Recursive search");
    
    cout<<"\n\n";
    return 0;
}
/* 

1) why does it take longer to add to numbers together than perform factorial or fibbonocci for small values?
    A) adding takes longer becasuse copies of variables need to be made, but small fibbonocci sequence compare the return value without having to make a copy.
 
2) why dont the timings increase steadily as the test data increase.
   A) iteration does, however recursion does not due to the overhead of making copy after copy of the function in memory. overhead increases exponentially.
 
3) which add<type> is noticably different than the others? why?
    A) add<string> is noticably different. a string is an object of type<char> and must be initialized, taking up more memory.
 
4) which technique usually performs faster? why? 
    A) Iterative usually performs faster because it doesnt save copies of itself over and over in memory, which
       gets exponentially more expensive the more recursion you do.

 
*/

/*

cpu clocks between calls to rdtsc()=33

cpu clocks to fill arrays = 2205118

Clock ticks took to complete small   recursive swap : 20996
Clock ticks took to complete medium  recursive swap : 12330
Clock ticks took to complete big     recursive swap : 59230
Clock ticks took to complete biggest recursive swap : 240233

Clock ticks took to complete small   iterative swap : 7214
Clock ticks took to complete medium  iterative swap : 5089
Clock ticks took to complete big     iterative swap : 14476
Clock ticks took to complete biggest Iterative swap : 9570

Clock ticks took to complete small   Iterative search : 641
Clock ticks took to complete medium  Iterative search : 8511
Clock ticks took to complete big     Iterative search : 71596
Clock ticks took to complete biggest Iterative search : 842228

Clock ticks took to complete small   Recursive search : 1178
Clock ticks took to complete medium  Recursive search : 45750
Clock ticks took to complete big     Recursive search : 914977
Clock ticks took to complete biggest Recursive search : 7792758


Program ended with exit code: 0

*/