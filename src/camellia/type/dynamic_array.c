#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/type/dynamic_array.h>
#include <stdlib.h>
#include <string.h>

cam_size_t cam_type_len_dyn_arr(const cam_type_dyn_arr_t *arr) {
  return arr->arr_used_size / arr->ele_size;
}

cam_type_dyn_arr_t cam_type_create_dyn_arr(const cam_size_t ele_size,
                                           const cam_size_t initial_len) {
  cam_size_t arr_size = ele_size * initial_len;
  cam_type_dyn_arr_t arr = {.ele_size = ele_size,
                            .arr_used_size = 0,
                            .arr_size = arr_size,
                            .data = malloc(arr_size)};
  return arr;
}

cam_out_t cam_type_push_dyn_arr(cam_type_dyn_arr_t *arr, const void *value) {
  CAM_ERR_CHECK(arr->data != CAM_NULL, CAM_ERR_NULL_PTR);
  CAM_ERR_CHECK(value != CAM_NULL, CAM_ERR_INV_ARG);

  if (arr->arr_used_size >= arr->arr_size) {
    arr->arr_size *= 2;
    arr->data = realloc(arr->data, arr->arr_size * arr->ele_size);
    CAM_ERR_CHECK(arr->data != CAM_NULL, CAM_ERR_NULL_PTR);
  }

  (void)memcpy(arr->data + (cam_type_len_dyn_arr(arr) * arr->ele_size), value,
               arr->ele_size);
  arr->arr_used_size += arr->ele_size;

  CAM_ERR_RETURN_SUCCESS();
}

// TODO: Return poped element
cam_out_t cam_type_pop_dyn_arr(cam_type_dyn_arr_t *arr) {
  CAM_ERR_CHECK(arr->data != CAM_NULL, CAM_ERR_NULL_PTR);
  arr->arr_used_size -= arr->ele_size;

  CAM_ERR_RETURN_SUCCESS();
}

void cam_type_free_dyn_arr(cam_type_dyn_arr_t *arr) {
  free(arr->data);
  arr->data = CAM_NULL;
  arr->arr_used_size = arr->arr_size = 0;
}

void *cam_type_get_dyn_arr(const cam_type_dyn_arr_t *arr,
                           const cam_size_t index) {
  if (arr->data == NULL) {
    cam_err_set(CAM_ERR_NULL_PTR);
    return CAM_NULL;
  }
  return arr->data + (index * arr->ele_size);
}
