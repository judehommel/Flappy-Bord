#include <random>
#include <chrono>

using namespace std;
template <typename IntegerT>
IntegerT random(IntegerT min, IntegerT max)
{
  static std::ranlux48 rng( std::chrono::system_clock().now().time_since_epoch().count() );
  return std::uniform_int_distribution <int> ( min, max )( rng );
}
