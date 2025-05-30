// Copyright 2023 The TensorStore Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "absl/status/status.h"
#include "tensorstore/driver/zarr3/codec/codec_test_util.h"
#include "tensorstore/util/status_testutil.h"

namespace {

using ::tensorstore::MatchesStatus;
using ::tensorstore::internal_zarr3::CodecRoundTripTestParams;
using ::tensorstore::internal_zarr3::CodecSpecRoundTripTestParams;
using ::tensorstore::internal_zarr3::GetDefaultBytesCodecJson;
using ::tensorstore::internal_zarr3::TestCodecRoundTrip;
using ::tensorstore::internal_zarr3::TestCodecSpecResolve;
using ::tensorstore::internal_zarr3::TestCodecSpecRoundTrip;

TEST(ZstdTest, EndianInferred) {
  CodecSpecRoundTripTestParams p;
  p.orig_spec = {
      {{"name", "zstd"}, {"configuration", {{"level", 7}}}},
  };
  p.expected_spec = {
      GetDefaultBytesCodecJson(),
      {{"name", "zstd"},
       {"configuration", {{"level", 7}, {"checksum", false}}}},
  };
  TestCodecSpecRoundTrip(p);
}

TEST(ZstdTest, Checksum) {
  CodecSpecRoundTripTestParams p;
  p.orig_spec = {
      {{"name", "zstd"}, {"configuration", {{"level", 7}, {"checksum", true}}}},
  };
  p.expected_spec = {
      GetDefaultBytesCodecJson(),
      {{"name", "zstd"}, {"configuration", {{"level", 7}, {"checksum", true}}}},
  };
  TestCodecSpecRoundTrip(p);
}

TEST(ZstdTest, ChecksumOptionalInMetadata) {
  CodecSpecRoundTripTestParams p;
  p.from_json_options.constraints = false;
  p.orig_spec = {
      GetDefaultBytesCodecJson(),
      {{"name", "zstd"}, {"configuration", {{"level", 7}}}},
  };
  p.expected_spec = {
      GetDefaultBytesCodecJson(),
      {{"name", "zstd"},
       {"configuration", {{"level", 7}, {"checksum", false}}}},
  };
  TestCodecSpecRoundTrip(p);
}

TEST(ZstdTest, LevelRequiredInMetadata) {
  CodecSpecRoundTripTestParams p;
  EXPECT_THAT(
      TestCodecSpecResolve(
          {
              GetDefaultBytesCodecJson(),
              {{"name", "zstd"}},
          },
          p.resolve_params, /*constraints=*/false),
      MatchesStatus(absl::StatusCode::kInvalidArgument, ".*\"level\".*"));
}

TEST(ZstdTest, DefaultLevel) {
  CodecSpecRoundTripTestParams p;
  p.orig_spec = {
      {{"name", "zstd"}},
  };
  p.expected_spec = {
      GetDefaultBytesCodecJson(),
      {{"name", "zstd"},
       {"configuration", {{"level", 3}, {"checksum", false}}}},
  };
  TestCodecSpecRoundTrip(p);
}

TEST(ZstdTest, RoundTrip) {
  CodecRoundTripTestParams p;
  p.spec = {"zstd"};
  TestCodecRoundTrip(p);
}

}  // namespace
