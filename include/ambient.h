#include <vector>
#include <utility>

using namespace std;

class Ambient
{
public:
  /**
   * @brief Construct a new Ambient object
   * @param stars Number of stars
   * @param radius Number of plane's radius
   */
  Ambient(int stars, int radius);

  /**
   * @brief Draw function
   */
  void draw();

private:
  /**
   * @brief Draws field with specified radius
   * @param radius 
   */
  void draw_field(int radius);

  /**
   * @brief Draw a number of stars
   * @param stars Number of stars
   */
  void draw_sky(int stars);

  /**
   * @brief Vector which holds the stars coordinates
   */
  vector<pair<int, pair<int, int>>> star_;

  /**
   * @brief Number of stars
   */
  int stars_;

  /**
   * @brief Radius of plane
   */
  int radius_;
};