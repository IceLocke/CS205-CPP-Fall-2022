cmake_minimum_required(VERSION 2.8.12.2)

project(travel)

aux_source_directory(. DIR_SRCS)

add_executable(travel ${DIR_SRCS})
