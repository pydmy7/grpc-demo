set(target mainprocess)
add_executable(${target})
deploy(${target} "Qt")

target_link_libraries(${target} PRIVATE
    protobuf::libprotobuf
    gRPC::grpc++
    RpcMessage

    Qt5::Core Qt5::Widgets Qt5::Gui
)
