#ifndef CAMELLIA__TEST_TEST_H__
#define CAMELLIA__TEST_TEST_H__

#include <camellia/camellia.h>
#include <stdlib.h>

typedef cam_out_t cam_test_result_t;

/**
 * @brief Return value for a failed test.
 */
#define CAM_TEST_FAILURE ((cam_test_result_t)EXIT_FAILURE)
/**
 * @brief Return value for a successful test.
 */
#define CAM_TEST_SUCCESS ((cam_test_result_t)EXIT_SUCCESS)

#define CAM_TEST_RETURN(v)                                                     \
  do {                                                                         \
    return (v);                                                                \
  } while (0)

#define CAM_TEST_STOP_SUCCESS()                                                \
  do {                                                                         \
    CAM_TEST_RETURN(CAM_TEST_SUCCESS);                                         \
  } while (0)

#define CAM_TEST_ASSERT(expr)                                                  \
  do {                                                                         \
    if (!(expr)) {                                                             \
      CAM_TEST_RETURN(CAM_TEST_FAILURE);                                       \
    }                                                                          \
  } while (0)

#define CAM_TEST_ASSERT_NOT(expr)                                              \
  do {                                                                         \
    if ((expr)) {                                                              \
      CAM_TEST_RETURN(CAM_TEST_FAILURE);                                       \
    }                                                                          \
  } while (0)

#define CAM_TEST_ASSERT_PREV_ERR(code)                                         \
  do {                                                                         \
    CAM_TEST_ASSERT(cam_err_get() == (code));                                  \
  } while (0)

#define CAM_TEST_ASSERT_PREV_ERR_NOT(code)                                     \
  do {                                                                         \
    CAM_TEST_ASSERT(cam_err_get() != (code));                                  \
  } while (0)

#define CAM_TEST_ASSERT_SUCCESS(expr)                                          \
  do {                                                                         \
    CAM_TEST_ASSERT((expr) == CAM_SUCCESS);                                    \
  } while (0)

#define CAM_TEST_ASSERT_FAILURE(expr)                                          \
  do {                                                                         \
    CAM_TEST_ASSERT((expr) == CAM_FAILURE);                                    \
  } while (0)

#define CAM_TEST_ASSERT_NULL(expr)                                             \
  do {                                                                         \
    CAM_TEST_ASSERT((expr) == CAM_NULL);                                       \
  } while (0)

#define CAM_TEST_ASSERT_NOT_NULL(expr)                                         \
  do {                                                                         \
    CAM_TEST_ASSERT((expr) != CAM_NULL);                                       \
  } while (0)

/**
 * @brief Ensures `expr` string is null terminated within `capacity` characters.
 */
#define CAM_TEST_ASSERT_NULL_TERMINATED(expr, capacity)                        \
  do {                                                                         \
    cam_size_t n__ = strnlen((expr), (capacity));                              \
    CAM_TEST_ASSERT(n__ < (capacity));                                         \
  } while (0)

#endif /* CAMELLIA__TEST_TEST_H__ */
