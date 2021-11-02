#include "flex_buffer.h"

FlexBuffer::FlexBuffer() {
    page_num = 1;
    size = page_num * BUFFER_PAGE;
    buf = (char*)malloc(sizeof(char) * size);
    buf[0] = '\0';
    nextfree = 1;
    p = 0;
}

void FlexBuffer::insert(char ch) {
    if (nextfree >= size) {     // 数组爆了
        page_num++;
        size = page_num * BUFFER_PAGE;
        char *temp = (char*)malloc(sizeof(char) * size);
        strcpy(temp, buf);
        free(buf);
        buf = temp;
    }
    buf[nextfree - 1] = ch;
    buf[nextfree] = '\0';
    nextfree++;
}

void FlexBuffer::self_delete() {
    page_num = 0;
    size = page_num * BUFFER_PAGE;
    free(buf);
    nextfree = 0;
    p = 0;
}

char* FlexBuffer::get_line() {
    char *res;
    int b = p;
    while (buf[p] != '\n' && buf[p] != '\0') {
        p++;
    }
    if (buf[p] == '\n') {
        res = (char*)malloc(sizeof(char) * (p - b + 1));
        memcpy(res, buf + b, (p - b) * sizeof(char));
        res[p - b] = '\0';
        while (buf[p] == '\n') {
            p++;
        }
        return res;
    }
    else {
        if (p == b) {
            return NULL;
        }
        else {
            res = (char*)malloc(sizeof(char) * (p - b + 1));
            memcpy(res, buf + b, (p - b) * sizeof(char));
            res[p - b] = '\0';
            return res;
        }
    }
}
