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

// TODO: Add more rigorous range checks
/**
 * @brief Checks if the first `n` characters of `a` and `b` are equal. This
 * should be less efficient than libc strcmp.
 */
extern cam_out_t cam_type_str_match(cam_cptr_t a, cam_cptr_t b, cam_size_t n);

/**
 * @brief Checks if the current character is a digit.
 */
extern cam_out_t cam_type_is_digit(char c);

/**
 * @brief Checks if the current character is a letter of the alphabet or an
 * underscore.
 */
extern cam_out_t cam_type_is_alpha(char c);

/**
 * @brief Checks if the current character is alphanumeric or an underscore.
 */
extern cam_out_t cam_type_is_alphanumeric(char c);

#endif /* CAMELLIA__TYPE_STRING_H__ */
