#include <string>
#include <ostream>
#include <vector>
#include <stack>
#include <queue>
using std::queue;
using std::stack;
using std::string;
using std::vector;
using std::ostream;

namespace ariel{
    class Node{
        string description="";
        uint level=0;
        vector<Node *> next=vector<Node *>();
        Node* prev=nullptr;
    public:
        Node()=default;

        Node(const string &description): description(description), level(0){}

        Node(const string &description, uint level): description(description), level(level){}

        Node(Node &other_node);

        friend ostream& operator<<(ostream &out, Node &node);

        void DestroyRecursive(Node* node){
            if(node){
                for(unsigned int i=0;i<node->next.size();i++){
                    delete node->next[i];
                    node->next[i] = nullptr;
                }
            }
        }

        ~Node() {
            DestroyRecursive(this);
        }

        string getDescription() const{
            return this->description;
        }

        void setDescription(const string &desc){
            this->description = desc;
        }

        const uint getLevel() const{
            return this->level;
        }

        uint size(){
            return next.size();
        }

        vector<Node *> getNextLevel() const{
            return next;
        }

        Node* getNewestSon(){
            return next.back();
        }

        void addToNextLevel(const string &next_description);

        Node getPrev();

        void setPrev(Node &previous_node);

        static queue<Node*> preOrderQueue(Node &root){
            queue<Node*> output_queue;
            std::stack<Node*> node_stack;
            node_stack.push(&root);
            Node temp;
            while(!node_stack.empty()){
                if(node_stack.top()== nullptr){
                    break;
                }
                temp = *node_stack.top();
                output_queue.push(node_stack.top());
                node_stack.pop();
                vector<Node *> next_level = temp.getNextLevel();
                if(next_level.size()>0){
                    uint i=next_level.size()-1;
                    for(;i>=0 && i<next_level.size();i--){
                        node_stack.push({next_level[i]});
                    }
                }
            }
            return output_queue;
        }

        static queue<Node *> levelOrderedQueue(Node &root){
            queue<Node*> output_queue;
            queue<Node*> node_queue;
            node_queue.push(&root);
            Node temp;
            while(!node_queue.empty()){
                if(node_queue.front()== nullptr){
                    break;
                }
                temp = *node_queue.front();
//                output_queue.push(node_queue.front());
                node_queue.pop();
                vector<Node *> next_level =temp.getNextLevel();
                if(next_level.size()>0) {
                    for (unsigned int i = 0; i < next_level.size(); i++) {
                        output_queue.push(next_level.at(i));
                        node_queue.push(next_level.at(i));
                    }
                }
            }
            return output_queue;
        }

        static stack<Node *> ReversedLevelOrderedStack(Node &root){
            queue<Node*> node_queue = Node::levelOrderedQueue(root);
            stack<Node*> output_stack;
            while(!node_queue.empty()){
                output_stack.push(node_queue.front());
                node_queue.pop();
            }
            return output_stack;
        }

    };

};