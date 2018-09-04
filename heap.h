
struct Pair {
  int key;
  char* value;
};

typedef struct Pair Pair;

struct Heap {
  int capacity;
  int size;
  Pair* elements;
};

typedef struct Heap Heap;

Heap* makeHeap(int capacity);
void add(Heap* heap, int priority, char* value);
char* removeMin(Heap* heap);
char* peek(Heap* heap);
int size(Heap* heap);
void cleanupHeap(Heap* h);
_Bool hasLeft(Heap* h, int index);
_Bool hasRight(Heap* h, int index);
