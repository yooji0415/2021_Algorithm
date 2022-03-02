#include <iostream>
using namespace std;

int n, m;
int cnt=0;

void move(int **arr, int x, int y, int num){
    if(x==m-1 && y==0){
        if(cnt<num) cnt=num;
    } else if(x==m || y==-1){
        return ;
    }
    if(arr[y][x]==2) return;
    if(arr[y][x]==1) num++;
    move(arr, x+1, y, num);
    move(arr, x, y-1, num);
}

int main(int argc, char const *argv[])
{
    cin>>n>>m;
    int **miro = new int*[n];
    for(int i=0; i<m; i++) miro[i]=new int[m];

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int k;
            cin>>k;
            miro[i][j] = k;
        }
    }

    move(miro, 0, n-1, 0);

    cout<<cnt<<endl;

	return 0;
}
