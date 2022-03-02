#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int vertaxnum, line;

class Edge {  // Edge
private:
	int ver; // ���� ��ġ�� ����
	int from = -1; // ���� �ܰ��� ���� ���������� �� ������ -1
	int wei = 0; //������ ����
public:
	friend class Prim;
	friend class comp;
	Edge(int v, int f) { // ������
		ver = v;
		from = f;
	}
};
class comp { // priority queue�� �񱳸� ���� ������ �����ε��� ���� Ŭ����
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
	}// visited �迭�� false�� �ʱ�ȭ 
	Edge st(start, -1); // start������ st�� ����
	priority_queue<Edge,vector<Edge>,comp> q; // priority_queue�� �̿��ϱ����� ����, comp class�� �̿��� ��
	q.push(st); // st�� q�� push
	while (!q.empty()) {
		Edge a = q.top(); // q�� top�� Edge�� ����
		q.pop(); //q�� pop
		if (visited[a.ver] == true) {
			continue;
		} // �ش� ������ �湮�� ���� ���, ��ŵ
		visited[a.ver] = true; // visited�� true
		cout << a.from << " - " << a.ver << " weight : " << a.wei << endl; // �����ܰ��� ����, ���� ����, ���Ը� ���
		vertaxwei = vertaxwei + a.wei; // ������ �� ���Ը� ���ϱ� ���� vertaxwei�� ����
		for (i = 1; i <= vertaxnum; i++) {
			if (map[a.ver][i] == 1 && visited[i] == false) { //������ ����Ǿ�������, �������� ���� ����
				Edge e(i, a.ver); // ���ο� Edge�� ����
				e.wei = weight[a.ver][i]; // ������ ���Դ� �̾��� ���� ����
				q.push(e); // q�� push
			}
		}
	}
	cout << "������ �� weigt : " << vertaxwei << endl;
}
int main() {
	int i, j, v, f, w, start;
	cout << "������ ���� �Է� : ";
	cin >> vertaxnum; // ������ ������ ������ ������ �Է�
	cout << "������ ���� �Է� : ";
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
	} // map�� weight�� 0���� �ʱ�ȭ
	cout << "������ ������ �Է� : " << endl;
	for (i = 0; i < line; i++) {
		cin >> v >> f >> w; // ���� ������ ���� ���� ������ ���Ը� �Է�
		map[v][f] = map[f][v] = 1; // ���� ������ ���� ������ ������ �Ǹ� 1
		weight[v][f] = weight[f][v] = w; // ���� �Է�
	}
	Prim p;
	cout << "������ ������ ��ġ�� �Է� : ";
	cin >> start;
	p.prim(map, weight, start);
}