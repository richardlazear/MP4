/******************************************************************************************************************************************
Design a program in C++ that will allow you to build, traverse, insert, and delete from a Binary Search Tree.

You should create a BST from a random set of strings in a file keeping track of the level as well as multiple occurences if there are any.

You should then have a menu that will allow you to traverse (submenu of InOrder, PreOrder, PostOrder, and LevelOrder), insert a string
in to the correct spot, and delete a string (having searched for it).  When you traverse inOrder, print out the level and number of
occurrences of each word.
******************************************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

struct node
{
	string myString;
	int occurrences = 1;
	int nodeLevel;
	node * left;
	node * right;
};

void readIn(node * &);
void addNode(node * &, string);
// Traverse functions
void traverseInOrder(node *);
void traversePreOrder(node *);
void traversePostOrder(node *);
void traverseLevelOrder(node *);
// End traverse functions
// node * searchNode(node * &, string);
void deleteNode(node * &, string);

int main()
{
	// Create the root of the binary search tree
	node * root = new node;
	root->left = NULL;
	root->right = NULL;
	// Build the binary search tree by reading in words from the file
	string line;
	ifstream myFile("myFile.txt");
	if (myFile.is_open())
		while (getline(myFile, line))
		{
			addNode(root, line);
		}
	myFile.close();
	cout << endl << endl;

	traverseInOrder(root);
	cout << endl;

	// Menu
	int userSelection;
	string insertInput, deleteInput;
	do
	{
		cout << "MAIN MENU" << endl;
		cout << "1. Traverse" << endl;
		cout << "2. Insert" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Exit" << endl;
		cout << "Please enter your selection: ";
		cin >> userSelection;

		switch (userSelection)
		{
		case 1: // TRAVERSE
			int traverseSelection;
			do
			{
				cout << endl;
				cout << "TRAVERSE MENU" << endl;
				cout << "1. InOrder" << endl;
				cout << "2. PreOrder" << endl;
				cout << "3. PostOrder" << endl;
				cout << "4. LevelOrder" << endl;
				cout << "5. Go Back" << endl;
				cin >> traverseSelection;

				switch (traverseSelection)
				{
				case 1:
					traverseInOrder(root);
					break;

				case 2:
					traversePreOrder(root);
					break;

				case 3:
					traversePostOrder(root);
					break;

				case 4:
					traverseLevelOrder(root);
					break;

				case 5: // go back up one level in menu
					break;

				default:
					cout << "Please enter a valid number." << endl;
					break;
				}
			} while (traverseSelection != 5);
			break;

		case 2: // INSERT
			cout << "Please enter the string you would like to insert into the binary tree: ";
			cin >> insertInput;
			addNode(root, insertInput);
			break;

		case 3: // DELETE
			cout << "Please enter the string you would like to delete from the binary tree: ";
			cin >> deleteInput;
			deleteNode(root, deleteInput);
			break;

		case 4: // EXIT
			break;

		default:
			cout << "Please enter a valid number." << endl;
			break;
		}
	} while (userSelection != 4);

	system("PAUSE");
}

void addNode(node * &inTree, string inString)
{
	int currentTreeLevel = 1;
	node * current = inTree;
	bool added = false;
	while (!added)
	{
		if (inString < current->myString)
		{
			if (current->left == NULL)
			{
				current->left = new node;
				current = current->left;
				current->left = NULL;
				current->right = NULL;
				current->myString = inString;
				current->nodeLevel = currentTreeLevel;
				cout << current->myString;
				added = true;
			}
			else
			{
				current = current->left;
				currentTreeLevel++;
			}
		}
		else if (inString > current->myString)
		{
			if (current->right == NULL)
			{
				current->right = new node;
				current = current->right;
				current->left = NULL;
				current->right = NULL;
				current->myString = inString;
				current->nodeLevel = currentTreeLevel;
				cout << current->myString;
				added = true;
			}
			else
			{
				current = current->right;
				currentTreeLevel++;
			}
		}
		else
		{
			// the string has already been found in a node, so increment the occurrences
			current->occurrences++;
			cout << current->occurrences << endl;
			added = true;
		}
	}
	return;
}

void traverseInOrder(node * inTree)
{
	node * current = inTree;
	if (current)
	{
		if (current->left != NULL)
		{
			traverseInOrder(current->left);
		}
		cout << left << setw(15) << current->myString << "occurs " << current->occurrences << " time(s); node level: " << current->nodeLevel << endl;
		if (current->right != NULL)
		{
			traverseInOrder(current->right);
		}
	}
}

void traversePreOrder(node * inTree) // Data Left Right
{
	node * current = inTree;
	if (current)
	{
		cout << current->myString << endl;
		if (current->left != NULL)
		{
			traversePreOrder(current->left);
		}
		if (current->right != NULL)
		{
			traversePreOrder(current->right);
		}
	}
}

void traversePostOrder(node * inTree) // Left Right Data
{
	node * current = inTree;
	if (current)
	{
		if (current->left != NULL)
		{
			traversePostOrder(current->left);
		}
		if (current->right != NULL)
		{
			traversePostOrder(current->right);
		}
		cout << current->myString << endl;
	}
}

void traverseLevelOrder(node * inTree)
{
	// Code adapted from https://www.youtube.com/watch?v=86g8jAQug04
	
	if (inTree == NULL) return;
	queue<node *> Q;
	Q.push(inTree);
	while (!Q.empty())
	{
		node * current = Q.front();
		cout << current->myString << endl;
		if (current->left != NULL) Q.push(current->left);
		if (current->right != NULL) Q.push(current->right);
		Q.pop(); // remove the element at the front of the queue
	}
}

void deleteNode(node * &inTree, string toDelete)
{
	// This funtion's code is adapted from the 'Big Java' textbook
	
	int currentTreeLevel = 1;
	// Find the node to delete
	node * nodeToDelete = inTree;
	node * parent = NULL;
	bool found = false;
	while (!found && nodeToDelete != NULL)
	{
		if (nodeToDelete->myString == toDelete)
		{
			found = true;
		}
		else
		{
			parent = nodeToDelete;
			if (nodeToDelete->myString > toDelete)
			{
				nodeToDelete = nodeToDelete->left;
			}
			else
			{
				nodeToDelete = nodeToDelete->right;
			}
			currentTreeLevel++;
		}
	}

	if (!found)
	{
		cout << "Sorry, that string was not found in the binary search tree";
		return;
	}
	// End searching for the node to delete

	// Delete procedure if the node to delete has only one child
	if (nodeToDelete->left == NULL || nodeToDelete->right == NULL)
	{
		node * newChild = NULL;
		if (nodeToDelete->left == NULL)
		{
			newChild = nodeToDelete->right;
		}
		else
		{
			newChild = nodeToDelete->left;
		}

		if (parent == NULL) // The root is to be deleted
		{
			inTree = newChild;
		}
		else if (parent->left != NULL && parent->left->myString == nodeToDelete->myString)
		{
			parent->left = newChild;
		}
		else
		{
			parent->right = newChild;
		}
		return;
	}

	// Delete procedure if the node to delete has two children
	
	// Find the smallest element in the right subtree of the node to delete
	node * smallestParent = nodeToDelete;
	node * smallest = nodeToDelete->right;
	while (smallest->left != NULL)
	{
		smallestParent = smallest;
		smallest = smallest->left;
	}
	// At this point, 'smallest' contains the smallest child in the right subtree of the node to delete

	nodeToDelete->myString = smallest->myString;
	nodeToDelete->occurrences = smallest->occurrences;
	if (smallestParent->myString == nodeToDelete->myString)
	{
		smallestParent->right = smallest->right;
	}
	else
	{
		smallestParent->left = smallest->right;
	}

	// Commented out below are my original delete and search functions
	/*
	// Search for the string in a node in the BST, and return the parent of that specific node to the function
	node * parent = searchNode(inTree, toDelete);
	if (parent->myString == inTree->myString) // The user wants to remove the root node
	{
		deleteRoot(parent);
	}
	else
	{
		// Determine which child of the parent is to be deleted
		node * nodeToDelete = NULL;
		bool toDeleteLeftChild; // Keeps track of which of the parent's nodes is to be deleted
		if (parent->left != NULL && parent->left->myString == toDelete)
		{
			nodeToDelete = parent->left;
			toDeleteLeftChild = true;
		}
		else if (parent->right != NULL && parent->right->myString == toDelete)
		{
			nodeToDelete = parent->right;
			toDeleteLeftChild = false;
		}

		// If the node to delete does not have any children, set its parent's reference to NULL and delete the node 
		if (nodeToDelete->left == NULL && nodeToDelete->right == NULL)
		{
			if (toDeleteLeftChild)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
			delete nodeToDelete;
		}
		// If the node to delete has only one child, bypass the node to delete and connect the parent with the child's child
		else if (nodeToDelete->left == NULL || nodeToDelete->right == NULL)
		{
			if (nodeToDelete->left == NULL)
			{
				if (toDeleteLeftChild)
				{
					parent->left = nodeToDelete->right;
				}
				else
				{
					parent->right = nodeToDelete->right;
				}
				delete nodeToDelete;
			}
			else if (nodeToDelete->right == NULL)
			{
				if (toDeleteLeftChild)
				{
					parent->left = nodeToDelete->left;
				}
				else
				{
					parent->right = nodeToDelete->left;
				}
				delete nodeToDelete;
			}
		}
		// If the node has two children...
		else
		{
			// Find the smallest element of the right subtree
			node * smallestParent = nodeToDelete;
			node * smallest = nodeToDelete->right;
			while (smallest->left != NULL)
			{
				smallestParent = smallest;
				smallest = smallest->left;
			}
			
			// 'smallest' contains the smallest child in the right subtree of the 'nodeToDelete'
			nodeToDelete->myString = smallest->myString;
			nodeToDelete->occurrences = smallest->occurrences;
			if (smallestParent->myString == nodeToDelete->myString)
			{
				smallestParent->right = smallest->right;
			}
			else
			{
				smallestParent->left = smallest->right;
			}

			// old delete two children
			if (toDeleteLeftChild)
			{
				// Check if the node to delete has any leafs...if so, replace the node to delete with the leaf
				if (nodeToDelete->left->left == NULL && nodeToDelete->left->right == NULL)
				{
					parent->left = nodeToDelete->left;
					parent->left->right = nodeToDelete->right;
					delete nodeToDelete;
				}
			}
			else
			{
				// Check if the node to delete has any leafs...if so, replace the node to delete with the leaf
				if (nodeToDelete->left->left == NULL && nodeToDelete->left->right == NULL)
				{
					parent->right = nodeToDelete->left;
					parent->right->right = nodeToDelete->right;
					delete nodeToDelete;
				}
			}
			// end old delete two children
		}
	}
	*/
}

/*
node * searchNode(node * &inTree, string toFind)
{
node * current = inTree;
if (toFind == current->myString) // The root node is where the string to find is located
{
return current;
}
else
{
if (toFind < current->myString)
{
if (toFind == current->left->myString)
{
return current;
}
else
{
return searchNode(current->left, toFind);
}
}
else if (toFind > current->myString)
{
if (toFind == current->right->myString)
{
return current;
}
else
{
return searchNode(current->right, toFind);
}
}
}
}
*/