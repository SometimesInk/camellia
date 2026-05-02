#ifndef CAMELLIA__ERR_ERR_H__
#define CAMELLIA__ERR_ERR_H__

#include <camellia/camellia.h>

typedef enum {
#define X(err) err,
#include <camellia/err/err_codes.inc>
#undef X
  /**
   * @brief Length of `cam_err_t` enum.
   */
  CAM_ERR_LEN,
} cam_err_t;

extern cam_str_t cam_err_to_string[CAM_ERR_LEN];

/**
 * @deprecated TODO: Look into alternatives to a global variable.
 */
extern cam_err_t cam_err_prerr;

extern void cam_err_set(cam_err_t err);

extern cam_err_t cam_err_get();

#define CAM_ERR_RETURN(err)                                                    \
  do {                                                                         \
    cam_err_set(err);                                                          \
    if (err == CAM_ERR_SUCCESS)                                                \
      return CAM_SUCCESS;                                                      \
    return CAM_FAILURE;                                                        \
  } while (0)

#define CAM_ERR_RETURN_SUCCESS() CAM_ERR_RETURN(CAM_ERR_SUCCESS)

/**
 * @brief Checks `expr`, if false, it throws `err` through `CAM_ERR_RETURN`.
 */
#define CAM_ERR_CHECK(expr, err)                                               \
  do {                                                                         \
    if (!(expr)) {                                                             \
      CAM_ERR_RETURN((err));                                                   \
    }                                                                          \
  } while (0)

#define CAM_ERR_CHECK_SUCCESS(expr, err)                                       \
  do {                                                                         \
    if (!((expr) == CAM_SUCCESS)) {                                            \
      CAM_ERR_RETURN((err));                                                   \
    }                                                                          \
  } while (0)

#define CAM_ERR_FAIL_ON_FAIL(expr)                                             \
  do {                                                                         \
    if (!((expr) == CAM_SUCCESS))                                              \
      return CAM_FAILURE;                                                      \
  } while (0)

#endif /* CAMELLIA__ERR_ERR_H__ */
