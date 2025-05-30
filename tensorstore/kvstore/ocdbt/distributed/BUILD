# Distributed write support for Optionally-cooperative Distributed B+tree driver

load(
    "//bazel:tensorstore.bzl",
    "tensorstore_cc_grpc_library",
    "tensorstore_cc_library",
    "tensorstore_cc_proto_library",
    "tensorstore_cc_test",
    "tensorstore_proto_library",
)

package(default_visibility = ["//tensorstore:internal_packages"])

licenses(["notice"])

tensorstore_cc_library(
    name = "coordinator_server",
    srcs = ["coordinator_server.cc"],
    hdrs = ["coordinator_server.h"],
    deps = [
        ":coordinator_cc_grpc",
        ":coordinator_cc_proto",
        ":rpc_security",
        "//tensorstore:json_serialization_options",
        "//tensorstore/internal/container:heterogeneous_container",
        "//tensorstore/internal/container:intrusive_red_black_tree",
        "//tensorstore/internal/grpc:peer_address",
        "//tensorstore/internal/grpc/serverauth:default_strategy",
        "//tensorstore/internal/grpc/serverauth:strategy",
        "//tensorstore/internal/json_binding",
        "//tensorstore/internal/json_binding:bindable",
        "//tensorstore/internal/log:verbose_flag",
        "//tensorstore/proto:encode_time",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/container:flat_hash_map",
        "@abseil-cpp//absl/log:absl_log",
        "@abseil-cpp//absl/meta:type_traits",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/synchronization",
        "@abseil-cpp//absl/time",
        "@abseil-cpp//absl/types:compare",
        "@grpc//:grpc++",
    ],
)

tensorstore_cc_test(
    name = "coordinator_server_test",
    size = "small",
    srcs = ["coordinator_server_test.cc"],
    tags = ["cpu:2"],
    deps = [
        ":btree_node_identifier",
        ":coordinator_cc_grpc",
        ":coordinator_server",
        ":lease_cache_for_cooperator",
        ":rpc_security",
        "//tensorstore/internal/grpc/clientauth:create_channel",
        "//tensorstore/kvstore:key_range",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:status_testutil",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/log:absl_log",
        "@abseil-cpp//absl/time",
        "@googletest//:gtest_main",
        "@grpc//:grpc++",
    ],
)

tensorstore_proto_library(
    name = "coordinator_proto",
    srcs = ["coordinator.proto"],
    has_services = True,
    deps = [
        "@com_google_protobuf//:duration_proto",
        "@com_google_protobuf//:timestamp_proto",
    ],
)

tensorstore_cc_proto_library(
    name = "coordinator_cc_proto",
    deps = [":coordinator_proto"],
)

tensorstore_cc_grpc_library(
    name = "coordinator_cc_grpc",
    srcs = [":coordinator_proto"],
    deps = [
        ":coordinator_cc_proto",
    ],
)

tensorstore_proto_library(
    name = "cooperator_proto",
    srcs = ["cooperator.proto"],
    has_services = True,
)

tensorstore_cc_proto_library(
    name = "cooperator_cc_proto",
    deps = [":cooperator_proto"],
)

tensorstore_cc_grpc_library(
    name = "cooperator_cc_grpc",
    srcs = [":cooperator_proto"],
    deps = [
        ":cooperator_cc_proto",
    ],
)

tensorstore_cc_library(
    name = "lease_cache_for_cooperator",
    srcs = ["lease_cache_for_cooperator.cc"],
    hdrs = ["lease_cache_for_cooperator.h"],
    deps = [
        ":btree_node_identifier",
        ":cooperator_cc_grpc",
        ":coordinator_cc_grpc",
        ":coordinator_cc_proto",
        ":rpc_security",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal/container:intrusive_red_black_tree",
        "//tensorstore/internal/grpc:utils",
        "//tensorstore/internal/grpc/clientauth:authentication_strategy",
        "//tensorstore/internal/grpc/clientauth:create_channel",
        "//tensorstore/internal/log:verbose_flag",
        "//tensorstore/kvstore:key_range",
        "//tensorstore/proto:encode_time",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/container:flat_hash_map",
        "@abseil-cpp//absl/log:absl_check",
        "@abseil-cpp//absl/log:absl_log",
        "@abseil-cpp//absl/meta:type_traits",
        "@abseil-cpp//absl/synchronization",
        "@abseil-cpp//absl/time",
        "@grpc//:grpc++",
        "@grpc//:grpc_security_base",
    ],
)

tensorstore_cc_library(
    name = "btree_node_identifier",
    srcs = ["btree_node_identifier.cc"],
    hdrs = ["btree_node_identifier.h"],
    deps = [
        "//tensorstore/kvstore:key_range",
        "//tensorstore/kvstore/ocdbt/format",
        "//tensorstore/util:endian",
        "@blake3",
    ],
)

tensorstore_cc_library(
    name = "btree_node_write_mutation",
    srcs = ["btree_node_write_mutation.cc"],
    hdrs = ["btree_node_write_mutation.h"],
    deps = [
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal/riegeli:delimited",
        "//tensorstore/kvstore:generation",
        "//tensorstore/kvstore:key_range",
        "//tensorstore/kvstore/ocdbt/format",
        "//tensorstore/util:span",
        "@abseil-cpp//absl/status",
        "@riegeli//riegeli/bytes:reader",
        "@riegeli//riegeli/bytes:writer",
    ],
)

tensorstore_cc_library(
    name = "cooperator",
    srcs = [
        "cooperator_commit_mutations.cc",
        "cooperator_get_manifest.cc",
        "cooperator_impl.cc",
        "cooperator_impl.h",
        "cooperator_start.cc",
        "cooperator_submit_mutation_batch.cc",
    ],
    hdrs = ["cooperator.h"],
    deps = [
        ":btree_node_identifier",
        ":btree_node_write_mutation",
        ":cooperator_cc_grpc",
        ":cooperator_cc_proto",
        ":coordinator_cc_grpc",
        ":lease_cache_for_cooperator",
        ":rpc_security",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:mutex",
        "//tensorstore/internal/container:heterogeneous_container",
        "//tensorstore/internal/grpc:utils",
        "//tensorstore/internal/grpc/clientauth:create_channel",
        "//tensorstore/internal/log:verbose_flag",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore:generation",
        "//tensorstore/kvstore:key_range",
        "//tensorstore/kvstore/ocdbt:io_handle",
        "//tensorstore/kvstore/ocdbt/format",
        "//tensorstore/kvstore/ocdbt/non_distributed:create_new_manifest",
        "//tensorstore/kvstore/ocdbt/non_distributed:storage_generation",
        "//tensorstore/kvstore/ocdbt/non_distributed:write_nodes",
        "//tensorstore/util:bit_span",
        "//tensorstore/util:bit_vec",
        "//tensorstore/util:division",
        "//tensorstore/util:executor",
        "//tensorstore/util:future",
        "//tensorstore/util:quote_string",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/container:flat_hash_map",
        "@abseil-cpp//absl/log:absl_log",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/synchronization",
        "@abseil-cpp//absl/time",
        "@grpc//:grpc++",
        "@riegeli//riegeli/bytes:string_reader",
        "@riegeli//riegeli/bytes:string_writer",
    ],
)

tensorstore_cc_test(
    name = "cooperator_server_test",
    size = "small",
    srcs = ["cooperator_server_test.cc"],
    tags = ["cpu:2"],
    deps = [
        ":cooperator",
        ":coordinator_server",
        ":rpc_security",
        "//tensorstore:context",
        "//tensorstore/internal:data_copy_concurrency_resource",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal/cache",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore/memory",
        "//tensorstore/kvstore/ocdbt:config",
        "//tensorstore/kvstore/ocdbt:io_handle",
        "//tensorstore/kvstore/ocdbt/io:io_handle_impl",
        "//tensorstore/util:result",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/time",
        "@googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "btree_writer",
    srcs = ["btree_writer.cc"],
    hdrs = ["btree_writer.h"],
    deps = [
        ":btree_node_identifier",
        ":btree_node_write_mutation",
        ":cooperator",
        ":rpc_security",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:mutex",
        "//tensorstore/internal/log:verbose_flag",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore:generation",
        "//tensorstore/kvstore:key_range",
        "//tensorstore/kvstore/ocdbt:btree_writer",
        "//tensorstore/kvstore/ocdbt:io_handle",
        "//tensorstore/kvstore/ocdbt/format",
        "//tensorstore/kvstore/ocdbt/non_distributed:btree_writer",
        "//tensorstore/kvstore/ocdbt/non_distributed:storage_generation",
        "//tensorstore/util:bit_vec",
        "//tensorstore/util:executor",
        "//tensorstore/util:future",
        "//tensorstore/util:quote_string",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/log:absl_log",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@abseil-cpp//absl/synchronization",
        "@abseil-cpp//absl/time",
        "@blake3",
    ],
)

tensorstore_cc_test(
    name = "driver_test",
    size = "small",
    srcs = ["driver_test.cc"],
    tags = ["cpu:2"],
    deps = [
        ":coordinator_server",
        "//tensorstore:context",
        "//tensorstore/internal:global_initializer",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal/testing:random_seed",
        "//tensorstore/internal/testing:scoped_directory",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore:test_util",
        "//tensorstore/kvstore/file",
        "//tensorstore/kvstore/memory",
        "//tensorstore/kvstore/ocdbt",
        "//tensorstore/kvstore/ocdbt:test_util",
        "//tensorstore/kvstore/ocdbt/format",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:status_testutil",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/random",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@abseil-cpp//absl/strings:str_format",
        "@googletest//:gtest_main",
        "@nlohmann_json//:json",
    ],
)

tensorstore_cc_library(
    name = "rpc_security",
    srcs = ["rpc_security.cc"],
    hdrs = [
        "rpc_security.h",
        "rpc_security_registry.h",
    ],
    deps = [
        "//tensorstore:json_serialization_options",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:json_registry",
        "//tensorstore/internal/cache_key",
        "//tensorstore/internal/grpc/clientauth:authentication_strategy",
        "//tensorstore/internal/grpc/clientauth:channel_authentication",
        "//tensorstore/internal/grpc/serverauth:default_strategy",
        "//tensorstore/internal/grpc/serverauth:strategy",
        "//tensorstore/internal/json_binding",
        "//tensorstore/internal/json_binding:bindable",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/base:no_destructor",
        "@abseil-cpp//absl/status",
        "@grpc//:grpc++",
        "@nlohmann_json//:json",
    ],
)
