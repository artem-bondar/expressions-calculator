#include "node.h"
#include "input.h"
#include "enum.h"

const double Node::countValue()
{
	if (rightPointer || inPointer) {
		if (inPointer) {
			switch (inOperation) {
			case LOGARIPHM:
			{
				value += (1 - 2 * (leftPointer && leftPointer->sideOperation == SUBSTRACTION)) * log(inPointer->countValue());
				break;
			}
			case COSINUS:
			{
				value += (1 - 2 * (leftPointer && leftPointer->sideOperation == SUBSTRACTION)) * cos(inPointer->countValue());
				break;
			}
			case EMPTY:
				value += (1 - 2 * (leftPointer && leftPointer->sideOperation == SUBSTRACTION)) * inPointer->countValue();
			}
		}
		if (rightPointer)
		{
			switch (sideOperation) {
			case MULTIPLICATION: return value * rightPointer->countValue();
			case ADDITION:		 
			{
				rightPointer->value += value;
				return rightPointer->countValue();
			}
			case SUBSTRACTION:	 
			{
				rightPointer->value = value - rightPointer->value;
				return rightPointer->countValue();
			}
			}
		}
		if (inPointer && !rightPointer)
			return value;
	}
	else {
		switch (inOperation)
		{
		case LOGARIPHM:		return log(value);
		case COSINUS:		return cos(value);
		case SUBSTITUTION:	return input.getX();
		case EMPTY:			return value;
		}
	}
}

void Node::setAllNull()
{
	leftPointer = rightPointer = inPointer = outPointer = nullptr;
	sideOperation = inOperation = EMPTY;
	value = 0;
}

Node::Node(const Node &tree)
{
	value = tree.value;
	inOperation = tree.inOperation;
	sideOperation = tree.sideOperation;
}

Node* Node::copyTree()
{
	Node* newTree = new Node;
	*newTree = *this;
	if (this->inPointer)
	{
		Node* deepTree = new Node;
		deepTree = this->inPointer->copyTree();
		newTree->inPointer = deepTree;
		deepTree->outPointer = newTree;
	}
	if (this->rightPointer)
	{
		Node* sideTree = new Node;
		sideTree = this->rightPointer->copyTree();
		newTree->rightPointer = sideTree;
		sideTree->leftPointer = newTree;
	}
	return newTree;
}

void Node::copyValuesBetweenTrees(Node* copy, const Node* original)
{
	copy->value = original->value;
	if (copy->inPointer)
		copyValuesBetweenTrees(copy->inPointer, original->inPointer);
	if (copy->rightPointer)
		copyValuesBetweenTrees(copy->rightPointer, original->rightPointer);
}