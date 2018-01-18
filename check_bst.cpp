/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(N)
 * Source: https://practice.geeksforgeeks.org/problems/check-for-bst/
 */
#include <iostream>
#include <list>
using namespace std;



/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* A binary tree node has data, pointer to left child
   and a pointer to right child  
struct Node {
    int data;
    Node* left, * right;
};
*/

/* Should return true if tree represented by root is BST. 
   For example, return  value should be 1 for following tree.
         20
     /      \ 
   10       30
  and return value should be 0 for following tree.
         10
     /      \ 
   20       30 */
void in_order_visit(Node * root, list<int>& order);
bool isBST(Node* root) {
  list<int> order;

  in_order_visit(root, order);

  auto it_first = order.begin();
  auto it_second = order.begin();
  it_second++; // Is there a better way to do it ?
  while (it_second != order.end()) {
    cout << *it_first << ", ";
    if (*it_first > *it_second)
      return false;

    it_first++;
    it_second++;
  }
  return true;
}

void in_order_visit(Node * root, list<int>& order) {
  if (root == NULL)
    return;

  in_order_visit(root->left, order);
  order.push_back(root->data);
  in_order_visit(root->right, order);
  return;
}

