/****************************************/
/****** Part-1: graph algorithms *********/
/****************************************/

// basic BFS
// find the distance from start_node to end_node in an unweighted graph, return -1 if not reachable

const int MM = 1e9;

int bfs(unordered_map <int, vector <int> > graph, int start_node, int end_node, int n)
{
    if (start_node == end_node) return 0;
    queue <int> q1;
    vector <int> dist(n + 1, MM);
    vector <bool> vis(n + 1, false);
    q1.push(start_node);
    dist[start_node] = 0;
    vis[start_node] = true;
    while (!q1.empty())
    {
        int cur_node = q1.front();
        q1.pop();
        for (auto x : graph[cur_node])
        {
            if (!vis[x])
            {
                vis[x] = true;
                dist[x] = dist[cur_node] + 1;
                if (end_node == x) return dist[x];
                q1.push(x);
            }
        }
    }
    return -1;
}

// BFS on 2D grid of char, 'O' is open space (you can go up, down, left, right), 'X' is wall (you can go into the cell)
// 'C' is start position, 'W' is destination, cell is numbered from 1 to 50

const int MM = 1e9;

int bfs(vector <vector <char> > graph, pair <int, int> start_node, pair <int, int> end_node, int n)
{
    if (start_node.first == end_node.first && start_node.second == end_node.second) return 0;
    queue <pair <int, int> > q1;
    vector <vector <int> > dist(n + 1, vector <int>(n + 1, MM));
    vector <vector <bool> > vis(n + 1, vector <bool>(n + 1, false));
    q1.push(start_node);
    dist[start_node.first][start_node.second] = 0;
    vis[start_node.first][start_node.second] = true;
    while (!q1.empty())
    {
        pair <int, int> cur_node = q1.front();
        q1.pop();
        vector <pair <int, int> > ops = {{cur_node.first - 1, cur_node.second}, {cur_node.first + 1, cur_node.second}, {cur_node.first, cur_node.second - 1}, {cur_node.first, cur_node.second + 1}};
        for (auto x : ops)
        {
            if (x.first < 1 || x.first > n || x.second < 1 || x.second < n || graph[x.first][x.second] == 'X' || vis[x.first][x.second]) continue;
            dist[x.first][x.second] = dist[cur_node.first][cur_node.second] + 1;
            if (x.first == end_node.first && x.second == end_node.second) return dist[x.first][x.second];
            vis[x.first][x.second] = true;
            q1.push(x);
        }
    }
    return -1;
}

// dfs on an unweighted graph
// initialize the two vectors as below:
vector <bool> vis(n + 1, false);
vector<int> dist(n + 1, 0);

void dfs(unordered_map <int, vector <int> > &graph, int cur_node, vector <bool> &vis, vector <int> &dist)
{
    vis[cur_node] = true;
    for (auto x : graph[cur_node])
    {
        if (!vis[x])
        {
            dist[x] = dist[cur_node] + 1;
            dfs(graph, x, vis, dist);
        }
    }
}

// DFS to detect loop in undirected graph
// returned params: loop_found: true or false; loop_nodes: the nodes in a loop
void dfs(unordered_map <int, unordered_set <int> > &graph, vector <int> &loop_nodes, int prev, int cur, unordered_map <int, int> &parents, vector <bool> &vis, bool &loop_found)
{
    if (loop_found) return;
    vis[cur] = true;
    for (auto x : graph[cur])
    {
        if (vis[cur] && x != prev)
        {
            int tmp = cur;
            loop_nodes = {x};
            while (tmp != x)
            {
                loop_nodes.emplace_back(tmp);
                tmp = parents[tmp];
            }
            loop_found = true;
            return;
        }
        if (!vis[cur])
        {
            parents[x] = cur;
            dfs(graph, loop_nodes, cur, x, parents, vis, loop_found);
        }
    }
}

// DFS to detect loop in a directed graph
void dfs(int start, unordered_map<int, unordered_set<int> > &graph, bool found_loop, 
vector<int> &visited, vector<int> &dist, int &loop_length)
{
    if (found_loop) return;
    visited[start] = 1;
    for (auto x : graph[start])
    {
        if (visited[x] == 1)
        {
            loop_length = dist[start] - dist[x] + 1;
            found_loop = true;
            return;
        }
        if (visited[x] == 0)
        {
            dist[x] = dist[start] + 1;
            dfs(x, graph, found_loop, visited, dist, loop_length);
        }
    }
    visited[start] = 2;
}

int num_nodes = 100;
vector <vector <int> > reachable(num_nodes+1, vector <int>(num_nodes+1, MM));

void floyd_warshall(unordered_map<int, vector<pair<int, int> > > graph, vector <vector <int> > &reachable, int n)
{
    for (auto x : graph)
    {
        for (auto y : x.second)
        {
            reachable[x.first][y.first] = y.second;
        }
    }
    for (int mid = 1; mid <= n; mid++)
    {
        for (int beg = 1; beg <= n; beg++)
        {
            for (int end = 1; end <= n; end++)
            {
                reachable[beg][end] = min(reachable[beg][mid] + reachable[mid][end], reachable[beg][end]);
            }
        }
    }
}

int num_nodes = 100;
int max_dist = 100000; // the max hops between any two nodes
vector <vector <int> > reachable(num_nodes+1, vector <int>(num_nodes+1, max_dist+1));

void floyd_warshall(unordered_map<int, unordered_map<int, int> > graph, vector <vector <int> > &reachable, int n)
{
    for (auto x: graph)
    {
        for (auto y: graph[x.first])
        {
            reachable[x.first][y.first] = y.second;
        }
    }  
    for (int mid = 1; mid <= n; mid++)
    {
        for (int beg = 1; beg <= n; beg++)
        {
            for (int end = 1; end <= n; end++)
            {
                reachable[beg][end] = min(reachable[beg][end], reachable[beg][mid] + reachable[mid][end]);
            }
        }
    }
}

// #### tree diamater and radius ###
void dfs(unordered_map <int, vector <pair <int, int> > > &graph, vector <bool> &vis,
vector <int> &dist, int cur_node, unordered_map <int, int> &parents, int &max_dist, int &max_node)
{
    vis[cur_node] = true;
    for (auto x : graph[cur_node])
    {
        if (!vis[x])
        {
            dist[x.first] = dist[cur_node] + x.second;
            if (dist[x.first] > max_dist)
            {
                max_dist = dist[x.first];
                max_node = x.first;
            }
            parents[x.first] = cur_node;
            dfs(graph, vis, dist, x.first, parents, max_dist, max_node);
        }
    }
}


int main()
{
    unordered_map <int, vector <pair <int, int> > > graph;
    
    //step-1: find one of the diameter endpoints

    dfs(graph, vis1, dist1, start_node, par1, max_dist1, max_node1);
    cout << "One diameter endpoint is: " << max_node1 << endl;
    
    // step-2: find the diameter
    parents[max_node1] = -1;
    dfs(graph, vis2, dist2, max_node1, parents, dia, max_node2);
    cout << "The tree diameter length is: " << dia << endl;
    cout << "The two diameter endpoints are: " << max_node1 << ", " << max_node2 << endl;
    
    // step-3: find radius and tree center
    int tmp = max_node2;
    while (tmp != -1)
    {
        if (max(dist2[tmp], dia - dist2[tmp]) < rad)
        {
            rad = max(dist2[tmp], dia - dist2[tmp]);
            center_node = tmp;
        }
        tmp = parents[tmp];
    }
    cout << "The tree radius length is: " << rad << endl;
    cout << "The tree center is: " << center_node << endl; 
}
// #### tree travel ###
/*
tree travel properties in a tree of N nodes and N-1 edges:
Tree property 1: start from node A, visit all nodes and return back to node A, the total travel distance is: 2*N-2 

Tree property 2:  start from node A, visit all nodes and finally stop at any node, what is the min total distance? 2*N-2-max_dist_from_node_A

Tree property 3:  you can start from any node, and visit all nodes, what is the min distance you need? 2*N-2-diameter

Tree property 4: how to find the max distance from any node to another node in O(N) complexity? dfs to find one diameter endpoint then another dfs to find the other diameter endpoint and you dfs the last diameter
endpoint and you can have the distance for every single node and you take the maximum

Tree property 5: you can start from any node and end at any node, find the min distance to travel to visit a set of nodes in a tree? prune the graph for all nodes that need to be travelled in order to reach one 
of the required nodes or be one itself then you have 2*N-2-dia_of_new_graph

*/

// ### Tree travel for a set of nodes
// DFS to prune nodes from a undirected tree to get a new graph
// desired_nodes contain the nodes that must be visited
// returned params: graph1 (new graph after cutting the unnecessary nodes)
void dfs(int start, unordered_map<int, unordered_set<int> > &graph, unordered_map<int, unordered_set<int> > &graph1, 
unordered_set<int> &desired_nodes, vector<bool> &visited, vector<bool> &keep)
{
    visited[start] = true;
    if (desired_nodes.count(start)) keep[start] = true;
    for (auto x : graph[start])
    {
        if (!visited[x])
        {
            dfs(x, graph, graph1, desired_nodes, visited, keep);
            keep[start] = keep[start] || keep[x];
            if (keep[start] && keep[x])
            {
                graph1[start].insert(x);
                graph1[x].insert(start);
            }
        }
    }
}

// topological sort on the undirected graph with n nodes
// can use priority_queue<int> to get unique output
bool top_sort(unordered_map <int, unordered_set <int> > &graph, int n, vector<int> &output1)
{
    priority_queue <int> q1;
    vector <int> indegree(n + 1);
    for (auto x : graph) for (auto y : x.second) indegree[y]++;
    for (int x = 1; x <= n; x++) if (!indegree[x]) q1.push(x);
    int counter = 0;
    while (!q1.empty())
    {
        int cur_node = q1.top();
        q1.pop();
        output1.emplace_back(cur_node);
        counter++;
        for (auto x : graph) if (--indegree[x] == 0) q1.push(x);
    }
    if (counter == n) return true;
    return false;
}




// Min-Spanning-Tree: PRIM
// to find the min-total-cost for MST in a directed graph with n nodes
// return the total cost for building the MST

// node_id from 1 to n
int prim(unordered_map <int, vector <pair <int, int> > > &graph, int n)
{
    vector <int> dist(n + 1, MM);
    vector <bool> vis(n + 1, false);
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > q1;
    dist[1] = 0;
    q1.push({0, 1});
    int s = 0;
    while (!q1.empty())
    {
        pair <int, int> cur_node = q1.top();
        q1.pop();
        if (vis[cur_node.second]) continue;
        vis[cur_node.second] = true;
        for (auto x : graph[cur_node.second])
        {
            for (auto y : x.second)
            {
                if (!vis[y.first] && y.second < dist[y.first])
                {
                    s += y.second;
                    dist[y.first] = y.second;
                    q1.push({y.second, y.first});
                }
            }
        }
    }
    return s;
}


//     Min-Spanning-Tree: Kruskal ********
// Union Find ****************
// Function to find root for a node
int find_set(int node, vector<int> &parents)
{
    if (node != parents[node]) parents[node] = find_set(parents[node], parents);
    return parents[node];
}
    
// Function to merge two nodes
bool unify(int node1, int node2, vector<int> &parents)
{
    int root1 = find_set(node1, parents), root2 = find_set(node2, parents);
    if (root1 == root2) return false;
    parents[root1] = root2;
    return true;
}

// Kruskal's algorithm to get MST for undirectional graph
// returned params: total cost to build the MST, and the new graph for MST (mst_graph)
int kruskal(unordered_map <int, vector<pair<int, int> > > &graph)
{
    vector <vector <int> > edges;
    for (auto x : graph) for (auto y : x.second) edges.push_back({y.second, x.first, y.first});
    sort(edges.begin(), edges.end());
    int tot_cost = 0;
    unordered_map <int, vector <pair <int, int> > > graph2;
    int ind = 1;
    for (auto cur_node : edges)
    {
        if (unify(cur_node[1], cur_node[2], parents)) 
        {
            tot_cost += cur_node[0];
            graph2[cur_node[1]].push_back({cur_node[2], cur_node[0]});
            graph2[cur_node[2]].push_back({cur_node[1], cur_node[0]});
            ind++;
        }
        if (ind == n) break;
    }
    return tot_cost;
}
// *** Binary search the answer ***********
bool check(vector <int> &vec1, int mid)
{
}
int main()
{
    vector <int> vec1;
    int ans = INT_MAX;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (check(mid))
        {
            high = mid - 1;
            ans = mid;
        }
        else low = mid + 1;
    }
    cout << ans << "\n";
}

// *** Dijkstra algorithm ***********
// initialize
vector <int> dist(n + 1, INT_MAX);
vector <bool> vis(n + 1, false);
void dijkstra(int start_node, unordered_map <int, vector<pair<int, int> > > &graph, vector <int> &dist, vector <bool> &vis)
{
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > q1;
    q1.push({0, start_node});
    dist[start_node] = 0;
    vis[start_node] = true;
    while (!q1.empty())
    {
        pair <int, int> cur_node = q1.top();
        q1.pop();
        if (vis[cur_node.second]) continue;
        vis[cur_node.second] = true;
        for (auto x : graph[cur_node.second])
        {
            if (x.second + cur_node.first < dist[x.first])
            {
                dist[x.first] = cur_node.first + x.second;
                q1.push({dist[x.first], x.first});
            }
        }
    }
}
// *** SPFA algorithm ***********
// The Shortest Path Faster Algorithm (SPFA) is an improvement of the Bellman–Ford algorithm 
// which can deal with negative edge-cost, a node may be put into the queue multiple times
const int MM = 1e9;
vector <int> dist(n + 1, MM);
vector <bool> inq(n + 1, false);
void spfa(int start_node, unordered_map <int, vector <pair <int, int> > > &graph, vector <int> &dist, vector <bool> &inq)
{
    queue <int> q1;
    q1.push(start_node);
    inq[start_node] = true;
    dist[start_node] = 0;
    while (!q1.empty())
    {
        int cur_node = q1.front();
        q1.pop();
        inq[cur_node] = false;
        for (auto x : graph[cur_node])
        {
            if (dist[cur_node] + x.second < dist[x.first])
            {
                dist[x.first] = dist[cur_node] + x.second;
                if (!inq[x.first])
                {
                    q1.push(x.first);
                    inq[x.first] = true;
                }
            }
        }
    }
}

/****************************************/
/****** Part-2: string and vectors *********/
/****************************************/



// find the index of substring="bh" from str1
string str1 = "xgbhfg"
int ind = str1.find("bh");
//find a substring from the end
// find the index of the last ‘sixth’
  std::string str="The sixth sick sheik's sixth sheep's sick.";
  std::string key="sixth";
    int ind2 = str.rfind(key);

// split a string into vector of words
    string s = "hello 123 234 world";
    vector <string> vec1;
    istringstream ss (s);
    string word;
    while (getline(ss, word, ' ')) vec1.emplace_back(word);

// digit string manipulations
// convert 23 to 5-digit palindrome
//“234” + “32” = “23432”
string p1 = ’234’
string p2 = p1;
reverse(p2.begin(), p2.end());
p1 += p2.substr(1);
// convert string to long long or int
string a = “1234”
long long b = stol(a);
int c = stoi(a);

// sort a string in ascending order and descending order
string sortedWord = "yifeng";
sort(sortedWord.begin(), sortedWord.end());
sort(sortedWord.rbegin(), sortedWord.rend());
// substring
string str1 = "yifeng";
// get substring from index 1 to 3 (not included)
string str2 = str1.substr(1, 2);

// get substring from index 3 to the end
string str3 = str1.substr(3);

// digit or alphabet for a char
char val1 = '3';
//check if val1 is an alphabet or a digit
if (isalpha(val1)) cout << "alpha";
if (isdigit(val1)) cout << "digit";


// convert string to lower or upper
std::string data = "Abc";
string data1, data2;
for (auto x : data)
{
    data1 += toupper(x);
    data2 += tolower(x);
}
// find number of vowels
string line = "aBeU i09yqED";
int cnt = 0;
for (auto x : line) if (tolower(x) == 'a' || tolower(x) == 'b' || tolower(x) == 'c' || tolower(x) == 'd' || tolower(x) == 'e') cnt++;

// compare two strings
string str1="abbc";
string str2 = "abba";
if (str1 > str2) cout << "str1 alphabetically bigger";
else if (str1 < str2) cout << "str2 alphabetically bigger";
else cout << "same string";


// find multiple appearances of a substring, find how many 'java'
string str1 = "I love java and java love me";
int cnt = 0, pos = str1.find("java");
while (pos != -1)
{
    cnt++;
    pos = str1.find("java", pos + 1);
}

// int/float to string
int a = 10;
string str1 = to_string(a);
float b = 10.1;
string str2 = to_string(b);

// string to int or double or float
string str2 = "123”;
int b = stoi(str2);
float c = stof(str2);
double d = stod(str2);


// find number of occurrences for each char
unordered_map <char, int> freq;
string str1="abcahjfsfcvfdsd";
for (auto x : str1) freq[x]++;
//$$$$$$$$$$ vectors $$$$$$$$$$$$$$$$$$
// vector ***

//question
//1. What is the time complexity to erase or insert on a vector?
//O(n)
//2. What is the time complexity for erasing the last element from a vector?
//O(1)
//3. If you need to do frequent operations (remove or add) to the ends of a sequence, what data structure should be used?
//deque

// find an element k from a vector v
//find(v.begin(), v.end(), k) - v.begin()

// sort a vector in ascending or descending order
vector<int> v1={1, 3, 4, 2};
sort(v1.begin(), v1.end());
sort(v1.rbegin(), v1.rend());

// Sort a vector of pairs {(2, “aaa”), (3, “mike”), (2, “zzz”)), ascending on the first element and then descending on the second element
vector<pair<int, string> > a = {{2, "aaa"}, {3, "bbb"}, {2, "zzz"}};
sort(a.begin(), a.end(), [](pair <int, string> p1, pair <int, string> p2){if (p1.first != p2.first) return p1.first < p2.first;
else return p1.second > p2.second;});

//sort a vector while preserving the order of equivalent elements
stable_sort(v1.begin(), v1.end()); //ascending order

//sort in ascending order based on the second element
vector<vector<int>> vec = {{1,4}, {9, 2}};
sort(vec.begin(), vec.end(), [](vector <int> a, vector <int> b){if (a[1] != b[1]) return a[1] < b[1]; else return a[0] < b[0];});


//vector of pairs
vector<pair<int, int> > v1 = {{1,-3}, {-2, 1}, {2, 4}};
int a1=1, b1=-3;
// find {a1, b1} from the vector
int ind = find(v1.begin(), v1.end(), make_pair(a1, b1)) - v1.begin();


//insert 100 to 2rd position
auto it=v1.begin();
v1.insert(it + 2, 100);

//pop (remove the last element)
v1.pop_back()

// remove the third element
v1.erase(it + 2);

//erase all elements with value equal to 1
vector<int> v2={1, 3, 4, 2, 1};
v2.erase(remove(v2.begin(), v2.end(), 1), v2.end());

//lower_boound and upper_bound
//lower_bound (3): point to the first iterator that is larger than or equal to 3
//upper_bound(3): point to the first iterator that is larger than 3
  std::vector<int> v={10,20,30,30,20,10,10,20};           // 10 20 30 30 20 10 10 20
// find the index of the first element >=20
sort(v.begin(), v.end());
int ind = lower_bound(v.begin(), v.end(), 20) - v.begin();
  
// find the index of the first element >20
int ind = upper_bound(v.begin(), v.end(), 20) - v.begin();

//use binary_search to find 27, return true or false
vector<int> arr = {10, 15, 20, 25, 30, 35};
bool flag;
if (arr[lower_bound(arr.begin(), arr.end(), 27) - arr.begin()] == 27) flag = true;
else flag = false;

//count the number of elements in vector that is less or equal to 30 using lower/upper bound
std::vector<int> v={10,20,30,30,20,10,10,20};  
sort(v.begin(), v.end());
int s = (upper_bound(v.begin(), v.end(), 30) - v.begin());


// count the number of occurrences for element 3 using lower/upper bound
vector<int> v = {3, 7, 3, 11, 3, 3, 2};
sort(v.begin(), v.end());
int ans = upper_bound(v.begin(), v.end(), 3) - lower_bound(v.begin(), v.end(), 3);

/****************************************/
/****** Part-3: PSA, Prime, and recursion ***/
/****************************************/



// calculate a = sqrt(2^2 + 4^2)
float a = sqrt(pow(2, 2) + pow(4, 2));

// a=4, b=6, find gcd and lcm of a and b
int g = __gcd(a, b);
int l = (a * b) / g;
//print all permutations using next_permutation
vector<int> a={1, 3, 2};
sort(a.begin(), a.end());
do
{
    for (auto x : a) cout << x << " ";
    cout << "\n";
} while (next_permutation(a.begin(), a.end()));

//#2. Permutation using recursion: generate 3-digit permutations using [‘a’, ‘b’]
// output: aaa, aab, aba, abb, baa, bab, bba, bbb
void rec(string str1, int size)
{
    if (size == 3)
    {
        cout << str1 << "\n";
        return;
    }
    rec(str1 + 'a', size + 1);
    rec(str1 + 'b', size + 1);
}


// find factors for all integers from 1 to 100 using Sieve algorithm
vector <vector <int> > factors(101);
for (int x = 1; x <= 100; x++)
{
    for (int y = x; y <= 100; y += x)
    {
        factors[y].emplace_back(x);
    }
}


// prefix sum array for partial sum or partial counting
// use psa to find partial sum from from the 2rd element to the 4th element
vector<int> v1 = {1, 3, 4, 2, 5}, psa = {0};
for (int x = 0; x < 5; x++) psa.emplace_back(psa[x] + v1[x]);
cout << psa[4] - psa[2 - 1] << "\n";
// difference array for partial constant update
// For example, original state = [1, 4, 2, 3], 
// Update 1: from element 1 to 2, add 1, 
// update 2: from element 3 to 4: add -1
vector <int> vec1 = {1, 4, 3, 2}, da(5), vec2;
da[2] -= 1;
da[1 - 1] += 1;
da[4] -= -1;
da[3 - 1] += -1;
for (int x = 0; x < 4; x++)
{
    if (x == 0) vec2.emplace_back(da[x]);
    else vec2.emplace_back(vec2[x - 1] + da[x]);
}
for (int x = 0; x < vec1.size(); x++) cout << vec2[x] + vec1[x] << " ";
cout << "\n";
// difference array to find how many updates applied (reverse application)
// For example, original state = [1, 4, 2, 3], desired state = [2, 5, 4, 4]
// How many partial update (each partial update increase 1) need to convert original state to desired state?
vector <int> vec1 = {1, 4, 2, 3}, vec2 = {2, 5, 4, 4}, da1 = {vec1[0]}, da2 = {vec2[0]};
int s1 = 0, s2 = 0;
for (int x = 1; x < 4; x++)
{
    da1.emplace_back(vec1[x] - vec1[x - 1]);
    da2.emplace_back(vec2[x] - vec2[x - 1]);
}
for (int x = 0; x < 4; x++)
{
    if (da2[x] - da1[x] > 0) s1 += da2[x] - da1[x];
    else s2 += da1[x] - da2[x];
}
cout << max(s1, s2) << "\n";
// prime related algorithms
// 1) how to test if a=18 is prime
int a = 18;
bool flag = true;
for (int x = 2; x * x <= a; x++)
{
    if (a % x == 0)
    {
        flag = false;
        break;
    }
}
if (flag) cout << "prime\n";
else cout << "not prime\n";

// how to find all prime numbers up to 100?
vector <vector <int> > factors(101);
for (int x = 1; x <= 100; x++)
{
    for (int y = x; y <= 100; y += x)
    {
        factors[y].emplace_back(x);
    }
}
vector <int> prime;
for (int x = 1; x <= 100; x++) if (factors[x].size() == 2) prime.emplace_back(x);
for (auto x : prime) cout << x << " ";
cout << "\n";

// how to do prime factorization for n=60
int n = 60, tmp = n;
vector <int> factors;
for (int x = 2; x * x <= n; x++)
{
    while (tmp % x == 0)
    {
        factors.emplace_back(x);
        tmp /= x;
    }
}
sort(factors.begin(), factors.end());
for (auto x : factors) cout << x << " ";
cout << "\n";

//# function to count number of ways for letter arrangements, for example, AAB, there are 3!/2! 
string str1 = "AAB";
int ans = 1;
for (int x = 2; x <= str1.size(); x++) ans *= x;
unordered_map <char, int> m1;
for (auto x : str1) m1[x]++;
for (auto x : m1)
{
    int tmp = 1;
    for (int a = 2; a <= x.second; a++) tmp *= a;
    ans /= tmp;
}
cout << ans << "\n";
//// calculate: a**b % c, for example, 2**121 % 100000007
long long power (long x, long n, long mod)
{
    if (n == 0) return 1;
    long long t = power(x, n / 2, mod);
    t = t * t % mod;
    if (n % 2 != 0) t = t * x % mod;
    return t;
}
//// find all 3-element combinations from n-element vector {1, 2, 3, 4}
void rec(vector <int> vec1, int ind, vector <int> &output, int size, int n)
{
    if (ind == vec1.size() + 1) return;
    if (size == n)
    {
        for (auto x : output) cout << x << " ";
        cout << "\n";
        return;
    }
    output.emplace_back(vec1[ind]);
    rec(vec1, ind + 1, output, size + 1, n);
    output.pop_back();
    rec(vec1, ind + 1, output, size, n);
}





