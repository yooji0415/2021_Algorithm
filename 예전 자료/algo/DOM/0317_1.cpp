#include <iostream>
using namespace std;


int gcd(int a, int b){
   int max, min;
   if(a>b) max=a, min=b;
   else max=b, min=a;
   
   if(max%min==0) return min;
   else return gcd(min, max%min);

}
    
int lcm(int a, int b){
    return a*b/gcd(a, b);
}

int main(int argc, char const *argv[])
{
    int a, b;
    cin>>a>>b;
    cout<<gcd(a, b)<<endl;
    cout<<lcm(a, b)<<endl;
    return 0;
}
