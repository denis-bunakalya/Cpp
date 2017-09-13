#include <string>

typedef std::string Key;



struct Value {
	unsigned age;
	unsigned weight;
};

struct Pair{
	Key key;
	Value value;
};

class noSuchPairException{};

class HashTable{

public:
	// конструктор
	HashTable();

	~HashTable();

	// конструктор копирования
	HashTable(const HashTable& b);

	// Обменивает значения двух хэш-таблиц.
	// Подумайте, зачем нужен этот метод, при наличии стандартной функции
	// std::swap.
	void swap(HashTable& b);

	// оператор =
	HashTable& operator=(const HashTable& b);

	// Очищает контейнер.
	void clear();

	// Удаляет элемент по заданному ключу.	
	bool erase(const Key& k);

	// Вставка в контейнер. Возвращаемое значение - успешность вставки.	
	bool insert(const Key& k, const Value& v);

	// Проверка наличия значения по заданному ключу.	
	bool contains(const Key& k);

	// Возвращает значение по ключу. Небезопасный метод.
	// В случае отсутствия ключа в контейнера следует вставить в контейнер
	// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
	Value& operator[](const Key& k);

	const Value& operator[](const Key& k) const;

	// Возвращает значение по ключу. Бросает исключение при неудаче.
	Value& at(const Key& k);

	const Value& at(const Key& k) const;

	size_t size() const;

	bool empty() const;

	//функция сравнения с другой хэш-таблицей
	bool compare(const HashTable& b) const;

	void printAll();

private:

	Pair* pairs;
	bool* filled;
	int Size;
	int current_quantity;

	// функция создания хэш-таблицы
	void create(int size_);

	// функция копирования значений хэш-таблицы
	void copy(const HashTable& b);

	// хэш-функция
	// возвращает номер ячейки в хэш-таблице
	int hash(const Key& k) const;

	// функция увеличения размера
	void resize();

	// функция поиска свободной ячейки
	// возвращает номер свободного места в хэш-таблице
	int searchForFreePlace(const Key& k, const bool* filled_) const;

	// функция поиска элемента
	// возвращает номер ячейки с этим элементом, -1 если такого элемента нет
	int find(const Key& k) const;	

};

bool operator==(const HashTable & a, const HashTable & b);
bool operator!=(const HashTable & a, const HashTable & b);