#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/*
Uses getchar and putchar to transliterate bytes as described above.
 */
void checkIO(){
  if(ferror(stdin)){
	fprintf(stderr, "Error, reading from stdin.");
	exit(1);
  }
}
typedef char* string;
int main(int argc, char ** argv){
  if(argc!=3){
	fprintf(stderr, "Error, insufficient number of arguments. \n");
	exit(1);
  }
  string from = argv[1];
  string to = argv[2];
  if(strlen(from)!=strlen(to)){
	fprintf(stderr, "Error, argument lengths do not match.\n");
	exit(1);
  }
  int i = 0; 
  int j = 0;
  for(i = 0; i < strlen(from); i++){
	for(j = i+1; j<strlen(from);j++){
	  if(from[i]==from[j]){
		fprintf(stderr, "Error, there are duplicate bytes in 1st argument. \n");
		exit(1);
	  }
	}
  }
  char c;
  c = getchar();
  checkIO();
  while(c!=EOF){
	i = 0;
	for(i=0;i<strlen(from);i++){
	  if(c == from[i]){
		c = to[i];
		break;
	  }
	}
	putchar(c);
	c = getchar();
	checkIO();
  }
  return 0;
  
}
