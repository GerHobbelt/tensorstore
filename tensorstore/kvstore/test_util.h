// Copyright 2020 The TensorStore Authors
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

#ifndef TENSORSTORE_KVSTORE_TEST_UTIL_H_
#define TENSORSTORE_KVSTORE_TEST_UTIL_H_

#include <stddef.h>

#include <functional>
#include <map>
#include <string>
#include <string_view>

#include "absl/functional/function_ref.h"
#include "absl/strings/cord.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include <nlohmann/json.hpp>
#include "tensorstore/context.h"
#include "tensorstore/json_serialization_options.h"
#include "tensorstore/kvstore/batch_util.h"
#include "tensorstore/kvstore/kvstore.h"
#include "tensorstore/kvstore/read_result.h"
#include "tensorstore/util/result.h"

namespace tensorstore {
namespace internal {

/// Returns the current time as of the start of the call, and waits until that
/// time is no longer the current time.
///
/// This is used to ensure consistent testing.
inline absl::Time UniqueNow(absl::Duration epsilon = absl::Nanoseconds(1)) {
  absl::Time t = absl::Now();
  do {
    absl::SleepFor(absl::Milliseconds(1));
  } while (absl::Now() < t + epsilon);
  return t;
}

/// Test read operations on `store`, where `key` is `expected_value`, and
/// `missing_key` does not exist.
void TestKeyValueStoreReadOps(const KvStore& store, std::string key,
                              absl::Cord expected_value,
                              std::string missing_key);

struct KeyValueStoreOpsTestParameters {
  // Name of test suite.
  std::string test_name;

  // Function that invokes a callback with the store.
  //
  // The `get_store` function can perform any necessary cleanup after the
  // callback returns.
  std::function<void(absl::FunctionRef<void(const KvStore& store)>)> get_store;

  // For kvstore adapters, returns an adapter on top of the base store.
  //
  // For non-kvstore adapters, should be left as a null function.
  std::function<void(const KvStore& base,
                     absl::FunctionRef<void(const KvStore& store)>)>
      get_store_adapter;

  // Minimum size of value to use for read/write tests.
  size_t value_size = 0;

  // Maps arbitrary strings (which are nonetheless valid file paths) to keys in
  // the format expected by `store`. For stores that support file paths as keys,
  // `get_key` can simply be the identity function. This function must ensure
  // that a given input key always maps to the same output key, and distinct
  // input keys always map to distinct output keys.
  std::function<std::string(std::string key)> get_key;

  // Perform transactional tests using an atomic_isolated transaction rather
  // than an isolated transaction.
  bool atomic_transaction = false;

  // Include DeleteRange tests.
  bool test_delete_range = true;

  // Include CopyRange tests.
  bool test_copy_range = false;

  // Include List tests.
  bool test_list = true;

  // If `test_list == true`, test list without an extra prefix. This fails if
  // keys remain across `get_store` calls.
  bool test_list_without_prefix = true;

  // Indicates if list is expected to return sizes.
  bool list_match_size = true;

  // If `test_list == true`, test listing with the specified prefix also.
  std::string test_list_prefix = "p/";

  // Test transactional list operations.
  bool test_transactional_list = true;

  // Test special characters in the key.
  bool test_special_characters = true;
};

/// Registers a suite of tests according to `params`.
void RegisterKeyValueStoreOpsTests(KeyValueStoreOpsTestParameters params);

/// Tests DeleteRange on `store`, which should be empty.
void TestKeyValueStoreDeleteRange(const KvStore& store);

/// Tests DeleteRange on `store`, which should be empty.
void TestKeyValueStoreDeletePrefix(const KvStore& store);

/// Tests DeleteRange on `store`, which should be empty.
void TestKeyValueStoreDeleteRangeToEnd(const KvStore& store);

/// Tests DeleteRange on `store`, which should be empty.
void TestKeyValueStoreDeleteRangeFromBeginning(const KvStore& store);

/// Tests CopyRange on `store`, which should be empty.
void TestKeyValueStoreCopyRange(const KvStore& store);

/// Tests List on `store`, which should be empty.
void TestKeyValueStoreList(const KvStore& store, bool match_size = true);

struct KeyValueStoreSpecRoundtripOptions {
  // Spec that round trips with default options.
  ::nlohmann::json full_spec;

  // Specifies spec for initially creating the kvstore.  Defaults to
  // `full_spec`.
  ::nlohmann::json create_spec = ::nlohmann::json::value_t::discarded;

  // Result of calling `base()` on full spec.  The default value of `discarded`
  // means a null spec.
  ::nlohmann::json full_base_spec = ::nlohmann::json::value_t::discarded;

  // Specifies spec returned when `MinimalSpec{true}` is specified.  Defaults to
  // `full_spec`.
  ::nlohmann::json minimal_spec = ::nlohmann::json::value_t::discarded;
  kvstore::SpecRequestOptions spec_request_options;
  JsonSerializationOptions json_serialization_options;

  Context context = Context::Default();

  // Checks reading and writing.
  bool check_write_read = true;

  // Checks that data persists after re-opening from the returned spec.
  // Requires `check_write_read == true`.
  bool check_data_persists = true;

  // Check that the store can be round-tripped through its serialized
  // representation.
  bool check_store_serialization = true;

  // Checks that data can be read/written after round-tripping through
  // serialization.
  //
  // Doesn't work for "memory://".
  bool check_data_after_serialization = true;

  std::string roundtrip_key = "mykey";
  absl::Cord roundtrip_value = absl::Cord("myvalue");
};

/// Tests that the KvStore spec round-trips in several ways.
///
/// - Tests that calling `kvstore::Open` with `options.create_spec` returns a
///   `KvStore` whose `spec()` method returns `options.full_spec`.
///
/// - Tests that applying the `MinimalSpec` option to `option.full_spec` results
///   in `options.minimal_spec`.
///
/// - If `options.check_data_persists`, tests that data persists when re-opened
///   using `options.minimal_spec`.
///
/// - If `options.check_data_persists`, tests that data persists when re-opened
///   using `options.full_spec`.
void TestKeyValueStoreSpecRoundtrip(
    const KeyValueStoreSpecRoundtripOptions& options);

/// Tests that the KvStore spec constructed from `json_spec` corresponds to the
/// URL representation `url`.
void TestKeyValueStoreUrlRoundtrip(::nlohmann::json json_spec,
                                   std::string_view url);

/// Tests that `json_spec` round trips to `normalized_json_spec`.
void TestKeyValueStoreSpecRoundtripNormalize(
    ::nlohmann::json json_spec, ::nlohmann::json normalized_json_spec);

/// Returns the contents of `kv_store` as an `std::map`.
Result<std::map<kvstore::Key, kvstore::Value>> GetMap(const KvStore& store);

struct BatchReadGenericCoalescingTestOptions {
  internal_kvstore_batch::CoalescingOptions coalescing_options;
  std::string metric_prefix;
  bool has_file_open_metric = false;
};

void TestBatchReadGenericCoalescing(
    const KvStore& store, const BatchReadGenericCoalescingTestOptions& options);

struct TestConcurrentWritesOptions {
  size_t num_iterations = 100;
  size_t num_threads = 4;
  std::string key = "test";
  std::function<KvStore()> get_store;
};

void TestConcurrentWrites(const TestConcurrentWritesOptions& options);

}  // namespace internal
}  // namespace tensorstore

#endif  // TENSORSTORE_KVSTORE_TEST_UTIL_H_
