#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;

struct s_list
{
	int data;
	s_list *next;
};

s_list * create_s_list(int data)
{
	s_list *head = new s_list;
	head->data = data;
	head->next = NULL;
	return head;
}

void s_add_node(int data, s_list *head)
{
	s_list *node = new s_list;
	node->data = data;
	node->next = NULL;
	s_list *temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = node;
}

void delete_s_list(s_list *&head, int &size)
{
	s_list *temp = head;
	s_list *current;
	while (temp->next != NULL)
	{
		current = temp;
		temp = temp->next;
		delete[]current;
	}
	delete[] temp;
}

void s_insert(s_list *&head, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	unsigned int id;
	int data;
	cout << "Enter the index (from 0 to " << size << ") of a new node:" << endl;
	cin >> id;
	cin.clear();
	if (id > size)
	{
		cout << "Invalid index! Please try again." << endl;
		s_insert(head, size);
	}
	else
	{
		if (id == size)
		{
			cout << "Enter the value of a new node:" << endl;
			cin.ignore();
			cin >> data;
			cin.clear();
			start = chrono::system_clock::now();
			s_add_node(data, head);
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << "The singly linked list was updated:" << endl;
			s_list *temp = head;
			size++;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << endl << "Inserting a new node took " << dur << " seconds." << endl;
		}
		else
		{
			cout << "Enter the value of a new node:" << endl;
			cin >> data;
			cin.clear();
			start = chrono::system_clock::now();
			if (id != 0)
			{
				s_list *node = new s_list;
				node->data = data;
				s_list *temp_p = head, *temp_n = head;
				for (int i = 0; i < (id - 1); i++)
					temp_p = temp_p->next;
				for (int i = 0; i < id; i++)
					temp_n = temp_n->next;
				node->next = temp_n;
				temp_p->next = node;
				end = chrono::system_clock::now();
				int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
				cout << endl << "The singly linked list was updated:" << endl;
				s_list *temp = head;
				size++;
				for (int i = 0; i < size; i++)
				{
					cout << temp->data << " ";
					temp = temp->next;
				}
				cout << endl << "Inserting a new node took " << dur << " seconds." << endl;
			}
			else
			{
				s_list *node = new s_list;
				node->data = head->data;
				node->next = head->next;
				head->data = data;
				head->next = node;
				end = chrono::system_clock::now();
				int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
				cout << "The singly linked list was updated:" << endl;
				s_list *temp = head;
				size++;
				for (int i = 0; i < size; i++)
				{
					cout << temp->data << " ";
					temp = temp->next;
				}
				cout << endl << "Inserting a new node took " << dur << " seconds." << endl;
			}
		}
	}
}

void s_del_by_id(s_list *&head, int &size, int id)
{
	if (id == (size - 1))
	{
		s_list *n_tail = head, *tail = head;
		for (int i = 0; i < id; i++)
			n_tail = n_tail->next;
		for (int i = 0; i < size; i++)
			tail = tail->next;
		n_tail->next = NULL;
		delete[]tail;
		cout << "The singly linked list was updated:" << endl;
		s_list *temp = head;
		size--;
		for (int i = 0; i < size; i++)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
	else
	{
		if (id != 0)
		{
			s_list *temp_c = head, *temp_p = head, *temp_n;
			for (int i = 0; i < id; i++)
				temp_c = temp_c->next;
			for (int i = 0; i < (id - 1); i++)
				temp_p = temp_p->next;
			temp_n = temp_c->next;
			temp_p->next = temp_n;
			delete[]temp_c;
			cout << "The singly linked list was updated:" << endl;
			s_list *temp = head;
			size--;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
		}
		else
		{
			s_list *n_head = head;
			n_head = n_head->next;
			delete[] head;
			cout << "The singly linked list was updated:" << endl;
			size--;
			head = n_head;
			s_list *temp = head;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
		}
	}

}

void s_del_by_value(s_list *&head, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	cout << "Enter the value of the node you want to delete:" << endl;
	cout << "Note: if there is more than one node wich such value only the last one will be deleted." << endl;
	int value;
	cin >> value;
	cin.clear();
	start = chrono::system_clock::now();
	int count = 0, id;
	s_list *temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->data == value)
		{
			count++;
			id = i;
		}
		temp = temp->next;
	}
	if (count == 0)
	{
		cout << "There is no such node! Please try again." << endl;
		s_del_by_value(head, size);
	}
	else
	{
		s_del_by_id(head, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Deleting a node took " << dur << " seconds." << endl;
	}
}

void s_get_by_id(s_list *&head, s_list *&element, int &size, int id)
{
	s_list *temp = head;
	for (int i = 0; i < id; i++)
		temp = temp->next;
	element = temp;
	element->data = temp->data;
}

void s_get(s_list *&head, int size, s_list *&element)
{
	int id;
	cout << "Enter the index (from 0 to " << (size - 1) << ") of the node you want to get:" << endl;
	cin >> id;
	cin.clear();
	if (id > (size - 1))
	{
		cout << "Invalid index! Please try again." << endl;
		s_get(head, size, element);
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		s_get_by_id(head, element, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "The address of this node: " << element;
		cout << endl << "The value of this node: " << (*element).data;
		cout << endl << "Getting a node from a singly linked list took " << dur << " seconds." << endl;
	}
}

void s_get_by_value(s_list *&head, s_list *&element, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	int id, value, count = 0;
	cout << "Enter the value of the node you want to get from the list:" << endl;
	cout << "Note: if there is more than one node with such value only the last one will be gotten." << endl;
	start = chrono::system_clock::now();
	cin >> value;
	cin.clear();
	s_list *temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->data == value)
		{
			count++;
			id = i;
		}
		temp = temp->next;
	}
	if (count == 0)
	{
		cout << "There is no such node in the list! Please try again." << endl;
		s_get_by_value(head, element, size);
	}
	else
	{
		s_get_by_id(head, element, size, id);
	}
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "The address of this node: " << element;
	cout << endl << "The value of this node: " << (*element).data;
	cout << endl << "Getting a node from a singly linked list took " << dur << " seconds." << endl;
}

void s_list_by_size(s_list *&head, int &size)
{
	cout << "Please enter the size of a linked list:" << endl;
	chrono::time_point<chrono::system_clock> start, end;
	cin >> size;
	if (size == 0)
	{
		cout << "Invalid size! Please try again." << endl;
		s_list_by_size(head, size);
	}
	else
	{
		srand(time(NULL));
		start = chrono::system_clock::now();
		int data;
		data = rand() % 100;
		head = create_s_list(data);
		for (int i = 1; i < size; i++)
		{
			data = rand() % 100;
			s_add_node(data, head);
		}
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "Your singly linked list of " << size << " randomised elements:" << endl;
		s_list *temp = head;
		for (int i = 0; i < size; i++)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl << "Creating your singly linked list took " << dur << " seconds." << endl;
	}
}

void s_list_from_file(s_list *&head, int &size)
{
	cout << "Enter your list of integers in slist.txt. Use arabic numerals." << endl;
	cout << "To start the reading of the list type in any number and press enter." << endl;
	int start;
	cin >> start;
	cin.clear();
	ifstream dataf("slist.txt");
	if (!dataf.is_open())
	{
		cout << "Error! Can't access the file!" << endl;
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		size = 1;
		int data;
		dataf >> data;
		head = create_s_list(data);
		while (!dataf.eof())
		{
			dataf >> data;
			s_add_node(data, head);
			size++;
		}
		dataf.close();
		if ((size - 1) == 0)
		{
			cout << "The file is empty! Please try again." << endl;
			dataf.close();
			s_list_from_file(head, size);
		}
		else
		{
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << "Your singly linked list:" << endl;
			s_list *temp = head;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << endl << "Reading your singly linked list took " << dur << " seconds." << endl;
		}
	}
}

void s_list_by_elements(s_list *&head, int &size)
{
	cout << "Please enter your list of integers, each of new line:" << endl;
	cout << "Make sure that the last element of your list is 0." << endl;
	chrono::time_point<chrono::system_clock> start, end;
	int value;
	size = 1;
	cin >> value;
	cin.clear();
	head = create_s_list(value);
	start = chrono::system_clock::now();
	while (value != 0)
	{
		cin >> value;
		cin.clear();
		s_add_node(value, head);
		size++;
	}
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "Your singly linked list of " << size << " elements:" << endl;
	s_list *temp = head;
	for (int i = 0; i < size; i++)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl << "Creating your singly linked list took " << dur << " seconds." << endl;
}