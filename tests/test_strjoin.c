#include "../includes/srcs.h"

int main()
{
	char *test1 = strjoin("hello ", "world");
    assert(strcmp(test1, "hello world") == 0);
    free(test1);

    char *test2 = strjoin("", "world");
    assert(strcmp(test2, "world") == 0);
    free(test2);

    char *test3 = strjoin("hello ", "");
    assert(strcmp(test3, "hello ") == 0);
    free(test3);

    char *test4 = strjoin("", "");
    assert(strcmp(test4, "") == 0);
    free(test4);

    char *test5 = strjoin("hello", " ");
    assert(strcmp(test5, "hello ") == 0);
    free(test5);

	// A NULL paramter should be checked before calling strjoin
	// char *test6 = strjoin(NULL, "world");
    // assert(strcmp(test6, "world") == 0);

    // char *test7 = strjoin("hello", NULL);
    // assert(strcmp(test7, "hello") == 0);

    // char *test8 = strjoin(NULL, NULL);
    // assert(test8 == NULL);
    return 0;
}

