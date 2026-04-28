#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/test/test.h>
#include <camellia/type/dynamic_array.h>
#include <stdio.h>

cam_type_dyn_arr_t arr;

#undef CAM_TEST_RETURN
#define CAM_TEST_RETURN(v)                                                     \
  do {                                                                         \
    cam_type_free_dyn_arr(&arr);                                               \
    printf("Last err: %u.", cam_err_get());                                    \
    return v;                                                                  \
  } while (0);

cam_test_result_t main(void) {
  cam_test_start();

  // Create
  arr = cam_type_create_dyn_arr(sizeof(int), 3);
  CAM_TEST_ASSERT_NOT_NULL(arr.data);
  printf("Created array.\n");

  // Add element
  int a = 5;
  int b = 5;
  int c = 5;
  int d = 5;
  int e = 5;
  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr, &a));
  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr, &b));
  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr, &c));
  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr, &d));
  CAM_TEST_ASSERT_SUCCESS(cam_type_push_dyn_arr(&arr, &e));
  printf("Added elements.\n");

  // Length
  cam_size_t len = cam_type_len_dyn_arr(&arr);
  printf("Length check %lu.\n", len);
  CAM_TEST_ASSERT(len == 5);

  // Removing elements
  CAM_TEST_ASSERT_SUCCESS(cam_type_pop_dyn_arr(&arr));
  CAM_TEST_ASSERT_SUCCESS(cam_type_pop_dyn_arr(&arr));
  CAM_TEST_ASSERT_SUCCESS(cam_type_pop_dyn_arr(&arr));
  printf("Removed elements.\n");

  // Length
  len = cam_type_len_dyn_arr(&arr);
  printf("Length check %lu.\n", len);
  CAM_TEST_ASSERT(len == 2);

  // Get
  CAM_TEST_ASSERT(*((int *)cam_type_get_dyn_arr(&arr, 1)) == b);

  CAM_TEST_STOP_SUCCESS();
}
