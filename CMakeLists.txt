# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE src/sx1509b.c)

target_sources(app PRIVATE src/basic_blinky.c)
target_sources(app PRIVATE src/basic_direct_blinky.c)
target_sources(app PRIVATE src/breathing_blinky.c)
