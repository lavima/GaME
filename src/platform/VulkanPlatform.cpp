#include "../GaME.h"

bool QueueFamilyIndices::IsComplete() {
    return graphics_index.has_value() && present_index.has_value();
}


