#ifndef CAM__TYPE_ARENA_H__
#define CAM__TYPE_ARENA_H__

#include <camellia/camellia.h>
#include <stddef.h>

typedef struct {
  /**
   * @brief Pointer to memory owned by the arena.
   */
  void *buf;
  /**
   * @brief Amount of bytes owned by the arena.
   */
  cam_size_t owned_size;
  /**
   * @brief Current position of the free region of the arena.
   */
  cam_size_t offset;
} cam_type_arena_t;

/**
 * @brief Initializes and allocates memory for arena using malloc. If the arena
 * buffer is already allocated, will succeed and not do anything.
 * @param size Number of bytes for initial size of the arena.
 * @throws CAM_ERR_NULL_PTR When pointer to arena is null.
 * @throws CAM_ERR_MEM_ALLOC When malloc fails to allocate memory for buffer.
 */
extern cam_out_t cam_type_create_arena(cam_type_arena_t *arena,
                                       const cam_size_t size);

/**
 * @brief Frees at once the full buffer of the arena. Does not set prerr.
 */
extern void cam_type_free_arena(cam_type_arena_t *arena);

/**
 * @brief Copies `size` bytes from `value` to the top of the arena.
 * @param size Maximum number of bytes to send over.
 * @throws CAM_ERR_NULL_PTR When arena or arena buffer is null.
 * @throws CAM_ERR_MEM_ALLOC Failed to resize memory using realloc.
 */
extern cam_out_t cam_type_push_arena(cam_type_arena_t *arena, const void *value,
                                     const cam_size_t size);

#endif /* CAM__TYPE_ARENA_H__ */
