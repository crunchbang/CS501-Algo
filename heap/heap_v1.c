#include<stdio.h>
#include<math.h>

/*
 *  N : 10^6
 *  k : 10^4
 *  Create a max heap and add the first k elements
 *  Keep adding new elements and removing the max element
 *  Continue until the entire input is read
 *  The current nodes in the heap represents the k smallest elements
 *
 *  Usage:
 *  <exec> <input_file>
 *  Output: 
 *  output_v1.txt
 */

#define N 1000000
#define K 10000


int heap[K+1];
int end = 0;

void add_element(int ele);
int delete_element();
void bottom_up_heapify();
void top_down_heapify(int index);
void init_heap();


int main(int argc, char *argv[])
{
        FILE *ifp = fopen(argv[1], "r");
        FILE *ofp = fopen("output_v1.txt", "w");

        for (int i = 0; i < K; ++i) 
                fscanf(ifp, "%d", &heap[i]);
        init_heap();
        int num;

        /*
        printf("Heap:\n");
        for (int i = 0; i < K; ++i)
                printf("%d ", heap[i]);
        printf("\n");
        */

        while (fscanf(ifp, "%d", &num) != EOF) {
                add_element(num);
                delete_element();
        //        printf("Add %d, delete %d\n", num, delete_element());
        }
        for (int i = 0; i < K; ++i) {
                num = delete_element();
                fprintf(ofp, "%d\n", num);
        }

        return 0;
}

void init_heap()
{
        end = K-1;
        for (int i = K/2; i >= 0; --i)
                top_down_heapify(i);
}

void top_down_heapify(int index)
{
        //printf("Top-Down %d\n", heap[index]);
        int lc = index * 2 + 1;
        int rc = index * 2 + 2;
        int max; 
        //printf("Top-Down %d c %d %d %d %d\n", end, heap[lc], lc, heap[rc], rc);
        if (rc > end && lc > end) {
                return;
        }
        else if (rc > end)
                max = lc;
        else 
                max = heap[lc] > heap[rc] ? lc : rc;
        if (heap[index] < heap[max]) {
        //printf("Top-Down swap %d %d\n", heap[index], heap[max]);
                int t = heap[index];
                heap[index] = heap[max];
                heap[max] = t;
                top_down_heapify(max);
        }
        else 
                return;
}

void bottom_up_heapify(int index)
{
//        printf("Bottom-up %d\n", heap[index]);
        if (index == 0)
                return;
        int parent = ((index - 1)/ 2);
        if (heap[index] > heap[parent]) {
                int t = heap[index];
                heap[index] = heap[parent];
                heap[parent] = t;
                bottom_up_heapify(parent);
        }
        else 
                return;
}

void add_element(int ele)
{
        heap[++end] = ele;
        bottom_up_heapify(end);
}

int delete_element()
{
        int e = heap[0];
        heap[0] = heap[end];
        heap[end] = -1;
        end--;
        top_down_heapify(0);
        return e;
}
