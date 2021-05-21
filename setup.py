from setuptools import Extension, setup, find_packages
from Cython.Build import cythonize

import numpy
import os

def graspi_paths():
    """Get Graspi paths
    """
    return ['cythonizeGraspi', 'src']


def graspi_extension():
    """Configure the graspi extension
    """
    return Extension(
        name="graspi",
        sources=[
            os.path.join('cythonizeGraspi', "graspi.pyx"),
            os.path.join('src', "graph_constructors.cpp"),
        ],
        include_dirs=[numpy.get_include(), '.'] + graspi_paths(),
        extra_compile_args=["-std=c++11"],
        language="c++",
        optional=True,
    )


def setup_args():
    """Get the setup args not availabe from setup.cfg
    """
    return dict(
        packages=find_packages(),
        data_files=["setup.cfg"],
        ext_modules=cythonize(
            [graspi_extension()],
            compiler_directives={"language_level": "3"},
            include_path=graspi_paths(),
        )
    )


setup(**setup_args())
