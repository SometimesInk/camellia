#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/test/test.h>
#include <camellia/type/string.h>

cam_test_result_t main(void) {
  cam_test_start();

  cam_cptr_t string = "Something.";

  // Match
  CAM_TEST_ASSERT_SUCCESS(cam_type_str_match(string, "Something!", 5));
  CAM_TEST_ASSERT_FAILURE(cam_type_str_match(string, "Something!", 10));

  CAM_TEST_STOP_SUCCESS();
}
