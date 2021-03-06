//===--- AIX.h - AIX ToolChain Implementations ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_AIX_H
#define LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_AIX_H

#include "clang/Driver/Tool.h"
#include "clang/Driver/ToolChain.h"

namespace clang {
namespace driver {
namespace tools {

/// aix -- Directly call system default linker.
// TODO: Enable direct call to system default assembler.
namespace aix {

class LLVM_LIBRARY_VISIBILITY Linker : public Tool {
public:
  Linker(const ToolChain &TC) : Tool("aix::Linker", "linker", TC) {}

  bool hasIntegratedCPP() const override { return false; }
  bool isLinkJob() const override { return true; }

  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};

} // end namespace aix

} // end namespace tools
} // end namespace driver
} // end namespace clang

namespace clang {
namespace driver {
namespace toolchains {

class LLVM_LIBRARY_VISIBILITY AIX : public ToolChain {
public:
  AIX(const Driver &D, const llvm::Triple &Triple,
      const llvm::opt::ArgList &Args);

  bool isPICDefault() const override { return true; }
  bool isPIEDefault() const override { return false; }
  bool isPICDefaultForced() const override { return true; }

protected:
  Tool *buildLinker() const override;
};

} // end namespace toolchains
} // end namespace driver
} // end namespace clang

#endif // LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_AIX_H
