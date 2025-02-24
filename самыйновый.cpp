#include <iostream> // Подключение библиотеки для ввода-вывода
#include <string>   // Подключение библиотеки для работы со строками
#include <algorithm> // Подключение библиотеки для использования алгоритмов
#include <fstream>   // Подключение библиотеки для работы с файлами
#include <limits>    // Подключение библиотеки для работы с числовыми пределами
#include <vector>    // Подключение библиотеки для работы с динамическими массивами
#include <map>       // Подключение библиотеки для работы с ассоциативными массивами
#include <set>       // Подключение библиотеки для работы с множествами
#include <sstream>   // Подключение библиотеки для работы с потоками строк
#include <tuple>     // Подключение библиотеки для работы с кортежами

using namespace std; // Использование пространства имен std

// Задание 1: Однонаправленный список
template <typename T> // класс для однонаправленного списка
class SinglyLinkedList {
private:
    struct Node { // Структура для узла списка
        T data;    // Данные узла
        Node* next; // Указатель на следующий узел
        Node(T data) : data(data), next(nullptr) {} // Конструктор узла
    };
    Node* head; // Указатель на первый узел списка

public:
    SinglyLinkedList() : head(nullptr) {} // Конструктор списка

    void add(T data) { // Метод добавления элемента в список
        Node* newNode = new Node(data); // Создание нового узла
        if (!head) { // Если список пуст
            head = newNode; // Новый узел становится первым
        } else {
            Node* current = head; // Начинаем с первого узла
            while (current->next) { // Пока не достигнем конца списка
                current = current->next; // Переходим к следующему узлу
            }
            current->next = newNode; // Добавляем новый узел в конец
        }
    }

    void remove(T data) { // Метод удаления элемента из списка
        if (!head) return; // Если список пуст, выходим

        if (head->data == data) { // Если первый элемент - тот, что нужно удалить
            Node* temp = head; // Сохраняем указатель на первый узел
            head = head->next; // Перемещаем указатель на следующий узел
            delete temp; // Удаляем первый узел
            return;
        }

        Node* current = head; // Начинаем с первого узла
        while (current->next) { // Пока не достигнем конца списка
            if (current->next->data == data) { // Если следующий элемент - тот, что нужно удалить
                Node* temp = current->next; // Сохраняем указатель на следующий узел
                current->next = current->next->next; // Перемещаем указатель на следующий узел
                delete temp; // Удаляем следующий узел
                return;
            }
            current = current->next; // Переходим к следующему узлу
        }
    }

    void reverse() { // Метод переворота списка
        Node* prev = nullptr; // Указатель на предыдущий узел
        Node* current = head; // Указатель на текущий узел
        Node* next = nullptr; // Указатель на следующий узел

        while (current) { // Пока не достигнем конца списка
            next = current->next; // Сохраняем указатель на следующий узел
            current->next = prev; // Переворачиваем указатель на предыдущий узел
            prev = current; // Перемещаем указатель на предыдущий узел
            current = next; // Перемещаем указатель на следующий узел
        }

        head = prev; // Обновляем указатель на первый узел
    }

    void print() const { // Метод вывода списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнем конца списка
            cout << current->data << " "; // Выводим данные узла
            current = current->next; // Переходим к следующему узлу
        }
        cout << endl; // Переход на новую строку
    }

    ~SinglyLinkedList() { // Деструктор списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнем конца списка
            Node* next = current->next; // Сохраняем указатель на следующий узел
            delete current; // Удаляем текущий узел
            current = next; // Перемещаем указатель на следующий узел
        }
    }
};

// Задание 2: Двунаправленный список
template <typename T> // класс для двунаправленного списка
class DoublyLinkedList {
private:
    struct Node { // Структура для узла списка
        T data;    // Данные узла
        Node* next; // Указатель на следующий узел
        Node* prev; // Указатель на предыдущий узел
        Node(T data) : data(data), next(nullptr), prev(nullptr) {} // Конструктор узла
    };

    Node* head; // Указатель на первый узел списка
    Node* tail; // Указатель на последний узел списка

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {} // Конструктор списка

    void add(T data) { // Метод добавления элемента в список
        Node* newNode = new Node(data); // Создание нового узла

        if (!head) { // Если список пуст
            head = newNode; // Новый узел становится первым
            tail = newNode; // Новый узел становится последним
        } else {
            tail->next = newNode; // Добавляем новый узел в конец
            newNode->prev = tail; // Обновляем указатель на предыдущий узел
            tail = newNode; // Обновляем указатель на последний узел
        }
    }

    void remove(T data) { // Метод удаления элемента из списка
        if (!head) return; // Если список пуст, выходим

        if (head->data == data) { // Если первый элемент - тот, что нужно удалить
            Node* temp = head; // Сохраняем указатель на первый узел
            head = head->next; // Перемещаем указатель на следующий узел
            if (head) { // Если новый первый узел существует
                head->prev = nullptr; // Обновляем указатель на предыдущий узел
            } else {
                tail = nullptr; // Если список стал пустым, обновляем указатель на последний узел
            }
            delete temp; // Удаляем первый узел
            return;
        }

        if (tail->data == data) { // Если последний элемент - тот, что нужно удалить
            Node* temp = tail; // Сохраняем указатель на последний узел
            tail = tail->prev; // Перемещаем указатель на предыдущий узел
            tail->next = nullptr; // Обновляем указатель на следующий узел
            delete temp; // Удаляем последний узел
            return;
        }

        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнем конца списка
            if (current->data == data) { // Если текущий элемент - тот, что нужно удалить
                current->prev->next = current->next; // Обновляем указатель на следующий узел
                current->next->prev = current->prev; // Обновляем указатель на предыдущий узел
                delete current; // Удаляем текущий узел
                return;
            }
            current = current->next; // Переходим к следующему узлу
        }
    }

    void insertAround(T e, T f) { // Метод вставки элемента вокруг другого
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнем конца списка
            if (current->data == e) { // Если текущий элемент - тот, вокруг которого нужно вставить
                Node* newRight = new Node(f); // Создание нового узла справа
                newRight->next = current->next; // Обновляем указатель на следующий узел
                newRight->prev = current; // Обновляем указатель на предыдущий узел
                if (current->next) { // Если существует следующий узел
                    current->next->prev = newRight; // Обновляем указатель на предыдущий узел
                } else {
                    tail = newRight; // Если новый узел стал последним, обновляем указатель на последний узел
                }
                current->next = newRight; // Обновляем указатель на следующий узел

                Node* newLeft = new Node(f); // Создание нового узла слева
                newLeft->prev = current->prev; // Обновляем указатель на предыдущий узел
                newLeft->next = current; // Обновляем указатель на следующий узел
                if (current->prev) { // Если существует предыдущий узел
                    current->prev->next = newLeft; // Обновляем указатель на следующий узел
                } else {
                    head = newLeft; // Если новый узел стал первым, обновляем указатель на первый узел
                }
                current->prev = newLeft; // Обновляем указатель на предыдущий узел
                return;
            }
            current = current->next; // Переходим к следующему узлу
        }
    }

    void print() const { // Метод вывода списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнем конца списка
            cout << current->data << " "; // Выводим данные узла
            current = current->next; // Переходим к следующему узлу
        }
        cout << endl; // Переход на новую строку
    }

    ~DoublyLinkedList() { // Деструктор списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнем конца списка
            Node* next = current->next; // Сохраняем указатель на следующий узел
            delete current; // Удаляем текущий узел
            current = next; // Перемещаем указатель на следующий узел
        }
    }
};

// Задание 3  4: Неупорядоченный список уникальных элементов
template <typename T> // класс для списка уникальных элементов
class UniqueList {
private:
    set<T> data; // Множество для хранения уникальных элементов

public:
    void add(T item) { // Метод добавления элемента в список
        data.insert(item); // Вставка элемента в множество
    }

    void remove(T item) { // Метод удаления элемента из списка
        data.erase(item); // Удаление элемента из множества
    }

    UniqueList<T> Union(const UniqueList<T>& other) const { // Метод объединения списков
        UniqueList<T> result = *this; // Создание копии текущего списка
        for (const auto& item : other.data) { // Для каждого элемента другого списка
            result.add(item); // Добавляем элемент в результат
        }
        return result; // Возвращаем результат
    }

    UniqueList<T> Except(const UniqueList<T>& other) const { // Метод исключения элементов другого списка
        UniqueList<T> result = *this; // Создание копии текущего списка
        for (const auto& item : other.data) { // Для каждого элемента другого списка
            result.remove(item); // Удаляем элемент из результата
        }
        return result; // Возвращаем результат
    }

    UniqueList<T> Intersect(const UniqueList<T>& other) const { // Метод пересечения списков
        UniqueList<T> result; // Создание пустого списка
        for (const auto& item : data) { // Для каждого элемента текущего списка
            if (other.contains(item)) { // Если элемент содержится в другом списке
                result.add(item); // Добавляем элемент в результат
            }
        }
        return result; // Возвращаем результат
    }

    bool contains(const T& item) const { // Метод проверки наличия элемента в списке
        return data.count(item) > 0; // Возвращаем true, если элемент содержится в множестве
    }

    void print() const { // Метод вывода списка
        for (const auto& item : data) { // Для каждого элемента множества
            cout << item << " "; // Выводим элемент
        }
        cout << endl; // Переход на новую строку
    }

    ~UniqueList() {} // Деструктор списка
};

//Задание 5: Словарь
template <typename K, typename V> // Шаблонный класс для словаря
class Dictionary {
private:
    map<K, V> data; // Ассоциативный массив для хранения пар ключ-значение

public:
    void add(const K& key, const V& value) { // Метод добавления элемента в словарь
        data[key] = value; // Вставка пары ключ-значение в ассоциативный массив
    }

    void remove(const K& key) { // Метод удаления элемента из словаря
        data.erase(key); // Удаление пары ключ-значение из ассоциативного массива
    }

    V get(const K& key) const { // Метод получения значения по ключу
        auto it = data.find(key); // Поиск пары ключ-значение
        if (it != data.end()) { // Если пара найдена
            return it->second; // Возвращаем значение
        }
        return V(); // Если пара не найдена, возвращаем значение по умолчанию
    }

    bool contains(const K& key) const { // Метод проверки наличия ключа в словаре
        return data.count(key) > 0; // Возвращаем true, если ключ содержится в ассоциативном массиве
    }

    void print() const { // Метод вывода словаря
        for (const auto& pair : data) { // Для каждой пары ключ-значение
            cout << pair.first << ": " << pair.second << endl; // Выводим ключ и значение
        }
    }

    map<K, V> getData() const { // Метод получения данных словаря
        return data; // Возвращаем ассоциативный массив
    }

    ~Dictionary() {} // Деструктор словаря
};

// Функции для решения задач 

void solveTask3() { // Функция для решения задачи 3
    int numStudents, numDiscos; // Количество студентов и дискотек

    cout << "Введите количество студентов: "; // Запрос количества студентов
    while (!(cin >> numStudents) || numStudents <= 0) { // Пока ввод некорректен
        cout << "Некорректное количество студентов. Попробуйте снова: "; // Сообщение об ошибке
        cin.clear(); // Очистка состояния потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов
    }

    cout << "Введите количество дискотек: "; // Запрос количества дискотек
    while (!(cin >> numDiscos) || numDiscos <= 0) { // Пока ввод некорректен
        cout << "Некорректное количество дискотек. Попробуйте снова: "; // Сообщение об ошибке
        cin.clear(); // Очистка состояния потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов

    vector<string> discoList(numDiscos); // Вектор для хранения названий дискотек
    cout << "Введите названия дискотек:" << endl; // Запрос названий дискотек
    for (int i = 0; i < numDiscos; ++i) { // Для каждой дискотеки
        getline(cin, discoList[i]); // Ввод названия дискотеки
    }

    vector<UniqueList<string>> studentDiscos(numStudents); // Вектор для хранения списков дискотек студентов
    cout << "Введите дискотеки, которые посещал каждый студент (каждый студент на новой строке, дискотеки через пробел):" << endl; // Запрос дискотек студентов
    for (int i = 0; i < numStudents; ++i) { // Для каждого студента
        string line; // Строка для ввода
        getline(cin, line); // Ввод строки
        stringstream ss(line); // Поток строки
        string disco; // Название дискотеки
        while (ss >> disco) { // Пока есть дискотеки в строке
            studentDiscos[i].add(disco); // Добавляем дискотеку в список студента
        }
    }

    UniqueList<string> allStudentsDiscos; // Список дискотек, которые посещали все студенты
    if (numStudents > 0) { // Если есть студенты
        allStudentsDiscos = studentDiscos[0]; // Начинаем с первого студента
        for (int i = 1; i < numStudents; ++i) { // Для каждого студента
            allStudentsDiscos = allStudentsDiscos.Intersect(studentDiscos[i]); // Пересечение списков
        }
    }

    UniqueList<string> someStudentsDiscos; // Список дискотек, которые посещали некоторые студенты
    for (int i = 0; i < numStudents; ++i) { // Для каждого студента
        someStudentsDiscos = someStudentsDiscos.Union(studentDiscos[i]); // Объединение списков
    }

    UniqueList<string> noStudentsDiscos; // Список дискотек, которые не посещал ни один студент
    for (const string& disco : discoList) { // Для каждой дискотеки
        noStudentsDiscos.add(disco); // Добавляем дискотеку в список
    }
    noStudentsDiscos = noStudentsDiscos.Except(someStudentsDiscos); 

    cout << "\nДискотеки, которые посещали все студенты:" << endl; 
    allStudentsDiscos.print(); // Вывод списка

    cout << "\nДискотеки, которые посещали некоторые студенты:" << endl; 
    someStudentsDiscos.print(); // Вывод списка

    cout << "\nДискотеки, которые не посещал ни один студент:" << endl; 
    noStudentsDiscos.print(); // Вывод списка
}

void solveTask4() { 
    string filename; // Имя файла
    cout << "Введите имя файла: ";
    cin >> filename; // Ввод имени файла

    ifstream file(filename); 
    if (!file.is_open()) { // Если файл не открыт
        cout << "Не удалось открыть файл!" << endl; 
        return;
    }

    string word; // Слово
    set<char> symbols; // Множество для хранения символов
    int wordCount = 0; // Счетчик слов

    while (file >> word) { // Пока есть слова в файле
        wordCount++; // Увеличиваем счетчик слов
        if (wordCount % 2 == 0) { // Если номер слова четный
            for (char c : word) { // Для каждого символа в слове
                symbols.insert(c); // Добавляем символ в множество
            }
        }
    }

    file.close();

    cout << "Символы, встречающиеся в словах с четными номерами (в алфавитном порядке):" << endl; 
    for (char c : symbols) { // Для каждого символа в множестве
        cout << c << " "; // Выводим символ
    }
    cout << endl; // Переход на новую строку
}

// Функция для чтения данных абитуриентов из файла
void readApplicantsFromFile(const string& filename, Dictionary<string, tuple<int, int, int>>& applicants) {
    ifstream file(filename); // Открываем файл для чтения
    if (!file.is_open()) { // Проверяем, удалось ли открыть файл
        cout << "Не удалось открыть файл!" << endl; // Если нет, выводим сообщение об ошибке
        return; // Завершаем выполнение функции
    }

    string line; // Строка для хранения каждой строки из файла
    while (getline(file, line)) { // Читаем файл построчно
        stringstream ss(line); // Создаем поток строки для разбора данных
        string lastName, firstName; // Переменные для фамилии и имени
        int score1, score2, score3; // Переменные для трех оценок

        // Разбираем строку на фамилию, имя и три оценки
        if (!(ss >> lastName >> firstName >> score1 >> score2 >> score3) ||
            score1 < 0 || score2 < 0 || score3 < 0) { // Проверяем корректность данных
            cout << "Некорректные данные абитуриента. Пропуск строки: " << line << endl; // Если данные некорректны, выводим сообщение
            continue; // Переходим к следующей строке
        }

        string fullName = lastName + " " + firstName; // Формируем полное имя
        applicants.add(fullName, make_tuple(score1, score2, score3)); // Добавляем данные в словарь
    }

    file.close(); // Закрываем файл
}

// Функция для решения задачи 5
void solveTask5() {
    string filename; // Переменная для хранения имени файла
    cout << "Введите имя файла с данными абитуриентов: ";
    cin >> filename; // Считываем имя файла

    Dictionary<string, tuple<int, int, int>> applicants; // Создаем словарь для хранения данных абитуриентов
    readApplicantsFromFile(filename, applicants); // Читаем данные из файла

    vector<string> admitted; // Вектор для хранения допущенных абитуриентов
    for (const auto& [name, scores] : applicants.getData()) { // Проходим по всем абитуриентам
        // Проверяем, соответствуют ли оценки условиям допуска
        if (get<0>(scores) >= 30 && get<1>(scores) >= 30 && get<2>(scores) >= 30 &&
            get<0>(scores) + get<1>(scores) + get<2>(scores) >= 140) {
            admitted.push_back(name); // Добавляем абитуриента в список допущенных
        }
    }

    sort(admitted.begin(), admitted.end()); // Сортируем список допущенных абитуриентов

    cout << "Абитуриенты, допущенные к сдаче экзаменов в первом потоке (в алфавитном порядке):" << endl;
    for (const string& name : admitted) { // Проходим по всем допущенным абитуриентам
        cout << name << endl; // Выводим имя абитуриента
    }
}


int main() { 
    int choice; 

    while (true) { 
        cout << "\nВыберите задание:" << endl;
        cout << "1. Однонаправленный список (Переворот списка)" << endl; 
        cout << "2. Двунаправленный список (Вставка элемента вокруг другого)" << endl; 
        cout << "3. Уникальный список (Дискотеки и студенты)" << endl; 
        cout << "4. Уникальный список (Анализ текстового файла)" << endl; 
        cout << "5. Словарь (Результаты тестирования абитуриентов)" << endl; 
        cout << "0. Выход" << endl; 
        cout << "Ваш выбор: "; 
        cin >> choice; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов

        switch (choice) { 
            case 1: { 
                SinglyLinkedList<double> list; // Создание однонаправленного списка
                cout << "Введите элементы списка (через пробел, окончание - любой нечисловой символ):" << endl; 
                double value; // Значение элемента
                while (cin >> value) { // Пока ввод корректен
                    list.add(value); // Добавляем элемент в список
                }
                cin.clear(); // Очистка состояния потока
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов

                cout << "Исходный список: "; 
                list.print(); 
                list.reverse(); // Переворот списка
                cout << "Перевернутый список: ";
                list.print(); 
                break;
            }
            case 2: {
                DoublyLinkedList<double> list; // Создание двунаправленного списка
                cout << "Введите элементы списка (через пробел, окончание - любой нечисловой символ):" << endl; 
                double value; // Значение элемента
                while (cin >> value) { // Пока ввод корректен
                    list.add(value); // Добавляем элемент в список
                }
                cin.clear(); // Очистка состояния потока
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов
                double e, f; // Элементы для вставки
                cout << "Введите элемент E, вокруг которого нужно вставить: "; // Запрос элемента E
                cin >> e; // Ввод элемента E
                cout << "Введите элемент F, который нужно вставить: "; // Запрос элемента F
                cin >> f;
                list.insertAround(e, f); // Вставка элемента F вокруг элемента E
                cout << "Результат: "; 
                list.print();
                break;
            }
            case 3: 
                solveTask3(); 
                break;
            case 4:
                solveTask4(); 
                break;
            case 5:
                solveTask5();
                break;
            case 0: 
                cout << "Выход из программы." << endl; 
                return 0; 
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl; 
        }
    }

    return 0; 
}
