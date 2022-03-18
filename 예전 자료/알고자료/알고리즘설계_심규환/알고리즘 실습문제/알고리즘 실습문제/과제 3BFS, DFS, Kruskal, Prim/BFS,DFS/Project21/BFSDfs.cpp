#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Bvertax {  //BFS 
private:
	int ver; //정점
	int from = -1; // 정점이 어느 정점으로부터 오는지 확인, -1로 초기화
public:
	Bvertax(int v, int f) {  // 생성자
		ver = v;
		from = f;
	}
	int getver() { // 정점을 출력
		return ver;
	}
	void BFS(int **map, int start, int n);
};

void Bvertax ::BFS(int **map, int start,int n) {
	int i;
	bool *visited = new bool[n+1];
	for (i = 0; i <= n; i++) {
		visited[i] = false;
	} // visited배열이며 false로 초기화
	Bvertax st(start, -1); // 매개변수로 입력된 start로 부터 시작하기 위해 하였으며, 시작 지점이기에 from -1 이다.
	visited[st.getver()] = true; //visited 배열의 start를 true
	queue<Bvertax> que; // queue 생성
	que.push(st); // start로 만들어진 클래스를 queue에 push
	while (!que.empty()) { // queue가 빌 때 까지 while문을 사용
		Bvertax j = que.front(); //  queue의 front를 j 클래스로 지정
		que.pop(); // front를 pop
		visited[j.getver()] = true; // j의 정점을 true
		for (i = 0; i <= n; i++) {
			if (map[j.getver()][i] == 1 && visited[i] == false) { 
				//map 배열을 통해 두개의 배열이 연결되어 있으며, 방문 하지 않은 정점일 경우,
				Bvertax tmp(i, j.getver()); // map 배열의 i를 새로운 정점으로, j.getver()는 from으로 tmp에 저장한다.
				que.push(tmp); //tmp를 queue에 삽입
				cout << j.getver() << " - " << i << endl; // j.getver()에서 i로 연결을 출력한다.
				visited[i] = true; // 방문하였으므로 true
			}
		}
	}
}

class Dvertax { //DFS
private:
	int ver; // 정점
	int from = -1; // 정점이 어디로부터 오는지 확인할 변수
public:
	Dvertax(int v, int f) { // 생성자
		ver = v;
		from = f;
	}
	int getver() {
		return ver;
	}
	void DFS(int **map, int start, int n);
};


void Dvertax::DFS(int **map, int start, int n) {
	bool *visited = new bool[n + 1];
	int i;
	for (i = 0; i <= n; i++) {
		visited[i] = false;
	} // visited를 false로 초기화
	Dvertax st(start, -1); //start로 시작하며, from은 -1이다.
	stack<Dvertax> sta; // stack을 생성
	sta.push(st); // stack에 st를 push
	while (!sta.empty()) { // stack이 빌 때까지 반복
		Dvertax j = sta.top(); // j 에 stack의 top을 저장
		sta.pop(); // top을 pop
		if (visited[j.getver()] == false) { 
			// BFS와는 다르게 stack을 이용해서 나중에 들어온 값이 먼저 나가게 된다.
			// 따라서 한번 거쳐간 정점을 다시 출력하지 않도록 visited배열이 false인지 확인을 한다.
			visited[j.getver()] = true; // visited배열을 true
			cout << j.from << " - " << j.ver << endl;
			// stack을 이용하여 위에서부터 나온 값을 확인하기에 아래 if문 안에서 출력하는 것이 아니라
			// 현재 위치에서 출력을 한다.
			for (i = 0; i <= n; i++) {
				if (map[j.getver()][i] == 1 && visited[i] == false) {
				    // map배열을 이용해 두개의 정점이 연결되어 있는지 확인하며, 방문을 하지 않은 정점인지 확인
					Dvertax tmp(i, j.getver()); //tmp에 i의 정점, from에 전에 온 정점을 넣어준다.
					sta.push(tmp); // tmp를 stack에 push
				}
			}
		}
	}
}


int main() {
	int start, v1, v2, num,i;
	cout << "12141668 김권중" << endl;
	cout << "정점의 갯수를 입력 : ";
	cin >> num;
	int **map = new int*[num + 1];
	for (i = 0; i <= num; i++) {
		map[i] = new int[num + 1];
	}
	cout << "시작할 정점의 위치 : ";
	cin >> start;
	Bvertax a(start, -1);
	Dvertax b(start, -1);
	cout << "정점 사이의 간선을 입력" << endl;
	for (;;) {
		cin >> v1 >> v2;
		if (v1 == -1 || v2 == -1) break;
		map[v1][v2] = 1; // 방향성이 없기에 map[v1][v2]=map[v2][v1]이다.
		map[v2][v1] = 1;
	} // 두개의 정점 중 -1이 입력이 되면, 더 이상의 간선이 없는 걸로 간주.
	cout << "BFS를 통한 그래프 해석" << endl;
	a.BFS(map, start, num);
	cout << endl;
	cout << "DFS를 통한 그래프 해석" << endl;
	b.DFS(map, start, num);
	return 0;
}