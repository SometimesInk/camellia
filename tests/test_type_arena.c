#define CAM_TEST

#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/test/test.h>
#include <camellia/type/arena.h>
#include <stdint.h>
#include <stdio.h>

cam_type_arena_t ar;

#undef CAM_TEST_RETURN
#define CAM_TEST_RETURN(v)                                                     \
  do {                                                                         \
    cam_type_free_arena(&ar);                                                  \
    printf("Last err: %u.", cam_err_get());                                    \
    return v;                                                                  \
  } while (0)

cam_test_result_t main(void) {
  cam_type_free_arena(CAM_NULL);

  CAM_TEST_ASSERT_FAILURE(cam_type_create_arena(CAM_NULL, sizeof(int)));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_NULL_PTR);
  CAM_TEST_ASSERT_FAILURE(cam_type_create_arena(&ar, 0));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);
  CAM_TEST_ASSERT_SUCCESS(cam_type_create_arena(&ar, sizeof(long)));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);

  CAM_TEST_ASSERT(cam_type_alloc_arena(&ar, sizeof(int), 0) == CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);
  CAM_TEST_ASSERT(cam_type_alloc_arena(&ar, sizeof(int), 3) == CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);

  void *ptr1 = cam_type_alloc_arena(&ar, sizeof(int), _Alignof(int));
  CAM_TEST_ASSERT(ptr1 != CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  *((int *)ptr1) = 5;
  CAM_TEST_ASSERT(((uintptr_t)ptr1 % _Alignof(int)) == 0);

  CAM_TEST_ASSERT(cam_type_alloc_arena(CAM_NULL, sizeof(int), _Alignof(int)) ==
                  CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_NULL_PTR);
  CAM_TEST_ASSERT(cam_type_alloc_arena(&ar, 0, _Alignof(int)) == CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);

  char *alignment_displacer =
      cam_type_alloc_arena(&ar, sizeof(char), _Alignof(char));
  CAM_TEST_ASSERT(alignment_displacer != CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  *alignment_displacer = '1';

  long *ptr2 = cam_type_alloc_arena(&ar, sizeof(long), _Alignof(long));
  CAM_TEST_ASSERT(ptr2 != CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  *ptr2 = 6;
  CAM_TEST_ASSERT(((uintptr_t)ptr2 % _Alignof(long)) == 0);

  int *ptr3 = cam_type_alloc_arena(&ar, sizeof(int), _Alignof(int));
  CAM_TEST_ASSERT(ptr3 != CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  *ptr3 = 7;
  CAM_TEST_ASSERT(((uintptr_t)ptr3 % _Alignof(int)) == 0);

  long long *ptr4 =
      cam_type_alloc_arena(&ar, sizeof(long long), _Alignof(long long));
  CAM_TEST_ASSERT(ptr4 != CAM_NULL);
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_SUCCESS);
  CAM_TEST_ASSERT(((uintptr_t)ptr4 % _Alignof(long long)) == 0);

  CAM_TEST_ASSERT(*((int *)ptr1) == 5);
  CAM_TEST_ASSERT(*ptr2 == 6);
  CAM_TEST_ASSERT(*ptr3 == 7);
  CAM_TEST_ASSERT((void *)ptr1 != (void *)ptr2);
  CAM_TEST_ASSERT((void *)ptr2 != (void *)ptr3);
  CAM_TEST_ASSERT((void *)ptr3 != (void *)ptr4);

  CAM_TEST_STOP_SUCCESS();
}
