#include <iostream>
using namespace std;

namespace sort{
    namespace {
        void swap(int &a, int &b){
            int tmp = a;
            a = b;
            b = tmp;
        }   

        void mot_quick_process(int *arr, int s, int e){
            int bs=s, be=e;
            int m = (s+e)/2;
            if(arr[s]>arr[m]) swap(arr[s], arr[m]);
            if(arr[m]>arr[e]) swap(arr[m], arr[e]);
            if(arr[s]>arr[m]) swap(arr[s], arr[m]);
            if(e-s<3) return ;

            int pivot = arr[m];
            swap(arr[bs+1], arr[m]);
            s++; e--;
            //12171833 이정우
            while(s<e){
                while(pivot<=arr[e] && s<e) e--;
                if(s>e) break;
                while(pivot>=arr[s] && s<e) s++;	
                if(s>e) break;
                swap(arr[s], arr[e]);
            }
            swap(arr[bs+1], arr[s]);
            if(bs<s) mot_quick_process(arr, bs, s-1);
            if(be>e) mot_quick_process(arr, s+1, be);
        }

        void bitonic_1d(bool up_flag, int *arr, int s, int e){
            if(e-s==1) return ;
            int d = (e-s)/2;
            int m = (s+e)/2;
            for(int i=s; i<m; i++){  
                if ((arr[i]>arr[i+d]) == up_flag)
                    swap(arr[i], arr[i+d]);
            }   //12171833 이정우
            bitonic_1d(up_flag, arr, s, m);
            bitonic_1d(up_flag, arr, m, e);
        }
        
        void bitonic_2d(bool up_flag, int *arr, int s, int e){
            if(e-s==1) return ;     //12171833 이정우
            int d = (e-s)/2;
            int m = (s+e)/2;
            bitonic_2d(true, arr, s, m);
            bitonic_2d(false, arr, m, e);
            for(int i=s; i<m; i++){  
                if ((arr[i]>arr[i+d]) == up_flag)
                    swap(arr[i], arr[i+d]);
            }
            bitonic_1d(up_flag, arr, s, m);
            bitonic_1d(up_flag, arr, m, e);
        }

        void oem_swap(int *arr, int s, int e){
            int d = (e-s)/2;
            int m = (s+e)/2;
            for(int i=s; i<m; i++){  
                if (arr[i]>arr[i+d])
                    swap(arr[i], arr[i+d]);
            }       //12171833 이정우
            while(true){
                d/=2;
                if(d==0) break;
                int i=s+d;
                while(d<e-d-i){
                    if (arr[i]>arr[i+d])
                        swap(arr[i], arr[i+d]);
                    i++;
                }
            }
        }

        void oem_process(int *arr, int s, int e){
            if(e-s==1) return ;
            int m = (s+e)/2;    //12171833 이정우
            oem_process(arr, s, m);
            oem_process(arr, m, e);
            oem_swap(arr, s, e);
        }
    }

    void selection_sort(int *arr, int length){
        for(int i=0; i<length-1; i++){
            int min=i;
            for(int j=i; j<length; j++){
                if(arr[j] < arr[min]) min=j;
            }
            if(min != i) swap(arr[i], arr[min]);
        }
    }

    void mot_quick_sort(int *arr, int length){
        mot_quick_process(arr, 0, length-1);
    }


    void shell_sort(int *arr, int length){
        int h=1;
        while(h<length-1) h=h=3*h+1;
        h/=3;
        //12171833 이정우
        while(h){
            for (int i=h; i<=length; i++){
                int v = arr[i];
                int j = i;
                while (j>=h && arr[j-h]>v){
                    arr[j] = arr[j-h];
                    j = j-h;
                }
                arr[j] = v;
            }
            h/=3;
        } 
    }   

    void bitonic_sort(int *arr, int length){
        bitonic_2d(true, arr, 0, length);
    }

    void odd_even_merge_sort(int *arr, int length){
        oem_process(arr, 0, length);
    }
};
