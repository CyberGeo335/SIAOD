#include "BTree.h"

TreeNode::TreeNode(int t1, bool leaf1)
{
	t = t1;
	leaf = leaf1;

	keys = new string[2 * t - 1];
	values = new int[2 * t - 1];
	C = new TreeNode *[2 * t];

	n = 0;
}

// Find the key
int TreeNode::findKey(string k)
{
	int idx = 0;
	while (idx < n && keys[idx] < k)
	{
		++idx;
	}
	return idx;
}

// Deletion operation
void TreeNode::deletion(string k)
{
	int idx = findKey(k);

	if (idx < n && keys[idx] == k)
	{
		if (leaf)
		{
			removeFromLeaf(idx);
		}
		else
		{
			removeFromNonLeaf(idx);
		}
	}
	else
	{
		if (leaf)
		{
			cout << "The key " << k << " is does not exist in the tree\n";
			return;
		}

		bool flag = ((idx == n) ? true : false);

		if (C[idx]->n < t)
		{
			fill(idx);
		}

		if (flag && idx > n)
		{
			C[idx - 1]->deletion(k);
		}
		else
		{
			C[idx]->deletion(k);
		}
	}
	return;
}

// Remove from the leaf
void TreeNode::removeFromLeaf(int idx)
{
	for (int i = idx + 1; i < n; ++i)
	{
		keys[i - 1] = keys[i];
		values[i - 1] = values[i];
	}

	n--;

	return;
}

// Delete from non leaf node
void TreeNode::removeFromNonLeaf(int idx)
{
	string k = keys[idx];
	int v = values[idx];

	if (C[idx]->n >= t)
	{
		string pred = getPredecessor(idx);
		keys[idx] = pred;
		C[idx]->deletion(pred);
	}

	else if (C[idx + 1]->n >= t)
	{
		string succ = getSuccessor(idx);
		keys[idx] = succ;
		C[idx + 1]->deletion(succ);
	}

	else
	{
		merge(idx);
		C[idx]->deletion(k);
	}
	return;
}

string TreeNode::getPredecessor(int idx)
{
	TreeNode *cur = C[idx];
	while (!cur->leaf)
	{
		cur = cur->C[cur->n];
	}

	return cur->keys[cur->n - 1];
}

string TreeNode::getSuccessor(int idx)
{
	TreeNode *cur = C[idx + 1];
	while (!cur->leaf)
		cur = cur->C[0];

	return cur->keys[0];
}

void TreeNode::fill(int idx)
{
	if (idx != 0 && C[idx - 1]->n >= t)
	{
		borrowFromPrev(idx);
	}

	else if (idx != n && C[idx + 1]->n >= t)
	{
		borrowFromNext(idx);
	}

	else
	{
		if (idx != n)
		{
			merge(idx);
		}
		else
		{
			merge(idx - 1);
		}
	}
	return;
}

// Borrow from previous
void TreeNode::borrowFromPrev(int idx)
{
	TreeNode *child = C[idx];
	TreeNode *sibling = C[idx - 1];

	for (int i = child->n - 1; i >= 0; --i)
	{
		child->keys[i + 1] = child->keys[i];
		child->values[i + 1] = child->values[i];
	}

	if (!child->leaf)
	{
		for (int i = child->n; i >= 0; --i)
		{
			child->C[i + 1] = child->C[i];
		}
	}

	child->keys[0] = keys[idx - 1];
	child->values[0] = values[idx - 1];

	if (!child->leaf)
	{
		child->C[0] = sibling->C[sibling->n];
	}

	keys[idx - 1] = sibling->keys[sibling->n - 1];
	values[idx - 1] = sibling->values[sibling->n - 1];

	child->n += 1;
	sibling->n -= 1;

	return;
}

// Borrow from the next
void TreeNode::borrowFromNext(int idx)
{
	TreeNode *child = C[idx];
	TreeNode *sibling = C[idx + 1];

	child->keys[(child->n)] = keys[idx];
	child->values[(child->n)] = values[idx];

	if (!(child->leaf))
	{
		child->C[(child->n) + 1] = sibling->C[0];
	}

	keys[idx] = sibling->keys[0];
	values[idx] = sibling->values[0];

	for (int i = 1; i < sibling->n; ++i)
	{
		sibling->keys[i - 1] = sibling->keys[i];
		sibling->values[i - 1] = sibling->values[i];
	}

	if (!sibling->leaf)
	{
		for (int i = 1; i <= sibling->n; ++i)
		{
			sibling->C[i - 1] = sibling->C[i];
		}
	}

	child->n += 1;
	sibling->n -= 1;

	return;
}

// Merge
void TreeNode::merge(int idx)
{
	TreeNode *child = C[idx];
	TreeNode *sibling = C[idx + 1];

	child->keys[t - 1] = keys[idx];
	child->values[t - 1] = values[idx];

	for (int i = 0; i < sibling->n; ++i)
	{
		child->keys[i + t] = sibling->keys[i];
		child->values[i + t] = sibling->values[i];
	}

	if (!child->leaf)
	{
		for (int i = 0; i <= sibling->n; ++i)
		{
			child->C[i + t] = sibling->C[i];
		}
	}

	for (int i = idx + 1; i < n; ++i)
	{
		keys[i - 1] = keys[i];
		values[i - 1] = values[i];
	}

	for (int i = idx + 2; i <= n; ++i)
	{
		C[i - 1] = C[i];
	}

	child->n += sibling->n + 1;
	n--;

	delete (sibling);
	return;
}
void TreeNode::traverse()
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (leaf == false)
		{
			C[i]->traverse();
		}
		cout << " " << keys[i];
		cout << " " << values[i];
	}

	if (leaf == false)
	{
		C[i]->traverse();
	}
}

int TreeNode::search(string k)
{
	int i = 0;
	while (i < n && k > keys[i])
	{
		i++;
	}

	if (keys[i] == k)
	{
		return values[i];
	}

	if (leaf == true)
	{
		return NULL;
	}

	return C[i]->search(k);
}

void BTree::insert(string k, int value)
{
	if (root == NULL)
	{
		root = new TreeNode(t, true);
		root->keys[0] = k;
		root->values[0] = value;
		root->n = 1;
	}
	else
	{
		if (root->n == 2 * t - 1)
		{
			TreeNode *s = new TreeNode(t, false);

			s->C[0] = root;

			s->splitChild(0, root);

			int i = 0;
			if (s->keys[0] < k)
			{
				i++;
			}
			s->C[i]->insertNonFull(k, value);

			root = s;
		}
		else
			root->insertNonFull(k, value);
	}
}

void TreeNode::insertNonFull(string k, int value)
{
	int i = n - 1;

	if (leaf == true)
	{
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			values[i + 1] = values[i];
			i--;
		}

		keys[i + 1] = k;
		values[i + 1] = value;
		n = n + 1;
	}
	else
	{
		while (i >= 0 && keys[i] > k)
		{
			i--;
		}

		if (C[i + 1]->n == 2 * t - 1)
		{
			splitChild(i + 1, C[i + 1]);

			if (keys[i + 1] < k)
			{
				i++;
			}
		}
		C[i + 1]->insertNonFull(k, value);
	}
}

void TreeNode::splitChild(int i, TreeNode *y)
{
	TreeNode *z = new TreeNode(y->t, y->leaf);
	z->n = t - 1;

	for (int j = 0; j < t - 1; j++)
	{
		z->keys[j] = y->keys[j + t];
		z->values[j] = y->values[j + t];
	}

	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
		{
			z->C[j] = y->C[j + t];
		}
	}

	y->n = t - 1;
	for (int j = n; j >= i + 1; j--)
	{
		C[j + 1] = C[j];
	}

	C[i + 1] = z;

	for (int j = n - 1; j >= i; j--)
	{
		keys[j + 1] = keys[j];
		values[j + 1] = values[j];
	}

	keys[i] = y->keys[t - 1];
	values[i] = y->values[t - 1];
	n = n + 1;
}

// Delete Operation
void BTree::deletion(string k)
{
	if (!root)
	{
		cout << "The tree is empty\n";
		return;
	}

	root->deletion(k);

	if (root->n == 0)
	{
		TreeNode *tmp = root;
		if (root->leaf)
		{
			root = NULL;
		}
		else
		{
			root = root->C[0];
		}

		delete tmp;
	}
	return;
}