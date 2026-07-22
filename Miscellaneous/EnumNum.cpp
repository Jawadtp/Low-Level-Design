#include <iostream>

using namespace std;

enum class VehicleSize
{
    Compact = 1,
    Medium = 2,
    Large = 3
};

int main()
{
    bool test = VehicleSize::Compact < VehicleSize::Medium;
    cout << test;
    return 0;
}