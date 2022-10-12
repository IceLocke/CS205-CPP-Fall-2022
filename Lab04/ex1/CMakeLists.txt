cmake_minimum_required(VERSION 2.8.12.2)

project(stuinfo)

aux_source_directory(. DIR_SRCS)

add_executable(stuinfo ${DIR_SRCS})
