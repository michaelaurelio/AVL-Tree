#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
	int ht;//height of node
};
struct node* root = NULL;


struct node* create_node(int data){
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	new_node->data = data;
	new_node->right = NULL;
	new_node->left = NULL;
	
	return new_node;
}

int max(int a, int b){
	return a > b ? a : b;
}

int balance_factor(struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	return lh - rh;
}


int height (struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	if (lh > rh)
		return lh;
	return rh;
}

struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);
 
    // return the new node after rotation
    return right_child;
}

struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);
 
    // return the new node after rotation
    return left_child;
}

struct node* insert (struct node* root, int data){
	if(root == NULL){
		struct node* new_node = create_node(data);
		root = new_node;
	}
	else if ( data > root->data){
		root->right = insert(root->right, data);
		
		//if unbalanced, rotate!
		if (balance_factor(root) == -2){
			if (data > root->right->data){//case RR
				root = rotate_left(root);
			}
			else{ //case RL
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}			
		}		
	}
	else{
		root->left = insert(root->left, data);
		
		if (balance_factor(root) == 2){
			//CASE LL
			if (data < root->left->data){ 
				root = rotate_right(root);
			}
			//CASE LR
			else{
				root->left = rotate_left(root->left);
				root = rotate_right(root);

			}
		}
	}
	//get height of node
	root->ht = height(root);
	return root;
}

struct node *find_pred(struct node *curr){
	while(curr->left != NULL) curr = curr->left;
	return curr;
}

struct node *deletion(struct node *curr, int dat){
	if(curr == NULL) return curr;
	if(dat < curr->data) curr->left = deletion(curr->left, dat);
	else if(dat > curr->data) curr->right = deletion(curr->right, dat);
	else {
		if(curr->left == NULL || curr->right == NULL){
			struct node *temp = curr->left ? curr->left : curr->right;
			if(temp == NULL){
				temp = curr;
				curr = NULL;
			} else {
				*curr = *temp;
			}
			free(temp);
		} else {
			struct node *temp = find_pred(curr->right);
			curr->data = temp->data;
			curr->right = deletion(curr->right, temp->data);
		}
	}
	
	if(curr == NULL) return curr;
	curr->ht = 1 + max(height(curr->left), height(curr->right));
	
	int bal = balance_factor(curr);
	if(bal > 1 && balance_factor(curr->left) >= 0) return rotate_right(curr); // LL Case
	if(bal > 1 && balance_factor(curr->left) < 0){ // LR Case
		curr->left = rotate_left(curr->left);
		return rotate_right(curr);
	}
	if(bal < -1 && balance_factor(curr->right) <= 0) return rotate_left(curr); // RR Case
	if(bal < -1 && balance_factor(curr->right) > 0){ // RL Case
		curr->right = rotate_right(curr->right);
		return rotate_left(curr);
	}
	
	return curr;
}

// inorder traversal of the tree
void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
 
// preorder traversal of the tree
void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
 
// postorder traversal of the tree
void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void search(struct node *curr, int dat){
	if(curr == NULL){
		printf("%d Not Found.\n", dat);
		return;
	}
	if(dat < curr->data) search(curr->left, dat);
	else if(dat > curr->data) search(curr->right, dat);
	else {
		printf("%d Found.\n", dat);
		return;
	}
}

void delete_all(struct node *curr){
	if(curr == NULL) return;
	delete_all(curr->left);
	delete_all(curr->right);
	free(curr);
}

void horizontal_line(){
	printf("================================\n\n");
}

int main(){
	printf("Initial Tree :\n");

	root = insert(root, 10);
	root = insert(root, 15); 
	root = insert(root, 20); 
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 16);
	root = insert(root, 17);
	root = insert(root, 8);
	root = insert(root, 6);
	
	inorder(root); printf("\n\n");
	
	// searching
	horizontal_line();
	printf("Searching %d...\n", 15);
	search(root, 15);
	printf("\n");
	printf("Searching %d...\n", 50);
	search(root, 50);
	printf("\n");
	
	delete_all(root);
	root = NULL;
	
	//Soal
	//terapkan deletion dengan memberikan 4 kasus rotation(LL, RR, LR, RL)
	//lengkapi juga searching pada AVL tree ini
	
	// Left - Left Case
	horizontal_line();
	printf("Left - Left Case :\n");
	
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 0);
	root = deletion(root, 30);
	
	inorder(root); printf("\n\n");
	delete_all(root);
	root = NULL;
	
	
	
	// Right - Right Case
	horizontal_line();
	printf("Right - Right Case :\n");
	
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 40);
	root = deletion(root, 10);
	
	inorder(root); printf("\n\n");
	delete_all(root);
	root = NULL;
	
	// Left - Right Case
	horizontal_line();
	printf("Left - Right Case :\n");
	
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 15);
	root = deletion(root, 30);
	
	inorder(root); printf("\n\n");
	delete_all(root);
	root = NULL;
	
	// Right - Left Case
	horizontal_line();
	printf("Right - Left Case :\n");
	
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 25);
	root = deletion(root, 10);
	
	inorder(root); printf("\n\n");
	delete_all(root);
	root = NULL;
	
	
	return 0;
}