#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/type/dynamic_array.h>
#include <stdlib.h>
#include <string.h>

cam_out_t cam_type_create_dyn_arr(cam_type_dyn_arr_t *arr,
                                  const cam_size_t ele_size,
                                  const cam_size_t initial_size) {
  if (arr == CAM_NULL) {
    cam_err_set(CAM_ERR_NULL_PTR);
    return CAM_FAILURE;
  }
  if (ele_size == 0 || initial_size == 0) {
    cam_err_set(CAM_ERR_INV_ARG);
    return CAM_FAILURE;
  }

  cam_size_t arr_size = ele_size * initial_size;

  arr->ele_size = ele_size;
  arr->arr_used_size = 0;
  arr->arr_size = arr_size;
  arr->data = malloc(arr_size);
  CAM_ERR_CHECK(arr->data != CAM_NULL, CAM_ERR_MEM_ALLOC);

  CAM_ERR_RETURN_SUCCESS();
}

void cam_type_free_dyn_arr(cam_type_dyn_arr_t *arr) {
  if (arr == CAM_NULL)
    return;
  if (arr->data != CAM_NULL)
    free(arr->data);
  arr->data = CAM_NULL;
  arr->arr_used_size = arr->arr_size = 0;
}

void *cam_type_get_dyn_arr(const cam_type_dyn_arr_t *arr,
                           const cam_size_t index) {
  if (arr == CAM_NULL || arr->data == CAM_NULL) {
    cam_err_set(CAM_ERR_NULL_PTR);
    return CAM_NULL;
  }
  if (index < 0) {
    cam_err_set(CAM_ERR_INV_ARG);
    return CAM_NULL;
  }
  if (index > arr->arr_size / arr->ele_size) {
    cam_err_set(CAM_ERR_RANGE);
    return CAM_NULL;
  }
  cam_err_set(CAM_ERR_SUCCESS);
  return arr->data + (index * arr->ele_size);
}

cam_size_t cam_type_len_dyn_arr(const cam_type_dyn_arr_t *arr) {
  if (arr == CAM_NULL || arr->data == CAM_NULL)
    return 0;
  return arr->arr_used_size / arr->ele_size;
}

cam_out_t cam_type_push_dyn_arr(cam_type_dyn_arr_t *arr, const void *value) {
  CAM_ERR_CHECK(arr != CAM_NULL, CAM_ERR_NULL_PTR);
  CAM_ERR_CHECK(arr->data != CAM_NULL, CAM_ERR_NULL_PTR);
  CAM_ERR_CHECK(value != CAM_NULL, CAM_ERR_NULL_PTR);

  if (arr->arr_used_size >= arr->arr_size) {
    // Grow array through geometric expansion instead of linear growth
    arr->arr_size *= 2;
    arr->data = realloc(arr->data, arr->arr_size);
    CAM_ERR_CHECK(arr->data != CAM_NULL, CAM_ERR_MEM_ALLOC);
  }

  (void)memcpy(arr->data + (cam_type_len_dyn_arr(arr) * arr->ele_size), value,
               arr->ele_size);
  arr->arr_used_size += arr->ele_size;

  CAM_ERR_RETURN_SUCCESS();
}

void *cam_type_pop_dyn_arr(cam_type_dyn_arr_t *arr) {
  if (arr == CAM_NULL || arr->data == CAM_NULL)
    return CAM_NULL;
  cam_size_t len = cam_type_len_dyn_arr(arr);
  if (len == 0)
    return CAM_NULL;
  void *out = cam_type_get_dyn_arr(arr, len - 1);
  arr->arr_used_size -= arr->ele_size;
  return out;
}
