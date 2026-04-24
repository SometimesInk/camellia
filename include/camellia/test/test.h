#ifndef CAMELLIA__TEST_TEST_H__
#define CAMELLIA__TEST_TEST_H__

#include <camellia/camellia.h>
#include <stdlib.h>
#include <string.h>

typedef cam_out_t cam_test_result_t;

/**
 * @brief Return value for a failed test.
 */
#define CAM_TEST_FAILURE ((cam_test_result_t)EXIT_FAILURE)
/**
 * @brief Return value for a successful test.
 */
#define CAM_TEST_SUCCESS ((cam_test_result_t)EXIT_SUCCESS)

/**
 * @brief Whether there is a test running or not.
 */
typedef enum {
  /**
   * @brief There is a test running.
   */
  CAM_TEST_STATE_TESTING,
  /**
   * @brief There is no test running.
   */
  CAM_TEST_STATE_NOT_TESTING
} cam_test_state_t;

typedef struct {
  cam_test_state_t state;
} cam_test_context_t;

extern cam_test_context_t cam_test_context;

extern void cam_test_start();
extern void cam_test_stop();

#define CAM_TEST_RETURN(v) return (v);

#define CAM_TEST_STOP_SUCCESS()                                                \
  do {                                                                         \
    cam_test_stop();                                                           \
    CAM_TEST_RETURN(CAM_TEST_SUCCESS)                                          \
  } while (0)

#define CAM_TEST_ASSERT(expr)                                                  \
  do {                                                                         \
    if (!(expr)) {                                                             \
      cam_test_stop();                                                         \
      CAM_TEST_RETURN(CAM_TEST_FAILURE)                                        \
    }                                                                          \
  } while (0)

#define CAM_TEST_ASSERT_NOT(expr)                                              \
  do {                                                                         \
    if ((expr)) {                                                              \
      cam_test_stop();                                                         \
      CAM_TEST_RETURN(CAM_TEST_FAILURE)                                        \
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

#define CAM_TEST_ASSERT_NULL_TERMINATED(expr, capacity)                        \
  do {                                                                         \
    cam_size_t n__ = strnlen((expr), (capacity));                              \
    CAM_TEST_ASSERT(n__ < (capacity));                                         \
  } while (0)

#endif /* CAMELLIA__TEST_TEST_H__ */
