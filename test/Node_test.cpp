#include "gtest/gtest.h"
#include "../src/ART.hpp"
#define FIRST_CHAR 0


TEST(NodeTest, NodeFunctionalityTest) {
    ART tree;
    
    for (int i=FIRST_CHAR;i<FIRST_CHAR+4;i++) {
        tree.insert(std::string(1, char(i)), std::string(1, char(i)));
        EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
        if (i!=FIRST_CHAR) {
            EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
            EXPECT_EQ(NodeType::N4, (tree.get_root())->node_type);
        } else {
            EXPECT_EQ(NodeType::L, (tree.get_root())->node_type);
        }
    }

    tree.insert(std::string(1, char(FIRST_CHAR+4)), std::string(1, char(FIRST_CHAR+4)));
    EXPECT_EQ(4+1, tree.get_size());
    EXPECT_EQ(4+1, (tree.get_root())->size);
    EXPECT_EQ(NodeType::N16, (tree.get_root())->node_type);

    for (int i=FIRST_CHAR+5;i<FIRST_CHAR+16;i++) {
        tree.insert(std::string(1, char(i)), std::string(1, char(i)));
        EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
        EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
        EXPECT_EQ(NodeType::N16, (tree.get_root())->node_type);
    }

    tree.insert(std::string(1, char(FIRST_CHAR+16)), std::string(1, char(FIRST_CHAR+16)));
    EXPECT_EQ(16+1, (tree.get_root())->size);
    EXPECT_EQ(NodeType::N48, (tree.get_root())->node_type);

    for (int i=FIRST_CHAR+17;i<FIRST_CHAR+48;i++) {
        tree.insert(std::string(1, char(i)), std::string(1, char(i)));
        EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
        EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
        EXPECT_EQ(NodeType::N48, (tree.get_root())->node_type);
    }

    tree.insert(std::string(1, char(FIRST_CHAR+48)), std::string(1, char(FIRST_CHAR+48)));
    EXPECT_EQ(48+1, (tree.get_root())->size);
    EXPECT_EQ(NodeType::N256, (tree.get_root())->node_type);

    for (int i=FIRST_CHAR+49;i<FIRST_CHAR+256;i++) {
        tree.insert(std::string(1, char(i)), std::string(1, char(i)));
        EXPECT_EQ(i-FIRST_CHAR+1, tree.get_size());
        EXPECT_EQ(i-FIRST_CHAR+1, (tree.get_root())->size);
        EXPECT_EQ(NodeType::N256, (tree.get_root())->node_type);
    }





}