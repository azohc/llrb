#ifndef llrbtree_h
#define llrbtree_h

/*



*/

#include <list>

const bool RED = true;
const bool BLACK = false;

template <class K, class V>
class LLRBTree {
public:
    //Constructor for an empty tree
    LLRBTree() {
       _root = new Node();
    } 

    //Constructor for a single-node tree
    LLRBTree(const K key, const V value) {
       _root = new Node(key, value);
    }

    //Destructor
    ~LLRBTree() {
        free(_root);
        _root = nullptr;
    }

    
    //Insert an element into the tree
    void insert(K key, V value){
         
    }

    

    //Delete


    //Search for a key in the tree. Return associated value if key is present
    V search(const K &key){
        Node *x = _root;
        while (x != nullptr) {
            if (key == x->_key)
                return x->_value;
            else if (key < x->_key)
                x = x->_left;
            else
                x = x->_right;
        }
        return nullptr;
    }


    std::list<V> inorder_treewalk(){
        std::list<V> l;
        gen_list_inorder(l, _root);
        return l;
    }
    
    /*
    Maybe make get iterator to key
    Maybe make observer function that checks if a given key exists in the tree
    */
    
protected:
    class Node {
    public:
        // Leaf constructor, needed?
        Node() {
            _color = BLACK;
            _left = nullptr;
            _right = nullptr;
        }

        Node(K key, V value) {
            _key = key;
            _value = value;
            _color = RED;
            _left = nullptr;
            _right = nullptr;
        }

        bool _color;
        K _key;
        V _value;
        Node *_left;
        Node *_right;
    };

    Node *_root;


    // Needed? Constructor to make a red-black tree from a node
    // LLRBTree(Node *root){
    //     _root = root;
    // }


private:    

    void insert_fixup(Node* z) {
      
    }

    void left_rotate(Node* x) {
       
    }

    void right_rotate(Node* x) {
       
    }

    bool isRed(const Node *n) const {
        if (n == nullptr)
            return false;
        return n->_color;
    }


    void gen_list_inorder(std::list<V> &l, const Node* r) const {
        if (r == nullptr)
            return;
        gen_list_inorder(l, r->_left);
        l.push_back(r->_value);
        gen_list_inorder(l, r->_right);
    }

    //Free all the children nodes that branch from root    
    void free(Node *root) {
        if(root != nullptr) {
            free(root->_left);
            free(root->_right);
            delete root;
        }
    }
};

#endif