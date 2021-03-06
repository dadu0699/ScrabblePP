#ifndef SCRABBLE___SIMPLELIST_H
#define SCRABBLE___SIMPLELIST_H

#include <iostream>
#include "SimpleNode.h"

using namespace std;

class SimpleList
{
private:
    SimpleNode *firstNode;
    SimpleNode *lastNode;

    bool isEmpty();
    void sortList();

public:
    SimpleList();
    ~SimpleList();

    SimpleNode* getFirstNode() const;
    SimpleNode* getLastNode() const;

    void addFirstNode(int score);
    void addLastNode(int score);
    void readNodes();
    void updateNode(int oldScore, int newScore);
    void deleteFirstNode();
    void deleteLastNode();
    void deleteSpecificNode(int score);
    SimpleNode *searchNode(int score);
    void report();
};

#endif //SCRABBLE___SIMPLELIST_H
