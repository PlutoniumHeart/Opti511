cmake_minimum_required(VERSION 2.8)

project(Sobel)

add_executable(Sobel src/main.cpp
					 src/BaseImage.h
					 src/BaseImage.cpp
					 src/NonMaxSuppression.h
					 src/NonMaxSuppression.cpp
					 src/SobelEdge.h
					 src/SobelEdge.cpp)

link_libraries(Sobel)