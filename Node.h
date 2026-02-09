#ifndef NODE_H
#define NODE_H

class Node {
public:
	Node(int num) {
		number = num;
		left = nullptr;
		right = nullptr;
	}

	~Node() {
		left = nullptr;
		right = nullptr;
	}

	Node* &getLeft() {
		return left;
	}

	Node* &getRight() {
		return right;
	}

	void setLeft(Node* node) {
		left = node;
	}
	
	void setRight(Node* node) {
		right = node;
	}

	int getNum() {
		return number;
	}

private:
	int number;
	Node* left;
	Node* right;
};

#endif
