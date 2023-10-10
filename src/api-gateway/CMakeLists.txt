project( api-gateway CXX )

add_executable( ${PROJECT_NAME} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20 )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/api-gateway.yaml ${CMAKE_CURRENT_BINARY_DIR}/api-gateway.yaml)

target_sources( ${PROJECT_NAME} PRIVATE
  main.cpp

  ApiGatewayHandler.h
  ApiGatewayHandler.cpp

  context/ApiGatewayContext.h
  context/ApiGatewayContext.cpp

  dto/CarDTO.h
  dto/CarDTO.cpp
  dto/GetRentDTO.h
  dto/GetRentDTO.cpp
  dto/PaymentDTO.h
  dto/PaymentDTO.cpp
  dto/RentDTO.h
  dto/RentDTO.cpp

  routes/GetRentPrep.h
  routes/GetRentPrep.cpp
  routes/GetRentsPrep.h
  routes/GetRentsPrep.cpp
  routes/GetRentPost.h
  routes/GetRentPost.cpp
  routes/GetRentsPost.h
  routes/GetRentsPost.cpp
  routes/GetCarRoute.h
  routes/GetCarRoute.cpp
  routes/GetCarsRoute.h
  routes/GetCarsRoute.cpp
  routes/GetPaymentRoute.h
  routes/GetPaymentRoute.cpp
  routes/GetRentRoute.h
  routes/GetRentRoute.cpp
  routes/GetRentsRoute.h
  routes/GetRentsRoute.cpp
)

target_include_directories(${PROJECT_NAME} 
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        base
        NetLib
        jsoncpp_lib
)