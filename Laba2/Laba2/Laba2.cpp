#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class Publication {
protected:
    string title;
    float price;
public:
    void getdata() {
        cout << "Введите название: ";
        getline(cin, title);
        cout << "Введите цену: ";
        cin >> price;
        cin.ignore();
    }

    void putdata() const {
        cout << "Название: " << title << endl;
        cout << "Цена: " << price << " руб." << endl;
    }
};

class Sales {
protected:
    float sales[3];
public:
    void getdata() {
        cout << "Введите продажи за последние 3 месяца:\n";
        for (int i = 0; i < 3; ++i) {
            cout << "Месяц " << i + 1 << ": ";
            cin >> sales[i];
        }
        cin.ignore();
    }

    void putdata() const {
        cout << "Продажи: ";
        for (int i = 0; i < 3; ++i) {
            cout << sales[i] << " ";
        }
        cout << "руб." << endl;
    }
};

class Book : public Publication, public Sales {
private:
    int pages;
public:
    void getdata() {
        Publication::getdata();
        Sales::getdata();
        cout << "Введите количество страниц: ";
        cin >> pages;
        cin.ignore();
    }

    void putdata() const {
        Publication::putdata();
        Sales::putdata();
        cout << "Страниц: " << pages << endl;
    }
};

class Type : public Publication, public Sales {
private:
    float time;
public:
    void getdata() {
        Publication::getdata();
        Sales::getdata();
        cout << "Введите длительность записи (в минутах): ";
        cin >> time;
        cin.ignore();
    }

    void putdata() const {
        Publication::putdata();
        Sales::putdata();
        cout << "Длительность: " << time << " мин." << endl;
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Book b;
    Type t;

    cout << "\n=== Ввод данных для книги ===\n";
    b.getdata();

    cout << "\n=== Ввод данных для аудиозаписи ===\n";
    t.getdata();

    cout << "\n=== Вывод данных книги ===\n";
    b.putdata();

    cout << "\n=== Вывод данных аудиозаписи ===\n";
    t.putdata();

    return 0;
}
