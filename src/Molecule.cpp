/**
 * @file molecule.cpp
 * @brief Implementation of the Molecule class methods, including XYZ file parsing and analysis calculations.
 * @author Martin Urban
 * @date 2026-07-11
 */

#include "Molecule.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ext {

/**
 * Parses an XYZ molecular file.
 * Opens the file stream, reads the atom count, stores the comment line, and iteratively
 * parses the atomic symbols and 3D floating-point coordinates.
 */
Molecule Molecule::FromXyzFile(const std::string& filepath) {
  std::ifstream infile(filepath);
  if (!infile.is_open()) {
    throw std::runtime_error("Failed to open file: " + filepath);
  }

  std::string line;
  if (!std::getline(infile, line)) {
    throw std::runtime_error("Invalid XYZ file: empty file");
  }

  std::stringstream count_ss(line);
  size_t num_atoms = 0;
  if (!(count_ss >> num_atoms)) {
    throw std::runtime_error("Invalid XYZ file: missing atom count on line 1");
  }

  std::string comment;
  std::getline(infile, comment); // Read comment line (line 2)

  Molecule mol;
  mol.comment_ = comment;
  mol.atoms_.reserve(num_atoms);

  for (size_t i = 0; i < num_atoms; ++i) {
    if (!std::getline(infile, line)) {
      throw std::runtime_error("Invalid XYZ file: unexpected EOF while reading atoms");
    }
    std::stringstream line_ss(line);
    std::string symbol;
    double x, y, z;
    if (!(line_ss >> symbol >> x >> y >> z)) {
      throw std::runtime_error("Invalid XYZ coordinate line: " + line);
    }
    mol.atoms_.emplace_back(symbol, x, y, z);
  }

  return mol;
}

/**
 * Calculates the geometric center of coordinates.
 * Returns [0.0, 0.0, 0.0] if the molecule contains no atoms.
 */
std::vector<double> Molecule::GetCenterOfMass() const {
  if (atoms_.empty()) {
    return {0.0, 0.0, 0.0};
  }
  double sum_x = 0.0, sum_y = 0.0, sum_z = 0.0;
  for (const auto& atom : atoms_) {
    sum_x += atom.x;
    sum_y += atom.y;
    sum_z += atom.z;
  }
  double count = static_cast<double>(atoms_.size());
  return {sum_x / count, sum_y / count, sum_z / count};
}

/**
 * Filters the list of atoms based on their elemental symbol.
 * Compares the parameter symbol directly with the Atom's symbol (case-sensitive).
 */
std::vector<Atom> Molecule::FilterByElement(const std::string& symbol) const {
  std::vector<Atom> result;
  for (const auto& atom : atoms_) {
    if (atom.symbol == symbol) {
      result.push_back(atom);
    }
  }
  return result;
}

}  // namespace ext
