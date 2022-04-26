#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <cstdio>
#include <climits>
#include <cstring>
#include <iomanip>
#include <set>
using namespace std;


// block of memory 
struct node {
	int allocated;
	int allocatedSize;
	int size;
	int intFragment;
	int allocatedBlocks;
	struct node* next;
	struct node* prev;
};

// function to create node with size and allocation status 
struct node* createNodeF(int size, int allocationStatus){
	struct node* ptr = (struct node*)malloc(sizeof(struct node));
	ptr->allocated = allocationStatus;
	ptr->allocatedSize = 0;
	ptr->size = size;
	ptr->intFragment = 0;
	ptr->next = NULL;
	ptr->allocatedBlocks = size/8;
	return ptr;
}

// Function to create node / block of memory
struct node* createNode(int size){

	struct node* ptr = (struct node*)malloc(sizeof(struct node));
	if(rand()%2 == 0){
		ptr->allocated = 1;
		ptr->allocatedSize = size;
		ptr->intFragment = 0;
		ptr->allocatedBlocks = size/8;
	}
	else{
		ptr->allocated = 0;
		//ptr->allocatedBlocks = size/8 + 1;
		ptr->allocatedSize = 0;
		ptr->intFragment = 0;
		ptr->allocatedBlocks = size/8;
	}

	ptr->size = size;
	ptr->next = NULL;
	return ptr;

}

// global HEAD of Memory
struct node* HEAD = createNode(32);

struct node* head = HEAD;

struct node* curr;


// Function to create whole memory layout
// Memory block are allocated randomly 
// along with the allocation status is also selected randomly
void createMemory(struct node* head){
	for(int i = 0; i < 20; i++){
		int randomNumber = ((rand()%10)*8);
		if(randomNumber == 0){
			randomNumber = 8;
		}
		struct node* newNode = createNode(randomNumber);
		head->next = newNode;
		head = newNode;	
		
		
	}
}

// Function to print the memory
// Representation 
// [allocation status, memory block size, allocated size, internal fragmentation]
void printMemory(){
	struct node* head = HEAD;
	cout << " a = allocation status , [memory block size, allocated size, no of blocks, internal fragmentation]\n";
	while(head){
		//cout << "[" << head->allocated << "," << head->size  << ","<< head->allocatedSize << "]->";

		cout <<"  a="<< head->allocated << "	[" << head->size << ", " << head->allocatedSize << ", " << head->allocatedBlocks <<", " <<  head->intFragment << "]" <<"\n";
		head = head->next;
	}
	cout << "\n";
}


// Function to perform firstFit Operation
// and split the memory block if required
struct node* firstFit(int size){
	struct node* h = HEAD;
	while(h){
		if(h->allocated == 0 && size <= h->size){
			h->allocated = 1;
			h->allocatedSize = size;
			if(h->allocatedSize + 8 >= h->size){
				h->intFragment = h->size - h->allocatedSize;
				h->allocatedBlocks = h->size/8;

			}
			else if(h->allocatedSize + 8 < h->size){
				int blocks = h->allocatedSize / 8 + 1;
				int newBlockSize = h->size - blocks*8;
				h->size = blocks*8;
				h->allocatedBlocks = blocks;
				h->intFragment = blocks*8 - h->allocatedSize;
				struct node* newBlock = createNodeF(newBlockSize, 0);
				newBlock->next = h->next;
				h->next = newBlock;
				


			}
			break;
		}
		else{
			h = h->next;
		}
	}
	curr = h;
	return h;
}

// Function to perform nextFit operation
// and split the memory block if required
struct node* nextFit(int size){
	//struct node* h = HEAD;
	while(curr){
		if(curr->allocated == 0 && size <= curr->size){
			curr->allocated = 1;
			curr->allocatedSize = size;
			if(curr->allocatedSize + 8 >= curr->size){
				curr->intFragment = curr->size - curr->allocatedSize;
				curr->allocatedBlocks = curr->size/8;

			}
			else if(curr->allocatedSize + 8 < curr->size){
				int blocks = curr->allocatedSize / 8 + 1;
				int newBlockSize = curr->size - blocks*8;
				curr->size = blocks*8;
				curr->intFragment = blocks*8 - curr->allocatedSize;
				curr->allocatedBlocks = blocks;
				struct node* newBlock = createNodeF(newBlockSize, 0);
				newBlock->next = curr->next;
				curr->next = newBlock;

			}
			break;
		}
		else{
			curr = curr->next;
		}
	}
	return curr;

}


// Function to perform bestFit 
// and split the memory if required
struct node* bestFit(int size){
	struct node* temp = HEAD;
	//printf("2\n");
	int minDiff = INT_MAX;
	struct node* t;
	//printf("3\n");
	//printMemory(temp);
	while(temp){
		if(temp->allocated == 0){
			int d = temp->size - size;
			if(d < 0){
				d = minDiff;
			}
			minDiff = min(d, minDiff);
			temp = temp->next;
		}
		else{
			temp = temp->next;
		}
		//printf("inwhile\n");
	}
	//printf("3\n");
	//printf("Here\n");
	struct node* head = HEAD;
	while(head){
		if(head->allocated == 0){
			int d = abs(head->size - size);
			if(d == minDiff){
				head->allocated = 1;
				head->allocatedSize = size;
				if(head->allocatedSize + 8 >= head->size){
					head->intFragment = head->size - head->allocatedSize;
					head->allocatedBlocks = size/8;

				}
				else if(head->allocatedSize + 8 < head->size){
					int blocks = head->allocatedSize / 8 + 1;
					int newBlockSize = head->size - blocks*8;
					head->size = blocks*8;
					head->intFragment = blocks*8 - head->allocatedSize;
					head->allocatedBlocks = blocks;
					struct node* newBlock = createNodeF(newBlockSize, 0);
					newBlock->next = head->next;
					head->next = newBlock;

				}
				break;
			}
			head = head->next;
		}
		else{
			head = head->next;
		}

	}
	return head;
}

// Function to Free Memory and coalesce / merge 
// the unallocated memory block 
void freeMemory(struct node* ptr){
	ptr->allocated = 0;
	ptr->allocatedSize = 0;
	ptr->intFragment = 0;
	struct node* h = HEAD;
	while(h && h->next){
		if(h->allocated == 0 && h->next->allocated == 0){
			h->allocatedBlocks += h->next->allocatedBlocks;
			h->size += h->next->size;
			h->next = h->next->next;
			h = h->next;
		}
		else{
			h = h->next;
		}
	}	

}	


int main(){
	cout << "\nNotation : \n";
	cout << "a = allocation status, [ memory block size, allocated size, no of blocks, internal fragmentation\n\n";
	struct node* head = HEAD;
	createMemory(head);
	cout << "Memory Before any allocation\n";
	printMemory();
	cout << "\nFirst Fit\n";
	struct node* p1 = firstFit(G);
	struct node* p2 = firstFit(44);
	printMemory();
	cout << "\nNext Fit\n";
	struct node* p3 = nextFit(7);
	struct node* p4 = nextFit(18);
	printMemory();
	cout << "\nBest Fit\n";
	struct node* p5 = bestFit(31);
	struct node* p6 = bestFit(15);
	printMemory();
	cout << "\nAfter some blocks of memory are made free\n";
	freeMemory(p1);
	freeMemory(p3);
	freeMemory(p5);
	printMemory();


	return 0;
}
