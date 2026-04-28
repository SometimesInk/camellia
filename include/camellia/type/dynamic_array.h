#ifndef CAMELLIA__TYPE_DYNAMIC_ARRAY_H__
#define CAMELLIA__TYPE_DYNAMIC_ARRAY_H__

#include <camellia/camellia.h>

typedef struct {
  cam_size_t ele_size;
  cam_size_t arr_used_size;
  cam_size_t arr_size;
  void *data;
} cam_type_dyn_arr_t;

extern cam_size_t cam_type_len_dyn_arr(const cam_type_dyn_arr_t *arr);

extern cam_type_dyn_arr_t
cam_type_create_dyn_arr(const cam_size_t ele_size,
                        const cam_size_t initial_size);

extern cam_out_t cam_type_push_dyn_arr(cam_type_dyn_arr_t *arr,
                                       const void *value);

extern cam_out_t cam_type_pop_dyn_arr(cam_type_dyn_arr_t *arr);

extern void cam_type_free_dyn_arr(cam_type_dyn_arr_t *arr);

extern void *cam_type_get_dyn_arr(const cam_type_dyn_arr_t *arr,
                                  const cam_size_t index);

#endif /* CAMELLIA__TYPE_DYNAMIC_ARRAY_H__ */
