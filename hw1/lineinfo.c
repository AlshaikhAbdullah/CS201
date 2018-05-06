// Abdullah Alshaikh - CS201 
// Homewokr 1 
/* program to help the user to read lines from text file and the shortest and the longest lines 
   and get the length and how many lines will be trancuted 
*/

#include <stdio.h>
#include <string.h>
int main(int argc , char * argv [])
{
	FILE * op;
	char sentance [300]; // temp variable to store line by line linuxlab.cs.pdx.edu
	int len = 0; // to get the length of the lines that read
	int count = 0;
	char largestS [21]; // to get the longest line
	int larLen = 0;
	int i;
	char shortest[20]; // to get the shortrst line 
	int shortLen = 0;
	int j; 
	int lineL = 0;
	int lineS = 0;

		op = fopen(argv [1], "r");

		if (!op)
		{
			printf("ERORR !!! File Not Found.\n");
			return 0;
		}
		while (!feof(op))
		{
		fgets(sentance,300,op);
		count+=1;
		len = strlen(sentance)-1;
		sentance[len] ='\0';
			
			if (len > larLen)//to check if the length is bigger to get the largest sentance
			{
				

				larLen = len; 
					for(i = 0; i < 20; ++i)
					{
						largestS[i] = sentance[i];
					}
					lineL = count;
			
			}
			if(strlen(sentance)-1 > 20 && !feof(op) )// to know how many lines will be trancuted 
			{
						//count +=1;
				printf("*Warning* Line #%d is truncated.\n", count);
					//	count -=1;
			
			}



			if (shortLen-1 > len || shortLen == 0) // to get the shortest line 
			{
				strcpy(shortest,sentance);
				shortLen = strlen(shortest)-1;
				lineS = count;
			}

		}
			count -=1;

			printf("Total number of lines: %d\n",count);
			larLen = strlen(largestS);
			printf("The largest is line %d: \"%s\" (len=%d)\n", lineL, largestS, larLen);
			shortLen = strlen(shortest);
			printf("the shortest is line %d: \"%s\" (len=%d)\n", lineS, shortest, shortLen);

	fclose(op);

 return 0;

}
