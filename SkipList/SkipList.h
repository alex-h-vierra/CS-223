//
// Created by alexv on 5/20/2023.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include "ComputerScientist.h"
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

class LLNode {
public:
    int level;
    int id;
    LLNode *next;
    LLNode *up;
    LLNode *down;

    //Initialize class members from constructor arguments
    //by using a member initializer list.
    //This method uses direct initialization, which is more
    //efficient than using assignment operators inside the constructor body.
    explicit LLNode(int key, LLNode *next = nullptr,
                    LLNode *up = nullptr, LLNode *down = nullptr, int level = 0)
            : next(next), up(up), down(down), id(key), level(level) {
    }
}; // end of LLNode class

class SkipList {
    LLNode *tower[25]{};
public:
    SkipList() {
        srand(time(nullptr));
        for (int i = 0; i < 25; i++) {
            tower[i] = new LLNode(1000000);
            tower[i]->level = i;
        }
        for (int i = 0; i < 25; i++) {
            if (i != 0) {
                tower[i]->down = tower[i - 1];
            }
            if (i != 24) {
                tower[i]->up = tower[i + 1];
            }
        }
    }

    ~SkipList() {
        for (int i = 24; i > 0; i--) {
            delete[] tower[i];
        }
    }

    static bool coinFlip() {
        int random = 1 + (rand() % 100);
        if (random > 50) {
            return true;
        }
        return false;
    }

    void printSkipList() {
        for (int i = 24; i >= 0; i--) {
            LLNode *iterator = tower[i];
            cout << "Level " << tower[i]->level << ": ";
            iterator = iterator->next;
            while (iterator != nullptr) {
                cout << iterator->id << ", ";
                iterator = iterator->next;
            }
            cout << endl;
        }
    }

    bool insert(LLNode *idNode, int level) {
        LLNode *iterator = tower[level];
        if (level > 25) {
            iterator = tower[0];
            idNode->level = 0;
        }
        while (iterator != nullptr) {
            if (iterator->next == nullptr) {
                if (level == 0 || iterator->down != nullptr) {
                    if (level == 0 || iterator->down->next != nullptr) {
                        iterator->next = idNode;
                        return true;
                    }
                }
                return false;
            }
            else if (iterator->next->id >= idNode->id) {
                if (iterator->id < idNode->id) {
                    if (coinFlip()) {
                        idNode->level++;
                        insert(idNode, idNode->level);
                        if (iterator->up == nullptr &&
                            iterator->level + 1 == idNode->level) {
                            iterator->up = idNode;
                        }
                        if (idNode->down == nullptr &&
                            iterator->level == idNode->level - 1) {
                            idNode->down = iterator;
                        }
                        return true;
                    }
                }
                if (iterator->down != nullptr || level == 0) {
                    if (level == 0 || iterator->down->next != nullptr) {
                        LLNode *temp = iterator->next;
                        iterator->next = idNode;
                        idNode->next = temp;
                        return true;
                    }
                }
                else {
                    if (idNode->level != 0) {
                        idNode->level--;
                    }
                    insert(idNode, idNode->level);
                    return false;
                }
            }
            else {
                iterator = iterator->next;
            }
        }
        return false;
    }

    LLNode *searchForID(int id) {
        for (int i = 24; i >= 0; i--) {
            LLNode *iterator = tower[i];
            iterator = iterator->next;
            while (iterator != nullptr) {
                if (iterator->id == id) {
                    return iterator;
                }
                iterator = iterator->next;
            }
        }
        cout << endl << "DID NOT FIND NODE ID: " << id << endl << endl;
        return nullptr;
    }

    /*
     * this function will delete the selected node to delete
     * as well as anything above the selected node
    */
    bool deleteElement(int id) {
        LLNode *temp = searchForID(id);
        int levelToDelete = 0;
        if (temp == nullptr) {
            return false;
        }
        LLNode *iterator = tower[temp->level];
        for (int i = 0; temp != nullptr; i++) {
            //gets count of how many about selected node to delete
            temp = temp->up;
            levelToDelete++;
        }
        //this while loop will take care of deleting the node selected as
        // well as everything above
        while (iterator != nullptr) {
            if (iterator->next->id == id){
                LLNode *nodeHolder = iterator->next;
                if (nodeHolder->next != nullptr){
                    if (nodeHolder->down != nullptr){
                        nodeHolder->down->up = nullptr;
                    }
                    iterator->next = nodeHolder->next;
                    delete nodeHolder;
                }
                //iterator is equal to before the node
                for (int i = 0; i <= levelToDelete; i++){
                    if (iterator->up != nullptr){
                        nodeHolder = iterator->next;
                        iterator->next = nodeHolder->next;
                        delete nodeHolder;
                    }
                    else{
                        //iterator is equal to the node
                        iterator = iterator->next;
                        for (int j = i; j < levelToDelete; j++){
                            if (iterator->up != nullptr){
                                nodeHolder = iterator;
                                iterator = iterator->up;
                                delete nodeHolder;
                            }
                            else{
                                delete iterator;
                            }
                        }
                        return true;
                    }
                    iterator = iterator->up;
                }
                return true;
            }
            iterator = iterator->next;
        }
        return false;
    }
};

#endif //SKIPLIST_SKIPLIST_H
