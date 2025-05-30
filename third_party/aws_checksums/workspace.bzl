# Copyright 2024 The TensorStore Authors
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
load("//third_party:repo.bzl", "third_party_http_archive")

def repo():
    maybe(
        third_party_http_archive,
        name = "aws_checksums",
        sha256 = "178e8398d98111f29150f7813a70c20ad97ab30be0de02525440355fe84ccb1d",
        strip_prefix = "aws-checksums-0.2.7",
        urls = [
            "https://storage.googleapis.com/tensorstore-bazel-mirror/github.com/awslabs/aws-checksums/archive/v0.2.7.tar.gz",
        ],
        build_file = Label("//third_party:aws_checksums/aws_checksums.BUILD.bazel"),
        cmake_name = "aws_checksums",
        cmake_target_mapping = {
            "@aws_checksums//:aws_checksums": "aws_checksums::aws_checksums",
        },
        bazel_to_cmake = {},
    )
