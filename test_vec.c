#include "includes/vector.h"
#include <stdio.h>

int main(void)
{
	t_xyz	test;
	t_xyz	test2;
	t_xyz	result;

	test = v_create(1,2,3);
	test2 = v_create(3,4,5);
	result = v_cross(test, test2);
	printf("x: %f, cross.x %f\n", test.x, result.x);
}