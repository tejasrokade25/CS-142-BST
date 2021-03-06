//Binary search tree
#include<iostream>
using namespace std;

//The node class
class Node{
	public:
	int data;
	Node* l = NULL;
	Node* r = NULL;
	Node* p = NULL;
	
	//Constructor
	Node(int val){
		data = val;
	}
};

//The tree class
class BST{
	public:
	Node* root;
	int count = 0;
	//Constructor
	BST(){
		root = NULL;
	}

	//The functionssssssss......
	//Insert
	void insert(int value){
		//If tree is null insert and leave
		if(root==NULL){
			root = new Node(value);
			count++;
			return;
		}
		insertHelper(root, value);
		count++;
	}

	void insertHelper(Node* curr, int value){
		//move accordingly (but check before moving)
		if(curr->data > value){
			//If the next position is NULL, insert
			if(curr->l==NULL){
				curr->l = new Node(value);
				curr->l->p = curr;
				return;
			}
			//else go for recursion
			else{insertHelper(curr->l, value);}
		}
		else{
			//If the next position is NULL, insert
			if(curr->r==NULL){
				curr->r = new Node(value);
				curr->r->p = curr;
				return;
			}
			//else go for recursion
		 	else {insertHelper(curr->r, value);}
		}
		
	}

	void display(){
		display2(root);
		cout<<"\b "<<endl;
	}
	
	//This is inorder display...
	void display2(Node* curr){
		//Base condition
		if(curr == NULL){return;}
		//display left
		display2(curr->l);
		//display current
		cout << curr->data << ",";
		//display right
		display2(curr->r);
	}




	//Search
	Node* search(int val){
		return search2(val, root);
	}

	Node* search2(int val,Node* curr){
		//If tree is empty or reached the end of tree or value found
		if(curr == NULL || curr->data == val){return curr;}
		else if(curr->data > val){return search2(val, curr->l);}
		else{return search2(val, curr->r);}
	}

	//Find min.
	Node* fmin(int val){
		Node* curr = search(val);
		if(root==NULL||curr==NULL){return NULL;}
		return fmin2(val,curr);
	}

	Node* fmin2(int val, Node* curr){
		if(curr->l==NULL){return curr;}
		else{fmin2(val, curr->l);}
	}
	
	//Count
	int Count(){
		return count;
	}

	//Delete (mendouksei....)
	void Delete(int val){
		Node* curr = search(val);
		//If node doesn't exist
		if(curr==NULL){
			cout << "This value doesn't exist in the tree.\nTry again!"<<endl;
		}
		else{
			count--;
			//If it has only one kid
			if(curr->l&&curr->r==NULL||curr->l==NULL&&curr->r){
				//If left child exist
				if(curr->l&&curr->r==NULL){
				Node* temp = curr->l;
					//if current is root
					if(curr==root){root=temp;}
					else{
						//Wether curr is left child or right one
						if((curr->data)<(curr->p->data)){
							curr->p->l=temp;}

						else{curr->p->r=temp;}
					}
				temp->p=curr->p;
				}
				//If right child exist
				else{
					Node* temp = curr->r;
					//if current is root
					if(curr==root){root=temp;}
					else{
						//Wether curr is left child or right one
						if((curr->data)<(curr->p->data)){
							curr->p->l=temp;}
						else{curr->p->r=temp;}
					}
				temp->p=curr->p;
				}		
				delete curr;
				return;
			}
			//If it has 2 children
			if(curr->l&&curr->r){
				//Go for inorder succesor
				Node* temp = fmin(curr->r->data);
				curr->data = temp->data;
				//Removing previous links
				//Note:- The minimum may have a right child
				if(temp->r){
					temp->p->l=temp->r;
					temp->r->p=temp->p;
				}
				else{

					temp->p->l=NULL;
				}
				delete temp;
				return;
			}
			//If it is impotent
			if(curr->l==NULL&&curr->r==NULL){
				//if current is root
				if(curr==root){root=NULL;}
				//removing previous links
				if((curr->data)<(curr->p->data)){
					curr->p->l=NULL;
				}
				else{curr->p->r=NULL;}
				delete curr;
			}
		}
	}

};


int main(){
	BST b1;
	b1.insert(3);
	b1.insert(6);
	b1.insert(2);
	b1.insert(5);
	b1.insert(4);
	b1.insert(1);
	b1.insert(9);
	b1.insert(7);
	b1.insert(8);
	b1.display();
	Node* find = b1.search(2);
	if (find!=NULL){cout << find->data << endl;}
	else{cout << "The number is not there in the tree" << endl;} 
	
	Node* p = b1.fmin(6);
	cout << p-> data << endl;
	int r = b1.Count();
	cout << "No of nodes = " << r << endl;
	b1.display();
	b1.Delete(3);
	b1.display();
return 0;
}
