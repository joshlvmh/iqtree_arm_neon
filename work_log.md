# Mon 6/7

Reading and research into IQ-TREE, Tephra2 and Catalyst. Setting up accounts.

# Tues 7/7

Cloned IQ-TREE repo.  
Loaded ``cmake`` and ARM compiler 19.2.0 modules: env.sh created.  
Created build/ dir.  
Ran ``cmake -DCMAKE_C_COMPILER=armclang -DCMAKE_CXX_COMPILER=armclang++ ..``  
Failed: ``Eigen3 missing.``  
Cloned Eigen3 repo.  
Ran ``cmake -DCMAKE_C_COMPILER=armclang -DCMAKE_CXX_COMPILER=armclang++ -DEIGEN3_INCLUDE_DIR=../../eigen/Eigen ..``  
``cmake`` successful. Build files in /build.  
Ran make  
Failed: ``unrecognized command line option '-msse3'``  
At same point at the end of Chris Edsall's notes.  
Looking into ``sse2neon`` as suggested.  

# Wed 8/7

Added ``|| defined ( __ARM_NEON__ )`` to ``vectorclass/intrset.h`` line 37 to force ``INSTRSET`` to that of ``__SSE4_2__``.  
Used ``find . -type f print0 | xargs -0 sed -E -i '' 's/(x|e|r|t|s|n|w)mmintrin.h/sse2neon.h/g'`` to replace intrincs header files.  
Replaced ``-msse3`` with ``-march=armv8-a+fp+simd+crypto+crc`` in ``/CMakeLists.txt`` on line 324.  
Will install the arm compiler 20.2 and Eigen3 when Catalyst is up and running.  
Need to check /pll in terms of any hardware probing to see if another similar ``INSTRSET`` forcing work around is required.  
Built IQ-TREE successfully on BC4 also. 

# Thur 9/7

Investigated ``cpuid`` assembly.  
Installed arm compiler 20.2 on Catalyst.  
Got login to Isambard sorted.  
Started Eigen install on Catalyst.  

# Fri 9/7

Installed Eigen on Catalyst.  
Built tests with ``gcc-8.2.0/armpl/`` module loaded.  
Tests: 7 fails / 923. Similar results to Isambard, with the addition of 824 and 883.  
```99% tests passed, 7 tests failed out of 923
Label TIme Summary:
Official       = 798.41 sec*proc  (710 tests)
Unsupported    = 90.46  sec*proc  (95 tests)
Total Test Time (real) = 1341.15 sec
The followiing tests FAILED:
         53 - vectorization_logic_1 (Child aborted)
         54 - vectorization_logic_2 (Child aborted)
        824 - cblat2 (Failed)
        829 - NonLinearOptimization (Child aborted)
        883 - mpreal_support (Child aborted)
        888 - sparse_extra_3 (Child aborted)
        915 - levenberg_marquardt (Child aborted)
```
Modified ``__ARM_NEON__`` to ``__ARM_NEON``.  
Started ``cpuid`` function to run on BCP4 for comparison.  

# Mon 10/7

Got ``cpuid`` function working on BCP4.  
Both ``Must compile with SSE2 or higher!`` errors solved: required ``__ARM_NEON`` in /vectorclass/instrset.h and /tree/phylokernelsse.cpp.  
Added ``#ifdef defined ( __ARM_NEON )`` in ``cpuid`` functions to force SSE4.2 selection. Forced SSE4.2 values.  
Ran sse2neon test suite - all pass.  
Identified remaining errors when trying to make IQ-TREE to be of the form:  
``_mm_XXX not declared in scope, did you mean _mm_YYY?``  
``(int8x16_t)(n) can't convert value to vector`` in sse2neon.h  
``there are no arguments to _mm_XXX that depend on a template parameter so a declaration of _mm_XXX must be available``  
``narrowing conversion of '-1' from 'int' to 'char' inside {}`` in vectorclass/vectori128.h lines 395,4927,4946.  

# Tue 11/7 - Mon 27/7

Extending functionality in sse2neon.h to include all intrinsics (bar ```_mm_setcsr``` and ```_mm_getcsr```) from IQ-TREE.  
Modified ```char``` to ```signed char``` to remove narrowing conversion errors.  
Not much to list on the work_log as just slowly getting through all of the intrinsics. Some have one-to-one mappings, others are much more complicated.  

# Tue 28/7

Investigating the manual controlling of the MXCSR register throughout vectorclass and eigen.  

##### /vectorclass/vectorf128.h:  

```uint32_t t1 = _mm_getcsr();
uint32_t t2 = t1 | (3 << 13); // 0x6000
_mm_setcsr(t2);
Vec4f r = round(a); // Towards zero rounding mode RC=RZ
_mm_setcsr(t1);

uint32_t t2 = t1 | (1 << 13) // 0x2000 RC=R- min inf

uint32_t t2 = t1 | (2 << 13) // 0x4000 RC=R+ round to pos inf
```
Above snippets repeated twice.  

```_mm_setcsr(w); // set MXCSR control word

_mm_getcsr() // get control word

set_control_word(t1):
t1 = get_control_word() | (1 << 6) | (1 << 15) // 0x40 | 0x8000 DAZ FTZ
t1 = 0x1F80 // reset_control_word

// assume MXCSR control register is set to rounding
```

```// Control word manipulaton
// ------------------------
// The MXCSR control word has the following bits:
//  0:    Invalid Operation Flag
//  1:    Denormal Flag (=subnormal)
//  2:    Divide-by-Zero Flag
//  3:    Overflow Flag
//  4:    Underflow Flag
//  5:    Precision Flag
//  6:    Denormals Are Zeros (=subnormals)
//  7:    Invalid Operation Mask
//  8:    Denormal Operation Mask (=subnormal)
//  9:    Divide-by-Zero Mask
// 10:    Overflow Mask
// 11:    Underflow Mask
// 12:    Precision Mask
// 13-14: Rounding control
//        00: round to nearest or even
//        01: round down towards -infinity
//        10: round up   towards +infinity
//        11: round towards zero (truncate)
// 15: Flush to Zero
```

##### ../eigen/bench/btl/generic_bench/btl.hh:  

```#define BTL_DISABLE_SSE_EXCEPTIONS() { _mm_setcsr(_mm_getcsr() | 0x8040); } // flush to zero and denormals are zero (FTZ & DAZ)```  

##### /pll/utils.c:  

```#if (defined(__AVX) || defined(__SSE3))
_mm_setcsr( _mm_getcsr() | _MM_FLUSH_ZERO_ON ); // flush to zero (FTZ) // 0x8000
```

#### FTZ:  
on: sets denormal results from fp calculations to zero  
off: does not change denormal results  

#### DAZ:  
on: treats denormal values used as input to fp intructions as zero  
off: does not change the denormal intruction inputs  



## FPSCR, ARM:  

NEON only uses FPSCR[31:27].  

#### FZ[24]: Flush-to-zero mode replaces denormalized numbers with +0.  
The value of this bit only controls scalar floating-point arithmetic. Advanced SIMD arithmetic always used FZ setting, regardless of value of FZ bit.  
```
Disabled: 0b0
Enabled: 0b1
```
Has no effect on half-precision calculations.  

#### FZ16[19]: Flush-to-zero mode control bit on half-precision data-processing intructions.  
The value of this bit applies to both scalar and Advanced SIMD fp half-precision.  
```
Disabled: 0b0
Enabled: 0b1
```
Effects on FP operations when FZ mode is enabled:
- A denormalized number is treated as 0 when used as an input to a floating-point operation. The source register is not altered.  
- If the result of a single-precision floating-point operation, before rounding, is in the range -2^-126 to +2^-126, it is replaced by 0.  
- If the result of a double-precision floating-point operation, before rounding, is in the range -2^-1022 to +2^-1022, it is replaced by 0.  

In FZ mode, an Input Denormal exception occurs whenever a denormalized number is used as an operand. An Underflow exception occurs when a result is flushed-to-zero.  

#### RMode[23:22]  
Rounding mode control field.  
```
0b00: Round to Nearest (RN) mode.
0b01: Round towards +infinity (RP) mode.
0b10: Round towards -infinity (RM) mode.
0b11: Round towards Zero (RZ) mode.
```
The specified rounding mode is used by almost all scalar fp instructions. Advanced SIMD arithmetic always uses RN setting, regardless of the value of the RMode bit.  

## Proposed changes:  

Access to the FPSCR register is done by using the ```VMRS``` and ```VMSR``` instructions, with the following encodings:  
```VMRS{<c>}{<q>}<Rt>,<spec_reg>```  
```VMSR{<c>}{<q>}<spec_reg>,<Rt>```  

Alternatively the ```__vfp_status``` intrinsic can be used to read and modify the FPCSR register.

Add conditional statements where MXCSR intrinsics are located.  

##### /pll/utils.c

```
#ifdef (__ARM_NEON)
// something here
#else
_mm_setcsr( _mm_getcsr() | _MM_FLUSH_ZERO_ON );
#endif
```
### NEON

Upon further research into specifically NEON, I have found:  
- denormalized numbers are flushed to zero  
- only default NaNs are supported  
- the Round to Nearest rounding mode is selected  
- untrapped exception handling selected for all floating-point exceptions.  

Therefore, perhaps it will be necessary to specify rounding mode in the operation intrinsics, depending on the instruction used, and to add conditional statements to not run the flush-to-zero intrinsics when __ARM_NEON is defined.  

#### Examples of proposed changes to rounding in /vectorclass/vectorf128.h

```
#ifdef (__ARM_NEON)
Vec4f r = _mm_round_ps(a, (0x03 | 0x08)); // triggers vrndq_f32(a) in sse2neon.h
#else
uint32_t t1 = _mm_getcsr();
uint32_t t2 = t1 | (3 << 13);
_mm_setcsr(t2);
Vec4f r = round(a);
_mm_setcsr(t1);
#endif
```

```
#ifdef (__ARM_NEON)
Vec4f r = _mm_round_ps(a, (0x01 | 0x08)); // triggers vrndmq_f32(a) in sse2neon.h
#else
uint32_t t1 = _mm_getcsr();
uint32_t t2 = t1 | (1 << 13);
_mm_setcsr(t2);
Vec4f r = round(a);
_mm_setcsr(t1);
#endif
```

```
#ifdef (__ARM_NEON)
Vec4f r = _mm_round_ps(a, (0x02 | 0x08)); // triggers vrndpq_f32(a) in sse2neon.h
#else
uint32_t t1 = _mm_getcsr();
uint32_t t2 = t1 | (2 << 13);
_mm_setcsr(t2);
Vec4f r = round(a);
_mm_setcsr(t1);
#endif
```

Apart from these instances, all other uses of the mxcsr intrinsics are FTZ or DAZ, which happens automatically in NEON. Need to investigate whether having these turned on permanently will affect the results of iq-tree, but will wait until compilation to run the tests to do this, so in the meantime will conditionally not run these intrinsics.  

##### /pll/utils.c

```
#if !defined(__ARM_NEON)
_mm_setcsr( _mm_getcsr() | _MM_FLUSH_ZERO_ON );
#endif
```

