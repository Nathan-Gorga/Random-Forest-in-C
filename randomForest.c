#include "randomForest.h"
#include "csv_lib.h"




tree_node * createNode(const enum NODE_TYPE type, const int feature_index, const double threshold, const int class_label){

    tree_node * node = (tree_node *)malloc(sizeof(tree_node)); 

    if(node == NULL) return NULL;

    node->type = type;

    node->left = NULL;
    node->right = NULL;

    node->feature_index = feature_index;

    node->threshold = threshold;

    node->label = class_label;

    return node;
}

//count the majority class in a dataset
int majorityClass(int labels[], const int n){
    
    int count1 = 0, count2 = 0;

    for(int i = 0; i < n; i++){

        if(labels[i] == 0) count1++;
        else count2++;
    }

    return (count1 >= count2) ? 0 : 1;

}


double giniImpurity(int labels[], const int n){
    
    if(n == 0) return 0.0f;

    int count1 = 0, count2 = 0;

    for(int i = 0; i < n; i++){

        if(labels[i] == 0) count1++;
        
        else count2++;

    }

    const double p1 = (double)count1 / n;
    const double p2 = (double)count2 / n;

    return 1.0f - (p1 * p1 + p2 * p2);

}

tree_node * buildTree(){

    //we need to figure out the distinction at the root

    //make a super simple tree with only one question

    //do this for all features

    //and look at how it correlates with the label trying to detect

    return NULL;
}

int main(void) {

size_t rows, cols;

    double ** data = getNumericData("./data/iris.csv", &rows, &cols);


    for(int i = 0; i < rows - 1; i++){
        

        for(int j = 0; j < cols ; j++){
            
            
            printf("%f\t", data[i][j]);
    
        }
    
        printf("\n");
    }


    for(int i = 0; i < rows; i++){
    
    
        free(data[i]);
    }

    free(data);

    return 0;

}





