//
//  Node.hpp
//  proj3
//
//  Created by Justin Lennox on 4/14/16.
//  Copyright © 2016 Justin Lennox. All rights reserved.
//

#ifndef Node_h
#define Node_h

//
//  proj2.cpp
//  proj2
//
//  Created by Justin Lennox on 3/24/16.
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

using std::ifstream;
using namespace std;

/**
 * A node class for use in a binary search tree.
 */
class Node {
public:
    char character;
    int frequency;
    Node *leftNode;
    Node *rightNode;
    
    //Default constructor
    Node();
    
    //Constructor with value passed
    Node(char character, int frequency);
};
#endif /* Node_h */
