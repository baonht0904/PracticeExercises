# Option
option(BUILD_SHARED_LIB "Build shared library!" ON)

add_library(MyVector myVector.cpp)

target_include_directories(MyVector PUBLIC "${CMAKE_SOURCE_DIR}/include")

# install(DIRECTORY DESTINATION include)
# # install(DIRECTORY DESTINATION lib)
# install(TARGETS MyVector)
# install(FILES ${CMAKE_SOURCE_DIR}/include/myVector.h DESTINATION include)
