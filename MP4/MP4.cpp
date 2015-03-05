/******************************************************************************************************************************************
Design a program in C++ that will allow you to build, traverse, insert, and delete from a Binary Search Tree.

You should create a BST from a random set of strings in a file keeping track of the level as well as multiple occurences if there are any.

You should then have a menu that will allow you to traverse (submenu of InOrder, PreOrder, PostOrder, and LevelOrder), insert a string
in to the correct spot, and delete a string (having searched for it).  When you traverse inOrder, print out the level and number of
occurrences of each word.
******************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node
{
	string myString;
	int occurrences = 0;
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
void deleteNode(node * &, string);

int main()
{
	// Create the root of the binary search tree
	node * root = new node;
	root->left = NULL;
	root->right = NULL;
	root->nodeLevel = 1;
	// Build the binary search tree by reading in words from the file
	string line;
	ifstream myFile("myFile.txt");
	if (myFile.is_open())
		while (getline(myFile, line))
		{
			addNode(root, line);
		}
	myFile.close();
	cout << endl;

	// Menu
	int userSelection;
	string insertInput, deleteInput;
	do
	{
		cout << "1. Traverse" << endl;
		cout << "2. Insert" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Exit" << endl;
		cout << "Please enter your selection: ";
		cin >> userSelection;

		switch (userSelection)
		{
		case 1:
			int traverseSelection;
			do
			{
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

				case 5:
					// go back up one level in menu
					break;

				default:
					cout << "Please enter a valid number." << endl;
					break;
				}
			} while (traverseSelection != 5);
		case 2:
			// insert
			cout << "Please enter the string you would like to insert into the binary tree: ";
			
			cin >> insertInput;
			addNode(root, insertInput);
			break;

		case 3:
			// delete
			cout << "Please enter the string you would like to delete from the binary tree: ";
			cin >> deleteInput;
			deleteNode(root, deleteInput);
			break;

		case 4: // Exit the program
			break;

		default:
			cout << "Please enter a valid number." << endl;
			break;
		}
	} while (userSelection != 4);
	cout << endl << root->occurrences;

	system("PAUSE");
}

void addNode(node * &inTree, string inString)
{
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
				current->occurrences = 1;
				cout << current->myString;
				added = true;
			}
			else
			{
				current = current->left;
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
				current->occurrences = 1;
				cout << current->myString;
				added = true;
			}
			else
			{
				current = current->right;
			}
		}
		else
		{
			// the string has already been found in a node, so increment the occurrences
			current->occurrences++;
			added = true;
		}
	}
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
		cout << current->myString << " ";
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
		cout << current->myString << " ";
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
		cout << current->myString << " ";
	}
}

void traverseLevelOrder(node * inTree)
{
	node * current = inTree;
	
}

void deleteNode(node * &inTree, string toDelete)
{
	node * current = inTree;
	if (current)
	{
		
	}
}