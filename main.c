#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include <ctype.h> 

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 

#define ALPHABET_SIZE (26) 
  

#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
    int size;
    char* word;
};

struct TrieTree
{

    struct TrieNode* root;
};


struct TrieNode* getNode(void) 
{ 
    struct TrieNode *pNode = NULL; 
  
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode)); 
    if (pNode)
    { 
        int i;

        pNode->size = 0;
        pNode->word = "";
  
        for (i = 0; i < ALPHABET_SIZE; i++) 
            pNode->children[i] = NULL; 
    } 
  
    return pNode;
}
struct TrieTree* makeTree(void){
    struct TrieTree* pTree = NULL;
    pTree = (struct TrieTree *)malloc(sizeof(struct TrieTree));
    if(pTree){
        pTree->root = getNode();
    }
    return pTree;
}
  

void insert(struct TrieTree *tree, const char *key)
{ 
    int level; 
    int length = strlen(key); 
    int index; 
  
    struct TrieNode *pCrawl = tree->root;
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode();
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    if(pCrawl->size > 0) {
        pCrawl->size++;
    }
    else{
        pCrawl->size++;

        char* buffer;
        buffer = malloc(sizeof (key));
        strcpy(buffer,key);
        pCrawl->word = buffer;

    }
}
  
bool search(struct TrieNode *root, const char *key) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->size > 0); 
} 
bool isLeafNode(struct TrieNode* root) { 
    return root->size > 0; 
} 
void display(struct TrieNode* root, char str[], int level) { 

    if (isLeafNode(root))  { 
        str[level] = '\0'; 
        printf("%s %d\n",str,root->size); 
    } 
  
    int i; 
    for (i = 0; i < ALPHABET_SIZE; i++) { 

        if (root->children[i]) { 
            str[level] = i + 'a'; 
            display(root->children[i], str, level + 1); 
        } 
    } 
}
void displayR(struct TrieNode* root, char str[],int level) { 

    if (isLeafNode(root)) { 
	
        str[level] = '\0'; 
        printf("%s %d\n",str,root->size); 
 
    } 

    int i; 
    for (i = ALPHABET_SIZE-1; i >= 0; i--) { 
        if (root->children[i]) { 
            str[level] = i + 'a'; 
            displayR(root->children[i], str, level + 1); 
        } 
    } 
}
void freeALL(struct TrieNode* root) { 
	if(!root) return;
	for(int i=0;i<ALPHABET_SIZE;i++) {
		freeALL(root->children[i]);
	}
	free(root);
}

int main(int argc, char* argv[]){

    char* word;
    char buffer[256];
    struct TrieTree* t = makeTree();
    
    while(fgets(buffer, 256 , stdin)){

            char * token = strtok(buffer, " ");
            while(token!= NULL){
            word = malloc(strlen(token) + 1);
            strcpy(word,token);
            int i;
            for (i = 0; i < strlen(word); i++)
            {
                if(word[i] >= 'A'|| word[i] <= 'Z'){
                  word[i] = tolower(word[i]); 

                }
                if (word[i] < 'a' || word[i] > 'z'){
                    word[i] = '\0';
                } 
            }
            insert(t,word);
            token = strtok(NULL, " ");
            free(word);
            }
    }
    char str[20];
    if(argc!=2) display(t->root,str,0);
	if(argc==2 && *argv[1]=='r') displayR(t->root,str,0);

	freeALL(t->root);
    free(t);
    return 0;


}
