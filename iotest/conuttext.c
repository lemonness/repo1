#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>

void main(int argc, char *argv[])
{
	int c ,i ,nwrite,nother;
	int num[10];

	nwrite=nother=0;
	for ( i = 0; i < 10; i++)
		num[i]=0;
	while((c=getchar())!=EOF){
		if(c>='0'&&c<='9'){
			++num[c-'0'];
		}
		else if (c==' '|| c=='\n'||c=='\t')
			++nwrite;
		else
			++nother;
	}
	printf("digits=");
	for ( i = 0; i < 10; i++)
		printf("%d",num[i]);
	printf(",nwrite=%d,nother=%d\n",nwrite,nother);


}


	// int c, i, nwhite, nother;
	// int ndigit[10];
	// nwhite = nother = 0;
	// for (i = 0; i < 10; ++i)
	// 	ndigit[i] = 0;
	// while ((c = getchar()) != EOF)
	// 	if (c >= '0' && c <= '9')
	// 		++ndigit[c - '0'];
	// 	else if (c == ' ' || c == '\n' || c == '\t')
	// 		++nwhite;
	// 	else
	// 		++nother;
	// printf("digits =");
	// for (i = 0; i < 10; ++i)
	// 	printf(" %d", ndigit[i]);
	// printf(", white space = %d, other = %d\n",
	// 	   nwhite, nother);