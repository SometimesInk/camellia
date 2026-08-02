#define CAM_TEST

#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/test/test.h>
#include <camellia/type/string.h>

cam_test_result_t main(void) {
  CAM_TEST_ASSERT(cam_type_is_digit('0'));
  CAM_TEST_ASSERT(cam_type_is_digit('1'));
  CAM_TEST_ASSERT(cam_type_is_digit('2'));
  CAM_TEST_ASSERT(cam_type_is_digit('3'));
  CAM_TEST_ASSERT(cam_type_is_digit('4'));
  CAM_TEST_ASSERT(cam_type_is_digit('5'));
  CAM_TEST_ASSERT(cam_type_is_digit('6'));
  CAM_TEST_ASSERT(cam_type_is_digit('7'));
  CAM_TEST_ASSERT(cam_type_is_digit('8'));
  CAM_TEST_ASSERT(cam_type_is_digit('9'));

  // Check values barely out of range to ensure there are no subtle comparison
  // errors.
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('0' - 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('9' + 1));

  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('q'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('w'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('e'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('r'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('t'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('y'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('u'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('i'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('o'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_digit('p'));

  CAM_TEST_ASSERT(cam_type_is_alpha('a'));
  CAM_TEST_ASSERT(cam_type_is_alpha('m'));
  CAM_TEST_ASSERT(cam_type_is_alpha('z'));
  CAM_TEST_ASSERT(cam_type_is_alpha('A'));
  CAM_TEST_ASSERT(cam_type_is_alpha('M'));
  CAM_TEST_ASSERT(cam_type_is_alpha('Z'));
  CAM_TEST_ASSERT(cam_type_is_alpha('_'));

  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('0' - 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('9' + 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('0'));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('1'));

  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('a' - 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('A' - 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('z' + 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alpha('Z' + 1));

  CAM_TEST_ASSERT(cam_type_is_alphanumeric('a'));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('m'));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('z'));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('A'));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('M'));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('Z'));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('_'));

  CAM_TEST_ASSERT_FAILURE(cam_type_is_alphanumeric('0' - 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alphanumeric('9' + 1));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('0'));
  CAM_TEST_ASSERT(cam_type_is_alphanumeric('1'));

  // These aren't numbers
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alphanumeric('a' - 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alphanumeric('A' - 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alphanumeric('z' + 1));
  CAM_TEST_ASSERT_FAILURE(cam_type_is_alphanumeric('Z' + 1));

  CAM_TEST_STOP_SUCCESS();
}
