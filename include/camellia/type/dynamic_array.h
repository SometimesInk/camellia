#ifndef CAMELLIA__TYPE_DYNAMIC_ARRAY_H__
#define CAMELLIA__TYPE_DYNAMIC_ARRAY_H__

#include <camellia/camellia.h>

typedef struct {
  /**
   * @brief Size allocated per element. In bytes.
   */
  cam_size_t ele_size;
  /**
   * @brief Used size in total array size. In bytes.
   */
  cam_size_t arr_used_size;
  /**
   * @brief Amount of memory allocated to the array. In bytes.
   */
  cam_size_t arr_size;
  /**
   * @brief Pointer to the memory owned by the array.
   * @warn Heap allocated.
   */
  void *data;
} cam_type_dyn_arr_t;

/**
 * @brief Allocates memory and initializes the dynamic array.
 * @param arr Pointer to the array to be initialized.
 * @param ele_size Size in bytes of each element.
 * @param initial_size Initial length of the array. Initial size times element
 * size gives the total amount of bytes to be allocated.
 * @throws CAM_ERR_MEM_ALLOC Failed `malloc(3)` call.
 * @throws CAM_ERR_NULL_PTR When pointer to the array is null.
 * @throws CAM_ERR_INV_ARG When `ele_size` or `initial_size` are 0 or smaller.
 * @warning Array is heap allocated; remember to use `cam_type_free_dyn_arr()`
 * after usage.
 * @warning Passing a negative value through `ele_size` or `initial_size` will
 * cause a memory overflow error due to `cam_size_t` being unsigned.
 */
extern cam_out_t cam_type_create_dyn_arr(cam_type_dyn_arr_t *arr,
                                         const cam_size_t ele_size,
                                         const cam_size_t initial_size);

/**
 * @brief Frees the dynamic array's allocated memory, sets it to null, and sets
 * its size to 0. Does not set prerr.
 */
extern void cam_type_free_dyn_arr(cam_type_dyn_arr_t *arr);

/**
 * @brief Finds the number of elements in the dynamic array from the used size
 * and the element size. Does not set prerr.
 * @param arr Pointer to the initialized array.
 * @retval Length of array or zero on null.
 */
extern cam_size_t cam_type_len_dyn_arr(const cam_type_dyn_arr_t *arr);

/**
 * @retval CAM_NULL Error occurred, check prerr. Otherwise, pointer to the i-th
 * element of the array.
 * @param arr Pointer to the initialized array.
 * @param index Index of the element to get from the array. In the range [0,
 * len).
 * @throws CAM_ERR_NULL_PTR When `arr` or `arr.data` is null.
 * @throws CAM_ERR_INV_ARG When index is smaller than 0.
 * @throws CAM_ERR_RANGE When index is greater than array length.
 */
extern void *cam_type_get_dyn_arr(const cam_type_dyn_arr_t *arr,
                                  const cam_size_t index);

/**
 * @brief Adds an elements at the end of the dynamic array and resizes using
 * geometric expension when need be.
 * @param arr Pointer to the initialized array.
 * @param value Pointer to the value to be pushed onto the array through
 * memcpy(3).
 * @throws CAM_ERR_NULL_PTR When `arr` or `arr.data` is null, or 'value' is
 * null.
 * @throws CAM_ERR_MEM_ALLOC Failed `realloc(3)` call.
 */
extern cam_out_t cam_type_push_dyn_arr(cam_type_dyn_arr_t *arr,
                                       const void *value);

/**
 * @brief Reduces array used size. In this way, the next element will override
 * the removed element. Does not set prerr.
 * @warn Output pointer should be accessible until another element is pushed
 * onto the array and overrides this object.
 * @retval CAM_NULL When `arr` or `arr.data` is null or array is empty.
 * Otherwise a pointer to the removed element.
 */
extern void *cam_type_pop_dyn_arr(cam_type_dyn_arr_t *arr);

#endif /* CAMELLIA__TYPE_DYNAMIC_ARRAY_H__ */
