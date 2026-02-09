#ifndef NODE_H
#define NODE_H

class Node {
public:
	Node(int num, bool isBlack) {
		number = num;
		left = nullptr;
		right = nullptr;
		black = isBlack;
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

	void setBlack(bool isBlack) {
		black = isBlack;
	}

	bool isBlack() {
		return black;
	}

private:
	int number;
	Node* left;
	Node* right;
	bool black;
};

#endif
