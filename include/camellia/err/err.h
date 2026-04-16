#ifndef CAMELLIA__ERR_ERR_H__
#define CAMELLIA__ERR_ERR_H__

#include <camellia/camellia.h>

typedef enum {
#define X(err) err,
#include <camellia/err/err_codes.inc>
#undef X
  CAM_ERR_LEN,
} cam_err_t;

extern cam_str_t cam_err_to_string[CAM_ERR_LEN];

extern void cam_err_set(cam_err_t err);

extern cam_err_t cam_err_get();

#define CAM_ERR_RETURN(err)                                                    \
  do {                                                                         \
    cam_err_set(err);                                                          \
    if (err == CAM_ERR_SUCCESS)                                                \
      return CAM_SUCCESS;                                                      \
    return CAM_FAILURE;                                                        \
  } while (0)

#endif /* CAMELLIA__ERR_ERR_H__ */
