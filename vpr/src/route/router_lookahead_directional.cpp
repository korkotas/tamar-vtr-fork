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

const int KMAX = 5;

typedef enum {
    NE, // North-East dx >=0 dy >= 0
    NW, // North-West dx < 0 dy >= 0
    SE, // South-East dx >= 0 dy < 0
    SW  // South-West dx < 0 dy < 0
} Cong_Direction;

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

void sum_neighbors(const RRGraphView& rr_graph, RRNodeId node_idx, int hops, t_rr_node_route_inf& lookahead_storage) {
    if (hops > KMAX)
        return;
    
    // Iterate over edges of node to get neighbors
    for (t_edge_size edge : rr_graph.edges(node_idx)) {
        RRNodeId neighbor = rr_graph.edge_sink_node(node_idx, edge);
        auto direction = get_direction(node_idx, neighbor);

        // Update the cost with this direction
        // lookahead_storage.value[direction] += neighbor.base_cost
        sum_neighbors(rr_graph, neighbor, hops + 1, lookahead_storage);

    }
}


/***
 * Computes the directional lookahead 
 * for all nodes in the rr_graph
 * 
*/
void compute_directional_lookahead(const RRGraphView& rr_graph, RoutingContext& route_ctx) {
    int num_rr_nodes = rr_graph.num_nodes();

    // Iterate over every node
    for (int rr_node_id = 0; rr_node_id < num_rr_nodes; rr_node_id++) {
        // Get the pointer to the directional lookahead storage
        auto node_idx = RRNodeId(rr_node_id);
        t_rr_node_route_inf& lookahead_storage = route_ctx.rr_node_route_inf[node_idx];
        sum_neighbors(rr_graph, node_idx, 0, lookahead_storage);
    }
}

/**
 * Recomputes the directional lookahead
 * only for the nodes in the bounding box
*/
void compute_directional_lookahead_bb() {

}