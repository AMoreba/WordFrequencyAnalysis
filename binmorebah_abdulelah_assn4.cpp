/*                                                                                                    
Name: Abdulelah Bin Morebah                                                                           
Date: 11/23/2021                                                                                      
Description: This program will be to parse a large text file and determine the word frequency of 
every word in the text file.                                             
*/
#include <iostream>
#include <bits/stdc++.h>
#include "binmorebah_list"
#include <algorithm>
using namespace std;

// this method is used to sort array of object
template<typename T> void sortByFrequency(Node<T>** arr, int n)
{
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j]->getCount() < arr[j+1]->getCount()) // compares frequency of 2 word
            {
                Node<T> *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

int main()
{
    BST<string> *bst = new BST<string>(); //create object of BST class
    fstream infile; //fstream object to read from file
    ofstream outfile; //ofstream object to write to file

    string str, searchw, filename;
    cout<<"Enter filename : ";
    cin>>filename; // read file name from user

    infile.open(filename.c_str());
    if (!infile.good()) {
        cout<<"File not found"<<endl;
        return 0;
    }

    while (infile >> str) // read string from file
    {
        transform(str.begin(), str.end(), str.begin(), ::tolower); // convert string to lower case
        string word;

        for (int i=0;i<str.length();i++)
        {
            if (isalpha(str[i]) || str[i]== '`') // checks if char in string is alphabet or not
            {
                word.push_back(str[i]); // push char into word
            }
            else
            {
                if (!word.empty()) //if word not empty
                {
                    bst->Insert(word); //insert word into BST
                    word = "";
                }
            }
        }

        if (!word.empty()) //if word not empty
        {
            bst->Insert(word); //insert word into BST
        }
    }
    Node<string>** alph = bst->ToArray(); // create array from BST

    Node<string>** arr = new Node<string>*[bst->Count()]; // create an array
    std::copy(alph, alph + bst->Count(), arr); // create copy of BST array

    sortByFrequency(arr, bst->Count()); // sort the array by frequency descending order
    int totalWords = 0;
    for(int i=0;i<bst->Count();i++)
    {
        totalWords+=arr[i]->getCount(); // computes total number of words
    }

    cout<<"Total Words: "<<totalWords<<endl;
    cout<<"Total Unique Words: "<<bst->Count()<<endl;
    cout<<"The 5 most frequently used words"<<endl;
    for(int i=0;i<std::min(5,bst->Count());i++) // loop from first 5
    {
        cout<<arr[i]->getData() << "       " <<arr[i]->getCount()<<endl; //prints 5 most frequently used words
    }

    cout<<"The 5 least frequently used words"<<endl;
    for(int i=bst->Count()-1;i>bst->Count()-6 && i>0 ;i--) // loop from last 5
    {
        cout<<arr[i]->getData() << "       " <<arr[i]->getCount()<<endl; //prints 5 least frequently used words
    }

    int choice;
    cout<<"Press 1 for find word frequency"<<endl<<"Press 2 for write to file by frequency"<<endl<<"Press 3 for write to file by alphabetically"<<endl<<"Press 0 for exit"<<endl<< "Enter Choice: ";
    cin>>choice;
    cout <<"================================================"<<endl;

    while(choice != 0) {
        if (choice == 1) {
            cout<<"Enter word :";
            cin>>searchw;
            Node<string> *node = bst->Find(searchw); // finds a word from BST
            if (node == NULL) {
                cout<<"Not Found"<<endl;
            } else {
                cout<<"Word Frequency : "<<node->getCount() <<endl;
            }
        } else if (choice == 2) {
            cout<<"Enter File path :";
            cin>>filename; // read file name from user
            outfile.open (filename.c_str());

            for(int i=0;i<bst->Count();i++)
            {
                outfile<<arr[i]->getData() << "       " <<arr[i]->getCount()<<endl; // write word summary by frequency
            }
            outfile.close();

        } else if (choice == 3) {
            cout<<"Enter File path :";
            cin>>filename; // read file name from user
            outfile.open (filename.c_str());

            for(int i=0;i<bst->Count();i++)
            {
                outfile<<alph[i]->getData() << "       " <<alph[i]->getCount()<<endl; // write word summary alphbatically
            }
            outfile.close();

        }
        cout <<"================================================"<<endl;
        cout<<"Press 1 for find word frequency"<<endl<<"Press 2 for write to file by frequency"<<endl<<"Press 3 for write to file by alphabetically"<<endl<<"Press 0 for exit"<<endl<< "Enter Choice: ";
        cin>>choice;

    }

    return 0;
}
