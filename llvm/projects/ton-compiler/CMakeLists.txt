set(TVM_RUNTIMES
  stdlib_cpp.tvm
  stdlib_c.tvm
)

set(TVM_SUPPLEMENTS
  abi_parser.py
)

set(TVM_C_HEADERS
  ton-sdk
)

add_custom_target(tvm-runtimes)

install(FILES ${TVM_RUNTIMES}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  COMPONENT tvm-runtimes)

if (NOT CMAKE_CONFIGURATION_TYPES)
  add_custom_target(install-tvm-runtimes
                    DEPENDS tvm-runtimes
                    COMMAND "${CMAKE_COMMAND}"
                            -DCMAKE_INSTALL_COMPONENT=tvm-runtimes
                            -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")
  add_custom_target(install-tvm-runtimes-stripped DEPENDS install-tvm-runtimes)
endif()

add_custom_target(tvm-supplements ALL DEPENDS ${TVM_SUPPLEMENTS})

install(FILES ${TVM_SUPPLEMENTS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ
  COMPONENT tvm-supplements)

if (NOT CMAKE_CONFIGURATION_TYPES)
  add_custom_target(install-tvm-supplements
                    DEPENDS tvm-supplements
                    COMMAND "${CMAKE_COMMAND}"
                            -DCMAKE_INSTALL_COMPONENT=tvm-supplements
                            -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")
  # Stripping is a no-op for scripts
  add_custom_target(install-tvm-supplements-stripped DEPENDS install-tvm-supplements)
endif()

add_custom_target(tvm-c-headers ALL DEPENDS ${TVM_C_HEADERS})

install(DIRECTORY ${TVM_C_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  COMPONENT tvm-c-headers)

if (NOT CMAKE_CONFIGURATION_TYPES)
  add_custom_target(install-tvm-c-headers
                    DEPENDS tvm-c-headers
                    COMMAND "${CMAKE_COMMAND}"
                            -DCMAKE_INSTALL_COMPONENT=tvm-c-headers
                            -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")
  add_custom_target(install-tvm-c-headers-stripped DEPENDS install-tvm-c-headers)
endif()

add_subdirectory(cpp-sdk)

ExternalProject_Add(tvm_linker
  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/tvm_linker
  BUILD_IN_SOURCE On
  GIT_REPOSITORY https://github.com/tonlabs/TVM-linker/
  CONFIGURE_COMMAND cd tvm_linker && cargo update
  BUILD_COMMAND cd tvm_linker && cargo build --release
  INSTALL_COMMAND cp tvm_linker/target/release/tvm_linker ${CMAKE_INSTALL_PREFIX}/bin
)

if (NOT CMAKE_CONFIGURATION_TYPES)
  add_custom_target(install-tvm_linker DEPENDS tvm_linker)
  add_custom_target(install-tvm_linker-stripped DEPENDS install-tvm_linker)
endif()
