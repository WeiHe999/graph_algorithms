#include <bits/stdc++.h>
using namespace std;

const int MM = 10;
unordered_map<int, vector<int> > graph, components;
vector<int> dfn(MM), low(MM), in_stack(MM);
stack<int> st;
int ind;

void tarjan(int cur_node)
{
    ind++;
    dfn[cur_node] = ind;
    low[cur_node] = ind;

    // push in stack
    st.push(cur_node);
    in_stack[cur_node] = 1;
    for (auto x: graph[cur_node])
    {
        // if the child has not been visited
        if (dfn[x]==0)
        {
            tarjan(x);
            low[cur_node] = min(low[cur_node], low[x]);
        }
        else
        {
            // if the child has been visited, but it is in stack
            if (in_stack[x])
            {
                low[cur_node] = min(low[cur_node], low[x]);
            }
        }
    }
    
    // if the current node is a root
    if (dfn[cur_node]==low[cur_node])
    {
        int w = 0;
        vector<int> v1; // vector to store the nodes in a component
        // pop stack until cur_node
        while(st.top()!=cur_node)
        {
            w = st.top();
            v1.push_back(w);
            in_stack[w] = 0;
            st.pop();
        }
        
        // continue to pop the current node (root)
        w = st.top();
        v1.push_back(w);
        in_stack[w] = 0;
        st.pop();
        components[w] = v1;        
        
    }

}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
    }
    
    
    int start_node = 1;
    ind = 0; // global index is set to 0
    tarjan(start_node);
    
    // print the result
    for (auto x: components)
    {
        cout << "root = " << x.first << endl;
        for (auto y: x.second)
        {
            cout << y << " ";
        }
        cout << endl;
    }
    
    
}
