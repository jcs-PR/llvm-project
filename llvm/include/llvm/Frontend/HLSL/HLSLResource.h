//===- HLSLResource.h - HLSL Resource helper objects ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file This file contains helper objects for working with HLSL Resources.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_FRONTEND_HLSL_HLSLRESOURCE_H
#define LLVM_FRONTEND_HLSL_HLSLRESOURCE_H

#include "llvm/IR/Metadata.h"

namespace llvm {
class GlobalVariable;

namespace hlsl {

enum class ResourceClass : uint8_t {
  SRV = 0,
  UAV,
  CBuffer,
  Sampler,
  Invalid,
  NumClasses = Invalid,
};

// The value ordering of this enumeration is part of the DXIL ABI. Elements
// can only be added to the end, and not removed.
enum class ResourceKind : uint32_t {
  Invalid = 0,
  Texture1D,
  Texture2D,
  Texture2DMS,
  Texture3D,
  TextureCube,
  Texture1DArray,
  Texture2DArray,
  Texture2DMSArray,
  TextureCubeArray,
  TypedBuffer,
  RawBuffer,
  StructuredBuffer,
  CBuffer,
  Sampler,
  TBuffer,
  RTAccelerationStructure,
  FeedbackTexture2D,
  FeedbackTexture2DArray,
  NumEntries,
};

class FrontendResource {
  MDNode *Entry;

public:
  FrontendResource(MDNode *E) : Entry(E) {
    assert(Entry->getNumOperands() == 5 && "Unexpected metadata shape");
  }

  FrontendResource(GlobalVariable *GV, StringRef TypeStr, ResourceKind RK,
                   uint32_t ResIndex, uint32_t Space);

  GlobalVariable *getGlobalVariable();
  StringRef getSourceType();
  ResourceKind getResourceKind();
  uint32_t getResourceIndex();
  uint32_t getSpace();
  MDNode *getMetadata() { return Entry; }
};
} // namespace hlsl
} // namespace llvm

#endif // LLVM_FRONTEND_HLSL_HLSLRESOURCE_H
