/// \file node.cpp Implementation of node system

#include "node.hpp"

#include "exceptions.hpp"
#include "logging.hpp"
#include "utils.hpp"

#include <algorithm>

namespace mute {


static NodeId operator++(NodeId& id) {
    id = static_cast<NodeId>(static_cast<int>(id) + 1);
    return id;
}

static LinkId operator++(LinkId& id) {
    id = static_cast<LinkId>(static_cast<int>(id) + 1);
    return id;
}

void NodeGraph::NodeProxy::check() const
{
    if (!graph.nodes.count(id)) {
        throw ProxyExpired(compose(
            "Node with id ",
            static_cast<int>(id),
            " has been removed from the graph"
        ));
    }
}

std::vector<NodeGraph::LinkProxy> NodeGraph::NodeProxy::links()
{
    check();

    std::vector<LinkProxy> links;
    for (const auto& item: graph.links) {
        const Link& link = item.second;
        if (link.x == id || link.y == id)
            links.emplace_back(LinkProxy{graph, item.first});
    }

    return links;
}

std::vector<NodeGraph::NodeProxy> NodeGraph::NodeProxy::neighbors()
{
    check();

    std::vector<NodeProxy> nodes;
    for (const auto& link_proxy: links()) {
        if (link_proxy.a().id == id) {
            nodes.emplace_back(NodeProxy{graph, link_proxy.a().id});
        } else {
            nodes.emplace_back(NodeProxy{graph, link_proxy.b().id});
        }
    }

    return nodes;
}

void NodeGraph::LinkProxy::check() const
{
    if (!graph.links.count(id)) {
        throw ProxyExpired(compose(
            "Link with id ",
            static_cast<int>(id),
            " has been removed from the graph"
        ));
    }
}

NodeGraph::NodeProxy NodeGraph::LinkProxy::a()
{
    check();
    return NodeProxy{graph, graph.links[id].x};
}

NodeGraph::NodeProxy NodeGraph::LinkProxy::b()
{
    check();
    return NodeProxy{graph, graph.links[id].y};
}

const NodeGraph::NodeProxy NodeGraph::LinkProxy::a() const
{
    check();
    return NodeProxy{graph, graph.links[id].x};
}

const NodeGraph::NodeProxy NodeGraph::LinkProxy::b() const
{
    check();
    return NodeProxy{graph, graph.links[id].y};
}

NodeGraph::NodeProxy NodeGraph::operator[](NodeId id)
{
    if (!nodes.count(id)) {
        throw KeyError(compose(
            "No node with id ",
            static_cast<int>(id),
            " exists"
        ));
    }

    return NodeProxy{*this, id};
}

NodeGraph::LinkProxy NodeGraph::operator[](LinkId id)
{
    if (!links.count(id)) {
        throw KeyError(compose(
            "No link with id ",
            static_cast<int>(id),
            " exists"
        ));
    }

    return LinkProxy{*this, id};
}

void NodeGraph::check(const Link& link) const
{
    if (!nodes.count(link.x) || !nodes.count(link.y)) {
        throw KeyError(compose(
            "Link between node ",
            static_cast<int>(link.x),
            " and node ",
            static_cast<int>(link.y),
            " is to a non-existing node"
        ));
    }
}

NodeGraph::NodeProxy NodeGraph::insert(Node node)
{
    NodeId id = ++top_node;
    nodes[id] = node;
    return NodeProxy{*this, id};
}

NodeGraph::LinkProxy NodeGraph::insert(Link link)
{
    check(link);

    LinkId id = ++top_link;
    links[id] = link;
    return LinkProxy{*this, id};
}

NodeGraph::NodeProxy NodeGraph::insert(Node node, NodeId id)
{
    if (id == NodeId::Auto) {
        return insert(node);
    }

    if (nodes.count(id)) {
        throw KeyExistsError(compose(
            "A node with the id ",
            static_cast<int>(id),
            " already exists"
        ));
    }

    top_node = std::max(top_node, id);
    nodes[id] = node;
    return NodeProxy{*this, id};
}

NodeGraph::LinkProxy NodeGraph::insert(Link link, LinkId id)
{
    if (id == LinkId::Auto) {
        return insert(link);
    }

    check(link);

    if (links.count(id)) {
        throw KeyExistsError(compose(
            "A link with the id ",
            static_cast<int>(id),
            " already exists"
        ));
    }

    top_link = std::max(top_link, id);
    links[id] = link;
    return LinkProxy{*this, id};
}

LoggingStream& operator<<(
    LoggingStream& ls,
    const NodeGraph::NodeProxy& node_proxy
) {
    ls << "<node " << static_cast<int>(node_proxy.id) << ">";
    return ls;
}

LoggingStream& operator<<(
    LoggingStream& ls,
    const NodeGraph::LinkProxy& link_proxy
) {
    ls << "<link " << static_cast<int>(link_proxy.id) << " " << link_proxy.a()
       << " " << link_proxy.b() << ">";
    return ls;
}


} // namespace mute
