; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "armv4t-unknown-linux-gnu"

@.str = private unnamed_addr constant [14 x i8] c"hello world!\0A\00", align 1

; Function Attrs: noinline nounwind optnone
define arm_aapcscc i32 @main() #0 !dbg !8 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  %call = call arm_aapcscc i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0)), !dbg !12
  ret i32 0, !dbg !13
}

declare arm_aapcscc i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="arm7tdmi" "target-features"="+soft-float,+strict-align,-crypto,-neon,-thumb-mode" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="arm7tdmi" "target-features"="+soft-float,+strict-align,-crypto,-neon,-thumb-mode" "unsafe-fp-math"="false" "use-soft-float"="true" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 6.0.0 (https://llvm.org/git/clang.git 257d24609e764e401cd8e727495a3e569f2f8f54) (https://llvm.org/git/llvm.git ca4d818dd00d0393cd964ffaf0901429b46dd9b1)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "test.c", directory: "/home/airobot/Desktop/dev")
!2 = !{}
!3 = !{i32 2, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 1, !"min_enum_size", i32 4}
!7 = !{!"clang version 6.0.0 (https://llvm.org/git/clang.git 257d24609e764e401cd8e727495a3e569f2f8f54) (https://llvm.org/git/llvm.git ca4d818dd00d0393cd964ffaf0901429b46dd9b1)"}
!8 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !9, isLocal: false, isDefinition: true, scopeLine: 4, isOptimized: false, unit: !0, variables: !2)
!9 = !DISubroutineType(types: !10)
!10 = !{!11}
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DILocation(line: 5, column: 2, scope: !8)
!13 = !DILocation(line: 6, column: 2, scope: !8)
