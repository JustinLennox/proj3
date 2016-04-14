//
//  main.cpp
//  proj3
//
//  Created by Justin Lennox on 4/14/16.
//  Copyright © 2016 Justin Lennox. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <map>
#include <algorithm>
#include "Node.hpp"

using std::ifstream;
using namespace std;

//Method Declarations
bool contains(vector<char> vect, char x);
void sort(vector<char> &v);
int freq(string in, char x);
Node rootNode;
void CreateFrequencyDictionaryFromFile(ifstream& inputFile);
void CreateTreeFromDictionary(map<int, char> frequencyDictionary);
vector<char> characterVector; // A vector containing all of the characters of the input file
map<int, char> frequencyDictionary; // A dictionary containing all of the characters and frequencies of the input file

//Visualization Methods
void PrintTree();
int getLevelForNode(Node *root, char searchingChar, int searchingFrequency, int level = 0);
vector<int> treeMap[100];
vector<int> treeValues;
int treeMapSize = 0;

int main(int argc, const char * argv[]) {

    if (argc < 2) { //No input file passed
        std::cerr << "Error: Please pass a text input file to parse." << std::endl;
        return EXIT_FAILURE;
    }else if(argc > 1){
        ifstream inputFile;
        inputFile.open(argv[1]); // open a file
        
        if(inputFile.is_open()){
            CreateFrequencyDictionaryFromFile(inputFile);
        }else{
            std::cerr << "Error: Couldn't open the input file." << std::endl;
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}

/**
 * Parses the input text file to read binary search tree commands and their corresponding values
 */
void CreateFrequencyDictionaryFromFile(ifstream& inputFile){
    string inputString;
    getline(inputFile, inputString);
    inputFile.close();
    cout << "The line read was: " << inputString << endl;
    
    //Add each unique character to a vector
    for (int i = 0; i < inputString.length(); i++)
    {
        if (!contains(characterVector, inputString[i]))
        {
            characterVector.push_back(inputString[i]);
        }//if
    }//for
    
    
    sort(characterVector); //sorts vector
    //Creates a dictionary mapping each unique character to its frequency
    for (int i = 0; i < characterVector.size(); ++i)
    {
        //Adds each unique character to the dictionary with its corresponding frequency
//        cout << characterVector.at(i) << ":" << freq(inputString, characterVector[i]) << "\n";
        frequencyDictionary[freq(inputString, characterVector[i])] = characterVector.at(i);
    }//for
    CreateTreeFromDictionary(frequencyDictionary);
}

void CreateTreeFromDictionary(map<int, char> frequencyDictionary){
    map<int, char> temporaryDictionaryHolder;
    vector<Node> nodeArray;
    for (auto const& x : frequencyDictionary)
    {
        Node *node = new Node();
        node->character = x.second;
        node->frequency = x.first;
        cout << "Added node with character: " << node->character << " and frequency: "  << node->frequency << endl;
        nodeArray.push_back(*node);
    }
    nodeArray;
    while(nodeArray.size() > 1){
        Node leftNode = nodeArray.at(0);
        cout << "Left node char: " << leftNode.character << ", freq: " << leftNode.frequency << endl;
        Node rightNode = nodeArray.at(1);
        cout << "Right node char: " << rightNode.character << ", freq: " << rightNode.frequency << endl;

        Node *parentNode = new Node();
        parentNode->leftNode = &leftNode;
        parentNode->rightNode = &rightNode;
        parentNode->frequency = leftNode.frequency + rightNode.frequency;
        for(int i = 0; i < nodeArray.size(); i++){
            if(parentNode->frequency < nodeArray.at(i).frequency){  //Add the parent node into the array
                nodeArray.insert(nodeArray.begin() + i, *parentNode);
                break;
            }
        }
        for(int i = 0; i < nodeArray.size(); i++){
            if(leftNode.frequency == nodeArray.at(i).frequency || rightNode.frequency == nodeArray.at(i).frequency){
                nodeArray.erase(nodeArray.begin() + i);
            }
        }
        for(int i = 0; i < nodeArray.size(); i++){
            if(leftNode.frequency == nodeArray.at(i).frequency || rightNode.frequency == nodeArray.at(i).frequency){
                nodeArray.erase(nodeArray.begin() + i);
            }
        }
        //
        cout << "Parent left node char: " << parentNode->leftNode->character << ", freq: " << parentNode->leftNode->frequency << endl;
        cout << "Parent right node char: " << parentNode->rightNode->character << ", freq: " << parentNode->rightNode->frequency << endl;
        cout << &nodeArray << endl;
    }
}

//void insert(Node *&root, int value){
//    if(root == nullptr){    //There's no root node, set this as the root
//        root = new Node();
//        root->value = value;
//        return;
//    }else if (value > root->value) {    //Recursively branch into right subtree
//        insert(root->rightNode, value);
//    }else { //Recursively branch into left subtree
//        insert(root->leftNode, value);
//    }
//}



//VISUALIZATION METHODS

/**
 * Prints out a visual representation of the binary search tree
 */
void PrintTree(){
    string treeString = "";
    for(int i = 0; i < (int)treeValues.size(); i++){
        vector<int> levelVector = treeMap[getLevelForNode(&rootNode, characterVector.at(i), frequencyDictionary[characterVector.at(i)])];
        levelVector.push_back(treeValues.at(i));
        treeMap[getLevelForNode(&rootNode, characterVector.at(i), frequencyDictionary[characterVector.at(i)])] = levelVector;
    }
    int maxCount = 0;
    for (int i = 0; i < (int)treeMapSize + 1; i++)
    {
        vector<int> currentVector = treeMap[i];
        maxCount = (int)currentVector.size() > maxCount ? (int)currentVector.size() : maxCount;
    }
    for (int i = 0; i < (int)treeMapSize + 1; i++)
    {
        vector<int> currentVector = treeMap[i];
        sort (currentVector.begin(), currentVector.begin() + currentVector.size());
        for(int i = (int)currentVector.size(); i <= maxCount; i++){
            treeString += "\t";
        }
        for(int i = 0; i < (int)currentVector.size(); i++){
            treeString += to_string((int)currentVector.at(i)) + "\t";
        }
        treeString += "\n";
    }
    cout << treeString;
}

/**
 * Takes a character and its frequency and figures out what level of the tree that character's node is at
 */
int getLevelForNode(Node *root, char searchingChar, int searchingFrequency, int level){
    if(root != nullptr){
        if(root->character == searchingChar){
            if(level > treeMapSize){
                treeMapSize = level;
            }
            return level;
        }else if(searchingFrequency > root->frequency){
            return getLevelForNode(root->rightNode, searchingChar, searchingFrequency, level + 1);
        }else{
            return getLevelForNode(root->leftNode, searchingChar, searchingFrequency, level + 1);
        }
    }else{
        return 0;
    }
}



//SORTING METHODS
bool contains(vector<char> vect, char x)
{
    for (int i = 0; i < vect.size(); i++)
    {
        if (vect[i] == x)
            return true;
    }//for
    return false;
}//contains

void sort(vector<char> &v)
{
    for(int i=0; i<v.size(); i++)
    {
        for(int j=0; j<v.size()-1; j++)
        {
            if(v[j]>v[j+1])
            {
                char temp = v[j+1];
                v[j+1] = v[j];
                v[j] = temp;
            }//if
        }//for
    }//for
}//sort

int freq(string in, char x)
{
    int count = 0;
    for (int i = 0; i < in.length(); i++)
    {
        if (in[i] == x)
            count++;
    }//for
    return count;
}


