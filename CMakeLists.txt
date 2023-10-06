#Using CMAKE to manage build because of libraries

#Set minimum required version
cmake_minimum_required(VERSION 3.15)

#Project name
project(NumericalMethods)

#Adding source directory
add_subdirectory(source)

#Adding libs directory
add_subdirectory(libs)