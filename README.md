SLOPE
=====

Slope is a free (LGPL) **C** library that creates charts from numerical data. It's
design principle is the following: **THE ONLY DEPENDENCY IS CAIRO**, and the **API**
is familiar to the users of cairo. Additionaly an alternative build provides a Gtk
widget and some utilities so create simple chart windows and animations, such as real
time data display. This build of course makes slope **Gtk** dependent. The cairo only
build will always be maintained.

Slope is in it's early stages of development and still needs some optimization
and polishing. Some accessor methods to objects properties are also absent. But here's
what we already have: The following chart is the output of the test.c program in de
top level source repository.

![](https://github.com/exocode/slope/blob/master/figure.png)

Slope's basic usage is: create a **slope_figure_t**, add one or more **slope_metrics_t**
to it and add some **slope_item_t** to the metrics, then use function **slope_figure_draw()**
to stroke the resulting chart via a **cairo_t**.

Contributions to slope are welcome, propose your's to elvismtt@gmail.com

Special thanks to Remi Bertho (remi.bertho@openmailbox.org) for his contributions
