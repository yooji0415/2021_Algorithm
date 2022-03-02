#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int vertaxnum, line;

class Edge {  // Edge
private:
	int ver; // 현재 위치의 정점
	int from = -1; // 이전 단계의 정점 시작지점의 전 정점은 -1
	int wei = 0; //정점의 무게
public:
	friend class Prim;
	friend class comp;
	Edge(int v, int f) { // 생성자
		ver = v;
		from = f;
	}
};
class comp { // priority queue의 비교를 위해 연산자 오버로딩을 위한 클래스
public:
	friend class Edge;
	bool operator()(Edge a, Edge b) {
		return a.wei > b.wei; 
	}
};
class Prim {
public:
	friend class Edge;
	void prim(int **map, int ** weight, int start);
};
void Prim::prim(int **map, int ** weight, int start) {
	int i,vertaxwei=0;
	bool *visited = new bool[vertaxnum+1];
	for (i = 0; i <= vertaxnum; i++) {
		visited[i] = false;
	}// visited 배열을 false로 초기화 
	Edge st(start, -1); // start지점을 st로 선언
	priority_queue<Edge,vector<Edge>,comp> q; // priority_queue를 이용하기위해 선언, comp class를 이용해 비교
	q.push(st); // st를 q에 push
	while (!q.empty()) {
		Edge a = q.top(); // q의 top을 Edge에 저장
		q.pop(); //q를 pop
		if (visited[a.ver] == true) {
			continue;
		} // 해당 정점이 방문을 했을 경우, 스킵
		visited[a.ver] = true; // visited를 true
		cout << a.from << " - " << a.ver << " weight : " << a.wei << endl; // 이전단계의 정점, 현재 정점, 무게를 출력
		vertaxwei = vertaxwei + a.wei; // 정점의 총 무게를 구하기 위해 vertaxwei에 저장
		for (i = 1; i <= vertaxnum; i++) {
			if (map[a.ver][i] == 1 && visited[i] == false) { //정점이 연결되어있으며, 접근하지 않은 정점
				Edge e(i, a.ver); // 새로운 Edge에 저장
				e.wei = weight[a.ver][i]; // 정점의 무게는 이어진 선의 무게
				q.push(e); // q에 push
			}
		}
	}
	cout << "정점의 총 weigt : " << vertaxwei << endl;
}
int main() {
	int i, j, v, f, w, start;
	cout << "정점의 갯수 입력 : ";
	cin >> vertaxnum; // 정점의 갯수와 간선의 갯수를 입력
	cout << "간선의 갯수 입력 : ";
	cin >> line;
	int **map = new int*[vertaxnum + 1];
	for (i = 0; i <= vertaxnum; i++) {
		map[i] = new int[vertaxnum];
	}
	int **weight = new int*[vertaxnum + 1];
	for (i = 0; i <= vertaxnum; i++) {
		weight[i] = new int[vertaxnum];
	}
	for (i = 0; i <= vertaxnum; i++) {
		for (j = 0; j <= vertaxnum; j++) {
			map[i][j] = 0;
			weight[i][j] = 0;
		}
	} // map과 weight을 0으로 초기화
	cout << "정점과 간선을 입력 : " << endl;
	for (i = 0; i < line; i++) {
		cin >> v >> f >> w; // 현재 정점과 이전 정점 간선의 무게를 입력
		map[v][f] = map[f][v] = 1; // 현재 정점과 이전 정점의 연결이 되면 1
		weight[v][f] = weight[f][v] = w; // 무게 입력
	}
	Prim p;
	cout << "시작할 정점의 위치를 입력 : ";
	cin >> start;
	p.prim(map, weight, start);
}