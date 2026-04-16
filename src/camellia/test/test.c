#include <camellia/test/test.h>

cam_test_context_t cam_test_context = {CAM_TEST_STATE_NOT_TESTING};

void cam_test_start() { cam_test_context.state = CAM_TEST_STATE_TESTING; }

void cam_test_stop() { cam_test_context.state = CAM_TEST_STATE_NOT_TESTING; }
