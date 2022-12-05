#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale.h>

using namespace std;

struct Data
{
	int clas;				// курс
	int groupCode;			// код группы
	string surname;			// фамилия
	int receiptDay;			// дата поступления
	int mount;
	int year;
	int numberRecordBook;	// номер зачет книжки
	string subject;			// дисциплина
	int markOfSubject;		// оценка за экзамен по дисциплине

	Data(){}

	Data(int _clas, int _groupCode, string _surname, int _receiptDay, int _mount, int _year, int _numberRecordBook, string _subject, int _markOfSubject) {
		clas = _clas;
		groupCode = _groupCode;
		surname = _surname;
		receiptDay = _receiptDay;
		mount = _mount;
		year = _year;
		numberRecordBook = _numberRecordBook;
		subject = _subject;
		markOfSubject = _markOfSubject;
	}
};

struct Node
{
	Data data;				// значение элемента списка
	Node* next;				// указатель на следующий элемент списка
};

struct List
{
	Node* first;			// поле с указателем на первый узел списка
	Node* last;				// поле с указателем на последний узел списка

	~List()
	{
		cout << "Список удалён";
	}
};

//УЗЕЛ(ВЕРШИНА) БИНАРНОГО ДЕРЕВА
class BinaryTreeNode {
public:
	Data data;
	int key;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	int numberOfNodes;
	BinaryTreeNode(const Data& _data, int _numberOfNodes) {
		data = _data;
		key = data.numberRecordBook;
		numberOfNodes = _numberOfNodes;
		left = nullptr;
		right = nullptr;
	}
};

//КЛАСС БИНАРНОГО ДЕРЕВА ПОИСКА
class BinarySearchTree {
public:
	BinaryTreeNode* root; //корень бинарного дерева

	//ФУНКЦИЯ ОПРЕДЕЛЕНИЯ РАЗМЕРА ТЕКУЩЕГО ПОДДЕРЕВА
	int size(BinaryTreeNode* currentTreeNode) {
		if (currentTreeNode == nullptr) {
			return 0;
		}
		else {
			return currentTreeNode->numberOfNodes;
		}
	}

	//ФУНКЦИЯ ПОЛУЧЕНИЯ ЭЛЕМЕНТА ПО КЛЮЧУ
	BinaryTreeNode* get(BinaryTreeNode* currentTree, int key) {
		if (currentTree == nullptr) return nullptr;

		if (key < currentTree->key) return get(currentTree->left, key);
		else if (key > currentTree->key) return get(currentTree->right, key);
		else return currentTree;
	}

	//ВСТАВКА ЭЛЕМЕНТА В ДЕРЕВО
	BinaryTreeNode* put(BinaryTreeNode* currentTree, int key, const Data& data) {
		if (currentTree == nullptr) return new BinaryTreeNode(data, 1);
		if (key < currentTree->key) {
			currentTree->left = put(currentTree->left, key, data);
		}
		else if(key > currentTree->key) {
			currentTree->right = put(currentTree->right, key, data);
		}
		else {
			currentTree->data = data;
		}
		currentTree->numberOfNodes = size(currentTree->left) + size(currentTree->right) + 1;
		return currentTree;
	}
};

BinarySearchTree listToTree(Node* head) {
	BinarySearchTree tree = BinarySearchTree();
	tree.root = new BinaryTreeNode(head->data, 1);
	BinaryTreeNode* currentTree = tree.root;

	head = head->next;
	while (head != nullptr) {
		while (currentTree != nullptr) {
			if (head->data.numberRecordBook < currentTree->key) {
				if (currentTree->left == nullptr) {
					currentTree->left = new BinaryTreeNode(head->data, 1);
					currentTree = tree.root;
					break;
				}
				else {
					currentTree = currentTree->left;
				}
			}
			else {
				if (currentTree->right == nullptr) {
					currentTree->right = new BinaryTreeNode(head->data, 1);
					currentTree = tree.root;
					break;
				}
				else {
					currentTree = currentTree->right;
				}
			}
		}
		head = head->next;
	}
	return tree;
}

// ИНИЦИАЛИЗАЦИЯ списка
List init_list()
{
	List list;
	list.first = nullptr;
	list.last = nullptr;

	return list;
}

// ВЫВОД ----------------------------------------------------
void print(List* list)
{
	Node* current = list->first;
	int i;


	cout << "  ";									// вывод
	for (i = 0; i < 37; i++) { cout << '_'; }		// оформления
	cout << endl;
	cout << left << setw(12) << " | Фамилия" << setw(5) << "| № ЗК " << setw(7) << "| Курс" << "| Дата пост. |" << endl;

	cout << "  ";									// вывод
	for (i = 0; i < 37; i++) { cout << '_'; }			// оформления
	cout << endl;									// таблицы


	while (current != nullptr)
	{
		cout << " | ";

		cout << left << setw(9) << current->data.surname <<
			"| " << setw(5) << current->data.numberRecordBook <<
			"| " << setw(5) << current->data.clas <<
			"| " << setw(2) << current->data.receiptDay << " " << setw(2) << current->data.mount << " " << current->data.year;
		current = current->next;

		cout << " |\n";
	}


	cout << "  ";									// вывод
	for (i = 0; i < 37; i++) { cout << '_'; }		// оформления
	cout << endl;									// таблицы
}

void printLastName(List* list)
{
	Node* current = list->first;
	int i;

	cout << " | Фамилия  |" << endl;
	cout << "  ";									// вывод
	for (i = 0; i < 10; i++) { cout << '_'; }		// оформления
	cout << endl;

	while (current != nullptr)
	{
		cout << left << " | " << setw(9) << current->data.surname << "|" << '\n';
		current = current->next;
	}
}

void insert_end(List* list, const Data& data)
{
	if (list->last == nullptr) // если список пустой
	{
		list->first = new Node(); // Создаём в списке первый узел
		// Заполняем созданный узел полезными данными
		list->first->data = data;
		list->last = list->first; // Первый узел будет и последним
		// У последнего узла нет следующего узла
		list->last->next = nullptr;
	}
	else // Если список не пустой
	{
		Node* x = new Node(); // Создаём новый узел
		x->data = data; // Заполняем созданный узел полезными данными
		// Этот узел будет последним, без следующего узла
		x->next = nullptr;
		// Новый узел будет добавлен после последнего
		list->last->next = x;
		list->last = x; // Делаем созданный узел последним
	}
}

// ОЧИСТКА --------------------------------------------------------
void clear(List* list) {
	Node* node = list->first;
	while (node != nullptr) {		// По очереди удаляем все узлы списка
		Node* next = node->next;	// Эта переменная необходима, так как
		delete node;				// после удаления node node->next станет недоступен
		node = next;				// переход к следующему узлу
	}
	list->first = nullptr;
	list->last = nullptr;
} //O(n)

int main() {

	int clas;				// курс
	int groupCode;			// код группы
	string surname;			// фамилия
	int receiptDay;			// дата поступления
	int mount;
	int year;
	int numberRecordBook;	// номер зачет книжки
	string subject;			// дисциплина
	int markOfSubject;		// оценка за экзамен по дисциплине

	List my_list = init_list();

	ifstream loadData;		// загрузка данных в лист 
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

	print(&my_list);

	//ТЕСТОВОЕ ПРЕОБРАЗОВАНИЕ ИЗ СВЯЗНОГО СПИСКА В ДЕРЕВО ПОИСКА. РАБОТАЕТ!!!
	BinarySearchTree test = listToTree(my_list.first);
	
	//ТЕСТОВАЯ ВСТАВКА ЭЛЕМЕНТА В ДЕРЕВО. РАБОТАЕТ!!!
	Data testData = Data(2, 121, "Makarov", 30, 11, 2022, 203, "Android", 5);
	test.put(test.root, 203, testData);

	//ТЕСТОВОЕ ПОЛУЧЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА. РАБОТАЕТ!!!
	cout << test.get(test.root, 145)->key << endl;

	int lol = 1; //затычка для точки остановы

	return 0;
}
