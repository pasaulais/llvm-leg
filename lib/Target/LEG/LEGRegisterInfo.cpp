//===-- LEGRegisterInfo.cpp - LEG Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the LEG implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "LEGRegisterInfo.h"
#include "LEG.h"
#include "LEGFrameLowering.h"
#include "LEGInstrInfo.h"
#include "LEGMachineFunctionInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#define GET_REGINFO_TARGET_DESC
#include "LEGGenRegisterInfo.inc"

using namespace llvm;

LEGRegisterInfo::LEGRegisterInfo() : LEGGenRegisterInfo(LEG::LR) {}

const uint16_t *
LEGRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const uint16_t CalleeSavedRegs[] = { LEG::R4, LEG::R5, LEG::R6,
                                              LEG::R7, LEG::R8, LEG::R9,
                                              0 };
  return CalleeSavedRegs;
}

BitVector LEGRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(LEG::SP);
  Reserved.set(LEG::LR);
  return Reserved;
}

const uint32_t *LEGRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                      CallingConv::ID) const {
  return CC_Save_RegMask;
}

bool
LEGRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
LEGRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

bool LEGRegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
  return false;
}

void LEGRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  MachineInstr &MI = *II;
  MachineBasicBlock &MBB = *MI.getParent();
  MachineFunction &MF = *MBB.getParent();
  const MachineFrameInfo *MFI = MF.getFrameInfo();
  const TargetInstrInfo *TII = MF.getSubtarget().getInstrInfo();
  MachineOperand &FIOp = MI.getOperand(FIOperandNum);

  // Materialize the offset in the index register.
  unsigned FI = FIOp.getIndex();
  int Offset = MFI->getObjectOffset(FI) + MFI->getStackSize();
  FIOp.ChangeToImmediate(Offset);

  // Compute the index as the stack pointer plus the offset.
  unsigned IndexReg = MI.getOperand(0).getReg();
  BuildMI(MBB, std::next(II), MI.getDebugLoc(), TII->get(LEG::ADDrr), IndexReg)
          .addReg(LEG::SP)
          .addReg(IndexReg);
}

unsigned LEGRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return LEG::SP;
}
