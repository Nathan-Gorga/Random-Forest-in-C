#ifndef RANDOM_FOREST_H
#define RANDOM_FOREST_H

#include "global.h"


enum SPECIES_TYPE{
    NOT_IRIS = -1,
    SETOSA,
    VERSICOLOR,
    VIRIGINICA,
    NUM_SPECIES_TYPE
};

enum NODE_TYPE{
    ROOT,
    BRANCH,
    LEAF
};



typedef struct {
    double value;
    int label;
} sample;


typedef struct tree_node {

    enum NODE_TYPE type;    

    struct tree_node *left;
    struct tree_node *right;

    int feature_index;

    double threshold;

    enum SPECIES_TYPE label;

} tree_node;


typedef struct{

    size_t size;
    size_t max_depth;

    tree_node ** forest;

} random_forest;



#endif