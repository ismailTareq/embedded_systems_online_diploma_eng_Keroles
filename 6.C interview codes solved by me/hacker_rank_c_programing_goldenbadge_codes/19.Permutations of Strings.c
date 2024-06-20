#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    int i,j;
    i = n-1;
    while(i>0 && strcmp(s[i-1],s[i])>=0)
    {
        i--;//key
    }
    if(i<=0)
        return 0;
    j=n-1;
    while(j>0 && strcmp(s[i-1],s[j])>=0)
    {
        j--;//rightmost successor to key
    }
    char *temp = s[i-1];
    s[i-1] = s[j];
    s[j] = temp;

    j = n-1;
    while(i<j)
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
    return 1;
}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
