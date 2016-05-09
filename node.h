#ifndef CONTAINER_H
#define CONTAINER_H

class Node {
public:
	
	Node() { setAllNull(); }
	Node(const Node &tree);

	void
		copyValuesBetweenTrees(Node* copy, const Node* original);

	const double
		countValue();

	Node*
		copyTree();

private:

	friend class Builder;

	void setAllNull();

	double value;

	Node *leftPointer, *rightPointer, *inPointer, *outPointer;

	unsigned int sideOperation, inOperation;

};

extern Node treeRoot;

#endif