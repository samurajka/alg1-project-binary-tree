#include <string>
#include <iostream>

using namespace std;

//! \struct Node
/*!
* A Node contains a Value and a Left and Right Node pointer \n
* The Left and Right pointers can be null pointers
*/
struct Node {
	//! value of the Node
	int value;
	//! pointer to the left Node
	struct Node* left;
	//! pointer to the right Node
	struct Node* right;
};

//! \fn newNode
/*!
* The newNode function creates a new Node struct and returns a pointer to the new Node \n
* The Left and Right pointers are set to null
* \param v is an integer argument that sets the Value of the new Node
* \return Pointer to a new Node
*/
Node* newNode(int v) {
	Node* n = (Node*)malloc(sizeof(Node));

	n->value = v;
	n->left = nullptr;
	n->right = nullptr;

	return n;
}


//! \fn treeConstructor
/*!
* Function that constructs the binary tree \n
* This function shouldn't be called directly but rather through the treeFromString function
* \param str is a string from which the binary tree is constructed
* \param index is the index of str the function is curently processing
* \param strLen is the lenght of str
* \return Pointer to the root Node of the binary tree
*/
Node* treeConstructor(string str, int &index, int strLen) {

	// basecase, delka je nula nebo jsme na konci
	if (strLen == 0 || strLen <= index) {
		return nullptr;
	}

	// nacteni hodnoty uzlu
	int value = 0;
	// 
	while (index < strLen && str[index] != '(' && str[index] != ')') {
		value = value * 10;
		value += str[index] - '0'; //48; // 48 je ascii nuly
		index++;
	}


	struct Node* r = nullptr;
	if (value > 0) {
		r = newNode(value);
	}
	
	// najdu zavorku, volam levy Node
	if (index < strLen && str[index] == '(') {
		index++;
		r->left = treeConstructor(str, index, strLen);
	}

	if (index < strLen && str[index] == '(') { //najdu dalsi zavorku a volam pravy node
		index++;
		r->right = treeConstructor(str, index, strLen);
	}
	
	index++;
	return r; 
}

//! \fn treeFromString
/*!
* This function builds a binary tree from the given string
* \param str is a string from which the binary tree is constructed 
* \return Pointer to the root Node of the binary tree 
*/
Node* treeFromString(string str) {
	int i = 0;
	int strLen = str.size();
	Node* result = nullptr;
	result = treeConstructor(str, i, strLen);
	return result;
}

//! \fn stringConstructor
/*!
* This function saves a binary tree into a string \n
* This function shouldn't be called directly but rather through the stringFromTree function
* \param root is a pointer to the root Node of the tree
* \param str is the string where the tree will be stored
*/
void stringConstructor(Node* root, string& str) {

	// basecase
	if (root == nullptr) {
		return;
	}

	// zapsani value
	string strVal = to_string(root->value);
	int lenVal = strVal.size();
	for (int i = 0; i < lenVal; i++) {
		str.push_back(strVal[i]);
	}

	// neni kam pokracovat takze return
	if (root->left == nullptr && root->right == nullptr) {
		return;
	}

	if (root->left != nullptr) {
		str.push_back('(');
		stringConstructor(root->left, str);
		str.push_back(')');
	}

	if (root->right != nullptr) {
		str.push_back('(');
		stringConstructor(root->right, str);
		str.push_back(')');
	}
}

//! \fn stringFromTree
/*!
* This function saves a binary tree into a string
* \param root is a pointer to the root Node of the tree
* \return string representation of the given tree
*/
string stringFromTree(Node* root) {
	string result = "";
	stringConstructor(root, result);
	return result;
}


int main() {

	string str1 = "1";
	Node* root1 = treeFromString(str1);
	cout << stringFromTree(root1) << endl;

	string str2 = "1(2)(3)";
	Node* root2 = treeFromString(str2);
	cout << stringFromTree(root2) << endl;

	string str3 = "4(2(3)(1))(6(5))";
	Node* root3 = treeFromString(str3);
	cout << stringFromTree(root3) << endl;

	string str4 = "10(9(8)(7(6(5))))";
	Node* root4 = treeFromString(str4);
	cout << stringFromTree(root4) << endl;


	delete root1,root2,root3,root4;

	return 0;
}
/*


*/