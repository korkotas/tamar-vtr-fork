#include <cmath>
#include <vector>
#include "connection_router_interface.h"
#include "vpr_types.h"
#include "vpr_error.h"
#include "vpr_utils.h"
#include "globals.h"
#include "vtr_math.h"
#include "vtr_log.h"
#include "vtr_assert.h"
#include "vtr_time.h"
#include "vtr_geometry.h"
#include "rr_graph2.h"
#include "rr_graph.h"
#include "route_common.h"


#include "router_lookahead_map_utils.h" // For get_xy_deltas
#include "router_lookahead_directional.h"

/**
 * Function for calculating the cost for the lookahead
 * @param node_idx the node we are calculating the cost for
 * @param hops the number of hops for exponential decay
 * @param route_ctx the routing context
*/
float cost_func(RRNodeId node_idx, int hops, RoutingContext& route_ctx) {
    return route_ctx.rr_node_route_inf[node_idx].acc_cost * ALPHA_POWERS[hops]; 
}


/***
 * Gets which direction is the to_node from from_node
*/
Cong_Direction get_direction(RRNodeId from_node, RRNodeId to_node) {
    auto [dx, dy] = util::get_xy_deltas(from_node, to_node);

    if (dx >= 0 && dy >= 0)
        return NE;
    else if (dx < 0 && dy >= 0)
        return NW;
    else if (dx >= 0 && dy < 0) 
        return SE;
    else
        return SW;
                
}

/**
 * Recursive function for calculating the directional costs of the parent node
 * 
 * @param rr_graph the routing graph storage
 * @param node_idx id of the current neighbor for exploration
 * @param lookahead_storage pointer to the parent node's routing cost storage
*/
void sum_neighbors(const RRGraphView& rr_graph, RRNodeId node_idx, RRNodeId parent_idx, int hops, std::set<RRNodeId> fx, RoutingContext& route_ctx) {
    // Skip if node already visited
    if (fx.find(node_idx) != fx.end()) {
        return;
    }

    if (hops > KMAX)
        return;

    // Keep track of already visited nodes
    fx.insert(node_idx);

    // Iterate over edges of node to get neighbors
    for (t_edge_size edge : rr_graph.edges(node_idx)) {
        RRNodeId neighbor = rr_graph.edge_sink_node(node_idx, edge);
        auto direction = get_direction(node_idx, neighbor);

        // Update the cost with this direction
        route_ctx.rr_node_route_inf[parent_idx].directional_cost[direction] += cost_func(node_idx, hops, route_ctx);
        sum_neighbors(rr_graph, neighbor, parent_idx, hops + 1, fx, route_ctx);

    }
}


/***
 * Computes the directional lookahead 
 * for all nodes in the rr_graph
 * 
 * @param rr_graph the routing graph storage
 * @param route_ctx the routing context that has access to each node cost parameters
 * 
*/
void compute_directional_lookahead(const RRGraphView& rr_graph, RoutingContext& route_ctx) {
    int num_rr_nodes = rr_graph.num_nodes();

    // Iterate over every node
    for (int rr_node_id = 0; rr_node_id < num_rr_nodes; rr_node_id++) {
        // Get the pointer to the directional lookahead storage
        auto node_idx = RRNodeId(rr_node_id);

        // Reset the old directional values
        for (int i  = 0; i < NUM_DIRECTIONS; i++) {
            route_ctx.rr_node_route_inf[node_idx].directional_cost[i] = 0;
        }

        // The set to keep track of which nodes were visited
        std::set<RRNodeId> fx;
        sum_neighbors(rr_graph, node_idx, node_idx, 0, fx, route_ctx);
    }
}

/**
 * Recomputes the directional lookahead
 * only for the nodes in the bounding box
*/
void compute_directional_lookahead_bb() {

}