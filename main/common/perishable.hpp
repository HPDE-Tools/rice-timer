#pragma once

#include <atomic>
#include <optional>
#include <type_traits>

#include "common/scope_guard.hpp"
#include "common/utils.hpp"

template <typename TData, typename TTime>
class Perishable {
 public:
  using TTimeDiff = std::make_signed_t<TTime>;

  struct Content {
    TData data;
    TTime time;
  };

  Perishable() {}
  Perishable(const TData& data, TTime time) : content_({data, time}) {}
  Perishable(TData&& data, TTime time) : content_({data, time}) {}
  void Reset() { content_.reset(); }
  void Set(const TData& data, TTime time) { content_ = Content{data, time}; }
  std::optional<Content> Get() const {
    vPortEnterCritical(&lock_);
    SCOPE_EXIT { vPortExitCritical(&lock_); };
    return content_;
  }
  std::optional<Content> Check(TTime now, TTimeDiff ttl) {
    vPortEnterCritical(&lock_);
    SCOPE_EXIT { vPortExitCritical(&lock_); };
    if (content_) {
      if (SignedMinus(now, content_->time) >= ttl) {
        content_.reset();
      }
    }
    return content_;
  }

 private:
  std::optional<Content> content_{};
  mutable portMUX_TYPE lock_ = portMUX_INITIALIZER_UNLOCKED;
};
