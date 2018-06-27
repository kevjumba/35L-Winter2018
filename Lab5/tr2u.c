#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
/*
Uses getchar and putchar to transliterate bytes as described above.
 */

typedef char* string;
int main(int argc, char ** argv){
  if(argc!=3){
	fprintf(stderr, "Error, insufficient number of arguments.");
	exit(1);
  }
  string from = argv[1];
  string to = argv[2];
  if(strlen(from)!=strlen(to)){
	fprintf(stderr, "Error, argument length do not match.");
	exit(1);
  }
  size_t i = 0; 
  size_t j = 0;
  for(i = 0; i < strlen(from); i++){
	for(j = i+1; j<strlen(from);j++){
	  if(from[i]==from[j]){
		fprintf(stderr, "Error, there are duplicate bytes in 1st argument.");
		exit(1);
	  }
	}
  }
  char c;
  ssize_t status = read(STDIN_FILENO, &c, 1);
  while(status>0){
	int i = 0;
	for(i=0;i<strlen(from);i++){
	  if(c == from[i]){
		c = to[i];
		break;
	  }
	}
	write(STDOUT_FILENO, &c, 1);
	status = read(STDIN_FILENO, &c, 1);
  }
  return 0;
  
}
