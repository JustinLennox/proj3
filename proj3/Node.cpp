//
//  Node.cpp
//  proj3
//
//  Created by Justin Lennox on 4/14/16.
//  Copyright © 2016 Justin Lennox. All rights reserved.
//

#include "Node.hpp"

Node::Node(){
    leftNode = nullptr;
    rightNode = nullptr;
    character = NULL;
    frequency = NULL;
}

Node::Node(char character, int frequency){
    leftNode = nullptr;
    rightNode = nullptr;
    this->character = character;
    this->frequency = frequency;
}
