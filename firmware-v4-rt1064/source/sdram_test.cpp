#include "sdram_test.hpp"

#include <algorithm>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory>
#include <optional>
#include <random>

#include "fsl_gpt.h"
#include "fsl_trng.h"

#include "scope_guard.hpp"
#include "sdram_config.hpp"
#include "utils.hpp"

std::optional<std::mt19937> MakeNewPrng() {
  uint32_t seed;
  if (const status_t status = TRNG_GetRandomData(TRNG, &seed, sizeof(seed)); status
      != kStatus_Success) {
    printf("MakeNewPrng error: %d\n", static_cast<int>(status));
    return {};
  }
  printf("Seed: 0x%08" PRIX32 "\n", seed);
  return std::mt19937(seed);
}

void TestSdramSeqWrite4B() {
  uint32_t volatile* const sdram = reinterpret_cast<uint32_t volatile*>(kSdramBase);
  constexpr int kSdramNumWords = kSdramNumBytes / sizeof(uint32_t);

  constexpr int kPatternNumWords = 1024;

  std::mt19937 rng1 = MakeNewPrng().value();
  static std::array<uint32_t, kPatternNumWords> pattern;
  std::generate(pattern.begin(), pattern.end(), [&rng1]() {
    return rng1();
  });

  printf("TestSdramSeqWrite4B: Write start\n");
  const uint32_t t0 = GPT_GetCurrentTimerCount(GPT2);
  for (int i = 0; i < kSdramNumWords; i++) {
    sdram[i] = pattern[i % pattern.size()];
  }
  const uint32_t t1 = GPT_GetCurrentTimerCount(GPT2);
  printf("TestSdramSeqWrite4B: Write done --- %" PRId32 " us\n", SignedMinus(t1, t0));

  while (SignedMinus(GPT_GetCurrentTimerCount(GPT2), t1) < 1'000'000)
    ;

  printf("TestSdramSeqWrite4B: Read start\n");
  const uint32_t t2 = GPT_GetCurrentTimerCount(GPT2);
  for (int i = 0; i < kSdramNumWords; i++) {
    const uint32_t expected = pattern[i % pattern.size()];
    const uint32_t actual = sdram[i];
    if (actual != expected) {
      printf(
          "TestSdramSeqWrite4B: First mismatch at i=%08x"
          " expected=%08" PRIx32 " actual=%08" PRIx32 "\n",
          i, expected, actual);
      return;
    }
  }
  const uint32_t t3 = GPT_GetCurrentTimerCount(GPT2);
  printf("TestSdramSeqWrite4B: Read done --- %" PRId32 " us\n", SignedMinus(t3, t2));

  printf("TestSdramSeqWrite4B: Success\n");
}

void TestSdramRandomAccess4B() {
  uint32_t volatile* const sdram = reinterpret_cast<uint32_t volatile*>(kSdramBase);
  constexpr int kSdramNumWords = kSdramNumBytes / sizeof(uint32_t);

  constexpr int kMaxNumAccesses = 1000;
  constexpr int kRepeats = 1000;

  std::mt19937 rng_index = MakeNewPrng().value();
  std::mt19937 rng_write = MakeNewPrng().value();
  std::mt19937 rng_read = rng_write;
  std::uniform_int_distribution<int> dist_index(0, kSdramNumWords);

  static std::array<int, kMaxNumAccesses> indices;
  std::generate(indices.begin(), indices.end(), [&]() {
    return dist_index(rng_index);
  });
  int num_unique_indices = 0;

  // O(N^2) is okay for now
  for (int i = 0; i < kMaxNumAccesses; i++) {
    if (std::find(indices.begin(), indices.begin() + i, indices[i]) == indices.begin() + i) {
      indices[num_unique_indices++] = indices[i];
    }
  }
  printf("TestSdramRandomAccess4B: %d unique indices\n", num_unique_indices);

  printf("TestSdramRandomAccess4B: Write start\n");
  const uint32_t t0 = GPT_GetCurrentTimerCount(GPT2);
  for (int repeat = 0; repeat < kRepeats; repeat++) {
    for (const int j : indices) {
      sdram[j] = rng_write();
    }
  }
  const uint32_t t1 = GPT_GetCurrentTimerCount(GPT2);
  printf("TestSdramRandomAccess4B: Write done --- %" PRId32 " us\n", SignedMinus(t1, t0));

  while (SignedMinus(GPT_GetCurrentTimerCount(GPT2), t1) < 1'000'000)
    ;

  printf("TestSdramRandomAccess4B: Read start\n");
  const uint32_t t2 = GPT_GetCurrentTimerCount(GPT2);
  volatile static uint32_t dummy;
  for (int repeat = 1; repeat < kRepeats; repeat++) {
    for (int i = 0; i < num_unique_indices; i++) {
      const int j = indices[i];
      dummy = sdram[j];
      dummy ^= rng_read();
    }
  }
  for (int i = 0; i < num_unique_indices; i++) {
    const int j = indices[i];
    const uint32_t expected = rng_read();
    const uint32_t actual = sdram[j];
    if (actual != expected) {
      printf(
          "TestSdramRandomAccess4B: First mismatch at i=0x%08x j=0x%08x"
          " expected=0x%08" PRIx32 " actual=0x%08" PRIx32 "\n",
          i, j, expected, actual);
      return;
    }
  }
  const uint32_t t3 = GPT_GetCurrentTimerCount(GPT2);
  printf("TestSdramRandomAccess4B: Read done --- %" PRId32 " us\n", SignedMinus(t3, t2));

  printf("TestSdramRandomAccess4B: Success\n");
}
