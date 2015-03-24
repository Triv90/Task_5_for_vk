#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prime close to 10 000
#define HASH_TABLE_SIZE 99971
#define PRIME_FOR_HASH 97
#define SMALLEST_ASCII_CODE 32
#define MAX_STRING_SIZE 1000000

typedef struct hash_elem_s {
	char *value;
	struct hash_elem_s *next;
} hash_elem_t;

int get_hash(char *str) {
	int n = strlen(str), i;
	unsigned int p = 1, res = 0;
	for (i = 0; i < n; ++i) {
		res += (str[i] - SMALLEST_ASCII_CODE + 1)*p;
		p = (p * PRIME_FOR_HASH);
	}
	return res % HASH_TABLE_SIZE;
}
	
void add_element(hash_elem_t** hashTable, char *str) {
	int key = get_hash(str); 
	hash_elem_t *el = malloc(sizeof(hash_elem_t));
	el->value = malloc(strlen(str));
	strcpy(el->value, str);
	el->next = NULL;
	if(hashTable[key] == NULL) {
		hashTable[key] = el;
		return;
	}
	hash_elem_t *iter = hashTable[key];
	while (iter->next != NULL) iter = iter->next;
	iter->next = el;
}

int check_element(hash_elem_t** hashTable, char *str) {
	 int key = get_hash(str);
	 hash_elem_t *iter = hashTable[key];
	 while (iter != NULL) {
		 if (strcmp(iter->value, str) == 0) return 1;
	   iter = iter->next;
	 }
	 return 0;
}

void clear_hash_table(hash_elem_t** hashTable) {
	int i;
	for (i = 0; i < HASH_TABLE_SIZE; ++i) {
		hash_elem_t *cur = hashTable[i];
		hash_elem_t *next;
		while(cur != NULL) {
			next = cur->next;
			free(cur->value);
			free(cur);
			cur = next;
		}
	}
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Please input filename. Exiting...\n");
		return -1;
	}
	FILE *f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("Error while opening file");
	}
	int i;
	hash_elem_t* hashTable[HASH_TABLE_SIZE];
	for (i = 0; i < HASH_TABLE_SIZE; ++i) {
		hashTable[i] = NULL;
	}
	char s[MAX_STRING_SIZE];
	while (!feof(f)) {
		fgets(s, MAX_STRING_SIZE, f);
		int n = strlen(s);
		if (s[n-1] == '\n') s[n-1] = '\0';
		add_element(hashTable, s);
	}

	fgets(s, MAX_STRING_SIZE, stdin);
	int n = strlen(s);
	if (s[n-1] == '\n') s[n-1] = '\0';
	while(strcmp("exit", s) != 0) {
		if (check_element(hashTable, s)) printf("YES\n");
		else printf("NO\n");
		fgets(s, MAX_STRING_SIZE, stdin);
		n = strlen(s);
		if (s[n-1] == '\n') s[n-1] = '\0';
	}
	clear_hash_table(hashTable);
  fclose(f);
	return 0;
}



