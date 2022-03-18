#include<iostream>
#include<vector>
using namespace std;

int vertaxnum, line;

int *parent = new int[vertaxnum]; // parent배열, 정점들을 집단으로 묶어주기 위한 배열이다.


class Edge { // 정점을 구현하기 위한 Edge class
private:
	int ver1; 
	int ver2;
	int wei;
public:
	friend class Kruskal;
	Edge(int v1, int v2, int w) {
		ver1 = v1;
		ver2 = v2;
		wei = w;
	} // 생성자
};

class Kruskal { // kruskal 알고리즘을 구현하기 위한 class
public:
	friend class Edge;
	void selectionsort(vector<Edge> &a); // weight을 오름차순으로 정렬하기 위한 selection sort
	void kruskal(vector<Edge> &a);
	int find(int x); 
	void merge( int x, int y);
};
void Kruskal::kruskal(vector<Edge> &a) {
	int i,weight=0;
	int s = a.size();
	selectionsort(a); // 입력받은 Edge의 무게를 오름차순으로 정ㄹ렬
	for (i = 0; i < s; i++) {
		Edge e = a.at(i); // vector 속의 Edge를 새로운 Edge에 저장
		int x = find(e.ver1); // ver1의 끝의 정점을 x에 저장
		int y = find(e.ver2); // ver2의 끝의 정점을 y에 저장
		if (x != y) { // x와 y가 같지 않다면, 두개의 정점의 집단이 연결되어 있지 않는다는 것을 의미
			merge(x, y); // 두개의 정점을 연결하여, 두개의 집단을 하나로 합친다.
			cout << e.ver1 << " - " << e.ver2 << endl; // 정점 연결 된 것을 출력
			weight = weight + e.wei; // 그래프의 총 무게를 출력하기 위해 weight을 더해준다.
		}
	}
	cout << "정점의 총 무게 : " << weight << endl; // weight 출력
}
int Kruskal::find(int x) { //정점의 끝을 찾아가 끝을 반환해준다.
	if (x == parent[x]) { //x값과 parent배열의[x]순서에서 값이 같을 경우  x를 return
		return x;
	}
	else {
		return parent[x] = find(parent[x]); // 값이 다를 경우 재귀를 이용하여 parent[x]를 반환해준다.
	}
}
void Kruskal::merge(int x, int y) { // 두 집단을 하나의 정점의 집단으로 묶어주기 위한 merge
	x = find(x); // find(x)를 x에 저장
	y = find(y); // find(y)를 y에 저장
	parent[x] = y; //parent[x]에 y를 저장하여, 하나의 정점 집단으로 만들어준다.
} 
void Kruskal::selectionsort(vector<Edge> &a) { //selection sort
	int minidx;
	int s = a.size();
	for (int i = 0; i < s- 1; i++) {
		minidx = i;
		for (int j = i; j < s; j++) {
			if (a[minidx].wei > a[j].wei) {
				minidx = j;
			}
		}if (minidx != i) {
			Edge temp = a[minidx];
			a[minidx] = a[i];
			a[i] = temp;
		}
	}
}


int main() {
	int i,v1,v2,w;
	cout << "학번 :12141668 이름 : 김권중" << endl;
	cout << "정점의 갯수 : ";
	cin >> vertaxnum;
	cout << "간선의 갯수 : ";
	cin >> line;
	for (i = 1; i <= vertaxnum; i++) {
		parent[i] = i;
	} // parent배열을 정점 순으로 초기화한다.
	vector<Edge> a;
	cout << "정점 간선 입력 : " << endl;
	for (i=0;i<line;i++) {
		cin >> v1 >> v2 >> w;
		Edge v(v1, v2, w);
		a.push_back(v);
	}
	cout << endl;
	Kruskal k;
	cout << "연결 된 정점 : " << endl;
	k.kruskal(a);
	return 0;
}