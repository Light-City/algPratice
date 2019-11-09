//
// Created by light on 19-10-31.
//

#include "array.h"

class Student {
private:
    string name;
    int score;
public:
    Student(string name = "", int score = 0) {
        this->name = name;
        this->score = score;
    }

    friend ostream &operator<<(ostream &out, Student &student) {
        out << "name : " << student.name << ", " << " score : " << student.score;
        return out;
    }

    bool operator==(const Student &student) {
        return this->name == student.name && this->score == student.score;
    }
};

class A {
private:
    string name;
    int age;

    void init(string name, int age) {
        this->name = name;
        this->age = age;
    }

public:
    A(string name, int age) {
        init(name, age);
    }

    A() {
        init("bob",20);
    }

    void print() {
        cout << name << " " << age << endl;
    }
    // ...
    // ...
};


// 测试文件
int main() {
    Array<int> array;

    for (int i = 0; i < 10; i++) array.addLast(i);
    cout << array;

    array.add(1, 100);
    cout << array;

    array.addFirst(-1);
    cout << array;

    cout << array.get(5) << endl;
    array.set(0, 10);
    cout << array.get(0) << endl;
    cout << array;

    cout << array.contains(11) << endl;

    cout << array.find(8) << endl;  // index=10

    array.remove(10);
    cout << array.find(8) << endl;  // not found
    cout << array;
    array.removeFirst();
    cout << array;
    array.removeLast();
    cout << array;
    array.removeElement(100);
    cout << array;


    Array<Student> *array1 = new Array<Student>(20);
    array1->addLast(Student("Alice", 100));
    array1->addLast(Student("Bob", 66));
    array1->addLast(Student("Charlie", 88));
    cout << *array1;
    array1->removeElement(Student("Bob", 66));
    cout << *array1;
//    array1->~Array();
    delete array1;

    return 0;
}
