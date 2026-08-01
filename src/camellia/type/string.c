#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/type/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cam_out_t cam_type_substring(cam_str_t *sub, const cam_cptr_t str,
                             const cam_size_t start, const cam_size_t end) {
  CAM_ERR_CHECK(end >= start, CAM_ERR_INV_ARG);
  sub->len = end - start + 1;
  sub->str = (cam_cptr_t)malloc(sub->len + 1);
  CAM_ERR_CHECK(sub->str, CAM_ERR_MEM_ALLOC);
  (void)memcpy(sub->str, str + start, sub->len);
  sub->str[sub->len] = '\0';
  CAM_ERR_RETURN_SUCCESS();
}

cam_out_t cam_type_str_match(cam_cptr_t a, cam_cptr_t b, cam_size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i])
      CAM_ERR_RETURN(CAM_FAILURE);
  }
  CAM_ERR_RETURN_SUCCESS();
}

// Allow me to record an funny occurence (it may only be called funny because it
// took me a mere hour to uncover): forgot to write the single quotes...
cam_out_t cam_type_is_digit(char c) { return '0' <= c && c <= '9'; }

cam_out_t cam_type_is_alpha(char c) {
  return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_';
}

cam_out_t cam_type_is_alphanumeric(char c) {
  return cam_type_is_digit(c) || cam_type_is_alpha(c);
};
