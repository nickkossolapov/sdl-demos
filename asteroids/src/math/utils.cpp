#include <numbers>
#include "./utils.h"

constexpr float radiansToDegrees(float radians) {
    return radians * (180.0f / std::numbers::pi_v<float>);
}
