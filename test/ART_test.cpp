#include "gtest/gtest.h"
#include "../src/ART.hpp"

TEST(ARTTest, InitTree) {
    ART tree;
    EXPECT_EQ(0, tree.get_size());
    EXPECT_TRUE(tree.empty());
    EXPECT_FALSE(tree.get_root());    
}

//test: insert (single insert in empty tree)
//relies on: NIL
TEST(ARTTest, SingleInsert) {
    ART tree;
    tree.insert("abc", "hello world");
    EXPECT_TRUE(tree.get_root());
    EXPECT_EQ(1, tree.get_size());
    EXPECT_EQ(NodeType::L, tree.get_root()->node_type);
    EXPECT_EQ("abc", static_cast<Leaf*>(tree.get_root())->key);
    EXPECT_EQ("hello world", static_cast<Leaf*>(tree.get_root())->value);
}

//test: search (single node tree)
//relies on: insert (single insert in empty tree)
TEST(ARTTest, SingleSearch) {
    ART tree;
    tree.insert("abc", "hello world");
    EXPECT_EQ("hello world", tree.search("abc"));
    EXPECT_EQ("", tree.search("bcd"));
    EXPECT_EQ("", tree.search(""));
}

/*
Double insert
//test: insert (double insert in empty tree)
//relies on: NIL

Double search
//test: search (double search in empty tree)
//relies on: insert (double insert in empty tree)

id/test
1/tree_neight 2, diff first letter
2/tree_height 2, same first letter
3/tree height 2, same first few (4) letters
*/


TEST(ARTTest, DoubleInsert1) {
    ART tree;
    tree.insert("bcd", "bye");
    tree.insert("abc", "hello world");
    
    EXPECT_EQ(2, tree.get_size());
    EXPECT_EQ(3, tree.get_total_node_count());
    EXPECT_EQ(NodeType::N4, (tree.get_root())->node_type);
    EXPECT_EQ(2, (tree.get_root())->size);
    EXPECT_EQ("", (tree.get_root())->read_prefix());
    EXPECT_EQ(0, (tree.get_root())->prefixLen);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[0]);
    EXPECT_EQ('b', ((static_cast<Node4*>(tree.get_root()))->keys[0]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[0])->node_type);
    EXPECT_EQ("bcd", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->key);
    EXPECT_EQ("bye", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->value);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[1]);
    EXPECT_EQ('a', ((static_cast<Node4*>(tree.get_root()))->keys[1]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[1])->node_type);
    EXPECT_EQ("abc", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->key);
    EXPECT_EQ("hello world", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->value);
}


TEST(ARTTest, DoubleSearch1) {
    ART tree;
    tree.insert("bcd", "bye");
    tree.insert("abc", "hello world");
    
    EXPECT_EQ("hello world", tree.search("abc"));
    EXPECT_EQ("bye", tree.search("bcd"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("", tree.search(""));
}

TEST(ARTTest, DoubleInsert2) {
    ART tree;
    tree.insert("bef", "bye");
    tree.insert("bcd", "hello world");
    
    EXPECT_EQ(2, tree.get_size());
    EXPECT_EQ(3, tree.get_total_node_count());
    EXPECT_EQ(NodeType::N4, (tree.get_root())->node_type);
    EXPECT_EQ(2, (tree.get_root())->size);
    EXPECT_EQ("b", (tree.get_root())->read_prefix());
    EXPECT_EQ(1, (tree.get_root())->prefixLen);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[0]);
    EXPECT_EQ('e', ((static_cast<Node4*>(tree.get_root()))->keys[0]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[0])->node_type);
    EXPECT_EQ("bef", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->key);
    EXPECT_EQ("bye", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->value);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[1]);
    EXPECT_EQ('c', ((static_cast<Node4*>(tree.get_root()))->keys[1]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[1])->node_type);
    EXPECT_EQ("bcd", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->key);
    EXPECT_EQ("hello world", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->value);
}

TEST(ARTTest, DoubleSearch2) {
    ART tree;
    tree.insert("bef", "bye");
    tree.insert("bcd", "hello world");
    
    EXPECT_EQ("hello world", tree.search("bcd"));
    EXPECT_EQ("bye", tree.search("bef"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("", tree.search(""));
}

TEST(ARTTest, DoubleInsert3) {
    ART tree;
    tree.insert("bcdIJKL", "bye");
    tree.insert("bcdIxyz", "hello world");
    
    EXPECT_EQ(2, tree.get_size());
    EXPECT_EQ(3, tree.get_total_node_count());
    EXPECT_EQ(NodeType::N4, (tree.get_root())->node_type);
    EXPECT_EQ(2, (tree.get_root())->size);
    EXPECT_EQ("bcdI", (tree.get_root())->read_prefix());
    EXPECT_EQ(4, (tree.get_root())->prefixLen);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[0]);
    EXPECT_EQ('J', ((static_cast<Node4*>(tree.get_root()))->keys[0]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[0])->node_type);
    EXPECT_EQ("bcdIJKL", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->key);
    EXPECT_EQ("bye", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->value);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[1]);
    EXPECT_EQ('x', ((static_cast<Node4*>(tree.get_root()))->keys[1]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[1])->node_type);
    EXPECT_EQ("bcdIxyz", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->key);
    EXPECT_EQ("hello world", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->value);
}

TEST(ARTTest, DoubleSearch3) {
    ART tree;
    tree.insert("bcdIxyz", "hello world");
    tree.insert("bcdIJKL", "bye");

    
    EXPECT_EQ("hello world", tree.search("bcdIxyz"));
    EXPECT_EQ("bye", tree.search("bcdIJKL"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("", tree.search(""));
}

TEST(ARTTest, DoubleInsert4) {
    ART tree;
    tree.insert("abc", "hello");
    tree.insert("abcdef", "bye");
    
    EXPECT_EQ(2, tree.get_size());
    EXPECT_EQ(3, tree.get_total_node_count());
    EXPECT_EQ(NodeType::N4, (tree.get_root())->node_type);
    EXPECT_EQ(2, (tree.get_root())->size);
    EXPECT_EQ("abc", (tree.get_root())->read_prefix());
    EXPECT_EQ(3, (tree.get_root())->prefixLen);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[0]);
    EXPECT_EQ('\0', ((static_cast<Node4*>(tree.get_root()))->keys[0]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[0])->node_type);
    EXPECT_EQ("abc", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->key);
    EXPECT_EQ("hello", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->value);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[1]);
    EXPECT_EQ('d', ((static_cast<Node4*>(tree.get_root()))->keys[1]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[1])->node_type);
    EXPECT_EQ("abcdef", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->key);
    EXPECT_EQ("bye", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->value);
}

TEST(ARTTest, DoubleSearch4) {
    ART tree;
    tree.insert("abc", "hello");
    tree.insert("abcdef", "bye");

    EXPECT_EQ("hello", tree.search("abc"));
    EXPECT_EQ("bye", tree.search("abcdef"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("", tree.search(""));
}

TEST(ARTTest, DoubleInsert5) {
    ART tree;
    tree.insert("abcdef", "hello");
    tree.insert("abc", "bye");

    EXPECT_EQ(2, tree.get_size());
    EXPECT_EQ(3, tree.get_total_node_count());
    EXPECT_EQ(NodeType::N4, (tree.get_root())->node_type);
    EXPECT_EQ(2, (tree.get_root())->size);
    EXPECT_EQ("abc", (tree.get_root())->read_prefix());
    EXPECT_EQ(3, (tree.get_root())->prefixLen);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[0]);
    EXPECT_EQ('d', ((static_cast<Node4*>(tree.get_root()))->keys[0]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[0])->node_type);
    EXPECT_EQ("abcdef", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->key);
    EXPECT_EQ("hello", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]))->value);

    EXPECT_TRUE((static_cast<Node4*>(tree.get_root()))->children[1]);
    EXPECT_EQ('\0', ((static_cast<Node4*>(tree.get_root()))->keys[1]));
    EXPECT_EQ(NodeType::L, ((static_cast<Node4*>(tree.get_root()))->children[1])->node_type);
    EXPECT_EQ("abc", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->key);
    EXPECT_EQ("bye", (static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]))->value);


}

TEST(ARTTest, DoubleSearch5) {
    ART tree;
    tree.insert("abcdef", "hello");
    tree.insert("abc", "bye");

    EXPECT_EQ("hello", tree.search("abcdef"));
    EXPECT_EQ("bye", tree.search("abc"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("", tree.search(""));
}

/*
Triple insert
//test: insert (Triple insert in empty tree)
//relies on: NIL

Triple search
//test: search (Triple search in empty tree)
//relies on: insert (Triple insert in empty tree)

id/test
1/tree_neight 2, diff first letter
2/tree_height 2, same first letter
3/tree height 2, same first few (4) letters
*/

TEST(ARTTest, TripleInsert1) {
    ART tree;
    tree.insert("abc", "hello");
    tree.insert("bcd", "bye");
    tree.insert("acd", "what");
    
    EXPECT_EQ(3, tree.get_size());
    EXPECT_EQ(5, tree.get_total_node_count());

    //check root node exists and is N4
    ASSERT_TRUE(tree.get_root());
    ASSERT_EQ(NodeType::N4, (tree.get_root())->node_type);

    //check root node attributes
    Node4* root_node = static_cast<Node4*>(tree.get_root());
    EXPECT_EQ(2, root_node->size);
    EXPECT_EQ("", root_node->read_prefix());
    EXPECT_EQ(0, root_node->prefixLen);

    //check bcd node exists and is leaf
    ASSERT_TRUE(static_cast<Leaf*>(root_node->children[1]));
    EXPECT_EQ('b', ((static_cast<Node4*>(tree.get_root()))->keys[1]));
    ASSERT_EQ(NodeType::L, static_cast<Leaf*>(root_node->children[1])->node_type);

    //check bcd node attributes
    Leaf* bcd_leaf = static_cast<Leaf*>(root_node->children[1]);
    EXPECT_EQ("bcd", bcd_leaf->key);
    EXPECT_EQ("bye", bcd_leaf->value);

    //check 2nd layer N4 node exists and is N4
    ASSERT_TRUE(root_node->children[0]);
    EXPECT_EQ('a', ((static_cast<Node4*>(root_node))->keys[0]));
    ASSERT_EQ(NodeType::N4, (root_node->children[0])->node_type);

    //check 2nd layer N4 node attributes
    Node4* h2_n4_node = static_cast<Node4*>(root_node->children[0]);
    EXPECT_EQ(2, h2_n4_node->size);
    EXPECT_EQ("", h2_n4_node->read_prefix());
    EXPECT_EQ(0, h2_n4_node->prefixLen);
    
    //check abc node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[0]);
    EXPECT_EQ('b', ((static_cast<Node4*>(h2_n4_node))->keys[0]));
    ASSERT_EQ(NodeType::L, h2_n4_node->children[0]->node_type);
    
    //check abc node exists and is leaf
    Leaf* abc_node= static_cast<Leaf*>(h2_n4_node->children[0]);
    EXPECT_EQ("abc", abc_node->key);
    EXPECT_EQ("hello", abc_node->value);

    //check acd node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[1]);
    EXPECT_EQ('c', ((static_cast<Node4*>(h2_n4_node))->keys[1]));
    ASSERT_EQ(NodeType::L, h2_n4_node->children[1]->node_type);
    
    //check acd node exists and is leaf
    Leaf* acd_node = static_cast<Leaf*>(h2_n4_node->children[1]);
    EXPECT_EQ("acd", acd_node->key);
    EXPECT_EQ("what", acd_node->value);
}

TEST(ARTTest, TripleSearch1) {
    ART tree;
    tree.insert("abc", "hello");
    tree.insert("bcd", "bye");
    tree.insert("acd", "what");

    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("", tree.search(""));
    EXPECT_EQ("bye", tree.search("bcd"));
    EXPECT_EQ("what", tree.search("acd"));
    EXPECT_EQ("hello", tree.search("abc")); 
}

TEST(ARTTest, TripleInsert2) {
    ART tree;
    tree.insert("abc", "hello");
    tree.insert("bcd", "bye");
    tree.insert("abd", "what");
    
    EXPECT_EQ(3, tree.get_size());
    EXPECT_EQ(5, tree.get_total_node_count());

    //check root node exists and is N4
    ASSERT_TRUE(tree.get_root());
    ASSERT_EQ(NodeType::N4, (tree.get_root())->node_type);

    //check root node attributes
    Node4* root_node = static_cast<Node4*>(tree.get_root());
    EXPECT_EQ(2, root_node->size);
    EXPECT_EQ("", root_node->read_prefix());
    EXPECT_EQ(0, root_node->prefixLen);

    //check bcd node exists and is leaf
    ASSERT_TRUE(static_cast<Leaf*>(root_node->children[1]));
    EXPECT_EQ('b', ((static_cast<Node4*>(root_node))->keys[1]));
    ASSERT_EQ(NodeType::L, static_cast<Leaf*>(root_node->children[1])->node_type);

    //check bcd node attributes
    Leaf* bcd_leaf = static_cast<Leaf*>(root_node->children[1]);
    EXPECT_EQ("bcd", bcd_leaf->key);
    EXPECT_EQ("bye", bcd_leaf->value);

    //check 2nd layer N4 node exists and is N4
    ASSERT_TRUE(root_node->children[0]);
    ASSERT_EQ(NodeType::N4, (root_node->children[0])->node_type);
    EXPECT_EQ('a', ((static_cast<Node4*>(root_node))->keys[0]));

    //check 2nd layer N4 node attributes
    Node4* h2_n4_node = static_cast<Node4*>(root_node->children[0]);
    EXPECT_EQ(2, h2_n4_node->size);
    EXPECT_EQ("b", h2_n4_node->read_prefix()); //only b, not ab, bcos prefix does not include the discriminating byte
    EXPECT_EQ(1, h2_n4_node->prefixLen);
    
    //check abc node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[0]);
    ASSERT_EQ(NodeType::L, h2_n4_node->children[0]->node_type);
    EXPECT_EQ('c', ((static_cast<Node4*>(h2_n4_node))->keys[0]));
    
    //check abc node exists and is leaf
    Leaf* abc_node= static_cast<Leaf*>(h2_n4_node->children[0]);
    EXPECT_EQ("abc", abc_node->key);
    EXPECT_EQ("hello", abc_node->value);

    //check acd node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[1]);
    ASSERT_EQ(NodeType::L, h2_n4_node->children[1]->node_type);
    EXPECT_EQ('d', ((static_cast<Node4*>(h2_n4_node))->keys[1]));
    
    //check acd node exists and is leaf
    Leaf* acd_node = static_cast<Leaf*>(h2_n4_node->children[1]);
    EXPECT_EQ("abd", acd_node->key);
    EXPECT_EQ("what", acd_node->value);
}

TEST(ARTTest, TripleSearch2) {
    ART tree;
    tree.insert("abc", "hello");
    tree.insert("bcd", "bye");
    tree.insert("abd", "what");

    EXPECT_EQ("bye", tree.search("bcd"));
    EXPECT_EQ("", tree.search(""));
    EXPECT_EQ("what", tree.search("abd"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("hello", tree.search("abc")); 
}


TEST(ARTTest, TripleInsert3) {
    ART tree;
    tree.insert("abcdefghi", "hello");
    tree.insert("abcxyz", "bye");
    tree.insert("abcdefwxyz", "what");
    
    EXPECT_EQ(3, tree.get_size());
    EXPECT_EQ(5, tree.get_total_node_count());

    //check root node exists and is N4
    ASSERT_TRUE(tree.get_root());
    ASSERT_EQ(NodeType::N4, (tree.get_root())->node_type);

    //check root node attributes
    Node4* root_node = static_cast<Node4*>(tree.get_root());
    EXPECT_EQ(2, root_node->size);
    EXPECT_EQ("abc", root_node->read_prefix());
    EXPECT_EQ(3, root_node->prefixLen);

    //check bcd node exists and is leaf
    ASSERT_TRUE(static_cast<Leaf*>(root_node->children[1]));
    ASSERT_EQ(NodeType::L, static_cast<Leaf*>(root_node->children[1])->node_type);
    EXPECT_EQ('x', ((static_cast<Node4*>(root_node))->keys[1]));

    //check bcd node attributes
    Leaf* bcd_leaf = static_cast<Leaf*>(root_node->children[1]);
    EXPECT_EQ("abcxyz", bcd_leaf->key);
    EXPECT_EQ("bye", bcd_leaf->value);

    //check 2nd layer N4 node exists and is N4
    ASSERT_TRUE(root_node->children[0]);
    ASSERT_EQ(NodeType::N4, (root_node->children[0])->node_type);
    EXPECT_EQ('d', ((static_cast<Node4*>(root_node))->keys[0]));

    //check 2nd layer N4 node attributes
    Node4* h2_n4_node = static_cast<Node4*>(root_node->children[0]);
    EXPECT_EQ(2, h2_n4_node->size);
    EXPECT_EQ("ef", h2_n4_node->read_prefix());
    EXPECT_EQ(2, h2_n4_node->prefixLen);
    
    //check abc node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[0]);
    ASSERT_EQ(NodeType::L, h2_n4_node->children[0]->node_type);
    EXPECT_EQ('g', ((static_cast<Node4*>(h2_n4_node))->keys[0]));
    
    //check abc node exists and is leaf
    Leaf* abc_node= static_cast<Leaf*>(h2_n4_node->children[0]);
    EXPECT_EQ("abcdefghi", abc_node->key);
    EXPECT_EQ("hello", abc_node->value);

    //check acd node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[1]);
    ASSERT_EQ(NodeType::L, h2_n4_node->children[1]->node_type);
    EXPECT_EQ('w', ((static_cast<Node4*>(h2_n4_node))->keys[1]));
    
    //check acd node exists and is leaf
    Leaf* acd_node = static_cast<Leaf*>(h2_n4_node->children[1]);
    EXPECT_EQ("abcdefwxyz", acd_node->key);
    EXPECT_EQ("what", acd_node->value);
}

TEST(ARTTest, TripleSearch3) {
    ART tree;
    tree.insert("abcdefghi", "hello");
    tree.insert("abcxyz", "bye");
    tree.insert("abcdefwxyz", "what");

    EXPECT_EQ("hello", tree.search("abcdefghi"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("what", tree.search("abcdefwxyz"));
    EXPECT_EQ("bye", tree.search("abcxyz"));
    EXPECT_EQ("", tree.search(""));
     
}


TEST(ARTTest, TripleInsert4) {
    ART tree;
    tree.insert("abcdefghi", "hello");
    tree.insert("abcdefwxyz", "what");
    tree.insert("abcxyz", "bye");
    
    EXPECT_EQ(3, tree.get_size());
    EXPECT_EQ(5, tree.get_total_node_count());

    //check root node exists and is N4
    ASSERT_TRUE(tree.get_root());
    ASSERT_EQ(NodeType::N4, (tree.get_root())->node_type);

    //check root node attributes
    Node4* root_node = static_cast<Node4*>(tree.get_root());
    EXPECT_EQ(2, root_node->size);
    EXPECT_EQ("abc", root_node->read_prefix());
    EXPECT_EQ(3, root_node->prefixLen);

    //check bcd node exists and is leaf
    ASSERT_TRUE(static_cast<Leaf*>(root_node->children[1]));
    ASSERT_EQ(NodeType::L, static_cast<Leaf*>(root_node->children[1])->node_type);
    EXPECT_EQ('x', ((static_cast<Node4*>(root_node))->keys[1]));

    //check bcd node attributes
    Leaf* bcd_leaf = static_cast<Leaf*>(root_node->children[1]);
    EXPECT_EQ("abcxyz", bcd_leaf->key);
    EXPECT_EQ("bye", bcd_leaf->value);

    //check 2nd layer N4 node exists and is N4
    ASSERT_TRUE(root_node->children[0]);
    ASSERT_EQ(NodeType::N4, (root_node->children[0])->node_type);
    EXPECT_EQ('d', ((static_cast<Node4*>(root_node))->keys[0]));

    //check 2nd layer N4 node attributes
    Node4* h2_n4_node = static_cast<Node4*>(root_node->children[0]);
    EXPECT_EQ(2, h2_n4_node->size);
    EXPECT_EQ("ef", h2_n4_node->read_prefix());
    EXPECT_EQ(2, h2_n4_node->prefixLen);
    
    //check abc node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[0]);
    ASSERT_EQ(NodeType::L, h2_n4_node->children[0]->node_type);
    EXPECT_EQ('g', ((static_cast<Node4*>(h2_n4_node))->keys[0]));
    
    //check abc node exists and is leaf
    Leaf* abc_node= static_cast<Leaf*>(h2_n4_node->children[0]);
    EXPECT_EQ("abcdefghi", abc_node->key);
    EXPECT_EQ("hello", abc_node->value);

    //check acd node exists and is leaf
    ASSERT_TRUE(h2_n4_node->children[1]);
    ASSERT_EQ(NodeType::L, h2_n4_node->children[1]->node_type);
    EXPECT_EQ('w', ((static_cast<Node4*>(h2_n4_node))->keys[1]));
    
    //check acd node exists and is leaf
    Leaf* acd_node = static_cast<Leaf*>(h2_n4_node->children[1]);
    EXPECT_EQ("abcdefwxyz", acd_node->key);
    EXPECT_EQ("what", acd_node->value);
}

TEST(ARTTest, TripleSearch4) {
    ART tree;
    tree.insert("abcdefghi", "hello");
    tree.insert("abcdefwxyz", "what");
    tree.insert("abcxyz", "bye");
    

    EXPECT_EQ("hello", tree.search("abcdefghi"));
    EXPECT_EQ("", tree.search("cde"));
    EXPECT_EQ("what", tree.search("abcdefwxyz"));
    EXPECT_EQ("bye", tree.search("abcxyz"));
    EXPECT_EQ("", tree.search(""));
     
}