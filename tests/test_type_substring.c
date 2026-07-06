#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/test/test.h>
#include <camellia/type/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cam_str_t substring1;
cam_str_t substring2;
cam_str_t substring3;
cam_str_t substring4;
cam_str_t substring5;
cam_str_t substring6;

#undef CAM_TEST_RETURN
#define CAM_TEST_RETURN(v)                                                     \
  do {                                                                         \
    free(substring1.str);                                                      \
    free(substring2.str);                                                      \
    free(substring3.str);                                                      \
    free(substring4.str);                                                      \
    free(substring5.str);                                                      \
    free(substring6.str);                                                      \
    printf("Last err: %u.", cam_err_get());                                    \
    return v;                                                                  \
  } while (0);

cam_test_result_t main(void) {
  cam_test_start();

  //                   0123456789
  cam_cptr_t string = "Something.";
  printf("String: %s\n", string);

  CAM_TEST_ASSERT_SUCCESS(cam_type_substring(&substring1, string, 3, 6));
  CAM_TEST_ASSERT_PREV_ERR_NOT(CAM_ERR_MEM_ALLOC);
  printf("Substring1: %s\n", substring1.str);
  CAM_TEST_ASSERT(substring1.len == 4);
  CAM_TEST_ASSERT(strcmp(substring1.str, "ethi") == 0);

  CAM_TEST_ASSERT_SUCCESS(cam_type_substring(&substring2, string, 0, 6));
  CAM_TEST_ASSERT_PREV_ERR_NOT(CAM_ERR_MEM_ALLOC);
  printf("Substring2: %s\n", substring2.str);
  CAM_TEST_ASSERT(substring2.len == 7);
  CAM_TEST_ASSERT(strcmp(substring2.str, "Somethi") == 0);

  CAM_TEST_ASSERT_SUCCESS(cam_type_substring(&substring3, string, 9, 9));
  CAM_TEST_ASSERT_PREV_ERR_NOT(CAM_ERR_MEM_ALLOC);
  printf("Substring3: %s\n", substring3.str);
  CAM_TEST_ASSERT(substring3.len == 1);
  CAM_TEST_ASSERT(strcmp(substring3.str, ".") == 0);

  CAM_TEST_ASSERT_SUCCESS(cam_type_substring(&substring4, string, 0, 0));
  CAM_TEST_ASSERT_PREV_ERR_NOT(CAM_ERR_MEM_ALLOC);
  printf("Substring4: %s\n", substring4.str);
  CAM_TEST_ASSERT(substring4.len == 1);
  CAM_TEST_ASSERT(strcmp(substring4.str, "S") == 0);

  CAM_TEST_ASSERT_SUCCESS(cam_type_substring(&substring5, string, 0, 9));
  CAM_TEST_ASSERT_PREV_ERR_NOT(CAM_ERR_MEM_ALLOC);
  printf("Substring5: %s\n", substring5.str);
  CAM_TEST_ASSERT(substring5.len == 10);
  CAM_TEST_ASSERT(strcmp(substring5.str, "Something.") == 0);

  CAM_TEST_ASSERT_FAILURE(cam_type_substring(&substring6, string, 6, 3));
  CAM_TEST_ASSERT_PREV_ERR(CAM_ERR_INV_ARG);

  CAM_TEST_STOP_SUCCESS();
}
