project(vartypes)
cmake_minimum_required(VERSION 2.4)

if(APPLE AND EXISTS /usr/local/opt/qt)
    # Homebrew installs Qt5 (up to at least 5.9.1) in
    # /usr/local/qt5, ensure it can be found by CMake since
    # it is not in the default /usr/local prefix.
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt")
endif()
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message(STATUS "Adding -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
    message(STATUS "Adding -std=c11")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
endif()

include_directories(${src_dir}/vartypes)
include_directories(${src_dir}/vartypes/primitives)
include_directories(${src_dir}/vartypes/enhanced)
include_directories(${src_dir}/vartypes/gui)
include_directories(${src_dir}/vartypes/xml)

set(src_dir .)

set (SRCS
  ${src_dir}/vartypes/VarBase64.cpp
  ${src_dir}/vartypes/VarNotifier.cpp
  ${src_dir}/vartypes/VarTypes.cpp
  ${src_dir}/vartypes/VarXML.cpp
  ${src_dir}/vartypes/VarTypesInstance.cpp
  ${src_dir}/vartypes/VarTypesFactory.cpp
  ${src_dir}/vartypes/xml/xmlParser.cpp

  ${src_dir}/vartypes/primitives/VarStringVal.cpp
  ${src_dir}/vartypes/primitives/VarBoolVal.cpp
  ${src_dir}/vartypes/primitives/VarVal.cpp
  ${src_dir}/vartypes/primitives/VarIntVal.cpp
  ${src_dir}/vartypes/primitives/VarDoubleVal.cpp

  ${src_dir}/vartypes/primitives/VarType.cpp
  ${src_dir}/vartypes/primitives/VarBlob.cpp
  ${src_dir}/vartypes/primitives/VarBool.cpp
  ${src_dir}/vartypes/primitives/VarDouble.cpp
  ${src_dir}/vartypes/primitives/VarExternal.cpp
  ${src_dir}/vartypes/primitives/VarInt.cpp
  ${src_dir}/vartypes/primitives/VarList.cpp
  ${src_dir}/vartypes/primitives/VarQWidget.cpp
  ${src_dir}/vartypes/primitives/VarSelection.cpp
  ${src_dir}/vartypes/primitives/VarString.cpp
  ${src_dir}/vartypes/primitives/VarStringEnum.cpp
  ${src_dir}/vartypes/primitives/VarTrigger.cpp

  ${src_dir}/vartypes/gui/VarItem.cpp
  ${src_dir}/vartypes/gui/VarItemDelegate.cpp
  ${src_dir}/vartypes/gui/VarTreeModel.cpp
  ${src_dir}/vartypes/gui/VarTreeView.cpp
  ${src_dir}/vartypes/gui/VarTreeViewOptions.cpp

  ${src_dir}/vartypes/primitives/VarProtoBufferVal.cpp
  ${src_dir}/vartypes/primitives/VarProtoBuffer.cpp

)

include_directories(${src_dir}/vartypes)
include_directories(${src_dir}/vartypes/primitives)
include_directories(${src_dir}/vartypes/gui)
include_directories(${src_dir}/vartypes/xml)


#only ones that need to be moc'ed
set (HEADERS
  ${src_dir}/vartypes/primitives/VarType.h
  ${src_dir}/vartypes/primitives/VarBlob.h
  ${src_dir}/vartypes/primitives/VarBool.h
  ${src_dir}/vartypes/primitives/VarDouble.h
  ${src_dir}/vartypes/primitives/VarExternal.h
  ${src_dir}/vartypes/primitives/VarInt.h
  ${src_dir}/vartypes/primitives/VarList.h
  ${src_dir}/vartypes/primitives/VarQWidget.h
  ${src_dir}/vartypes/primitives/VarSelection.h
  ${src_dir}/vartypes/primitives/VarString.h
  ${src_dir}/vartypes/primitives/VarStringEnum.h
  ${src_dir}/vartypes/primitives/VarTrigger.h
  ${src_dir}/vartypes/gui/VarItem.h
  ${src_dir}/vartypes/gui/VarItemDelegate.h
  ${src_dir}/vartypes/gui/VarTreeModel.h
  ${src_dir}/vartypes/gui/VarTreeView.h
  ${src_dir}/vartypes/VarNotifier.h
)

set (INSTALLABLE_HEADERS
  ${HEADERS}
  ${src_dir}/vartypes/VarTypes.h
  ${src_dir}/vartypes/VarTypesFactory.h
  ${src_dir}/vartypes/gui/VarTreeViewOptions.h
  ${src_dir}/vartypes/xml/xmlParser.h
  ${src_dir}/vartypes/primitives/VarVal.h
  ${src_dir}/vartypes/primitives/VarStringVal.h
  ${src_dir}/vartypes/primitives/VarIntVal.h
  ${src_dir}/vartypes/primitives/VarDoubleVal.h
  ${src_dir}/vartypes/primitives/VarBoolVal.h
  ${src_dir}/vartypes/VarXML.h
  ${src_dir}/vartypes/VarTypesInstance.h
  ${src_dir}/vartypes/VarBase64.h
  ${src_dir}/vartypes/primitives/VarProtoBufferVal.h
  ${src_dir}/vartypes/primitives/VarProtoBuffer.h
)

set (INSTALLABLE_DOCFILES
  ${src_dir}/README
  ${src_dir}/COPYING
)

set (INSTALLABLE_EXAMPLE
  ${src_dir}/README
  ${src_dir}/COPYING
)


set (RC
  ${src_dir}/vartypes/gui/icons/icons.qrc
)

qt5_wrap_cpp (MOC_SRCS
  ${HEADERS}
)

qt5_add_resources(RC_SRCS
  ${RC}
)

#flags to set in debug mode
set (CMAKE_CXX_FLAGS_DEBUG "-g")

#flags to set in release mode
set (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -march=native")

set (libs Qt5::Core Qt5::Widgets Qt5::Gui)


SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
SET(CMAKE_INSTALL_INCLUDEDIR include CACHE PATH "Output directory for header files")
SET(CMAKE_INSTALL_DOCDIR share/doc CACHE PATH "Output directory for documentation and license files")

set (target vartypes)
add_library(${target} SHARED ${MOC_SRCS} ${SRCS} ${RC_SRCS})
set_target_properties(${target} PROPERTIES VERSION 0.7.0 SOVERSION 1)
target_link_libraries(${target} ${libs})

INSTALL(FILES ${INSTALLABLE_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vartypes)

INSTALL(FILES ${INSTALLABLE_DOCFILES} DESTINATION ${CMAKE_INSTALL_DOCDIR}/vartypes)

INSTALL(TARGETS ${target}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

