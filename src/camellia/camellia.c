#include <camellia/camellia.h>
#include <string.h>

cam_str_t cam_create_str(const cam_cptr_t cptr) {
  cam_str_t str = {strlen(cptr), cptr};
  return str;
}

cam_str_t cam_cp_str(const cam_str_t str) {
  cam_str_t new = {str.len, strdup(str.str)};
  return new;
}
