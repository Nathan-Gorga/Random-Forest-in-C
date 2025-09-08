#include "randomForest.h"
#include "csv_lib.h"


int cmpfunc(const void * a, const void * b){
    const float fa = ((sample *)a)->value;
    const float fb = ((sample *)b)->value;
    
    if(fa < fb) return -1;
    else if (fa > fb) return 1;
    else return 0;

}

float giniImpurity(int * class_counts, const int total, const int n_classes){
    if(total == 0) return 0.0f;
    float gini = 1.0f;
    for(int i = 0; i < n_classes; i++){
        float p = (float)class_counts[i]/total;
        gini -= p * p;
    }

    return gini;

}


float bestThreshold(double *x, int *y, const int n_samples, const int n_classes, float * best_gini){
    sample * samples = malloc(n_samples * sizeof(sample));
    for(int i = 0; i < n_samples; i++){
        samples[i].value = x[i];
        samples[i].label = y[i];
    }

    qsort(samples, n_samples, sizeof(sample), cmpfunc);

    int * left_counts = calloc(n_classes, sizeof(int));
    int * right_counts = calloc(n_classes, sizeof(int));

    for(int i = 0; i < n_samples; i++){

        right_counts[samples[i].label]++;
    }

    int left_total = 0;
    int right_total = n_samples;

    float best_tresh = samples[0].value;
    *best_gini = FLT_MAX;

    for(int i = 0; i < n_samples - 1; i++){
        
        
        int cls = samples[i].label;
        left_counts[cls]++;
        right_counts[cls]--;
        left_total++;
        right_total--;


        if(samples[i].label != samples[i + 1].label){
            float threshold = (samples[i].value + samples[i+1].value) / 2.0f;

            float gini_left = giniImpurity(left_counts, left_total, n_classes);
            float gini_right = giniImpurity(right_counts, right_total, n_classes);
            float weighted_gini = (left_total * gini_left + right_total * gini_right) / n_samples;

            if(weighted_gini < *best_gini){
                *best_gini = weighted_gini;
                best_tresh = threshold;
            }

        }

    }

    free(samples);
    free(left_counts);
    free(right_counts);
    return best_tresh;

}




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

tree_node * buildTree(double ** data, const size_t rows, const size_t cols){

    //we need to figure out the distinction at the root

    //make a super simple tree with only one question

    //do this for all features

    //and look at how it correlates with the label trying to detect

    return NULL;
}

int main(void) {

    // size_t rows, cols;

    // double ** data = getNumericData("./data/iris.csv", &rows, &cols);

    // for(int i = 0; i < rows - 1; i++){

    //     for(int j = 0; j < cols ; j++){
            
    //         printf("%f\t", data[i][j]);
    
    //     }
    
    //     printf("\n");
    // }


    // for(int i = 0; i < rows; i++){
    
    
    //     free(data[i]);
    // }

    // free(data);

    double x[] = {1.0, 1.2, 4.7, 4.5, 5.0};
    int y[] = {0, 0, 1 ,1 ,2};
    int n_samples = 5;
    int n_classes = 3;

    float best_gini;
    float threshold = bestThreshold(x, y, n_samples, n_classes, &best_gini);

    printf("Best threshold : %f, gini : %f\n", threshold, best_gini);

    return 0;

}





