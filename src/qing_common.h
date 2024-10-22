#ifndef QING_COMMON_H
#define QING_COMMON_H

#define QING_MAX_DIMS     4
#define QING_MAX_NAME     64
#define QING_MAX_INPUT    10

#define DEBUG
#define DEBUG_LOG_GC

#ifdef DEBUG
  #include <stdio.h>
  #define QING_ASSERT(condition, message)                                           \
      do                                                                       \
      {                                                                        \
        if (!(condition))                                                      \
        {                                                                      \
          fprintf(stderr, "[%s:%d] Assert failed in %s(): %s\n",               \
              __FILE__, __LINE__, __func__, message);                          \
          abort();                                                             \
        }                                                                      \
      } while (false)

  #define QING_UNREACHABLE()                                                        \
      do                                                                       \
      {                                                                        \
        fprintf(stderr, "[%s:%d] This code should not be reached in %s()\n",   \
            __FILE__, __LINE__, __func__);                                     \
        abort();                                                               \
      } while (false)

#else

  #define QING_ASSERT(condition, message) do { } while (false)

  // Tell the compiler that this part of the code will never be reached.
  #if defined( _MSC_VER )
    #define QING_UNREACHABLE() __assume(0)
  #elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
    #define QING_UNREACHABLE() __builtin_unreachable()
  #else
    #define QING_UNREACHABLE()
  #endif

#endif

#endif //QING_COMMON_H
