#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { double x, y, z; int group; } point_t, *point;

double randf(double m)
{
        return m * rand() / (RAND_MAX - 1.);
}

point gen_xy(int count, double radius)
{
        double alpha, beta, gamma, r;
        point p, pt = (point)malloc(sizeof(point_t) * count);

        /* note: this is not a uniform 2-d distribution */
        for (p = pt + count; p-- > pt;) {
                alpha = randf(2 * M_PI);
                beta = randf(2 * M_PI);
                gamma = randf(2 * M_PI);
                r = randf(radius);
                p->x = r * cos(alpha);
                p->y = r * cos(beta);
                p->z = r * cos(gamma);
        }

        return pt;
}

inline double dist3(point a, point b)
{
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

inline int
nearest(point pt, point cent, int n_cluster, double *d2)
{
        int i, min_i;
        point c;
        double d, min_d;

#	define for_n for (c = cent, i = 0; i < n_cluster; i++, c++)
        for_n {
                min_d = HUGE_VAL;
                min_i = pt->group;
                for_n {
                        if (min_d > (d = dist3(c, pt))) {
                                min_d = d; min_i = i;
                        }
                }
        }
        if (d2) *d2 = min_d;
        return min_i;
}

void kpp(point pts, int len, point cent, int n_cent)
{
#	define for_len for (j = 0, p = pts; j < len; j++, p++)
        int i, j;
        int n_cluster;
        double sum, *d = (double*)malloc(sizeof(double) * len);

        point p, c;
        cent[0] = pts[ rand() % len ];
        for (n_cluster = 1; n_cluster < n_cent; n_cluster++) {
                sum = 0;
                for_len {
                        nearest(p, cent, n_cluster, d + j);
                        sum += d[j];
                }
                sum = randf(sum);
                for_len {
                        if ((sum -= d[j]) > 0) continue;
                        cent[n_cluster] = pts[j];
                        break;
                }
        }
        for_len p->group = nearest(p, cent, n_cluster, 0);
        free(d);
}

point lloyd(point pts, int len, int n_cluster)
{
        int i, j, min_i;
        int changed;

        point cent = (point)malloc(sizeof(point_t) * n_cluster), p, c;

        /* assign init grouping randomly */
        //for_len p->group = j % n_cluster;

        /* or call k++ init */
        kpp(pts, len, cent, n_cluster);

        do {
                /* group element for centroids are used as counters */
                for_n { c->group = 0; c->x = c->y = 0; }
                for_len {
                        c = cent + p->group;
                        c->group++;
                        c->x += p->x; c->y += p->y;
                }
                for_n { c->x /= c->group; c->y /= c->group; }

                changed = 0;
                /* find closest centroid of each point */
                for_len {
                        min_i = nearest(p, cent, n_cluster, 0);
                        if (min_i != p->group) {
                                changed++;
                                p->group = min_i;
                        }
                }
        } while (changed > (len >> 10)); /* stop when 99.9% of points are good */

        for_n { c->group = i; }

        return cent;
}
