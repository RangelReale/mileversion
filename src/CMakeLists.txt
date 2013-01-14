IF("${CMAKE_SYSTEM}" MATCHES "Linux")
FIND_PACKAGE(LibElf REQUIRED)
INCLUDE_DIRECTORIES(${LIBELF_INCLUDE_DIRS})
ENDIF()

SET(SRCS
	mileversion.cpp
)

SET(INCS
	../include/mileversion/mileversion.h
	../include/mileversion/mileversionimpl.h
	../include/mileversion/exceptions.h
)

if (WIN32)
	add_definitions(-DMILEVERSION_IMPL_WIN32)
	LIST(APPEND SRCS mileversionimpl_WIN32.cpp)
	LIST(APPEND INCS ../include/mileversion/mileversionimpl_WIN32.h)
elseif ("${CMAKE_SYSTEM}" MATCHES "Linux")
	add_definitions(-DMILEVERSION_IMPL_LINUX)
	LIST(APPEND SRCS mileversionimpl_LINUX.cpp)
	LIST(APPEND INCS ../include/mileversion/mileversionimpl_LINUX.h)
else()
	message( FATAL_ERROR "No platform implementation available" )
endif()

ADD_LIBRARY(mileversion SHARED ${SRCS} ${INCS} )
ADD_LIBRARY(mileversionstatic STATIC ${SRCS} ${INCS} )

if (WIN32)
TARGET_LINK_LIBRARIES ( mileversion version )
endif()
IF("${CMAKE_SYSTEM}" MATCHES "Linux")
TARGET_LINK_LIBRARIES ( mileversion ${LIBELF_LIBRARIES} )
ENDIF()
