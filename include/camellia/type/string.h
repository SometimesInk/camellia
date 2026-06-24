#ifndef CAMELLIA__TYPE_STRING_H__
#define CAMELLIA__TYPE_STRING_H__

// TODO: Move string type here

#include <camellia/camellia.h>

/**
 * @brief Gets the substring of `str` from index `start` to `end`.
 * @warm This is inclusive, thus from the range [start, end].
 */
extern cam_out_t cam_type_substring(cam_str_t *sub, const cam_cptr_t str,
                                    const cam_size_t start,
                                    const cam_size_t end);

extern cam_out_t cam_type_str_match(cam_cptr_t a, cam_cptr_t b, cam_size_t n);

#endif /* CAMELLIA__TYPE_STRING_H__ */
