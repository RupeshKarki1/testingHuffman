#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//to avoid constant
#define ASCII_SIZE 256

#define MAX_TREE_HT 100

struct codeTable
{
    char code[ASCII_SIZE][MAX_TREE_HT];
};


// for nodes to store data
struct nodeData
{
    //for storing characters and frequency in nodes
    char data;
    int freq;

    //left and right pointers to nodeData, gathering info on data and freq
    struct nodeData *left, *right;
};
//shortening the struct name to just a variable
typedef struct nodeData NodeData;

//to hold values of heap 
struct nodeHeap
{
    //number of current node in heap
    unsigned size;

    //total number of node allowed in heap
    unsigned capacity; // this is done for mem allocation and preventing overflow

    //array of pointers storing addresses of nodes
    //for efficient manipulation of data, as array gives more freedom
    // in swapping elements
    NodeData **array;
};
typedef struct nodeHeap NodeHeap;

//function to create new nodes, has pointer to nodedata for its data and freq
NodeData* createNewNode(char data, int freq)
{
    //allocation memory for nodes
    NodeData* temp = (NodeData*) malloc(sizeof(NodeData));

    //clearing values in left and right nodes before putting values
    temp->right = temp->left = NULL;

    //assigning values to nodes as per the given params
    temp->data = data;
    temp->freq = freq;

    return temp;
}

//to assign and allocate mem
NodeHeap* createNodeHeap(unsigned capacity)
{
    //allocate mem and check for failure
    NodeHeap* ptrNodeHeap = (NodeHeap*) malloc(sizeof(NodeHeap));
    if (!ptrNodeHeap)
    {
        printf("mem allocation failed for ptrNodeHeap");
        return NULL; 
    }

    //init size and capacity
    ptrNodeHeap->size = 0;
    ptrNodeHeap->capacity = capacity;

    //allocate mem for array according to NodeData
    ptrNodeHeap->array = (NodeData**)malloc(ptrNodeHeap->capacity * sizeof(NodeData*));
    if (!ptrNodeHeap->array)
    {
        free(ptrNodeHeap);
        return NULL;
    }
    return ptrNodeHeap;
    
}

//swapping function
void swapNodes(NodeData** a, NodeData** b)
{
    //storing address of node in temp and reassigning temp to address of pointer to node(i.e. *a)
    NodeData* temp = *a;

    //penetrate one level and swap the addresses of a and b
    *a = *b;
    *b = temp;
}

//for finding smallest freq between child and parent nodes
void heapify(NodeHeap* nodeheap, int idx)
{
    //initialize smallest as idx
    int smallest = idx; //assume idx as current smallest
    int leftIdx = 2 * idx + 1; // to calculate index of left and right child from root
    int rightIdx = 2 * idx + 2;

    //checking and comparing frequencies
    if (leftIdx < nodeheap->size &&
        nodeheap->array[leftIdx]->freq < nodeheap->array[smallest]->freq)
    {
        //set smallest to left if it is inboundary of size and its freq is lower than 
        // current smallest freq
        smallest = leftIdx;
    }

    if (rightIdx < nodeheap->size &&
        nodeheap->array[rightIdx]->freq < nodeheap->array[smallest]->freq)
    {
        smallest = rightIdx;
    }

    //if the current index is not smallest then swap smallest freq in this cycle and 
    // current idx
    if(smallest != idx)
    {
        swapNodes(&nodeheap->array[smallest], &nodeheap->array[idx]);
        //recursive until the current idx is smallest
        heapify(nodeheap, smallest);
    }
}

int sizeOneCheck(NodeHeap* nodeheap)
{
    return (nodeheap->size == 1);
}

//to extract minimum node from root and add another element, heap sorting
NodeData* extractMin(NodeHeap* nodeheap)
{
    // temp to hold 0th array element or root
    NodeData* temp = nodeheap->array[0];

    //now assigning the root to last element after removing 0th element
    nodeheap->array[0] = nodeheap->array[nodeheap->size-1];

    //adjusting size after removing element
    --nodeheap->size;

    //heapify to restore heap structure of binary tree
    heapify(nodeheap, 0);

    return temp;
}

//function to insert node and keep it in order
void insertNode(NodeHeap* nodeheap, NodeData* nodedata)
{
    //increment the size of array to contain the newly inserted element
    ++nodeheap->size;

    //hold last index of array or the new index as i
    int i = nodeheap->size-1;

    //as long as current node freq is less than its parent node
    while (i && nodedata->freq < nodeheap->array[((i-1)/2)]->freq)
    {
        //swap to maintain minHeap structure
        nodeheap->array[i] = nodeheap->array[(i-1)/2];

        //reconfigure i as we changed the position of new node
        i = (i-1)/2;
    }

    //insert new node in heap array
    nodeheap->array[i] = nodedata;   
}

//to build min heap
void buildMinHeap(NodeHeap* nodeheap)
{
    //variable to hold last idx
    int n = nodeheap->size-1;

    //from last internal node to root(0th element), loop for arranging internal and root 
    //element in order
    for (int i = (n-1)/2; i >= 0; --i)
    {
       heapify(nodeheap, i);
    }    
}

//simple func to print array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
       printf("%d", arr[i]);
    }
    printf("\n");  
}

//to check if the node is leaf or not
int isLeaf(NodeData* leafnode)
{
    return !(leafnode->left) && !(leafnode->right);
}

// creating and building min heap
NodeHeap* buildingHeap(char data[], int freq[], int size)
{
    //make a heap of size as given in parameter
    NodeHeap* nodeheap  = createNodeHeap(size);

    //loop through 0 to size and populate array with new nodes
    for (int i = 0; i < size; i++)
    {
        nodeheap->array[i] = createNewNode(data[i], freq[i]);
    }
    
    //initialize size of heap
    nodeheap->size = size;

    //maintain heap structure of the newly created heap
    buildMinHeap(nodeheap);

    //return the heap
    return nodeheap;   
}

//building huffman tree
NodeData* huffmanTree(char data[], int freq[], int size)
{
    //make left right and top node for heap
    NodeData *left, *right, *top;

    //after making nodes make heap using prev func to arrange
    NodeHeap* nodeheap = buildingHeap(data, freq, size);

    //loop until only root remains 
    while (!sizeOneCheck(nodeheap))
    {
        //extract minimum values from heap and put in left and right in tree
        left = extractMin(nodeheap);
        right = extractMin(nodeheap);

        //add left and right freq and placeholder $ sign for the internal node
        top = createNewNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        //insert the new internal node in heap
        insertNode(nodeheap, top);
    }
    //only one element remains, root, return it
    return extractMin(nodeheap);
}

//function to print code from huffman tree
void printCode(NodeData* root, int arr[], int top) {

    //if root has left child assign 0 and recurse the function
    if (root->left) {
        arr[top] = 0;
        printCode(root->left, arr, top + 1);  // Traverse left, add 0
    }
    if (root->right) {
        arr[top] = 1;
        printCode(root->right, arr, top + 1); // Traverse right, add 1
    }
    
    //check if the root is leaf, if it is print character and array of codes recorded
    if (isLeaf(root)) {
        
        printf("%c: ", root->data);
        printArray(arr, top);  // Print the code when a leaf node is reached    
        
    }
}

//final function to make huffman tree and display codes
void huffmanCode(char data[], int freq[], int size)
{
    NodeData* root = huffmanTree(data, freq, size);

    //100 length max arr for code
    int arr[MAX_TREE_HT];
    int top = 0;

    printCode(root, arr, top);
}
//function to show frequency and characters in console
void printFreq(int arrtoCount[])
{
    for (int i = 0; i < ASCII_SIZE; i++)
    {
        if (arrtoCount[i] > 0)
        {
            if(isprint(i)){

            printf("%c: %d\n", i, arrtoCount[i]);
        }else
        {
            printf("ascii %d: %d\n", i, arrtoCount[i]);
        }
        }
              
    }
               
}

//function to read contents of file and store it in arrays
void fileHandling(char data[], int freq[], int* uniqueChar, const char *filename)
{
    //pointer to file
    FILE *fh;
    char ch;

    //frequency count with the size of 256
    int freqCount[ASCII_SIZE] = {0};

    fh = fopen(filename, "r"); //opens file in read only mode

    //check for empty file
    if (fh == NULL)
    {
        printf("error opening file: %s \n", filename);
        return;
    }
    
    //puts a character and checks if it end of file
    while ((ch = fgetc(fh)) != EOF)
    {
        freqCount[(unsigned char)ch]++; //increment frequency count for ascii value index
    }

    fclose(fh);
    *uniqueChar = 0;

    printFreq(freqCount);

    //loop through 0 to 256 and put unique characters and their freq in arrays
    for (int i = 0; i < ASCII_SIZE; i++)
    {
        //if the index contains freq more than one
        if(freqCount[i] > 0)
        {

            data[*uniqueChar] = (char) i;
            freq[*uniqueChar] = freqCount[i];

            (*uniqueChar)++;         
        }
       
    }
}

int main()
{
   char data[ASCII_SIZE];
   int freq[ASCII_SIZE];

   int uniqueChar = 0;

   fileHandling(data, freq, &uniqueChar, "test.txt");
  
   //if we have unique characters more than one make huffman tree 
   if(uniqueChar > 0)
   {
    huffmanCode(data, freq, uniqueChar);
   }else
   {
        printf("No data found in file.\n");
   }
    
    return 0;
}

