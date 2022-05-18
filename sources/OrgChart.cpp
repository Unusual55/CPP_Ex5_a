#include "OrgChart.hpp"

using namespace ariel;

OrgChart::OrgChart(OrgChart &other_org) {
    root = &other_org.getRootCopy();
    for (auto element: other_org.inserted) {
        inserted[element.first] = element.second;
    }
}

Node &OrgChart::getRootCopy() {
    Node *ret{root};
    return *ret;
}


Node &OrgChart::getRoot() {
    return *root;
}

OrgChart &OrgChart::add_root(const string &root_name) {
    if (root == nullptr) {
        *root= Node{root_name};
        this->inserted[root_name] = root;
    } else {
        this->inserted.erase(root->getDescription());
        setRoot(root_name);
        this->inserted[root_name] = root;
    }
    return *this;
}

Node *OrgChart::getNode(const string &name) {
    if (!inserted.contains(name)) {
        throw std::invalid_argument("Error: cannot add under someone who does not exist!");
    }
    return inserted.at(name);
}

bool OrgChart::check_isExist(const string &name) {
    return (inserted.at(name));
}

OrgChart &OrgChart::add_sub(const string &parent, const string &node) {
    inserted.at(parent)->addToNextLevel(node);
    Node *n = this->inserted.at(parent)->getNewestSon();
    inserted[node] = n;
    return *this;
}

ostream &ariel::operator<<(ostream &out, OrgChart &org) {
    string t_push = "\t";
    auto p = org.end_preorder();
    for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
            unsigned int level = it->getLevel();
            for (int i = 0; i < level; i++) {
                out << t_push;
            }
            out << (*it) << endl;
    }
    return out;
}

ostream &ariel::operator<<(ostream& out, Node& node){
    string push_t;
    for(int i = 0; i < node.level; i++){
        push_t+="\t";
    }
    out<<push_t<<node.getDescription()<<std::endl;
    return out;
}
