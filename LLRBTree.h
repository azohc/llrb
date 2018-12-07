#ifndef llrbtree_h
#define llrbtree_h

/*

*/

#include <list>

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
        _root = insert_nod(_root, key, value);
        _root->_color = BLACK;
    }

    

    //Delete


    //Search for a key in the tree. Return associated value if key is present
    V search(const K &key) {
        Node *x = _root;
        while (x != nullptr) {
            if (key == x->_key)
                return x->_value;
            else if (key < x->_key)
                x = x->_left;
            else
                x = x->_right;
        }
        throw "Key not found in the tree.";
    }

    bool contains(const K &key) {
        Node *x = _root;
        while (x != nullptr) {
            if (key == x->_key)
                return true;
            else if (key < x->_key)
                x = x->_left;
            else
                x = x->_right;
        }
        return false;
    }

    std::list<V> inorder_treewalk(){
        std::list<V> l;
        gen_list_inorder(l, _root);
        return l;
    }
    
    /*
    Maybe make get iterator to key
    */
    
private:    

    enum { 
        RED = true, 
        BLACK = false, 
        RIGHT = true, 
        LEFT = false 
    };

    class Node {
    public:
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

    Node* insert_nod(Node* z, K key, V value) {
        if (z == nullptr)
            return new Node(key, value);

            if (isRed(z->_left) && isRed(z->_right)) 
                colorFlip(z);       

            if (key == z->_key)     
                z->_value = value;       

            else if (key < z->_key) 
                z->_left = insert_nod(z->_left, key, value);     

            else              
                z->_right = insert_nod(z->_right, key, value);   

            if (isRed(z->_right) && !isRed(z->_left))    
                z = rotate(z, LEFT); 

            if (isRed(z->_left) && isRed(z->_left->_left)) 
                z = rotate(z, RIGHT);   

        return z;
    }

    

    // Performs a left or right rotate on node z
    // right ? right rotate node z : left rotate node z
    Node* rotate(Node* z, bool right) {
        Node* x;
        right ? x = z->_left            : x = z->_right;   
        right ? z->_left = x->_right    : z->_right = x->_left;
        right ? x->_right = z           : x->_left = z;   
        x->_color = z->_color;   
        z->_color = RED;   
        return x;
    }

    void colorFlip(Node* z) {
        z->_color = !z->_color;
        z->_left->_color = !z->_left->_color;
        z->_right->_color = !z->_right->_color;
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