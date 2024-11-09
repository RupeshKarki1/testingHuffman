#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 100

// Structure for Huffman Tree Nodes
struct nodeData {
    char data;           // Character
    int freq;            // Frequency of the character
    struct nodeData *left, *right; // Left and right child pointers
};
typedef struct nodeData NodeData;

// Structure for the Min-Heap
struct nodeHeap {
    unsigned size;      // Number of nodes in heap
    unsigned capacity;  // Total number of nodes allowed in heap
    NodeData **array;   // Array of pointers to nodes
};
typedef struct nodeHeap NodeHeap;

// Create new node
NodeData* createNewNode(char data, int freq) {
    NodeData* temp = (NodeData*)malloc(sizeof(NodeData));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// Create and initialize heap
NodeHeap* createNodeHeap(unsigned capacity) {
    NodeHeap* ptrNodeHeap = (NodeHeap*)malloc(sizeof(NodeHeap));
    ptrNodeHeap->size = 0;
    ptrNodeHeap->capacity = capacity;
    ptrNodeHeap->array = (NodeData**)malloc(ptrNodeHeap->capacity * sizeof(NodeData*));
    return ptrNodeHeap;
}

// Swap two nodes in the heap
void swapNodes(NodeData** a, NodeData** b) {
    NodeData* temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain min-heap property
void heapify(NodeHeap* nodeheap, int idx) {
    int smallest = idx;
    int leftIdx = 2 * idx + 1;
    int rightIdx = 2 * idx + 2;

    if (leftIdx < nodeheap->size && nodeheap->array[leftIdx]->freq < nodeheap->array[smallest]->freq)
        smallest = leftIdx;

    if (rightIdx < nodeheap->size && nodeheap->array[rightIdx]->freq < nodeheap->array[smallest]->freq)
        smallest = rightIdx;

    if (smallest != idx) {
        swapNodes(&nodeheap->array[smallest], &nodeheap->array[idx]);
        heapify(nodeheap, smallest);
    }
}

// Extract the minimum node (root) from heap
NodeData* extractMin(NodeHeap* nodeheap) {
    NodeData* temp = nodeheap->array[0];
    nodeheap->array[0] = nodeheap->array[nodeheap->size - 1];
    --nodeheap->size;
    heapify(nodeheap, 0);
    return temp;
}

// Insert node into the heap
void insertNode(NodeHeap* nodeheap, NodeData* nodedata) {
    ++nodeheap->size;
    int i = nodeheap->size - 1;
    while (i && nodedata->freq < nodeheap->array[(i - 1) / 2]->freq) {
        nodeheap->array[i] = nodeheap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    nodeheap->array[i] = nodedata;
}

// Build min-heap from the given data
NodeHeap* buildMinHeap(char data[], int freq[], int size) {
    NodeHeap* nodeheap = createNodeHeap(size);
    for (int i = 0; i < size; i++) {
        nodeheap->array[i] = createNewNode(data[i], freq[i]);
    }
    nodeheap->size = size;
    for (int i = (nodeheap->size - 2) / 2; i >= 0; i--) {
        heapify(nodeheap, i);
    }
    return nodeheap;
}

// Build the Huffman tree
NodeData* huffmanTree(char data[], int freq[], int size) {
    NodeData *left, *right, *top;
    NodeHeap* nodeheap = buildMinHeap(data, freq, size);

    while (nodeheap->size > 1) {
        left = extractMin(nodeheap);
        right = extractMin(nodeheap);
        top = createNewNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertNode(nodeheap, top);
    }

    return extractMin(nodeheap);
}

// Check if a node is a leaf node
int isLeaf(NodeData* leafnode) {
    return !(leafnode->left) && !(leafnode->right);
}

// Print the Huffman codes for characters
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
       printf("%d", arr[i]);
    }
    printf("\n");
}

// Print Huffman code for a given node
void printCode(NodeData* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCode(root->left, arr, top + 1);  // Traverse left, add 0
    }
    if (root->right) {
        arr[top] = 1;
        printCode(root->right, arr, top + 1); // Traverse right, add 1
    }
    
    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArray(arr, top);  // Print the code when a leaf node is reached
    }
}

// Main function to build and print the Huffman code
void huffmanCode(char data[], int freq[], int size) {
    NodeData* root = huffmanTree(data, freq, size);
    int arr[MAX_TREE_HT];
    int top = 0;
    printCode(root, arr, top);  // Call the recursive print function
}

int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    int freq[] = {5, 9, 12, 13, 16};
    int size = sizeof(arr) / sizeof(arr[0]);
    huffmanCode(arr, freq, size);
    return 0;
}
