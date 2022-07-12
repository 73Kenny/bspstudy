#include <stdio.h>

// inline
// __forceinline
// __arrribute__((always_inline))

int add_inline(int);

int main(int argc, char** argv)
{
	int r = add_inline(10);

	printf("r = %d\n", r);

	return 0;
}

inline int add_inline(int n)
{
	int ret = 0;
	for(int i = 0; i < n; i++)
	{
		ret += 1;	
	}

	return ret;
}
