#define CAM_TEST

#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/test/test.h>
#include <camellia/type/dynamic_array.h>
#include <stdio.h>

cam_type_dyn_arr_t arr1;

int a = 5;
int b = 6;
int c = 7;
int d = 8;
int e = 9;

#undef CAM_TEST_RETURN
#define CAM_TEST_RETURN(v)                                                     \
  do {                                                                         \
    cam_type_free_dyn_arr(&arr1);                                              \
    printf("Last err: %u.", cam_err_get());                                    \
    return v;                                                                  \
  } while (0)

cam_test_result_t main(void) {
  cam_type_free_dyn_arr(CAM_NULL);

  CAM_TEST_ASSERT_NULL(cam_type_pop_dyn_arr(CAM_NULL));
  CAM_TEST_ASSERT_NULL(cam_type_pop_dyn_arr(&arr1));
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(CAM_NULL) == 0);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 0);

  CAM_TEST_ASSERT_FAILURE(cam_type_create_dyn_arr(CAM_NULL, sizeof(int), 3));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_NULL_PTR);
  CAM_TEST_ASSERT_FAILURE(cam_type_create_dyn_arr(&arr1, 0, 3));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);
  CAM_TEST_ASSERT_FAILURE(cam_type_create_dyn_arr(&arr1, sizeof(int), 0));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);
  CAM_TEST_ASSERT_FAILURE(cam_type_create_dyn_arr(&arr1, 0, 0));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);
  CAM_TEST_ASSERT_SUCCESS(cam_type_create_dyn_arr(&arr1, sizeof(int), 3));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);

  CAM_TEST_ASSERT_NULL(cam_type_pop_dyn_arr(&arr1));
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 0);

  CAM_TEST_ASSERT_FAILURE(cam_type_push_dyn_arr(CAM_NULL, &a));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_NULL_PTR);
  CAM_TEST_ASSERT_FAILURE(cam_type_push_dyn_arr(&arr1, CAM_NULL));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_NULL_PTR);
  CAM_TEST_ASSERT_FAILURE(cam_type_push_dyn_arr(CAM_NULL, CAM_NULL));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_NULL_PTR);

  // Pushing elements

  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr1, &a));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  CAM_TEST_ASSERT(*((int *)cam_type_get_dyn_arr(&arr1, 0)) == a);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 1);

  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr1, &b));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  CAM_TEST_ASSERT(*((int *)cam_type_get_dyn_arr(&arr1, 1)) == b);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 2);

  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr1, &c));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  CAM_TEST_ASSERT(*((int *)cam_type_get_dyn_arr(&arr1, 2)) == c);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 3);

  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr1, &d));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  CAM_TEST_ASSERT(*((int *)cam_type_get_dyn_arr(&arr1, 3)) == d);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 4);

  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr1, &e));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  CAM_TEST_ASSERT(*((int *)cam_type_get_dyn_arr(&arr1, 4)) == e);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 5);

  // Popping elements

  int *e_ptr = cam_type_pop_dyn_arr(&arr1);
  CAM_TEST_ASSERT(*e_ptr == e);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 4);

  int *d_ptr = cam_type_pop_dyn_arr(&arr1);
  CAM_TEST_ASSERT(*d_ptr == d);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 3);

  // Override d_ptr through push

  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr1, &a));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  CAM_TEST_ASSERT(*((int *)cam_type_get_dyn_arr(&arr1, 3)) == a);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 4);

  CAM_TEST_ASSERT(*d_ptr == a);

  // Pop until empty

  int *fourth = cam_type_pop_dyn_arr(&arr1);
  CAM_TEST_ASSERT(*fourth == a);
  CAM_TEST_ASSERT(fourth == d_ptr);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 3);

  int *third = cam_type_pop_dyn_arr(&arr1);
  CAM_TEST_ASSERT(*third == c);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 2);

  int *second = cam_type_pop_dyn_arr(&arr1);
  CAM_TEST_ASSERT(*second == b);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 1);

  int *first = cam_type_pop_dyn_arr(&arr1);
  CAM_TEST_ASSERT(*first == a);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 0);

  int *null = cam_type_pop_dyn_arr(&arr1);
  CAM_TEST_ASSERT(null == CAM_NULL);
  CAM_TEST_ASSERT(cam_type_len_dyn_arr(&arr1) == 0);

  CAM_TEST_STOP_SUCCESS();
}
