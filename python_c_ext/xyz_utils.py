"""Cheminformatics coordinate utility functions.

This module provides high-performance integration between the C++-backed 
`Molecule` class and numeric Python libraries like NumPy.
"""

import numpy as np
from ._ext import Molecule

def to_numpy_coords(molecule: Molecule) -> np.ndarray:
    """Extracts raw coordinates from a C++ Molecule into a 2D numpy float array.

    Args:
        molecule (Molecule): The C++-backed molecule instance containing atom coordinates.

    Returns:
        np.ndarray: A 2D array of shape (N, 3) where N is the number of atoms, 
            containing [x, y, z] coordinates as float64.
    """
    atoms = molecule.get_atoms()
    return np.array([[a.x, a.y, a.z] for a in atoms], dtype=np.float64)

def calculate_pairwise_distances(molecule: Molecule) -> np.ndarray:
    """Computes the full pairwise distance matrix for all atoms in a Molecule.

    Uses NumPy vector broadcasting to calculate pairwise Euclidean distances
    in a vectorized manner, avoiding slow python loops.

    Args:
        molecule (Molecule): The C++-backed molecule instance.

    Returns:
        np.ndarray: A square symmetric 2D array of shape (N, N) where entry (i, j) 
            represents the distance in Angstroms between atom i and atom j.
    """
    coords = to_numpy_coords(molecule)
    diff = coords[:, np.newaxis, :] - coords[np.newaxis, :, :]
    return np.sqrt(np.sum(diff ** 2, axis=-1))
