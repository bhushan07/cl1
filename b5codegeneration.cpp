#include <iostream>
#include <stdlib.h>
using namespace std;

struct bin_tree
{
	int label;
	char data;
	bin_tree *left,*right;
};
typedef bin_tree node;

class dag
{
private:
	int R[10];
	int top;
	char *op;

public:
	/*dag();
	~dag();*/

	void init_stack(node *root)
	{
		top = root->label - 1;

		int temp = top;
		for(int i=0;i<=top;i++)
		{
			R[i]=temp;
			temp--;
		}		
	}

	void insert_node(node **tree, char val)
	{
		node *temp = NULL;

		if(!(*tree))
		{
			temp = (node *)malloc(sizeof(node));
			temp->left=temp->right = NULL;
			temp->data = val;
			temp->label = -1;
			*tree = temp;
		}
	}

	void insert(node **tree, char val)
	{
		char l,r;
		int numberofchildren;

		insert_node(tree,val);		

		cout<<"Enter number of children of "<<val<<": ";
		cin>>numberofchildren;

		if(numberofchildren==2)
		{
			cout<<"Enter left child of node "<<val<<": ";
			cin>>l;
			insert_node(&(*tree)->left,l);
			cout<<"Enter right child of node "<<val<<": ";
			cin>>r;
			insert_node(&(*tree)->right,r);

			insert(&(*tree)->left,l);
			insert(&(*tree)->right,r);
		}
	}

	void findleafnodelabel(node *tree,int val)
	{
		if(tree->left!=NULL && tree->right!=NULL)
		{
			findleafnodelabel(tree->left,1);
			findleafnodelabel(tree->right,0);
		}
		else		
			tree->label = val;
		
	}

	void findinteriornodelabel(node *tree)
	{
		if(tree->left->label==-1)
			findinteriornodelabel(tree->left);
		else if (tree->right->label==-1)
			findinteriornodelabel(tree->right);
		else
		{
			if(tree->left!= NULL && tree->right!= NULL)
			{
				if(tree->left->label==tree->right->label)
					tree->label = (tree->left->label) +1;
				else
				{
					if(tree->left->label>tree->right->label)
						tree->label = tree->left->label;
					else
						tree->label = tree->right->label;
				}
			}
		}
	}

	void print_inorder(node *tree)
	{
		if(tree)
		{
			print_inorder(tree->left);
			cout<<tree->data<<" with label "<<tree->label<<endl;
			print_inorder(tree->right);
		}
	}

	void swap()
	{
		int temp = R[0];
		R[0] = R[1];
		R[1] = temp;
	}

	int pop()
	{
		int temp = R[top];
		top--;
		return temp;		
	}

	void push(int val)
	{
		top++;
		R[top] = val;
	}

	void nameofoperation(char temp)
	{
		switch(temp)
		{
			case '+': op = (char *)"ADD"; break;
			case '-': op = (char *)"SUB"; break;
			case '*': op = (char *)"MUL"; break;
			case '/': op = (char *)"DIV"; break;
		}
	}

	void gencode(node *tree)
	{
		if(tree->left!=NULL && tree->right!=NULL)
		{
			if(tree->left->label==1 && tree->right->label==0)
			{
				cout<<"MOV "<<tree->left->data<<" R["<<R[top]<<"]"<<endl;
				nameofoperation(tree->data);
				cout<<op<<" "<<tree->right->data<<" R["<<R[top]<<"]"<<endl;
			}
			else if(tree->left->label>=1 && tree->right->label==0)
			{
				gencode(tree->left);
				nameofoperation(tree->data);
				cout<<op<<" "<<tree->right->data<<" R["<<R[top]<<"]"<<endl;
			}
			else if(tree->left->label<tree->right->label)
			{				
				swap();
				gencode(tree->right);
				int temp = pop();
				gencode(tree->left);
				push(temp);
				swap();
				nameofoperation(tree->data);
				cout<<op<<" R["<<R[top-1]<<"] R["<<R[top]<<"]"<<endl;
			}
			else if(tree->left->label>=tree->right->label)
			{
				gencode(tree->left);
				int temp = pop();
				gencode(tree->right);
				push(temp);
				nameofoperation(tree->data);
				cout<<op<<" R["<<R[top-1]<<"] R["<<R[top]<<"]"<<endl;
			}
		}
		else if(tree->left==NULL && tree->right==NULL && tree->label==1)		
			cout<<"MOV "<<tree->data<<" R["<<R[top]<<"]"<<endl;		
	}

	void deltree(node *tree)
	{
		if(tree)
		{
			deltree(tree->left);
			deltree(tree->right);
			free(tree);
		}
	}
};

int main()
{
	node *root=NULL,*temp_node;
	char val;
	int i,temp;

	dag d;

	cout<<"Enter root of tree: ";
	cin>>val;

	d.insert(&root,val);

	d.findleafnodelabel(root,1);

	while(root->label == -1)	
		d.findinteriornodelabel(root);
	
	
	d.init_stack(root);
	

	d.print_inorder(root);

	d.gencode(root);

	d.deltree(root);

	return 0;
}
