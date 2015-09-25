#ifndef CEMMESH_H
#define CEMMESH_H


#include <vector>
#include <iostream>
#include "element.h"

namespace cem_mesh
{
class NodeReader;
class ElementsOfMesh;
class NodesOfMesh;
class Element;
class Node;



//****************************************************************************//
//****************************************************************************//
class Mesh
{
public:
    // Default Constructor:
    Mesh() {initialize();}

    void initialize();
    void copy(const Mesh& mesh);

    // Copy Constructor:
    Mesh(const Mesh& mesh) {initialize(); copy(mesh);}

    // Read and Write from file:
    void ReadFromGmshFile(const std::string filename);
    void WriteToGmshFile(const std::string filename);


    friend NodeReader;
    friend ElementsOfMesh;
    friend NodesOfMesh;



private:
    std::vector<Node>       node_table_;
    std::vector<Element>    element_table_;
};
//****************************************************************************//




//****************************************************************************//
//****************************************************************************//
class Node: public V3D
{
public:
    // Default constructor:
    Node():V3D() {initialize();}

    void initialize();
    void copy(const Node& node);

    // Constructor with parameters:
    Node(const cemDOUBLE& x1, const cemDOUBLE& x2, const cemDOUBLE& x3);
    Node(const V3D& point);

    // Copy constructor:
    Node(const Node& node) {initialize(); copy(node);}
    Node& operator=(const Node& node) {initialize(); copy(node);}

    // Get data members:
    cemBOOL has_been_checked_in() const {return has_been_checked_in_;}
    cemBOOL is_element_boundary() const {return is_element_boundary_;}
    cemBOOL is_surface_boundary() const {return is_surface_boundary_;}

private:
    cemBOOL has_been_checked_in_;
    cemBOOL is_element_boundary_;
    cemBOOL is_surface_boundary_;
};
//****************************************************************************//




//****************************************************************************//
//****************************************************************************//
class NodeReader
{
public:
    // Constructor with parameters:
    NodeReader(Mesh& m, std::istream& in): mesh_(m), input_stream_(in) {}

    // Get data from outside:
    cemINT getNumberOfNodes();
    Node* getNode();

private:
    Mesh&           mesh_;
    std::istream&   input_stream_;
};
//****************************************************************************//




//****************************************************************************//
//****************************************************************************//
class Element
{
    enum ElementType {LINE,TRI,QUAD,TET,PRISM,HEX};

public:
    // Default constructor:
    Element() {initialize();}

    void initialize();
    void copy(const Element& elem);

    // Constructor with parameters:
    Element(const ElementType& type) {initialize(); type_=type;}
    Element(const ElementType& type, const cemINT& order);
    Element(const std::vector<Node*>& node_pointers);

    // Copy constructor:
    Element(const Element& elem) {initialize(); copy(elem);}
    Element& operator=(const Element& elem) {initialize(); copy(elem);}

    // Set data members:
    void set_type(const ElementType& type) {type_ = type;}
    void set_order(const cemINT& order) {order_ = order;}
    void set_is_surface_boundary(const cemBOOL& is_boundary) {is_surface_boundary_ = is_boundary;}
    void set_node_ptrs(const std::vector<Node*>& nodes) {node_ptrs_ = nodes;}

    // Get data members:
    ElementType get_type() const {return type_;}
    cemBOOL is_surface_boundary() const {return is_surface_boundary_;}
    cemINT get_order() const {return order_;}
    std::vector<Node*> get_node_ptrs() const {return node_ptrs_;}


private:
    ElementType         type_;
    cemBOOL             is_surface_boundary_;
    cemINT              order_;
    std::vector<Node*>  node_ptrs_;
};
//****************************************************************************//





}


#endif // CEMMESH_H
