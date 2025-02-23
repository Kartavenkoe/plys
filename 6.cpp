#include <iostream> // Подключение библиотеки для ввода-вывода
#include <string> // Подключение библиотеки для работы со строками
#include <algorithm> // Подключение библиотеки для алгоритмов
#include <fstream> // Подключение библиотеки для работы с файлами
#include <limits> // Подключение библиотеки для работы с числовыми пределами
#include <vector> // Подключение библиотеки для работы с динамическими массивами
#include <map> // Подключение библиотеки для работы с ассоциативными массивами
#include <set> // Подключение библиотеки для работы с множествами
#include <sstream> // Подключение библиотеки для работы с потоками строк
#include <tuple> // Подключение библиотеки для работы с кортежами

using namespace std; // Использование пространства имен std

// Задание 1: Однонаправленный список
template <typename T> //  для работы с любым типом данных
class SinglyLinkedList { // Класс для однонаправленного списка
private:
    struct Node { // Структура для узла списка
        T data; // Данные узла
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
        } else { // Если список не пуст
            Node* current = head; // Начинаем с первого узла
            while (current->next) { // Ищем последний узел
                current = current->next;
            }
            current->next = newNode; // Добавляем новый узел в конец
        }
    }

    void remove(T data) { // Метод удаления элемента из списка
        if (!head) return; // Если список пуст, выходим

        if (head->data == data) { // Если удаляемый элемент - первый
            Node* temp = head; // Сохраняем указатель на первый узел
            head = head->next; // Перемещаем указатель на следующий узел
            delete temp; // Удаляем старый первый узел
            return;
        }

        Node* current = head; // Начинаем с первого узла
        while (current->next) { // Ищем узел перед удаляемым
            if (current->next->data == data) { // Если найден удаляемый элемент
                Node* temp = current->next; // Сохраняем указатель на удаляемый узел
                current->next = current->next->next; // Переставляем указатели
                delete temp; // Удаляем узел
                return;
            }
            current = current->next; // Переходим к следующему узлу
        }
    }

    // Задача 1: Переворот списка
    void reverse() { // Метод переворота списка
        Node* prev = nullptr; // Указатель на предыдущий узел
        Node* current = head; // Указатель на текущий узел
        Node* next = nullptr; // Указатель на следующий узел

        while (current) { // Пока не достигнут конец списка
            next = current->next; // Сохраняем следующий узел
            current->next = prev; // Переворачиваем указатель текущего узла
            prev = current; // Перемещаем указатель на предыдущий узел
            current = next; // Перемещаем указатель на следующий узел
        }

        head = prev; // Обновляем указатель на первый узел
    }

    void print() const { // Метод вывода списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнут конец списка
            cout << current->data << " "; // Выводим данные узла
            current = current->next; // Переходим к следующему узлу
        }
        cout << endl; // Переход на новую строку
    }

    ~SinglyLinkedList() { // Деструктор списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнут конец списка
            Node* next = current->next; // Сохраняем следующий узел
            delete current; // Удаляем текущий узел
            current = next; // Переходим к следующему узлу
        }
    }
};

// Задание 2: Двунаправленный список 
template <typename T> // Шаблон для работы с любым типом данных
class DoublyLinkedList { // Класс для двунаправленного списка
private:
    struct Node { // Структура для узла списка
        T data; // Данные узла
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
        } else { // Если список не пуст
            tail->next = newNode; // Добавляем новый узел в конец
            newNode->prev = tail; // Обновляем указатель на предыдущий узел
            tail = newNode; // Обновляем указатель на последний узел
        }
    }

    void remove(T data) { // Метод удаления элемента из списка
        if (!head) return; // Если список пуст, выходим

        if (head->data == data) { // Если удаляемый элемент - первый
            Node* temp = head; // Сохраняем указатель на первый узел
            head = head->next; // Перемещаем указатель на следующий узел
            if (head) { // Если новый первый узел существует
                head->prev = nullptr; // Обновляем указатель на предыдущий узел
            } else { // Если список стал пустым
                tail = nullptr; // Обновляем указатель на последний узел
            }
            delete temp; // Удаляем старый первый узел
            return;
        }

        if (tail->data == data) { // Если удаляемый элемент - последний
            Node* temp = tail; // Сохраняем указатель на последний узел
            tail = tail->prev; // Перемещаем указатель на предыдущий узел
            tail->next = nullptr; // Обновляем указатель на следующий узел
            delete temp; // Удаляем старый последний узел
            return;
        }

        Node* current = head; // Начинаем с первого узла
        while (current) { // Ищем удаляемый элемент
            if (current->data == data) { // Если найден удаляемый элемент
                current->prev->next = current->next; // Обновляем указатель на следующий узел
                current->next->prev = current->prev; // Обновляем указатель на предыдущий узел
                delete current; // Удаляем узел
                return;
            }
            current = current->next; // Переходим к следующему узлу
        }
    }

    // Задача 2: Вставить элемент F слева и справа от элемента E
    void insertAround(T e, T f) { // Метод вставки элемента вокруг другого
        Node* current = head; // Начинаем с первого узла
        while (current) { // Ищем элемент E
            if (current->data == e) { // Если найден элемент E
                // Вставка справа
                Node* newRight = new Node(f); // Создание нового узла
                newRight->next = current->next; // Обновляем указатель на следующий узел
                newRight->prev = current; // Обновляем указатель на предыдущий узел
                if (current->next) { // Если существует следующий узел
                    current->next->prev = newRight; // Обновляем указатель на предыдущий узел
                } else { // Если E - последний узел
                    tail = newRight; // Обновляем указатель на последний узел
                }
                current->next = newRight; // Обновляем указатель на следующий узел

                // Вставка слева
                Node* newLeft = new Node(f); // Создание нового узла
                newLeft->prev = current->prev; // Обновляем указатель на предыдущий узел
                newLeft->next = current; // Обновляем указатель на следующий узел
                if (current->prev) { // Если существует предыдущий узел
                    current->prev->next = newLeft; // Обновляем указатель на следующий узел
                } else { // Если E - первый узел
                    head = newLeft; // Обновляем указатель на первый узел
                }
                current->prev = newLeft; // Обновляем указатель на предыдущий узел
                return;
            }
            current = current->next; // Переходим к следующему узлу
        }
    }

    void print() const { // Метод вывода списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнут конец списка
            cout << current->data << " "; // Выводим данные узла
            current = current->next; // Переходим к следующему узлу
        }
        cout << endl; // Переход на новую строку
    }

    ~DoublyLinkedList() { // Деструктор списка
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока не достигнут конец списка
            Node* next = current->next; // Сохраняем следующий узел
            delete current; // Удаляем текущий узел
            current = next; // Переходим к следующему узлу
        }
    }
};

// Задание 34: Неупорядоченный список уникальных элементов
template <typename T> // Шаблон для работы с любым типом данных
class UniqueList { // Класс для неупорядоченного списка уникальных элементов
private:
    set<T> data; // Множество для хранения уникальных элементов

public:
    void add(T item) { // Метод добавления элемента
        data.insert(item); // Вставка элемента в множество
    }

    void remove(T item) { // Метод удаления элемента
        data.erase(item); // Удаление элемента из множества
    }

    UniqueList<T> Union(const UniqueList<T>& other) const { // Метод объединения списков
        UniqueList<T> result = *this; // Копируем текущий список
        for (const auto& item : other.data) { // Для каждого элемента другого списка
            result.add(item); // Добавляем элемент в результат
        }
        return result; // Возвращаем результат
    }

    UniqueList<T> Except(const UniqueList<T>& other) const { // Метод исключения элементов другого списка
        UniqueList<T> result = *this; // Копируем текущий список
        for (const auto& item : other.data) { // Для каждого элемента другого списка
            result.remove(item); // Удаляем элемент из результата
        }
        return result; // Возвращаем результат
    }

    UniqueList<T> Intersect(const UniqueList<T>& other) const { // Метод пересечения списков
        UniqueList<T> result; // Создаем пустой результат
        for (const auto& item : data) { // Для каждого элемента текущего списка
            if (other.contains(item)) { // Если элемент содержится в другом списке
                result.add(item); // Добавляем элемент в результат
            }
        }
        return result; 
    }

    bool contains(const T& item) const { // Метод проверки наличия элемента
        return data.count(item) > 0; // Возвращаем true, если элемент найден
    }

    void print() const { // Метод вывода списка
        for (const auto& item : data) { // Для каждого элемента списка
            cout << item << " "; // 
        }
        cout << endl; // Переход на новую строку
    }

    ~UniqueList() {} // Деструктор списка
};

// Задание 5: Словарь
template <typename K, typename V> // Шаблон для работы с любым типом данных
class Dictionary { // Класс для словаря
private:
    map<K, V> data; // Ассоциативный массив для хранения пар ключ-значение

public:
    void add(const K& key, const V& value) { // Метод добавления элемента
        data[key] = value; // Вставка пары ключ-значение в массив
    }

    void remove(const K& key) { // Метод удаления элемента
        data.erase(key); // Удаление пары ключ-значение из массива
    }

    V get(const K& key) const { // Метод получения значения по ключу
        auto it = data.find(key); // Поиск пары ключ-значение
        if (it != data.end()) { // Если пара найдена
            return it->second; // Возвращаем значение
        }
        return V(); // Возвращаем значение по умолчанию, если пара не найдена
    }

    bool contains(const K& key) const { // Метод проверки наличия ключа
        return data.count(key) > 0; // Возвращаем true, если ключ найден
    }

    void print() const { // Метод вывода словаря
        for (const auto& pair : data) { // Для каждой пары ключ-значение
            cout << pair.first << ": " << pair.second << endl; // Выводим пару
        }
    }

    map<K, V> getData() const { // Метод получения данных словаря
        return data; // Возвращаем данные словаря
    }

    ~Dictionary() {} // Деструктор словаря
};

// Функции для решения задач 

void solveTask3() { // Функция для решения задачи 3
    int numStudents, numDiscos; // Количество студентов и дискотек

    cout << "Введите количество студентов: "; // Запрос количества студентов
    cin >> numStudents; // Ввод количества студентов
    cout << "Введите количество дискотек: "; // Запрос количества дискотек
    cin >> numDiscos; // Ввод количества дискотек
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Игнорирование символа новой строки

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
        while (ss >> disco) { // Пока есть данные в потоке
            studentDiscos[i].add(disco); // Добавление дискотеки в список студента
        }
    }

    // Дискотеки, которые посещали все студенты
    UniqueList<string> allStudentsDiscos; // Список дискотек, которые посещали все студенты
    if (numStudents > 0) { // Если есть студенты
        allStudentsDiscos = studentDiscos[0]; // Инициализация списка дискотеками первого студента
        for (int i = 1; i < numStudents; ++i) { // Для каждого последующего студента
            allStudentsDiscos = allStudentsDiscos.Intersect(studentDiscos[i]); // Пересечение списков
        }
    }

    // Дискотеки, которые посещали некоторые студенты
    UniqueList<string> someStudentsDiscos; // Список дискотек, которые посещали некоторые студенты
    for (int i = 0; i < numStudents; ++i) { // Для каждого студента
        someStudentsDiscos = someStudentsDiscos.Union(studentDiscos[i]); // Объединение списков
    }

    // Дискотеки, которые не посещал ни один студент
    UniqueList<string> noStudentsDiscos; // Список дискотек, которые не посещал ни один студент
    for (const string& disco : discoList) { // Для каждой дискотеки
        noStudentsDiscos.add(disco); // Добавление дискотеки в список
    }
    noStudentsDiscos = noStudentsDiscos.Except(someStudentsDiscos); // Исключение посещенных дискотек

    cout << "\nДискотеки, которые посещали все студенты:" << endl; 
    allStudentsDiscos.print(); // Вывод списка

    cout << "\nДискотеки, которые посещали некоторые студенты:" << endl; 
    someStudentsDiscos.print(); // Вывод списка

    cout << "\nДискотеки, которые не посещал ни один студент:" << endl; 
    noStudentsDiscos.print(); // Вывод списка
}

void solveTask4() { // Функция для решения задачи 4
    string filename; // Имя файла
    cout << "Введите имя файла: "; // Запрос имени файла
    cin >> filename; // Ввод имени файла

    ifstream file(filename); 
    if (!file.is_open()) { 
        cout << "Не удалось открыть файл!" << endl; 
        return;
    }

    string word; // Слово
    set<char> symbols; // Множество для хранения символов
    int wordCount = 0; // Счетчик слов

    while (file >> word) { // Пока есть данные в файле
        wordCount++; // Увеличение счетчика слов
        if (wordCount % 2 == 0) { // Если номер слова четный
            for (char c : word) { // Для каждого символа в слове
                symbols.insert(c); // Вставка символа в множество
            }
        }
    }

    file.close(); 

    cout << "Символы, встречающиеся в словах с четными номерами (в алфавитном порядке):" << endl; // Вывод символов
    for (char c : symbols) { // Для каждого символа в множестве
        cout << c << " "; 
    }
    cout << endl; 
}

void solveTask5() { 
    int n; // Количество абитуриентов
    cout << "Введите количество абитуриентов/ Фамилия имя баллы за 3 экзамена через пробел: ";
    cin >> n; 
    cin.ignore();

    Dictionary<string, tuple<int, int, int>> applicants; // Словарь для хранения данных абитуриентов

    for (int i = 0; i < n; ++i) { // Для каждого абитуриента
        string line; // Строка для ввода
        getline(cin, line); // Ввод строки

        stringstream ss(line); // Поток строки
        string lastName, firstName; // Фамилия и имя
        int score1, score2, score3; // Оценки

        ss >> lastName >> firstName >> score1 >> score2 >> score3; // Ввод данных абитуриента

        string fullName = lastName + " " + firstName; // Полное имя
        applicants.add(fullName, make_tuple(score1, score2, score3)); // Добавление данных в словарь
    }

    vector<string> admitted; // Вектор для хранения допущенных абитуриентов
    for (const auto& [name, scores] : applicants.getData()) { // Для каждого абитуриента
        if (get<0>(scores) >= 30 && get<1>(scores) >= 30 && get<2>(scores) >= 30 &&
            get<0>(scores) + get<1>(scores) + get<2>(scores) >= 140) { // Если абитуриент допущен
            admitted.push_back(name); // Добавление абитуриента в вектор
        }
    }

    sort(admitted.begin(), admitted.end()); // Сортировка вектора

    cout << "Абитуриенты, допущенные к сдаче экзаменов в первом потоке (в алфавитном порядке):" << endl; // Вывод допущенных абитуриентов
    for (const string& name : admitted) { // Для каждого допущенного абитуриента
        cout << name << endl; // Вывод имени
    }
}

int main() { 
    int choice; 

    while (true) { // Бесконечный цикл
        cout << "\nВыберите задание:" << endl; 
        cout << "1. Однонаправленный список (Переворот списка)" << endl; 
        cout << "2. Двунаправленный список (Вставка элемента вокруг другого)" << endl; 
        cout << "3. Уникальный список (Дискотеки и студенты)" << endl; 
        cout << "4. Уникальный список (Анализ текстового файла)" << endl; 
        cout << "5. Словарь (Результаты тестирования абитуриентов)" << endl;
        cout << "0. Выход" << endl; 
        cout << "Ваш выбор: "; 
        cin >> choice; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Игнорирование символа новой строки

        switch (choice) { 
            case 1: { 
                SinglyLinkedList<int> list; // Создание однонаправленного списка
                cout << "Введите элементы списка (через пробел, окончание - любой нечисловой символ):" << endl; // Запрос элементов списка
                int value; // Значение элемента
                while (cin >> value) { // Пока есть данные в потоке
                    list.add(value);
                }
                cin.clear(); // Очистка потока
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование символа новой строки

                cout << "Исходный список: ";
                list.print(); 
                list.reverse(); 
                cout << "Перевернутый список: "; 
                list.print(); 
                break;
            }
            case 2: { 
                DoublyLinkedList<int> list; // Создание двунаправленного списка
                cout << "Введите элементы списка (через пробел, окончание - любой нечисловой символ):" << endl;
                int value; // Значение элемента
                while (cin >> value) { // Пока есть данные в потоке
                    list.add(value); 
                }
                cin.clear(); // Очистка потока
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование символа новой строки
                int e, f; 
                cout << "Введите элемент E, вокруг которого нужно вставить: "; 
                cin >> e; // Ввод элемента E
                cout << "Введите элемент F, который нужно вставить: "; 
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
