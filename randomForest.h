#ifndef RANDOM_FOREST_H
#define RANDOM_FOREST_H

#include "global.h"


enum SPECIES_TYPE{
    UNKNOWN = -1,
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
    float value;
    int label;
} sample;


typedef struct tree_node {

    enum NODE_TYPE type;    

    struct tree_node *left;
    struct tree_node *right;

    int feature_index;

    double threshold;

    int label;

} tree_node;


#endif