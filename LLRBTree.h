#ifndef llrbtree_h
#define llrbtree_h

/*
http://cplusplus.kurttest.com/notes/llrb.html
http://www.teachsolaisgames.com/articles/balanced_left_leaning.html
*/

#include <exception>
#include <list>

// Exception that arises with searches of keys that are not in the tree
class inexistent_key : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Specified key does not exist in the tree";
    }
};


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
    void insert(K key, V value) {
        _root = rec_insert(_root, key, value);
        _root->_color = black;
    }

    //Delete a key in the tree
    void remove(K key) {
        _root = rec_remove(_root, key);
        _root->_color = black;
    }

    //Search for a key in the tree. Return associated value if key is present
    V search(const K &key) const {
        Node *x = _root;
        while (x != nullptr) {
            if (key == x->_key)
                return x->_value;
            else if (key < x->_key)
                x = x->_left;
            else
                x = x->_right;
        }
        throw inexistent_key();
    }

    bool contains(const K &key) const {
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

    //Maybe change list getters to take argument for inorder, preorder, postorder...
    std::list<K> get_keys_inorder() const {
        std::list<K> l;
        gen_key_list_inorder(l, _root);
        return l;
    }

    std::list<V> get_values_inorder() const {
        std::list<V> l;
        gen_val_list_inorder(l, _root);
        return l;
    }
    
    
private:    

    enum { 
        red = true, 
        black = false, 
        right = true, 
        left = false 
    };

    class Node {
    public:
        Node() {
            _color = black;
            _left = nullptr;
            _right = nullptr;
        }

        Node(K key, V value) {
            _key = key;
            _value = value;
            _color = red;
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

    Node* rec_insert(Node* z, const K &key, const V &value) {
        if (z == nullptr)
            return new Node(key, value);

            if (is_red(z->_left) && is_red(z->_right)) 
                color_flip(z);       

            if (key == z->_key) //Prevents duplicates
                z->_value = value;       

            else if (key < z->_key) 
                z->_left = rec_insert(z->_left, key, value);     

            else              
                z->_right = rec_insert(z->_right, key, value);   

            if (is_red(z->_right) && !is_red(z->_left))    
                z = rotate(left, z); 

            if (is_red(z->_left) && is_red(z->_left->_left)) 
                z = rotate(right, z);   

        return z;
    }

    Node* rec_remove(Node *z, const K &key){
        if (key < z->_key) {
            if (!is_red(z->_left) && !is_red(z->_left->_left))
                z = move_red_left(z);
            z->_left = rec_remove(z->_left, key);
        }
        else {
            if (is_red(z->_left))
                z = rotate(right, z);
            if (key == z->_key && z->_right == nullptr)
                return nullptr; //check if ok
            if (!is_red(z->_right) && !is_red(z->_right->_left))
                z = move_red_right(z);
            if (key == z->_key) {
                //TODO
                // h.val = get(h.right, min(h.right).key);
                // h.key = min(h.right).key;
                // h.right = deleteMin(h.right);
            }
            else
                z->_right = rec_remove(z->_right, key);
        }
        return fix_up(z);   
    }

    // Performs a left or right rotate on node z
    // right ? right rotate node z : left rotate node z
    Node* rotate(bool right, Node* z) {
        Node* x;
        right ? x = z->_left            : x = z->_right;   
        right ? z->_left = x->_right    : z->_right = x->_left;
        right ? x->_right = z           : x->_left = z;   
        x->_color = z->_color;   
        z->_color = red;   
        return x;
    }

    void color_flip(Node* z) {
        z->_color = !z->_color;
        z->_left->_color = !z->_left->_color;
        z->_right->_color = !z->_right->_color;
    }

    Node* move_red_left(Node* z) {
        color_flip(z);
        if (is_red(z->_right->_left)) {
            z->_right = rotate(right, z->_right);
            z = rotate(left, z);
            color_flip(z);
        }
        return z;
    }

    Node* move_red_right(Node* z) {
        color_flip(z);
        if (is_red(z->_left->_left)) {
            z = rotate(right, z);
            color_flip(z);
        }
        return z;
    }

    bool is_red(const Node *n) const {
        if (n == nullptr)
            return false;
        return n->_color;
    }

    void gen_key_list_inorder(std::list<K> &l, const Node* r) const {
        if (r == nullptr)
            return;
        gen_key_list_inorder(l, r->_left);
        l.push_back(r->_key);
        gen_key_list_inorder(l, r->_right);
    }

    void gen_val_list_inorder(std::list<V> &l, const Node* r) const {
        if (r == nullptr)
            return;
        gen_val_list_inorder(l, r->_left);
        l.push_back(r->_value);
        gen_val_list_inorder(l, r->_right);
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