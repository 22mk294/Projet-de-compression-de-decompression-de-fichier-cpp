# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Archiz_autogen"
  "CMakeFiles\\Archiz_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Archiz_autogen.dir\\ParseCache.txt"
  )
endif()
