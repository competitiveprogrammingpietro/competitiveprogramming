/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(N)
 * Source: https://practice.geeksforgeeks.org/problems/maximum-path-sum/
 * To solve the problem I had to realize that two cases need to ba handled:
 * 1) The node can return a path
 * 2) The node can't return a path but can serve as an edge
*/
#include <stack>
#include <iostream>
#include <climits>

//Node is as follows
struct Node{
	int data;
	Node *left, *right;
};

using namespace std;
int max_path(struct Node *root, int * edge)
{
  int pl, pr, el, er;

  pl = pr = el = er = INT_MIN;
  
  if (!root->left && !root->right) {
    *edge = root->data;
    
#ifdef DEBUG
    cout << root->data << " returns:" << INT_MIN << "," << *edge << endl;
#endif
    
    return INT_MIN;
  }

  if (root->left) {
    pl = max_path(root->left, &el);
  }

  if (root->right) {
    pr = max_path(root->right, &er);
  }
  *edge = ((er > el) ? er : el) + root->data;

  // Either this node does not have two children
  // or both of them are leaves
  if (!root->right || !root->left) {
    
#ifdef DEBUG
    cout << root->data << " returns:" << INT_MIN << "," << *edge << endl;
#endif
    
    return INT_MIN;
  } 

  // Clumsy .. 
  int max_path_children = (pr > pl) ? pr : pl;
  int path_root = er + el + root->data;
  int max = (max_path_children > path_root) ? max_path_children : path_root;
  
#ifdef DEBUG
  cout << root->data << " plel" << pl << "," << el << "prer" << pr << "," << er << endl;
#endif
  
  return max;
}

int maxPathSum(struct Node *root)
{
  int edge;
  return max_path(root, &edge);
}
