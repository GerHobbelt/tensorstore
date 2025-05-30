load("//bazel:tensorstore.bzl", "tensorstore_cc_library", "tensorstore_cc_test")

package(default_visibility = [":__subpackages__"])

licenses(["notice"])

tensorstore_cc_library(
    name = "driver_impl",
    hdrs = ["driver_impl.h"],
    deps = [
        "//tensorstore:array",
        "//tensorstore:chunk_layout",
        "//tensorstore:codec_spec",
        "//tensorstore:context",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore:open_mode",
        "//tensorstore:resize_options",
        "//tensorstore:schema",
        "//tensorstore:staleness_bound",
        "//tensorstore:transaction",
        "//tensorstore/driver",
        "//tensorstore/driver:chunk",
        "//tensorstore/index_space:index_transform",
        "//tensorstore/internal:arena",
        "//tensorstore/internal:concurrency_resource",
        "//tensorstore/internal:data_copy_concurrency_resource",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:lock_collection",
        "//tensorstore/internal:nditerable",
        "//tensorstore/internal:nditerable_transformed_array",
        "//tensorstore/internal/cache",
        "//tensorstore/internal/cache:async_cache",
        "//tensorstore/internal/cache:async_initialized_cache_mixin",
        "//tensorstore/internal/cache:cache_pool_resource",
        "//tensorstore/internal/cache:kvs_backed_cache",
        "//tensorstore/internal/cache_key",
        "//tensorstore/internal/json_binding",
        "//tensorstore/internal/json_binding:staleness_bound",
        "//tensorstore/internal/meta:type_traits",
        "//tensorstore/kvstore",
        "//tensorstore/serialization:absl_time",
        "//tensorstore/util:executor",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "//tensorstore/util/execution",
        "//tensorstore/util/execution:any_receiver",
        "//tensorstore/util/garbage_collection",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings:cord",
        "@abseil-cpp//absl/time",
    ],
    alwayslink = True,
)

tensorstore_cc_test(
    name = "image_test",
    size = "small",
    srcs = [
        "driver_test.cc",
        "test_image.cc",
        "test_image.h",
    ],
    deps = [
        "//tensorstore",
        "//tensorstore:array",
        "//tensorstore:box",
        "//tensorstore:context",
        "//tensorstore:index",
        "//tensorstore:open",
        "//tensorstore:open_mode",
        "//tensorstore:strided_layout",
        "//tensorstore:transaction",
        "//tensorstore/driver/image/avif",  # build_cleaner: keep
        "//tensorstore/driver/image/bmp",  # build_cleaner: keep
        "//tensorstore/driver/image/jpeg",  # build_cleaner: keep
        "//tensorstore/driver/image/png",  # build_cleaner: keep
        "//tensorstore/driver/image/tiff",  # build_cleaner: keep
        "//tensorstore/driver/image/webp",  # build_cleaner: keep
        "//tensorstore/index_space:dim_expression",
        "//tensorstore/internal/testing:json_gtest",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore/memory",  # build_cleaner: keep
        "//tensorstore/util:result",
        "//tensorstore/util:status",
        "//tensorstore/util:status_testutil",
        "//tensorstore/util:str_cat",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/strings:cord",
        "@googletest//:gtest_main",
        "@nlohmann_json//:json",
    ],
)
