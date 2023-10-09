#Add executables
add_executable(waveEquationTest waveEquationTest.cpp)
add_executable(laplaceEquationTest2D laplaceEquationTest2D.cpp)

#Make sure our wonderful matplotplusplus library is linked to each executable
target_link_libraries(waveEquationTest PUBLIC matplot)
target_link_libraries(laplaceEquationTest2D PUBLIC matplot)