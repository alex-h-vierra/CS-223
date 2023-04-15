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
    int size = 50;
    // the array that holds the pairs
    Pair **root = new Pair *[size];

    /*
    * Prints the data of the trea in order based on the key to the output stream
    */
    void printTree(int index, std::ostream &out) const {
        //  stub code: needs to be implemented
        if (root[index] != nullptr) {
            printTree(index * 2, out);
            out << root[index] << endl;
            printTree(index * 2 + 1, out);
        }
    }

public:
    BinarySearchTree() {
        for (int i = 0; i <= size; i++) {
            root[i] = nullptr;
        }
    }

    ~BinarySearchTree() {
        //  stub code: needs to be implemented
        for (int i = 0; i <= size; i++)
        {
            delete root[i];
        }
    }

    /*
    * Finds the node with the smallest element in the tree
    */
    const Value findMin() const {
        //  stub code: needs to be implemented
        return nullptr;
    }

    /*
    * Finds the node with the largest element in the tree
    */
    const Value findMax() const {
        //  stub code: needs to be implemented
        return nullptr;
    }

    /*
    * Finds the node with a key that matches the argKey
    * updates the founditem refrerence if found
    * returns true if it was found
    * returns false if it was not
    */
    bool find(const KeyComparable &argKey, Value &founditem) const {
        //  stub code: needs to be implemented
        return false;
    }

    /*
    * Returns true if the item is found in the tree
    */
    bool contains(const KeyComparable &argKey) const {
        //  stub code: needs to be implemented
        int i = 0;
        for (; root[i] != nullptr && root[i]->key != argKey; i = 2 * i +
                                                                 (root[i]->key < argKey));
        return root[i] != nullptr;
    }

    /*
    * Returns true if tree has no nodes
    */
    bool isEmpty() const {
        //  stub code: needs to be implemented
        return root[1] == nullptr;
    }

    /*
    * Prints all the data from the tree in order based on key
    */
    void printTree(std::ostream &out = cout) const {
        printTree(0, out);
        //  stub code: needs to be implemented
    }

    /*
    * Removes all nodes from the tree
    */
    void makeEmpty() {
        for (int i = 0; i <= size ; count++)
        {
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
            //TODO fix expanding size so that it's not conflicting with other TODO
            //however insert function is done just with a fixed size
//            while (i * 2 + 1 > size)
//            {
//                size *= 2; <---- the problem child
//            }
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
                /*
                 * TODO sig fault is caused from if statement not reading in spot 41 right
                 * */
                if (root[i * 2 + 1] == nullptr) {
                    count++;
                    root[i * 2 + 1] = node;
                    return true;
                }
                i = i * 2 + 1;
            }
            else
            {
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
        //  stub code: needs to be implemented
    }

    int getSize() {
        //  stub code: needs to be implemented
        return size;
    }

    int getCount() {
        //  stub code: needs to be implemented
        return count;
    }

};    // end of BinarySearchTree class