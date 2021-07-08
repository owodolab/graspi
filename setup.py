"""GraSPI - tool for microstucture morphology analysis

See the documentation for more details at
https://owodolab.github.io/graspi
"""

import os

from setuptools import Extension, setup, find_packages
from Cython.Build import cythonize
import numpy


def graspi_paths():
    """Get Graspi paths
    """
    return ["graspi", "src"]


def graspi_extension():
    """Configure the graspi extension
    """
    return Extension(
        name="graspi.graspi",
        sources=[
            os.path.join("graspi", "graspi.pyx"),
            os.path.join("src", "graph_constructors.cpp"),
        ],
        include_dirs=[numpy.get_include(), "."] + graspi_paths(),
        extra_compile_args=["-std=c++11"],
        language="c++",
        optional=True,
    )


def setup_args():
    """Get the setup args not availabe from setup.cfg
    """
    return dict(
        packages=find_packages(),
        version="0.1-dev",
        data_files=["setup.cfg"],
        ext_modules=cythonize(
            [graspi_extension()],
            compiler_directives={"language_level": "3"},
            include_path=graspi_paths(),
        ),
    )


setup(**setup_args())
