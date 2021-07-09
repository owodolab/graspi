## GraSPI: what it is and what it does?

GraSPI is a tool for morphology analysis. The first application was in
the field of organic solar cells, where morphology affect the final
performance of device. GraSPI helped us to quantify various
morphological features. However, GraSPI can be used for any other
application, assuming that descriptor used in GraSPI are physically
relevant. We decided to share to code

## Small example

See example the folder with [2 phase
morpholgies](https://github.com/owodolab/graspi/tree/master/examples/2phaseMorphologies)
and the slides
[GraSPI.pdf](https://github.com/owodolab/graspi/blob/master/examples/GraSPI.pdf)

## Major features

GraSPI computes the set of descriptors/features that can used for data
analytics (e.g., to establish process-structure-property maps). GraSPI
is implemented in C++ and uses bash as a scripting tool to encode
basic analysis pipelines. GraSPI aims to handle multiple input
formats, and tools to convert various formats it to internal data
structures.

## Documentation

Documentation can be found here (generated using sphinx+doxygen+breathe).

[GraSPI documentation](https://owodolab.github.io/graspi/)

## Installation

GraSPI can be built both as a C++ library and as a Python Package.

### C++ Library

GraSPI requires boost library.  To compile go to src file, you find
there Makefile. If you install boost library in location that is not
searchable, you need to explicity provide the path.

Type make all

### Python Library

#### Conda

Coming soon.

#### Pip

Coming soon.

#### Nix

Follow the [Nix installation
guild](https://nixos.org/nix/manual/#chap-quick-start) and then run

    $ export NIX_VERSION=20.09
    $ export GRASPI_VERSION=v1.0
    $ nix-shell \
        -I nixpkgs=https://github.com/NixOS/nixpkgs/archive/${NIX_VERSION}.tar.gz \
        -I graspi=https://github.com/materialsinnovation/pymks/archive/${GRASPI_VERSION}.tar.gz \
        -E 'with (import <nixpkgs> {}); mkShell { buildInputs = [ (python3Packages.callPackage <graspi> { }) ]; }'

to drop into a shell with PyMKS and all its requirements available. To
create a development environment with Nix, clone this repository and
run

    $ nix-shell

in the base directory.

## Testing

To test an installed version of GraSPI run

    $ python -c "import graspi; graspi.test()"

To test a development version of GraSPI run

    $ py.test

in the base directory.

## How to cite GraSPI

@article{wodo2012graph,
  title={A graph-based formulation for computational characterization of bulk heterojunction morphology},
  author={Wodo, Olga and Tirthapura, Srikanta and Chaudhary, Sumit and Ganapathysubramanian, Baskar},
  journal={Organic Electronics},
  volume={13},
  number={6},
  pages={1105--1113},
  year={2012}
}

## Support

This project is supported by [National Science Foundation](https://www.nsf.gov/), award number [1906344](https://www.nsf.gov/awardsearch/showAward?AWD_ID=1906344&HistoricalAwards=false#)

## License

GraSPI is distributed under BSD license - for more details see the LICENSE.txt file in the main folder of the project.

## Changelog

We keep updating GraSPI, here we log the major changes:

* June 2020, the first release of GraSPI, with the capabilities to analyze two phase morphology
* October 2020, cythonized version of GraSPI released
* January 2021, documentation and examples added

## Community information

If you want to some additional features, send us email - see Contact info at the bottom. Here, we will keep the list of requests that we plan to introduce, and our planned extensions.

## Contributor Information

GraSPI has been developing at two institutions:

* Olga Wodo, University at Buffalo
* Baskar Ganapathysubramian,  Iowa State Univiersity
* Jaroslaw Zola, Univeristy at Buffalo
* Devyani Jivani, University at Buffalo

## Contact info

Any questions and queries can be directed to Olga: olgawodo at buffalo dot edu.
