#include "randomForest.h"
#include "csv_lib.h"


int cmpfunc(const void * a, const void * b){
    const double fa = ((sample *)a)->value;
    const double fb = ((sample *)b)->value;
    
    if(fa < fb) return -1;
    else if (fa > fb) return 1;
    else return 0;

}

double giniImpurity(int * class_counts, const int total, const int n_classes){
    if(total == 0) return 0.0f;
    double gini = 1.0f;
    for(int i = 0; i < n_classes; i++){
        double p = (double)class_counts[i]/total;
        gini -= p * p;
    }

    return gini;

}


double bestThreshold(double *x, int *y, const int n_samples, const int n_classes, double * best_gini){
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

    double best_tresh = samples[0].value;
    *best_gini = FLT_MAX;

    for(int i = 0; i < n_samples - 1; i++){
        
        
        int cls = samples[i].label;
        left_counts[cls]++;
        right_counts[cls]--;
        left_total++;
        right_total--;


        if(samples[i].label != samples[i + 1].label){
            double threshold = (samples[i].value + samples[i+1].value) / 2.0f;

            double gini_left = giniImpurity(left_counts, left_total, n_classes);
            double gini_right = giniImpurity(right_counts, right_total, n_classes);
            double weighted_gini = (left_total * gini_left + right_total * gini_right) / n_samples;

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


int arrmin(double arr[], const int size){
    double min = arr[0];
    int idx = 0;

    for(int i = 1; i < size; i++){
        if(arr[i] < min){
            min = arr[i];
            idx = i;
        }
    }

    return idx;
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


void printNode(tree_node * n){
    printf("type : %d\n", n->type);
    printf("left : %p\n", n->left);
    printf("right : %p\n", n->right);
    printf("feature idx : %d\n", n->feature_index);
    printf("threshold : %f\n", n->threshold);
    printf("label : %d\n", n->label);
}



tree_node * buildTree(double ** data, const size_t rows, const size_t cols){

    tree_node * root = NULL;

    //separate data by column features
    double ** column_data = malloc((cols-1) * sizeof(double *));

    if(!column_data) return NULL;

    int  * label_data = malloc(rows * sizeof(int));

    if(!label_data) goto column;

    for(int i = 0; i < cols - 1 ; i++){

        column_data[i] = malloc(rows * sizeof(double));

        if(!column_data[i]){
            for(int j = 0; j < i; j++) free(column_data[j]);
            
            goto label_data;
        }


        for(int j = 0; j < rows; j++){
            column_data[i][j] = data[j][i];
        }
    }

    for(int i = 0; i < rows; i++){
        label_data[i] = (int)data[i][cols-1];
    }


    //calculate the best gini index by feature
    const int n_samples = rows, n_classes = NUM_SPECIES_TYPE;

    double * best_gini = malloc((cols-1) * sizeof(double));

    if(!best_gini) goto col;

    double * threshold = malloc((cols-1) * sizeof(double));

    if(!threshold) goto gini;
  

    for(int i = 0; i < cols - 1; i++){
        threshold[i] = bestThreshold(column_data[i], label_data, n_samples, n_classes, &best_gini[i]);
        printf("for feature %d, threshold is %f with gini : %f\n", i, threshold[i], best_gini[i]);
    }

    //create root node using this feature with threshold

    const int best_feature = arrmin(best_gini, cols - 1);
    const double best_threshold = threshold[best_feature];

    root = createNode(ROOT, best_feature, best_threshold, -1); 

    free(threshold);


gini:

    free(best_gini);

col:

    for(int i = 0; i < cols - 1; i++){
    
        free(column_data[i]);

    }

label_data:

    free(label_data);

column:

    free(column_data);

    return root;
}

int main(void) { //PROTOCOL FOR BUILDING A DECISION TREE

    size_t rows, cols;
    
    //extract data from CSV file
    double ** data = getNumericData("./data/iris.csv", &rows, &cols);

    tree_node * root = buildTree(data, rows, cols);

    if(!root) return 1;

    printNode(root);

    free(root);

    for(int i = 0; i < rows; i++){
    
        free(data[i]);

    }

    free(data);


    return 0;

}





