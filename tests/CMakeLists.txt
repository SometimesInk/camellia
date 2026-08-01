set(UNIT_TEST_SOURCES test_type_dynamic_array.c test_type_str_match.c
                      test_type_substring.c test_type_is_digit_alpha_alphanumeric.c)

foreach(test_src ${UNIT_TEST_SOURCES})
  get_filename_component(test_name ${test_src} NAME_WE)

  add_executable(${test_name} ${test_src})
  target_link_libraries(${test_name} PRIVATE camellia)

  # Add flags for better warnings
  target_compile_options(${test_name} PRIVATE -fsanitize=address,undefined
                                              -fno-omit-frame-pointer -g)

  target_link_options(${test_name} PRIVATE -fsanitize=address,undefined)

  add_test(NAME ${test_name} COMMAND ${test_name})
  set_tests_properties(${test_name} PROPERTIES LABELS "unit")
endforeach()
