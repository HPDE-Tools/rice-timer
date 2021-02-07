// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

// Reason for centralizing: Each priority number alone does not make sense; it does only when it's
// compared to those of other tasks. Having a single place to look up all the priorities makes it
// clear which task has higher priority.

constexpr int kPriorityLogging = 1;
constexpr int kPrioritySdCard = 2;
constexpr int kPriorityUi = 3;
constexpr int kPriorityCan = 4;
constexpr int kPriorityGpsd = 5;
constexpr int kPriorityImu = 6;
