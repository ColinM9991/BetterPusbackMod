/*
 * CDDL HEADER START
 *
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 *
 * CDDL HEADER END
 * Copyright 2026 ColinM. All rights reserved.
 */

/*
 * Computes the outline BpB derives from an aircraft .acf file.
 *
 * The output should be pasted in the objects/overrides/acf_outlines.txt file. The headers will align with the acf name which BpB checks at runtime.
 *
 * Usage: acf_outline_dump <path/to/aircraft.acf> [section name ...]
 */

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <acfutils/log.h>

#include "acf_outline.h"

static void
log_to_stderr(const char *msg) {
    fputs(msg, stderr);
}

int
main(int argc, char **argv) {
    acf_outline_t *outline;
    const char *name;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <aircraft.acf> [extra section name ...]\n",
                argv[0]);
        return (1);
    }

    log_init(log_to_stderr, "acf_outline_dump");

    outline = acf_outline_read(argv[1]);
    if (outline == NULL) {
        fprintf(stderr, "%s: unable to read an outline\n", argv[1]);
        return (1);
    }

    name = strrchr(argv[1], '/');
    if (name == NULL)
        name = strrchr(argv[1], '\\');
    name = (name != NULL ? name + 1 : argv[1]);

    printf("[%s", name);
    for (int i = 2; i < argc; i++)
        printf(" %s", argv[i]);
    printf("]\n");
    printf("semispan %.4f\n", outline->semispan);
    printf("length %.4f\n", outline->length);
    printf("wingtip %.4f %.4f\n", outline->wingtip.x, outline->wingtip.y);
    for (size_t i = 0; i < outline->num_pts; i++) {
        vect2_t pt = outline->pts[i];

        if (IS_NULL_VECT2(pt))
            printf("pt null\n");
        else
            printf("pt %.4f %.4f\n", pt.x, pt.y);
    }

    acf_outline_free(outline);
    return (0);
}
