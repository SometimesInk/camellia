#include <camellia/err/err.h>
#include <camellia/type/string.h>
#include <string.h>

// TODO: TEST
cam_out_t cam_type_substring(cam_str_t *sub, const cam_cptr_t str,
                             const cam_size_t start, const cam_size_t end) {
  sub->len = end - start + 1;
  (void)memcpy(sub->str, str + start, sub->len);
  sub->str[sub->len] = '\0';
  CAM_ERR_RETURN_SUCCESS();
}
