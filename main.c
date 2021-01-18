#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include <ctype.h>


// define character size
#define CHAR_SIZE 26

//A Trie node
struct Trie{
	int isLeaf;	// marks the node as leaf for the value of 1.
	struct Trie* character[CHAR_SIZE];
	int count;
    bool EndWord; 
};
//Returns new trie node
struct Trie* getNode(){

	struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	//check the node 
	if(node){
		//mark the node
		node->isLeaf = 0;
		node->EndWord = false;
		for (int i = 0; i < CHAR_SIZE; i++){
			node->character[i] = NULL;
		}
	}
	return node;
}
//Inserts the word to the trie tree
void insert(struct Trie *head, char* str){
	//Starts from root node of the trie.
	struct Trie* currentNode = head;
	while (*str){
		//if path doesn't exists we create a new node 
		if (currentNode->character[*str - 'a'] == NULL){
			currentNode->character[*str - 'a'] = getNode();
		}
		//get the next node by indexs of the string
		currentNode = currentNode->character[*str - 'a'];
		//move to next character in string
		str++;
	}
	//mark current node as a leaf and as the end of word.
	currentNode->isLeaf = 1;
	currentNode->EndWord = true;
	//increasing the occurrences amount of the word.
	currentNode->count += 1;

}
//Searches for the string in Trie. If the word exists in the Trie return true,  
//else returns false.
int search(struct Trie* head, char* str){
	// if the head of the Trie is null return false
	if (head == NULL){
		return 0;
	}
	struct Trie* curr = head;
	while (*str){
		// iterates over the word
		curr = curr->character[*str - 'a'];
		// if the next character is null (reached end of path in Trie)
		if (curr == NULL){
			return 0;
		}	
		//next character of the word
		str++;
	}
	// if we reached the last character of the word, return if it's marked as an EndWord.
	return curr->isLeaf;
}
//free memory and deletes the trie.
void freeMemory(struct Trie* head) { 
	if(!head) {
		return;
	}
	for(int i = 0; i < CHAR_SIZE; i++) {
		freeMemory(head->character[i]);
	}
	free(head);
}
//prints the trie words with number of occurrences of each word.
void printNormalTrie(struct Trie* head, char str[], int j) { 
    //if node is end of word we print the word and the count times
    if (head->EndWord != false)  { 
        str[j] = '\0'; 
        printf("%s %d\n",str,head->count); 
    } 
	//recursive call to printNormalTrie function according to each word.
    for (int i = 0; i < CHAR_SIZE; i++) { 
        if (head->character[i]) { 
            str[j] = i + 'a'; 
            printNormalTrie(head->character[i], str, j + 1); 
        } 
    } 
} 
//prints the trie in reverse with the count of each word.
void printReversTrie(struct Trie* head, char str[],int j) { 
    //if node is the end of the word, we print the word and number of occurrences.
    if (head->EndWord != false) { 
        str[j] = '\0'; 
        printf("%s %d\n",str,head->count); 
    } 
	//recursive call to printReversTrie function according to each word.
    for (int i = CHAR_SIZE-1; i >= 0; i--) { 
        if (head->character[i]) { 
            str[j] = i + 'a'; 
            printReversTrie(head->character[i], str, j + 1); 
        } 
    } 
} 
//checks if a node has any children.
int existChildren(struct Trie* curr){
	for (int i = 0; i < CHAR_SIZE; i++)
		if (curr->character[i]){
			return 1;
		}
	return 0;
}
//deletes a string in Trie if it exists and returns true, else returns false.
bool deletion(struct Trie **curr, char* str){
	//if the trie is empty no deletion can happen. 
	if (*curr == NULL)
		return false;
	//if we didn't reach a leaf yet of the string.
	if (*str){
		if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL && deletion(&((*curr)->character[*str - 'a']), str + 1)  == true&& (*curr)->isLeaf == 0){
			if (!existChildren(*curr)){
				free(*curr);
				(*curr) = NULL;
				return true;
			}
			else {
				return false;
			}
		}
	}
	// reached the 'leaf' marking it as the end of the word.
	if (*str == '\0' && (*curr)->isLeaf){
		// if current node is a leaf node and don't have any children
		if (!existChildren(*curr)){
			free(*curr); // delete current node
			(*curr) = NULL;
			return true; // delete non-leaf parent nodes
		}
		// if current node is a leaf node and have children
		else{
			// marks the current node as not a leaf.
			(*curr)->isLeaf = 0;
			(*curr)->EndWord = false;
			return false;
		}
	}

	return false;
}

int main(int argc, char* argv[]){
    char* word;
    char buffer[256];
    struct Trie* t = getNode();
    
    while(fgets(buffer, 256 , stdin)){

            char * token = strtok(buffer, " ");
            while(token!= NULL){
            word = malloc(strlen(token) + 1);
            strcpy(word,token);
            for (int i = 0; i < strlen(word); i++){
                if(word[i] < 'a' || word[i] > 'z'){
                   word[i] = '\0';
                }else if (word[i] >= 'A' && word[i] <= 'Z'){
					word[i] = tolower(word[i]);
                    
                } 
            }
            insert(t,word);
            token = strtok(NULL, " ");
            free(word);
            }
    }
    char str[20];
    if(argc == 1){
		printNormalTrie(t,str,0);
	}else if(argc == 2 && *argv[1] == 'r'){
		printReversTrie(t,str,0);
	} else{
		printf("Error");
	}

	freeMemory(t);
    return 0;
}