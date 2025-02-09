#include <stdio.h>

int main(){
	char foo = '\033[B\033[1D' ;
	printf("foo=%d",foo);

	return 0;
}
