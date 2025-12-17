#include <iostream>
#include <string>
#include <stdexcept> 

using namespace std;

class ProgramError {
public:
    virtual ~ProgramError() = default;
    virtual void print() const = 0;
};

class InvalidPointerError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Ошибочный указатель." << endl;
    }
};

class ListOperationError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Ошибка работы со списком." << endl;
    }
};

class InvalidIndexError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Недопустимый индекс." << endl;
    }
};

class ListOverflowError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Список переполнен." << endl;
    }
};


template<typename T>
class PointerArray {
private:
    T** ptrs;
    size_t capacity;
    size_t count;

public:
    explicit PointerArray(size_t cap = 10) : capacity(cap), count(0) {
        if (cap == 0) cap = 1;
        ptrs = new T * [capacity]();
    }

    ~PointerArray() {
        delete[] ptrs;
        cout << "Массив указателей освобождён." << endl;
    }

    PointerArray(const PointerArray&) = delete;
    PointerArray& operator=(const PointerArray&) = delete;

    void add(T* p) {
        if (p == nullptr) {
            throw InvalidPointerError();
        }
        if (count >= capacity) {
            throw ListOverflowError();
        }
        ptrs[count++] = p;
    }

    T*& operator[](size_t index) {
        if (index >= count) {
            throw out_of_range("Индекс вне диапазона (operator[])");
        }
        return ptrs[index];
    }

    const T* operator[](size_t index) const {
        if (index >= count) {
            throw out_of_range("Индекс вне диапазона (const operator[])");
        }
        return ptrs[index];
    }

    size_t size() const { return count; }
    size_t getCapacity() const { return capacity; }
};

class Book {
private:
    string title;
    string author;
public:
    Book(const string& t, const string& a) : title(t), author(a) {}
    void show() const {
        cout << "\"" << title << "\" by " << author;
    }
};

class ProgramError {
public:
    virtual ~ProgramError() = default;
    virtual void print() const = 0;
};

class InvalidPointerError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Ошибочный указатель." << endl;
    }
};

class ListOperationError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Ошибка работы со списком." << endl;
    }
};

class InvalidIndexError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Недопустимый индекс." << endl;
    }
};

class ListOverflowError : public ProgramError {
public:
    void print() const override {
        cout << "Ошибка: Список переполнен." << endl;
    }
};

template<typename T>
class PointerArray {
private:
    T** ptrs;
    size_t capacity;
    size_t count;

public:
    explicit PointerArray(size_t cap = 10) : capacity(cap > 0 ? cap : 1), count(0) {
        ptrs = new T * [capacity]();
    }

    ~PointerArray() {
        delete[] ptrs;
        cout << "Массив указателей освобождён." << endl;
    }

    PointerArray(const PointerArray&) = delete;
    PointerArray& operator=(const PointerArray&) = delete;

    void add(T* p) {
        if (p == nullptr) {
            throw invalid_argument("Нельзя добавлять nullptr в PointerArray — это логическая ошибка.");
        }
        if (count >= capacity) {
            throw ListOverflowError();
        }
        ptrs[count++] = p;
    }

    T*& operator[](size_t index) {
        if (index >= count) {
            throw out_of_range("Индекс вне диапазона (operator[])");
        }
        return ptrs[index];
    }

    const T* operator[](size_t index) const {
        if (index >= count) {
            throw out_of_range("Индекс вне диапазона (const operator[])");
        }
        return ptrs[index];
    }

    size_t size() const { return count; }
};

class Product {
    string name;
    double price;
public:
    Product(const string& n, double p) : name(n), price(p) {}
    void show() const {
        cout << name << " — " << price << " руб." << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    //Задание 1

    try {
        int x = 42, y = 77, z = 99;
        PointerArray<int> intArr(3);
        intArr.add(&x);
        intArr.add(&y);
        intArr.add(&z);

        cout << "Целые числа:\n";
        for (size_t i = 0; i < intArr.size(); ++i) {
            cout << "  [" << i << "] = " << *intArr[i] << endl;
        }

        Book b1("1984", "Джордж Оруэлл");
        Book b2("Преступление и наказание", "Ф. Достоевский");
        PointerArray<Book> bookArr(2);
        bookArr.add(&b1);
        bookArr.add(&b2);

        cout << "\nКниги:\n";
        for (size_t i = 0; i < bookArr.size(); ++i) {
            cout << "  [" << i << "] = ";
            bookArr[i]->show();
            cout << endl;
        }

        cout << "\nПопытка доступа к индексу 5 (ошибка)...\n";
        cout << *intArr[5] << endl;

    }
    catch (const out_of_range& ex) {
        cout << "Перехвачено стандартное исключение: " << ex.what() << endl;
        InvalidIndexError().print();
    }
    catch (const ProgramError& e) {
        e.print();
    }
    catch (...) {
        cout << "Неизвестное исключение!" << endl;
    }

    cout << "\nПрограмма завершена. Память освобождена автоматически." << endl;

    //Задание 2

    try {
        int a = 100, b = 200;
        PointerArray<int> arr(2);
        arr.add(&a);
        arr.add(&b);

        cout << "Значения: " << *arr[0] << ", " << *arr[1] << endl;

        cout << "\nПопытка добавить nullptr..." << endl;
        arr.add(nullptr);

    }
    catch (const out_of_range& e) {
        cout << "Ошибка диапазона: " << e.what() << endl;
        InvalidIndexError().print();
    }
    catch (const invalid_argument& e) {
        cout << "Перехвачена логическая ошибка (invalid_argument): " << e.what() << endl;
    }
    catch (const logic_error& e) {
        cout << "Перехвачена логическая ошибка: " << e.what() << endl;
    }
    catch (const ProgramError& e) {
        e.print();
    }
    catch (...) {
        cout << "Неизвестное исключение!" << endl;
    }

    cout << "\nПрограмма завершена. Память освобождена." << endl;
    return 0;

}
