import numpy as np
from ._ext import Molecule

def to_numpy_coords(molecule: Molecule) -> np.ndarray:
    """Extracts raw coordinates from a C++ Molecule into a 2D numpy float array."""
    atoms = molecule.get_atoms()
    return np.array([[a.x, a.y, a.z] for a in atoms], dtype=np.float64)

def calculate_pairwise_distances(molecule: Molecule) -> np.ndarray:
    """Computes the full pairwise distance matrix using NumPy broadcasting."""
    coords = to_numpy_coords(molecule)
    diff = coords[:, np.newaxis, :] - coords[np.newaxis, :, :]
    return np.sqrt(np.sum(diff ** 2, axis=-1))
