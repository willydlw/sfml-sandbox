#pragma once 

#include <random>
#include <type_traits>
#include <limits>

template <typename T>
class RandomGenerator
{
    private:

    static inline std::mt19937 engine{std::random_device{}()};

    using DistributionType = typename std::conditional<
        std::is_integral<T>::value,
        std::uniform_int_distribution<T>,
        std::uniform_real_distribution<T>
    >::type;

    DistributionType dist;

    public:

    // Constructor to set min and max bounds for the distribution
    RandomGenerator(T min_val = std::numeric_limits<T>::min(),
                    T max_val = std::numeric_limits<T>::max())
                : dist(min_val, max_val) {}

    // Method to generate a random number
    T generate(){
        return dist(engine);
    }
};
