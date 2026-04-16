#include <camellia/camellia.h>
#include <camellia/err/err.h>

cam_str_t cam_err_to_string[CAM_ERR_LEN] = {
#define X(err) {sizeof(#err) - 1, #err},
#include <camellia/err/err_codes.inc>
#undef X
};

cam_err_t cam_err_prev;

void cam_err_set(cam_err_t err) { cam_err_prev = err; }

cam_err_t cam_err_get() { return cam_err_prev; }
