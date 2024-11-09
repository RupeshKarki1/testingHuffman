#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HEIGHT 100
#define ASCII_COUNT 256

int frequency[ASCII_COUNT] = {0};
char txtChar[ASCII_COUNT] = {0};

int charCount = 0;

struct minHeapNode
{
    char data;

    unsigned freq;
    struct minHeapNode *leftChild, *rightChild;
};

struct minHeap
{
    unsigned size;
    unsigned capacity;
    struct minHeapNode** array;

};

struct minHeapNode* newNode(char data , unsigned freq)
{
    struct minHeapNode* temp = (struct minHeapNode*) malloc(sizeof(struct minHeapNode));
    temp->leftChild = temp -> rightChild = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;

}

struct minHeap* createMinHeap(unsigned capacity)
{
    struct minHeap* MinHeap  = (struct minHeap*) malloc(sizeof(struct minHeap));

    MinHeap->size = 0;
    MinHeap->capacity = capacity;
    MinHeap->array = (struct minHeapNode**) malloc(MinHeap->capacity * sizeof(struct minHeapNode**));
    return MinHeap;
}   

void swapMinHeapNode(struct minHeapNode** a,
                struct minHeapNode** b)
    
{
    struct minHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct minHeap* MinHeap, int idx)
{
    
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if(left < MinHeap->size 
    && MinHeap->array[left]->freq < MinHeap -> array[smallest]->freq)
    smallest = left;

    if(right < MinHeap->size && MinHeap -> array[right]-> freq 
    < MinHeap -> array[right]-> freq)
    smallest = right;   

    if(smallest != idx)
    {
        swapMinHeapNode(&MinHeap -> array[smallest], &MinHeap -> array[idx]);
        minHeapify(MinHeap, smallest);
    }

}

int isSizeOne(struct minHeap* MinHeap)
{
    return(MinHeap -> size == 1);
}

struct minHeapNode* extractMin(struct minHeap* MinHeap)
{
    struct minHeapNode* temp = MinHeap -> array[0];
    MinHeap -> array[0] = MinHeap->array[MinHeap->size - 1];
    --MinHeap -> size;
    minHeapify(MinHeap, 0);
    return temp;
}
void insertMinHeap(struct minHeap* MinHeap,
struct minHeapNode* MinHeapNode)
{
    ++MinHeap -> size;
    int i = MinHeap->size - 1;

    while (i 
    && MinHeapNode-> freq < MinHeap-> array[(i-1)/2]->freq)
    {
        MinHeap->array[i] = MinHeap->array[(i-1)/2];
        i = (i-1)/2;
    }
    MinHeap->array[i] = MinHeapNode;
    
}

void buildMinHeap(struct minHeap* MinHeap)
{
    int n = MinHeap -> size - 1;
    int i;

    for(i = (n-1)/2; i >= 0; --i)
    {
        minHeapify(MinHeap, i);
    }
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
    
}

int isLeaf(struct minHeapNode* root)
{
    return (!(root->leftChild)&& !(root->rightChild));

}

struct minHeap*  createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct minHeap* MinHeap = createMinHeap(size);
    for(int i = 0; i < size; ++i)
    { 
        MinHeap -> array[i]= newNode(data[i], freq[i]);
    }

    MinHeap -> size  = size;
    buildMinHeap(MinHeap);
    return MinHeap;
}

struct minHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct minHeapNode *left, *right, *top;
    struct minHeap* MinHeap = createAndBuildMinHeap(data , freq, size);
    
    while (!isSizeOne(MinHeap))
    {
        left = extractMin(MinHeap);
        right = extractMin(MinHeap);

        top = newNode('$', left->freq + right->freq);

        top->leftChild = left;
        top->rightChild = right;
        insertMinHeap(MinHeap, top);
    }
    return extractMin(MinHeap);
}

void printCodes(struct minHeapNode* root, int arr[], int top)
{
    if(root->leftChild)
    {
        arr[top] = 0;
        printCodes(root->leftChild, arr, top + 1);
    }
    if(root->rightChild)
    {
        arr[top] = 1;
        printCodes(root->rightChild, arr, top + 1);
    }

    if (isLeaf(root))   
    {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
        
}
void HuffmanCode(char data[], int freq[], int size)
{
    struct minHeapNode* root = buildHuffmanTree(data, freq, size);

    int arr[MAX_TREE_HEIGHT];
    int top = 0;
    printCodes(root, arr, top);
}

int main()
{
   // freqCount();
    
    
    int size = sizeof(txtChar) / sizeof(txtChar[0]);

    HuffmanCode(txtChar, frequency, size);
    
    return 0;
}