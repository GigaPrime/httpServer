cmake_minimum_required(VERSION 3.17)
project(thread_pool C)

set(CMAKE_C_STANDARD 11)

add_library(thread_pool main.c
            cmake-build-debug/Headers/ThreadPool.h
            cmake-build-debug/Sources/ThreadPool.c
            cmake-build-debug/Headers/Thread.h
            cmake-build-debug/Sources/Thread.c)