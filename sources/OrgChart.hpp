#include "Node.hpp"
#include <ostream>
#include <unordered_map>
#include <stack>
#include <queue>
#include <iterator>

using std::queue, std::stack, std::string, std::endl, std::ostream;

namespace ariel {
    class OrgChart {

    public:
        void setRoot(const string &root_name) {
            root->setDescription(root_name);
        }

        OrgChart() {root = new Node{};}

        OrgChart(OrgChart &other_org);

        ~OrgChart() {  }

        Node &getRoot();

        Node &getRootCopy();

        OrgChart &add_root(const string &root_name);

        Node *getNode(const string &name);

        OrgChart &add_sub(const string &parent, const string &node);

        bool check_isExist(const string &name);

        friend ostream& operator<<(ostream &out, OrgChart &org);

    public:

        class preOrderIterator {
        private:
            queue<Node *> q;
            Node *pointer_to_current_node;
        public:
            preOrderIterator(Node *ptr){
                if(ptr) {
                    q=Node::preOrderQueue(*ptr);
                    pointer_to_current_node = q.front();
                    q.pop();
                }
                else{
                    pointer_to_current_node = nullptr;
                }
            }

            string operator*() const {
                return pointer_to_current_node->getDescription();
            }

            Node* operator->() const {
                return (pointer_to_current_node);
            }

            preOrderIterator &operator++() {
                pointer_to_current_node = q.front();
                q.pop();
                return *this;
            }

            const preOrderIterator operator++(int) {
                preOrderIterator tmp = *this;
                pointer_to_current_node = q.front();
                q.pop();
                return tmp;
            }

            bool operator==(const preOrderIterator &rhs) const {
                return this->pointer_to_current_node==rhs.pointer_to_current_node;
            }

            bool operator!=(const preOrderIterator &rhs) const {
                return this->pointer_to_current_node!=rhs.pointer_to_current_node;
            }

                bool isEnded(){
                    return pointer_to_current_node!=nullptr;
                }
            };

    public:

        class levelOrderIterator {
        private:
            queue<Node *> q=queue<Node *>();
            Node *pointer_to_current_node;
        public:
            levelOrderIterator(Node *ptr) {
                if(ptr) {
                    q=Node::levelOrderedQueue(*ptr);
                    pointer_to_current_node=nullptr;
//                    pointer_to_current_node = q.front();
//                    q.pop();
                }
                else{
                    pointer_to_current_node = nullptr;
                }
            }

            string operator*() const {
                return pointer_to_current_node->getDescription();
            }

            Node* operator->() const {
                return pointer_to_current_node;
            }

            levelOrderIterator &operator++() {
                pointer_to_current_node = q.front();
                q.pop();
                return *this;
            }

            const levelOrderIterator operator++(int) {
                levelOrderIterator tmp = *this;
                pointer_to_current_node = q.front();
                q.pop();
                return tmp;
            }

            bool operator==(const levelOrderIterator &rhs) const {
                return this->pointer_to_current_node==rhs.pointer_to_current_node;
            }

            bool operator!=(const levelOrderIterator &rhs) const {
                return this->pointer_to_current_node!=rhs.pointer_to_current_node;
            }

        };


    public:

        class ReversedlevelOrderIterator {
        private:
            stack<Node *> s;
            Node *pointer_to_current_node;
        public:
            ReversedlevelOrderIterator(Node *ptr){
                if(ptr) {
                    s=Node::ReversedLevelOrderedStack(*ptr);
                    pointer_to_current_node = nullptr;
//                    pointer_to_current_node = s.top();
//                    s.pop();
                }
                else{
                    pointer_to_current_node = nullptr;
                }
            }

            string operator*() const {
                return pointer_to_current_node->getDescription();
            }

            Node* operator->() const {
                return pointer_to_current_node;
            }

            ReversedlevelOrderIterator &operator++() {
                if(s.empty()){
                    pointer_to_current_node=nullptr;
                }
                else {
                    pointer_to_current_node = s.top();
                    s.pop();
                }
                return *this;
            }

            const ReversedlevelOrderIterator operator++(int) {
                ReversedlevelOrderIterator tmp = *this;
                pointer_to_current_node = s.top();
                s.pop();
                return tmp;
            }

            bool operator==(const ReversedlevelOrderIterator &rhs) const {
                return this->pointer_to_current_node==rhs.pointer_to_current_node;
            }

            bool operator!=(const ReversedlevelOrderIterator &rhs) const {
                return this->pointer_to_current_node!=rhs.pointer_to_current_node;
            }

        };


    protected:
        Node *root{};
        std::unordered_map<string, Node *> inserted;


    public:
            preOrderIterator begin_preorder() {
                return preOrderIterator(root);
            }

            preOrderIterator end_preorder(){
                return preOrderIterator(nullptr);
            }

            levelOrderIterator begin_level_order() {
                return levelOrderIterator(root);
            }

            levelOrderIterator end_level_order(){
                return levelOrderIterator(nullptr);
            }

            ReversedlevelOrderIterator begin_reverse_order(){
                return ReversedlevelOrderIterator(root);
            }

            ReversedlevelOrderIterator reverse_order(){
                return ReversedlevelOrderIterator(nullptr);
            }

            levelOrderIterator begin(){
                return begin_level_order();
            }

            levelOrderIterator end(){
                return end_level_order();
            }

        };
    }