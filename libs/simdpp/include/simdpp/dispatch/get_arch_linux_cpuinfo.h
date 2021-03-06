/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_DISPATCH_GET_ARCH_LINUX_CPUINFO_H
#define LIBSIMDPP_DISPATCH_GET_ARCH_LINUX_CPUINFO_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>
#include <simdpp/dispatch/arch.h>

namespace simdpp {

/** @ingroup simdpp_dispatcher
    Retrieves supported architecture from Linux /proc/cpuinfo file.

    Works on X86 and ARM.
*/
inline Arch get_arch_linux_cpuinfo()
{
    Arch res;

    std::map<std::string, Arch> features;
    std::string ident;

#if defined(__arm__)
    ident = "Features\t";
    features["neon"] = Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP;

#elif defined(__i386__) || defined(__amd64__)
    Arch a_sse2 = Arch::X86_SSE2;
    Arch a_sse3 = a_sse2 | Arch::X86_SSE3;
    Arch a_ssse3 = a_sse3 | Arch::X86_SSSE3;
    Arch a_sse4_1 = a_ssse3 | Arch::X86_SSE4_1;
    Arch a_avx = a_sse4_1 | Arch::X86_AVX;
    Arch a_avx2 = a_avx | Arch::X86_AVX2;
    Arch a_fma3 = a_sse3 | Arch::X86_FMA3;
    Arch a_fma4 = a_sse3 | Arch::X86_FMA4;
    Arch a_xop = a_sse3 | Arch::X86_XOP;

    ident = "flags\t";
    features["sse2"] = a_sse2;
    features["pni"] = a_sse3;
    features["ssse3"] = a_ssse3;
    features["sse4_1"] = a_sse4_1;
    features["avx"] = a_avx;
    features["avx2"] = a_avx2;
    features["fma"] = a_fma3;
    features["fma4"] = a_fma4;
    features["xop"] = a_xop;
#else
    return res;
#endif

    std::ifstream in("/proc/cpuinfo");

    if (!in) {
        return res;
    }

    std::string line;
    while (std::getline(in, line)) {
        // Check whether identification string matches
        if (line.length() < ident.length()) {
            continue;
        }
        auto r = std::mismatch(ident.begin(), ident.end(), line.begin());
        if (r.first != ident.end()) {
            continue;
        }

        // Get the items
        std::istringstream sin(std::string(r.second, line.end()));
        std::vector<std::string> items;

        std::copy(std::istream_iterator<std::string>(sin),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(items));

        // Match items to known features
        for (auto& item : items) {
            auto it = features.find(item);
            if (it == features.end()) {
                continue;
            }
            res |= it->second;
        }
    }

    return res;
}

} // namespace simdpp

#endif
