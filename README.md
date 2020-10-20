# IQ-TREE : ARM NEON Implementation

IQ-TREE is a fast and effective stochastic algorithm to inferphylogenetic trees by maximum likelihood. It contains Intel intrinsics, and this project provides a mapping layer between those intrinsics and the underlying hardware, in order to port the software to work correctly on ARM NEON instruction set architecture.

Process included modifying IQ-TREE code to coerce the compiler into compiling for SSE4.2, and extending funtionality in sse2neon.h to include all missing intrinsics.

## Licence

Copyright (C) 2020 Joshua Measure-Hughes

Written for the Advanced Computing Research Centre, University of Bristol.

Licensed under the GNU General Public License, Version 3.0 (the “License”); you may not use this file except in compliance with the License. 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
