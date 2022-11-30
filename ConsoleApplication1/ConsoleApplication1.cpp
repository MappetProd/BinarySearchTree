#include <iostream>
#include <fstream>
#include <Windows.h>
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

//КЛАСС БИНАРНОГО ДЕРЕВА ПОИСКА
class BinarySearchTree {
	//УЗЕЛ(ВЕРШИНА) БИНАРНОГО ДЕРЕВА
	class BinaryTreeNode {
	public:
		Data* data;
		int key = data->numberRecordBook;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
		int numberOfNodes;
	};

	BinaryTreeNode* root; //корень бинарного дерева

	//ФУНКЦИЯ ПОЛУЧЕНИЯ ЭЛЕМЕНТА ПО КЛЮЧУ
	BinaryTreeNode* get(BinaryTreeNode* currentTree, int key) {
		if (currentTree == nullptr) return nullptr;

		if (key < currentTree->key) return get(currentTree->left, key);
		else if (key > currentTree->key) return get(currentTree->right, key);
		else return currentTree;
	}

	void put(BinaryTreeNode* currentTree, int key, Data* data) {
		if (currentTree == nullptr) return Bina
	}
};

BinarySearchTree* ListToTree(List list, BinarySearchTree tree) {
	tree.root = list.first;
	Node* currentNode = list.first;
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
	SetConsoleCP(1251);				// Рускоязычный вывод в консоль
	SetConsoleOutputCP(1251);

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

	return 0;
}
