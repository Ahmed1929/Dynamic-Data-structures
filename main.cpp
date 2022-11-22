#include <iostream>

using namespace std;

class btree
{
private:
	struct tnode
{
	int item;
	tnode*left;
	tnode*right;
};
tnode*root;
public:
	btree();
	
	void insertitem(int);
	void insert(tnode*&,int);
	
	void inorder(tnode*);
	void postorder(tnode*);
	void preorder(tnode*);

	void removeitem(int);
	void remove(tnode*&,int);
	void removnode(tnode*&);
	void processleftmost(tnode*&,int&);

	void searchitem(int);
	void search(tnode*,int);

	tnode*getroot(){return root;}

};
btree::btree()
{
	root=NULL;
}
void btree::insertitem(int item)
{
	insert(root,item);
}
void btree::insert(tnode*&ptr,int item)
{
	if(ptr==NULL)
	{
		ptr=new tnode;
		if(ptr==NULL)
			cout<<"can not allocation of memore"<<endl;
		else
		{
			ptr->right=NULL;
		    ptr->left=NULL;
            ptr->item=item;
		}
	}
	else
	{
		if(item<ptr->item)
			insert(ptr->left,item);
		else
			insert(ptr->right,item);
	}
}
void btree::inorder(tnode*cur)
{
	if(cur==NULL)
		return;
	else
	{
    inorder(cur->left);
	cout<<cur->item<<"\t";
    inorder(cur->right);
	}
}
void btree::postorder(tnode*cur)
{
	if(cur==NULL)
		return;
	else
	{
    postorder(cur->left);
    postorder(cur->right);
	cout<<cur->item<<"\t";
	}
}
void btree::preorder(tnode*cur)
{
	if(cur==NULL)

		return;
	else
	{
		cout<<cur->item<<"\t";
		postorder(cur->left);
		postorder(cur->right);
	}
}
void btree::removeitem(int item)
{
	remove(root,item);
}
void btree::remove(tnode*&ptr,int item)
{
	if(ptr==NULL)
		cout<<"not node to delete "<<endl;
	else if(item==ptr->item)
			removnode(ptr);
		else if(item<ptr->item)
			remove(ptr->left,item);
		else
			remove(ptr->right,item);
}
void btree::removnode(tnode*&ptr)
{
	tnode*temp;
	int item;
	if(ptr->left==NULL&&ptr->right==NULL)
	{
		delete ptr;
		ptr=NULL;
	}
	else
		if(ptr->left==NULL)
		{
			temp=ptr;
			ptr=ptr->right;
			temp->right=NULL;
			delete temp;
		}
		else
		if(ptr->right==NULL)
		{
			temp=ptr;
			ptr=ptr->left;
			temp->left=NULL;
			delete temp;
		}
		else
		{
          processleftmost(ptr->right,item);
		  ptr->item=item;
		}
}
void btree::processleftmost(tnode*&ptr,int&item)
{
	if(ptr->left==NULL)
	{
		item=ptr->item;
		tnode*temp=ptr;
		ptr=ptr->right;
		temp->right=NULL;
		delete temp;
	}
	else
		processleftmost(ptr->left,item);
}
void btree::searchitem(int item)
{
	search(root,item);
}
void btree::search(tnode*ptr,int item)
{
	if(ptr==NULL)
	{
		cout<<"item not found"<<endl;
		return;
	}
	  if(item==ptr->item)
			cout<<"item found"<<endl;
		else
			if(item<ptr->item)
            search(ptr->left,item);
			else
				search(ptr->right,item);
}

struct dnode
{
	int item;
	dnode *next, *prev;
	dnode(int item)
	{
		this -> item = item;
		this -> next = NULL;
		this -> prev = NULL;
	}
	dnode()
	{
		this -> item = 0;
		this -> next = NULL;
		this -> prev = NULL;
	}
};
class queue
{
	dnode *front;
	dnode *back;
	int size;
	public:
		queue()
		{
			front = NULL;
			back = NULL;
			size = 0;
		};
		~queue()
		{
			front = NULL;
			back = NULL;
		}
		void display();
		void redisplay();
		void dequeue();
		dnode *find(int);
		void enqueue(int);
		bool isempty()
		{
			return front == NULL;
		};
		void sort();
		void sortn();
		dnode *gettop()
		{
			return front;
		};
};
dnode *queue::find(int index)
{
	if(index < 1 || index > size)
	{
		return NULL;
	}
	else
	{
		dnode *curr = front;
		for(int i = 1; i < index; i++)
		{
			curr = curr -> next;
		}
		return curr;
	}
}
void queue::dequeue()
{
	if(front == NULL)
	{
		return;
	}
	else
	{
		dnode *temp = front;
		front = front -> next;
		if(front == NULL)
		{
			back = NULL;
		}
		else
		{
			front -> prev = NULL;
		}
		size--;
		free(temp);
	}
}
void queue::enqueue(int item)
{
	size++;
	dnode *temp = new dnode(item);
	if(back != NULL)
	{
		back -> next = temp;
		temp -> prev = back;

	}
	back = temp;
	if(front == NULL)
	{
		front = temp;
		front -> next = back;
	}
}
void queue::display()
{
	dnode *curr = front;
	while(curr != NULL)
	{
		cout << curr -> item << ' ';
		curr = curr -> next;
	}
}
void queue::redisplay()
{
	dnode *curr = front;
	while(curr != NULL)
	{
		cout << curr -> item << ' ';
		curr = curr -> next;
	}
}
void queue::sort()
{
	dnode *befor;
	dnode *cur;
	for(int d = 1; d < size; d++)
	{
		for(int j = 1; j < size; j++)
		{
			befor = find(j);
			cur = find(j + 1);
			if(befor -> item > cur -> item)
			{
				int temp;
				temp = cur -> item;
				cur -> item = befor -> item;
				befor -> item = temp;
			}
		}
	}
}
void queue::sortn()
{
	dnode *before;
	dnode *second;
	dnode *first;
	for(int d = 1; d <= size; d++)
	{
		for(int j = 1; j <= size - d; j++)
		{
			first = find(j);
			before = find(j-1);
			second = find(j+1);
			if(first -> item > second -> item)
			{
			first -> next = second -> next;
			if(before == NULL)
				front = second;
			else
				before -> next = second;
			second -> next = first;
			}

			
		}
	}
}

class stack
{
	dnode *top;
	int size;
	public:
		stack()
		{
			top = NULL;
			size = 0;
		};
		~stack()
		{
			top = NULL;
			size = 0;
		}
		dnode *find(int);
		void push(int);
		void pop();
		void display();
		void redisplay();
		bool isempty()
		{
			return top == NULL;
		};
		void sort();
		void sortn();
		dnode *gettop()
		{
			return top;
		}
};
dnode *stack::find(int index)
{
	if(index < 1 || index > size)
	{
		return NULL;
	}
	else
	{
		dnode *curr = top;
		for(int i = 1; i < index; i++)
		{
			curr = curr -> prev;
		}
		return curr;
	}
}
void stack::push(int data)
{
	size++;
	dnode *temp = new dnode(data);
	if(top == NULL)
	{
		top = temp;
		return;
	}
	top -> next = temp;
	temp -> prev = top;
	top = temp;
}
void stack::pop()
{
	if(top == NULL)
	{
		return;
	}
	top = top -> prev;
	top -> next = NULL;
	size--;
}
void stack::display()
{
	dnode *curr = top;
	while(curr != NULL)
	{
		cout << curr -> item << ' ';
		curr = curr -> prev;
	}
}
void stack::sort()
{
	dnode *befor;
	dnode *cur;
	for(int d = 1; d < size; d++)
	{
		for(int j = 1;j < size; j++)
		{
			befor = find(j);
			cur = find(j + 1);
			if(befor -> item > cur -> item)
			{
				int temp;
				temp = cur -> item;
				cur -> item = befor -> item;
				befor -> item= temp;
			}
		}
	}
}
void stack::sortn()
{
	dnode *before;
	dnode *second;
	dnode *first;
	for(int d = 1; d <= size; d++)
	{
		for(int j = 1;j <= size - d; j++)
		{
			first = find(j);
			before = find( j - 1);
			second = find(j + 1);
			if(first -> item > second -> item)
			{
			first -> prev = second -> prev;
			if(before == NULL)
				top=second;
			else
				before -> prev = second;
			second -> prev= first;
			}

			
		}
	}
}

class dlist
{
	dnode *front;
	dnode *back;
	int size;
	public:
		dlist()
		{
			front = NULL;
			size = 0;
			back = NULL;
		}
		void sort();
		void sortn();
		void insert(int, int);
		void remove(int index);
		dnode *find(int);
		int getsize()
		{
			return size;
		}
		void displayForward();
		void displayBackward();
		void redisplayforward(dnode*);
		void redsiplaybackward(dnode*);
		dnode *getFront()
		{
			return front;
		}
		dnode *getback()
		{
			return back;
		}
		bool isempty()
		{
			return front == NULL;
		}
};
dnode *dlist::find(int index)
{
	if(index < 1 || index > size)
	{
		return NULL;
	}
	else
	{
		dnode *curr = front;
		for(int i = 1; i < index; i++)
		{
			curr = curr -> next;
		}
		return curr;
	}
}
void dlist::displayForward()
{
	dnode *curr = front;
	while(curr != NULL)
	{
		cout << curr -> item << ' ';
		curr = curr -> next;
	}
	cout << endl;
}
void dlist::displayBackward()
{
	dnode *curr = back;
	while(curr != NULL)
	{
		cout << curr -> item << ' ';
		curr = curr -> prev;
	}
	cout << endl;
}
void dlist::sort()
{
	dnode *befor;
	dnode *cur;
	for(int d = 1; d < size; d++)
	{
		for(int j = 1; j < size; j++)
		{
			befor = find(j);
			cur = find(j + 1);
			if(befor -> item > cur -> item)
			{
				int temp;
				temp = cur -> item;
				cur -> item = befor -> item;
				befor -> item = temp;
			}
		}
	}
}
void dlist::sortn()
{
	dnode *before;
	dnode *second;
	dnode *first;
	for(int d = 1; d <= size; d++)
	{
		for(int j = 1; j <= size - d; j++)
		{
			first = find(j);
			before = find(j-1);
			second = find(j+1);
			if(first -> item > second -> item)
			{
			first -> next = second -> next;
			if(before == NULL)
				front = second;
			else
				before -> next = second;
			second -> next = first;
			}

			
		}
	}
}
void dlist::redisplayforward(dnode *node)
{
	dnode *curr = node;
	while(curr != NULL)
	{
		cout << curr -> item << ' ';
		curr = curr -> next;
	}
	cout << endl;
}
void dlist::redsiplaybackward(dnode *node)
{
	dnode *curr = node;
	while(curr != NULL)
	{
		cout << curr -> item << ' ';
		curr = curr -> prev;
	}
	cout << endl;
}
void dlist::insert(int index, int value)
{
	dnode *temp = new dnode(value);
	if(index > size)
	{
		size++;
		if(back != NULL)
		{
			back -> next = temp;
			temp -> prev = back;

		}
		back = temp;
		if(front == NULL)
		{
			front = temp;
			front -> next = back;
		}
		return;
	}
	size++;
	dnode *curr = find(index);
	temp -> next = curr;
	temp -> prev = curr -> prev;
	curr -> prev -> next = temp;
	curr -> prev = temp;

}
void dlist::remove(int index)
{
	if(index < 1 || index > size)
	{
		cout << "out of range" << endl;
		return;
	}
	size--;
	dnode *temp = find(index);
	if(index == 1)
	{
		front = front -> next;
		front -> prev = NULL;
		return;
	}
	temp -> prev -> next = temp -> next;
	temp -> next -> prev = temp -> prev;
}

int main()
{
	stack test;
	test.push(134324);
	test.push(13431);
	test.push(1);
	test.push(1234);
	test.push(1344);
	test.push(19);
	test.sortn();
	test.pop();
	test.display();
	
	cout << endl;

	queue test1;
	test1.enqueue(512);
	test1.enqueue(5242);
	test1.enqueue(522);
	test1.enqueue(5142);
	test1.enqueue(511);
	test1.enqueue(5972);
	test1.dequeue();
	test1.sort();
	test1.display();

	cout << endl;

	dlist test3;
	test3.insert(1, 320);
	test3.insert(2, 340);
	test3.insert(2, 540);
	test3.insert(2, 580);
	test3.insert(4, 570);
	test3.insert(6, 510);
	test3.remove(2);

	test3.displayForward();

	cout << endl;

	btree test4;

	test4.insertitem(4);
	test4.insertitem(234);
	test4.insertitem(44);
	test4.insertitem(442);

	cout << test4.getroot() -> item;

	return 0;
}