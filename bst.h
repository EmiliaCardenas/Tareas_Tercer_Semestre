/*
Emilia Cárdenas Lobatón
A01706807

Arbol de busqueda binaria
*/

#ifndef BST_H_
#define BST_H_
#include <iostream>
#include <string>
#include <sstream>
#include <stack>

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

	TreeNode<T>* succesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
	bool find(T);

	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;

	int getLevel(T val, int level);

	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri) {}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < value){
		if(left != 0){
			left -> add(val);
		}else{
			left = new TreeNode<T>(val);
		}
	} else{
		if(right != 0){
			right -> add(val);
		} else{
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value){
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
	return false;
} 

template <class T>
TreeNode<T>* TreeNode<T>::succesor() {
	TreeNode<T> *le, *ri, *parent, *child;
	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}
	
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}

template <class T>
int TreeNode<T>::getLevel(T val, int level){
	if (value == val) {
            return level;
        }
        if (val < value && left != 0) {
            return left->getLevel(val, level + 1);
        }
        if (val > value && right != 0) {
            return right->getLevel(val, level + 1);
        }
        return 0;
}

template <class T>
class BST{
    private:
	TreeNode<T> *root;

    public:
    BST();

    T add(T val);
    std::string visit();
    T height();
    std::string ancestors(T val);
    T whatlevelamI(T val);
	bool empty() const;

	std::string inorder() const;
	std::string preorder() const;
	std::string postorder() const;
	std::string ansestro(T) const; 
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template <class T>
T BST<T>::add(T val){
	if(root != 0){
		if (!root -> find(val)){
			root -> add(val);
		}
	}else{
		root = new TreeNode<T>(val);
	}
	return val;
}

template <class T>
std::string BST<T>::visit() {
    std::stringstream result;

    result << preorder() << "\n";
    result << inorder() << "\n";
    result << postorder() << "\n";
    result << preorder();

    return result.str();
}

template <class T>
T BST<T>::height() {
    if (root == NULL) {
        return 0;
    }

    std::stack<std::pair<TreeNode<T>*, int>> stack;
    stack.push({root, 1});

    int maxHeight = 0;

    while (!stack.empty()) {
        auto [node, currentHeight] = stack.top();
        stack.pop();

        if (node != NULL) {
            maxHeight = std::max(maxHeight, currentHeight);
            stack.push({node->right, currentHeight + 1});
            stack.push({node->left, currentHeight + 1});
        }
    }

    return maxHeight;
}



template <class T>
std::string BST<T>::ancestors(T val){
	std::stringstream aux;
    aux << "[";
    TreeNode<T>* current = root;
    bool encontrado = false;

    while (current != NULL) {
        if (val < current->value) {
            if (encontrado) aux << " "; 
            aux << current->value;
            current = current->left; 
            encontrado = true;
        } else if (val > current->value) {
            if (encontrado) aux << " ";
            aux << current->value;
            current = current->right;
            encontrado = true;
        } else {
            break;
        }
    }
    if (current == NULL) {
        return "[]"; 
    }
    aux << "]";
    return aux.str(); 
}

template <class T>
T BST<T>::whatlevelamI(T val){
	if (root == NULL) {
            return 0;
        }
        return root->getLevel(val, 1);
}


template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif