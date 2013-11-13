cmake_minimum_required(VERSION 2.8)

project(Opti532)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(src/Include/)

add_executable(Sobel src/sobel.cpp
                     src/Include/BaseImage.h
                     src/BaseImage.cpp
                     src/Include/NonMaxSuppression.h
                     src/NonMaxSuppression.cpp
                     src/Include/SobelEdge.h
                     src/SobelEdge.cpp
                     src/Include/ArgumentParsing.h
                     src/ArgumentParsing.cpp
                     src/Include/Utils.h
)

add_executable(LoG src/LoG.cpp
                   src/Include/BaseImage.h
                   src/BaseImage.cpp
                   src/Include/LoGEdge.h
                   src/LoGEdge.cpp
                   src/Include/ZeroCross.h
                   src/ZeroCross.cpp
                   src/Include/ArgumentParsing.h
                   src/ArgumentParsing.cpp
                   src/Include/Utils.h
)

add_executable(Kittler src/Kittler.cpp
                       src/Include/BaseImage.h
                       src/BaseImage.cpp
                       src/Include/Histogram.h
                       src/Histogram.cpp
                       src/Include/KittlerThreshold.h
                       src/KittlerThreshold.cpp
                       src/Include/ArgumentParsing.h
                       src/ArgumentParsing.cpp
                       src/Include/Utils.h
)

add_executable(Label src/Label.cpp
                     src/Include/ConnectedComponentsLabelling.h
                     src/ConnectedComponentsLabelling.cpp
                     src/Include/BaseImage.h
                     src/BaseImage.cpp
                     src/Include/ArgumentParsing.h
                     src/ArgumentParsing.cpp
                     src/Include/Utils.h
)

add_executable(Dilation src/Include/BaseImage.h
                        src/BaseImage.cpp
                        src/Include/ArgumentParsing.h
                        src/ArgumentParsing.cpp
                        src/Include/BinaryDilation.h
                        src/BinaryDilation.cpp
                        src/Dilation.cpp
)

add_executable(Erosion src/Include/BaseImage.h
                       src/BaseImage.cpp
                       src/Include/ArgumentParsing.h
                       src/ArgumentParsing.cpp
                       src/Include/BinaryDilation.h
                       src/BinaryDilation.cpp
                       src/Include/BinaryErosion.h
                       src/BinaryErosion.cpp
                       src/Erosion.cpp
)

add_executable(Openning src/Include/BaseImage.h
                        src/BaseImage.cpp
                        src/Include/ArgumentParsing.h
                        src/ArgumentParsing.cpp
                        src/Include/BinaryDilation.h
                        src/BinaryDilation.cpp
                        src/Include/BinaryErosion.h
                        src/BinaryErosion.cpp
                        src/Include/BinaryOpening.h
                        src/BinaryOpening.cpp
                        src/Opening.cpp
)

add_executable(Closing src/Include/BaseImage.h
                       src/BaseImage.cpp
                       src/Include/ArgumentParsing.h
                       src/ArgumentParsing.cpp
                       src/Include/BinaryDilation.h
                       src/BinaryDilation.cpp
                       src/Include/BinaryErosion.h
                       src/BinaryErosion.cpp
                       src/Include/BinaryOpening.h
                       src/BinaryOpening.cpp
                       src/Include/BinaryClosing.h
                       src/BinaryClosing.cpp
                       src/Closing.cpp
)
