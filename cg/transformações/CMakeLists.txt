cmake_minimum_required(VERSION 3.0)
project( Transformacoes )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable( Transformacoes Transformacoes.cpp )
target_link_libraries( Transformacoes ${OpenCV_LIBS} Eigen3::Eigen)