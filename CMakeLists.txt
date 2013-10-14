cmake_minimum_required(VERSION 2.8)

project(Opti532)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(Sobel src/sobel.cpp
                     src/BaseImage.h
                     src/BaseImage.cpp
                     src/NonMaxSuppression.h
                     src/NonMaxSuppression.cpp
                     src/SobelEdge.h
                     src/SobelEdge.cpp
                     src/ArgumentParsing.h
                     src/ArgumentParsing.cpp
                     src/Utils.h
)

add_executable(LoG src/LoG.cpp
                   src/BaseImage.h
                   src/BaseImage.cpp
                   src/LoGEdge.h
                   src/LoGEdge.cpp
                   src/ZeroCross.h
                   src/ZeroCross.cpp
                   src/ArgumentParsing.h
                   src/ArgumentParsing.cpp
                   src/Utils.h
)

add_executable(Kittler src/Kittler.cpp
                       src/BaseImage.h
                       src/BaseImage.cpp
                       src/Histogram.h
                       src/Histogram.cpp
                       src/KittlerThreshold.h
                       src/KittlerThreshold.cpp
                       src/ArgumentParsing.h
                       src/ArgumentParsing.cpp
                       src/Utils.h
)
