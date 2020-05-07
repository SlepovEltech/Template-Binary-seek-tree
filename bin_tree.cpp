#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;
 
const int N = 10;
const int SSIZE = 80;

template<typename T> 
string to_string(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

//Class of tree Node with template data
template <typename Type>
struct Node{
public:
	Node* parent;
	Node* left;
	Node* right;	
	Type data; 
	Node() : parent(this), left(NULL), right(NULL) {}
	Node(Type value) : data(value), parent(NULL), left(NULL), right(NULL) {}
	Node(Node* parent, Type value): 
		parent(parent), left(NULL), right(NULL), data(value) {}
	
};

template <typename Type>
class BinTree {
	private:
		Node <Type> *root;
		int offset,maxrow;
		char **SCREEN;
	public:
		BinTree(Type *input);
		~BinTree() {}
		bool Empty();
		void Insert(Type value);
		void OutNodes(Node <Type> *v, int r, int c);
		void OutTree();
		void clrscr();
		Node<Type> *getNodeByValue(Type value);
		Node<Type> *findMaxNode(Node<Type> *root);
		void deleteNode(Node<Type> *target);
		void deleteNode(Type value);
		Type getMin();
		Type getMax();
		Node<Type> *getRoot();
		void preorderTravel(Node<Type> *cur); //aka previos
		

};


int main()
{
	//string a[N] = {"bob", "alice","vera","valens","ugin","sasha","george", "qar","artem"};
	//char a[N] = {'b', 'a','u','s','o', 'g','w','m', 'q'};
	int a[N] = {8, 3, 1, 6, 4,7, 10,6, 14, 13}; 
	BinTree <int> tree(a);
	/*tree.OutTree();
	tree.Insert(9);
	tree.OutTree();*/
	tree.deleteNode(10);
	tree.OutTree();
	tree.preorderTravel(tree.getRoot());
	cout<<endl;
	return 0;
}


template <typename Type>
BinTree<Type> :: BinTree(Type *input)
{
	maxrow = 8;
	offset = 40;
	SCREEN = new char *[maxrow];
	for(int i = 0; i < maxrow; i++)
		SCREEN[i] = new char[SSIZE];

	root = new Node<Type>(input[0]);
	for(int i = 1; i < N; i++)
		Insert(input[i]);
}
template <typename Type>
bool BinTree<Type> :: Empty() 
{
	return ((root->left == NULL) && (root->right == NULL));
}
template <typename Type>
void BinTree<Type> :: Insert(Type value) 
{
	Node <Type> *current = root;
	while(current)
	{
		if(value > current->data)
			if(current->right)
				current = current->right;
			else
				current->right = new Node<Type>(current, value);
		else 
			if(value < current->data)
				if(current->left)
					current = current->left;
				else 
					current->left = new Node<Type>(current, value);
			else //Eliminate repetitions if root==insert
				current = NULL;
	}

}
template <typename Type>
void BinTree<Type> :: OutNodes(Node <Type> *v, int r, int c)
{
	char res[10];
	if(r && c && (c < SSIZE)) 
	{
		string strData = to_string(v->data);
		int n = strData.length();
		for(int i = 0; i < n; i++)
			SCREEN[r-1][c-n/2-1+i] = strData[i];
	}
	if(r < maxrow)
	{
		if(v->left) OutNodes(v->left, r+1, c-(offset >> r));
		if(v->right) OutNodes(v->right, r+1, c+(offset >> r));

	}
}
template <typename Type>
void BinTree<Type> :: OutTree()
{
	clrscr();
	if(root)
	{
		OutNodes(root,1,offset);
		for(int i = 0; i < maxrow; i++)
		{
			SCREEN[i][SSIZE-1] = 0;
			cout << '\n' << SCREEN[i];
		}
		cout << '\n';	
	}
	
}
template <typename Type>
void BinTree<Type> :: clrscr()
{
	for(int i = 0; i < maxrow; i++)
		memset(SCREEN[i], ' ', SSIZE);	
}

template <typename Type>
Node<Type>* BinTree<Type> :: getNodeByValue(Type value) 
{
	Node<Type> *tmp = root;
	while (tmp) 
	{
		if (tmp->data > value) 
    		tmp = tmp->left;
		else 
			if(tmp->data < value) 
    			tmp = tmp->right;
			else 
    			return tmp;
	}
	return NULL;
}	
template <typename Type>
Node<Type>* BinTree<Type> ::findMaxNode(Node<Type> *root)
{
	Node <Type> *tmp = root;
	while (tmp->right) 
    	tmp = tmp->right;
	return tmp;
}
template <typename Type>
void BinTree<Type> :: deleteNode(Node<Type> *target) {
if (target->left && target->right) {
    Node<Type> *localMax = findMaxNode(target->left);
    target->data = localMax->data;
    deleteNode(localMax);
    return;
} else if (target->left) {
    if (target == target->parent->left) {
        target->parent->left = target->left;
    } else {
        target->parent->right = target->left;
    }
} else if (target->right) {
    if (target == target->parent->right) {
        target->parent->right = target->right;
    } else {
        target->parent->left = target->right;
    }
} else {
    if (target == target->parent->left) {
        target->parent->left = NULL;
    } else {
        target->parent->right = NULL;
    }
}
delete target;
}
template <typename Type>
void BinTree<Type> :: deleteNode(Type value) 
{
    Node<Type> *target = getNodeByValue(value);
    deleteNode(target);
}

template <typename Type>
Type BinTree<Type> :: getMin()
{
	Node <Type> *tmp = root;
	while (tmp->left) 
    	tmp = tmp->left;
	return tmp->data;
}

template <typename Type>
Type BinTree<Type> ::getMax()
{
	Node <Type> *tmp = root;
	while (tmp->right) 
    	tmp = tmp->right;
	return tmp->data;
}

template <typename Type>
Node<Type>* BinTree<Type>::getRoot()
{
	return root;
}
template <typename Type>
void BinTree<Type> :: preorderTravel(Node<Type> *cur) //aka previos
{
	if(cur)
	{
		cout << cur->data<< " ";
		preorderTravel(cur->left);
		preorderTravel(cur->right);
	}
}	 


