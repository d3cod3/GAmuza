
#include "randomUtils.h"

//--------------------------------------------------
int * ofUniqueRandom(int dim) {
    int * keys = new int[dim];
    int * world = new int[dim];
    int magnitude = dim-1;
    int rr = (int)(ofRandomuf()*magnitude);

    for(int i=0;i<dim;i++){
        world[i] = i;
        keys[i] = 0;
    }

    for(int i=0;i<dim;i++){
        int pos = int(ofRandom(0,magnitude));
        keys[i] = world[pos];
        world[pos] = world[magnitude];
        magnitude--;
    }
    int buffer = keys[0];
    keys[0] = keys[rr];
    keys[rr] = buffer;
    return keys;
}
