#pragma once
#include "structures/Iterable.h"

namespace SDIZO {
    class BinaryTreeDrawer {
    public:
        BinaryTreeDrawer();
        ~BinaryTreeDrawer();
        void draw(SDIZO::Iterable* tree);
    };
}