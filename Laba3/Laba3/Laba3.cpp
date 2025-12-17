#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <locale>

using namespace std;

class Detail {
protected:
    string name;

    explicit Detail(const string& n) : name(n) {}

public:
    virtual ~Detail() = default;

    virtual void print() const {
        cout << "Деталь: " << name << endl;
    }

    template<typename T, typename... Args>
    friend unique_ptr<T> create(Args&&... args);
};

class Assembly : public Detail {
protected:
    string type;

    Assembly(const string& n, const string& t) : Detail(n), type(t) {}

public:
    void print() const override {
        cout << "Сборка: " << name << " (тип: " << type << ")" << endl;
    }

    template<typename T, typename... Args>
    friend unique_ptr<T> create(Args&&... args);
};

template<typename T, typename... Args>
unique_ptr<T> create(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Base {
public:
    virtual ~Base() = default;

    virtual void show() const {
        cout << "Это объект Base" << endl;
    }

    virtual unique_ptr<Base> clone() const {
        return make_unique<Base>(*this);
    }
};

class Derived : public Base {
public:
    void show() const override {
        cout << "Это объект Derived" << endl;
    }

    unique_ptr<Base> clone() const override {
        return make_unique<Derived>(*this);
    }
};

vector<unique_ptr<Base>> storage;

void add(const Base& obj) {
    storage.push_back(obj.clone());
}


int main() {
    setlocale(LC_ALL, "Russian");
    //Задание 1
    vector<unique_ptr<Detail>> storage1;

    storage1.push_back(create<Detail>("Шестерёнка"));
    storage1.push_back(create<Detail>("Винт"));
    storage1.push_back(create<Assembly>("Коробка передач", "Механическая"));
    storage1.push_back(create<Assembly>("Электродвигатель", "Постоянного тока"));

    for (const auto& item : storage1) {
        item->print();
    }
    //Задание 2
    srand(static_cast<unsigned int>(time(nullptr)));

    const int COUNT = 6;

    cout << "Создание объектов:\n";
    for (int i = 0; i < COUNT; ++i) {
        int r = rand();
        unique_ptr<Base> obj;

        if (r % 2 == 0) {
            obj = make_unique<Base>();
            cout << "  Создан Base (случайное: " << r << " — чётное)\n";
        }
        else {
            obj = make_unique<Derived>();
            cout << "  Создан Derived (случайное: " << r << " — нечётное)\n";
        }

        add(*obj);
    }

    cout << "\nПолиморфный вывод из хранилища:\n";
    for (const auto& item : storage) {
        item->show();
    }

    return 0;
}
