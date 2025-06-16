#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node *prev{};
	Node *next{};
	Node(int data) : data(data) {};
};
class DoublyList
{
private:
	Node *head{};
	Node *tail{};
	int length = 0;

public:
	void Link(Node *first, Node *second)
	{
		if (first)
			first->next = second;
		if (second)
			second->prev = first;
	}
	void insert_end(int val)
	{
		Node *my_node = new Node(val);
		if (!head)
			head = tail = my_node;
		else
		{
			Link(tail, my_node);
			tail = my_node;
		}
		length++;
	}
	void insert_front(int val)
	{
		Node *new_one = new Node(val);
		if (!head)
			head = tail = new_one;
		else
		{
			Link(new_one, head);
			head = new_one;
		}
		length++;
	}
	void Print_list()
	{
		if (!head)
			return;
		for (Node *trav = head; trav; trav = trav->next)
			cout << trav->data << " ";
		cout << endl;
	}
	void Print_address()
	{
		if (!head)
			return;
		for (Node *trav = head; trav; trav = trav->next)
			cout << trav << " ";
		cout << endl;
	}
	void Delete_front()
	{
		if (!head)
			return;
		else
		{
			Node *trav = head;
			head = head->next;
			if (head)
				head->prev = nullptr;
			if (!head)
				tail = head = nullptr;
			delete trav;
			length--;
		}
	}
	void Delete_End()
	{
		if (!head)
			return;
		else if (!head->next)
		{
			delete head;
			tail = head = nullptr;
		}
		else
		{
			for (Node *trav = head; trav; trav = trav->next)
			{
				if (trav == tail)
				{
					tail = tail->prev;
					delete tail->next;
					tail->next = nullptr;
					break;
				}
			}
		}
		length--;
	}
	Node *Link_and_Delete_utility(Node *my_node)
	{
		Node *ret = my_node->prev;
		Link(my_node->prev, my_node->next);
		delete my_node;
		length--;
		return ret;
	}
	void Delete_node_with_key(int key)
	{
		if (!head)
			return;
		else
		{
			for (Node *curr = head; curr; curr = curr->next)
			{
				if (curr->data == key)
				{
					if (curr == head)
						Delete_front();
					else if (curr == tail)
						Delete_End();
					else
						curr = Link_and_Delete_utility(curr);
				}
				break;
			}
		}
	}
	void Delete_all_nodes_with_key(int key)
	{
		if (!head)
			return;
		else
		{
			for (Node *curr = head; curr; curr = curr->next)
			{
				if (curr->data == key)
				{
					if (curr == head)
						Delete_front();
					else if (curr == tail)
						Delete_End();
					else
						curr = Link_and_Delete_utility(curr);
				}
			}
		}
	}
	void delete_all_nodes_with_key_most(int value)
	{
		if (!length)
			return;

		// insert dummy. assume -value no overflow

		for (Node *cur = head; cur;)
		{
			if (cur->data == value)
			{
				cur = Link_and_Delete_utility(cur);
				if (!cur->next)
					tail = cur;
			}
			else
				cur = cur->next;
		}
	}
	void Delete_even_positon()
	{
		if (!head || !head->next)
			return;
		for (Node *curr = head->next; curr; curr = curr->next)
		{
			curr = Link_and_Delete_utility(curr);
			curr = curr->next;
			if (!curr)
				break;
		}
	}
	void Delete_odd_positon()
	{
		insert_front(-3);
		Delete_even_positon();
		Delete_front();
	}
	bool is_palindrome()
	{
		if (!head || !head->next)
			return true;
		for (Node *p0 = head, *p1 = tail; p0 != p1 && p1->next != p0;
			 p0 = p0->next, p1 = p1->prev)
			if (p0->data != p1->data)
				return false;
		return true;
	}
	void find_middle()
	{
		if (!head || !head->next)
			return;
		Node *p0 = head, *p1 = tail;
		for (; p0 != p1 && p1->next != p0; p0 = p0->next, p1 = p1->prev)
			;
		if (p0 == p1)
			cout << "middle is " << p1->data << endl;
		else
			cout << "first &&second middle are "
				 << p1->data << " " << p0->data << endl;
	}
	void find_middle_hard()
	{
		if (!head || !head->next)
			return;
		Node *my_prev = nullptr, *my_curr = head, *my_trav = head;
		for (; my_trav && my_trav->next;
			 my_prev = my_curr, my_curr = my_curr->next, my_trav = my_trav->next->next)
			;
		if (!my_trav)
			cout << "middle is:" << my_prev->data << " && " << my_curr->data << endl;
		else
			cout << "middle is:" << my_curr->data << endl;
	}
	void get_length()
	{
		cout << "length is:" << length << endl;
	}
	Node *get_nth_front(int key)
	{
		if (!head)
			return nullptr;
		int cnt = 0;
		for (Node *trav = head; trav; trav = trav->next)
			if (++cnt == key)
				return trav;
		return nullptr;
	}
	Node *get_nth_back(int key)
	{
		if (!head)
			return nullptr;
		int cnt = 0;
		for (Node *trav = tail; trav; trav = trav->prev)
			if (++cnt == key)
				return trav;
		return nullptr;
	}
	void swap_forward_with_back(int key)
	{
		if (!head || !head->next)
			return;
		Node *my_p0 = get_nth_front(key);
		Node *my_p1 = get_nth_back(key);
		if (my_p0 == my_p1)
			return;
		if (!my_p0)
			return;
		if (my_p0->prev == my_p1)
			swap(my_p0, my_p1);
		Node *prev_p0 = my_p0->prev;
		Node *next_p0 = my_p0->next;
		Node *prev_p1 = my_p1->prev;
		Node *next_p1 = my_p1->next;
		if (my_p0->next == my_p1 || my_p0->prev == my_p1)
		{

			Link(my_p0, next_p1);
			Link(my_p1, my_p0);
			Link(prev_p0, my_p1);
		}
		else
		{
			Link(prev_p1, my_p0);
			Link(my_p0, next_p1);
			////////////////
			Link(prev_p0, my_p1);
			Link(my_p1, next_p0);
		}
		if (my_p1 == head || my_p1 == tail)
			swap(head, tail);
	}
	void Reverse_List()
	{
		if (!head || !head->next)
			return;
		for (Node *trav = head; trav; trav = trav->prev)
			swap(trav->prev, trav->next);
		swap(head, tail);
	}
	void merge_2sorted_lists(DoublyList &other)
	{
		if ((!head && !other.head) || (head && !other.head))
			return;
		if (!head && other.head)
		{
			head = other.head, tail = other.tail;
			return;
		}
		Node *prev1 = nullptr;
		Node *curr1 = head;
		Node *prev2 = nullptr;
		Node *curr2 = other.head;
		while (curr1 && curr2)
		{
			if (curr1->data <= curr2->data)
				prev1 = curr1, curr1 = curr1->next;
			else if (curr1->data > curr2->data)
			{
				prev2 = curr2, curr2 = curr2->next;
				Link(prev1, prev2), Link(prev2, curr1);
				if (curr1 == head)
					head = prev2;
				prev1 = prev2;
			}
		}
		if (curr2)
			prev1->next = curr2, tail = other.tail;
		other.head=other.tail=nullptr;	
		length+=other.length;
		other.length=0;
	}
	~DoublyList()
	{
		if (!head)
		{
			cout << "Destructor:No items Deleted " << endl;
			return;
		}
		for (Node *my_prev = head; my_prev; my_prev = head)
		{
			head = head->next;
			delete my_prev;
		}
		cout << "Destructor:Deleted successfully " << endl;
	}
};
int main()
{
	DoublyList l1;
	DoublyList l2;
	cout << boolalpha;
	l2.insert_end(1);
	l2.insert_end(2);
	l2.insert_end(3);
	l2.insert_end(4);
	l2.insert_end(5);
	l1.insert_end(10);
	l1.insert_end(20);
	l1.insert_end(30);
	l1.insert_end(40);
	l1.insert_end(50);
	l1.merge_2sorted_lists(l2);
	l1.Print_list();
}