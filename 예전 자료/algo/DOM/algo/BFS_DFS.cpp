#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
	int N, M, V;
	cin>>N>>M>>V;
	vector<int> *lines_b = new vector<int>[N+1];
	vector<int> *lines_d = new vector<int>[N+1];
	for(int i=0; i<M; i++){
		int a, b;
		cin>>a>>b;
		lines_b[a].push_back(b);
		lines_b[b].push_back(a);
	}

	for(int i=1; i<N+1; i++) sort(lines_b[i].begin(), lines_b[i].end());
	for(int i=1; i<N+1; i++)
		for(int j=0; j<lines_b[i].size(); j++)
			lines_d[i].push_back(lines_b[i].at(j));

	bool *visit = new bool[N+1]();
	vector<int> visited;
	stack<int> order_stack;
	order_stack.push(V);

    //DFS
	while(1){
		if(order_stack.empty()) break;
		int node = order_stack.top();
		order_stack.pop();
		if(visit[node]==1) continue;
		visit[node]=1;
		visited.push_back(node);
		while(!lines_d[node].empty()){
			int e = lines_d[node].back();
			order_stack.push(e);
			for(int i=0; i<lines_d[e].size(); i++){
				if(lines_d[e].at(i) == node)
					lines_d[e].erase(lines_d[e].begin()+i);
			}
			lines_d[node].pop_back();
		}
	}
	for(int i=0; i<visited.size(); i++)
		cout<< visited[i]<<" ";
	cout<<endl;

    //BFS
	visited.clear();
	queue<int> order;
	order.push(V);
    
	for(int i=1; i<N+1; i++) visit[i]=0;

	while(1){
		if(order.empty()) break;
		int node = order.front();
		order.pop();
		if(visit[node]==1) continue;
		visit[node]=1;
		visited.push_back(node);
		while(!lines_b[node].empty()){
			int e = lines_b[node].at(0);
			order.push(e);
			for(int i=0; i<lines_b[e].size(); i++){
				if(lines_b[e].at(i) == node)
					lines_b[e].erase(lines_b[e].begin()+i);
			}
			lines_b[node].erase(lines_b[node].begin());
		}
	}
	for(int i=0; i<visited.size(); i++)
		cout<< visited[i]<<" ";

    //Kruskal
    struct edge{
        int s;
        int e;
        int w;
    };
    int N;
	vector<edge> edges;



	return 0;
}

