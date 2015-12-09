     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

// Includes
#include "Graph.h"

// Overloaders
int operator==(const vertex &lhs, const vertex &rhs)
{
	return lhs.get_id() == rhs.get_id();
}
bool operator<(const vertex &lhs, const vertex &rhs)
{
	return lhs.get_id() < rhs.get_id();
}
bool operator>(const vertex &lhs, const vertex &rhs)
{
	return lhs.get_id() > rhs.get_id();
}

// Constructors
graph::graph()
{
	//_vertices = empty!
}
graph::graph(unordered_map<int, vertex> new_vertices)
{
	_vertices = new_vertices;
}

// Copy Consturctor

// Destructor

// Getters
unordered_map<int, vertex> graph::get_vertices() const
{
	return _vertices;
}

// Setters
void graph::set_vertices(unordered_map<int, vertex> new_vertices)
{
	_vertices = new_vertices;
}

// Methods
unordered_map<vertex, path> graph::computeShortestPath(vertex *start)
{
	//holds known distances
	unordered_map<vertex, path> paths;

	//underlying heap
	priority_queue<vertex, vector<vertex>, PathWeightComparer> dijkstra_queue{};

	//reset start's path weight
	start->set_path_weight(0);
	//start->reset_path();


	//make sure that the starting vertex is in the graph
	if (_vertices.find(start->get_id()) != _vertices.end())
	{
	

		//push on starting vertex
		dijkstra_queue.push(*start);


		//while queue not empty
		while (dijkstra_queue.empty() != true)
		{		
			//push on outgoing edges that haven't been discovered
			vertex top = dijkstra_queue.top();
			dijkstra_queue.pop();

			//Top of heap not known (in distances)?
			if (paths.count(top) == 0)
			{
				//make known
				int current_path_weight = top.getPathWeight();
				stack<unordered_map<int, int>> temp_path = top.get_path_of_ids();
				temp_path.top()[top.get_id()] = current_path_weight;
				temp_path.push(top.get_path_of_ids().top());
				top.set_path_of_ids(temp_path);
				paths[top] = temp_path;
				
				//push on outgoing edges
				for (auto i : top.get_edges())
				{
					vertex *next = i.first;
					path new_path = top.getPathWeight();
					int weight = i.second;
					int adjusted_weight = next->get_load_factor() * weight;
					new_path.set_distance_traveled(adjusted_weight + current_path_weight);
					next->set_path(new_path);
				}
			}			
		}		
	}

	return paths;
}
//cout << endl << endl << "*****END DIJKSTRAS*****" << endl << endl;

	// Print all of stack...
//	for (int i = 0; i < temp_stack.size(); i++)
//	{
//		cout << endl << "TS: " << temp_stack.top().get_id();
//		temp_stack.pop();
//	}

	/*cout << "*****DISTANCES*****" << endl << endl;
	cout << "Path";
	for (auto i : distances)
	{
		cout << " -> V" << i.first.get_id() << ", W" << i.second;
	}
	cout << endl << "Distance to dest: ";
	for (auto i : distances)
	{
		if (i.first.get_id() == 1)
		{
			cout << " -> V" << i.first.get_id() << ", W" << i.second;
		}
	}
	cout << endl << endl << "*****END DISTS*****" << endl;*/



	return dijkstra_queue.top();
}