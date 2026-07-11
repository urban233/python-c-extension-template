"""Cheminformatics C++ Extension package.

This package exposes the high-performance C++ `Molecule` and `Atom` classes 
along with Python-side utility functions for NumPy-based operations and matrix calculations.
"""

from ._ext import Molecule, Atom
from .xyz_utils import to_numpy_coords, calculate_pairwise_distances

__all__ = [
    "Molecule",
    "Atom",
    "to_numpy_coords",
    "calculate_pairwise_distances"
]
