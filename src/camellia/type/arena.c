#include <camellia/camellia.h>
#include <camellia/err/err.h>
#include <camellia/type/arena.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct cam_type_arena_block_s {
  /**
   * @brief Pointer to memory owned by the arena.
   */
  char *buf;
  /**
   * @brief Amount of bytes owned by the arena. Capacity of the arena.
   */
  cam_size_t cap;
  /**
   * @brief Start of current memory block.
   */
  cam_size_t off_start;
  /**
   * @brief End of current memory block.
   */
  cam_size_t off;
  /**
   * @brief Pointer to the next block.
   */
  struct cam_type_arena_block_s *next;
} cam_type_arena_block_t;

CAM_STATIC cam_size_t cam_type_align_up_(cam_size_t offset,
                                         cam_size_t alignment) {
  return (offset + alignment - 1) & ~(alignment - 1);
}

CAM_STATIC cam_int_t cam_type_is_power_of_two_(cam_size_t x) {
  return x != 0 && (x & (x - 1)) == 0;
}

cam_out_t cam_type_create_arena_block_(cam_type_arena_block_t *a,
                                       const cam_size_t size) {
  a->off_start = 0;
  a->off = 0;
  a->cap = size;
  a->next = CAM_NULL;
  a->buf = malloc(size);
  if (a->buf == CAM_NULL) {
    cam_err_set(CAM_ERR_MEM_ALLOC);
    return CAM_FAILURE;
  }

  cam_err_set(CAM_ERR_SUCCESS);
  return CAM_SUCCESS;
}

void cam_type_free_arena_block_(cam_type_arena_block_t *a) {
  while (a != CAM_NULL) {
    cam_type_arena_block_t *next = a->next;

    free(a->buf);
    free(a);

    a = next;
  }
}

void *cam_type_alloc_new_block_(cam_type_arena_block_t *current,
                                const cam_size_t size,
                                const cam_size_t alignment,
                                cam_type_arena_t *arena);

void *cam_type_alloc_arena_block_(cam_type_arena_block_t *current,
                                  const cam_size_t size,
                                  const cam_size_t alignment,
                                  cam_type_arena_t *arena) {
  cam_size_t aligned = cam_type_align_up_(current->off, alignment);
  cam_size_t new_off = aligned + size;

  if (new_off <= current->cap) {
    current->off_start = aligned;
    current->off = new_off;
    cam_err_set(CAM_ERR_SUCCESS);
    return current->buf + aligned;
  }

  return cam_type_alloc_new_block_(current, size, alignment, arena);
}

void *cam_type_alloc_new_block_(cam_type_arena_block_t *current,
                                const cam_size_t size,
                                const cam_size_t alignment,
                                cam_type_arena_t *arena) {
  current->next = malloc(sizeof(cam_type_arena_block_t));
  if (current->next == CAM_NULL) {
    cam_err_set(CAM_ERR_MEM_ALLOC);
    return CAM_NULL;
  }
  if (cam_type_create_arena_block_(current->next, current->cap * 2) ==
      CAM_FAILURE) {
    free(current->next);
    return CAM_NULL;
  }
  arena->current = current->next;
  arena->current->off_start = 0;
  arena->current->off = size;

  cam_err_set(CAM_ERR_SUCCESS);
  return arena->current->buf;
}

cam_out_t cam_type_create_arena(cam_type_arena_t *a, const cam_size_t size) {
  if (a == CAM_NULL) {
    cam_err_set(CAM_ERR_NULL_PTR);
    return CAM_FAILURE;
  }
  if (size == 0) {
    cam_err_set(CAM_ERR_INV_ARG);
    return CAM_FAILURE;
  }

  a->first = malloc(sizeof(struct cam_type_arena_block_s));
  if (a->first == CAM_NULL) {
    cam_err_set(CAM_ERR_MEM_ALLOC);
    return CAM_FAILURE;
  }
  a->current = a->first;
  if (cam_type_create_arena_block_(a->first, size) == CAM_FAILURE) {
    free(a->first);
    a->first = CAM_NULL;
    a->current = CAM_NULL;
    return CAM_FAILURE;
  }
  return CAM_SUCCESS;
}

void cam_type_free_arena(cam_type_arena_t *a) {
  if (a == CAM_NULL)
    return;

  cam_type_free_arena_block_(a->first);

  a->first = CAM_NULL;
  a->current = CAM_NULL;
}

void *cam_type_alloc_arena(cam_type_arena_t *a, const cam_size_t size,
                           const cam_size_t alignment) {
  if (a == CAM_NULL || a->current == CAM_NULL || a->first == CAM_NULL) {
    cam_err_set(CAM_ERR_NULL_PTR);
    return CAM_NULL;
  }
  if ((size == 0) || !cam_type_is_power_of_two_(alignment)) {
    cam_err_set(CAM_ERR_INV_ARG);
    return CAM_NULL;
  }

  return cam_type_alloc_arena_block_(a->current, size, alignment, a);
}
