#include "gtest/gtest.h"
#include "../src/ART.hpp"
#define FIRST_CHAR 0


// TEST(NodeTest, NodeFunctionalityTest) {
//     ART tree;
    
//     for (int i=FIRST_CHAR;i<FIRST_CHAR+4;i++) {
//         tree.insert(std::string(1, char(i)), std::string(1, char(i)));
//         EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
//         if (i!=FIRST_CHAR) {
//             EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
//             EXPECT_EQ(NodeType::N4, (tree.get_root())->node_type);
//         } else {
//             EXPECT_EQ(NodeType::L, (tree.get_root())->node_type);
//         }
//     }

//     for (int i=FIRST_CHAR;i<FIRST_CHAR+4;i++) {
//         EXPECT_EQ(std::string(1, char(i)), tree.search(std::string(1, char(i))));
//     }

//     tree.insert(std::string(1, char(FIRST_CHAR+4)), std::string(1, char(FIRST_CHAR+4)));
//     EXPECT_EQ(4+1, tree.get_size());
//     EXPECT_EQ(4+1, (tree.get_root())->size);
//     EXPECT_EQ(NodeType::N16, (tree.get_root())->node_type);

//     for (int i=FIRST_CHAR;i<=FIRST_CHAR+4;i++) {
//         EXPECT_EQ(std::string(1, char(i)), tree.search(std::string(1, char(i))));
//     }

//     for (int i=FIRST_CHAR+5;i<FIRST_CHAR+16;i++) {
//         tree.insert(std::string(1, char(i)), std::string(1, char(i)));
//         EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
//         EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
//         EXPECT_EQ(NodeType::N16, (tree.get_root())->node_type);
//     }

//     for (int i=FIRST_CHAR;i<FIRST_CHAR+16;i++) {
//         EXPECT_EQ(std::string(1, char(i)), tree.search(std::string(1, char(i))));
//     }

//     tree.insert(std::string(1, char(FIRST_CHAR+16)), std::string(1, char(FIRST_CHAR+16)));
//     EXPECT_EQ(16+1, (tree.get_root())->size);
//     EXPECT_EQ(NodeType::N48, (tree.get_root())->node_type);

//     for (int i=FIRST_CHAR;i<=FIRST_CHAR+16;i++) {
//         EXPECT_EQ(std::string(1, char(i)), tree.search(std::string(1, char(i))));
//     }

//     for (int i=FIRST_CHAR+17;i<FIRST_CHAR+48;i++) {
//         tree.insert(std::string(1, char(i)), std::string(1, char(i)));
//         EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
//         EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
//         EXPECT_EQ(NodeType::N48, (tree.get_root())->node_type);
//     }

//     for (int i=FIRST_CHAR;i<FIRST_CHAR+48;i++) {
//         EXPECT_EQ(std::string(1, char(i)), tree.search(std::string(1, char(i))));
//     }

//     tree.insert(std::string(1, char(FIRST_CHAR+48)), std::string(1, char(FIRST_CHAR+48)));
//     EXPECT_EQ(48+1, (tree.get_root())->size);
//     EXPECT_EQ(NodeType::N256, (tree.get_root())->node_type);

//     for (int i=FIRST_CHAR;i<=FIRST_CHAR+48;i++) {
//         EXPECT_EQ(std::string(1, char(i)), tree.search(std::string(1, char(i))));
//     }

//     for (int i=FIRST_CHAR+49;i<FIRST_CHAR+256;i++) {
//         tree.insert(std::string(1, char(i)), std::string(1, char(i)));
//         EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
//         EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
//         EXPECT_EQ(NodeType::N256, (tree.get_root())->node_type);
//     }

//     for (int i=FIRST_CHAR;i<FIRST_CHAR+256;i++) {
//         EXPECT_EQ(std::string(1, char(i)), tree.search(std::string(1, char(i))));
//     }
// }

TEST(NodeTest, SingleNodeExpansion) {
    ART tree;
    tree.insert("a", "0");
    tree.insert("ab", "1");
    tree.insert("ac", "2");
    tree.insert("ad", "3");

    Leaf* my_leaf;

    EXPECT_TRUE(tree.get_root());
    EXPECT_EQ(NodeType::N4, (static_cast<Node4*>(tree.get_root()))->node_type);
    EXPECT_EQ("a", (static_cast<Node4*>(tree.get_root()))->read_prefix());
    EXPECT_TRUE(static_cast<Node4*>(tree.get_root())->children[0]);
    EXPECT_EQ(NodeType::L, (static_cast<Node4*>(tree.get_root()))->children[0]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[0]);
    EXPECT_EQ("a", my_leaf->key);
    EXPECT_EQ("0", my_leaf->value);
    EXPECT_TRUE(static_cast<Node4*>(tree.get_root())->children[1]);
    EXPECT_EQ(NodeType::L, (static_cast<Node4*>(tree.get_root()))->children[1]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[1]);
    EXPECT_EQ("ab", my_leaf->key);
    EXPECT_EQ("1", my_leaf->value);
    EXPECT_TRUE(static_cast<Node4*>(tree.get_root())->children[2]);
    EXPECT_EQ(NodeType::L, (static_cast<Node4*>(tree.get_root()))->children[2]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[2]);
    EXPECT_EQ("ac", my_leaf->key);
    EXPECT_EQ("2", my_leaf->value);
    EXPECT_TRUE(static_cast<Node4*>(tree.get_root())->children[3]);
    EXPECT_EQ(NodeType::L, (static_cast<Node4*>(tree.get_root()))->children[3]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node4*>(tree.get_root()))->children[3]);
    EXPECT_EQ("ad", my_leaf->key);
    EXPECT_EQ("3", my_leaf->value);
    
    EXPECT_EQ("0", tree.search("a"));
    EXPECT_EQ("1", tree.search("ab"));
    EXPECT_EQ("2", tree.search("ac"));
    EXPECT_EQ("3", tree.search("ad"));

    tree.insert("ae", "4"); //expansion
    

    EXPECT_TRUE(tree.get_root());
    EXPECT_EQ(NodeType::N16, (static_cast<Node16*>(tree.get_root()))->node_type);
    EXPECT_EQ("a", (static_cast<Node16*>(tree.get_root()))->read_prefix());
    EXPECT_TRUE(static_cast<Node16*>(tree.get_root())->children[0]);
    EXPECT_EQ(NodeType::L, (static_cast<Node16*>(tree.get_root()))->children[0]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node16*>(tree.get_root()))->children[0]);
    EXPECT_EQ("a", my_leaf->key);
    EXPECT_EQ("0", my_leaf->value);
    EXPECT_TRUE(static_cast<Node16*>(tree.get_root())->children[1]);
    EXPECT_EQ(NodeType::L, (static_cast<Node16*>(tree.get_root()))->children[1]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node16*>(tree.get_root()))->children[1]);
    EXPECT_EQ("ab", my_leaf->key);
    EXPECT_EQ("1", my_leaf->value);
    EXPECT_TRUE(static_cast<Node16*>(tree.get_root())->children[2]);
    EXPECT_EQ(NodeType::L, (static_cast<Node16*>(tree.get_root()))->children[2]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node16*>(tree.get_root()))->children[2]);
    EXPECT_EQ("ac", my_leaf->key);
    EXPECT_EQ("2", my_leaf->value);
    EXPECT_TRUE(static_cast<Node16*>(tree.get_root())->children[3]);
    EXPECT_EQ(NodeType::L, (static_cast<Node16*>(tree.get_root()))->children[3]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node16*>(tree.get_root()))->children[3]);
    EXPECT_EQ("ad", my_leaf->key);
    EXPECT_EQ("3", my_leaf->value);
    EXPECT_TRUE(static_cast<Node16*>(tree.get_root())->children[4]);
    EXPECT_EQ(NodeType::L, (static_cast<Node16*>(tree.get_root()))->children[4]->node_type);
    my_leaf = static_cast<Leaf*>((static_cast<Node16*>(tree.get_root()))->children[4]);
    EXPECT_EQ("ae", my_leaf->key);
    EXPECT_EQ("4", my_leaf->value);

    EXPECT_EQ("0", tree.search("a"));
    EXPECT_EQ("1", tree.search("ab"));
    EXPECT_EQ("2", tree.search("ac"));
    EXPECT_EQ("3", tree.search("ad"));
    EXPECT_EQ("4", tree.search("ae"));

}
void check_structure_helper(ART& tree, int node_size, NodeType node_type) ;
TEST(NodeTest, SingleNodeExpansionAll) {
    ART tree;

    for (int i=0;i<4;i++) {
        tree.insert(std::string("a") + static_cast<char>(i), std::to_string(i));
    }

    for (int i=0;i<4;i++) {
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }

    check_structure_helper(tree, 4, NodeType::N4);
    tree.insert(std::string("a") + static_cast<char>(4), std::to_string(4));
    check_structure_helper(tree, 5, NodeType::N16);

    for (int i=0;i<=4;i++) {
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }
    



    for (int i=4;i<16;i++) {
        tree.insert(std::string("a") + static_cast<char>(i), std::to_string(i));
    }

    for (int i=4;i<16;i++) {
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }

    check_structure_helper(tree, 16, NodeType::N16);
    tree.insert(std::string("a") + static_cast<char>(16), std::to_string(16));
    check_structure_helper(tree, 17, NodeType::N48);

    for (int i=0;i<=16;i++) {
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }


    
    for (int i=16;i<48;i++) {
        tree.insert(std::string("a") + static_cast<char>(i), std::to_string(i));
    }

    for (int i=16;i<48;i++) {
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }

    check_structure_helper(tree, 48, NodeType::N48);
    tree.insert(std::string("a") + static_cast<char>(48), std::to_string(48));
    check_structure_helper(tree, 49, NodeType::N256);

    for (int i=0;i<=48;i++) {
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }



    for (int i=48;i<256;i++) {
        tree.insert(std::string("a") + static_cast<char>(i), std::to_string(i));
    }

    check_structure_helper(tree, 256, NodeType::N256);
    for (int i=48;i<256;i++) {
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }
}

void check_structure_helper(ART& tree, int node_size, NodeType node_type) {
    
    
    Leaf* my_leaf;

    EXPECT_TRUE(tree.get_root());
    Node* root = tree.get_root();

    switch (node_type) {
        case NodeType::N4: {
            EXPECT_EQ(NodeType::N4, (static_cast<Node16*>(root))->node_type);
            break;
        }
        case NodeType::N16: {
            EXPECT_EQ(NodeType::N16, (static_cast<Node16*>(root))->node_type);
            break;
        }
        case NodeType::N48: {
            EXPECT_EQ(NodeType::N48, (static_cast<Node16*>(root))->node_type);
            break;
        }
        case NodeType::N256: {
            EXPECT_EQ(NodeType::N256, (static_cast<Node16*>(root))->node_type);
            break;
        }
        default:
            ASSERT_FALSE("unknown NodeType in helper of SingleNodeExpansionAll");
    }
    
    EXPECT_EQ("a", (static_cast<Node16*>(tree.get_root()))->read_prefix());

    for (int i=0;i<node_size;i++) {
        

        switch (node_type) {
            case NodeType::N4: {
                EXPECT_TRUE(static_cast<Node4*>(root)->children[i]);
                EXPECT_EQ(NodeType::L, (static_cast<Node4*>(root))->children[i]->node_type);
                Node4* node = static_cast<Node4*>(root);
                my_leaf = static_cast<Leaf*>(node->children[i]);
                EXPECT_EQ(std::string("a") + static_cast<char>(i), my_leaf->key);
                EXPECT_EQ(std::to_string(i), my_leaf->value);
                break;
            }
            case NodeType::N16: {
                EXPECT_TRUE(static_cast<Node16*>(root)->children[i]);
                EXPECT_EQ(NodeType::L, (static_cast<Node16*>(root))->children[i]->node_type);
                Node16* node = static_cast<Node16*>(root);
                my_leaf = static_cast<Leaf*>(node->children[i]);
                EXPECT_EQ(std::string("a") + static_cast<char>(i), my_leaf->key);
                EXPECT_EQ(std::to_string(i), my_leaf->value);
                break;
            }
            case NodeType::N48: {
                EXPECT_TRUE(static_cast<Node48*>(root)->children[i]);
                EXPECT_EQ(NodeType::L, (static_cast<Node48*>(root))->children[i]->node_type);
                Node48* node = static_cast<Node48*>(root);
                my_leaf = static_cast<Leaf*>(node->children[node->ptr_arr_idx[i]]);
                EXPECT_EQ(std::string("a") + static_cast<char>(i), my_leaf->key);
                EXPECT_EQ(std::to_string(i), my_leaf->value);
                break;
            }
            case NodeType::N256: {
                EXPECT_TRUE(static_cast<Node256*>(root)->children[i]);
                EXPECT_EQ(NodeType::L, (static_cast<Node256*>(root))->children[i]->node_type);
                Node256* node = static_cast<Node256*>(root);
                my_leaf = static_cast<Leaf*>(node->children[i]);
                EXPECT_EQ(std::string("a") + static_cast<char>(i), my_leaf->key);
                EXPECT_EQ(std::to_string(i), my_leaf->value);
                break;
            }
            default:
                ASSERT_FALSE("unknown NodeType in helper of SingleNodeExpansionAll");
        }
        EXPECT_EQ(std::to_string(i), tree.search(std::string("a") + static_cast<char>(i)));
    }
}