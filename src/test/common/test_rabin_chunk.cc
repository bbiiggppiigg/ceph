// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#include <vector>
#include <cstring>

#include "include/types.h"
#include "include/buffer.h"

#include "common/rabin.h"
#include "gtest/gtest.h"

TEST(Rabin, rabin_hash) {
  char data[] = "q";
  uint64_t expected = 0;
  uint64_t result;
  //result = gen_rabin_hash(data, 0);
  //EXPECT_EQ(expected, result);

  char zero_data[1024];
  memset(zero_data, 0, 1024);
  expected = 0;
  result = gen_rabin_hash(zero_data, 0);
  ASSERT_EQ(expected, result);
  ASSERT_EQ(true, end_of_chunk(result));
}

TEST(Rabin, chunk_file) {
  const char *fname = "/bin/bash";
  std::string error;
  bufferlist bl;

  bl.read_file(fname, &error);

  std::vector<bufferlist> out;
  size_t min_chunk = 2000;
  size_t max_chunk = 8000;
  get_rabin_chunks(min_chunk, max_chunk, bl, &out);
  for (size_t i = 0; i < out.size(); ++i) {
    // test if min <= chunk <= max
    uint64_t chunk_size = out[i].length();
    ASSERT_GE(chunk_size , min_chunk);
    ASSERT_LE(chunk_size , max_chunk);
  }
}

