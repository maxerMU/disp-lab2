project( api-gateway CXX )

add_executable( ${PROJECT_NAME} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20 )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/api-gateway.yaml ${CMAKE_CURRENT_BINARY_DIR}/api-gateway.yaml)

target_sources( ${PROJECT_NAME} PRIVATE
  main.cpp

  ApiGatewayHandler.h
  ApiGatewayHandler.cpp

  routes/GetCarsRoute.h
  routes/GetCarsRoute.cpp
)

target_include_directories(${PROJECT_NAME} 
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        base
        NetLib
)