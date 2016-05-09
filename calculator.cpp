#include "node.h"
#include "input.h"
#include "interface.h"
#include "calculator.h"

void Calculator::solveExpression()
{
	print(text.result, BLUE, LIGHT_GREY);
	cout << text.n + text.n;
	double result;
	if (!input.needTabulation)
	{
		result = treeRoot.countValue();
		cout << text.whiteSpaces[5];
		if (result == result)
			cout << result;
		else
			cout << text.NotANumber;
		cout << text.n;
		if (input.isExpressionConstant)
			print(text.constantExpression, LIGHT_GREY, BLUE);
	}
	else {
		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		SetConsoleScreenBufferSize(hStdOut, { csbi.dwSize.X, csbi.dwCursorPosition.Y + (short)((input.tabulation.end - input.tabulation.start) / input.tabulation.step) });
		Node* treeCopy = treeRoot.copyTree();
		for (input.X = input.tabulation.start; input.X <= input.tabulation.end; input.X += input.tabulation.step) {
			result = treeCopy->countValue();
			cout << text.whiteSpaces[5] << text.f << input.X << text.brackets[1] << text.equal;
			if (result == result)
				cout << result;
			else
				cout << text.NotANumber;
			cout << text.n;
			treeCopy->copyValuesBetweenTrees(treeCopy, &treeRoot);
		}
	}
	cout << text.whiteSpaces[5];
}