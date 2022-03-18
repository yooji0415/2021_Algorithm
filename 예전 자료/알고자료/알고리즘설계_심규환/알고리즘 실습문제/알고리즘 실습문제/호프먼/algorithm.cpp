#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct node
{


	node * leftChild;
	node * rightChild;
	double frequency;
	string content;
	string code;


};
//class Vector {
//private:
//	string  arr;
//public:
//	Vector();
//	string begin();
//	void end();
//	void erase();
//	string push_back(node &a);
//	
//};
//Vector::Vector() {
//	arr = { 0 };
//}
//string Vector::begin() {
//	return arr.begin();
//}
//
//string Vector::end() {
//	return arr.end();
// } vector 사용으로 시간이 부족하여 완성할 수 없었습니다... 아랫부분을 실행시킬 경우 각 단어의 이진 비트까지 출력을 해보았습니다.



vector<node> nodeArray;



node  extractMin()
{
	double temp = (double)INT_MAX;
	vector<node>::iterator i1, pos;
	for (i1 = nodeArray.begin(); i1 != nodeArray.end(); i1++)
	{

		if (temp>(*i1).frequency)
		{
			pos = i1;
			temp = (*i1).frequency;
		}
	}

	node tempNode = (*pos);
	nodeArray.erase(pos);



	return tempNode;
}



node getHuffmanTree()
{
	while (!nodeArray.empty())
	{


		node * tempNode = new node;
		node * tempNode1 = new node;
		node * tempNode2 = new node;
		*tempNode1 = extractMin();
		*tempNode2 = extractMin();


		tempNode->leftChild = tempNode1;
		tempNode->rightChild = tempNode2;
		tempNode->frequency = tempNode1->frequency + tempNode2->frequency;
		nodeArray.push_back(*tempNode);
		if (nodeArray.size() == 1)
		{
			break;
		}
	}
	return nodeArray[0];
}


void BFS(node * temproot, string s)
{
	
	node * root1 = new node;
	root1 = temproot;

	root1->code = s;
	if (root1 == NULL)
	{

	}
	else if (root1->leftChild == NULL && root1->rightChild == NULL)
	{

		cout << "the content is " << root1->content << endl;
		cout << "and its corresponding code is " << root1->code << endl;  
		// 각 단어의 카운트 세는 것을 보여주기 위하여 넣어주었습니다.

	}
	else
	{

		root1->leftChild->code = s.append("0");
		s.erase(s.end() - 1);
		root1->rightChild->code = s.append("1");
		s.erase(s.end() - 1);


		BFS(root1->leftChild, s.append("0"));
		s.erase(s.end() - 1);
		BFS(root1->rightChild, s.append("1"));
		s.erase(s.end() - 1);
	}

}


void getHuffmanCode()
{
	int size, i, j;
	double tempDouble;
	string tempString;
	string tempchar = "";
	int stringnum[26] = { 0 };
	cin >> tempString;
	size= tempString.size();
	for (i = 0; i < size; i++) {
		for (j = 0; j < 26; j++) {
			if (tempString[i] == 97 + j) {
				stringnum[j]++;
			}
		}
	}
	int total = 0;
	for (i = 0; i < 26; i++) {
		if (stringnum[i] != 0) {
			total++;
		}
	}

	node tempNode;

	for (j = 0; j < 26; j++) {
		if (stringnum[j] != 0) {
			tempchar = 97 + j;
			tempDouble = stringnum[j];

			tempNode.frequency = tempDouble;
			tempNode.content = tempchar;
			tempNode.leftChild = NULL;
			tempNode.rightChild = NULL;
			nodeArray.push_back(tempNode);
		}
	}
	node root = getHuffmanTree();

	BFS(&root, "");

}

int main()
{
	getHuffmanCode();
	return 0;
}