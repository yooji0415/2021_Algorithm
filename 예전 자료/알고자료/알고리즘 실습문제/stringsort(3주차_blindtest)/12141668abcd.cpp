#include<iostream>
#include<string>

using namespace std;

void find(string arr[], string key, int index, int orderarr[]) {  //find keyword = text

   for (int i = 0; i<index; i++) {
      orderarr[i] = -1;
   }
   for (int k = 0; k<index; k++) {
      for (int i = 0; i<(arr[k].length()) - (key.length()) + 1; i++) {
         if (arr[k].substr(i, (int)key.length()).compare(key) == 0) {
            orderarr[k] = i;

         }

      }
   }

}
int findmin(int arr[], int len) {  //min index find
   int min = 99999;
   int k = 0;
   for (int i = 0; i<len; i++) {
      if (arr[i]<min) {
         min = arr[i];
         k = i;
      }
   }
   return k;
}
int main() {
	
   string key; // key
   string data[100]; //data
   string tmp; 
   int orderarr[100];
   int index = 0;
   getline(cin, key);

   for (;;) {
      getline(cin, tmp);
      if (tmp == "0")break;
      else data[index++] = tmp;
   }
   find(data, key, index, orderarr);
   int min;
   for (int i = 0; i<index; i++) {
      min = findmin(orderarr, index);
      cout << data[min] << endl;
      orderarr[min] = 99999;
   }
}