#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "unistd.h"
#include <sys/stat.h>
#include "limits.h"
/*
Use your C function to write a program sfrob that reads frobnicated text lines from standard input, and writes a sorted version to standard output in frobnicated form. Frobnicated text lines consist of a series of non-space bytes followed by a single space; the spaces represent newlines in the original text. Your program should do all the sorting work itself, by calling frobcmp. If standard input ends in a partial record that does not have a trailing space, your program should behave as if a space were appended to the input.

Use <stdio.h> functions to do I/O. Use malloc, realloc and free to allocate enough storage to hold all the input, and use qsort to sort the data. Do not assume that the input file is not growing: some other process may be appending to it while you're reading, and your program should continue to read until it reaches end of file. For example, your program should work on the file /proc/self/maps, a "file" that is constantly mutating: it always appears to be of size 0 when you ls it, but it always contains nonempty contents if you read it. You should make sure your program works on empty files, as well as on files that are relatively large, such as /usr/local/cs/jdk/jre/lib/rt.jar on SEASnet.

If the program encounters an error of any kind (including input, output or memory allocation failures, it should report the error to stderr and exit with status 1; otherwise, the program should succeed and exit with status 0. The program need not report stderr output errors.
*/
int noCase = 0;

char decode(char c){
  if(noCase){
	if(CHAR_MIN <= c && CHAR_MAX>=c)
	  c = toupper(c);
  }
  return c^42; //bitwise OR operator with 42 to defrobnicate character
}

int frobcmp(char const * a, char const * b){
  for(; ; a++, b++){
    if(*a == ' ' && *b == ' ') return 0;
    if(*a == ' ' || decode(*a) < decode(*b)) return -1;
    if(*b == ' ' || decode(*a) > decode(*b)) return 1;
  }
  
}
void checkIO(ssize_t status){
  if(status < 0){
    fprintf(stderr, "Error, can't read from stdin");
    exit(1);
  }
}

int compare(const void * c1, const void * c2){
  return frobcmp(*(const char **) c1, *(const char **) c2);
}

typedef char * string;

int main(int argc, char *argv[])
{
  if (argc >= 2)
    if ((strncmp(argv[1], "-f"))==0)
      noCase = 1;
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
  ssize_t status = read(STDIN_FILENO, &c, 1);
  checkIO(status);
  char last = c;
  while(status > 0){
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
	status = read(STDIN_FILENO, &c, 1);
    checkIO(status);
    if(status<=0){
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
		status = read(STDIN_FILENO, &c, 1);
		checkIO(status);
	  }
	  numChars = 0;
	  }
  }
  qsort(words, numWords, sizeof(string), compare);
  int i;
  int j;
  i = 0; 
  j = 0;
  for(i = 0; i < numWords; i++){
    for(j = 0; ; j++){
      if(words[i][j]=='\0'){
		break;
      }
	  else if(words[i][j]==' '){
		status = write(STDOUT_FILENO, &words[i][j], 1);
		checkIO(status);
		break;
	  }
	  else{
		status = write(STDOUT_FILENO, &words[i][j], 1);
	  }
    }
	char temp = ' ';
	status = write(STDOUT_FILENO, &temp, 1); 
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
