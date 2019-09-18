; RUN: llc < %s -march=tvm | tvm-testrun --no-trace --entry check_main | FileCheck %s -check-prefix=CHECK-RUN

target datalayout = "E-S257-i1:257:257-i8:257:257-i16:257:257-i32:257:257-i64:257:257-i257:257:257-p:257:257-a:257:257"
target triple = "tvm"

; Function Attrs: noinline norecurse nounwind
define dso_local void @f(i257* nocapture %val) local_unnamed_addr noinline norecurse nounwind {
entry:
  %0 = load i257, i257* %val, align 1
  %inc = add nsw i257 %0, 1
  store i257 %inc, i257* %val, align 1
  ret void
}

; Function Attrs: nounwind
define dso_local i257 @check_main() local_unnamed_addr nounwind {
; CHECK-RUN-NOT: custom error

entry:
  %var = alloca i257, align 1
  store i257 0, i257* %var, align 1
  call void @f(i257* nonnull %var)
  %rv = load i257, i257* %var, align 1
  %not_eq = sub i257 %rv, 1
  call void @llvm.tvm.throwif(i257 %not_eq, i257 13)
  ret i257 %rv
}

declare void @llvm.tvm.throwif(i257 %cond, i257 %exception)

