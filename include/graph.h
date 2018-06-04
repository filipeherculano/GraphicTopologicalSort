#include <vector>
#include <tuple>

#include "ambient.h"
#include "edges.h"

using namespace std;

/**
 * @brief Class that defines the graph
 */
class Graph
{
  public:
	/**
	 * @brief Construct a new Graph object
	 * @param n Number of nodes
	 * @param m Number of edges
	 */
	Graph(int n, int m);

	/**
	 * @brief Topological sorting algorithm
	 */
	void topological_sort();

	/**
	 * @brief Calls each edge drawing function
	 */
	void draw_edges();

	/**
	 * @brief Draws plane
	 */
	void draw_plane(GLuint _textureId);

	/**
	 * @brief Calls each vertex drawing function
	 */
	void draw_vertex(GLuint _buildTextId);

	/**
	 * @brief Destroy node at the head of the topological sort
	 */
	void destroy_node();

	/**
	 * @brief Creates a current node on the field
	 */
	void next_node();

  private:
	/**
	 * @brief Class containing ambient drawing functions
	 */
	Ambient ambient_;

	/**
	 * @brief Number of nodes in the graph
	 */
	int number_nodes_;

	/**
	 * @brief Number of edges in the graph
	 */
	int number_edges_;

	/**
	 * @brief Boolean vector to determine if node is already visited while on DFS
	 */
	vector<bool> visited_;

	/**
	 * @brief Vector containing all building nodes in the graph
	 */
	vector<Building> buildings_;

	/**
	 * @brief Vector containing all edges conecting nodes in the graph
	 */
	vector<Edges> edges_;

	/**
	 * @brief Topological sequence of nodes to destroy
	 */
	vector<int> topological_sort_;

	/**
	 * @brief Adjacency list of graph topology
	 */
	vector<int> adj_[12];

	/**
	 * @brief DFS (Depth First Search) used to create topological sort
	 * @param u Current node
	 */
	void DFS(int u);

	/**
	 * @brief Connects two Buildings 
	 * @param source Source building
	 * @param destination Destination building
	 */
	void connect(Building source, Building destination, int u, int v);

	/**
	 * @brief Current node to be created
	 */
	int current_ = 0;

	/**
	 * @brief Vector with the indices of each node linked
	 */
	vector<pair<int, int>> end_points_;
};
