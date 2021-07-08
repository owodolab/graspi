from .graspi import compute_descriptors


def get_version():
    """Get the version of the code from egg_info.

    Returns:
      the package version number
    """
    # pylint: disable=import-outside-toplevel
    from pkg_resources import get_distribution, DistributionNotFound

    try:
        version = get_distribution(
            __name__.split(".")[0]
        ).version  # pylint: disable=no-member
    except DistributionNotFound:  # pragma: no cover
        version = "unknown, try running `python setup.py egg_info`"

    return version


__version__ = get_version()

__all__ = [
    "__version__",
    "compute_descriptors",
]
