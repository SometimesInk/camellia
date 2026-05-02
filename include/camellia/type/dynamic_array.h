#ifndef CAMELLIA__TYPE_DYNAMIC_ARRAY_H__
#define CAMELLIA__TYPE_DYNAMIC_ARRAY_H__

#include <camellia/camellia.h>

typedef struct {
  cam_size_t ele_size;
  cam_size_t arr_used_size;
  cam_size_t arr_size;
  void *data;
} cam_type_dyn_arr_t;

/**
 * @brief Finds the number of elements in the dynamic array from the used size
 * and the element size.
 */
extern cam_size_t cam_type_len_dyn_arr(const cam_type_dyn_arr_t *arr);

/**
 * @brief Allocates memory and initializes the dynamic array.
 * @throws CAM_ERR_MEM_ALLOC Failed `malloc(3)` call.
 * @warning Array is heap allocated; remember to use `cam_type_free_dyn_arr()`
 * after usage.
 */
extern cam_out_t cam_type_create_dyn_arr(cam_type_dyn_arr_t *arr,
                                         const cam_size_t ele_size,
                                         const cam_size_t initial_size);

/**
 * @brief Adds an elements at the end of the dynamic array and resizes using
 * geometric expension when need be.
 * @throws CAM_ERR_NULL_PTR Array's `data` is null.
 * @throws CAM_ERR_INV_ARG `value` is null.
 * @throws CAM_ERR_MEM_ALLOC Failed `realloc(3)` call when size runs out.
 */
extern cam_out_t cam_type_push_dyn_arr(cam_type_dyn_arr_t *arr,
                                       const void *value);

extern cam_out_t cam_type_pop_dyn_arr(cam_type_dyn_arr_t *arr);

/**
 * @brief Frees the dynamic array's allocated memory, sets it to null, and sets
 * its size to 0.
 */
extern void cam_type_free_dyn_arr(cam_type_dyn_arr_t *arr);

/**
 * @retval CAM_NULL Data of the array is null. Sets prerr to `CAM_ERR_NULL_PTR`.
 * @retval Pointer to the i-th element of the array. Sets prerr to success.
 */
extern void *cam_type_get_dyn_arr(const cam_type_dyn_arr_t *arr,
                                  const cam_size_t index);

#endif /* CAMELLIA__TYPE_DYNAMIC_ARRAY_H__ */
