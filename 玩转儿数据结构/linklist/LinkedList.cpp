//
// Created by light on 19-11-8.
//

#include "LinkedList.h"
#include "../stack/LinkedListStack.h"
#include "../queue/LinkedListQueue.h"

int main() {
    LinkedList<int> *linkedList = new LinkedList<int>;

    for (int i = 0; i < 10; i++) {
        linkedList->add(i, i);
    }

    cout << linkedList->get(9) << endl;
    cout << linkedList->getSize() << endl;

    cout << *linkedList << endl;
    linkedList->addFirst(100);
    cout << *linkedList << endl;
    linkedList->addLast(101);
    cout << *linkedList << endl;
    cout << linkedList->contains(101) << endl;

    linkedList->remove(2);      // index=2 delete 1
    cout << *linkedList << endl;

    linkedList->removeFirst();
    cout << *linkedList << endl;

    linkedList->removeLast();
    cout << *linkedList << endl;

    delete linkedList;



    LinkedListStack<int> *stack = new LinkedListStack<int>();

    for (int i = 0; i < 5; i++) {
        stack->push(i);
        cout << *stack << endl;
    }

    stack->pop();
    cout << *stack << endl;

    cout << stack->peek() << endl;

    delete stack;


    LinkedListQueue<int> *queue= new LinkedListQueue<int>();

    for (int i = 0; i < 5; i++) {
        queue->enqueue(i);
        cout << *queue<< endl;
    }

    queue->dequeue();
    cout << *queue<< endl;

    cout << queue->getFront() << endl;

    delete queue;

    return 0;
}