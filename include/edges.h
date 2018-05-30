#include "building.h"

using namespace std;

/**
 * @brief Class that defines the edge
 */
class Edges
{
public:
  /**
     * @brief Construct a new Edges object
     * @param source Source building
     * @param destination Destination building
     */
  Edges(Building source, Building destination);

  void draw();

  /**
     * @brief Verify if passed building is the same as the source
     * @param s Candidate building
     * @return true if is the same, false otherwise
     */
  bool is_source(Building s);

  /**
     * @brief Destroy current edge
     */
  void destroy();

private:
  /**
     * @brief Boolena variable determining if current edge is destroyed
     */
  bool is_destroyed_;

  /**
     * @brief Source building
     */
  Building source_;

  /**
     * @brief Destination building
     */
  Building destination_;
};