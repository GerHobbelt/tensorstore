# N5 TensorStore driver

load("//bazel:tensorstore.bzl", "tensorstore_cc_library", "tensorstore_cc_test")
load("//docs:doctest.bzl", "doctest_test")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

DOCTEST_SOURCES = glob([
    "**/*.rst",
    "**/*.yml",
])

doctest_test(
    name = "doctest_test",
    srcs = DOCTEST_SOURCES,
)

filegroup(
    name = "doc_sources",
    srcs = DOCTEST_SOURCES,
)

tensorstore_cc_library(
    name = "n5",
    deps = [
        ":blosc_compressor",
        ":bzip2_compressor",
        ":driver",
        ":gzip_compressor",
        ":xz_compressor",
        ":zstd_compressor",
    ],
)

tensorstore_cc_library(
    name = "blosc_compressor",
    srcs = ["blosc_compressor.cc"],
    deps = [
        ":compressor",
        "//tensorstore/internal/compression:blosc_compressor",
        "//tensorstore/internal/json_binding",
    ],
    alwayslink = 1,
)

tensorstore_cc_test(
    name = "blosc_compressor_test",
    size = "small",
    srcs = ["blosc_compressor_test.cc"],
    deps = [
        ":blosc_compressor",
        ":compressor",
        ":metadata",
        "//tensorstore:array",
        "//tensorstore:index",
        "//tensorstore/internal/json_binding:gtest",
        "//tensorstore/internal/testing:json_gtest",
        "//tensorstore/util:status_testutil",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
        "@nlohmann_json//:json",
    ],
)

tensorstore_cc_library(
    name = "bzip2_compressor",
    srcs = ["bzip2_compressor.cc"],
    deps = [
        ":compressor",
        "//tensorstore/internal/compression:bzip2_compressor",
        "//tensorstore/internal/json_binding",
    ],
    alwayslink = 1,
)

tensorstore_cc_test(
    name = "bzip2_compressor_test",
    size = "small",
    srcs = ["bzip2_compressor_test.cc"],
    deps = [
        ":bzip2_compressor",
        ":compressor",
        ":metadata",
        "//tensorstore:array",
        "//tensorstore:index",
        "//tensorstore/internal/json_binding:gtest",
        "//tensorstore/internal/testing:json_gtest",
        "//tensorstore/util:span",
        "//tensorstore/util:status_testutil",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "compressor",
    srcs = ["compressor.cc"],
    hdrs = [
        "compressor.h",
        "compressor_registry.h",
    ],
    deps = [
        "//tensorstore/internal:json_registry",
        "//tensorstore/internal/compression:json_specified_compressor",
        "//tensorstore/internal/json_binding",
        "//tensorstore/internal/json_binding:bindable",
        "@abseil-cpp//absl/base:no_destructor",
    ],
)

tensorstore_cc_test(
    name = "driver_test",
    size = "small",
    srcs = ["driver_test.cc"],
    deps = [
        ":driver",
        "//tensorstore",
        "//tensorstore:array",
        "//tensorstore:box",
        "//tensorstore:chunk_layout",
        "//tensorstore:codec_spec",
        "//tensorstore:context",
        "//tensorstore:contiguous_layout",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore:json_serialization_options_base",
        "//tensorstore:open",
        "//tensorstore:open_mode",
        "//tensorstore:rank",
        "//tensorstore:resize_options",
        "//tensorstore:schema",
        "//tensorstore:spec",
        "//tensorstore:strided_layout",
        "//tensorstore/driver:driver_testutil",
        "//tensorstore/driver/zarr",
        "//tensorstore/index_space:dim_expression",
        "//tensorstore/index_space:index_transform",
        "//tensorstore/internal:global_initializer",
        "//tensorstore/internal/testing:json_gtest",
        "//tensorstore/internal/testing:parse_json_matches",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore:test_matchers",
        "//tensorstore/kvstore:test_util",
        "//tensorstore/kvstore/file",
        "//tensorstore/kvstore/memory",
        "//tensorstore/util:dimension_set",
        "//tensorstore/util:span",
        "//tensorstore/util:status_testutil",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
        "@nlohmann_json//:json",
    ],
)

tensorstore_cc_test(
    name = "golden_file_test",
    size = "small",
    srcs = ["golden_file_test.cc"],
    args = [
        "--tensorstore_test_data_dir=" +
        package_name() + "/testdata",
    ],
    data = [":testdata"],
    deps = [
        ":blosc_compressor",
        ":bzip2_compressor",
        ":driver",
        ":gzip_compressor",
        ":xz_compressor",
        "//tensorstore",
        "//tensorstore:array",
        "//tensorstore:context",
        "//tensorstore:index",
        "//tensorstore:open",
        "//tensorstore:open_mode",
        "//tensorstore/internal:path",
        "//tensorstore/kvstore/file",
        "//tensorstore/util:status_testutil",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/log:absl_log",
        "@googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "gzip_compressor",
    srcs = ["gzip_compressor.cc"],
    deps = [
        ":compressor",
        "//tensorstore/internal/compression:zlib_compressor",
        "//tensorstore/internal/json_binding",
    ],
    alwayslink = 1,
)

tensorstore_cc_test(
    name = "gzip_compressor_test",
    size = "small",
    srcs = ["gzip_compressor_test.cc"],
    deps = [
        ":compressor",
        ":gzip_compressor",
        ":metadata",
        "//tensorstore:array",
        "//tensorstore:index",
        "//tensorstore/internal/json_binding:gtest",
        "//tensorstore/util:status_testutil",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "metadata",
    srcs = ["metadata.cc"],
    hdrs = ["metadata.h"],
    deps = [
        ":blosc_compressor",
        ":compressor",
        "//tensorstore:array",
        "//tensorstore:box",
        "//tensorstore:chunk_layout",
        "//tensorstore:codec_spec",
        "//tensorstore:contiguous_layout",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore:json_serialization_options_base",
        "//tensorstore:rank",
        "//tensorstore:schema",
        "//tensorstore:strided_layout",
        "//tensorstore/index_space:dimension_units",
        "//tensorstore/index_space:index_transform",
        "//tensorstore/internal:json_metadata_matching",
        "//tensorstore/internal/json:same",
        "//tensorstore/internal/json_binding",
        "//tensorstore/internal/json_binding:bindable",
        "//tensorstore/internal/json_binding:data_type",
        "//tensorstore/internal/json_binding:dimension_indexed",
        "//tensorstore/internal/meta:type_traits",
        "//tensorstore/internal/riegeli:array_endian_codec",
        "//tensorstore/serialization",
        "//tensorstore/serialization:json",
        "//tensorstore/util:constant_vector",
        "//tensorstore/util:endian",
        "//tensorstore/util:extents",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "//tensorstore/util:unit",
        "//tensorstore/util/garbage_collection",
        "@abseil-cpp//absl/algorithm:container",
        "@abseil-cpp//absl/meta:type_traits",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/strings:cord",
        "@nlohmann_json//:json",
        "@riegeli//riegeli/bytes:cord_reader",
        "@riegeli//riegeli/bytes:cord_writer",
        "@riegeli//riegeli/bytes:reader",
        "@riegeli//riegeli/bytes:writer",
        "@riegeli//riegeli/endian:endian_reading",
        "@riegeli//riegeli/endian:endian_writing",
    ],
    alwayslink = 1,
)

tensorstore_cc_test(
    name = "metadata_test",
    size = "small",
    srcs = ["metadata_test.cc"],
    deps = [
        ":blosc_compressor",
        ":metadata",
        "//tensorstore:array",
        "//tensorstore:codec_spec",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore/internal/json_binding:gtest",
        "//tensorstore/internal/testing:json_gtest",
        "//tensorstore/util:status_testutil",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
        "@nlohmann_json//:json",
    ],
)

tensorstore_cc_library(
    name = "driver",
    srcs = ["driver.cc"],
    deps = [
        ":metadata",
        "//tensorstore:array",
        "//tensorstore:array_storage_statistics",
        "//tensorstore:box",
        "//tensorstore:chunk_layout",
        "//tensorstore:codec_spec",
        "//tensorstore:contiguous_layout",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore:index_interval",
        "//tensorstore:open_mode",
        "//tensorstore:open_options",
        "//tensorstore:rank",
        "//tensorstore:strided_layout",
        "//tensorstore:transaction",
        "//tensorstore/driver",
        "//tensorstore/driver:chunk_cache_driver",
        "//tensorstore/driver:kvs_backed_chunk_driver",
        "//tensorstore/index_space:dimension_units",
        "//tensorstore/index_space:index_transform",
        "//tensorstore/internal:async_write_array",
        "//tensorstore/internal:chunk_grid_specification",
        "//tensorstore/internal:grid_storage_statistics",
        "//tensorstore/internal/cache",
        "//tensorstore/internal/cache_key",
        "//tensorstore/internal/json_binding",
        "//tensorstore/kvstore",
        "//tensorstore/util:constant_vector",
        "//tensorstore/util:dimension_set",
        "//tensorstore/util:executor",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "//tensorstore/util/garbage_collection",
        "@abseil-cpp//absl/container:inlined_vector",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@nlohmann_json//:json",
    ],
    alwayslink = 1,
)

filegroup(
    name = "testdata",
    srcs = glob(
        include = [
            "testdata/**",
        ],
        exclude = ["testdata/*.py"],
    ),
)

tensorstore_cc_library(
    name = "xz_compressor",
    srcs = ["xz_compressor.cc"],
    deps = [
        ":compressor",
        "//tensorstore/internal/compression:xz_compressor",
        "//tensorstore/internal/json_binding",
    ],
    alwayslink = 1,
)

tensorstore_cc_test(
    name = "xz_compressor_test",
    size = "small",
    srcs = ["xz_compressor_test.cc"],
    deps = [
        ":compressor",
        ":metadata",
        ":xz_compressor",
        "//tensorstore:array",
        "//tensorstore:index",
        "//tensorstore/internal/json_binding:gtest",
        "//tensorstore/internal/testing:json_gtest",
        "//tensorstore/util:span",
        "//tensorstore/util:status_testutil",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "zstd_compressor",
    srcs = ["zstd_compressor.cc"],
    deps = [
        ":compressor",
        "//tensorstore/internal/compression:zstd_compressor",
        "//tensorstore/internal/json_binding",
        "@riegeli//riegeli/zstd:zstd_writer",
    ],
    alwayslink = 1,
)

tensorstore_cc_test(
    name = "zstd_compressor_test",
    srcs = ["zstd_compressor_test.cc"],
    deps = [
        ":compressor",
        ":zstd_compressor",
        "//tensorstore/util:status_testutil",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
        "@nlohmann_json//:json",
    ],
)

tensorstore_cc_test(
    name = "storage_statistics_test",
    size = "small",
    srcs = ["storage_statistics_test.cc"],
    deps = [
        ":driver",
        "//tensorstore/driver/zarr:storage_statistics_test_util",
        "@googletest//:gtest_main",
    ],
)
