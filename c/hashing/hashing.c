#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11

typedef struct {
    int key;
    int value;
} Item;

typedef struct {
    Item table[TABLE_SIZE];
} Table;

void init_hash_table(Table* table);
int hash(int key);
void insert(Table* hash_table, int key, int value);

void printTable(Table* hash_table);

int main(int argc, char* argv[]) {
    int array[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};

    Table* table = (Table*) malloc(sizeof(Table));

    if (table == NULL) {
        fprintf(stderr, "Failed to allocate memory!\n");
        return 1;
    }

    init_hash_table(table);

    insert(table, 10, 2);
    insert(table, 22, 2);
    insert(table, 31, 2);
    insert(table, 4, 2);
    insert(table, 15, 2);
    insert(table, 28, 2);
    insert(table, 17, 2);
    insert(table, 88, 2);
    insert(table, 59, 2);

    printTable(table);

    free(table);
    return 0;
}

void init_hash_table(Table* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i].key = -1;
        hash_table->table[i].value = 0;
    }
}

int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(Table* hash_table, int key, int value) {
    int index = hash(key);
    int index_tmp = index;
    int i = 0;

    while (hash_table->table[index].key != -1) {
        if (hash_table->table[index].key == key) {
            printf("Updated value in existing entry!\n");
            hash_table->table[index].value = value;
            return;
        }

        // Lineares Probieren (linear probing)
        //i++;
        //index = (index_tmp + i) % TABLE_SIZE;

        // Quadratisches Probieren (quadratic probing)
        //i++;
        //index = (index_tmp + 1*i + 3*i*i) % TABLE_SIZE;

        // Doppeltes Hashing (double hashing)
        int h1 = index;
        int h2 = 1 + (key % (TABLE_SIZE - 1));
        i++;
        index = (h1 + h2) % TABLE_SIZE;

        if (i == TABLE_SIZE) {
            printf("No space left!\n");
            return;
        }
    }

    hash_table->table[index].key = key;
    hash_table->table[index].value = value;
}

void printTable(Table* hash_table) {
    printf("key\tvalue\t\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%i\t%i\t\n", hash_table->table[i].key, hash_table->table[i].value);
    }
}
