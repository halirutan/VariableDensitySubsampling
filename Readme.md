![Just a nice banner](subsample.jpg)

# Python Interface for Poisson Subsampling

This repository provides a Python interface for the Poisson subsampling
method available in the [CS_MoCo_LAB repository](https://github.com/thomaskuestner/CS_MoCo_LAB).
It means that instead of writing sampling mask to a text file, you can now directly
call the subsampling function from Python and get a Numpy array.

This project uses a CMake build setup that uses Pybind11 to directly interface with the C++ code.
It can do both build an installable Python wheel and install the package in a (virtual) Python environment
for you.

## Usage

The core of the interface is a data-class that gives you access to almost all the command-line
arguments available for the Poisson subsampling:

```python
class PoissonSampling:
    width: int = 256
    height: int = 128
    acceleration: float = 2.0
    fully_sampled_fraction: float = 0.065
    espresso_factor: float = 1.0
    espresso_direction: bool = True
    phases: int = 1
    variable_density_type: int = 4
    sample_type: int = 1
    elliptical_mask: bool = True
    power: float = 2.0
    root: float = 2.0
```

Therefore, a simple usage of the sampling is done by importing the package, create a `PoissonSampling`
instance, setting all parameters that deviate from the defaults and call the `subsample()` method:

```python
from subsample import PoissonSampling

mask = PoissonSampling(width=10, height=10).subsample()
```

If you have your parameters as a dict because, e.g. you imported it from JSON, then you can do the same
by unpacking the dict.
You only need to take care of correct spelling of the keys.

```python
from subsample import PoissonSampling

my_dict = {"width" : 10, "height": 20}
mask = PoissonSampling(**my_dict).subsample()
```

## Installation

TODO

## CS_MoCo_LAB License

Copyright (c) 2015, thomaskuestner
All rights reserved.
Created by Thomas Kuestner, Christian Wuerslin, Martin Schwartz, Marc Fischer
and others. Institute of Signal Processing and System Theory, University of Stuttgart,
Stuttgart, Germany and Department of Radiology, University Hospital Tübingen, Tübingen,
Germany.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

