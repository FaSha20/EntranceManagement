# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\webserver_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\webserver_autogen.dir\\ParseCache.txt"
  "webserver_autogen"
  )
endif()
