// HashTable.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "HashTable.h"



// ������� �������� ���-�������
void HashTable::create(int size_){
	current_quantity = 0;
	Size = size_;
	pairs = new Pair[Size];
	filled = new bool[Size];
	for (int i = 0; i < Size; i++){
		filled[i] = false;
	}
}



// ������� ����������� �������� ���-�������
void HashTable::copy(const HashTable& b){
	current_quantity = b.current_quantity;
	for (int i = 0; i < Size; i++){
		if ( b.filled[i] ){
			filled[i] = true;
			pairs[i] = b.pairs[i];
		}
	}
}

// ���-�������
// ���������� ����� ������ � ���-�������
int HashTable::hash(const Key& k) const {
	unsigned int c = 1;
	int length = k.length();
	for(int i = 0; i < length; i++){
		c = c * k.at(i);
	}
	return abs( (int) c % Size);
}

// ������� ���������� �������
void HashTable::resize(){			
	Pair* tempPairs = new Pair[Size * 2];
	bool* tempFilled = new bool[Size * 2];
	int oldSize = Size;
	Size = Size * 2;
	for (int i = 0; i < Size; i++){
		tempFilled[i] = false;
	}

	for (int i = 0; i < oldSize; i++) {
		if ( filled[i] ){
			int j = searchForFreePlace(pairs[i].key, tempFilled);
			tempPairs[j] = pairs[i];
			tempFilled[j] = true;
		}
	}

	delete[] pairs;
	delete[] filled;
	pairs = tempPairs;
	filled = tempFilled;		
}

// ������� ������ ��������� ������
// ���������� ����� ���������� ����� � ���-�������
int HashTable::searchForFreePlace(const Key& k, const bool* filled_) const {
	int j = hash(k);
	for(int i = 0; i < Size; i++){
		if (filled_[j] == false){
			return j;
		}						
		j = (j + 1) % Size;
	}
}

// ������� ������ ��������
// ���������� ����� ������ � ���� ���������, -1 ���� ������ �������� ���
int HashTable::find(const Key& k) const {
	int j = hash(k);
	for (int i = 0; i < Size; i++){
		if ( ( filled[j] ) && ( pairs[j].key == k ) ){
			return j;
		}		  
		j = (j + 1) % Size;
	}
	return -1;
}


// �����������
HashTable::HashTable(){
	create(100);
}

HashTable::~HashTable(){
	delete[] pairs;
	delete[] filled;
}

// ����������� �����������
HashTable::HashTable(const HashTable& b){
	create(b.Size);
	copy(b);	  
}


// ���������� �������� ���� ���-������.
// ���������, ����� ����� ���� �����, ��� ������� ����������� �������
// std::swap.
void HashTable::swap(HashTable& b){

	HashTable tempHashTable = b;
	b = *this;
	*this = tempHashTable;

}


// �������� =
HashTable& HashTable::operator=(const HashTable& b){
	if (this != &b){
		delete[] pairs;
		delete[] filled;
		create(b.Size);
		copy(b);			
	}		
	return *this;
}

// ������� ���������.
void HashTable::clear(){
	for(int i = 0; i < Size; i++){
		filled[i] = false;
	}
	current_quantity = 0;
}


// ������� ������� �� ��������� �����.
bool HashTable::erase(const Key& k){
	int j = find(k);
	if (j == -1){
		return false;
	}

	filled[j] = false;
	current_quantity--;
	return true;
}


// ������� � ���������. ������������ �������� - ���������� �������.
bool HashTable::insert(const Key& k, const Value& v){

	if (find(k) != -1){
		return false;
	}

	if ( (double) current_quantity / Size > 0.6 ){
		resize();
	}

	int j = searchForFreePlace(k, filled);	  
	pairs[j].key = k;
	pairs[j].value = v;
	filled[j] = true;
	current_quantity++;

	return true;
}



// �������� ������� �������� �� ��������� �����.
bool HashTable::contains(const Key& k) {
	if (find(k) == -1){
		return false;
	}
	return true;

}

// ���������� �������� �� �����. ������������ �����.
// � ������ ���������� ����� � ���������� ������� �������� � ���������
// ��������, ��������� ������������� �� ��������� � ������� ������ �� ����. 
Value& HashTable::operator[](const Key& k){
	int j = find(k);
	if (j == -1){
		Value v;
		insert(k, v);
		return v;
	}
	return pairs[j].value;
}
const Value& HashTable::operator[](const Key& k) const {
	int j = find(k);
	if (j == -1){	
		Value v;
		return v;
	}
	return pairs[j].value;
}

// ���������� �������� �� �����. ������� ���������� ��� �������.
Value& HashTable::at(const Key& k){
	int j = find(k);
	if (j == -1){
		throw std::invalid_argument("No such pair in the hash table");
	}
	return pairs[j].value;
}

const Value& HashTable::at(const Key& k) const {
	int j = find(k);
	if (j == -1){
		throw std::invalid_argument("No such pair in the hash table");
	}
	return pairs[j].value;
}

size_t HashTable::size() const {
	return Size;
}

bool HashTable::empty() const {
	return (current_quantity == 0);
}

//������� ��������� � ������ ���-��������
bool HashTable::compare(const HashTable& b) const{

	if (Size != b.size() ) {
		return false;
	}

	Value v;
	Value thisV;

	for(int i=0; i<Size; i++){
		if (filled[i] == true){
			try{
				v =  b.at((pairs+i)->key);
				thisV = (pairs + i)->value;
				if ( (v.age != thisV.age) || (v.weight != thisV.weight) ){
					return false;
				}
			}
			catch (noSuchPairException){
				return false;
			}
		}
	}
	return true;
}

void HashTable::printAll(){
	printf("\n\n");
	for(int i = 0; i < Size; i++){
		if ( filled[i] ){
			printf("%d %s %d %d\n", i, pairs[i].key.data(), pairs[i].value.age, pairs[i].value.weight);
		}
	}
	printf("\n\n");
}



bool operator==(const HashTable & a, const HashTable & b){
	return a.compare(b);
}
bool operator!=(const HashTable & a, const HashTable & b){
	return !a.compare(b);
}


int _tmain(int argc, _TCHAR* argv[])
{
	HashTable ht;

	Value v1 = {20, 80};
	Value v2 = {25, 90};
	Value v3 = {218, 4};
	ht.insert("Vasya", v1);
	ht.insert("Kolya", v3);
	ht.insert("Alena", v2);

	ht.printAll();

	return 0;
}

