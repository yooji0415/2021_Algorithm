#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Bvertax {  //BFS 
private:
	int ver; //����
	int from = -1; // ������ ��� �������κ��� ������ Ȯ��, -1�� �ʱ�ȭ
public:
	Bvertax(int v, int f) {  // ������
		ver = v;
		from = f;
	}
	int getver() { // ������ ���
		return ver;
	}
	void BFS(int **map, int start, int n);
};

void Bvertax ::BFS(int **map, int start,int n) {
	int i;
	bool *visited = new bool[n+1];
	for (i = 0; i <= n; i++) {
		visited[i] = false;
	} // visited�迭�̸� false�� �ʱ�ȭ
	Bvertax st(start, -1); // �Ű������� �Էµ� start�� ���� �����ϱ� ���� �Ͽ�����, ���� �����̱⿡ from -1 �̴�.
	visited[st.getver()] = true; //visited �迭�� start�� true
	queue<Bvertax> que; // queue ����
	que.push(st); // start�� ������� Ŭ������ queue�� push
	while (!que.empty()) { // queue�� �� �� ���� while���� ���
		Bvertax j = que.front(); //  queue�� front�� j Ŭ������ ����
		que.pop(); // front�� pop
		visited[j.getver()] = true; // j�� ������ true
		for (i = 0; i <= n; i++) {
			if (map[j.getver()][i] == 1 && visited[i] == false) { 
				//map �迭�� ���� �ΰ��� �迭�� ����Ǿ� ������, �湮 ���� ���� ������ ���,
				Bvertax tmp(i, j.getver()); // map �迭�� i�� ���ο� ��������, j.getver()�� from���� tmp�� �����Ѵ�.
				que.push(tmp); //tmp�� queue�� ����
				cout << j.getver() << " - " << i << endl; // j.getver()���� i�� ������ ����Ѵ�.
				visited[i] = true; // �湮�Ͽ����Ƿ� true
			}
		}
	}
}

class Dvertax { //DFS
private:
	int ver; // ����
	int from = -1; // ������ ���κ��� ������ Ȯ���� ����
public:
	Dvertax(int v, int f) { // ������
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
	} // visited�� false�� �ʱ�ȭ
	Dvertax st(start, -1); //start�� �����ϸ�, from�� -1�̴�.
	stack<Dvertax> sta; // stack�� ����
	sta.push(st); // stack�� st�� push
	while (!sta.empty()) { // stack�� �� ������ �ݺ�
		Dvertax j = sta.top(); // j �� stack�� top�� ����
		sta.pop(); // top�� pop
		if (visited[j.getver()] == false) { 
			// BFS�ʹ� �ٸ��� stack�� �̿��ؼ� ���߿� ���� ���� ���� ������ �ȴ�.
			// ���� �ѹ� ���İ� ������ �ٽ� ������� �ʵ��� visited�迭�� false���� Ȯ���� �Ѵ�.
			visited[j.getver()] = true; // visited�迭�� true
			cout << j.from << " - " << j.ver << endl;
			// stack�� �̿��Ͽ� ���������� ���� ���� Ȯ���ϱ⿡ �Ʒ� if�� �ȿ��� ����ϴ� ���� �ƴ϶�
			// ���� ��ġ���� ����� �Ѵ�.
			for (i = 0; i <= n; i++) {
				if (map[j.getver()][i] == 1 && visited[i] == false) {
				    // map�迭�� �̿��� �ΰ��� ������ ����Ǿ� �ִ��� Ȯ���ϸ�, �湮�� ���� ���� �������� Ȯ��
					Dvertax tmp(i, j.getver()); //tmp�� i�� ����, from�� ���� �� ������ �־��ش�.
					sta.push(tmp); // tmp�� stack�� push
				}
			}
		}
	}
}


int main() {
	int start, v1, v2, num,i;
	cout << "12141668 �����" << endl;
	cout << "������ ������ �Է� : ";
	cin >> num;
	int **map = new int*[num + 1];
	for (i = 0; i <= num; i++) {
		map[i] = new int[num + 1];
	}
	cout << "������ ������ ��ġ : ";
	cin >> start;
	Bvertax a(start, -1);
	Dvertax b(start, -1);
	cout << "���� ������ ������ �Է�" << endl;
	for (;;) {
		cin >> v1 >> v2;
		if (v1 == -1 || v2 == -1) break;
		map[v1][v2] = 1; // ���⼺�� ���⿡ map[v1][v2]=map[v2][v1]�̴�.
		map[v2][v1] = 1;
	} // �ΰ��� ���� �� -1�� �Է��� �Ǹ�, �� �̻��� ������ ���� �ɷ� ����.
	cout << "BFS�� ���� �׷��� �ؼ�" << endl;
	a.BFS(map, start, num);
	cout << endl;
	cout << "DFS�� ���� �׷��� �ؼ�" << endl;
	b.DFS(map, start, num);
	return 0;
}