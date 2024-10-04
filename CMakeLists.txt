cmake_minimum_required(VERSION 3.11)

project(ParserHTML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} srs/main.cpp srs/request.cpp srs/request.h)


find_package(CURL REQUIRED) #линоковка с помощью vcpkg 
find_package(unofficial-gumbo CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::gumbo::gumbo)


 
#[===[target_link_libraries(${PROJECT_NAME} PRIVATE libcurl) #линоковка с помощью заранее установленных библиотек 
set(libcurl_DIR "C:/dev/vcpkg/installed/x64-windows") #каталог с установленной libcurl
set(libcurl_LIB_DIR ${libcurl_DIR}/lib)
set(libcurl_INCLUDE_DIR ${libcurl_DIR}/include)
add_library(libcurl STATIC IMPORTED)
set_property(TARGET libcurl PROPERTY IMPORTED_LOCATION ${libcurl_LIB_DIR}/libcurl.lib)
target_include_directories(libcurl INTERFACE ${libcurl_INCLUDE_DIR})]===]


if(CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif() 

target_link_libraries(${PROJECT_NAME} ${SYSTEM_LIBS})