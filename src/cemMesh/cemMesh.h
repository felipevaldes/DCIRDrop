#ifndef CEMMESH_H
#define CEMMESH_H
#pragma once

#include <vector>
#include <iostream>
#include "cemSpace.h"
#include "cemTypes.h"

using cem_space::V3D;
using namespace cem_def;

namespace cem_mesh
{
class NodeReader;
class ElementsOfMesh;
class NodesOfMesh;
class Element;
class Node;



//************************************************************************************************//
/** @brief The Mesh class : Contains all data and actions related with an input mesh. */
//************************************************************************************************//
class Mesh
{
public:
    /** @brief Mesh : Default constructor. */
    Mesh() {;}

    // Copy cosntructor:
    Mesh(const Mesh& mesh);

    // Read and Write from file:
    void ReadFromGmshFile(const std::string filename);
    void WriteToGmshFile(const std::string filename);

    /** NodeReader allows hiding how a Mesh stores its nodes. */
    friend NodeReader;

private:
    cemINT                  num_nodes_;         /**< Number of nodes in the mesh. */
    cemINT                  num_elements_;      /**< Number of elements in the mesh. */
    std::vector<Node>       node_table_;        /**< Nodes in the mesh, from 1 to num_nodes_. */
    std::vector<Element>    element_table_;     /**< Elements in the mesh, from 1 to num_elements_ */

    void copy(const Mesh& mesh);
};
//************************************************************************************************//




//************************************************************************************************//
/** @brief The Node class : Simply a 3D point plus an ID and a few boolean flags . */
//************************************************************************************************//
class Node: public V3D
{
public:
    /** @brief Node : Default constructor */
    Node():V3D() {initialize();}

    // Constructor with parameters:
    Node(const cemDOUBLE& x1, const cemDOUBLE& x2, const cemDOUBLE& x3);
    Node(const V3D& point);

    // Copy constructor:
    Node(const Node& node);
    Node& operator=(const Node& node);

    // Get data members:
    cemBOOL has_been_checked_in() const;
    cemBOOL is_element_boundary() const;
    cemBOOL is_surface_boundary() const;
    cemINT node_id() const;

    // Set data members:
    void set_node_id(const cemINT& node_id);

private:
    cemINT  node_id_;                   /**< Unique identifier within the mesh. */
    cemBOOL has_been_checked_in_;       /**< TRUE if other flags have been validated */
    cemBOOL is_element_boundary_;       /**< TRUE if node is in element's boundary */
    cemBOOL is_surface_boundary_;       /**< TRUE if node is in surfaces's boundary */

    // Private member functions:
    void initialize();
    void copy(const Node& node);
};
//************************************************************************************************//



//************************************************************************************************//
/** @brief The NodeReader class : Class used to hide Mesh's node_table from Element. */
//************************************************************************************************//
class NodeReader
{
public:
    /** @brief Node : Constructor with parameters. */
    NodeReader(Mesh& m, std::istream& in): mesh_(m), input_stream_(in) {}

    /** @brief getNode : Gets node pointer from mesh_.node_table_. */
    Node* getNode()
    {
        cemINT node_number;
        input_stream_ >> node_number;
        return &mesh_.node_table_[node_number];
    }

private:
    Mesh&           mesh_;              /**< Mesh from which has access to node_table */
    std::istream&   input_stream_;      /**< Imput stream from wich the mesh is being read */
};
//************************************************************************************************//



//************************************************************************************************//
/** @brief The Element class : Element within a mesh.
 *
 * For each type and order of the element there is a specific node numbering:
 *
 *      Line:                   Line3:           Line4:
 *
 *      0----------1 --> u      0-----2----1     0----2----3----1
 *
 *      ===========================================================================================
 *      Triangle:               Triangle6:          Triangle9/10:          Triangle12/15:
 *
 *      v
 *      ^                                                                   2
 *      |                                                                   | \
 *      2                       2                    2                      9   8
 *      |`\                     |`\                  | \                    |     \
 *      |  `\                   |  `\                7   6                 10 (14)  7
 *      |    `\                 5    `4              |     \                |         \
 *      |      `\               |      `\            8  (9)  5             11 (12) (13) 6
 *      |        `\             |        `\          |         \            |             \
 *      0----------1 --> u      0-----3----1         0---3---4---1          0---3---4---5---1
 *
 *      ===========================================================================================
 *      Quadrangle:            Quadrangle8:            Quadrangle9:
 *
 *            v
 *            ^
 *            |
 *      3-----------2          3-----6-----2           3-----6-----2
 *      |     |     |          |           |           |           |
 *      |     |     |          |           |           |           |
 *      |     +---- | --> u    7           5           7     8     5
 *      |           |          |           |           |           |
 *      |           |          |           |           |           |
 *      0-----------1          0-----4-----1           0-----4-----1
 *
 *      ===========================================================================================
 *      Tetrahedron:                          Tetrahedron10:
 *
 *                         v
 *                       .
 *                     ,/
 *                    /
 *                 2                                     2
 *               ,/|`\                                 ,/|`\
 *             ,/  |  `\                             ,/  |  `\
 *           ,/    '.   `\                         ,6    '.   `5
 *         ,/       |     `\                     ,/       8     `\
 *       ,/         |       `\                 ,/         |       `\
 *      0-----------'.--------1 --> u         0--------4--'.--------1
 *       `\.         |      ,/                 `\.         |      ,/
 *          `\.      |    ,/                      `\.      |    ,9
 *             `\.   '. ,/                           `7.   '. ,/
 *                `\. |/                                `\. |/
 *                   `3                                    `3
 *                      `\.
 *                         ` w
 *
 *      ===========================================================================================
 *      Hexahedron:             Hexahedron20:          Hexahedron27:
 *
 *             v
 *      3----------2            3----13----2           3----13----2
 *      |\     ^   |\           |\         |\          |\         |\
 *      | \    |   | \          | 15       | 14        |15    24  | 14
 *      |  \   |   |  \         9  \       11 \        9  \ 20    11 \
 *      |   7------+---6        |   7----19+---6       |   7----19+---6
 *      |   |  +-- |-- | -> u   |   |      |   |       |22 |  26  | 23|
 *      0---+---\--1   |        0---+-8----1   |       0---+-8----1   |
 *       \  |    \  \  |         \  17      \  18       \ 17    25 \  18
 *        \ |     \  \ |         10 |        12|        10 |  21    12|
 *         \|      w  \|           \|         \|          \|         \|
 *          4----------5            4----16----5           4----16----5
 *
 *      ===========================================================================================
 *      Prism:                      Prism15:               Prism18:
 *
 *                 w
 *                 ^
 *                 |
 *                 3                       3                      3
 *               ,/|`\                   ,/|`\                  ,/|`\
 *             ,/  |  `\               12  |  13              12  |  13
 *           ,/    |    `\           ,/    |    `\          ,/    |    `\
 *          4------+------5         4------14-----5        4------14-----5
 *          |      |      |         |      8      |        |      8      |
 *          |    ,/|`\    |         |      |      |        |    ,/|`\    |
 *          |  ,/  |  `\  |         |      |      |        |  15  |  16  |
 *          |,/    |    `\|         |      |      |        |,/    |    `\|
 *         ,|      |      |\        10     |      11       10-----17-----11
 *       ,/ |      0      | `\      |      0      |        |      0      |
 *      u   |    ,/ `\    |    v    |    ,/ `\    |        |    ,/ `\    |
 *          |  ,/     `\  |         |  ,6     `7  |        |  ,6     `7  |
 *          |,/         `\|         |,/         `\|        |,/         `\|
 *          1-------------2         1------9------2        1------9------2
 *
 *      ===========================================================================================
 *      Pyramid:                     Pyramid13:                   Pyramid14:
 *
 *                     4                            4                            4
 *                   ,/|\                         ,/|\                         ,/|\
 *                 ,/ .'|\                      ,/ .'|\                      ,/ .'|\
 *               ,/   | | \                   ,/   | | \                   ,/   | | \
 *             ,/    .' | `.                ,/    .' | `.                ,/    .' | `.
 *           ,/      |  '.  \             ,7      |  12  \             ,7      |  12  \
 *         ,/       .' w |   \          ,/       .'   |   \          ,/       .'   |   \
 *       ,/         |  ^ |    \       ,/         9    |    11      ,/         9    |    11
 *      0----------.'--|-3    `.     0--------6-.'----3    `.     0--------6-.'----3    `.
 *       `\        |   |  `\    \      `\        |      `\    \     `\        |      `\    \
 *         `\     .'   +----`\ - \ -> v  `5     .'        10   \      `5     .' 13     10   \
 *           `\   |    `\     `\  \        `\   |           `\  \       `\   |           `\  \
 *             `\.'      `\     `\`          `\.'             `\`         `\.'             `\`
 *                1----------------2            1--------8-------2           1--------8-------2
 *                          `\
 *                             u
 *
 * The node ordering of a higher order (possibly curved) element is compatible with the
 * numbering of low order element (it is a generalization). We number nodes in the following order:
 *
 * - the element principal or corner vertices
 * - the internal nodes for each edge
 * - the internal nodes for each face
 * - the volume internal nodes
 *
 * The numbering for internal nodes is recursive, ie. the numbering follows that of the
 * nodes of an embedded edge/face/volume of lower order. The higher order nodes are assumed
 * to be equispaced. Edges and faces are numbered following the lowest order template that
 * generates a single high-order on this edge/face. Furthermore, an edge is oriented from
 * the vertex with the lowest to the highest index. The orientation of a face is such that
 * the computed normal points outward; the starting point is the vertex with the lowest index.
 */
//************************************************************************************************//
class Element
{
public:
    /** @brief The ElementType enum : Defines the type of element */
    enum ElementType
    {
        POINT=0,      /**< Single point element */
        LINE=1,       /**< Line element: straight or curved */
        TRI=2,        /**< Triangle: flat or curved */
        QUAD=3,       /**< Quadrangle: flat or curved */
        TET=4,        /**< Tetrahedron: flat or curved */
        HEX=5,        /**< Hexahedron: flat or curved */
        PRISM=6,      /**< Prism: flat or curved */
        PYRA=7        /**< Pyramid: flat or curved */
    };

    /** @brief Element : Default constructor */
    Element() {initialize();}

    // Constructor with parameters:
    Element(const ElementType& type);
    Element(const ElementType& type, const cemINT& order);
    Element(const cemINT& num_nodes, const std::vector<const Node*>& node_pointers);

    // Copy constructor:
    Element(const Element& elem);
    Element& operator=(const Element& elem);

    // Set data members:
    void set_element_id(const cemINT& elem_id);
    void set_type(const ElementType& type);
    void set_order(const cemINT& order);
    void set_is_complete(const cemBOOL& is_complete);
    void set_is_surface_boundary(const cemBOOL& is_boundary);
    void set_node_ptrs(const std::vector<const Node*>& nodes);
    void set_num_nodes(const cemINT& num_nodes);
    void set_physical_id(const cemINT& phys_id);
    void set_geometrical_id(const cemINT& geom_id);
    void set_num_partitions(const cemINT& num_partitions);
    void set_partitions(const std::vector<cemINT>& partitions);

    // Get data members:
    cemINT element_id() const;
    ElementType type() const;
    cemBOOL is_surface_boundary() const;
    cemINT order() const;
    cemBOOL is_complete() const;
    std::vector<const Node*> node_ptrs() const;
    cemINT num_nodes() const;
    cemINT physical_id() const;
    cemINT geometrical_id() const;
    cemINT num_partitions() const;
    std::vector<cemINT> partitions() const;


    // Read-Write from file:
    void ReadFromGmshFile(std::istream& mesh_file, NodeReader& reader);
    void WriteToGmsgFile(std::ostream& mesh_file);

private:
    // Private atributes:
    cemINT              element_id_;            /**< Unique identifier whithin the mesh */
    ElementType         type_;                  /**< Type of element */
    cemBOOL             is_complete_;           /**< TRUE if polynomial expansion is complete */
    cemBOOL             is_surface_boundary_;   /**< TRUE if element is in the surface boundary */
    cemINT              order_;                 /**< Polynomial order of the element >= 1 */
    cemINT              physical_id_;           /**< Physical entity to which element belongs */
    cemINT              geometrical_id_;        /**< Geometrical entity to which element belongs */
    cemINT              num_partitions_;        /**< Number of partitions to which element belongs */
    std::vector<cemINT> partitions_;            /**< Vector of partitions to which element belongs */
    cemINT              num_nodes_;             /**< Number of nodes that define the element */
    std::vector<const Node*>  node_ptrs_;       /**< Vector of nodes that define the element */

    // Private member functions:
    void initialize();
    void copy(const Element& elem);
};
//************************************************************************************************//





}


#endif // CEMMESH_H
