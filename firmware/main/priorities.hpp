// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

// Reason for centralizing: Unlike stack size, each priority number alone does not make sense; it
// does only when it's compared to those of other tasks. Having a single place to look up all the
// priorities puts all the numbers into context.

constexpr int kPriorityBackground = 0;
constexpr int kPriorityLogger = 1;
constexpr int kPrioritySdCard = 2;
constexpr int kPriorityOnboardAnalysis = 3;
constexpr int kPriorityUi = 4;
constexpr int kPriorityCan = 5;
constexpr int kPriorityGpsd = 6;
constexpr int kPriorityImu = 7;
