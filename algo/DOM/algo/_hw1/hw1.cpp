#include <iostream>
#include <ctime>
#include <chrono>
#include "sort.h"
using namespace std;

double test_sorting(void (*sort)(int *, int), int *arr, int n){
    int *tmp = new int[n];
    for(int i=0; i<n; i++) tmp[i] = arr[i];
    clock_t s, e;
    s = clock();
    sort(tmp, n);
    e = clock();
    return (double)(e-s)/CLOCKS_PER_SEC;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    
    // // n = 1,000
    // int n = 1000;
    // int *arr = new int[n];
    // // generate random number
    // for(int i=0; i<n; i++){
    //     arr[i] = rand()%n;
    // }
    // double time;
    // cout<<"n : 1,000"<<endl;
    // time = test_sorting(sort::selection_sort, arr, n);
    // cout<<"selection sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::mot_quick_sort, arr, n);
    // cout<<"median of three quick sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::shell_sort, arr, n);
    // cout<<"shell sort : "<<time<<"s"<<endl;


    // // n = 10,000
    // n = 10000;
    // arr = new int[n];
    // // generate random number
    // for(int i=0; i<n; i++){
    //     arr[i] = rand()%n;
    // }
    // cout<<"n : 10,000"<<endl;
    // time = test_sorting(sort::selection_sort, arr, n);
    // cout<<"selection sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::mot_quick_sort, arr, n);
    // cout<<"median of three quick sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::shell_sort, arr, n);
    // cout<<"shell sort : "<<time<<"s"<<endl;


    // // n = 100,000
    // n = 100000;
    // arr = new int[n];
    // // generate random number
    // for(int i=0; i<n; i++){
    //     arr[i] = rand()%n;
    // }
    // cout<<"n : 100,000"<<endl;
    // time = test_sorting(sort::selection_sort, arr, n);
    // cout<<"selection sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::mot_quick_sort, arr, n);
    // cout<<"median of three quick sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::shell_sort, arr, n);
    // cout<<"shell sort : "<<time<<"s"<<endl;

    // // n = 1,000,000
    // n = 1000000;
    // arr = new int[n];
    // // generate random number
    // for(int i=0; i<n; i++){
    //     arr[i] = rand()%n;
    // }
    // cout<<"n : 1000,000"<<endl;
    // time = test_sorting(sort::selection_sort, arr, n);
    // cout<<"selection sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::mot_quick_sort, arr, n);
    // cout<<"median of three quick sort : "<<time<<"s"<<endl;
    // time = test_sorting(sort::shell_sort, arr, n);
    // cout<<"shell sort : "<<time<<"s"<<endl;

    // n = 1,024
    int n = 1024;
    int *arr = new int[n];
    // generate random number
    for(int i=0; i<n; i++){
        arr[i] = rand()%n;
    }
    double time;
    cout<<"n : 1,024"<<endl;
    time = test_sorting(sort::shell_sort, arr, n);
    cout<<"shell sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::bitonic_sort, arr, n);
    cout<<"bitonic sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::odd_even_merge_sort, arr, n);
    cout<<"odd even merge sort : "<<time<<"s"<<endl;


    // n = 8,192
    n = 8192;
    arr = new int[n];
    // generate random number
    for(int i=0; i<n; i++){
        arr[i] = rand()%n;
    }
    cout<<"n : 8,192"<<endl;
    time = test_sorting(sort::shell_sort, arr, n);
    cout<<"shell sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::bitonic_sort, arr, n);
    cout<<"bitonic sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::odd_even_merge_sort, arr, n);
    cout<<"odd even merge sort : "<<time<<"s"<<endl;


    // n = 65,536
    n = 65536;
    arr = new int[n];
    // generate random number
    for(int i=0; i<n; i++){
        arr[i] = rand()%n;
    }
    cout<<"n : 65,536"<<endl;
    time = test_sorting(sort::shell_sort, arr, n);
    cout<<"shell sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::bitonic_sort, arr, n);
    cout<<"bitonic sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::odd_even_merge_sort, arr, n);
    cout<<"odd even merge sort : "<<time<<"s"<<endl;
    
    // n = 524,288
    n = 524288;
    arr = new int[n];
    // generate random number
    for(int i=0; i<n; i++){
        arr[i] = rand()%n;
    }
    cout<<"n : 524,288"<<endl;
    time = test_sorting(sort::shell_sort, arr, n);
    cout<<"shell sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::bitonic_sort, arr, n);
    cout<<"bitonic sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::odd_even_merge_sort, arr, n);
    cout<<"odd even merge sort : "<<time<<"s"<<endl;

    // n = 4,194,304
    n = 4194304;
    arr = new int[n];
    // generate random number
    for(int i=0; i<n; i++){
        arr[i] = rand()%n;
    }
    cout<<"n : 4,194,304"<<endl;
    time = test_sorting(sort::shell_sort, arr, n);
    cout<<"shell sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::bitonic_sort, arr, n);
    cout<<"bitonic sort : "<<time<<"s"<<endl;
    time = test_sorting(sort::odd_even_merge_sort, arr, n);
    cout<<"odd even merge sort : "<<time<<"s"<<endl;


    return 0;
}
