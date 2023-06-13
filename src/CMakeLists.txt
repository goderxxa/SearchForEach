cmake_minimum_required (VERSION 3.24)

set(src
	"SearchServer.cpp"
	"InvertedIndex.cpp"
	"main.cpp"
	"ConverterJson.cpp" )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(SearchForEach ${src})

target_link_libraries(SearchForEach nlohmann_json::nlohmann_json)
target_include_directories(SearchForEach PUBLIC ${MY_INCLUDE_DIR})