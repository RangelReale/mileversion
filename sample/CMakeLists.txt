include_directories(.)

IF("${CMAKE_SYSTEM}" MATCHES "Linux")
FIND_PACKAGE(LibElf REQUIRED)
INCLUDE_DIRECTORIES(${LIBELF_INCLUDE_DIRS})
ENDIF()


SET(SRCS
   main.cpp mileversion_sample.rc
)
SET(INCS
   resources.h
)

ADD_EXECUTABLE( mileversion_sample ${SRCS} ${INCS} )

TARGET_LINK_LIBRARIES ( mileversion_sample mileversionstatic )

if (WIN32)
TARGET_LINK_LIBRARIES ( mileversion_sample version )
endif()
IF("${CMAKE_SYSTEM}" MATCHES "Linux")
TARGET_LINK_LIBRARIES ( mileversion_sample ${LIBELF_LIBRARIES} )
ENDIF()
