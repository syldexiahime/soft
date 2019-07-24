file(GLOB_RECURSE SOURCES "**/*.c")
file(GLOB_RECURSE HEADERS "../include/*.h")

add_library(libsoft ${SOURCES} ${HEADERS})
target_include_directories(libsoft PRIVATE ../include)

add_library(libsoftpreprocessor ${SOURCES} ${HEADERS})
target_include_directories(libsoftpreprocessor PRIVATE ../include)

add_executable(soft soft.c ${HEADERS})
target_include_directories(soft PRIVATE ../include)
target_link_libraries(soft libsoft)

add_executable(softc softc.c ${HEADERS})
target_include_directories(softc PRIVATE ../include)
target_link_libraries(softc libsoftpreprocessor)


option(NDEBUG "NDEBUG" OFF)

if (NDEBUG)
	target_compile_options(libsoftpreprocessor PRIVATE -DNDEBUG)
	target_compile_options(softc PRIVATE -DNDEBUG)

	target_compile_options(libsoft PRIVATE -DNDEBUG)
	target_compile_options(soft PRIVATE -DNDEBUG)

	target_link_options(libsoftpreprocessor PRIVATE -DNDEBUG)
	target_link_options(softc PRIVATE -DNDEBUG)

	target_link_options(libsoft PRIVATE -DNDEBUG)
	target_link_options(soft PRIVATE -DNDEBUG)
endif ()
