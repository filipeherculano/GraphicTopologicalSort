/**
 * @brief Class that defines the Building (node)
 */
class Building
{
public:
  /**
     * @brief Construct a new Building object
     * @param x Coordinate
     * @param y Coordinate
     * @param z Coordinate
     * @param side Side size
     * @param height Height size
     */
  Building(int x, int y, int z, int side, int height);

  /**
     * @brief Draws the current building
     */
  void draw();

  /**
     * @brief Destroys the current building
     */
  void destroy();

  /**
     * @brief Get x coordinate
     * @return int 
     */
  int x();

  /**
     * @brief Get y coordinate
     * @return int 
     */
  int y();

  /**
     * @brief Get z coordinate
     * @return int 
     */
  int z();

  /**
   * @brief Set the y object
   * @param y 
   */
  void set_y(int y);

  /**
   * @brief Starts the current building
   */
  void start();

  /**
   * @brief Checks if the current building is already built
   * @return true if is built, false otherwise
   */
  bool built();

private:
  /**
   * @brief State of the building
   */
  enum State
  {
    BUILDING = 0,
    ALIVE = 1,
    DESTROYING = 2,
    DEAD = 3
  };

  /**
   * @brief Building current state
   */
  State state_;

  /**
   * @brief Updates current building state
   */
  void update_state();

  /**
     * @brief X coordinate
     */
  int x_;

  /**
     * @brief Y coordinate
     */
  int y_;

  /**
     * @brief Z coordinate
     */
  int z_;

  /**
     * @brief Side size of the polygon
     */
  int side_;

  /**
     * @brief Height size of the polygon
     */
  int height_;

  /**
     * @brief Boolean variable determining if current building is destroyed already
     */
  bool is_destroyed_;
};
