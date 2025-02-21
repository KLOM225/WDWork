#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// 检查命令行参数数量是否符合预期
#define ARGS_CHECK(argc, expected){\
    do { \
        if ((argc) != (expected)) { \
            fprintf(stderr, "args num error!\n"); \ 
            exit(1); \       
        } \                          
    } while (0); \
}

// 检查返回值是否是错误标记,若是则打印msg和错误信息
#define ERROR_CHECK(ret, error_flag, msg) \
    do { \
        if ((ret) == (error_flag)) { \
            perror(msg); \
            exit(1); \
        } \
    } while (0)

#endif
