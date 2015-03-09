/*
 * Copyright (C) 2015  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "slope/scene_p.h"
#include "slope/metrics_p.h"
#include <stdlib.h>
#include <cairo.h>


slope_scene_t* slope_scene_create()
{
    slope_scene_t *scene = malloc(sizeof(slope_scene_t));
    scene->metrics = NULL;
    scene_color_set_name(&scene->back_color, SLOPE_WHITE);
    scene->fill_back = 1;
    // TODO
}


/**
 * Drestroys scene
 */
void slope_scene_destroy (slope_scene_t *scene)
{
    if (scene == NULL) {
        return;
    }
    if (scene->_cleanup_fn) {
        (*scene->_cleanup_fn)(scene);
    }
    slope_list_destroy(scene->metrics);
    free(scene);
    scene = NULL;
}

/**
 * Draw the contents of scenes to the surface targeted by cr
 */
void slope_scene_draw (slope_scene_t *scene, cairo_t *cr, slope_rect_t *area)
{
    /* affects only area */
    cairo_stroke(cr);
    cairo_save(cr);
    cairo_rectangle(cr, area->x, area->y,
                    area->width, area->height);
    cairo_clip(cr);
    /* fill background if required */
    if (scene->fill_back) {
        cairo_set_source_rgba(cr,
                              scene->back_color.red,
                              scene->back_color.green,
                              scene->back_color.blue,
                              scene->back_color.alpha);
        cairo_rectangle(cr, area->x, area->y,
                        area->width, area->height);
        cairo_paint(cr);
    }
    /* draw contents */
    slope_iterator_t *iter =
        slope_list_first(scene->metrics);
    while (iter) {
        slope_metrics_t *metrics =
            (slope_metrics_t*) slope_iterator_data(iter);
        if (slope_metrics_visible(metrics)) {
            _slope_metrics_draw(metrics, cr, &area);
        }
        slope_iterator_next(&iter);
    }
    cairo_restore(cr);
}

/*
 * Writes the scene to a png file
 */
void slope_scene_write_to_png (slope_scene_t *scene,
                               const char *filename,
                               int width, int height)
{
    cairo_surface_t *image =
        cairo_image_surface_create(CAIRO_FORMAT_RGB24,
                                   width, height);
    cairo_t *cr = cairo_create(image);
    slope_rect_t rect;
    slope_rect_set(&rect, 0.0, 0.0, width, height);
    slope_scene_draw(scene, cr, &rect);
    cairo_surface_write_to_png(image, filename);
    cairo_surface_destroy(image);
    cairo_destroy(cr);
}


void slope_scene_set_back_color_name (slope_scene_t *scene,
                                      slope_color_name_t color_name)
{
    slope_color_set_name(&scene->back_color, color_name);
}


void slope_scene_add_metrics (slope_scene_t *scene,
                              slope_metrics_t *metrics)
{
    scene->metrics = slope_list_append(scene->metrics, plot);
}


slope_list_t* slope_scene_metrics_list (slope_scene_t *scene)
{
    return scene->metrics;
}


/* slope/scene.c */
