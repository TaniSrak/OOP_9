#include <iostream>
#include <vector>

//создание шаблонного связного списка

template<typename Type>
class LinkedList
{
public:

	//что будет уметь делать связный список
	LinkedList();
	LinkedList(int n); //лис с уже созданными n элементами
	LinkedList(const LinkedList& other);
	LinkedList(LinkedList&& other); //конструктор копирования можно не делать, но для оптимизации скорости программы полезно
	//мы не будем реализовывать конструктор от списка инициализации, весем позже
	~LinkedList(); //деструктор

	//чтобы не возникали ошибка при работе с памятью
	LinkedList& operator = (const LinkedList& other); //присваивание копированием
	LinkedList& operator = (LinkedList&& other); //присваивание переносом

	//для доступа
	Type& operator[](int i);
	const Type& operator[](int i)const;

	//метод at, будт работать снаружи для пользователя, в паре с квадратными скобками выше
	Type& at(int i);
	const Type& at(int i)const;

	//для работы нашего контейнера методы для добавление\удаления элементов
	void push_back(const Type& obj); //засунуть новый элемент в конец
	void push_front(const Type& obj); //начало списка

	void pop_back(); //уничтожение данных в начале и конце списка
	void pop_front();
	
	int size()const; //сообщить пользователю а сколько сейчас точек имеется вообще

private:

	class Node 
	{
	public:

		Node() :Node(Type()) {}//что точка должна уметь делать // тип данных нам неизвестен // при делегации мы вызываем конструктор по умолчанию типа данных. 
		// данный синтаксис корректно отработает даже если прямой вызов такого метода (например конструктора встроенных типов) недоступен.
		Node(const Type& data, Node* place = nullptr)
			:data_(data), 
			next_(place) {}

		Type& Data()
		{
			return data_;
		}
		const Type& Data()const //получаем по ссылке дату без копирования
		{
			return data_;
		}

		//установка нового указателя с выводом информации как неконстантная. метод для предоставления информации о метсоположении следующей точки в списке
		Node* Next()const
		{
			return next_;
		}

		void Next(Node* next) //устанавливаем новое значение для следующей точки
		{
			next_ = next;
		}

	private:

		Type data_;
		Node* next_; //должна знать где нходится следующая точка
	};

	Node* start_; //начало списка
	Node* end_;//конец
	int size_; //размер списка
};

int main() {
	setlocale(LC_ALL, "Russian");
	int n;

	int arr[10];
	std::vector<int> vec(10);
	LinkedList<int> list;
	arr[5] = 34;
	vec[5] = 23;
	list[5] = 12;

	return 0;
}