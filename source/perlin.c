#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "sdnoise1234.h"



typedef struct _perlin {
    t_object  ob;
    void    *outlet;
} t_perlin;

void *perlin_new(long n);
void perlin_free(t_perlin *x);
void perlin_float(t_perlin *x, double f);
void perlin_list(t_perlin *x, t_symbol *sym, long argc, t_atom *argv);



t_class *perlin_class;


void ext_main(void *r)
{
    t_class *c;
    
    c = class_new("perlin", (method)perlin_new, (method)perlin_free, sizeof(t_perlin), 0L, 0);
    
    class_addmethod(c, (method)perlin_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)perlin_list, "list", A_GIMME, 0);
    
    class_register(CLASS_BOX, c);
    perlin_class = c;
}


void *perlin_new(long n)
{
    t_perlin *x = (t_perlin *)object_alloc(perlin_class);
    x->outlet = floatout((t_object *)x);
    
    return x;
}


void perlin_free(t_perlin *x)
{
    object_free(x->outlet);
}



void perlin_float(t_perlin *x, double f) {
    outlet_float(x->outlet, sdnoise1((float)f, NULL));
}

void perlin_list(t_perlin *x, t_symbol *sym, long argc, t_atom *argv) {
    switch (argc) {
        case 2:
            outlet_float(x->outlet, sdnoise2(atom_getfloat(argv),
                                             atom_getfloat(argv + 1),
                                             NULL,
                                             NULL));
            break;
        case 3:
            outlet_float(x->outlet, sdnoise3(atom_getfloat(argv),
                                             atom_getfloat(argv + 1),
                                             atom_getfloat(argv + 2),
                                             NULL,
                                             NULL,
                                             NULL));
            break;
        case 4:
            outlet_float(x->outlet, sdnoise4(atom_getfloat(argv),
                                             atom_getfloat(argv + 1),
                                             atom_getfloat(argv + 2),
                                             atom_getfloat(argv + 3),
                                             NULL,
                                             NULL,
                                             NULL,
                                             NULL));
            break;
    }
}


