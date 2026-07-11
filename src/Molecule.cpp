#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Molecule.hpp"

namespace ext {

Molecule Molecule::from_xyz_file(const std::string& filepath) {
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
    mol.m_comment = comment;
    mol.m_atoms.reserve(num_atoms);

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
        mol.m_atoms.emplace_back(symbol, x, y, z);
    }

    return mol;
}

std::vector<double> Molecule::get_center_of_mass() const {
    if (m_atoms.empty()) {
        return {0.0, 0.0, 0.0};
    }
    double sum_x = 0.0, sum_y = 0.0, sum_z = 0.0;
    for (const auto& atom : m_atoms) {
        sum_x += atom.x;
        sum_y += atom.y;
        sum_z += atom.z;
    }
    double count = static_cast<double>(m_atoms.size());
    return {sum_x / count, sum_y / count, sum_z / count};
}

std::vector<Atom> Molecule::filter_by_element(const std::string& symbol) const {
    std::vector<Atom> result;
    for (const auto& atom : m_atoms) {
        if (atom.symbol == symbol) {
            result.push_back(atom);
        }
    }
    return result;
}

} // namespace ext
