#include "BSTInterface.h"
#include <string>

using namespace std;

template <typename KeyComparable, typename Value >
class BinarySearchTree : BSTInterface < KeyComparable, Value >  {
private:

    /*
    * Private BinaryNode Class
    */
    class BinaryNode {
    public:
        KeyComparable key;
        Value value;

        BinaryNode *left;
        BinaryNode *right;
        //Initialize class members from constructor arguments
        //by using a member initializer list.
        //This method uses direct initialization, which is more
        //efficient than using assignment operators inside the constructor body.
        BinaryNode( KeyComparable & key, Value & value, BinaryNode *left = nullptr, BinaryNode *right = nullptr)
                : value{ value }, left{ left }, right{ right } , key{ key }
        {

        }

    };	// end of BinaryNode class

    // the root node of the tree
    BinaryNode *root = nullptr;

    /*
    * Inserts a node into the tree
    * returns true if item inserted
    * returns false if item not inserted (Key already in tree)
    * maintains this property of th tree:
    *     All nodes to the left will be less
    *     All nodes to the right will be greater
    */
    bool insert_Private(Value item, KeyComparable key, BinaryNode * node) {
        //DONE write for lab 1
        node = new BinaryNode(key,item);
        BinaryNode *iterator = this->root;
        if (this->root == nullptr)
        {
            this->root = node;
            return true;
        }
        while (iterator != nullptr)
        {
            if (iterator->key == node->key)
            {
                cout << "Node is already inserted" << endl;
                delete[] node;
                return false;
            }
            else if (iterator->key > node->key)
            {
                if (iterator->left == nullptr)
                {
                    iterator->left = node;
                    return true;
                }
                iterator = iterator->left;
            }
            else if (iterator->key < node->key)
            {
                if (iterator->right == nullptr)
                {
                    iterator->right = node;
                    return true;
                }
                iterator = iterator->right;
            }
        }
    }

    /*
    * remove a node from the tree
    * maintains this property of th tree:
    *     All nodes to the left will be less
    *     All nodes to the right will be greater
    */
    void remove(const KeyComparable & key, BinaryNode ** t) {
        //TODO write for lab 2
        BinaryNode *temp = find_Private(key, this->root);
        if (temp == nullptr){
            return;
        }
        BinaryNode *iterator = this->root;
        BinaryNode *max = this->findMax_Private(iterator);
        while (iterator != nullptr)
        {
            if (iterator == temp)
            {
                iterator = max;
                iterator->left = temp->left;
                iterator->right = temp->right;
                delete[] temp;
                return;
            }
            else if (iterator->key > temp->key)
            {
                if (iterator->left == temp)
                {
                    iterator->left = this->findMin_Private(this->root);
                    iterator = iterator->left;
                    iterator->left = temp->left;
                    iterator->right = temp->right;
                    delete[] temp;
                    cout << "found key: " << temp->key;
                    return;
                }
                iterator = iterator->left;
            }
            else if (iterator->key <= temp->key)
            {
                if (iterator->left == temp)
                {
                    iterator->right = this->findMax_Private(this->root);
                    iterator = iterator->right;
                    iterator->left = temp->left;
                    iterator->right = temp->right;
                    delete[] temp;
                    return;
                }
                iterator = iterator->right;
            }
        }
    }

    /*
    * Finds the node with the smallest element in the subtree
    */
    BinaryNode * findMin_Private(BinaryNode *t) const {
        //DONE write for lab 2
        t = t->left;
        while (t != nullptr)
        {
            if (t->right == nullptr)
            {
                return t;
            }
            t = t->right;
        }
        return t;
    }

    /*
    * Finds the node with the largest element in the subtree
    */
    BinaryNode * findMax_Private(BinaryNode *t) const {
        //DONE write for lab 2
        t = t->right;
        while (t != nullptr)
        {
            if (t->left == nullptr)
            {
                return t;
            }
            t = t->left;
        }
        return t;
    }

    /*
    * Finds the node with that satisfies equality for the element
    */
    BinaryNode *  find_Private(const KeyComparable & key, BinaryNode *node) const {
        //TODO find_private
        BinaryNode *temp;
        if (key == node->key)
        {
            temp = node;
            return temp;
        }
        else if (key > node->key)
        {
            if (node->right != nullptr)
            {
                return find_Private(key,node->right);
            }
            return nullptr;
        }
        else if (key < node->key)
        {
            if (node->left != nullptr)
            {
                return (find_Private(key, node->left));
            }
            return nullptr;
        }
    }

    /*
    * Returns true if the item is found in the tree
    */
    bool contains(const Value & item, BinaryNode *t) const {
        // optional code
    }

    /*
    * Removes all elelements from the tree
    */
    void makeEmpty(BinaryNode * & t) {
        // optional code
    }

    /*
    * Prints all the data from the tree in order based on key
    */
    void printTree_Private(BinaryNode *t, std::ostream & out) const {
        //DONE write for lab 1
        if (this->root == nullptr)
        {
            return;
        }
        if (t->left != nullptr)
        {
            printTree_Private(t->left, out);
        }
        cout << t->key << endl;
        if (t->right != nullptr)
        {
            printTree_Private(t->right,out);
        }

    }

public:
    BinarySearchTree() {
        // optional code
    }

    ~BinarySearchTree() {
        // optional code
    }

    /*
    * Finds the node with the smallest element in the tree
    */
    const Value findMin() const {
        // DONE calls private findMin lab 2
        return (findMin_Private(this->root)->value);
    }

    /*
    * Finds the node with the largest element in the tree
    */
    const Value findMax() const {
        // DONE calls private findMax lab 2
        return (findMax_Private(this->root)->value);
    }

    /*
    * Finds the node with that the key
    * updates the founditem refrerence if found
    * returns true if it was found
    * returns false if it was not
    */
    bool find(const KeyComparable & key , Value & founditem) const {
        //TODO calls private find lab 1
        BinaryNode *temp = find_Private(key, this->root);
        if (temp != nullptr)
        {
            founditem = temp->value;
            return true;
        }
        return false;
    }

    /*
    * Returns true if the item is found in the tree
    */
    bool contains(const KeyComparable & key) const {
        // optional code
        return false;
    }

    /*
    * Returns true if tree has no nodes
    */
    bool isEmpty() const{
        // optional code
        return root == nullptr;
    }

    /*
    * Prints all the data from the tree in order based on key
    */
    void printTree(std::ostream & out = cout) const {
        // DONE Calls the private printTree function
        printTree_Private(this->root,out);
    }

    /*
    * Removes all nodes from the tree
    */
    void makeEmpty() {
        // optional code
    }

    /*
    * Inserts a node into the tree
    * maintains this property of the tree:
    *     All nodes to the left will be less
    *     All nodes to the right will be greater
    */
    bool insert( Value value,  KeyComparable key) {
        //DONE calls private remove
        return insert_Private(value,key,this->root);
    }

    /*
    * Removes the nodes if it contains the given item
    */
    void remove(const KeyComparable & key) {
        //TODO calls private remove
        BinaryNode **temp = new BinarySearchTree::BinaryNode *;
        remove(key,temp);
    }

};  // end of BinarySearchTree class
