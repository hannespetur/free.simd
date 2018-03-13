# Free.SIMD

**Free.SIMD** is a portable SIMD programming library that is derived from the Boost.SIMD library.

## Supported Compilers and Hardware

Support for x86 architectures with SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, AVX, AVX2 extensions. **Free.SIMD** requires a C++11 compliant compiler and Boost 1.61 and is thoroughly tested on the following compilers:

Compiler                | Version
------------------------|-------------------
g++                     | 4.8 and above
clang++                 | 3.5 and above

## Getting Started

We start out on the premise you already have a proper installation of Boost 1.61 or superior setup on your machine.

You can retrieve the current status of the library by cloning the repository:

    git clone https://github.com/hannespetur/free.simd.git

Once cloned, the library headers are located in the `include/` folder and are ready to be used. A very simple example like:

```cpp
#include <boost/simd/pack.hpp>
#include <iostream>

namespace bs = boost::simd;

int main()
{
   bs::pack<float,4> p{1.f,2.f,3.f,4.f};
   std::cout << p + 10*p << "\n";

   return 0;
}
```

can then be compiled via:

    g++ main.cpp -std=c++11 -O3 -msse4.2 -I<path/to/boost/1.61/include> -I<path/to/boost/simd/include> -o main

and display:

    (11, 22, 33, 44)
