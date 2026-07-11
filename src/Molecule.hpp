/**
 * @file molecule.hpp
 * @brief Declaration of the Molecule class that represents a collection of atoms and provides parsing/analysis methods.
 * @details The Molecule class wraps a 3D coordinate system and elemental details of multiple atoms.
 *          It acts as the primary data interface between C++ algorithms and Python.
 * @author Martin Urban
 * @date 2026-07-11
 */

#ifndef EXT_MOLECULE_HPP_
#define EXT_MOLECULE_HPP_

#include "Atom.hpp"
#include <vector>
#include <string>

namespace ext {

/**
 * @brief Represents a single molecular structure composed of multiple atoms.
 * @details This class is responsible for managing the collection of atoms, parsing molecular 
 *          data from external files (like standard XYZ files), and computing spatial metrics 
 *          such as the center of mass or filtering subsets of atoms.
 */
class Molecule {
 public:
  /**
   * @brief Default constructor creating an empty Molecule.
   */
  Molecule() = default;

  /**
   * @brief Static factory method to instantiate a Molecule by parsing an XYZ file.
   * @details Reads a standard XYZ format file. The first line must contain the total number of atoms,
   *          the second line contains a free-text comment, and subsequent lines define the element symbol
   *          and coordinates (X, Y, Z separated by whitespace).
   * @param filepath The absolute or relative system path to the target XYZ file.
   * @return An initialized Molecule instance.
   * @throws std::runtime_error If the file cannot be opened, or if the format of the file is invalid.
   */
  static Molecule FromXyzFile(const std::string& filepath);

  /**
   * @brief Retrieve the metadata comment line of the molecule.
   * @return A constant reference to the comment string.
   */
  [[nodiscard]] const std::string& GetComment() const { return comment_; }

  /**
   * @brief Get the total number of atoms contained in the molecule.
   * @return The size of the atom list as a size_t.
   */
  [[nodiscard]] size_t GetAtomCount() const { return atoms_.size(); }

  /**
   * @brief Get a read-only list of all atoms in this molecule.
   * @return A constant reference to the internal vector of Atom structs.
   */
  [[nodiscard]] const std::vector<Atom>& GetAtoms() const { return atoms_; }

  /**
   * @brief Calculate the 3D geometric center (center of mass/geometry) of the molecule.
   * @details Sums the Cartesian coordinates of all contained atoms and divides by the total atom count.
   *          Assumes uniform atomic weight (geometric center). If the molecule is empty, returns {0.0, 0.0, 0.0}.
   * @return A vector of doubles containing exactly three values: [X, Y, Z].
   */
  [[nodiscard]] std::vector<double> GetCenterOfMass() const;

  /**
   * @brief Filter and retrieve a list of atoms matching a specific element symbol.
   * @param symbol The element symbol to filter by (case-sensitive, e.g., "H").
   * @return A new vector of Atom structs matching the filter.
   */
  [[nodiscard]] std::vector<Atom> FilterByElement(const std::string& symbol) const;

 private:
  /**
   * @brief The title or metadata comment line retrieved from the XYZ file header.
   */
  std::string comment_;

  /**
   * @brief The internal collection of Atom instances comprising the molecule.
   */
  std::vector<Atom> atoms_;
};

}  // namespace ext

#endif  // EXT_MOLECULE_HPP_
