/*
This is an implementation of a binary tree, with searching and deletion.
Users can also use files to add many numbers at once.

Author: Luca Ardanaz
*/

#include <iostream>
#include <string>
#include <queue>
#include <fstream>

#include "Node.h"

using namespace std;

string toLower(string str);
void addNum(Node* &node, int num);
void printTree(Node* tree);
void print(Node* node, int depth);
void parseNumbers(Node* &tree, string input);
void deleteTree(Node* &tree);
Node* searchTree(Node* node, int num);
void removeFromTree(Node* &node, Node* &parent, int num);
void processFile(Node* &node);

int main() {

	Node* tree = nullptr;
	string input = "";
	
	do {
		//get user input
		cout << endl << endl;
		cout << "Enter numbers or a command (FILE, PRINT, SEARCH, DELETE, QUIT): " << endl;
		getline(cin, input);
		input = toLower(input);	
		
		//check if the input matches any commands, if not see if it's numbers
		
		if (input == "file") {
			processFile(tree);
			continue;
		}
		
		if (input == "print") {
			printTree(tree);
			continue;
		}
	
		if (input == "search") {
			//get input and make sure it is valid
			cout << "Enter a number to search for: " << endl;
			getline(cin, input);

			int num = 0;

			try {
				num = stoi(input);
			}
			catch(...) {
				cout << "Invalid input." << endl;
				continue;
			}

			//search the tree for this value
			bool found = searchTree(tree, num) != nullptr;

			cout << "Value" << (found ? " " : " not ") << "found in tree." << endl;

			continue;
		}

		if (input == "delete") {
			//get input and make sure it is valid
			cout << "Enter a number to remove: " << endl;
			getline(cin, input);

			int num = 0;
			try {
				num = stoi(input);
			}
			catch(...) {
				cout << "Invalid input." << endl;
				continue;
			}

			//delete the number from the tree
			removeFromTree(tree, tree, num);

			continue;
		}

		if (input == "quit") {
			continue;
		}

		//try to procces as a series of numbers
		parseNumbers(tree, input);

	} while(input != "quit");

	deleteTree(tree);
	
	return 0;
}

string toLower(string str) {
	for (char& c : str) {
		c = (char)tolower(c);
	}

	return str;
}

void addNum(Node* &node, int num) {

	//if the node is null, set as the new root
	if (node == nullptr) {
		node = new Node(num);
		return;
	}

	//if lower than the node, go left, if higher, go right
	
	if (num < node -> getNum()) {
		
		//check if the left child exists
		if (node -> getLeft() != nullptr) {
			addNum(node -> getLeft(), num);
		}
		//otherwise add this as the new left node
		else {
			node -> setLeft(new Node(num));
		}
	}

	else {
		
		//check if the right child exists
		if (node -> getRight() != nullptr) {
			addNum(node -> getRight(), num);
		}
		//otherwise add this as the new right node
		else {
			node -> setRight(new Node(num));
		}
	}	
}

void printTree(Node* tree) {
	cout << "Tree: " << endl;
	print(tree, 0);
	cout << endl;
}

void print(Node* node, int depth) {
	//if node is null, output that
	if (node == nullptr) {
		cout << "The tree is empty." << endl;
		return;
	}
	
	//prints everything to the right first
	if (node -> getRight() != nullptr) {
		print(node -> getRight(), depth + 1);
	}

	//adds appropriate indentation
	for (int i = 0; i < depth; i++) {
		cout << "\t";
	}

	//prints value
	cout << node -> getNum() << endl;

	//prints everything to the left
	if (node -> getLeft() != nullptr) {
		print(node -> getLeft(), depth + 1);
	}
}

void parseNumbers(Node* &tree, string input) {
	queue<int> numbers;

	string substring = "";

	for (char c : input) {

		//if there is a space, try parsing the substring to int
		if (c == ' ') {
			try {
				int num = stoi(substring);
				numbers.push(num);
				substring = "";
			}
			catch(...) {
				cout << "Invalid input." << endl;
				return;
			}
		}
		//otherwise, add the character to the substring
		else {
			substring += c;
		}
	}

	try {
		int num = stoi(substring);
		numbers.push(num);
		substring = "";
	}
	catch(...) {
		cout << "Invalid input." << endl;
		return;
	}

	//if the input was fully parsed, now just add the queue to the tree
	while (!numbers.empty()) {
		addNum(tree, numbers.front());
		numbers.pop();
	}
}

void deleteTree(Node* &tree) {
	//null node case
	if (tree == nullptr) {
		return;
	}

	//delete all children first
	if (tree -> getLeft() != nullptr) {
		deleteTree(tree -> getLeft());
	}
	
	if (tree -> getRight() != nullptr) {
		deleteTree(tree -> getRight());
	}

	delete tree;
}

Node* searchTree(Node* node, int num) {
	//if there is no node, return null
	if (node == nullptr) {
		return nullptr;
	}
	
	//if the node matches the value, return true
	if (node -> getNum() == num) {
		return node;
	}

	//if the number is less than the current node, go left, otherwise go right
	if (num < node -> getNum()) {
		
		if (node -> getLeft() != nullptr) {
			return searchTree(node -> getLeft(), num);
		}
		//if there is no further left, return false
		else {
			return nullptr;
		}
	}
	else {

		if (node -> getRight() != nullptr) {
			return searchTree(node -> getRight(), num);
		}
		//if there is no further right, return false
		else {
			return nullptr;
		}
	}
}

void removeFromTree(Node* &node, Node* &parent, int num) {
	
	//make sure that the node is not null
	if (searchTree(node, num) == nullptr) {
		cout << "Value not found in tree." << endl;
		return;
	}

	//get the chosen node and parent node
	
	if (num < node -> getNum()) {
		if (node -> getLeft() != nullptr) {
			removeFromTree(node -> getLeft(), node, num);
		}
		return;
	}
	else if (num > node -> getNum()) {
		if (node -> getRight() != nullptr) {
			removeFromTree(node -> getRight(), node, num);
		}
		return;
	}

	//figure out how to handle deletion
	
	//if no children, then simply delete
	if (node -> getLeft() == nullptr && node -> getRight() == nullptr) {
		//figure out which side of the parent to delete
		if (parent -> getLeft() != nullptr && parent -> getLeft() -> getNum() == num) {

			//if it is the root, set that to null rather than the parent
			if (node == parent) {
				delete node;
				node = nullptr;
				return;
			}
			else {
				delete node;
				parent -> setLeft(nullptr);
				return;
			}
		}
		else {
			
			//if this is the root, set that to null rather than the parent
			if (node == parent) {
				delete node;
				node = nullptr;
				return;
			}
			else {
				delete node;
				parent -> setRight(nullptr);
				return;
			}
		}
	}

	//if only has a left child
	if (node -> getLeft() != nullptr && node -> getRight() == nullptr) {
			
		Node* replacement = node -> getLeft();

		if (node == parent) {
			delete node;
			node = replacement;
		}

		else if (parent -> getLeft() != nullptr && parent -> getLeft() -> getNum() == num) {
			delete node;
			parent -> setLeft(replacement);
		}

		else if (parent -> getRight() != nullptr && parent -> getRight() -> getNum() == num) {
			delete node;
			parent -> setRight(replacement);
		}

		return;
	}	
	
	//if only has a right child
	if (node -> getRight() != nullptr && node -> getLeft() == nullptr) {
	
		Node* replacement = node -> getRight();

		if (node == parent) {
			delete node;
			node = replacement;
		}

		else if (parent -> getLeft() != nullptr && parent -> getLeft() -> getNum() == num) {
			delete node;
			parent -> setLeft(replacement);
		}

		else if (parent -> getRight() != nullptr && parent -> getRight() -> getNum() == num) {
			delete node;
			parent -> setRight(replacement);
		}

		return;

		}	

	//if has two children
	if (node -> getRight() != nullptr && node -> getLeft() != nullptr) {
		//save the children
		Node* leftChild = node -> getLeft();
		Node* rightChild = node -> getRight();

		//find the successor
		//go one to the right and then go to the left until reaching the end
		Node* successor = node -> getRight();
		Node* previous = nullptr;

		//get to the successor
		while (successor -> getLeft() != nullptr) {
			previous = successor;
			successor = successor -> getLeft();
		}

		//its ok if the replacement is null
		Node* replacement = nullptr;
		if (successor -> getRight() != nullptr) {
			replacement = successor -> getRight();
		}

		//delete the node and set the sucessor to be it
		delete node;
		node = successor;

		//make sure that the node right before the successor points to the elements after the successor
		if (previous != nullptr) {
			previous -> setLeft(successor -> getRight());
		}
		
		//make sure that we aren't linking a copy of the new node to itself
		if (leftChild != successor) {
			node -> setLeft(leftChild);
		}

		if (rightChild != successor) {
			node -> setRight(rightChild);
		}


	}
}

void processFile(Node* &node) {
	
	//first process the entire file to see if it is all valid
	//then add it to the tree

	cout << "Enter the file name: " << endl;
	string fileName;
	getline(cin, fileName);
	
	try {
		fstream file(fileName);
		
		//store the numbers in a queue
		queue<int>* numbers = new queue<int>();
	
		int num;
		string numStr;		

		//push the numbers into the queue
		while (getline(file, numStr)) {
			num = stoi(numStr);
			numbers -> push(num);
		} 

		//then add all of the numbers in the queue to the tree
		while (!numbers -> empty()) {
			addNum(node, numbers -> front());
			numbers -> pop();			
		}

		file.close();

	}
	catch(...) {
		return;
	}

}
