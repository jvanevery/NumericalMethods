#Add executables
add_executable(machineEps machineEps.cpp)
add_executable(floatingPointGaps floatingPointGaps.cpp)
add_executable(roundingAndCutoff roundingAndCutoff.cpp)

#Make sure our wonderful matplotplusplus library is linked to each executable
target_link_libraries(machineEps PUBLIC matplot)
target_link_libraries(floatingPointGaps PUBLIC matplot)
target_link_libraries(roundingAndCutoff PUBLIC matplot)