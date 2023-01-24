# cpp-single-linked-list
Аналог шаблонного класса forvard_list из стандартной библиотеки. Ноды создаются в куче и хранят в себе данные и указатель на следующую ноду в списке.
Реализован собственный иетратор типа Forward iterator. Для итератора определены операторы сравнения, разыменования, доступа, посфиксный и префиксный инкременты.

## Работа с классом SingleLinkedList
#### Создание списка:
Конструктор по умолчанию.
```CPP
SingleLinkedList<int> list;
```
Конструктор принимающий список инициализации.
```CPP
SingleLinkedList<int> list{1, 2, 3, 4, 5};
```
Копирующий конструктор.
```CPP
SingleLinkedList<int> non_empty_list{1, 2, 3, 4};
auto list_copy(non_empty_list);
```
Оператор присваивания.
```CPP
const SingleLinkedList<int> non_empty_list{1, 2, 3, 4};
SingleLinkedList<int> list_copy = non_empty_list;
```
#### Основные возможности:
Возврат константных/неконстантных итераторов на начало и конец списка, возможно использование в for-range циклах.
```CPP
SingleLinkedList<int> non_empty_list{1, 2, 3, 4};
for (auto elem : non_empty_list) {
    std::cout << elem << " ";
}
```
swap - обмен данными двух списков.
```CPP
SingleLinkedList<int> non_empty_list1{1, 2, 3, 4};
SingleLinkedList<int> non_empty_list2{12, 13, 14, 15, 16};
non_empty_list1.swap(non_empty_list2);
for (auto elem : non_empty_list1) {
    std::cout << elem << " ";
}
```
 Возврат информации о состоянии списка :
 
 GetSize - текущий размер.
 
 IsEmpty - проверка на пустоту.
 ```CPP
SingleLinkedList<int> non_empty_list{1, 2, 3, 4};
std::cout << non_empty_list.GetSize() << std::endl;
std::cout << std::boolalpha << non_empty_list.IsEmpty() << std::endl;
```
PushFront - добавление элемента в начало списка.

PushBack - добавление элемента в конец списка.

PopFront - удаление элемента из начала списка.
```CPP
SingleLinkedList<int> list;
list.PushFront(2);
list.PushFront(1);
list.PushFront(3);
list.Pushback(4);
list.PopFront();
for (auto elem : list) {
    std::cout << elem << " ";
}
```
InsertAfter - добавление элемента в произвольное место в списке (по итератору).

EraseAfter - удаление элемента в произвольное место в списке (по итератору).
```CPP
SingleLinkedList<int> list;
list.InsertAfter(list.cbefore_begin(), 1);
list.InsertAfter(list.cbefore_begin(), 2);
list.InsertAfter(list.cbefore_begin(), 3);
list.InsertAfter(list.cbefore_begin(), 4);
list.EraseAfter(list.cbegin());
for (auto elem : list) {
    std::cout << elem << " ";
}
```
Операторы сравнения для двух списков (лексикографически, поэлементно).
```CPP
SingleLinkedList<int> list1 = {1, 2, 3, 4, 5};
SingleLinkedList<int> list2 = {1, 2, 3, 4, 6};
std::cout << std::boolalpha << (list2 > list1);
```
## Использование
Скопируйте файл singlelinkedlist.h в папку с вашим проектом и подключите через директиву #include<single-linked-list.h>
## Системные требования
Компилятор С++ с поддержкой стандарта C++17 или новее
