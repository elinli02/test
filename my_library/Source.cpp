#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<locale.h>
#include<cstdio>
#include<windows.h>
#include<fstream>
#define FILE_BOOKS "books.txt"
#define FILE_USERS "users.txt"
using namespace std;
struct user;
struct book
{
	string author;
	string name;
	string date;
	int count_page;
	user* user = nullptr;
	string article;
};
struct user
{
	string name;
	string date;
	string adress;
	book** arr_book;
	int count_book;
	int id;
};
int choice_user_or_book();
int user_menu();
int book_menu();
int add_book(book** array_books, int book_amount, int count_books);
void return_book(book* b);
void show_free_books(book* array_books, int count_books);
void save_file(book* array_books, int count_book, int amount_new_book, string filename);
int load_books(book** array_books, string filename);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	book* books=0;
	int amount_new_books=0;
	int result_user_or_book;
	int result_user_menu;
	int result_book_menu;
	int count_books = load_books(&books, FILE_BOOKS); //подгружаем из файла
	do
	{
		result_user_or_book=choice_user_or_book();
		switch (result_user_or_book)
		{
		case 1:
				result_user_menu = user_menu();
				switch (result_user_menu)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
					//case
				case 7:
					result_user_or_book = choice_user_or_book();
					break;
				}
			break;
		case 2:
			result_book_menu = book_menu();
			switch (result_book_menu)
			{
			case 1:
				cout << "Введите количество книг для ввода: ";
				cin >> amount_new_books;
				count_books = add_book(&books, amount_new_books, count_books);
				save_file(books, count_books, amount_new_books, FILE_BOOKS);
				break;
			case 2:
				break;
			case 3:
				show_free_books(books, count_books);
				break;
			case 4:
				break;
			case 5:
				result_user_or_book = choice_user_or_book();
				break;
			}
			break;
		case 0:
			break;
		}
	} while (result_user_or_book != 0);
}
int choice_user_or_book()
{
	int choice;
	do
	{
		cout << " " << endl; 
		cout << "Работа с пользователем - введите 1" << endl;
		cout << "Работа с книгами  - введите 2" << endl;
		cout << "Завершить работу - введите 0" << endl;
		cout << "Выбор пункта меню: " << endl;
		cin >> choice;
	} while (choice < 0 && choice>2);
	return choice;
}
int book_menu()
{
	int choice;
	do
	{
		cout << " " << endl;
		cout << "Заполнить библиотеку книгами - 1" << endl;
		cout << "Удалить книги - 2" << endl;
		cout << "Вывод информации о книгах - 3" << endl;
		cout << "Отредактировать данные - 4" << endl;
		cout << "Вернуться обратно - 5" << endl;
		cout << "Выбор пункта меню: ";
		cin >> choice;
	} while (choice < 1 && choice>5);
	return choice;
}
int user_menu()
{
	int choice;
	do
	{
		cout << " " << endl;
		cout << "Ввести пользователей - 1" << endl;
		cout << "Удалить пользователя - 2" << endl;
		cout << "Вывод пользоватлей - 3" << endl;
		cout << "Отредактировать данные пользователя - 4" << endl;
		cout << "Выдать книгу - 5" << endl;
		cout << "Возврат книги - 6" << endl;
		cout << "Вернуться обратно - 7" << endl;
		cout << "Выбор пункта меню: ";
		cin >> choice;
	} while (choice < 1 && choice>7);
	return choice;
}
int add_book(book** array_books, int new_book_amount, int count_books)
{
	book* temp_array_books = new book[count_books+new_book_amount];
	for (int i = 0; i < count_books; i++)
	{
		temp_array_books[i] = *array_books[i]; //копируем во временный объект
	}
	delete[] *array_books;
	for (int i = count_books; i < new_book_amount+count_books; i++)
	{
		cout << " " << endl;
		cout << "Введите автора книги " << i << " ";
		cin.ignore(32767, '\n');
		getline(cin, temp_array_books[i].author);
		cout << "Введите название книги " << i << " ";
		getline(cin, temp_array_books[i].name);
		cout << "Введите дату издания " << i << " ";
		getline(cin, temp_array_books[i].date);
		cout << "Введите количество страниц " << i << " ";
		cin >> temp_array_books[i].count_page;
		temp_array_books[i].article =to_string(i);
	}
	*array_books = temp_array_books; //в ячейку памяти записываем адрес указателя //ИЗМЕНЯем содержимое адреса указателя
	return count_books + new_book_amount;
}
void return_book(book* b)
{
	user* u = b->user;
	b->user = NULL;
	for (int i = 0; i < u->count_book; i++)
	{
		if (b->article == u->arr_book[i]->article)
		{
			for (int j = i; j < u->count_book - 1; j++) //осток и сдвиг //-1 так как работает с текущим и следующим
			{
				u->arr_book[j] = u->arr_book[j + 1];
			}
			u->count_book--;
			break;
		}
	}
}
void show_free_books(book* array_books, int count_books)
{
	bool flag_not_free_books = true;
	for (int i = 0; i < count_books; i++)
	{
		if (array_books[i].user == nullptr)
		{
			cout << array_books[i].author << " " << array_books[i].name << " " << array_books[i].date << " " << array_books[i].count_page << endl;
			flag_not_free_books = false;
		}
	}
	if (flag_not_free_books)
	{
		cout << "В библиотеке нет книг" << endl;
	}
}
void save_file(book* array_books, int count_book, int amount_new_book, string filename)
{
	ofstream output(filename, ios::app);
	if (output.is_open())
	{
		for (int i = count_book - amount_new_book; i < count_book; i++)
		{
			output << array_books[i].article<<endl;
			output << array_books[i].author<<endl;
			output << array_books[i].count_page << endl;
			output << array_books[i].date << endl;
			output << array_books[i].name << endl;
			if (array_books[i].user != NULL)
			{
				output << array_books[i].user->id << endl;
			}
			else
			{
				output << -1 << endl;
			}
		}
	}
	else
	{
		cout << "Ошибка при записи в файл"<<endl;
	}
	output.close();
}
int load_books(book** array_books, string filename)
{
	int count_books=0;
	ifstream input;
	input.open(filename.c_str());
	if (input.is_open())
	{
		struct book one_book;
		while (!input.eof()) //проверка на конец файла
		{
			input >> one_book.article;
			input >> one_book.author;
			input >> one_book.count_page;
			input >> one_book.date;
			input >> one_book.name;
			input >> one_book.user->id;
			count_books++;
		}
		input.clear();
		input.seekg(0);//на самое начало файла
		//rewind(input);
		*array_books = new book[count_books];
		int i=0; //цикл for
		while (!input.eof()) //проверка на конец файла
		{
			input >> one_book.article;
			input >> one_book.author;
			input >> one_book.count_page;
			input >> one_book.date;
			input >> one_book.name;
			input >> one_book.user->id;
			*array_books[i] = one_book;
			i++;
		}
		input.close();
	}
	else
	{
		cout << "Ошибка при чтении файла" << endl;
	}
	return count_books;
}