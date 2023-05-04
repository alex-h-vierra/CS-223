#include "BSTInterface.h"
#include <string>

using namespace std;

template<typename KeyComparable, typename Value>
class BinarySearchTree : BSTInterface<KeyComparable, Value> {
private:
    /*
    * Private "Node" Class...for this implementation, the Pair is the Node
    */
    class Pair {
    public:
        KeyComparable key;
        Value value;

        //Initialize class members from constructor arguments
        //by using a member initializer list.
        //This method uses direct initialization, which is more
        //efficient than using assignment operators inside the constructor body.
        Pair(KeyComparable &key, Value &value)
                : value{value}, key{key} {
            // empty constructor...member initializer is doing all the work
        }

    };   // end of Pair class

    // number of values stored in the tree
    int count = 0;
    // capacity of array holding the tree
    int size = 25;
    // the array that holds the pairs
    Pair **root = new Pair *[size];

    /*
    * Prints the data of the trea in order based on the key to the output stream
    */
    void printTree(int index, std::ostream &out) const {
        if (root[index] != nullptr) {
            if (index * 2 <= size) {
                if (root[index * 2] != nullptr) {
                    printTree(index * 2, out);
                }
            }
            out << *(root[index]->value) << endl;
            if (index * 2 + 1 <= size) {
                if (root[index * 2 + 1] != nullptr) {
                    printTree(index * 2 + 1, out);
                }
            }
        }
    }

public:
    BinarySearchTree() {
        for (int i = 0; i < size; i++) {
            root[i] = nullptr;
        }
    }

    ~BinarySearchTree() {
        //  stub code: needs to be implemented
        for (int i = 0; i < size; i++) {
            delete root[i];
        }
        delete[] root;
    }

    /*
    * Finds the node with the smallest element in the tree
    */
    const Value findMin() const {
        int i = 1;
        while (root[i] != nullptr) {
            if (root[i * 2] == nullptr) {
                return root[i]->value;
            }
            i *= 2;
        }
        return root[i]->value;
    }

    /*
    * Finds the node with the largest element in the tree
    */
    const Value findMax() const {
        int i = 1 * 2 + 1;
        while (root[i] != nullptr) {
            if (root[i * 2] == nullptr) {
                return root[i]->value;
            }
            i = i * 2;
        }
        return root[i]->value;
    }

    /*
    * Finds the node with a key that matches the argKey
    * updates the founditem refrerence if found
    * returns true if it was found
    * returns false if it was not
    */
    bool find(const KeyComparable &argKey, Value &founditem) const {
        int i = 1;
        while (root[i] != nullptr) {
            if (root[i]->key == argKey) {
                founditem = root[i]->value;
                return true;
            }
            else if (root[i]->key > argKey) {
                i = i * 2;
            }
            else if (root[i]->key < argKey) {
                i = i * 2 + 1;
            }
        }
        return false;
    }

    /*
    * Returns true if the item is found in the tree
    */
    bool contains(const KeyComparable &argKey) const {
        int i = 1;
        for (; root[i] != nullptr && root[i]->key != argKey; i = 2 * i +
                                                                 (root[i]->key < argKey));
        return root[i] != nullptr;
    }

    /*
    * Returns true if tree has no nodes
    */
    bool isEmpty() const {
        return root[1] == nullptr;
    }

    /*
    * Prints all the data from the tree in order based on key
    */
    void printTree(std::ostream &out = cout) const {
        printTree(1, out);
    }

    /*
    * Removes all nodes from the tree
    */
    void makeEmpty() {
        for (int i = 0; i < size; count++) {
            root[i] = nullptr;
        }
    }

    /*
    * Inserts a node into the tree
    * maintains this property of the tree:
    *     All nodes to the left will be less
    *     All nodes to the right will be greater
    */
    bool insert(Value value, KeyComparable key) {
        Pair *node = new Pair(key, value);
        int i = 1;
        if (isEmpty()) {
            count++;
            root[i] = node;
            cout << root[i]->key << " ";
            return true;
        }
        while (i < size) {
            if (i * 4 > size) {
                checkSize(i * 2 + 1);
            }
            if (root[i]->key > node->key) {
                //This goes to the left child
                if (root[i * 2] == nullptr) {
                    count++;
                    root[i * 2] = node;
                    return true;
                }
                i = i * 2;
            }
            else if (root[i]->key < node->key) {
                if (root[i * 2 + 1] == nullptr) {
                    count++;
                    root[i * 2 + 1] = node;
                    return true;
                }
                i = i * 2 + 1;
            }
            else {
                delete node;
                return false;
            }
        }
        return false;
    }

/*
* Removes the nodes if it contains the given item
*/
    void remove(const KeyComparable &key) {
        Value temp;
        int iterator = 1;
        if (find(key, temp) == false) {
            return;
        }
        while (iterator <= size) {
            if (root[iterator]->key > key) {
                iterator = iterator * 2;

            }
            else if (root[iterator]->key < key) {
                iterator = iterator * 2 + 1;
            }
            else {
                if (root[iterator * 2] == nullptr && root[iterator * 2 + 1] == nullptr
                    || iterator * 2 + 1 > size) {
                    root[iterator] = nullptr;
                    return;
                }
                else if (root[iterator * 2] != nullptr &&
                         root[iterator * 2 + 1] != nullptr) {
                    Value max = findMax();
                    for (int i = iterator; i <= size; i++) {
                        if (root[i]->value == max) {
                            Pair *temp1 = new Pair(root[i]->key, root[i]->value);
                            remove(root[i]->key);
                            root[iterator] = nullptr;
                            root[iterator] = temp1;
                            count--;
                            return;
                        }
                    }
                }
                else {
                    if (root[iterator * 2] != nullptr) {
                        orphan(iterator * 2);
                        return;
                    }
                    else {
                        orphan(iterator * 2 + 1);
                        return;
                    }
                }
            }
        }
    }

    int getSize() {
        return size;
    }

    int getCount() {
        return count;
    }

    void checkSize(const int futureSize) {
        int pastSize = size;
        while (futureSize > size) {
            size = size * 4;
        }
        Pair **temp = new Pair *[size];
        for (int i = 0; i != pastSize; i++) {
            temp[i] = root[i];
            if (root[i] == nullptr) {
                temp[i] = nullptr;
            }

        }
        for (int j = pastSize; j != size; j++) {
            temp[j] = nullptr;
        }
        delete[] root;
        root = temp;
    }

    void orphan(int index) {
        if (index <= size) {
            if (root[index * 2] != nullptr && root[index * 2 <= size]) {
                orphan(index * 2);
            }
            root[index / 2] = root[index];
            root[index] = nullptr;
        }
        if (index <= size) {
            if (root[index * 2 + 1] != nullptr && root[index * 2 + 1 <= size]) {
                orphan(index * 2 + 1);
            }
        }
    }
};    // end of BinarySearchTree class
