#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/type/arena.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

cam_out_t cam_type_create_arena(cam_type_arena_t *arena,
                                const cam_size_t size) {
  if (arena == CAM_NULL) {
    cam_err_set(CAM_ERR_NULL_PTR);
    return CAM_FAILURE;
  }
  if (arena->buf != CAM_NULL)
    goto success;

  arena->offset = 0;
  arena->owned_size = size;
  arena->buf = malloc(size);
  if (arena->buf == CAM_NULL) {
    cam_err_set(CAM_ERR_MEM_ALLOC);
    return CAM_FAILURE;
  }

success:
  cam_err_set(CAM_ERR_SUCCESS);
  return CAM_SUCCESS;
}

void cam_type_free_arena(cam_type_arena_t *arena) {
  if (arena == CAM_NULL || arena->buf == CAM_NULL)
    return;
  free(arena->buf);
  arena->buf = CAM_NULL;
  arena->offset = 0;
  arena->owned_size = 0;
}

void *cam_type_alloc_arena(cam_type_arena_t *arena, const void *value,
                           const cam_size_t size) {
  if (arena == CAM_NULL || arena->buf == CAM_NULL) {
    cam_err_set(CAM_ERR_NULL_PTR);
    return CAM_NULL;
  }

  // TODO: Align pointer
  void *ptr = arena->buf + arena->offset;

  arena->offset += size;
  if (arena->offset < arena->owned_size) {
    cam_err_set(CAM_ERR_SUCCESS);
    return ptr;
  }

  // Resize through geometric expansion since it is more efficient
  arena->owned_size *= 2;
  arena->buf = realloc(arena->buf, arena->owned_size);
  if (arena->buf == CAM_NULL) {
    cam_err_set(CAM_ERR_MEM_ALLOC);
    return CAM_NULL;
  }

  return ptr;
}

cam_out_t cam_type_push_arena(cam_type_arena_t *arena, const void *value,
                              const cam_size_t size) {
  void *ptr = cam_type_alloc_arena(arena, value, size);
  if (ptr == CAM_NULL)
    return CAM_FAILURE;

  (void)memcpy(arena->buf + arena->offset, value, size);

  cam_err_set(CAM_ERR_SUCCESS);
  return CAM_SUCCESS;
}
