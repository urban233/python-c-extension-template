/**
 * @file atom.hpp
 * @brief Definition of the Atom structure representing a single chemical atom in 3D space.
 * @details This file defines a lightweight, copyable, and serializable representation
 *          of an atom, housing its chemical symbol and coordinates.
 * @author Martin Urban
 * @date 2026-07-11
 */

#ifndef EXT_ATOM_HPP_
#define EXT_ATOM_HPP_

#include <string>
#include <utility>

namespace ext {

/**
 * @brief Representation of a single atom in a 3D molecule structure.
 * @details Atom is a lightweight data structure designed to hold the basic attributes
 *          of a chemical atom. It is optimized for passing by value or reference
 *          between the C++ calculation engine and Python-side scripts.
 */
struct Atom {
  /**
   * @brief The chemical element symbol (e.g., "H", "O", "Fe").
   */
  std::string symbol;

  /**
   * @brief The X-coordinate of the atom in 3D Cartesian space, usually in Angstroms.
   */
  double x;

  /**
   * @brief The Y-coordinate of the atom in 3D Cartesian space, usually in Angstroms.
   */
  double y;

  /**
   * @brief The Z-coordinate of the atom in 3D Cartesian space, usually in Angstroms.
   */
  double z;

  /**
   * @brief Constructor to initialize an Atom with explicit symbol and coordinates.
   * @param sym The chemical element symbol.
   * @param x_val The X-coordinate value.
   * @param y_val The Y-coordinate value.
   * @param z_val The Z-coordinate value.
   */
  Atom(std::string sym, double x_val, double y_val, double z_val)
      : symbol(std::move(sym)), x(x_val), y(y_val), z(z_val) {}
};

}  // namespace ext

#endif  // EXT_ATOM_HPP_
