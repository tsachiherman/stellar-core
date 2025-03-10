#pragma once

// Copyright 2022 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/Logging.h"

// This file just contains "shims" which are global C++ functions that cxx.rs
// can understand how to call, that themselves call through to C++ code in some
// way that is too complex for cxx.rs to understand (static member calls,
// constructors, etc). We isolate them in this file to avoid polluting normal
// C++ code with too much interop glue.

namespace rust
{
inline namespace cxxbridge1
{
template <typename T> class Vec;
}
}
struct XDRBuf;
namespace stellar
{
class Application;
struct PreflightResults;
struct PreflightCallbacks
{
    Application& mApp;
    PreflightResults& mRes;
    PreflightCallbacks(Application& app, PreflightResults& res)
        : mApp(app), mRes(res){};
    XDRBuf get_ledger_entry(rust::Vec<uint8_t> const& key);
    bool has_ledger_entry(rust::Vec<uint8_t> const& key);
    void set_result_value(rust::Vec<uint8_t> const& val);
    void set_result_footprint(rust::Vec<uint8_t> const& footprint);
    void set_result_cpu_insns(uint64_t cpu);
    void set_result_mem_bytes(uint64_t mem);
};

inline bool
shim_isLogLevelAtLeast(std::string const& partition, LogLevel level)
{
    return Logging::isLogLevelAtLeast(partition, level);
}

inline void
shim_logAtPartitionAndLevel(std::string const& partition, LogLevel level,
                            std::string const& msg)
{
    Logging::logAtPartitionAndLevel(partition, level, msg);
}
}
