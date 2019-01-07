#ifndef llrbtree_h
#define llrbtree_h

/*
http://cplusplus.kurttest.com/notes/llrb.html
http://www.teachsolaisgames.com/articles/balanced_left_leaning.html
https://stackoverflow.com/questions/37492768/inserting-element-into-LEFT-leaning-BLACK  RED-tree-c (good main for testing)
http://www.cs.princeton.edu/~rs/talks/LLRB/Java/RedBlackBST.java
*/

#include <memory>
#include <exception>
#include <list>


// Exception that arises with searches of keys that are not in the tree
class inexistent_key : public std::exception 
{
public:
    virtual const char* what() const throw() 
    {
        return "Specified key does not exist in the tree";
    }
};


template <class K, class V>
class LLRBTree 
{
public:

    //Constructor for an empty tree
    LLRBTree() 
    {
       _root = nullptr;
    } 

    //Constructor for a single-node tree
    LLRBTree(const K key, const V value) 
    {
       _root = std::make_shared<Node>(Node(key, value));
    }

    //Destructor
    ~LLRBTree() 
    {
        free(_root);
        _root = nullptr;
    }

    //Insert an element into the tree
    void insert(K key, V value) 
    {
        _root = rec_insert(_root, key, value);
        _root->_color = BLACK;
    }

    //Delete a key in the tree
    void remove(K key) 
    {
        if(_root != nullptr)
        {
            _root = rec_remove(_root, key);
            if(_root != nullptr)
                _root->_color = BLACK;
        }
    }

    //Search for a key in the tree. Return associated value if key is present
    V get(const K &key) 
    {
        nodeptr nod = get(_root, key);
        if (nod == nullptr)
            throw inexistent_key();
        return nod->_value;
    }

    bool contains(const K &key) const 
    {
        return get(_root, key) != nullptr;
    }

    void delete_min() 
    {
        _root = rec_delete_min(_root);
        _root->_color = BLACK;
    }

    //Maybe change list getters to take argument for inorder, preorder, postorder...
    std::list<K> get_keys_inorder() const 
    {
        std::list<K> l;
        gen_key_list_inorder(l, _root);
        return l;
    }

    std::list<V> get_values_inorder() const 
    {
        std::list<V> l;
        gen_val_list_inorder(l, _root);
        return l;
    }
    
    
private:    

    enum 
    { 
        RED = true, 
        BLACK = false, 
        RIGHT = true, 
        LEFT = false 
    };

    class Node 
    {
    public:
        Node() 
        {
            _color = BLACK;
            _left = nullptr;
            _right = nullptr;
        }

        Node(K key, V value) 
        {
            _key = key;
            _value = value;
            _color = RED;
            _left = nullptr;
            _right = nullptr;
        }

        bool _color;
        K _key;
        V _value;
        std::shared_ptr<Node> _left;
        std::shared_ptr<Node> _right;
    };

    using nodeptr = std::shared_ptr<Node>;

    nodeptr _root;

    nodeptr rec_insert(nodeptr h, const K &key, const V &value) 
    {
        if (h == nullptr)
            return std::make_shared<Node>(Node(key, value));

        if (key == h->_key) //Duplicate key, replace value
            h->_value = value;       
        else if (key < h->_key) 
            h->_left = rec_insert(h->_left, key, value);     
        else              
            h->_right = rec_insert(h->_right, key, value);   

        if (is_red(h->_right) && !is_red(h->_left))    
            h = rotate(LEFT, h); 

        if (is_red(h->_left) && is_red(h->_left->_left)) 
            h = rotate(RIGHT, h);   

        if (is_red(h->_left) && is_red(h->_right)) 
            color_flip(h);       

        return h;
    }

    nodeptr rec_remove(nodeptr h, const K &key)
    {
        if (key < h->_key) 
        {
            if (!is_red(h->_left) && !is_red(h->_left->_left))
                h = move_red_left(h);
            h->_left = rec_remove(h->_left, key);
        }
        else {
            if (is_red(h->_left))
                h = rotate(RIGHT, h);
            if (key == h->_key && h->_right == nullptr)
            {
                free(h);
                return nullptr;
            }
            if(h->_right != nullptr)
            {
                if (!is_red(h->_right) && !is_red(h->_right->_left))
                    h = move_red_right(h);

                if (key == h->_key) 
                {
                    nodeptr m = min_node(h->_right);
                    h->_value = get(h->_right, m->_key)->_value;
                    h->_key = m->_key;
                    h->_right = rec_delete_min(h->_right);
                }
                else
                    h->_right = rec_remove(h->_right, key);
            }
        }
        return fixup(h);   
    }

    nodeptr rec_delete_min(nodeptr h)
    {
        if (h->_left == nullptr)
        {
            free(h);
            return nullptr;
        }
        if (!is_red(h->_left) && !is_red(h->_left->_left))
            h = move_red_left(h);
        
        h->_left = rec_delete_min(h->_left);

        return fixup(h);
    }

    nodeptr get(nodeptr x, const K &key)
    {
        if (x == nullptr) 
            return nullptr;
        if (key == x->_key)
            return x;
        else if (key < x->_key)
            return get(x->_left, key);
        else
            return get(x->_right, key);
    }

    // Performs a LEFT or RIGHT rotate on node h
    // RIGHT ? right rotate node h : left rotate node h
    nodeptr rotate(bool RIGHT, nodeptr h) 
    {
        nodeptr x;
        RIGHT ? x = h->_left            : x = h->_right;   
        RIGHT ? h->_left = x->_right    : h->_right = x->_left;
        RIGHT ? x->_right = h           : x->_left = h;   
        x->_color = h->_color;   
        h->_color = RED;   
        return x;
    }

    nodeptr fixup(nodeptr h)
    {   
        if (is_red(h->_right))       
            h = rotate(LEFT, h);
        
        if (is_red(h->_left) && is_red(h->_left->_left)) 
            h = rotate(RIGHT, h);

        if(is_red(h->_left) && is_red(h->_right))          
            color_flip(h);

        return h;
    }

    nodeptr min_node(nodeptr h)
    {
        return h->_left != nullptr ? min_node(h->_left) : h;
    }

    nodeptr move_red_left(nodeptr h) 
    {
        color_flip(h);
        if (is_red(h->_right->_left)) 
        {
            h->_right = rotate(RIGHT, h->_right);
            h = rotate(LEFT, h);
            color_flip(h);
        }
        return h;
    }

    nodeptr move_red_right(nodeptr h) 
    {
        color_flip(h);
        if (is_red(h->_left->_left)) 
        {
            h = rotate(RIGHT, h);
            color_flip(h);
        }
        return h;
    }

    void color_flip(nodeptr h)
    {
        h->_color = !h->_color;
        h->_left->_color = !h->_left->_color;
        h->_right->_color = !h->_right->_color;
    }  

    bool is_red(const nodeptr n) const 
    {
        if (n == nullptr)
            return false;
        return n->_color;
    }

    void gen_key_list_inorder(std::list<K> &l, const nodeptr r) const 
    {
        if (r == nullptr)
            return;
        gen_key_list_inorder(l, r->_left);
        l.push_back(r->_key);
        gen_key_list_inorder(l, r->_right);
    }

    void gen_val_list_inorder(std::list<V> &l, const nodeptr r) const 
    {
        if (r == nullptr)
            return;
        gen_val_list_inorder(l, r->_left);
        l.push_back(r->_value);
        gen_val_list_inorder(l, r->_right);
    }

    //Free all the children nodes that branch from root    
    void free(nodeptr root) 
    {
        if(root != nullptr) 
        {
            free(root->_left);
            free(root->_right);
            root.reset();
        }
    }
};

#endif