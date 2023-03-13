#include <iostream>

template<class T>
class Table {
private:
	int rows = 0;
	int cols = 0;
	T** table;
public:
	Table(int rows, int cols) {
		table = new T * [rows];
		for (int i = 0; i < rows; ++i) {
			table[i] = new T[cols];
		}
		this->rows = rows;
		this->cols = cols;
	}
	~Table() {
		for (int i = 0; i < rows; ++i) {
			delete[] table[i];
		}
		delete[] table;
	}

	T* operator[](int i) const {
		std::cout << "const\n";
		return table[i];
	}

	T* operator[](int i) {
		std::cout << "not const\n";
		return table[i];
	}



};

int main()
{
	auto table = Table<int>(2, 3);
	table[0][0] = 4;
	//std::cout << table[0][0];
}
