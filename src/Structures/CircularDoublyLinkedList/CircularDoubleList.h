#ifndef SCRABBLE___CIRCULARDOUBLELIST_H
#define SCRABBLE___CIRCULARDOUBLELIST_H

#include <iostream>
#include "CircularDoubleNode.h"

using namespace std;

template<class T>
class CircularDoubleList {
private:
    CircularDoubleNode<T> *firstNode;

    bool isEmpty();

public:
    CircularDoubleList();
    ~CircularDoubleList();
    void addNode(T object);
    void readStartNodes();
    void readEndNodes();
    void updateNode(T oldObject, T newObject);
    void deleteSpecificNode(T object);
    CircularDoubleNode<T> *searchNode(T object);
    CircularDoubleNode<T> *getLastNode();
};


template<class T>
CircularDoubleList<T>::CircularDoubleList() {
    firstNode = nullptr;
}

template<class T>
CircularDoubleList<T>::~CircularDoubleList() {
}

template<class T>
bool CircularDoubleList<T>::isEmpty() {
    return firstNode == nullptr;
}

template<class T>
void CircularDoubleList<T>::addNode(T object) {
    CircularDoubleNode<T> *newNode = new CircularDoubleNode<T>(object);
    CircularDoubleNode<T> *lastNode;

    if (firstNode != nullptr) {
        newNode->setNextNode(firstNode->getNextNode());
        newNode->setPreviousNode(firstNode);
        firstNode->setNextNode(newNode);
    }
    firstNode = newNode;

    lastNode = getLastNode();
    if (lastNode != nullptr) {
        lastNode->getNextNode()->setPreviousNode(newNode);
    }
}

template<class T>
void CircularDoubleList<T>::readStartNodes() {
    if (!isEmpty()) {
        CircularDoubleNode<T> *auxiliaryNode = firstNode->getNextNode();
        do {
            cout <<auxiliaryNode->getPreviousNode()->getObject() << " <--> ";
            cout << auxiliaryNode->getObject() << " <--> ";
            cout << auxiliaryNode->getNextNode()->getObject() << endl;
            auxiliaryNode = auxiliaryNode->getNextNode();
        } while (auxiliaryNode != firstNode->getNextNode());
        cout << endl;
    }
}

template<class T>
void CircularDoubleList<T>::readEndNodes() {
    if (!isEmpty()) {
        CircularDoubleNode<T> *auxiliaryNode = getLastNode();
        do {
            cout <<auxiliaryNode->getPreviousNode()->getObject() << " <--> ";
            cout << auxiliaryNode->getObject() << " <--> ";
            cout << auxiliaryNode->getNextNode()->getObject() << endl;
            auxiliaryNode = auxiliaryNode->getPreviousNode();
        } while (auxiliaryNode != firstNode);
        cout << endl;
    }
}

template<class T>
void CircularDoubleList<T>::updateNode(T oldObject, T newObject) {
    CircularDoubleNode<T> *node = searchNode(oldObject);
    if (node != nullptr) {
        node->setObject(newObject);
    }
}

template<class T>
void CircularDoubleList<T>::deleteSpecificNode(T object) {
    if (!isEmpty()) {
        CircularDoubleNode<T> *auxiliaryNode = searchNode(object);
        if (auxiliaryNode != nullptr) {
            CircularDoubleNode<T> *previousNode = auxiliaryNode->getPreviousNode();
            CircularDoubleNode<T> *nextNode = auxiliaryNode->getNextNode();

            previousNode->setNextNode(auxiliaryNode->getNextNode());
            nextNode->setPreviousNode(auxiliaryNode->getPreviousNode());

            if (firstNode == auxiliaryNode) {
                if (firstNode == previousNode && firstNode == nextNode) {
                    firstNode = nullptr;
                } else {
                    firstNode = firstNode->getPreviousNode();
                    firstNode->setNextNode(nextNode);
                }
            }
        }
    }
}

template<class T>
CircularDoubleNode<T> *CircularDoubleList<T>::searchNode(T object) {
    CircularDoubleNode<T> *auxiliaryNode = firstNode;
    do {
        if (auxiliaryNode->getObject() == object) {
            return auxiliaryNode;
        } else {
            auxiliaryNode = auxiliaryNode->getNextNode();
        }
    } while (auxiliaryNode != firstNode);
    return nullptr;
}

template<class T>
CircularDoubleNode<T> *CircularDoubleList<T>::getLastNode() {
    CircularDoubleNode<T> *lastNode = firstNode;
    if (firstNode != nullptr) {
        do {
            lastNode = lastNode->getNextNode();
        } while (lastNode != firstNode);
    }
    return lastNode;
}

#endif //SCRABBLE___CIRCULARDOUBLELIST_H