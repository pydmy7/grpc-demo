add_library(RpcMessage
    ${CMAKE_CURRENT_SOURCE_DIR}/rpcmessage.proto
)
protobuf_generate(
    TARGET RpcMessage
    LANGUAGE cpp
)
protobuf_generate(
    TARGET RpcMessage
    LANGUAGE grpc
    PLUGIN protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
)
target_link_libraries(RpcMessage
    PRIVATE
        protobuf::libprotobuf
        gRPC::grpc++
)
target_include_directories(RpcMessage
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
)
