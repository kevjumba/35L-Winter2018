#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

char decode(char c){
  return c^42; //bitwise OR operator with 42 to defrobnicate character
}

int frobcmp(char const * a, char const * b){
  for(; ; a++, b++){
    if(*a == ' ' || *b == ' ') return 0;
    if(*a == ' ' || decode(*a) < decode(*b)) return -1;
    if(*b == ' ' || decode(*a) > decode(*b)) return 1;
  }
  
}
void checkIO(){
  if(ferror(stdin)){
    fprintf(stderr, "Error, can't read from stdin");
    exit(1);
  }
}

int compare(const void * c1, const void * c2){
  return frobcmp(*(const char **) c1, *(const char **) c2);
}

typedef char * string;

int main()
{
  string word;
  string * words;
  int numWords = 0;
  int numChars = 0;
  word = (string)malloc(sizeof(char)); //initialize empty string
  words = (string *)malloc(sizeof(string));
  if(word == NULL || words == NULL){
    fprintf(stderr, "Error: Memory allocation failed.");
  }
  char c;
  c = getchar();
  checkIO();
  char last = c;
  while(1){
    if(feof(stdin) || ferror(stdin)){
      break;
    }
    if(c == ' ' && numChars >= 1){
	  word[numChars]='\0';
      words[numWords] = word;
      string * temp = realloc(words, (numWords+2)*sizeof(string));
      if(temp != NULL){
		words = temp;
		numWords++;
		word = (char*)malloc(sizeof(char));
		numChars = 0;
      }
      else{
		free(word);
		fprintf(stderr, "Error: Memory allocation failed.");
		exit(1);
      }
    }
    else{
      word[numChars] = c;
      string temp = realloc(word, (numChars+2)*sizeof(char)); //allocate for another character + nullbyte
      if(temp != NULL){
		word = temp;
		numChars++;
      }
      else{
		free(words);
		fprintf(stderr, "Error: Memory allocation failed.");
		exit(1);
      }
            
    }
    last = c;
    c = getchar();
    checkIO();
    if(c == EOF || feof(stdin)){
      if (last == ' '){
		break;
      }
      else if(numChars>=1){
		words[numWords] = word;
		string * temp = realloc(words, (numWords+2)*sizeof(string));
		if(temp != NULL){
		  words = temp;
		  numWords++;
		  word = (char*)malloc(sizeof(char));
		  numChars = 0;
		}
		else{
   		  free(words);
		  fprintf(stderr, "Error: Memory allocation failed.");
		  exit(1);
		}
		break;
      }
    }
   
	else if(c == ' '  && last == ' '){
	  while(c == ' '){
		c = getchar();
		checkIO();
	  }
	  numChars = 0;
	  }
  }
  qsort(words, numWords, sizeof(string), compare);
  int i, j;
  i, j = 0,0;
  for(i = 0; i < numWords; i++){
    for(j = 0; ; j++){
      if(words[i][j]=='\0'){
		break;
      }
	  else if(words[i][j]==' '){
		putchar(words[i][j]);
		break;
	  }
	  else{
		putchar(words[i][j]);
	  }
    }
    putchar(' ');
  }
  i=0;
  for(i = 0; i< numWords; i++){
    free(words[i]);
  }
  free(words);
  exit(0);
}

/*
void qsort (void* base, size_t num, size_t size, 
            int (*comparator)(const void*,const void*));
*/
