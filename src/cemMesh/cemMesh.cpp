#include "cemMesh.h"
#include "cemerror.h"

#include <fstream>
#include <iostream>

using cem_space::V3D;
using namespace cem_def;
using namespace cem_mesh;
using cemcommon::Exception;


//****************************************************************************//
//****************************************************************************//
void Mesh::ReadFromGmshFile(const std::string filename)
{
    // Open File:
    std::ifstream mesh_file(filename.c_str());
    if (mesh_file.is_open() == false)
        throw (Exception("FILE", "File can't be opened"));

    // Check format section:
    std::string line;
    mesh_file >> line;
    if (line == "$MeshFormat")
    {
        mesh_file >> line;
        mesh_file >> line;
        if (line != "$EndMeshFormat")
            throw (Exception("FILE FORMAT", "Expected $EndMeshFormat"));
    }
    else
        throw (Exception("FILE FORMAT", "Expected $MeshFormat"));

    // Read Sections until EOF:
    while (!mesh_file.eof())
    {
        mesh_file >> line;
        if (line == "$Nodes")
        {

        }
        else if (line == "$Elements")
        {

        }
        else if (line == "$PhysicalNames")
        {

        }
        else
        {
            // Keep reading lines until section ends:
            std::string end_line = line.insert(1,"End");
            while (line != end_line)
                mesh_file >> line;
        }
    }

    mesh_file.close();
}



//****************************************************************************//



//****************************************************************************//
//****************************************************************************//
void Node::initialize()
{
    has_been_checked_in_ = false;
    is_element_boundary_ = false;
    is_surface_boundary_ = false;
}


void Node::copy(const cem_mesh::Node &node)
{
    V3D::copy(node);
    has_been_checked_in_ = node.has_been_checked_in_;
    is_element_boundary_ = node.is_element_boundary_;
    is_surface_boundary_ = node.is_surface_boundary_;
}
//****************************************************************************//



//****************************************************************************//
//****************************************************************************//
cemINT NodeReader::getNumberOfNodes()
{
    cemINT size;
    input_stream_ >> size;
    return size;
}


Node* NodeReader::getNode()
{
    cemINT node_number;
    input_stream_ >> node_number;
    return &mesh_.node_table_[node_number];
}

//****************************************************************************//



//****************************************************************************//
//****************************************************************************//
void Element::initialize()
{
    type_ = TRI;                        // Most common case for now.
    is_surface_boundary_ = false;
    order_ = 1;                         // Most common case for now.
    node_ptrs_.resize(3);               // TRI order 1 has 3 nodes.
}

void Element::copy(const cem_mesh::Element &elem)
{
    type_ = elem.type_;
    is_surface_boundary_ = elem.is_surface_boundary_;
    order_ = elem.order_;
    node_ptrs_.resize(elem.node_ptrs_.size());
    node_ptrs_ = elem.node_ptrs_;
}
//****************************************************************************//
