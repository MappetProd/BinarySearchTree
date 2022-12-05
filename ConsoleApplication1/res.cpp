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
		int key;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
		int numberOfNodes;
};


BinaryTreeNode* get(BinaryTreeNode* currentTree, int key) {
		if (currentTree == nullptr) return nullptr;
		if (key < currentTree->key) return get(currentTree->left, key);
		else if (key > currentTree->key) return get(currentTree->right, key);
		else return currentTree;
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


void dump3(BinaryTreeNode * root, int space = 0) {
   if (!root)
      return;
   enum { COUNT = 2 };
   space += COUNT;
   dump3(root->right, space);
   for (int i = COUNT; i < space; ++i)
      cout << "  ";
   cout << root->data.numberRecordBook << endl;
   dump3(root->left, space);
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


BinaryTreeNode* FindParent(BinaryTreeNode * root, int key)
{
		while (root != nullptr)
		{
				if (root->right->data.numberRecordBook == key ||  root->left->data.numberRecordBook == key) return root;
				else if (key >= root->data.numberRecordBook) root = root->right;
				else root = root->left; // Не больше и не меньше - значит равно
		}
		return nullptr; // Не найдено
}


void Remove(BinaryTreeNode * &root, BinaryTreeNode *current)
{		
		if (root->data.numberRecordBook == current->data.numberRecordBook){
						
				if (root == nullptr) return;
				else if (root->left == nullptr){
						delete root;
						root = root->right;
						return;
				} else if (root->right == nullptr){
						delete root;
						root = root->left;
						return;
				} else {
						BinaryTreeNode* child = current->left;
						while (child->right != nullptr)
						child = child->right;
						Data vl = child->data;
						Remove(root, child);
						root->data = vl;
						return;
				}
		}

		BinaryTreeNode *parent = FindParent(root, current->data.numberRecordBook);
		if (current == nullptr)
		return;
		
		if (current->left == nullptr) // Нет левого ребёнка
		{
				// Заменяем удаляемый элемент на правого ребёнка
				if (parent->data.numberRecordBook >= current->data.numberRecordBook ){
						parent->left = current->right;
				} else {
						parent->right = current->right;
				}
				delete current;
		}
		else if (current->right == nullptr) // Нет правого ребёнка
		{
				// Заменяем удаляемый элемент на левого ребёнка
				if (parent->data.numberRecordBook >= current->data.numberRecordBook ){
						parent->left = current->left;
				} else {
						parent->right = current->left;
				}
				delete current;
		}
		else // Удаляем узел с обеими детьми
		{		
				// Ищем самый правый элемент левого поддерева
				BinaryTreeNode* child = current->left;
				while (child->right != nullptr)
				child = child->right;
				Data vl = child->data;
				// Заменяем удаляемый элемент на найденный
				if (parent->data.numberRecordBook >= current->data.numberRecordBook ){
						Remove(root, child); //сначала удаляем этот элемент, только потом меняем значения
						parent->left->data = vl;
				} else {
						Remove(root, child);
						parent->right->data = vl;
				}	
		}
}


void postorderPrint(BinaryTreeNode *root)
{
    if (root == NULL)   // Базовый случай
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

	// cout << "Фамилии:\n";
	// print(&my_list);
	// cout << '\n' << endl;

	Data test3 = {2, 121, "Iskhakov", 23, 9, 2021, 1, "Math", 5};
	Data test4 = {2, 121, "Iskhakov", 23, 9, 2021, 10, "Math", 5};
	Data test5 = {2, 121, "Iskhakov", 23, 9, 2021, 20, "Math", 5};
	Data test6 = {2, 121, "Iskhakov", 23, 9, 2021, 141, "Math", 5};
	Data test7 = {2, 121, "Iskhakov", 23, 9, 2021, 9, "Math", 5};
	Data test8 = {2, 121, "Iskhakov", 23, 9, 2021, 11, "Math", 5};

	BinaryTreeNode *tree = nullptr;

	// преобразование из листа
	addOne(tree, my_list.first->data);	
	listToTree(tree, my_list.first->next);

	//вывод дерева
	dump3(tree);
	cout << '\n' << endl;
	cout << '\n' << endl;

	//добавление новых
	addOne(tree, test3);
	addOne(tree, test4);
	addOne(tree, test5);
	addOne(tree, test6);
	addOne(tree, test7);
	// addOne(tree, test8);

	dump3(tree);	
	cout << '\n' << endl;
	cout << '\n' << endl;

	Remove(tree, Find(tree, 145));
	
	dump3(tree);		


	postorderPrint(tree);
	return 0;
}
