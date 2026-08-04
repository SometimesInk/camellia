#ifndef CAM__TYPE_ARENA_H__
#define CAM__TYPE_ARENA_H__

#include <camellia/camellia.h>
#include <stddef.h>

struct cam_type_arena_block_s;

typedef struct {
  struct cam_type_arena_block_s *first;
  struct cam_type_arena_block_s *current;
} cam_type_arena_t;

/**
 * @brief Initializes and allocates memory for arena using malloc. If the arena
 * buffer is already allocated, will succeed and not do anything.
 * @param size Number of bytes for initial size of the arena.
 * @throws CAM_ERR_NULL_PTR When pointer to arena is null.
 * @throws CAM_ERR_INV_ARG When size is 0.
 * @throws CAM_ERR_MEM_ALLOC When malloc fails to allocate memory for buffer.
 */
extern cam_out_t cam_type_create_arena(cam_type_arena_t *a,
                                       const cam_size_t size);

/**
 * @brief Frees at once the full buffer of the arena. Does not set prerr.
 */
extern void cam_type_free_arena(cam_type_arena_t *a);

/**
 * @brief Gives a pointer to the next memory block in the arena.
 * @param size Maximum number of bytes to send over.
 * @throws CAM_ERR_NULL_PTR When arena or arena buffer is null.
 * @throws CAM_ERR_INV_ARG When size is 0 or alignment is not a power of two.
 * @throws CAM_ERR_MEM_ALLOC Failed to resize memory using realloc.
 */
extern void *cam_type_alloc_arena(cam_type_arena_t *a, const cam_size_t size,
                                  const cam_size_t alignment);

#endif /* CAM__TYPE_ARENA_H__ */
