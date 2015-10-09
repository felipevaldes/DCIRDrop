#include "cemMesh.h"
#include "cemerror.h"

#include <fstream>
#include <iostream>

using cem_space::V3D;
using namespace cem_def;
using namespace cem_mesh;
using cemcommon::Exception;


///***********************************************************************************************//
/// CLASS: MESH
///***********************************************************************************************//

//************************************************************************************************//
/** @brief Mesh::Mesh : Copy constructor.
 * @param [in] mesh : mesh to be copied */
//************************************************************************************************//
Mesh::Mesh(const Mesh& mesh) {copy(mesh);}


//************************************************************************************************//
/** @brief Mesh::copy : Deep copy of given mesh.
 * @param [in] mesh mesh to be copied */
//************************************************************************************************//
void Mesh::copy(const Mesh &mesh)
{
    // Copy nodes:
    this->num_nodes_ = mesh.num_nodes_;
    this->node_table_ = mesh.node_table_;

    // Copy elements:
    num_elements_ = mesh.num_elements_;
    element_table_ = mesh.element_table_;

    // Each element in this->element_table is now pointing to nodes in mesh.node_table_
    // Change node_ptrs in each element of this->element_table_:
    for (cemINT ii=1; ii<=this->num_elements_; ++ii)
    {
        Element& elem = element_table_[ii];
        std::vector<const Node*> temp_array;
        temp_array = elem.node_ptrs();

        // For each node pointer in temp_array, redirect to this->node_table_:
        for (cemINT jj=0; jj<temp_array.size(); ++jj)
        {
            cemINT node_id = temp_array[jj]->node_id();
            temp_array[jj] = &node_table_[node_id];
        }
    }
}


//************************************************************************************************//
/** @brief Mesh::ReadFromGmshFile : Reads mesh-file generated with Gmsh.
 *
 * Reads mesh-file in the MSH ASCII file format of the mesher Gmsh (http://geuz.org/gmsh/)
 * Compatible with version 2.2 and below.
 * @param [in] filename : Name of the file containing the mesh.
 * @author Felipe Valdes
 * @version 1.0 */
//************************************************************************************************//
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
        cemDOUBLE version_number;
        mesh_file >> version_number;
        if (version_number != 2.2)
            throw (Exception("UNKNOWN FILE FORMAT", "Expected version_number = 2.2"));

        cemINT file_type;
        mesh_file >> file_type;
        if (file_type != 0)
            throw (Exception("UNKNOWN FILE FORMAT", "Expected file_type = 0"));

        cemINT data_size;
        mesh_file >> data_size;

        mesh_file >> line;
        if (line != "$EndMeshFormat")
            throw (Exception("UNKNOWN FILE FORMAT", "Expected $EndMeshFormat"));
    }
    else
        throw (Exception("UNKNOWN FILE FORMAT", "Expected $MeshFormat"));

    // Read Sections until EOF:
    while (!mesh_file.eof())
    {
        mesh_file >> line;

        //========================================================================================//
        if (line == "$Nodes")
        {
            // Get number of nodes in the mesh:
            mesh_file >> num_nodes_;
            node_table_.resize(num_nodes_+1); // Nodes are stored from 1 to num_nodes (no zero)

            for (cemINT ii=1; ii<=num_nodes_; ++ii)
            {
                cemINT node_id;
                mesh_file >> node_id;
                if (ii != node_id)
                    throw (Exception("UNKNOWN FILE FORMAT", "Nodes are not stored consecutively"));

                Node& node = node_table_[ii];
                node.set_node_id(node_id);
                mesh_file >> node[0];   // Set x-coordinate of node
                mesh_file >> node[1];   // Set y-coordinate of node
                mesh_file >> node[2];   // Set z-coordinate of node
            }

            mesh_file >> line;
            if (line != "$EndNodes")
                throw (Exception("UNKNOWN FILE FORMAT", "Expected $EndNodes"));
        }
        //========================================================================================//
        else if (line == "$Elements")
        {
            // Get number of elements in the mesh:
            mesh_file >> num_elements_;
            element_table_.resize(num_elements_+1);  // Elements are stored from 1 to num_elements

            NodeReader node_reader(*this,mesh_file);
            for (cemINT ii=1; ii<=num_elements_; ++ii)
            {
                cemINT elem_id;
                mesh_file >> elem_id;
                if (ii != elem_id)
                    throw (Exception("UNKNOWN FILE FORMAT", "Elements are not stored consecutively"));

                Element& element = element_table_[ii];
                element.set_element_id(elem_id);
                element.ReadFromGmshFile(mesh_file,node_reader);
            }
            mesh_file >> line;
            if (line != "$EndElements")
                throw (Exception("UNKNOWN FILE FORMAT", "Expected $EndElements"));
        }
        //========================================================================================//
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


//************************************************************************************************//
/** @brief Mesh::WriteToGmshFile : Writes mesh in a file readable by Gmsh.
 *
 * Writes the mesh in file in the MSH ASCII file format of the mesher Gmsh (http://geuz.org/gmsh/)
 * Compatible with version 2.2 and below.
 * @param [in] filename : Name of the file where the mesh is written.
 * @author Felipe Valdes
 * @version 1.0 */
//************************************************************************************************//
void Mesh::WriteToGmshFile(const std::string filename)
{
    // Open file:
    std::ofstream mesh_file(filename.c_str());
    if (mesh_file.is_open() == false)
        throw (Exception("FILE", "File can't be opened"));

    // Write Format section:
    mesh_file << "$MeshFormat" << std::endl;
    mesh_file << 2.2 << " " << 0 << " " << 8 << std::endl;
    mesh_file << "$EndMeshFormat" << std::endl;

    // Write Nodes section:
    mesh_file << "$Nodes" << std::endl;
    mesh_file << num_nodes_ << std::endl;
    for (cemINT ii=1; ii<=num_nodes_; ++ii)
    {
        Node& node = node_table_[ii];
        mesh_file << node.node_id() << " " << node[0] << " " << " " << node[1] << " " << node[2] << std::endl;
    }
    mesh_file << "$EndNodes" << std::endl;

    // Write Elements section:
    mesh_file << "$Elements" << std::endl;
    mesh_file << num_elements_ << std::endl;
    for (cemINT ii=1; ii<=num_elements_; ++ii)
    {
        Element& element = element_table_[ii];
        element.WriteToGmsgFile(mesh_file);
    }
    mesh_file << "$EndElements" << std::endl;
}




///***********************************************************************************************//
/// CLASS: NODE
///***********************************************************************************************//

//************************************************************************************************//
/** @brief Node::initialize : Initializes a node with default data. */
//************************************************************************************************//
void Node::initialize()
{
    has_been_checked_in_ = false;
    is_element_boundary_ = false;
    is_surface_boundary_ = false;
}

//************************************************************************************************//
/** @brief Node::copy : Deep copy of a node.
 * @param [in] node : node to be copied */
//************************************************************************************************//
void Node::copy(const cem_mesh::Node &node)
{
    V3D::copy(node);
    has_been_checked_in_ = node.has_been_checked_in_;
    is_element_boundary_ = node.is_element_boundary_;
    is_surface_boundary_ = node.is_surface_boundary_;
}


//************************************************************************************************//
/** @brief Node::Node : Constructor with parameters.
 * @param [in] x1 : x-coordinate of the node
 * @param [in] x2 : y-coordinate of the node
 * @param [in] x3 : z-coordinate of the node */
//************************************************************************************************//
Node::Node(const cemDOUBLE &x1, const cemDOUBLE &x2, const cemDOUBLE &x3):V3D(x1,x2,x3){}


//************************************************************************************************//
/** @brief Node::Node : Constructor with parameters.
 * @param [in] point : position of the node in cartesian coordinates */
//************************************************************************************************//
Node::Node(const V3D& point):V3D(point){}


//************************************************************************************************//
/** @brief Node::Node : Copy constructor.
 * @param [in] node : Node to be copied */
//************************************************************************************************//
Node::Node(const Node &node)
{
    initialize();
    copy(node);
}


//************************************************************************************************//
/** @brief Node::operator = : Copy operator.
 * @param [in] node : Node to be copied
 * @return : A new node, equal to the one given */
//************************************************************************************************//
Node& Node::operator=(const Node& node)
{
    initialize();
    copy(node);
}


//************************************************************************************************//
/** @brief Node::has_been_checked_in : TRUE if other flags have been validated.
 * @return has_been_checked_in_ */
//************************************************************************************************//
cemBOOL Node::has_been_checked_in() const {return has_been_checked_in_;}


//************************************************************************************************//
/** @brief Node::is_element_boundary :  TRUE if node is in the element's boundary.
 * @return is_element_boundary_ */
//************************************************************************************************//
cemBOOL Node::is_element_boundary() const {return is_element_boundary_;}


//************************************************************************************************//
/** @brief Node::is_surface_boundary : TRUE if node is in the surface's boundary.
 * @return is_surface_boundary_ */
//************************************************************************************************//
cemBOOL Node::is_surface_boundary() const {return is_surface_boundary_;}


//************************************************************************************************//
/** @brief Node::node_id : Gets unique identifier whithin the mesh.
 * @return node_id_ */
//************************************************************************************************//
cemINT Node::node_id() const {return node_id_;}


//************************************************************************************************//
/** @brief Node::set_node_id : Sets unique identifier whithin the mesh.
 * @param [in] node_id  */
//************************************************************************************************//
void Node::set_node_id(const cemINT& node_id) {node_id_ = node_id;}







///***********************************************************************************************//
/// CLASS: ELEMENT
///***********************************************************************************************//

//************************************************************************************************//
/** @brief Element::Element : Constructor with parameters.
 * @param [in] type : Type of element */
//************************************************************************************************//
Element::Element(const ElementType& type)
{
    initialize();
    type_ = type;
}


//************************************************************************************************//
/** @brief Element::Element : Constructor with parameters.
 * @param [in] type : Type of element
 * @param [in] order : Polynomial order of the element >= 1 */
//************************************************************************************************//
Element::Element(const ElementType& type, const cemINT& order)
{
    if (order < 1)
        throw (Exception("INVALID ARGUMENT", "Polynomial order must be greater than zero"));

    initialize();
    type_ = type;
    order_ = order;
}


//************************************************************************************************//
/** @brief Element::Element : Constructor with parameters.
 * @param [in] num_nodes : Number of nodes that define the element
 * @param [in] node_pointers : Vector of nodes that define the element */
//************************************************************************************************//
Element::Element(const cemINT& num_nodes, const std::vector<const Node*>& node_pointers)
{
    if (num_nodes < 1)
        throw (Exception("INVALID ARGUMENT", "Number of nodes must be greater than zero"));

    initialize();
    num_nodes_ = num_nodes;
    node_ptrs_.resize(num_nodes);
    node_ptrs_ = node_pointers;
}


//************************************************************************************************//
/** @brief Element::Element : Copy constructor.
 * @param [in] elem : Element to be copied */
//************************************************************************************************//
Element::Element(const Element& elem) {initialize(); copy(elem);}


//************************************************************************************************//
/** @brief Element::operator = : Copy operator.
 * @param [in] elem : Element to be copied
 * @return A new element, equal to the one given */
//************************************************************************************************//
Element& Element::operator=(const Element& elem) {initialize(); copy(elem);}


//************************************************************************************************//
/*! @brief Element::initialize : Initializes an element with default data. */
//************************************************************************************************//
void Element::initialize()
{
    type_ = TRI;                        // Most common case for now.
    is_complete_ = true;                // Most common case for now.
    order_ = 1;                         // Most common case for now.
    num_nodes_ = 3;                     // TRI order 1 has 3 nodes.
    node_ptrs_.resize(3);               // TRI order 1 has 3 nodes.
    physical_id_ = 0;
    geometrical_id_ = 0;
    is_surface_boundary_ = false;
    num_partitions_ = 0;
}


//************************************************************************************************//
/*! @brief Element::copy : Deep copy of an element.
 * Node pointers of the new element point to the same nodes pointed by the original element.
 * @param [in] elem : element to be copied */
//************************************************************************************************//
void Element::copy(const cem_mesh::Element &elem)
{
    type_ = elem.type_;
    is_surface_boundary_ = elem.is_surface_boundary_;
    order_ = elem.order_;
    num_nodes_ = elem.num_nodes_;
    physical_id_ = elem.physical_id_;
    geometrical_id_ = elem.geometrical_id_;
    num_partitions_ = elem.num_partitions_;
    partitions_ = elem.partitions_;

    node_ptrs_.resize(elem.node_ptrs_.size());
    node_ptrs_ = elem.node_ptrs_;
}


//************************************************************************************************//
/*! @brief Element::set_element_id : Sets unique identifier whithin the mesh.
 * @param [in] elem_id */
//************************************************************************************************//
void Element::set_element_id(const cemINT& elem_id) {element_id_ = elem_id;}


//************************************************************************************************//
/** @brief Element::element_id : Gets unique identifier whithin the mesh.
 * @return element_id_ */
//************************************************************************************************//
cemINT Element::element_id() const {return element_id_;}


//************************************************************************************************//
/*! @brief Element::set_type : Set the type of element.
 * @param [in] type */
//************************************************************************************************//
void Element::set_type(const ElementType& type) {type_ = type;}


//************************************************************************************************//
/** @brief Element::type : Gets type the of element.
 * @return type_ */
//************************************************************************************************//
Element::ElementType Element::type() const {return type_;}


//************************************************************************************************//
/*! @brief Element::set_order : Sets polynomial order of the element >= 1.
 * @param [in] order */
//************************************************************************************************//
void Element::set_order(const cemINT& order)
{
    if (order < 1)
        throw (Exception("INVALID ARGUMENT", "Polynomial order must be greater than zero"));
    order_ = order;
}


//************************************************************************************************//
/** @brief Element::order : Gets polynomial order of the element.
 * @return order_ */
//************************************************************************************************//
cemINT Element::order() const {return order_;}


//************************************************************************************************//
/*! @brief Element::set_is_complete : Sets flag that records if polynomial expansion is complete.
 * @param [in] is_complete */
//************************************************************************************************//
void Element::set_is_complete(const cemBOOL& is_complete) {is_complete_ = is_complete;}


//************************************************************************************************//
/** @brief Element::is_complete : TRUE if polynomial expansion is complete.
 * @return is_complete_ */
//************************************************************************************************//
cemBOOL Element::is_complete() const {return is_complete_;}


//************************************************************************************************//
/*! @brief Element::set_is_surface_boundary : Sets flag that records if element is in the surface's boundary.
 * @param [in] is_boundary */
//************************************************************************************************//
void Element::set_is_surface_boundary(const cemBOOL& is_boundary) {is_surface_boundary_ = is_boundary;}


//************************************************************************************************//
/** @brief Element::is_surface_boundary : TRUE if element is in the surface's boundary.
 * @return is_surface_boundary_ */
//************************************************************************************************//
cemBOOL Element::is_surface_boundary() const {return is_surface_boundary_;}


//************************************************************************************************//
/*! @brief Element::set_node_ptrs : Sets vector of nodes that define the element.
 * @param [in] nodes : Vector of pointers to the nodes that define the element. */
//************************************************************************************************//
void Element::set_node_ptrs(const std::vector<const Node*>& nodes)
{
    cemINT num_nodes = nodes.size();
    node_ptrs_.resize(num_nodes);
    node_ptrs_ = nodes;
}


//************************************************************************************************//
/** @brief Element::node_ptrs : Gets vector of nodes that define the element.
 * @return node_ptrs_ */
//************************************************************************************************//
std::vector<const Node*> Element::node_ptrs() const {return node_ptrs_;}


//************************************************************************************************//
/*! @brief Element::set_num_nodes : Sets the number of nodes that define the element.
 * @param [in] num_nodes */
//************************************************************************************************//
void Element::set_num_nodes(const cemINT& num_nodes)
{
    if (num_nodes < 1)
        throw (Exception("INVALID ARGUMENT", "Number of nodes must be greater than zero"));
    num_nodes_ = num_nodes;
}


//************************************************************************************************//
/** @brief Element::num_nodes : Gets the number of nodes that define the element.
 * @return num_nodes_ */
//************************************************************************************************//
cemINT Element::num_nodes() const {return num_nodes_;}


//************************************************************************************************//
/*! @brief Element::set_physical_id : Sets the physical entity to which element belongs.
 * @param [in] phys_id */
//************************************************************************************************//
void Element::set_physical_id(const cemINT& phys_id) {physical_id_ = phys_id;}


//************************************************************************************************//
/** @brief Element::physical_id : Gets the physical entity to which element belongs.
 * @return physical_id_  */
//************************************************************************************************//
cemINT Element::physical_id() const {return physical_id_;}


//************************************************************************************************//
/*! @brief Element::set_geometrical_id : Sets the geometrical entity to which element belongs.
 * @param [in] geom_id */
//************************************************************************************************//
void Element::set_geometrical_id(const cemINT& geom_id) {geometrical_id_ = geom_id;}


//************************************************************************************************//
/** @brief Element::geometrical_id : Sets the geometrical entity to which element belongs.
 * @return geometrical_id_ */
//************************************************************************************************//
cemINT Element::geometrical_id() const {return geometrical_id_;}


//************************************************************************************************//
/*! @brief Element::set_num_partitions : Sets the number of partitions to which element belongs.
 *
 * If the number of partitions is zero, it is understood that there is no partition at all.
 * @param [in] num_partitions */
//************************************************************************************************//
void Element::set_num_partitions(const cemINT& num_partitions) {num_partitions_ = num_partitions;}


//************************************************************************************************//
/** @brief Element::num_partitions : Gets the number of partitions to which element belongs.
 * @return num_partitions_ */
//************************************************************************************************//
cemINT Element::num_partitions() const {return num_partitions_;}


//************************************************************************************************//
/*! @brief Element::set_partitions : Sets the vector of partitions to which element belongs.
 * @param [in] partitions */
//************************************************************************************************//
void Element::set_partitions(const std::vector<cemINT>& partitions) {partitions_ = partitions;}


//************************************************************************************************//
/** @brief Element::partitions : Gets the vector of partitions to which element belongs.
 * @return partitions_ */
//************************************************************************************************//
std::vector<cemINT> Element::partitions() const {return partitions_;}



//************************************************************************************************//
/** @brief Element::ReadFromGmshFile : Reads element from mesh-file genereated with Gmsh.
 *
 * Elements in mesh-file are assumed to be witten in MSH ASCII file format 2.2
 * The first parameter read from the mesh-file determines the type of element,
 * its polynomial order (complete or not), and the number of nodes.
 * Then comes a list of tags, the first one being a "physical ID", the second a "geometrycal ID",
 * and the third the number of partitions to which the element belongs,
 * followed by the prtition IDs. Finally comes the list of nodes.
 * @param [in] mesh_file : istream of the file containing the mesh
 * @param [in] reader : node reader that knows where nodes are located inside the mesh
 * @author Felipe Valdes
 * @version 1.0 */
//************************************************************************************************//
void Element::ReadFromGmshFile(std::istream& mesh_file, NodeReader& reader)
{
    // Get element type and order:
    cemINT elem_type;
    mesh_file >> elem_type;
    switch (elem_type) {

    case 1: // 2-node line.
        this->set_type(LINE);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(2);
        break;

    case 2: // 3-node triangle.
        this->set_type(TRI);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(3);
        break;

    case 3: // 4-node quadrangle.
        this->set_type(QUAD);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(4);
        break;

    case 4: // 4-node tetrahedron.
        this->set_type(TET);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(4);
        break;

    case 5: // 8-node hexahedron.
        this->set_type(HEX);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(8);
        break;

    case 6: // 6-node prism.
        this->set_type(PRISM);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(6);
        break;

    case 7: // 5-node pyramid.
        this->set_type(PYRA);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(5);
        break;

    case 8: // 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
        this->set_type(LINE);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(3);
        break;

    case 9: // 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
        this->set_type(TRI);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(6);
        break;

    case 10: // 9-node second order quadrangle (4 nodes associated with the vertices, 4 with the edges and 1 with the face).
        this->set_type(QUAD);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(9);
        break;

    case 11: // 10-node second order tetrahedron (4 nodes associated with the vertices and 6 with the edges).
        this->set_type(TET);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(10);
        break;

    case 12: // 27-node second order hexahedron (8 nodes associated with the vertices, 12 with the edges, 6 with the faces and 1 with the volume).
        this->set_type(HEX);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(27);
        break;

    case 13: // 18-node second order prism (6 nodes associated with the vertices, 9 with the edges and 3 with the quadrangular faces).
        this->set_type(PRISM);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(18);
        break;

    case 14: // 14-node second order pyramid (5 nodes associated with the vertices, 8 with the edges and 1 with the quadrangular face).
        this->set_type(PYRA);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(14);
        break;

    case 15: // 1-node point.
        this->set_type(POINT);
        this->set_order(1);
        this->set_is_complete(true);
        this->set_num_nodes(1);
        break;

    case 16: // 8-node second order quadrangle (4 nodes associated with the vertices and 4 with the edges).
        this->set_type(QUAD);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(8);
        break;

    case 17: // 20-node second order hexahedron (8 nodes associated with the vertices and 12 with the edges).
        this->set_type(HEX);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(20);
        break;

    case 18: // 15-node second order prism (6 nodes associated with the vertices and 9 with the edges).
        this->set_type(PRISM);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(15);
        break;

    case 19: // 13-node second order pyramid (5 nodes associated with the vertices and 8 with the edges).
        this->set_type(PYRA);
        this->set_order(2);
        this->set_is_complete(true);
        this->set_num_nodes(13);
        break;

    case 20: // 9-node third order incomplete triangle (3 nodes associated with the vertices, 6 with the edges)
        this->set_type(TRI);
        this->set_order(3);
        this->set_is_complete(false);
        this->set_num_nodes(9);
        break;

    case 21: // 10-node third order triangle (3 nodes associated with the vertices, 6 with the edges, 1 with the face)
        this->set_type(TRI);
        this->set_order(3);
        this->set_is_complete(true);
        this->set_num_nodes(10);
        break;

    case 22: // 12-node fourth order incomplete triangle (3 nodes associated with the vertices, 9 with the edges)
        this->set_type(TRI);
        this->set_order(4);
        this->set_is_complete(false);
        this->set_num_nodes(12);
        break;

    case 23: // 15-node fourth order triangle (3 nodes associated with the vertices, 9 with the edges, 3 with the face)
        this->set_type(TRI);
        this->set_order(4);
        this->set_is_complete(true);
        this->set_num_nodes(15);
        break;

    case 24: // 15-node fifth order incomplete triangle (3 nodes associated with the vertices, 12 with the edges)
        this->set_type(TRI);
        this->set_order(5);
        this->set_is_complete(false);
        this->set_num_nodes(15);
        break;

    case 25: // 21-node fifth order complete triangle (3 nodes associated with the vertices, 12 with the edges, 6 with the face)
        this->set_type(TRI);
        this->set_order(5);
        this->set_is_complete(true);
        this->set_num_nodes(21);
        break;

    case 26: // 4-node third order edge (2 nodes associated with the vertices, 2 internal to the edge)
        this->set_type(LINE);
        this->set_order(3);
        this->set_is_complete(true);
        this->set_num_nodes(4);
        break;

    case 27: // 5-node fourth order edge (2 nodes associated with the vertices, 3 internal to the edge)
        this->set_type(LINE);
        this->set_order(4);
        this->set_is_complete(true);
        this->set_num_nodes(5);
        break;

    case 28: // 6-node fifth order edge (2 nodes associated with the vertices, 4 internal to the edge)
        this->set_type(LINE);
        this->set_order(5);
        this->set_is_complete(true);
        this->set_num_nodes(6);
        break;

    case 29: // 20-node third order tetrahedron (4 nodes associated with the vertices, 12 with the edges, 4 with the faces)
        this->set_type(TET);
        this->set_order(3);
        this->set_is_complete(true);
        this->set_num_nodes(20);
        break;

    case 30: // 35-node fourth order tetrahedron (4 nodes associated with the vertices, 18 with the edges, 12 with the faces, 1 in the volume)
        this->set_type(TET);
        this->set_order(4);
        this->set_is_complete(true);
        this->set_num_nodes(35);
        break;

    case 31: // 56-node fifth order tetrahedron (4 nodes associated with the vertices, 24 with the edges, 24 with the faces, 4 in the volume)
        this->set_type(TET);
        this->set_order(5);
        this->set_is_complete(true);
        this->set_num_nodes(56);
        break;

    case 92: // 64-node third order hexahedron (8 nodes associated with the vertices, 24 with the edges, 24 with the faces, 8 in the volume)
        this->set_type(HEX);
        this->set_order(3);
        this->set_is_complete(true);
        this->set_num_nodes(64);
        break;

    case 93: // 125-node fourth order hexahedron (8 nodes associated with the vertices, 36 with the edges, 54 with the faces, 27 in the volume)
        this->set_type(HEX);
        this->set_order(4);
        this->set_is_complete(true);
        this->set_num_nodes(125);
        break;

    default:
        break;
    }

    // Get element tags:
    cemINT num_tags;
    mesh_file >> num_tags;
    if (num_tags >= 2)
    {
        mesh_file >> physical_id_;
        mesh_file >> geometrical_id_;
    }
    if (num_tags >=3)
    {
        mesh_file >> num_partitions_;
        partitions_.resize(num_partitions_);

        for (cemINT ii=0; ii<num_partitions_; ++ii)
        {
            mesh_file >> partitions_[ii];
        }
    }

    // Get element nodes:
    for (cemINT ii=0; ii<num_nodes_; ++ii)
    {
        node_ptrs_[ii] = reader.getNode();
    }
}


//************************************************************************************************//
/*! @brief Element::WriteToGmsgFile : Writes element in a mesh-file readable by Gmsh.
 * @param [in] mesh_file : ostream of the file where the mesh is being written
 * @author Felipe Valdes
 * @version 1.0 */
//************************************************************************************************//
void Element::WriteToGmsgFile(std::ostream &mesh_file)
{
    // Set element type:
    cemINT element_type;
    if (type_ == LINE && order_ == 1 && is_complete_ && num_nodes_ == 2)
        element_type = 1;

    if (type_ == TRI && order_ == 1 && is_complete_ && num_nodes_ == 3)
        element_type = 2;

    if (type_ == QUAD && order_ == 1 && is_complete_ && num_nodes_ == 4)
        element_type = 3;

    if (type_ == TET && order_ == 1 && is_complete_ && num_nodes_ == 4)
        element_type = 4;

    if (type_ == HEX && order_ == 1 && is_complete_ && num_nodes_ == 8)
        element_type = 5;

    if (type_ == PRISM && order_ == 1 && is_complete_ && num_nodes_ == 6)
        element_type = 6;

    if (type_ == PYRA && order_ == 1 && is_complete_ && num_nodes_ == 5)
        element_type = 7;

    if (type_ == LINE && order_ == 2 && is_complete_ && num_nodes_ == 3)
        element_type = 8;

    if (type_ == TRI && order_ == 2 && is_complete_ && num_nodes_ == 6)
        element_type = 9;

    if (type_ == QUAD && order_ == 2 && is_complete_ && num_nodes_ == 9)
        element_type = 10;

    if (type_ == TET && order_ == 2 && is_complete_ && num_nodes_ == 10)
        element_type = 11;

    if (type_ == HEX && order_ == 2 && is_complete_ && num_nodes_ == 27)
        element_type = 12;

    if (type_ == PRISM && order_ == 2 && is_complete_ && num_nodes_ == 18)
        element_type = 13;

    if (type_ == PYRA && order_ == 2 && is_complete_ && num_nodes_ == 14)
        element_type = 14;

    if (type_ == POINT && order_ == 1 && is_complete_ && num_nodes_ == 1)
        element_type = 15;

    if (type_ == QUAD && order_ == 2 && is_complete_ && num_nodes_ == 8)
        element_type = 16;

    if (type_ == HEX && order_ == 2 && is_complete_ && num_nodes_ == 20)
        element_type = 17;

    if (type_ == PRISM && order_ == 2 && is_complete_ && num_nodes_ == 15)
        element_type = 18;

    if (type_ == PYRA && order_ == 2 && is_complete_ && num_nodes_ == 13)
        element_type = 19;

    if (type_ == TRI && order_ == 3 && !is_complete_ && num_nodes_ == 9)
        element_type = 20;

    if (type_ == TRI && order_ == 3 && is_complete_ && num_nodes_ == 10)
        element_type = 21;

    if (type_ == TRI && order_ == 4 && !is_complete_ && num_nodes_ == 12)
        element_type = 22;

    if (type_ == TRI && order_ == 4 && is_complete_ && num_nodes_ == 15)
        element_type = 23;

    if (type_ == TRI && order_ == 5 && !is_complete_ && num_nodes_ == 15)
        element_type = 24;

    if (type_ == TRI && order_ == 5 && is_complete_ && num_nodes_ == 21)
        element_type = 25;

    if (type_ == LINE && order_ == 3 && is_complete_ && num_nodes_ == 4)
        element_type = 26;

    if (type_ == LINE && order_ == 4 && is_complete_ && num_nodes_ == 5)
        element_type = 27;

    if (type_ == LINE && order_ == 5 && is_complete_ && num_nodes_ == 6)
        element_type = 28;

    if (type_ == TET && order_ == 3 && is_complete_ && num_nodes_ == 20)
        element_type = 29;

    if (type_ == TET && order_ == 4 && is_complete_ && num_nodes_ == 35)
        element_type = 30;

    if (type_ == TET && order_ == 5 && is_complete_ && num_nodes_ == 56)
        element_type = 31;

    if (type_ == HEX && order_ == 3 && is_complete_ && num_nodes_ == 64)
        element_type = 92;

    if (type_ == HEX && order_ == 4 && is_complete_ && num_nodes_ == 125)
        element_type = 93;

    // Write element_id, element_type:
    mesh_file << element_id_ << " " << element_type << " ";

    // Write tags:
    if (num_partitions_ > 0)
    {
        mesh_file << num_partitions_ + 3 << " " << physical_id_ << " " << geometrical_id_ << " ";
        mesh_file << num_partitions_ << " ";
        for (cemINT ii=0; ii<num_partitions_; ++ii)
        {
            mesh_file << partitions_[ii] << " ";
        }
    }
    else
    {
        mesh_file << 2 << " " << physical_id_ << " " << geometrical_id_ << " ";
    }

    // Write nodes:
    for (cemINT ii=0; ii<num_nodes_; ++ii)
    {
        mesh_file << node_ptrs_[ii]->node_id() << " ";
    }
    mesh_file << std::endl;
}

