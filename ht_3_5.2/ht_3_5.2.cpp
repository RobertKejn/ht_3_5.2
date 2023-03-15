#include <iostream>
#include <exception>

template<class T>
class Table {
private:
	int rows = 0;
	int cols = 0;
	T** table;
public:
	Table(int rows, int cols) {
		if (rows < 1 || cols < 1) throw std::invalid_argument("Размерности не должны быть меньше 0");
		table = new T * [rows];
		for (int i = 0; i < rows; ++i) {
			table[i] = new T[cols];
		}
		this->rows = rows;
		this->cols = cols;
	}
	Table(const Table<T>& t) {
		rows = t.rows;
		cols = t.cols;

		table = new T * [rows];
		for (int i = 0; i < rows; ++i) {
			table[i] = new T[cols];
		}

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				table[i][j] = t.table[i][j];
			}
		}
	}
	~Table() {
		for (int i = 0; i < rows; ++i) {
			delete[] table[i];
		}
		delete[] table;
	}

	T* operator[](int i) const {
		if (i < 0 || i >= rows) throw std::out_of_range("Индекс вне заданной размерности");
		return table[i];
	}

	T* operator[](int i) {
		if (i < 0 || i >= rows) throw std::out_of_range("Индекс вне заданной размерности");
		return table[i];
	}
	int Size() { return rows; }

	Table<T>& operator=(const Table<T>& t) {
		if (&t != this) {
			for (int i = 0; i < rows; ++i) {
				delete[] table[i];
			}
			delete[] table;

			rows = t.rows;
			cols = t.cols;

			table = new T * [rows];
			for (int i = 0; i < rows; ++i) {
				table[i] = new T[cols];
			}

			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					table[i][j] = t.table[i][j];
				}
			}
		}
		return *this;
	}
};

int main()
{
	try {
		auto table1 = Table<int>(3, 3);
		table1[0][0] = 4;
		std::cout << table1[0][0]<<'\n';
		auto table2 = Table<int>(2, 3);
		table2[0][0] = 10;
		table1 = table1;
		table1 = table2;
		Table<int> table3(table2);
		std::cout << table3[0][0];
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
}