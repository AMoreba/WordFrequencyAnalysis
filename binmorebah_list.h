/*                                                                                                    
Name: Abdulelah Bin Morebah                                                                           
Date: 11/23/2021                                                                                      
Description: This program will be to parse a large text file and determine the word frequency of 
every word in the text file.                                             
*/
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
template <typename T> class Node;
template <typename T> class BST;

template <typename T> class WordEntry // class to store word and frequency
{
public:
	WordEntry(T);

private:
	T data;
	int frequency;
    friend class Node<T>; // this class is friend of Node class
};

//constructor
template <typename T> WordEntry<T>::WordEntry(T datain)
{
    data = datain;
    frequency = 1;
}

template <typename T> class Node //node class for creating tree
{
public:
	Node(T);
	T getData();
	void IncreaseCount();
    int getCount();
    int operator<(const Node<T> &);

private:
	WordEntry<T> *wordEntry;
	Node* left; // store left tree
	Node* right; // store right tree

	friend class BST<T>; // this class is friend of BST class
};

template <typename T> Node<T>::Node(T data)
{
	wordEntry = new WordEntry<T>(data);
	left = NULL;
	right = NULL;
}

template <typename T> int Node<T>::operator<(Node<T> const & node)
{
    if (getCount() > node.getCount()) return 1;
    else if (getCount() < node.getCount()) return -1;
    else return 0;
}


//increase word frequency
template <typename T> void Node<T>::IncreaseCount()
{
    wordEntry->frequency++;
}

// get word string
template <typename T> T Node<T>::getData()
{
	return wordEntry->data;
}

template <typename T> int Node<T>::getCount()
{
	return wordEntry->frequency;
}

template <typename T> class BST // this class used to create BST
{

public:
	BST();
    ~BST();
    bool Insert(T data);
    void Remove (T data);
    bool ElementExists(T data);
    Node<T>** ToArray();
    Node<T>* Find(T data);
    void Empty();
    int Count();

private:
	Node<T> *root;
	int count;
	bool Insert(Node<T>* ,T data);
	Node<T>* Find(Node<T>*, T data);
	int crateArray(Node<T>*, Node<T>**, int);
    void Empty(Node<T>*);
    Node<T>* Remove (Node<T>*, T);
    Node<T>* leftmost(Node<T>*);
};

template <typename T> BST<T>::BST()
{
    root = NULL;
    count = 0;
}

template <typename T> BST<T>::~BST()
{
    Empty();
}

// this public method used to empty BST and free memory used
template <typename T> void BST<T>::Empty()
{
    if (root != NULL) {
        Empty(root);
        root = NULL;
    }
    count = 0;
}

// this private recursive method used to empty BST and free memory used under a node
template <typename T> void BST<T>::Empty(Node<T>* node)
{
    if (node->left != NULL)
    {
        Empty(node->left); // empty left tree
    }

    delete(node); // empty parent node

    if (node->right != NULL)
    {
        Empty(node->right); // empty right tree
    }
}

// this private recursive method used to crate Array from BST
template <typename T> int BST<T>::crateArray(Node<T>* node, Node<T>** arr, int index)
{
    if (node->left != NULL)
    {
        index = crateArray(node->left, arr, index); // create array of left sub tree
    }

    arr[index++] = node; // add parent node to array

    if (node->right != NULL)
    {
        index = crateArray(node->right, arr, index); // create array of right sub tree
    }

    return index;
}

// this public method used create array from BSt
template <typename T> Node<T>** BST<T>::ToArray() // create array from the BST
{
    Node<T>** arr = new Node<T>*[count]; // initialize the array of object
    if (root != NULL)
    {
        crateArray(root, arr, 0); // traverse from the root node
    }

    return arr;

}

// this private recursive method used to insert data into BST under a node
template <typename T> bool BST<T>::Insert(Node<T> *node, T data)
{
    if (node->getData() < data)
    {
        if (node->right == NULL) // if right node is empty
        {
            node->right = new Node<T>(data); // insert right
            count++;
            return true;
        }
        else
        {
            return Insert(node->right, data); // insert right sub tree
        }
    }
    else if (node->getData() == data) // if data is equal
    {
        node->IncreaseCount(); // increase frequency
        return false;
    }
    else
    {
        if (node->left == NULL) // if left node is empty
        {
            node->left = new Node<T>(data); // insert left
            count++;
            return true;
        }
        else
        {
            return Insert(node->left, data); // insert left sub tree
        }
    }
}

template <typename T> bool BST<T>::Insert(T data)
{
    if (root == NULL) // if root null
    {
        root = new Node<T>(data);
        count++;
        return true;
    }
    else
    {
        return Insert(root, data); // insert under root
    }
}

// this recursive method used to find data under a node
template <typename T> Node<T>* BST<T>::Find(Node<T>* node, T data)
{
    if (node->getData() < data) // search data greater than node data then go right
    {
        if (node->right == NULL) // if right node is null  return null
        {
            return NULL;
        }
        else
        {
            return Find(node->right, data); //else search into right sub tree
        }
    }
    else if (node->getData() == data) // found the data
    {
        return node;
    }
    else // search data less than node data then go left
    {
        if (node->left == NULL) // if right node is null then return null
        {
            return NULL;;
        }
        else
        {
            return Find(node->left, data); //else search into left sub tree
        }
    }
}

// this method used to find data in BST
template <typename T> Node<T>* BST<T>::Find(T data)
{
    if (root == NULL) // if BST empty
    {
        return NULL;
    }
    else
    {
        return Find(root, data); //find under root
    }
}

// checks if data element exists or not
template <typename T> bool BST<T>::ElementExists(T data)
{
    if (Find(data) == NULL) // if data found
    {
        return false;
    }
    else
    {
        return true;
    }
}

// returns number of node in BST
template <typename T> int BST<T>::Count()
{
    return count;
}

//gets leftmost node under a tree
template <typename T> Node<T>* BST<T>::leftmost(Node<T>* node)
{
        Node<T>* minv = node;
        while (node->left != NULL) // loop through left most node
        {
            minv = node->left;
            node = node->left;
        }
        return minv;
}

// this recursive method removes a node with given data
template <typename T> Node<T>* BST<T>::Remove(Node<T> *node, T data)
{
    if (node == NULL) // if BST empty
        return NULL;
    if (data < node->getData()) // if data less than current node
        node->left = Remove(node->left, data);
    else if (data > node->getData())  // if data greater than current node
        node->right = Remove(node->right, data);
    else {
            if (node->left == NULL) // node have only left child
                return node->right;
            else if (node->right == NULL) // node have only right child
                return node->left;

            // node with two children then replace with right leftmost node
            Node<T>* minNode = leftmost(node->right);
            node->wordEntry = minNode->wordEntry;

            // remove right leftmost node
            node->right = Remove(node->right, node->getData());
        }

        return node;
}

template <typename T> void BST<T>::Remove(T data)
{
    root = Remove(root, data);
}

#endif // LIST_H_INCLUDED
