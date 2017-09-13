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
	// �����������
	HashTable();

	~HashTable();

	// ����������� �����������
	HashTable(const HashTable& b);

	// ���������� �������� ���� ���-������.
	// ���������, ����� ����� ���� �����, ��� ������� ����������� �������
	// std::swap.
	void swap(HashTable& b);

	// �������� =
	HashTable& operator=(const HashTable& b);

	// ������� ���������.
	void clear();

	// ������� ������� �� ��������� �����.	
	bool erase(const Key& k);

	// ������� � ���������. ������������ �������� - ���������� �������.	
	bool insert(const Key& k, const Value& v);

	// �������� ������� �������� �� ��������� �����.	
	bool contains(const Key& k);

	// ���������� �������� �� �����. ������������ �����.
	// � ������ ���������� ����� � ���������� ������� �������� � ���������
	// ��������, ��������� ������������� �� ��������� � ������� ������ �� ����. 
	Value& operator[](const Key& k);

	const Value& operator[](const Key& k) const;

	// ���������� �������� �� �����. ������� ���������� ��� �������.
	Value& at(const Key& k);

	const Value& at(const Key& k) const;

	size_t size() const;

	bool empty() const;

	//������� ��������� � ������ ���-��������
	bool compare(const HashTable& b) const;

	void printAll();

private:

	Pair* pairs;
	bool* filled;
	int Size;
	int current_quantity;

	// ������� �������� ���-�������
	void create(int size_);

	// ������� ����������� �������� ���-�������
	void copy(const HashTable& b);

	// ���-�������
	// ���������� ����� ������ � ���-�������
	int hash(const Key& k) const;

	// ������� ���������� �������
	void resize();

	// ������� ������ ��������� ������
	// ���������� ����� ���������� ����� � ���-�������
	int searchForFreePlace(const Key& k, const bool* filled_) const;

	// ������� ������ ��������
	// ���������� ����� ������ � ���� ���������, -1 ���� ������ �������� ���
	int find(const Key& k) const;	

};

bool operator==(const HashTable & a, const HashTable & b);
bool operator!=(const HashTable & a, const HashTable & b);