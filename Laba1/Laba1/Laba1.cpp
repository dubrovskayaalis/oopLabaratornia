#include <iostream>
#include <string>
#include <vector>
#include <memory>


using namespace std;

// Задание 1

void partA() {
    std::cout << "=== Часть A (int) ===" << std::endl;

    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    // Выделить память
    int* arr = new int[n];

    // Заполнить
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // Вывести
    std::cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Адрес начала массива: " << arr << std::endl;
    std::cout << "Расстояния от начала:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Элемент " << i << ": адрес " << (arr + i)
            << ", расстояние " << (arr + i - arr) * sizeof(int)
            << " байт" << std::endl;
    }

    // Освободить
    delete[] arr;
}

void partC() {
    std::cout << "\n=== Часть C (short) ===" << std::endl;

    const int size = 10;
    short* arr = new short[size];

    // Заполнить
    std::cout << "Введите 10 чисел типа short: ";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    // Вывести
    std::cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Адрес начала массива: " << arr << std::endl;
    std::cout << "Расстояния от начала:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Элемент " << i << ": адрес " << (arr + i)
            << ", расстояние " << (arr + i - arr) * sizeof(short)
            << " байт" << std::endl;
    }

    delete[] arr;
}

//Зададие 2

enum class BookType {
    FICTION,    // Художественная (?) так сказал переводчик
    TECHNICAL   // Техническая
};

class Book {
private:
    std::string author;
    std::string title;
    BookType type;

public:
    // Конструктор с проверкой на пустоту
    Book(const std::string& author, const std::string& title, BookType type)
        : author(author), title(title), type(type) {

        if (author.empty() || title.empty()) {
            throw std::invalid_argument("Автор и название не могут быть пустыми");
        }
    }

    // Гетеры
    const std::string& getAuthor() const { return author; }
    const std::string& getTitle() const { return title; }
    BookType getType() const { return type; }

    // Деструктор
    ~Book() {
        std::cout << "Книга '" << title << "' удалена" << std::endl;
    }
};

class Library {
private:
    std::vector<std::unique_ptr<Book>> books;

public:
    // Добавить
    void addBook(const std::string& author, const std::string& title, BookType type) {
        books.push_back(std::make_unique<Book>(author, title, type));
    }

    // Подсчет книг по типу (со switch)
    void countBooksWithSwitch() const {
        int fictionCount = 0;
        int technicalCount = 0;

        for (const auto& book : books) {
            switch (book->getType()) {
            case BookType::FICTION:
                fictionCount++;
                break;
            case BookType::TECHNICAL:
                technicalCount++;
                break;
            }
        }

        std::cout << "\nКоличество книг (со switch):" << std::endl;
        std::cout << "Художественная литература: " << fictionCount << std::endl;
        std::cout << "Техническая литература: " << technicalCount << std::endl;
    }

    // Подсчет книг по типу (без switch)
    void countBooksWithoutSwitch() const {
        int fictionCount = 0;
        int technicalCount = 0;

        for (const auto& book : books) {
            if (book->getType() == BookType::FICTION) {
                fictionCount++;
            }
            else if (book->getType() == BookType::TECHNICAL) {
                technicalCount++;
            }
        }

        std::cout << "\nКоличество книг (без switch):" << std::endl;
        std::cout << "Художественная литература: " << fictionCount << std::endl;
        std::cout << "Техническая литература: " << technicalCount << std::endl;
    }

    // Вывод инфы
    void printAllBooks() const {
        std::cout << "\nВсе книги в библиотеке:" << std::endl;
        for (const auto& book : books) {
            std::cout << "Автор: " << book->getAuthor()
                << ", Название: " << book->getTitle()
                << ", Тип: " << (book->getType() == BookType::FICTION ?
                    "Художественная" : "Техническая")
                << std::endl;
        }
    }
};

void part2() {
    std::cout << "\n=== Часть 2: Библиотека книг ===" << std::endl;

    Library library;

    // Добавить (было интересно сделать больше для себя)
    try {
        library.addBook("Лев Толстой", "Война и мир", BookType::FICTION);
        library.addBook("Федор Достоевский", "Преступление и наказание", BookType::FICTION);
        library.addBook("Бьярне Страуструп", "Язык программирования C++", BookType::TECHNICAL);
        library.addBook("Дональд Кнут", "Искусство программирования", BookType::TECHNICAL);
        library.addBook("Антон Чехов", "Вишневый сад", BookType::FICTION);
        library.addBook("Эндрю Таненбаум", "Современные операционные системы", BookType::TECHNICAL);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при добавлении книги: " << e.what() << std::endl;
    }

    // Вывод
    library.printAllBooks();

    // Подсчет с switch 
    library.countBooksWithSwitch();

    // Подсчет без switch
    library.countBooksWithoutSwitch();

    // Память автоматически из-за unique_ptr
}


int main() {
    setlocale(LC_ALL, "Russian");
    // Задание 1
    partA();
    partC();
    //Задание 2
    part2();
    return 0;
}
