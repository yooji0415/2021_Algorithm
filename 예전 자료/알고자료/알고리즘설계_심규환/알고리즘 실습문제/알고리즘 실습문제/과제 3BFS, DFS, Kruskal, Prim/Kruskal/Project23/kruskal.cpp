#include<iostream>
#include<vector>
using namespace std;

int vertaxnum, line;

int *parent = new int[vertaxnum]; // parent�迭, �������� �������� �����ֱ� ���� �迭�̴�.


class Edge { // ������ �����ϱ� ���� Edge class
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
	} // ������
};

class Kruskal { // kruskal �˰����� �����ϱ� ���� class
public:
	friend class Edge;
	void selectionsort(vector<Edge> &a); // weight�� ������������ �����ϱ� ���� selection sort
	void kruskal(vector<Edge> &a);
	int find(int x); 
	void merge( int x, int y);
};
void Kruskal::kruskal(vector<Edge> &a) {
	int i,weight=0;
	int s = a.size();
	selectionsort(a); // �Է¹��� Edge�� ���Ը� ������������ ������
	for (i = 0; i < s; i++) {
		Edge e = a.at(i); // vector ���� Edge�� ���ο� Edge�� ����
		int x = find(e.ver1); // ver1�� ���� ������ x�� ����
		int y = find(e.ver2); // ver2�� ���� ������ y�� ����
		if (x != y) { // x�� y�� ���� �ʴٸ�, �ΰ��� ������ ������ ����Ǿ� ���� �ʴ´ٴ� ���� �ǹ�
			merge(x, y); // �ΰ��� ������ �����Ͽ�, �ΰ��� ������ �ϳ��� ��ģ��.
			cout << e.ver1 << " - " << e.ver2 << endl; // ���� ���� �� ���� ���
			weight = weight + e.wei; // �׷����� �� ���Ը� ����ϱ� ���� weight�� �����ش�.
		}
	}
	cout << "������ �� ���� : " << weight << endl; // weight ���
}
int Kruskal::find(int x) { //������ ���� ã�ư� ���� ��ȯ���ش�.
	if (x == parent[x]) { //x���� parent�迭��[x]�������� ���� ���� ���  x�� return
		return x;
	}
	else {
		return parent[x] = find(parent[x]); // ���� �ٸ� ��� ��͸� �̿��Ͽ� parent[x]�� ��ȯ���ش�.
	}
}
void Kruskal::merge(int x, int y) { // �� ������ �ϳ��� ������ �������� �����ֱ� ���� merge
	x = find(x); // find(x)�� x�� ����
	y = find(y); // find(y)�� y�� ����
	parent[x] = y; //parent[x]�� y�� �����Ͽ�, �ϳ��� ���� �������� ������ش�.
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
	cout << "�й� :12141668 �̸� : �����" << endl;
	cout << "������ ���� : ";
	cin >> vertaxnum;
	cout << "������ ���� : ";
	cin >> line;
	for (i = 1; i <= vertaxnum; i++) {
		parent[i] = i;
	} // parent�迭�� ���� ������ �ʱ�ȭ�Ѵ�.
	vector<Edge> a;
	cout << "���� ���� �Է� : " << endl;
	for (i=0;i<line;i++) {
		cin >> v1 >> v2 >> w;
		Edge v(v1, v2, w);
		a.push_back(v);
	}
	cout << endl;
	Kruskal k;
	cout << "���� �� ���� : " << endl;
	k.kruskal(a);
	return 0;
}