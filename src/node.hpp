/// \file node.hpp Node system

#ifndef MUTE_NODE_HPP
#define MUTE_NODE_HPP

#include <map>
#include <vector>

namespace mute {

// Forward declarations
class LoggingStream;


/**
 * \defgroup node Node System
 * @{
 *
 * \brief The heart of Mute
 *
 * Every action in Mute revolves around manipulation and inspection of a
 * node graph that contains all the data about places, characters,
 * objects, etc.  Nodes are linked to each other with biderictional
 * links that themselve describe what kind they are and how the linked
 * nodes relate to each other in the world.  The structs \ref Node and
 * \ref Link contain the actual data stored in nodes and links
 * respectively while \ref NodeGraph maintains a consisten graph of
 * nodes and links.  The usual way to access nodes and links in a
 * NodeGraph is to use the <tt>[]</tt> operator with a \ref NodeId or
 * \ref LinkId.  This returns either a NodeGraph::NodeProxy or a
 * NodeGraph::LinkProxy depending on the id passed.  Access through the
 * \ref NodeGraph proxy objects ensure that the graph stays consistent.
 * That is, no link points to a non-existing node.
 */

/**
 * \brief Node identifier
 *
 * A unique identifier for a Node in a NodeGraph.  The special id
 * NodeId::Auto signals that an id should be created when inserting a
 * new node.
 */
enum class NodeId : int {

    /**
     * \brief Signals a new unique id should be assigned automatically
     */
    Auto
};

/**
 * \brief Link identifier
 *
 * A unique identifier for a Link in a NodeGraph.  The special id
 * NodeId::Auto signals that an id should be created when inserting a
 * new node.
 */
enum class LinkId : int {

    /**
     * \brief Signals a new unique id should be assigned automatically
     */
    Auto
};

/**
 * \brief Base structure for Mute data
 *
 * Holds the information about node
 */
struct Node {
};

/**
 * \brief Base structure for Mute relations
 */
struct Link {
    NodeId x;
    NodeId y;
};

/**
 * \brief Graph container for nodes with links
 */
class NodeGraph {
    std::map<NodeId, Node> nodes;
    std::map<LinkId, Link> links;

    NodeId top_node = NodeId::Auto;
    LinkId top_link = LinkId::Auto;

    void check(const Link& link) const;

public:
    class LinkProxy;

    /**
     * \brief Proxy for accessing Nodes
     */
    class NodeProxy {
        void check() const;

    public:
        NodeGraph& graph;
        const NodeId id;

        std::vector<LinkProxy> links();
        std::vector<NodeProxy> neighbors();
    };

    /**
     * \brief Proxy for accessing Nodes
     */
    class LinkProxy {
        void check() const;

    public:
        NodeGraph& graph;
        const LinkId id;

        NodeProxy a();
        NodeProxy b();

        const NodeProxy a() const;
        const NodeProxy b() const;
    };

    /**
     * \brief Node lookup
     */
    NodeProxy operator[](NodeId id);

    /**
     * \brief Link lookup
     */
    LinkProxy operator[](LinkId id);

    /**
     * \brief Node insertion
     */
    NodeProxy insert(Node node);

    /**
     * \brief Link insertion
     */
    LinkProxy insert(Link link);

    /**
     * \brief Node insertion
     */
    NodeProxy insert(Node node, NodeId id);

    /**
     * \brief Link insertion
     */
    LinkProxy insert(Link link, LinkId id);

    /**
     * \brief Node erasure
     */
    void erase(NodeId id);

    /**
     * \brief Link erasure
     */
    void erase(LinkId id);
};

/**
 * \brief Node logging
 */
LoggingStream& operator<<(LoggingStream& ls, const NodeGraph::LinkProxy& link);

/**
 * \brief Link logging
 */
LoggingStream& operator<<(LoggingStream& ls, const NodeGraph::NodeProxy& node);

/**
 * @} // defgroup logging
 */


} // namespace mute

#endif // MUTE_NODE_HPP
