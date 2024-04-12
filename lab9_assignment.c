#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
};

// Node for linked list in HashType
struct ListNode {
    struct RecordType data;
    struct ListNode* next;
};

// HashType structure
struct HashType {
    struct ListNode** array;
    int size;
};

// Create a new ListNode
struct ListNode* newListNode(struct RecordType data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Compute the hash function
int hash(int x, int hashSize) {
    return x % hashSize;
}

// Function to insert a record into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType data) {
    int index = hash(data.id, hashTable->size);
    struct ListNode* newNode = newListNode(data);
    newNode->next = hashTable->array[index];
    hashTable->array[index] = newNode;
}

// Function to display records in the hash table
void displayRecordsInHash(struct HashType *hashTable) {
    printf("\nHash Table:\n");
    for (int i = 0; i < hashTable->size; ++i) {
        struct ListNode* node = hashTable->array[i];
        if (node != NULL) {
            printf("Index %d -> ", i);
            while (node != NULL) {
                printf("%d %c %d -> ", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

// Your existing code for parsing data and printing records...

int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;
    const int hashSz = 10; // Define the size of the hash table

    // Parse data from the file
    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize hash table
    struct HashType hashTable;
    hashTable.size = hashSz;
    hashTable.array = (struct ListNode**)malloc(hashSz * sizeof(struct ListNode*));
    for (int i = 0; i < hashSz; ++i) {
        hashTable.array[i] = NULL;
    }

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i) {
        insertRecord(&hashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(&hashTable);

    // Free allocated memory (not shown for brevity)
    // ...

    return 0;
}