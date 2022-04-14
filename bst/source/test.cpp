#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct node *Node;
struct node {
	int key;	/*key*/
	int val;	/*associated value*/
	Node left;	/*link to subtrees*/
	Node right;	
	int N;		/* # nodes in subtree rooted here*/
};


Node newNode(int key, int val, Node l, Node r, int N) {
	Node p = (Node)malloc(sizeof(*p));
	p->key = key;
	p->val = val;
	p->left = r;
	p->right = r;
	p->N = N;
	return p;
} 

int main() {
	Node p = newNode(1, 1, NULL, NULL, 1);
	cout << p->key << endl;
}
// 	// strcmp(str1,str2)
// 	// == 0 -> iguais
// 	// > 0 -> str1 > str2
// 	// < 0 str1 < str2

// getHashCode(key) {
// 	return  strcmp(key)%table_size
// }

// class Hashtable {
// 	LinkedList[] data
// 	boolean put(Key, value) {
// 		int hashCode = getHashCode(key);
// 		int index = convertToIndex(hashCode)
// 		LinkedList list = data[index];
// 		list.insert(key, value)
// 	}
// }


// bfs(Node s, Node e) {

// }
