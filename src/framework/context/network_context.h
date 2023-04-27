/**
 * @file network_context.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief NetworkContext
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include "../system/network.h"
#include "tools/crazy_log.h"

// template<typename T>
template <class T>
class NetworkContext {
 private:
  Network* network_ = nullptr;

 protected:
  Network& network() {
    ContainNetwork();
    return *network_;
  }

  bool ContainNetwork() {
    if (network_ == nullptr) {
      CrazyLog::e("NetworkContext", "is null!");
      return false;
    }
    return true;
  }

 public:
  T& SetNetwork(Network& network) {
    network_ = &network;
    return (T&)(*this);
  }
};