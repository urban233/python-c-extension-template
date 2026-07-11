#pragma once
#include "Atom.hpp"
#include <vector>
#include <string>

namespace ext {

class Molecule {
public:
    Molecule() = default;

    // Static builder parsing XYZ format from a file path
    static Molecule from_xyz_file(const std::string& filepath);

    // Accessors
    const std::string& get_comment() const { return m_comment; }
    size_t get_atom_count() const { return m_atoms.size(); }
    const std::vector<Atom>& get_atoms() const { return m_atoms; }

    // Algorithms
    std::vector<double> get_center_of_mass() const;
    std::vector<Atom> filter_by_element(const std::string& symbol) const;

private:
    std::string m_comment;
    std::vector<Atom> m_atoms;
};
} // namespace ext
