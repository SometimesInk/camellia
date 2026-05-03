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

#undef CAM_TEST_RETURN
#define CAM_TEST_RETURN(v)                                                     \
  do {                                                                         \
    free(substring1.str);                                                      \
    free(substring2.str);                                                      \
    free(substring3.str);                                                      \
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
  CAM_TEST_ASSERT(strcmp(string, "ethi"));

  CAM_TEST_ASSERT_SUCCESS(cam_type_substring(&substring2, string, 0, 6));
  CAM_TEST_ASSERT_PREV_ERR_NOT(CAM_ERR_MEM_ALLOC);
  printf("Substring2: %s\n", substring2.str);
  CAM_TEST_ASSERT(strcmp(string, "Somethi"));

  CAM_TEST_ASSERT_SUCCESS(cam_type_substring(&substring3, string, 3, 9));
  CAM_TEST_ASSERT_PREV_ERR_NOT(CAM_ERR_MEM_ALLOC);
  printf("Substring3: %s\n", substring3.str);
  CAM_TEST_ASSERT(strcmp(string, "ething."));

  CAM_TEST_STOP_SUCCESS();
}
