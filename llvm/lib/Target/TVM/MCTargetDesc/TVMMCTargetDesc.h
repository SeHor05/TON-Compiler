//===-- TVMMCTargetDesc.h - TVM Target Descriptions -------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides TVM specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_TVM_MCTARGETDESC_TVMMCTARGETDESC_H
#define LLVM_LIB_TARGET_TVM_MCTARGETDESC_TVMMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class Target;

Target &getTheTVMTarget();

} // End llvm namespace

// Defines symbolic names for CapriMPU registers.
// This defines a mapping from register name to register number.
#define GET_REGINFO_ENUM
#include "TVMGenRegisterInfo.inc"

// Defines symbolic names for the CapriMPU instructions.
#define GET_INSTRINFO_ENUM
#include "TVMGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "TVMGenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_TVM_MCTARGETDESC_TVMMCTARGETDESC_H
