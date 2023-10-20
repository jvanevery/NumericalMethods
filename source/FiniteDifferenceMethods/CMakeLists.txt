set(UTILSPATH ../Utils)
set(UTILSSOURCES ${UTILSPATH}/vector2d.h ${UTILSPATH}/vector2d.cpp)

include_directories(../Utils)

#Add executables
add_executable(waveEquationTest waveEquationTest.cpp ${UTILSSOURCES})
add_executable(laplaceEquationTest2D laplaceEquationTest2D.cpp ${UTILSSOURCES})

#Make sure our wonderful matplotplusplus library is linked to each executable
target_link_libraries(waveEquationTest PUBLIC matplot)
target_link_libraries(laplaceEquationTest2D PUBLIC matplot)
