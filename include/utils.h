/* utils.h */
#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>

// uint: 无符号整数类型
typedef unsigned int uint;

// foreach: 遍历数组或指定次数
#define foreach(i, a, b) for (uint i = (uint)(a); i < (uint)(b); ++i)
// foreach_ptr: 遍历结构体数组指针（C23 typeof 支持）
#define foreach_ptr(item, array, len) \
    for (typeof(*(array)) *_item = (array), item = *_item;\
     _item < (array) + (len); ++_item, item = *_item)

// assign_stable: 迭代赋值直到稳定（带默认最大迭代次数，适合组合反馈环路，C23标准）
#ifndef ASSIGN_STABLE_MAX_ITER
#define ASSIGN_STABLE_MAX_ITER 16
#endif
#define assign_stable(lhs, expr) assign_stable_n(lhs, expr, ASSIGN_STABLE_MAX_ITER)
#define assign_stable_n(lhs, expr, max_iter)                        \
    do {                                                           \
        typeof(lhs) _new;                            \
        int _iter = 0;                                             \
        do {                                                       \
            _new = (expr);                                         \
            if (memcmp(&_new, &(lhs), sizeof((lhs))) == 0) break;  \
            (lhs) = _new;                                           \
        } while (++_iter < (max_iter));                            \
        if (_iter == (max_iter))                                   \
            fprintf(stderr, "[WARN] assign_stable: not stable after %d iterations\n", (max_iter)); \
        (lhs) = _new;                                              \
    } while(0)

// assign_stable_ptr: 迭代拷贝引用类型内容直到稳定（带最大迭代次数）
#define assign_stable_ptr(ptr, expr, size) assign_stable_ptr_n(ptr, expr, size, ASSIGN_STABLE_MAX_ITER)
#define assign_stable_ptr_n(ptr, expr, size, max_iter)                 \
    do {                                                              \
        unsigned char _new[size];                                     \
        int _iter = 0;                                                \
        do {                                                          \
            memcpy(_new, (expr), size);                               \
            if (memcmp(_new, ptr, size) == 0) break;                  \
            memcpy(ptr, _new, size);                                  \
        } while (++_iter < (max_iter));                               \
        if (_iter == (max_iter))                                      \
            fprintf(stderr, "[WARN] assign_stable_ptr: not stable after %d iterations\n", (max_iter)); \
        memcpy(ptr, _new, size);                                      \
    } while(0)

// UNUSED: 消除未使用变量警告
#define UNUSED(x) (void)(x)

#endif // UTILS_H
