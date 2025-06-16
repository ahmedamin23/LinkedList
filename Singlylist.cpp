#include <iostream>
using namespace std;

struct Node
{
	int data{};
	Node *next{};
	Node(int data) : data(data) {}
};
class LinkedList
{
private:
	Node *head{};
	Node *tail{};
	int length = 0;

public:
	void get_length()
	{
		cout << "lengthsfh:" << length << endl;
	}
	void get_head()
	{
		if (!head)
			cout << "head:ifts nullptr " << endl;
		else
			cout << "head:" << head->data << endl;
	}
	void get_tail()
	{
		if (!tail)
			cout << "ta:its nullptr " << endl;
		else
			cout << "tail:" << tail->data << endl;
	}
	void insert_end(int val)
	{
		if (!head)
		{
			head = new Node(val);
			tail = head;
		}
		else
		{
			tail->next = new Node(val);
			tail = tail->next;
		}
		length++;
	}
	void insert_front(int val)
	{
		if (!head)
		{
			head = new Node(val);
			tail = head;
		}
		else
		{
			Node *new_one = new Node(val);
			new_one->next = head;
			head = new_one;
		}
		length++;
	}
	void Delete_front()
	{
		if (!head)
			return;
		else
		{
			if (!head->next)
			{
				delete head;
				head = tail = nullptr;
			}
			else
			{
				Node *cur = head;
				head = head->next;
				delete cur;
			}
		}
		length--;
	}
	void Print_Nodes()
	{
		for (Node *trav = head; trav; trav = trav->next)
			cout << trav->data << " ";
		cout << endl;
	}
	Node *get_nth_node(int n)
	{
		int cnt = 0;
		for (Node *trav = head; trav; trav = trav->next)
			if (++cnt == n)
				return trav;
		return nullptr;
	}
	Node *get_nth_node_from_back(int n)
	{
		int cnt = length - n;

		int inner_cnt = 0;
		for (Node *trav = head; trav; trav = trav->next, inner_cnt++)
			if (inner_cnt == cnt)
				return trav;

		return nullptr;
	}
	bool is_same(LinkedList &list2)
	{
		cout << "its List2 address:" << &list2 << endl;
		if (!head && !list2.head)
			return true;
		if ((head && !list2.head) || (!head && list2.head))
			return false;
		else
		{
			Node *trav = head;
			Node *trav2 = list2.head;
			for (; (trav && trav2); trav = trav->next, trav2 = trav2->next)
				if ((trav && !trav2) || (!trav && trav2) || (trav->data != trav2->data))
					return false;
		}
		return true;
	}
	void Delete_with_key(int val)
	{
		if (!head)
			return;
		Node *prev = nullptr;
		for (Node *curr = head; curr; prev = curr, curr = curr->next)
		{
			if (curr->data == val)
			{

				if (!head->next)
					head = tail = nullptr;
				else if (head->data == curr->data)
					head = head->next;
				else if (curr->next)
					prev->next = curr->next;
				else
				{
					prev->next = curr->next;
					tail = prev;
				}
				delete curr;
				length--;
				return;
			}
		}
		return;
	}
	void Swap_pairs()
	{
		if (!head)
			return;
		Node *prev = head;
		for (Node *curr = prev->next; (prev && curr);
			 curr = prev->next)
		{
			int temp = prev->data;
			prev->data = curr->data;
			curr->data = temp;
			prev = curr->next;
			if (!prev)
				return;
		}
	}

	void reverse(Node *prev, Node *curr)
	{
		if (!curr)
			return;
		reverse(curr, curr->next);
		curr->next = prev;
		if (curr == head)
		{
			Node *temp = head;
			head = tail;
			tail = temp;
		}
	}
	Node *get_my_head()
	{
		return head;
	}
	void for_reverserd()
	{
		if (!head)
			return;
		Node *p0 = nullptr;
		Node *p1 = head;
		Node *p2 = head;
		for (;;)
		{
			p2 = p2->next;
			p1->next = p0;
			p0 = p1;
			p1 = p2;
			if (!p1)
				break;
		}
		Node *temp = head;
		head = tail;
		tail = temp;
	}
	void delete_even_positon()
	{
		if (!head)
			return;
		Node *p0 = nullptr;
		Node *p1 = head;
		int cnt = 1;

		while (p1)
		{
			p0 = p1;
			p1 = p1->next;
			cnt++;
			if (cnt % 2 == 0 && p1)
			{
				p0->next = p1->next;
				delete p1;
				p1 = p0->next;
				cnt++;
				if (!p1)
					tail = p0;
			}
		}
	}
	void delete_even_positon_most_saad()
	{
		if (!head)
			return;
		Node *prev = head;
		for (Node *curr = head->next; curr && prev;prev = prev->next,curr = prev->next)
		{
			prev->next = curr->next;
			delete curr;
			if (!prev->next)
			{
				tail = prev;
				break;
			}
		}
	}
	void sorted_insert(int val)
	{
		Node *new_one = new Node(val);
		if (!head)
		{
			head = new_one;
			return;
		}
		else
		{
			for (Node *p = head; p; p = p->next)
			{
				if (val <= p->data && p == head)
				{
					new_one->next = head;
					head = new_one;
					return;
				}
				else if (val >= p->data)
				{
					if (!p->next)
					{
						new_one->next = p->next;
						p->next = new_one;
						tail = new_one;
						return;
					}
					else
					{
						if (val <= p->next->data)
						{
							new_one->next = p->next;
							p->next = new_one;
							return;
						}
					}
				}
			}
		}
		length++;
	}
	~LinkedList()
	{
		Node *cur = nullptr;
		for (; head; cur = head, head = head->next)
			if (cur)
				delete cur;
		if (cur)
			delete cur;
		cout << "delete sucessfuly " << endl;
	}
};
int main()
{
	LinkedList l1;

	l1.sorted_insert(6);
	l1.sorted_insert(10);
	l1.sorted_insert(15);
	l1.sorted_insert(12);
	l1.Print_Nodes();
}