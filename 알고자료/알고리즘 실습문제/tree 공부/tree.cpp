#include<iostream>
using namespace std;
#define null 0

template<typename T>
class Tree;

template<typename T>
class TreeNode{
	friend class Tree<T>;
private:
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;
	T data;
public:
	TreeNode(T data=0, TreeNode* left = NULL, TreeNode* right = NULL){
		this->data=data;
		this->left=left;
		this->right=right;
	}
	/*friend ostream& operator<<(ostream& os,const TreeNode<T>& node){
	os<<"[data] "<<node.data<<endl;
	if(node.left != NULL){
	os<<"[left] "<<node.left->data<<endl;
	}
	if(node.right != NULL){
	os<<"[right] " << node.right->data<<endl;
	}
	return os;
	}*/
};

template<typename T>
class Tree{
private:
	TreeNode<T>* root;
public:
	Tree(T data){
		/*root = new TreeNode<T>(data);*/
	}
	TreeNode<T>* search(TreeNode<T>* current, T data){
		if(current==null) return null;
		if(data == current->data){
			return current;
		}else if(data < current->data){
			search(current->left,data);
		}else{
			search(current->right,data);
		}
	}
	void InsertNode(TreeNode<T>* node){
		if(search(root,node->data)==null){
			TreeNode<T>* parent = null;
			TreeNode<T>* current = root;
			while(current != null){
				parent = current;
				if(node->data < parent->data){
					current = current -> left;
				}
				else{
					current = current -> right;
				}
			}
			if(node->data<parent->data){
				parent->left = node;
			}
			else{
				parent->right = node;
			}
		}
	}
	TreeNode<T>* getRoot(){
		return root;
	}
	void Inorder(TreeNode<T>* current){
		if(current == null)return;
		Inorder(current->left);
		visit(current);
		Inorder(current->right);

	}
	void Preorder(TreeNode<T>* current){
		if(current == null)return;
		visit(current);
		Preorder(current->left);
		Preorder(current->right);

	}
	void Postorder(TreeNode<T>* current){
		if(current == null)return;
		Postorder(current->left);
		Postorder(current->right);
		visit(current);

	}
	void visit(TreeNode<T>* current){
		cout<<current->data<<" ";
	}
	//TreeNode<T>* removeNode(TreeNode<T>* current, int data){
	//	TreeNode<T>* tempNode;

	//	if(current==NULL)printf("null");
	//	else if(current->data > data){
	//		current->left = removeNode(current->left,data);
	//	}else if(current->data < data){
	//		current->right = removeNode(current->right,data);
	//	}
	//	else{
	//		if(current->left != NULL &&  current->right != NULL){
	//			tempNode = findMinNode(current->right);
	//			current->data = tempNode->data;
	//			current->right=removeNode(current->right, tempNode->data);
	//		}
	//		else{
	//			tempNode = current;

	//			if(current->left == NULL){
	//				current=current->right;
	//			}else if(current->right == NULL){
	//				current=current->left;
	//			}
	//			delete tempNode;

	//			return current;

	//		}
	//	}
	//}
	TreeNode<T>* findMinNode(TreeNode<T>* current){
		if(current == NULL) return NULL;
		if(current->left != NULL) return findMinNode(current->left);
		else return current;
	}
};



int main(){
	Tree<int> tree();
	int num,i;
	for(i=0;i<8;i++){
		cin>>num;
		tree.InsertNode(new TreeNode<int>(num));
	}

	

	tree.Inorder(tree.getRoot());

	/*tree.Postorder(tree.getRoot());*/

}