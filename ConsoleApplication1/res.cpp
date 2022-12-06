#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;


struct Data
{
		int clas;
		int groupCode;
		string surname;
		int receiptDay;
		int mount;
		int year;
		int numberRecordBook;
		string subject;
		int markOfSubject;
};


struct Node
{
		Data data;
		Node *next;
};


struct List
{
		Node *first;			
		Node *last;				
};


List init_list()
{
		List list;			
		list.first = nullptr;
		list.last = nullptr;

		return list;
}


void insert_end(List * list, const Data &data)
{
		if (list->last == nullptr)
		{
				list->first = new Node(); 
				list->first->data = data;
				list->last = list->first;
				list->last->next = nullptr;
		}
		else
		{
				Node* x = new Node();
				x->data = data;
				x->next = nullptr;
				list->last->next = x;
				list->last = x;
		}
}


int length(List* list)
{
	int count = 0;
		if (list->first)
		{
				count++;
				Node * current = list->first;
				while (true)
				{
						current = current->next;
						if (current == nullptr) 
						{ 
								return count; 
						}
						count++;
				}
		}
		return count;
}


void print(List *list) {
		int sizeOfList = length(list);
		if (sizeOfList == 0) 
		{cout << "Список пуст";}
		else
		{
				Node* current = list->first;
				while(current != nullptr)
				{
						cout << " Текущая фамилия" << current->data.surname << '\n';
						current = current->next;
						sizeOfList--;
				}
		}
}


struct BinaryTreeNode{
		Data data;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
		~BinaryTreeNode(){
			cout<<"Удаление узла"<<endl;
		};
};


void Delete_BinaryTree(BinaryTreeNode *&Node) {
  if (Node != nullptr) {
    Delete_BinaryTree(Node->left);
    Delete_BinaryTree(Node->right);
    delete(Node);
    return;
  }
}


void addOne(BinaryTreeNode* &tree, Data newData) {
		if (tree == nullptr) {
				tree = new BinaryTreeNode;
				tree->data = newData;
				// cout<<tree->data.numberRecordBook<<endl;
				tree->left = nullptr;
				tree->right = nullptr;
				return;
		} else if (newData.numberRecordBook < tree->data.numberRecordBook) {
				addOne(tree->left, newData);
		} else {
				addOne(tree->right, newData);
		}
}


void listToTree(BinaryTreeNode* tree, Node* head){
		if (head != nullptr){
				addOne(tree, head->data);
				head = head->next;
				while (head != nullptr){
						addOne(tree, head->data);
						head = head->next;
				}
		} 
}


void printTree(BinaryTreeNode * root, int space = 0) {
   	if (root == nullptr){
		 		for (int i = 0; i < space; i++){
						cout<<"  ";
				}
				cout<<"--"<<endl;
      	return;
		}
   	space += 2;
   	printTree(root->right, space);
  	for (int i = 2; i < space; ++i)
    		cout << "  ";

  	cout << root->data.numberRecordBook << endl;
  	printTree(root->left, space);
}


BinaryTreeNode* Find(BinaryTreeNode * root, int key)
{
		while (root != nullptr)
		{
				if (key < root->data.numberRecordBook) root = root->left;
				else if (key > root->data.numberRecordBook) root = root->right;
				else return root; // Не больше и не меньше - значит равно
		}
		return nullptr; // Не найдено
}


void remove(BinaryTreeNode*& root, int key){
		BinaryTreeNode* curr = root;
  	BinaryTreeNode* parent = nullptr;

		while (curr && curr->data.numberRecordBook != key)
		{
			parent = curr;
			if (curr->data.numberRecordBook > key)
				curr = curr->left;
			else
				curr = curr->right;
		}
		if (curr == nullptr)
			return;
		if (curr->left == nullptr)
		{
			if (parent && parent->left == curr)
				parent->left = curr->right;
			if (parent && parent->right == curr)
				parent->right = curr->right;
			delete curr;
			return;
		}
		if (curr->right == nullptr)
		{

			if (parent && parent->left == curr)
				parent->left = curr->left;
			if (parent && parent->right == curr)
				parent->right = curr->left;
			delete curr;
			return;
		}
		BinaryTreeNode* child = curr->right;
  	while (child->left)
    	child = child->left;
		Data child_value = child->data;
		remove(root, child_value.numberRecordBook);
		curr->data = child_value;
}


void postorderPrint(BinaryTreeNode *root)
{
    if (root == nullptr)   // Базовый случай
    {
       return;
    }
    postorderPrint(root->left);   //рекурсивный вызов левого поддерева
    postorderPrint(root->right);  //рекурсивный вызов правого поддерева
    cout << root->data.numberRecordBook << " ";
}


int main() {
	int clas;				
	int groupCode;			
	string surname;			
	int receiptDay;		
	int mount;
	int year;
	int numberRecordBook;	
	string subject;			
	int markOfSubject;		

	List my_list = init_list();

	ifstream loadData;		
	loadData.open("list_data.txt");
	if (!loadData) { cout << "Error of file opening"; }
	else
	{
		while (!loadData.eof())
		{
			loadData >> clas >> groupCode >> surname >> receiptDay >> mount >> year >> numberRecordBook >> subject >> markOfSubject;

			Data current = { clas, groupCode, surname, receiptDay, mount, year, numberRecordBook, subject, markOfSubject };
			insert_end(&my_list, current);
			
		}
		loadData.close();
	}


	Data test3 = {2, 121, "Iskhakov", 23, 9, 2021, 1, "Math", 5};
	Data test4 = {2, 121, "Petrov", 23, 9, 2021, 10, "Math", 5};
	Data test5 = {2, 121, "Zverev", 23, 9, 2021, 20, "Math", 5};
	Data test6 = {2, 121, "Wild", 23, 9, 2021, 141, "Math", 5};
	Data test7 = {2, 121, "Smith", 23, 9, 2021, 9, "Math", 5};
	Data test8 = {2, 121, "Pavlov", 23, 9, 2021, 11, "Math", 5};

	BinaryTreeNode *tree = nullptr;

	// преобразование из листа
	addOne(tree, my_list.first->data);	
	listToTree(tree, my_list.first->next);

	cout << '\n' << endl;
	cout << '\n' << endl;

	cout << "-----Исходное дерево------" << endl;
	//вывод дерева
	printTree(tree);
	cout << '\n' << endl;
	cout << '\n' << endl;

	cout << "-----Добавление новых узлов------" << endl;
	//добавление новых
	addOne(tree, test3);
	addOne(tree, test4);
	addOne(tree, test5);
	addOne(tree, test6);
	addOne(tree, test7);

	printTree(tree);	
	cout << '\n' << endl;
	cout << '\n' << endl;

	cout << "-----Удаление узла с ключом 10------" << endl;
	remove(tree, 140);
	printTree(tree);

	cout << "-----Поиск узла по ключу------" << endl;
	cout << Find(tree, 20)->data.surname<< endl;

	cout << '\n' << endl;
	cout << '\n' << endl;		
	cout << "-----Обход в глубину------" << endl;
	postorderPrint(tree);
	cout << '\n' << endl;
	cout << '\n' << endl;

	Delete_BinaryTree(tree);
	return 0;
}
