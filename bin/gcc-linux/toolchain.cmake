set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

add_compile_options(-std=c++11 -Wall -Wextra)
add_compile_options(
	"$<$<CONFIG:RELEASE>:-O3>"
	"$<$<CONFIG:RELEASE>:-ffunction-sections>"
	"$<$<CONFIG:RELEASE>:-fdata-sections>"
	"$<$<CONFIG:RELEASE>:-flto>"
	"$<$<CONFIG:DEBUG>:-O0>"
	"$<$<CONFIG:DEBUG>:-g>"
)
add_link_options(
	"$<$<CONFIG:RELEASE>:-Wl,--gc-sections>"
)
