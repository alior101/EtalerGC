project(example1 CXX)

add_executable(example1 example1.cpp)
target_link_libraries(example1 Etaler)

project(spbench CXX)
add_executable(spbench spbench.cpp)
target_link_libraries(spbench Etaler)


project(tmexample CXX)
add_executable(tmexample tmexample.cpp)
target_link_libraries(tmexample Etaler)

project(tm_gc CXX)
add_executable(tm_gc tm_gc.cpp)
target_link_libraries(tm_gc Etaler)

project(tmbench CXX)
add_executable(tmbench tmbench.cpp)
target_link_libraries(tmbench Etaler)

project(mnist CXX)
add_executable(mnist mnist.cpp)
target_link_libraries(mnist Etaler)

if(ETALER_ENABLE_OPENCL)
	project(backend2backend CXX)
	add_executable(backend2backend backend2backend.cpp)
	target_link_libraries(backend2backend Etaler)
endif()
