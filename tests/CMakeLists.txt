set (SRC_TEST
  main.cpp
  Test/Test.cpp
  Tester/Tester.cpp
  )

add_executable(unit_test ${SRC_TEST})
target_compile_features(unit_test PRIVATE cxx_std_17)
add_test(first unit_test)
