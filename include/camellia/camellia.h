#ifndef CAMELLIA__CAMELLIA_H__
#define CAMELLIA__CAMELLIA_H__

#include <camellia/type/int.h>
#include <stddef.h>
#include <string.h>

typedef int cam_out_t;

#define CAM_SUCCESS ((cam_out_t)1)
#define CAM_FAILURE ((cam_out_t)0)

#define CAM_TRUE ((cam_int_t)1)
#define CAM_FALSE ((cam_int_t)0)

#define CAM_NULL ((void *)0)

/**
 * @deprecated Prefer `char *`
 */
typedef char *cam_cptr_t;

typedef size_t cam_size_t;

struct cam_type_str_s {
  cam_size_t len;
  cam_cptr_t str;
};
typedef struct cam_type_str_s cam_str_t;

#define CAM_STR_NULL ((cam_str_t){.len = 0, .str = CAM_NULL})

typedef cam_type_sint32_t cam_int_t;

extern cam_str_t cam_create_str(const cam_cptr_t cptr);

extern cam_str_t cam_cp_str(const cam_str_t str);

#ifdef CAM_TEST
#define CAM_STATIC
#else
#define CAM_STATIC static
#endif

#endif /* CAMELLIA__CAMELLIA_H__ */
