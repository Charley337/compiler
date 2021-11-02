#ifndef __FLEX_BUFFER__H__
#define __FLEX_BUFFER__H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_PAGE 1024

class FlexBuffer {
public:
    char *buf;
    int page_num;
    int size;
    int nextfree;
    int p;

    FlexBuffer();

    void insert(char ch);

    void self_delete();

    char* get_line();

private:
};

#endif