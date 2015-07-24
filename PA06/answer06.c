#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Create a single instance of a sparse array tree node with a specific
 * index and value. This sparse array will be implemented by a binary search
 * tree.
 *
 * Arguments:
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 *
 * returns:
 * SparseNode *  the pointer points to the node just constructed
 *
 * This is a constructor function that allocates memory for a sparse array tree
 * node, sets the given index and value, and initialize the subtree pointers to
 * NULL.
 */
SparseNode * SparseNode_create(int index, int value)
{
	SparseNode * node = malloc(sizeof(SparseNode));
	node->value = value;
	node->index = index;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/* Add a particular value into a sparse array tree at a particular index.
 *
 * Arguments:
 * array         the root node of the sparse array tree
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 *
 * returns:
 * SparseNode *  the pointer points to the root node of the modified sparse
 *               array tree
 *
 * The sparse array tree uses the index as a key in a binary search tree.
 * If the index does not exist, create it.
 * If the index exists, REPLACE the value with the new one.
 * Use the index to determine whether to go left or right in the tree (smaller
 * index values than the current one go left, larger ones go right).
 * (For this assignment, you should not insert nodes with a value of 0)
 */
SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
	if(NULL == array)
	{
		SparseNode * temp = SparseNode_create(index, value);
		array = temp;
		return array; 
	}
	if(array->index == index)
	{
		array->value = value;
		return array;
	}
	if(value == 0 || value == NULL)
	{
		return array;
	}
	if(array->index > index)
	{
		if(array->left == NULL)
		{
			SparseNode * temp = SparseNode_create(index, value);
			array->left = temp;
		}
		else
		{
			SparseArray_insert(array->left, index, value);
		}
		
	}
	else
	{
		if(array->right == NULL)
		{
			SparseNode * temp = SparseNode_create(index, value);
			array->right = temp;
		}
		else
		{
			SparseArray_insert(array->right, index, value);
		}
	}
	return array;
}

/**
 * Build a sparse array tree from given array of indices and array of values,
 * each having the same length.
 *
 * Arguments:
 * indices      a pointer pointing to the start position of the index array
 * values       a pointer pointing to the start position of the value array
 * length       the size of each of the above input arrays
 *
 * returns:
 * SparseNode *     the pointer points to the root node of sparse array
 *                  tree just constructed
 *
 * It returns a sparse array tree.  You need to insert tree nodes in order,
 * starting from index zero of the array.
 *
 * i.e. The first sparse array node contains indices[0] and values[0], second node
 * contains indices[1] and values[1], etc. Basically, elements of the index array
 *  and value array that have the same array index form a sparse array pair 
 * and should go into the same sparse array node.
 */

SparseNode * SparseArray_build(int * indices, int * values, int length)
{
	int i;
	SparseNode * newarray = malloc(length * sizeof(SparseNode));
	
	for(i = 0; i < length; i++)
	{
		SparseNode * temp = NULL;
		temp = SparseArray_insert(newarray, indices[i], values[i]);
		newarray = temp;
		free(temp);
	}
	return newarray;
}

/**
 * Destroy an entire sparse array node and its subtrees.
 *
 * Arguments:
 * array          the root node of a sparse array tree
 *
 * returns: void
 *
 * Traversing the binary tree in postorder, use the SparseArray_destroy()
 * function to destroy each node individually.
 */
void SparseArray_destroy(SparseNode * array)
{
	if(NULL == array)
	{
		return;
	}
	SparseArray_destroy(array->left);
	SparseArray_destroy(array->right);
	free(array);
	
	return;
}

/**
 * Retrieve the smallest index in the sparse array tree.
 *
 * Arguments:
 * array        the root node of a sparse array tree, is never NULL
 *
 * returns:
 * int          the smallest index in the sparse array tree
 *
 * If array is NULL then it does not make sense to get the max value,
 * so you are free to do whatever you think is appropriate. 
 *
 * (Hint: consider the property of binary search tree)
 */
int SparseArray_getMin(SparseNode * array)
{
	SparseNode * current = array;
	
	while(current->left != NULL)
	{
		current = current->left;
	}
	
	return(current->index);
}

/**
 * Retrieve the largest index in the sparse array tree.
 *
 * Arguments:
 * array        the root node of a sparse array tree, is never NULL
 *
 * returns:
 * int          the largest index in the sparse array tree
 *
 * If array is NULL then it does not make sense to get the max value,
 * so you are free to do whatever you think is appropriate. 
 *
 * (Hint: consider the property of binary search tree)
 */
int SparseArray_getMax(SparseNode * array)
{
	SparseNode * current = array;
	
	while(current->right != NULL)
	{
		current = current->right;
	}
	
	return(current->index);
}

/**
 * Retrieve the node associated with a specific index in a sparse array tree.
 *
 * Arguments:
 * array        the root node of a sparse array tree
 * index        the index of the node you want to search for
 *
 * returns:
 * SparseNode *     the node with the index that you searched from the tree.
 *                  If no node is found, NULL should be returned.
 *
 * (Hint: consider the property of binary search tree)
 */
SparseNode * SparseArray_getNode(SparseNode * array, int index)
{
	if(NULL == array)
	{
		return NULL;
	}
	else if(index == array->index)
	{
		return array;
	}
	else if(index < array->index)
	{
		return(SparseArray_getNode(array->left, index));
	}
	else if(index > array->index)
	{
		return(SparseArray_getNode(array->right, index));
	}
	else
	{
		return NULL;
	}
}

/**
 * Remove a value associated with a particular index from the sparse array. It
 * returns the new sparse array tree ( binary tree root ).
 *
 * Arguments:
 * array        the root node of a sparse array tree
 * index        the index of the node you want to remove
 *
 * returns:
 * SparseNode *     the root node of the sparse array tree that you just
 *                  modified
 *
 * HINT : First, you need to go to that node. Then, you will need to isolate
 * several different cases here :
 * - If array is empty ( NULL ), return NULL.
 * - Go left or right if the current node index is different.
 * - If both subtrees are empty, you can just remove the node.
 * - If one subtree is empty, you can just remove the current node and replace it
 *   with the non - empty child.
 * - If both children exist, you must find the immediate successor of the
 *   current node ( leftmost of right branch ), swap its values with the
 *   current node ( BOTH index and value ), and then delete the index in the
 *   right subtree.
 */
SparseNode * findSuccessor(SparseNode * array)
{
	if(array->right == NULL)
	{
		return findSuccessor(array->left);
	}
	else
	{
		return array;
	}
}
 
/* 
SparseNode * SparseArray_remove(SparseNode * array, int index)
{
	if(NULL == array)
	{
		return NULL;
	}
	else if(index < array->index)
	{
		SparseArray_remove(array->left, index);
	}
	else if(index > array->index)
	{
		SparseArray_remove(array->right, index);
	}
	else if(index == array->index)
	{
		if(array->right == NULL && array->left == NULL)
		{
			free(array);
			return 0;
		}
		else if(array->right == NULL)
		{
			array = array->left;
			free(array->left);
			return 0;
		}
		else if(array->left == NULL)
		{
			array = array->right;
			free(array->right);
			return 0;
		}
		else
		{
			SparseNode * temp = findSuccessor(array->right);
			array = temp;
			free(temp);
			return 0;
		}
	}
	
	return array;
}
*/

SparseNode * removeLeftMost(SparseNode * node, SparseNode * remove) 
{
    if (node == remove) 
	{
       return node->right; // Note that remove->left should be null
    }
    else 
	{
       node->left = removeLeftMost(node->left,remove);
       return node;
    }
}

SparseNode * SparseArray_remove(SparseNode * array, int index)
{
	if(NULL == array)
	{
		return NULL;
	}
	else if(index < array->index)
	{
		SparseArray_remove(array->left, index);
	}
	else if(index > array->index)
	{
		SparseArray_remove(array->right, index);
	}
	
	else if(index == array->index)
	{
		SparseNode * temp;
		
		if(array->right == NULL && array->left == NULL)
		{
			temp = NULL;
		}
		else if(array->right == NULL && array->left != NULL)
		{
			temp = array->left;
		}
		else if(array->left == NULL && array->right != NULL)
		{
			temp = array->right;
		}
		else
		{
			temp = findSuccessor(array->right);
			temp->right = removeLeftMost(array->right, temp);
			temp->left = array->left;
		}
		free(array);
		array = temp;
		free(temp);
		return NULL;
	}
	
	return array;
}
/**
 * The function makes a copy of the input sparse array tree and returns this
 * new copy.
 *
 * Arguments:
 * array            the root node of a sparse array tree
 *
 * returns:
 * SparseNode *     the root node of the new sparse array tree that you
 *                  just copied from the input sparse array tree.
 *
 * To copy the array you will need to traverse the tree. See README Hints on
 * iterate.
 */
SparseNode * SparseArray_copy(SparseNode * array)
{
	if (array != NULL)
	{
		SparseNode * copyNode = malloc(sizeof(SparseNode));
		copyNode->index = array->index;
		copyNode->value = array->value;
		copyNode->left = SparseArray_copy(array->left);
		copyNode->right = SparseArray_copy(array->right);
		return copyNode;
	}
	else
	{
		return NULL;
	}
	return NULL;
}

/**
 * Merge array_1 and array_2, and return the result array.  This function WILL
 * NOT CHANGE the contents in array_1 and array_2.
 *
 * Arguments:
 * array_1          the root node of the first sparse array tree
 * array_2          the root node of the second sparse array tree
 *
 * returns:
 * SparseNode *     the root node of the new sparse array tree that you
 *                  just merged from the two input sparse array tree
 *
 * When merging two sparse array tree:
 * 1. The contents in array_1 and array_2 should not be changed. You should
 *    make a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in
 *    array_2 and insert them into array_1.
 * 3. You need to traverse the array_2 tree. (See README Hints on iterate.)
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 *
 * Hint: you may write new functions
 */
SparseNode * SparseArray_copymerge(SparseNode * new, SparseNode * array_1)
{
	new = malloc(sizeof(SparseNode));
	
	if (array_1)
	{
		new->index = array_1->index;
		new->value = array_1->value;
		new->left = SparseArray_copymerge(new, array_1->left);
		new->right = SparseArray_copymerge(new, array_1->right);
	}
	
	return new;
}

SparseNode * SparseArray_merge2(SparseNode * new, SparseNode * array_2)
{
	if (array_2)
	{
		if(new->index < array_2->index)
		{
			return(SparseArray_merge2(new->right, array_2));
		}
		else if(new->index > array_2->index)
		{
			return(SparseArray_merge2(new->left, array_2));
		}
		else if(new->index == array_2->index)
		{
			new->value += array_2->value;
		}
		else if(NULL == new)
		{
			SparseArray_insert(array_2, array_2->index, array_2->value);
		}
	}
	return array_2;
}
 
SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
	SparseNode * new = malloc(sizeof(SparseNode));
	
	if (array_1)
	{
		new->index = array_1->index;
		new->value = array_1->value;
		new->left = SparseArray_copymerge(new, array_1->left);
		new->right = SparseArray_copymerge(new, array_2->right);
	}
	
	if (array_2)
	{
		if(new->index < array_2->index)
		{
			(SparseArray_merge2(new->right, array_2));
		}
		else if(new->index > array_2->index)
		{
			(SparseArray_merge2(new->left, array_2));
		}
		else if(new->index == array_2->index)
		{
			new->value += array_2->value;
		}
		while(array_2->left)
		{
			SparseArray_merge2(new, array_2);
			while(array_2->right)
			{
				SparseArray_merge2(new, array_2);
			}
		}
		while(array_2->right)
		{
			SparseArray_merge2(new, array_2);
			while(array_2->left)
			{
				SparseArray_merge2(new, array_2);
			}
		}
	}
	
	return new;
}
