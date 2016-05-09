#include "builder.h"
#include "filehandler.h"
#include "interface.h"
#include "lexer.h"
#include "input.h"
#include "enum.h"
#include "node.h"

void Builder::loadExpression()
{
	try {
		if (input.isFromFile)
			fileHandler.tryToOpenFile(input.fullPathToFile, input.shortPathToFile);
		input.getExpression();
		lexer.clearWhiteCharacters(input.expression);
		if (!input.expression.size())
			throw unsigned int(EMPTY_EXPRESSION_ERROR);
		lexer.loadExpression(input.expression);
		double buffer;
		Node *current = &treeRoot;
		input.isExpressionConstant = true;
		unsigned int lexem, lexemAttached, bracketsOpened(0);
		do {
			lexemAttached = 0;
			lexem = lexer.getLexem(buffer, lexemAttached);
			switch (lexem)
			{
			case LEFT_BRACKET:
			{
				bracketsOpened++;
				if (current->sideOperation) {
					Node *newSideNode = new Node;
					current->rightPointer = newSideNode;
					newSideNode->leftPointer = current;
					current = newSideNode;
				}
				Node *newInNode = new Node;
				current->inPointer = newInNode;
				newInNode->outPointer = current;
				current = newInNode;
				break;
			}
			case RIGHT_BRACKET:
			{
				if (bracketsOpened)
					bracketsOpened--;
				else
					throw unsigned int(BRACKETS_FORMATTING_ERROR);
				if (current->sideOperation)
					throw unsigned int(OPERATOR_FORMATTING_ERROR);
				if (current->leftPointer)
				{
					if (current->leftPointer->sideOperation == MULTIPLICATION) {
						while (current->leftPointer)
							current = current->leftPointer;
						current = current->outPointer;
					}
					while (current->leftPointer)
						current = current->leftPointer;					
				}
				current = current->outPointer;
				if (lexemAttached != END_OF_EXPRESSION) {
					if (lexemAttached == MULTIPLICATION) {
						if (current->leftPointer) {
							if (current->leftPointer->sideOperation != MULTIPLICATION) {
								Node *newOutNode = new Node;
								current->outPointer = newOutNode;
								newOutNode->inPointer = current;
								current->leftPointer->rightPointer = newOutNode;
								newOutNode->leftPointer = current->leftPointer;
								current->leftPointer = nullptr;
							}
						}
						else {
							Node *newOutNode = new Node;
							newOutNode->outPointer = current->outPointer;
							current->outPointer = newOutNode;
							newOutNode->inPointer = current;
						}
					}
					else {
						if (current->leftPointer && current->leftPointer->sideOperation == MULTIPLICATION) {
								while (current->leftPointer && current->leftPointer->sideOperation == MULTIPLICATION)
									current = current->leftPointer;
								current = current->outPointer;
						}
					}
					current->sideOperation = lexemAttached;
				}
				break;
			}
			case LOGARIPHM:
			{
				bracketsOpened++;
				if (current->sideOperation) {
					Node *newSideNode = new Node;
					current->rightPointer = newSideNode;
					newSideNode->leftPointer = current;
					current = newSideNode;
				}
				Node *newInNode = new Node;
				current->inPointer = newInNode;
				current->inOperation = LOGARIPHM;
				newInNode->outPointer = current;
				current = newInNode;
				break;
			}
			case COSINUS:
			{
				bracketsOpened++;
				if (current->sideOperation) {
					Node *newSideNode = new Node;
					current->rightPointer = newSideNode;
					newSideNode->leftPointer = current;
					current = newSideNode;
				}
				Node *newInNode = new Node;
				current->inPointer = newInNode;
				current->inOperation = COSINUS;
				newInNode->outPointer = current;
				current = newInNode;
				break;
			}
			case VARIABLE:
			{
				input.isExpressionConstant = false;
				if (current->sideOperation)
				{
					Node *newSideNode = new Node;
					Node *newSideInNode = new Node;
					newSideNode->inPointer = newSideInNode;
					newSideInNode->outPointer = newSideNode;
					newSideInNode->inOperation = SUBSTITUTION;
					if (lexemAttached != END_OF_EXPRESSION) {
						if (current->sideOperation == MULTIPLICATION)
						{
							current->rightPointer = newSideNode;
							newSideNode->leftPointer = current;
							if (lexemAttached == MULTIPLICATION)
								current = newSideNode;
							else
								if (current->leftPointer && current->leftPointer->sideOperation == MULTIPLICATION) {
									while (current->leftPointer && current->leftPointer->sideOperation == MULTIPLICATION)
										current = current->leftPointer;
									current = current->outPointer;
							}
						}
						else
						{
							if (lexemAttached == MULTIPLICATION)
							{
								Node *newInNode = new Node;
								current->rightPointer = newInNode;
								newInNode->leftPointer = current;
								newInNode->inPointer = newSideNode;
								newSideNode->outPointer = newInNode;
							}
							else {
								current->rightPointer = newSideNode;
								newSideNode->leftPointer = current;
							}
							current = newSideNode;
						}
						current->sideOperation = lexemAttached;
					}
					else
					{
						current->rightPointer = newSideNode;
						newSideNode->leftPointer = current;
					}
				}
				else {
					if (lexemAttached == MULTIPLICATION)
					{
						Node *newInNode = new Node;
						current->inPointer = newInNode;
						newInNode->outPointer = current;
						current = newInNode;
					}
					Node *newInNode = new Node;
					current->inPointer = newInNode;
					newInNode->outPointer = current;
					newInNode->inOperation = SUBSTITUTION;
					if (lexemAttached != END_OF_EXPRESSION)
						current->sideOperation = lexemAttached;
				}
				break;
			}
			case INVARIABLE:
			{
				if (current->sideOperation)
				{
					Node *newSideNode = new Node;
					newSideNode->value = buffer;
					if (lexemAttached != END_OF_EXPRESSION) {
						if (current->sideOperation == MULTIPLICATION)
						{
							current->rightPointer = newSideNode;
							newSideNode->leftPointer = current;
							if (lexemAttached == MULTIPLICATION)
								current = newSideNode;
							else {							
								while (current->leftPointer && current->leftPointer->sideOperation == MULTIPLICATION)
									current = current->leftPointer;
								current = current->outPointer;
							}
						}
						else
						{
							if (lexemAttached == MULTIPLICATION)
							{
								Node *newInNode = new Node;
								current->rightPointer = newInNode;
								newInNode->leftPointer = current;
								newInNode->inPointer = newSideNode;
								newSideNode->outPointer = newInNode;
							}
							else {
								current->rightPointer = newSideNode;
								newSideNode->leftPointer = current;						
							}
							current = newSideNode;
						}
						current->sideOperation = lexemAttached;
					}
					else
					{
						current->rightPointer = newSideNode;
						newSideNode->leftPointer = current;
					}
				}
				else {
					if (lexemAttached == MULTIPLICATION)
					{
						Node *newInNode = new Node;
						current->inPointer = newInNode;
						newInNode->outPointer = current;
						current = newInNode;
					}
					if (lexemAttached != END_OF_EXPRESSION)
						current->sideOperation = lexemAttached;
					current->value = buffer;
				}
				break;
			}
			}
		} while (lexem != END_OF_EXPRESSION && lexemAttached != END_OF_EXPRESSION);
		if (bracketsOpened)
			throw unsigned int(BRACKETS_FORMATTING_ERROR);
		while (current->rightPointer)
			current = current->rightPointer;
		if (current->sideOperation)
			throw unsigned int(OPERATOR_FORMATTING_ERROR);
	}
	catch (unsigned int errorCode) {
		print(text.error + text.builderErrors[errorCode] + text.sound, WHITE, RED);
		if (errorCode == FILE_OPEN_ERROR && input.pathFromConsole)
			cout << text.n << text.argumentsHelp;
		throw true;
	}
}