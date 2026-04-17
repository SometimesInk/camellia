#include <camellia/camellia.h>
#include <string.h>

cam_str_t cam_create_str(const cam_cptr_t cptr) {
  cam_str_t str = {.len = strlen(cptr), .str = cptr};
  return str;
}

cam_str_t cam_cp_str(const cam_str_t str) {
  cam_str_t new = {.len = str.len, .str = strdup(str.str)};
  return new;
}
