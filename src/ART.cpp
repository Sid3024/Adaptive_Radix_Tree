#include "ART.hpp"




constexpr bool is_debug = false;




// adds child to existing node_ptr
// assumes that it has alr been checked that the node_ptr does not have a child for char c
// handles node_expansion if needed
void ART::add_child(Node*& node_ptr, char c, Node* child_ptr) { 
    assert(node_ptr && "called add_child() on nullptr\n");
    assert(!is_leaf(node_ptr) && "called add_child() on leaf\n");
    if (node_ptr->at_capacity()) {
        std::cout << "node at capacity" << std::endl;
        node_ptr = expand_node(node_ptr);
    }
    switch (node_ptr->node_type) {
        case NodeType::N4: {
            Node4* n4 = static_cast<Node4*>(node_ptr);
            //node_ptr = static_cast<Node16*>(node_ptr); //remove?
            n4->keys[n4->size] = c; //insert key into first empty slot (idx=size)
            n4->children[n4->size] = child_ptr; //insert new_node_ptr into (corresponding) first empty slot (idx=size)
            break;    
        }
        case NodeType::N16: {
            Node16* n16 = static_cast<Node16*>(node_ptr);
            //node_ptr = static_cast<Node16*>(node_ptr); //remove?
            n16->keys[n16->size] = c; //insert key into first empty slot (idx=size)
            n16->children[n16->size] = child_ptr; //insert new_node_ptr into (corresponding) first empty slot (idx=size)
            break;
        }
        case NodeType::N48: {
            Node48* n48 = static_cast<Node48*>(node_ptr);
            n48->ptr_arr_idx[::c_idx(c)] = n48->size; //insert idx of ptr in children arr (first empty slot; idx=size) into its pos (c-idxed)
            n48->children[n48->size] = child_ptr; //insert child ptr in first empty slot (idx=size)
            break;
        }
        case NodeType::N256: {
            Node256* n256 = static_cast<Node256*>(node_ptr);
            n256->children[::c_idx(c)] = child_ptr; //insert new_node_ptr in its pos (c-idxed)
            break;
        }
    }
    node_ptr->size++; //increment size of (parent) node
}

bool ART::is_leaf(Node* node_ptr) const {
    return node_ptr->node_type == NodeType::L;
}

//replaces a node_ptr with a different node_ptr (replaces the ptr itself, in place)
void ART::replace(Node** node_dptr, Node* new_node_ptr) {
    *node_dptr = new_node_ptr;
}

//insert a new key/value pair
bool ART::insert(std::string key, std::string value) {
    Leaf* leaf = new Leaf(key, value); //create leaf node for new key/value pair
    return insert_helper(&my_root, key, 0, leaf); //TODO: depth = 0 or 1?
}

bool ART::insert_helper(Node** node_dptr, std::string key, int depth, Leaf* leaf) {
    if (!(*node_dptr)) { //empty tree
        replace(node_dptr, leaf);
        my_size++;
        my_total_node_count++;
        return true;
    } else if (is_leaf(*node_dptr)) { 
        if (static_cast<Leaf*>(*node_dptr)->verify_key(key)) { //why need static cast to leaf if node_dptr is_leaf?
            return false; //duplicate insertion
        }
        Node* new_node_ptr = new Node4(); //curr leaf node swaps to Node4, with new_node (a leaf) as its child
        std::string existing_key = static_cast<Leaf*>(*node_dptr)->fetch_key(); //why need static cast to leaf if node_dptr is_leaf?
        int i;
        for (i=depth; key[i] == existing_key[i]; i++) {
            new_node_ptr->append_to_prefix(key[i]); // note append_to_prefix() implicitly handles prefixLen increase
            if (i >= key.length() || i >= existing_key.length()) {
                break;
            }
        }
        
        add_child(new_node_ptr, custom_index_string(existing_key, i), *node_dptr); //what if existing_key.length < i?
        add_child(new_node_ptr, custom_index_string(key, i), leaf); //what if key.length < i?
        replace(node_dptr, new_node_ptr);
        my_size++;
        my_total_node_count+=2; //adding both leaf and new_node
        return true; //successfully inserted
    } 
    int prefix_match_len = checkPrefix(*node_dptr, key, depth);
    if (prefix_match_len != (*node_dptr)->prefixLen) { // TODO: make more efficient using memcpy
        depth += prefix_match_len;
        Node* new_node_ptr = new Node4();

        add_child(new_node_ptr, custom_index_string((*node_dptr)->prefix, prefix_match_len), *node_dptr);
        add_child(new_node_ptr, custom_index_string(key, depth), leaf);

        //Node4* inspect_node_ptr = static_cast<Node4*>(*node_dptr);
        
        memcpy(new_node_ptr->prefix, (*node_dptr)->prefix, prefix_match_len);
        new_node_ptr->prefixLen = prefix_match_len;

        (*node_dptr)->prefixLen = (*node_dptr)->prefixLen - (prefix_match_len+1); //note we +1 because the prefix does not contain the discriminating byte used to guide search from the parent node to the curr node
        memmove((*node_dptr)->prefix, ((*node_dptr)->prefix)+prefix_match_len+1, (*node_dptr)->prefixLen);

        replace(node_dptr, new_node_ptr);
        my_size++;
        my_total_node_count+=2; //adding both leaf and new_node
        return true; //successfully inserted
    } else {
        depth += (*node_dptr)->prefixLen;
        Node** next_node_dptr = find_child_dptr(*node_dptr, key[depth]);
        //Node256* inspect_ptr = static_cast<Node256*>(*node_dptr);
        if (!next_node_dptr) {
            add_child(*node_dptr, key[depth], leaf);
            my_size++;
            my_total_node_count++;
            return true;
        } else {
            return insert_helper(find_child_dptr(*node_dptr, key[depth]), key, depth+1, leaf);
        }
        
    }
}


std::string ART::search(std::string key) const {
    return search_helper(my_root, key, 0);
}

std::string ART::search_helper(Node* node_ptr, std::string key, int depth) const {
    if (!node_ptr) {
        return "";
    } else if (node_ptr->node_type == NodeType::L) {
        if (static_cast<Leaf*>(node_ptr)->verify_key(key)) {
            return static_cast<Leaf*>(node_ptr)->value;
        } else {
            return "";
        }
    } else if (checkPrefix(node_ptr, key, depth) != node_ptr->prefixLen) {
        return "";
    } else {
        depth += node_ptr->prefixLen;
        return search_helper(find_child(node_ptr, key[depth]), key, depth+1); //depth+1 bcos the prefixLen does not include the discriminating byte
    }
}








Node* ART::find_child(Node* node_ptr, char c) const {
    Node** out = find_child_dptr(node_ptr, c);
    if (out) {
        return *out;
    } else { //out is null -> child is not found
        return nullptr;
    }
}

Node** ART::find_child_dptr(Node* node_ptr, char c) const {
    switch (node_ptr->node_type) {
        case NodeType::N4: {
            Node4* n4 = static_cast<Node4*>(node_ptr);
            for (int i=0;i<n4->size;i++) {
                if (c == n4->keys[i]) {
                    return &n4->children[i];
                }
            }
            break;
        }
        case NodeType::N16: {
            Node16* n16 = static_cast<Node16*>(node_ptr);
            for (int i=0;i<16;i++) { //TODO: speed up using simd
                if (c == n16->keys[i]) {
                    return &n16->children[i];
                }
            }
            break;
        }
        case NodeType::N48: {
            Node48* n48 = static_cast<Node48*>(node_ptr);
            int idx = n48->ptr_arr_idx[::c_idx(c)]; 
            if (idx != -1) {
                return &n48->children[idx];
            } else {
                return nullptr;
            }
            break;
        }
        case NodeType::N256: {
            Node256* n256 = static_cast<Node256*>(node_ptr);
            if (!n256->children[::c_idx(c)]) {
                return nullptr;
            }
            else {
                return &n256->children[::c_idx(c)];
            }
            
            break;
        }
    }
    assert("exited find_child_dptr w/o returning Node ptr\n");
    return nullptr;
}

int ART::checkPrefix(Node* node, std::string key, int depth) const {
    for (int i=0;i<node->prefixLen;i++) {
        if (key[depth+i] != node->prefix[i]) { //+1 bcos we dont include the discriminating char in prefix //WRONG, depth is alr at position one after the discriminating prefix
            return i;
        }
    }
    return node->prefixLen;
}

Node* ART::expand_node(Node* node_ptr) {
    switch (node_ptr->node_type) {
        case NodeType::N4: {
            auto* n4 = static_cast<Node4*>(node_ptr);
            return new Node16(n4);
            break;
        }
        case NodeType::N16: {
            auto* n16 = static_cast<Node16*>(node_ptr);
            return new Node48(n16);
            break;
        }
        case NodeType::N48: {
            auto* n48 = static_cast<Node48*>(node_ptr);
            return new Node256(n48);
            break;
        }
        case NodeType::N256: {
            throw std::logic_error("called expand_node on Node256\n");
            break;
        }
    }
    assert("exited expand_node() without returning Node ptr\n");
    return nullptr;
}




















