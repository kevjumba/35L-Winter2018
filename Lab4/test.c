#include "stdio.h"

int add(int a, int b){
  return a+b;
}

void main(){
  int a =5, b = 10, c;
  c = add(a, b);
  int *ptr = NULL;
  printf("%d", *ptr);
  c= 19;
  printf("%d", c);
}
