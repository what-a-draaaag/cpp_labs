#include"str.h"
#include "string.h"
#include"assert.h"

void my_strcpy_test()
{
	char destination[] = "Hello";
	char source1[] = "world";
	char source2[] = "";
	char* pd = &destination;
	char* ps1 = &source1;
	char* ps2 = &source2;
	pd = my_strcpy(pd, ps1);
	assert(strcmp(destination,source1) == 0);
	pd = my_strcpy(pd, ps2);
	assert(strcmp(destination,source2) == 0);
}

void my_strlen_test()
{
	char string1[] = "Hello";
	char string2[] = "";
	assert(my_strlen(&string1) == 5);
	assert(my_strlen(&string2) == 0);
}

void my_strcat_test()
{
	char destination[] = "Hello,";
	char source1[] = " world";
	char source2[] = "";
	char result[] = "Hello, world";
	char* pd = &destination;
	char* ps1 = &source1;
	char* ps2 = &source2;
	char* pr = &result;
	pd = my_strcat(pd, ps1);
	assert(strcmp(pd,pr) == 0);
	pd = my_strcat(pd, ps2);
	assert(strcmp(pd,pr) == 0);
}

void my_strcmp_test()
{
	char string1[] = "Hello,";
	char string2[] = " world";
	char string3[] = "";
	char string4[] = "Hello, ";
	char* p1 = &string1;
	char* p2 = &string2;
	char* p3 = &string3;
	char* p4 = &string4;
	assert(my_strcmp(p1,p2)==strcmp(p1,p2));
	assert(my_strcmp(p1,p3)==strcmp(p1,p3));
	assert(my_strcmp(p1,p4)==strcmp(p1,p4));
	assert(my_strcmp(p2,p3)==strcmp(p2,p3));
}