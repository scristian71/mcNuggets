#include <iostream>
#include <boost/math/common_factor.hpp>
#define SEEDS_COUNT 3
static uint32_t seeds[SEEDS_COUNT] = {6,9,20};

bool McNuggets(uint32_t totalItemsSumInit)
{
    uint32_t lcm = 1;
    for (uint32_t i = 0; i < SEEDS_COUNT; i++)
        lcm = boost::math::lcm(lcm, seeds[i]);

    uint32_t totalItemsSum = totalItemsSumInit % lcm;
    uint32_t toBeAdded = totalItemsSumInit / lcm;
    uint32_t toBeAddedLast = (toBeAdded * lcm) / seeds[SEEDS_COUNT - 1];

    uint32_t fixItemMaxCount[SEEDS_COUNT] = {0};
    uint32_t fixItemCount[SEEDS_COUNT] = {0};

    for (uint32_t i = 0; i < SEEDS_COUNT; i++)
    {
        fixItemMaxCount[i] = lcm / seeds[i];
    }

    while(true)
    {
        uint32_t itemsSum = 0;
        for (uint32_t i = 0; i < SEEDS_COUNT; i++)
            itemsSum += fixItemCount[i] * seeds[i];
        if (itemsSum == totalItemsSum)
        {
            //found solution
            std::cout << "Solution for:" << totalItemsSumInit << ":";
            for (int i = 0; i < SEEDS_COUNT - 1; i++)
                std::cout << seeds[i] << "*" << fixItemCount[i] << "+";
            std::cout << (seeds[SEEDS_COUNT - 1]) << "*" << (fixItemCount[SEEDS_COUNT - 1]  + toBeAddedLast) << std::endl;
            return true;
        }
        uint32_t index = 0;
        while (fixItemCount[index] + 1 > fixItemMaxCount[index] && index < SEEDS_COUNT)
        {
            fixItemCount[index] = 0;
            index++;
        }
        if (index < SEEDS_COUNT)
        {
            fixItemCount[index]++;
            continue;
        }
        else
            break;
    }
    std::cout << "No solution for:" << totalItemsSumInit << "!" << std::endl;
    return false;
}

int main(int argc, char *argv[])
{
//    cout << "Hello World!" << endl;
    for (uint32_t i = 1; i < 1200; i++)
        McNuggets(i);
    return 0;
}
