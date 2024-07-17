#include "vpr_types.h"
#include "vpr_utils.h"
#include "globals.h"
#include "rr_graph2.h"
#include "rr_graph.h"
#

// Maximum hops constant
const int KMAX = 4;
const float ALPHA_POWERS[] = {
    1.0f,
    0.5f, 
    0.25f,
    0.125f,
    0.0625f,
    0.03125f
};

// Congestion directions
typedef enum {
    NE, // North-East dx >= 0 dy >= 0
    NW, // North-West dx < 0 dy >= 0
    SE, // South-East dx >= 0 dy < 0
    SW, // South-West dx < 0 dy < 0
    NUM_DIRECTIONS
} Cong_Direction;

// Function for calculating the cost for the lookahead
float cost_func(RRNodeId node_idx, int hops, RoutingContext& route_ctx);

// Function to get direction based on the difference in x and y coordinates
Cong_Direction get_direction(RRNodeId from_node, RRNodeId to_node);

// Recursive function to sum neighbors cost
void sum_neighbors(const RRGraphView& rr_graph, RRNodeId node_idx, RRNodeId parent_idx, int hops, std::set<RRNodeId> fx, RoutingContext& route_ctx);

// Function to compute directional lookahead for all nodes in the rr_graph
void compute_directional_lookahead(const RRGraphView& rr_graph, RoutingContext& route_ctx);

// Function to recompute directional lookahead only for nodes in the bounding box
void compute_directional_lookahead_bb();