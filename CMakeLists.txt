cmake_minimum_required(VERSION 2.8)

project(Opti511)

add_executable(Sobel src/sobel.cpp
					 src/BaseImage.h
					 src/BaseImage.cpp
					 src/NonMaxSuppression.h
					 src/NonMaxSuppression.cpp
					 src/SobelEdge.h
					 src/SobelEdge.cpp)

add_executable(LoG src/LoG.cpp
                   src/BaseImage.h
				   src/BaseImage.cpp
				   src/LoGEdge.h
				   src/LoGEdge.cpp
)