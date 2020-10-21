# IQ-TREE : ARM NEON Implementation

IQ-TREE is a fast and effective stochastic algorithm to inferphylogenetic trees by maximum likelihood. It contains Intel intrinsics, and this project provides a mapping layer between those intrinsics and the underlying hardware, in order to port the software to work correctly on ARM NEON instruction set architecture.

Process included modifying IQ-TREE code to coerce the compiler into compiling for SSE4.2, adding functionality to recognise NEON ISA, and extending funtionality in sse2neon.h to include all missing intrinsics.

## Licence

Copyright (C) 2020 Joshua Measure-Hughes

Written for the Advanced Computing Research Centre, University of Bristol.

Licensed under the MIT License, (the “License”); you may not use this file except in compliance with the License.

The License applies to unique documents to this implementation, and not to those present in [1], [2] and [3]. Additional functionality in [2] has been labelled and is at the end of the document. The original Licenses for [1], [2], and [3] apply otherwise.

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

## References

[1]  B.Q.   Minh,   H.A.   Schmidt,   O.   Chernomor,   D.Schrempf,  M.D.  Woodhams,  A.  von  Haeseler,  R.Lanfear   (2020)   IQ-TREE   2:New   models   andefficient   methods   for   phylogenetic   inference   inthe  genomic  era.  Mol.  Biol.  Evol.,  37:1530-1534.https://doi.org/10.1093/molbev/msaa015

[2]  J.W.  Ratcliff,  B.  Rowlett,  K.  Fast,  E.  van  Beur-den,  A.  Potylitsin,  H.  Gamaarachchi,  J.  Huang,M.   Cheng,    M.   James,    D.   Hussey,    S.   Pop,Developer   Ecosystem   Engineering,   D.   Kutenin,F.    Turban,P-H.    Hung,Y-H.    Yang    (2020)sse2neon:  A  C/C++  header  file  that  converts  In-tel SSE intrinsics to Arm/Aarch64 NEON intrinsics.https://github.com/DLTcollab/sse2neon

[3]  B.   Jacob   (founder),    G.   Guennebaud   (guru),et   al.   (2020)   Eigen   is   a   C++   template   li-brary   for   linear   algebra:matrices,    vectors,numericalsolvers,andrelatedalgorithms.http://eigen.tuxfamily.org/index.php

[4]  Intel Intrinsics Guide.https://software.intel.com/sites/landingpage/IntrinsicsGuide/

[5]  ARM NEON Intrinsics Reference.https://developer.arm.com/architectures/instruction-sets/simd-isas/neon/intrinsics
