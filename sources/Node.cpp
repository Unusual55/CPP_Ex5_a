#include "Node.hpp"
using ariel::Node;
//Node::Node(const std::string &description){
//    this->description=description;
//}

Node::Node(Node &other_node){
    this->description=other_node.description;
    this->level=other_node.level;
    for(Node* node: other_node.next){
        this->next.emplace_back(node);
    }
    for(Node* node:this->next){
        node->setPrev(*this);
    }
}

void Node::addToNextLevel(const string &next_description){
    uint next_level = this->level+1;
    Node *t=new Node{next_description, next_level};
    this->next.emplace_back(t);
    this->next.back()->setPrev(*this);
}

Node Node::getPrev(){
    return *prev;
}

void Node::setPrev(Node &previous_node){
    if(this->prev!= nullptr && this->prev->getDescription() != previous_node.getDescription()){
        throw std::logic_error("Error: Cannot add more than one parent to a node");
    }
    this->prev = &previous_node;
}