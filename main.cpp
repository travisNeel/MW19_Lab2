#include <iomanip>
#include <iostream>
#include <array>
using namespace std;

string word="shoobie-doop";
int test_array[100];



void  writeStringBackwards_Recursive(string str){                     // recursive string reverse
    
    auto length=str.length();
    
    if (length>0) {
        cout<<str.substr(length-1, 1);
        writeStringBackwards_Recursive(str.substr(0, length-1));
    }
}

void writeStringBackwards_Iterative(string str){                      // iterative string reverse
    
    long length=str.length();
    
    for (int i=0; i<length+1; i++) {
        cout<<str[length-i];
    }
    cout<<"\n";
}


void binarySearch_Recursive(int arr[], int size, int key){            // recursive binary search

    size-=1;
    
    if (size==0) cout<<"Not found!\n";
    else if (arr[size]==key)cout<<"Found!\n";
    else binarySearch_Recursive(arr, size, key);
    
}

void binarySearch_Iterative(int arr[], int size, int key) {            // terative binary search
    for (int i=0; i<size; ++i)
        if (arr[i]==key){
            cout<<"Found!\n"; return;
        }
    cout<<"Not found!\n";
    }


int main (){
    
    for (int i=0; i<100; i++) test_array[i]=i;          // fills array with sorted numbers 1-100
    
    writeStringBackwards_Recursive(word); cout<<"\n";
    writeStringBackwards_Iterative(word); cout<<"\n";

    binarySearch_Recursive(test_array, 100, 4);
    binarySearch_Iterative(test_array, 100, 4);

    
    
    return 0;
}