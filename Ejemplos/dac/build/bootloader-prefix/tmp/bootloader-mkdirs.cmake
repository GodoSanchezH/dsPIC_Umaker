# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp32/esp-idf/components/bootloader/subproject"
  "C:/Users/HP/Documents/ESP32/dac/build/bootloader"
  "C:/Users/HP/Documents/ESP32/dac/build/bootloader-prefix"
  "C:/Users/HP/Documents/ESP32/dac/build/bootloader-prefix/tmp"
  "C:/Users/HP/Documents/ESP32/dac/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/HP/Documents/ESP32/dac/build/bootloader-prefix/src"
  "C:/Users/HP/Documents/ESP32/dac/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/HP/Documents/ESP32/dac/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
