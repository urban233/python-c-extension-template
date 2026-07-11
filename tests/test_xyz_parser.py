"""Test suite for the C++ nanobind XYZ parser and NumPy utility functions.

This test module verifies the correctness of XYZ file parsing, coordinate 
extraction, center of mass calculation, element filtering, and distance matrix computations.
"""

import os
import tempfile
import pytest
import numpy as np
from python_c_ext import Molecule, Atom
from python_c_ext.xyz_utils import to_numpy_coords, calculate_pairwise_distances

# Mock XYZ data representing a water molecule (H2O)
WATER_XYZ = """3
Water molecule reference
O   0.000000   0.000000   0.000000
H   0.758602   0.000000   0.504284
H  -0.758602   0.000000   0.504284
"""

@pytest.fixture
def temp_xyz_file():
    """Fixture that generates a temporary XYZ file containing a water molecule.

    Yields:
        str: The absolute path of the generated temporary XYZ file.
    """
    with tempfile.NamedTemporaryFile(mode='w', suffix='.xyz', delete=False) as f:
        f.write(WATER_XYZ)
        filepath = f.name
    yield filepath
    os.remove(filepath)

def test_molecule_loading(temp_xyz_file):
    """Verifies that the Molecule object successfully parses metadata and atom contents.

    Args:
        temp_xyz_file (str): The temporary XYZ file path provided by the fixture.
    """
    # Load Molecule using the C++ static method
    mol = Molecule.from_xyz_file(temp_xyz_file)
    
    # Assert parsed properties
    assert mol.atom_count == 3
    assert mol.comment == "Water molecule reference"
    
    # Assert atom list
    atoms = mol.get_atoms()
    assert len(atoms) == 3
    assert atoms[0].symbol == "O"
    assert abs(atoms[0].x) < 1e-6
    assert atoms[1].symbol == "H"
    
    # Assert C++ algorithms
    center = mol.get_center_of_mass()
    assert len(center) == 3
    # Water center of mass on X axis is 0
    assert abs(center[0] - 0.0) < 1e-6
    
    # Assert filtering method
    h_atoms = mol.filter_by_element("H")
    assert len(h_atoms) == 2
    assert all(a.symbol == "H" for a in h_atoms)

def test_numpy_integration(temp_xyz_file):
    """Verifies that the coordinate array extraction and distance matrices are accurate.

    Args:
        temp_xyz_file (str): The temporary XYZ file path provided by the fixture.
    """
    mol = Molecule.from_xyz_file(temp_xyz_file)
    coords = to_numpy_coords(mol)
    
    assert coords.shape == (3, 3)
    np.testing.assert_allclose(coords[0], [0.0, 0.0, 0.0])
    
    dist_matrix = calculate_pairwise_distances(mol)
    assert dist_matrix.shape == (3, 3)
    
    # Check manual distance calculation between Atom 1 (H) and Atom 2 (H)
    expected_dist = np.linalg.norm(np.array([0.758602, 0.0, 0.504284]) - np.array([-0.758602, 0.0, 0.504284]))
    assert abs(dist_matrix[1, 2] - expected_dist) < 1e-6
