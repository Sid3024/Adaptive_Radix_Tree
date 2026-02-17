#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include <algorithm>  // for std::fill
#include <iterator>   // for std::begin, std::end (C++11 and later)
#include <cstdint>

inline std::uint8_t c_idx(char c) {
    return static_cast<std::uint8_t>(static_cast<unsigned char>(c));
}

const int MAX_PREFIX_LEN = 8;
inline constexpr char NULLCHAR = 0;

// inline uint8_t c_idx(char c) {
//     return static_cast<uint8_t>(c);
// }


struct data {
    std::string key;
    std::string value;
};


enum NodeType {
    N4,
    N16,
    N48,
    N256,
    L
};

struct Node {
    NodeType node_type;
    int size = 0, prefixLen = 0, capacity = 0;
    bool has_prefix_capacity_exceeded = false;
    char prefix[MAX_PREFIX_LEN]{}; //do i need to set to ""
    virtual Node* find_child(char c) {
        return nullptr;
    }

    bool verify_prefix(std::string expected_prefix) {
        std::string s = std::string(prefix, std::min(prefixLen, MAX_PREFIX_LEN));
        return (s == expected_prefix);
    }

    int get_compare_len() {
        return (prefixLen > MAX_PREFIX_LEN) ? MAX_PREFIX_LEN : prefixLen;
    }

    int get_size() {
        return size;
    }
    bool at_capacity() {
        return size == capacity;
    }
    void append_to_prefix(char c) {
        
        if (prefixLen < MAX_PREFIX_LEN) {
            prefix[prefixLen] = c;
            
        } else {
            std::cout << "ABC: " << c << std::endl << "prefixLen: " << prefixLen << " MAX_PREFIX_LEN: " << MAX_PREFIX_LEN << std::endl;
            has_prefix_capacity_exceeded = true;
        }
        prefixLen++;//even if prefixLen>8 must keep increasing so program knows to skip that number of bytes when passing over the node
    }
    
    char prefix_head() {
        return prefix[0];
    }

    std::string read_prefix() {
        std::string s;
        for (int i=0;i<prefixLen;i++) {
            s.push_back(prefix[i]);
        }
        return s;
    }

    void copy_into_prefix(void* src, size_t size, std::string s, int depth) {
        if (s == "") {
            memcpy(&prefix, src, size);
        } else {

        }
        if (size > MAX_PREFIX_LEN) {
            has_prefix_capacity_exceeded = true;
            
        } else {
            memcpy(&prefix, src, size);
        }
        
    }

    void update_prefix_len(int new_prefix_len) {
        prefixLen = new_prefix_len;
        // if (new_prefix_len > MAX_PREFIX_LEN) {
        //     prefixLen = MAX_PREFIX_LEN;
        // } else {
        //     prefixLen = new_prefix_len;
        // }
    }

};

struct Node4 : public Node {
    char keys[4]{};
    Node* children[4]{}; // do i need to init to nullptr
    Node4() {
        node_type = NodeType::N4;
        capacity = 4;
    }
    Node4(char c) {
        node_type = NodeType::N4;
        capacity = 4;
        append_to_prefix(c); //wnhy not just assign
    }
    //do i need ctr for a string (ie prefix set to >1char)

};

struct Node16 : public Node {
    char keys[16]{};
    Node* children[16]{};

    Node16(Node4* n4) {
        int i;
        for (i=0;i<4;i++) {
            keys[i] = n4->keys[i];
            children[i] = n4->children[i];
        }
        size = n4->get_size();
        node_type = NodeType::N16;
        capacity = 16;
        prefixLen = n4->prefixLen;
        std::memcpy(&prefix, &n4->prefix, prefixLen);
    }
    
    Node16(char* init_key_arr, Node** init_children_arr, int copy_size) {
        assert(copy_size <= 16 && "called Node48 ctor called with copy_size >16\n");
        int i;
        for (i=0;i<copy_size;i++) {
            keys[i] = init_key_arr[i];
            children[i] = init_children_arr[i];
        }
        for (;i<16;i++) {
            keys[i] = NULLCHAR;
            children[i] = nullptr;
        }
        node_type = NodeType::N16;
        capacity = 16;
    }
};

struct Node48 : public Node {
    int ptr_arr_idx[256]{};
    
    Node* children[48]{};

    Node48(Node16* n16) {
        std::fill(std::begin(ptr_arr_idx), std::end(ptr_arr_idx), -1);
        for (int i=0;i<16;i++) {
            ptr_arr_idx[c_idx(n16->keys[i])] = i;
            children[i] = n16->children[i];
        }
        size = 16;
        node_type = NodeType::N48;
        capacity = 48;
        prefixLen = n16->prefixLen;
        std::memcpy(&prefix, &n16->prefix, prefixLen);
    }

    Node48(char* init_key_arr, Node** init_children_arr, int copy_size) {
        assert(copy_size <= 48 && "called Node48 ctor called with copy_size >16\n");
        node_type = NodeType::N48;
        for (int i=0;i<48;i++) {
            ptr_arr_idx[i] = -1;
        }
        for (int i=0;i<copy_size;i++) {
            ptr_arr_idx[init_key_arr[i]] = i;
            children[i] = init_children_arr[i];
        }
        capacity = 48; //shouldnt this be outside ctor?
    }
};

struct Node256 : public Node {
    Node* children[256] = {}; //init nullptr?
    
    Node256(char* init_key_arr, Node** init_children_arr, int copy_size) { 
        node_type = NodeType::N256;
        for (int i=0;i<copy_size;i++) {
            children[init_key_arr[i]] = init_children_arr[i]; 
            //shouldnt init_children_arr be Node*, not Node**, since children holds the node objects, not node ptrs?
        }
        
        capacity = 256; //shouldnt this be outside ctor?
    }

    Node256(Node48* n48) {
        int c;
        for (int i=0;i<256;i++) {
            c = n48->ptr_arr_idx[i];
            if (c != -1) {
                children[c_idx(c)] = n48->children[i];
                //shouldnt it be children[i] = n48->children[c_idx(c)];
            }
        }
        size = 48;
        node_type = NodeType::N256;
        capacity = 256;
        prefixLen = n48->prefixLen;
        std::memcpy(&prefix, &n48->prefix, prefixLen);
    }
};

struct Leaf : public Node {
    std::string key;
    std::string value;
    Leaf(std::string k, std::string val) : key(k), value(val) {
        node_type = NodeType::L;
    }
    bool verify_key(std::string k) {
        return key == k;
    }
    std::string fetch_key() { //TODO: shld i return in place?
        return key; 
    }
};


class ART {
private:
    Node* my_root = nullptr;
    int my_size = 0;
    int my_total_node_count = 0;
    Leaf* find_leaf(std::string key) const;
    Node* expand_node(Node* node_ptr);
    int checkPrefix(Node* node, std::string key, int depth) const;
    Node* find_child(Node* node_ptr, char c) const;
    Node** find_child_dptr(Node* node_ptr, char c) const;
    void replace(Node** node_dptr, Node* new_node_ptr);
    bool is_leaf(Node* node_ptr) const;
    void add_child(Node*& node_ptr, char c, Node* child_ptr);
    bool insert_helper(Node** node_dptr, std::string key, int depth, Leaf* leaf);
    std::string pop_helper(Node** node_dptr, std::string key, int depth);
    Node* shrink_node(Node* node_ptr);
    void radix_sort(data* data_arr, int start_idx, int end_idx, int depth, data* radix_sorted_arr, int* size_arr, int* idx_arr, bool* char_is_present_arr);
    void bulk_construct_helper(Node* root_node, int depth, data* data_arr, int start_idx, int end_idx, data* copy_to_arr);
    std::string search_helper(Node* node_ptr, std::string key, int depth, bool has_prefix_capacity_exceeded_somewhere) const;
    Leaf* find_any_leaf(Node* node_ptr) const;
    char custom_index_string(std::string s, int i) { //returns null char if s.length == i, which is needed for ART logic
        return (s.length() == i) ? '\0' : s[i];
    }
    
    
public:
    std::string search(std::string key) const;
    bool insert(std::string key, std::string value);
    std::string pop(std::string key);
    void bulk_construct(data* data_arr, int arr_len);
    bool empty() {
        return my_size == 0;
    }
    int get_size() {
        return my_size;
    }
    Node* get_root() {
        return my_root;
    }
    int get_total_node_count() {
        return my_total_node_count;
    }
};
