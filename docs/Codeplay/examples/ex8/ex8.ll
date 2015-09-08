; ModuleID = 'docs/Codeplay/examples/ex8/ex8.c'
target datalayout = "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-f64:32-a:0:32-n32"
target triple = "leg"

; Function Attrs: noinline nounwind readnone uwtable
define i32 @foo(i32 %x) #0 {
entry:
  %mul = mul nsw i32 %x, 3
  ret i32 %mul
}

; Function Attrs: nounwind readnone uwtable
define i32 @bar(i32 %x) #1 {
entry:
  %sub = add nsw i32 %x, 5
  %call = tail call i32 @foo(i32 %sub)
  ret i32 %call
}

attributes #0 = { noinline nounwind readnone uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
