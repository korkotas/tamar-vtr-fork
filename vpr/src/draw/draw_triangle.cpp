#include <cstdio>
#include <cfloat>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <array>
#include <iostream>

#include "vtr_assert.h"
#include "vtr_ndoffsetmatrix.h"
#include "vtr_memory.h"
#include "vtr_log.h"
#include "vtr_color_map.h"
#include "vtr_path.h"

#include "vpr_utils.h"
#include "vpr_error.h"

#include "globals.h"
#include "draw_color.h"
#include "draw.h"
#include "draw_rr.h"
#include "draw_rr_edges.h"
#include "draw_toggle_functions.h"
#include "draw_triangle.h"
#include "draw_searchbar.h"
#include "draw_mux.h"
#include "read_xml_arch_file.h"
#include "draw_global.h"
#include "draw_basic.h"

#include "move_utils.h"

#ifdef VTR_ENABLE_DEBUG_LOGGING
#    include "move_utils.h"
#endif

#ifdef WIN32 /* For runtime tracking in WIN32. The clock() function defined in time.h will *
              * track CPU runtime.														   */
#    include <time.h>
#else /* For X11. The clock() function in time.h will not output correct time difference   *
       * for X11, because the graphics is processed by the Xserver rather than local CPU,  *
       * which means tracking CPU time will not be the same as the actual wall clock time. *
       * Thus, so use gettimeofday() in sys/time.h to track actual calendar time.          */
#    include <sys/time.h>
#endif

#ifndef NO_GRAPHICS

//To process key presses we need the X11 keysym definitions,
//which are unavailable when building with MINGW
#    if defined(X11) && !defined(__MINGW32__)
#        include <X11/keysym.h>
#    endif

/**
 * Retrieves the current zoom level based on the visible world and screen dimensions.
 * The zoom level is calculated as the ratio of the visible world width to the visible screen width.
 * The zoom level can be adjusted within the specified range and scaled by a default zoom factor.
 *
 * @param g The renderer object.
 * @param default_zoom The default zoom factor for the default zoom level (1.0 by default).
 * @param min_zoom The minimum allowed zoom level (0.5 by default).
 * @param max_zoom The maximum allowed zoom level (2.3 by default).
 * @return The calculated zoom level.
 */
double get_zoom_level(ezgl::renderer* g) {
    ezgl::rectangle current_view = g->get_visible_world();
    double zoom_level = current_view.width() / g->get_visible_screen().width();

    double min_zoom = 0.5;
    double max_zoom = 2.3;

    if (zoom_level < min_zoom) {
        zoom_level = min_zoom;
    } else if (zoom_level > max_zoom) {
        zoom_level = max_zoom;
    }

    return zoom_level;
}

/**
 * Draws a small triangle, at a position along a line from 'start' to 'end'.
 *
 * 'relative_position' [0., 1] defines the triangle's position relative to 'start'.
 *
 * A 'relative_position' of 0. draws the triangle centered at 'start'.
 * A 'relative_position' of 1. draws the triangle centered at 'end'.
 * Fractional values draw the triangle along the line.
 *
 * 'g' is the renderer object, 'start' and 'end' are the line segment points,
 * 'relative_position' is the position of the triangle along the line,
 * and 'arrow_size' is the size of the triangle.
 */
void draw_triangle_along_line(ezgl::renderer* g, ezgl::point2d start, ezgl::point2d end, float relative_position, float arrow_size) {
    VTR_ASSERT(relative_position >= 0. && relative_position <= 1.);
    float xdelta = end.x - start.x;
    float ydelta = end.y - start.y;

    float xtri = start.x + xdelta * relative_position;
    float ytri = start.y + ydelta * relative_position;

    double zoom = get_zoom_level(g); // Get the current zoom level

    float scaled_arrow_size = arrow_size * zoom; // Scale arrow size based on zoom level

    draw_triangle_along_line(g, xtri, ytri, start.x, end.x, start.y, end.y, scaled_arrow_size);
}

/* Draws a triangle with its center at loc, and of length & width
 * arrow_size, rotated such that it points in the direction
 * of the directed line segment start -> end.
 *
 * 'g' is the renderer object, 'loc' is the center of the triangle,
 * 'start' and 'end' are the line segment points, and 'arrow_size' is the size of the triangle.
 */
void draw_triangle_along_line(ezgl::renderer* g, ezgl::point2d loc, ezgl::point2d start, ezgl::point2d end, float arrow_size) {
    double zoom = get_zoom_level(g);             // Get the current zoom level
    float scaled_arrow_size = arrow_size * zoom; // Scale arrow size based on zoom level
    draw_triangle_along_line(g, loc.x, loc.y, start.x, end.x, start.y, end.y, scaled_arrow_size);
}

/**
 * Draws a triangle with its center at (xend, yend), and of length & width
 * arrow_size, rotated such that it points in the direction
 * of the directed line segment (x1, y1) -> (x2, y2).
 *
 * Note that the parameters are in a strange order.
 *
 * 'g' is the renderer object, 'xend' and 'yend' are the coordinates of the triangle's center,
 * 'x1' and 'x2' are the x-coordinates of the line segment points,
 * 'y1' and 'y2' are the y-coordinates of the line segment points,
 * 'arrow_size' is the size of the triangle.
 */
void draw_triangle_along_line(ezgl::renderer* g, float xend, float yend, float x1, float x2, float y1, float y2, float arrow_size) {
    double zoom = get_zoom_level(g); // Get the current zoom level

    float switch_rad = arrow_size / 2 * zoom; // Scale switch_rad based on zoom level
    float xdelta, ydelta;
    float magnitude;
    float xunit, yunit;
    float xbaseline, ybaseline;

    std::vector<ezgl::point2d> poly;

    xdelta = x2 - x1;
    ydelta = y2 - y1;
    magnitude = sqrt(xdelta * xdelta + ydelta * ydelta);

    xunit = xdelta / magnitude;
    yunit = ydelta / magnitude;

    poly.push_back({xend + xunit * switch_rad, yend + yunit * switch_rad});
    xbaseline = xend - xunit * switch_rad;
    ybaseline = yend - yunit * switch_rad;
    poly.push_back({xbaseline + yunit * switch_rad, ybaseline - xunit * switch_rad});
    poly.push_back({xbaseline - yunit * switch_rad, ybaseline + xunit * switch_rad});

    g->fill_poly(poly);
}

#endif
