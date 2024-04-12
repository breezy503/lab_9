#include <stdio.h>
#include <stdlib.h>


// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

typedef struct Node 
{
    struct RecordType record;
    struct Node* next;
} Node;

// Fill out this structure
struct HashType
{
	Node* buckets[23];
};

// Compute the hash function
int hash(int x)
{
	return x % 23;
}

void initHashTable(struct HashType* hashTable) {
    for (int i = 0; i < 23; ++i) {
        hashTable->buckets[i] = NULL;
    }
}

void insertRecord(struct HashType* hashTable, struct RecordType* record) {
    int index = hash(record->id);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    newNode->record = *record;
    newNode->next = hashTable->buckets[index];
    hashTable->buckets[index] = newNode;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* hashTable) {
    for (int i = 0; i < 23; ++i) {
        Node* current = hashTable->buckets[i];
        if (current != NULL) {
            printf("Index %d -> ", i);
            while (current != NULL) {
                printf("%d, %c, %d -> ", current->record.id, current->record.name, current->record.order);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

int main(void)
{
	struct HashType hashTable;
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	for (int i = 0; i < recordSz; i++) {
        insertRecord(&hashTable, &pRecords[i]);
    }
	displayRecordsInHash(&hashTable);

    return 0;
}