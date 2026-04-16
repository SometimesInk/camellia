#ifndef CAMELLIA__CAMELLIA_H__
#define CAMELLIA__CAMELLIA_H__

#include <stddef.h>
#include <string.h>

typedef int cam_out_t;

#define CAM_SUCCESS ((cam_out_t)1)
#define CAM_FAILURE ((cam_out_t)0)

#define CAM_NULL ((void *)0)

typedef char *cam_cptr_t;

typedef size_t cam_size_t;

typedef struct {
  cam_size_t len;
  cam_cptr_t str;
} cam_str_t;

extern cam_str_t cam_create_str(const cam_cptr_t cptr);

extern cam_str_t cam_cp_str(const cam_str_t str);

#endif /* CAMELLIA__CAMELLIA_H__ */
