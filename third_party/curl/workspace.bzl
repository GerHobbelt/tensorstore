# Copyright 2020 The TensorStore Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# buildifier: disable=module-docstring

load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load(
    "//third_party:repo.bzl",
    "mirror_url",
    "third_party_http_archive",
)

def repo():
    maybe(
        third_party_http_archive,
        name = "curl",
        doc_name = "curl",
        doc_version = "8.20.0",
        doc_homepage = "https://curl.se/",
        strip_prefix = "curl-8.20.0",
        urls = mirror_url("https://curl.se/download/curl-8.20.0.tar.gz"),
        sha256 = "fc5819cad3f9f5482669adcdc49a782c15f36d2a0715b395b06d9173593d2dc0",
        build_file = Label("//third_party:curl/curl.BUILD.bazel"),
        system_build_file = Label("//third_party:curl/system.BUILD.bazel"),
        cmake_name = "CURL",
        bazel_to_cmake = {},
        cmake_target_mapping = {
            "//:curl": "CURL::libcurl",
        },
    )
