#include <iostream>
#include <vector>
#include <chrono>

//создание шаблонного связного списка

template<typename Type>
class LinkedList
{
public:

	//что будет уметь делать связный список //конструктор по умолчанию
	LinkedList() :start_(nullptr), end_(nullptr), size_(0) {}


	//лист с уже созданными n элементами
	LinkedList(int n) 
		:LinkedList() //стартовое значение
	{
		if (n < 0) throw - 1; //сообщение об ошибке
		if (n == 0) return;
		Node* tmp{}; //указатель на вновьсоздаваемую точку
	
		int AddedNodes{ 0 }; //сколько точек мы вообще добавили в наш список
		tmp = new Node{}; //создание новой точки
		start_ = tmp; //запись данных точки в наши списки начало/конец
		end_ = tmp;
		AddedNodes += 1;
		while (AddedNodes < n) //сработает только тогда, мы получим больше единицы на вход
		{
			tmp = new Node{}; //создаем новую точку
			end_->Next(tmp); //старому концу списка говорит, что новый существует
			end_ = tmp; //чтобы список запомнил какой элемент последний
			AddedNodes += 1;
		}
		size_ = n; //после окончания запомним сколько пользователь попросил ввести точек
	}


	//конструктор копирования, будем копировать из одного списка в другой
	LinkedList(const LinkedList& other):LinkedList()
	{
		if (other.size() == 0) return; //если другой список был пустым, тогда заканчиваем работу

		start_ = new Node(other.start_->Data()); //перенесли данные из стартовой точки в другой список
		end_ = start_;

		for (Node * current = other.start_ -> Data();//зацикливаем следующие переносы точек
			current != nullptr; 
			current = current -> Next())
		{
			// Node* tmp = new Node(other[i]); такая строка замедлит память []
			Node* tmp = new Node(current->Data()); //возвращает с помощью даты значение нодб то есть новой точки
			end_->Next(tmp); //старому концу списка говорит, что новый существует
			end_ = tmp; //чтобы список запомнил какой элемент последний
		}
		size_ = other.size_;
	}


	LinkedList(LinkedList&& other):LinkedList() //конструктор копирования жена (для переноса) можно не делать, но для оптимизации скорости программы полезно
		//мы не будем реализовывать конструктор от списка инициализации, весем позже
	{
		//все поля мы просто махнем местами, чтобы переложить
		std::swap(start_, other.start_);
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);
	}
	

	~LinkedList() //деструктор для удаления данных
	{
		Node* current = start_;
		while (current != nullptr)
		{
			Node* tmp = current->Next();
			delete current;
			current = tmp;
		}
	}

	void clear() //метод клеар
	{
		Node* current = start_;//скопировали из деструктора
		while (current != nullptr)
		{
			Node* tmp = current->Next();
			delete current;
			current = tmp;
		}
		start_ = nullptr;
		end_ = nullptr;
		size_ = 0;
	}


	//чтобы не возникали ошибка при работе с памятью
	LinkedList& operator = (const LinkedList& other)//присваивание копированием
	{
		clear();

		if (other.size() == 0) return *this; //если другой список был пустым, тогда заканчиваем работу
		start_ = new Node(other.start_->Data()); //перенесли данные из стартовой точки в другой список
		end_ = start_;
		for (Node* current = other.start_->Data();//зацикливаем следующие переносы точек
			current != nullptr;
			current = current->Next())
		{
			// Node* tmp = new Node(other[i]); такая строка замедлит память []
			Node* tmp = new Node(current->Data()); //возвращает с помощью даты значение нодб то есть новой точки
			end_->Next(tmp); //старому концу списка говорит, что новый существует
			end_ = tmp; //чтобы список запомнил какой элемент последний
		}
		size_ = other.size_;
		return *this;
	}


	LinkedList& operator = (LinkedList&& other) //присваивание переносом
	{
		clear();
		std::swap(start_, other.start_); 
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);
		return *this;
	}


	//оператор доступа к хранящимся элементам
	Type& operator[](int i)
	{
		int count{};
		Node* tmp = start_;
		while (count < i)
		{
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}
	//константный оператор доступа
	const Type& operator[](int i)const
	{
		int count{};
		Node* tmp = start_;
		while (count < i)
		{
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	//метод at, будт работать снаружи для пользователя, в паре с оператором квадратные скобки выше
	Type& at(int i)
	{
		if (i < 0 || i >= size_) throw - 1;
		int count{};
		Node* tmp = start_;
		while (count < i)
		{
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}
	const Type& at(int i)const
	{
		if (i < 0 || i >= size_) throw - 1;
		int count{};
		Node* tmp = start_;
		while (count < i)
		{
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	//для работы нашего контейнера методы для добавление\удаления элементов
	void push_back(const Type& obj) //засунуть новый элемент в конец
	{
		Node* tmp = new Node{ obj };
		if (size_ == 0) //передем данные для заполнения даты
		{
			start_ = tmp;
			end_ = tmp;
		}
		else
		{
			end_->Next(tmp);//след элемент наше временное значение чтобы предыдущий знал где следующий
			end_ = tmp; //присваиваем
		}
		size_++;
	}
	void push_front(const Type& obj) //в начало списка
	{
		Node* tmp = new Node{ obj };
		//прорка сайз на ноль
		if (!size_) //передем данные для заполнения даты
		{
			start_ = tmp;
			end_ = tmp;
		}
		else
		{
			tmp->Next(start_);//первый элемент наше временное значение, чтобы предыдущий знал где следующий
			start_ = tmp; //присваиваем
		}
		size_++;
	}

	void pop_back()//уничтожение данных в начале списка
	{
		if (end_) 
		{
			auto tmp = start_;
			//цикл предпоследнего элемента
			while(tmp->Next != end_)
			{	
				tmp = tmp->Next();
			}
			//освобождение и замена последнего элемента
			delete end_;
			end_ = tmp;
			size_--;
		}
		if (!size_)
		{
			end_ = start_ = nullptr;
		}
	}
	void pop_front() //в конце списка
	{
		if (start_) //(start!=0)если в точке начала что-то есть, тогда удаляем
		{
			auto tmp = start_;
			start_ = start_->Next();
			delete tmp;
			size_--;	
		}
		if (!size_) //если не сайз (size_==0)
		{
			end_ = start_ = nullptr;
		}
	}
	
	int size()const //сообщить пользователю а сколько сейчас точек имеется вообще
	{
		return size_;
	}

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

	int arr[10]{};
	std::vector<int> vec;
	LinkedList<int> list;

	arr;
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(i + 1);
	}
	for (int i = 0; i < 10000; i++)
	{
		list.push_back(i + 1);
	}
	arr;
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i];
	}
	for (int i = 0; i < list.size(); i++)
	{
		list[i];
	}
	arr;

	//для перебора коллекций, но для нашего списка пока недоступный функционал
	//for (/*переменная для хранения элементов*/ : /*элементы, который нужно перебрать*/)
	//for (int &e : arr)
	//{
	//	std::cout << e << ' ';
	//}
	//for (int &e : vec)
	//{
	//	std::cout << e << ' ';
	//}
	//std::chrono::duration<float> time_length; //хроно - библиотека для работы  временем


	return 0;
}