include(CheckFunctionExists)
add_definitions(-DINSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\")

add_executable (nespackager
NESPackager.cpp
)

add_executable (pbbookmaker
PBBookMaker.cpp
)

target_link_libraries (nespackager LINK_PUBLIC DCL pthread)
target_link_libraries (pbbookmaker LINK_PUBLIC DCL pthread)
install(TARGETS nespackager RUNTIME DESTINATION bin)
install(TARGETS pbbookmaker RUNTIME DESTINATION bin)
install(FILES NESPackager_Template/nespkgtemplate.nsof DESTINATION share/DCL/)
install(DIRECTORY PBBookMaker_Templates/ DESTINATION share/DCL/ FILES_MATCHING PATTERN *.nsof)
