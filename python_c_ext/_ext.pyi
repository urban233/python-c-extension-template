"""XYZ Molecular File Parser & Chemistry Extension"""



class Atom:
    def __init__(self, symbol: str, x: float, y: float, z: float) -> None:
        """Constructor to initialize an Atom instance."""

    @property
    def symbol(self) -> str:
        """The chemical symbol."""

    @symbol.setter
    def symbol(self, arg: str, /) -> None: ...

    @property
    def x(self) -> float:
        """X coordinate in Angstroms."""

    @x.setter
    def x(self, arg: float, /) -> None: ...

    @property
    def y(self) -> float:
        """Y coordinate in Angstroms."""

    @y.setter
    def y(self, arg: float, /) -> None: ...

    @property
    def z(self) -> float:
        """Z coordinate in Angstroms."""

    @z.setter
    def z(self, arg: float, /) -> None: ...

    def __repr__(self) -> str: ...

class Molecule:
    def __init__(self) -> None:
        """Constructs an empty Molecule instance."""

    @staticmethod
    def from_xyz_file(filepath: str) -> Molecule:
        """Parses an XYZ file and returns a Molecule."""

    @property
    def comment(self) -> str:
        """The title or metadata comment on the XYZ file."""

    @property
    def atom_count(self) -> int:
        """Total count of atoms in the molecule."""

    def get_atoms(self) -> list[Atom]:
        """Returns list of contained Atom objects (referenced internally)."""

    def get_center_of_mass(self) -> list[float]:
        """Computes and returns the 3D geometric center [x, y, z]."""

    def filter_by_element(self, symbol: str) -> list[Atom]:
        """Retrieves a subset list of atoms matching the given element symbol."""
