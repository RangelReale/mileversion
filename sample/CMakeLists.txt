include_directories(.)


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
