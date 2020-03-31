#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;

//scrapped bc it cant be implemented into the menu rip :^)

void a_insert(int *&arr, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	int n_size;
	n_size = size + 1;
	int *n_arr = new int[n_size];
	int id, value;
	cout << "Enter the index (from 0 to " << size << ") of a new element:" << endl;
	cin >> id;
	cin.clear();
	if (id > size)
	{
		cout << "Invalid index! Please try again." << endl;
		a_insert(arr, size);
	}
	else
	{
		cout << "Enter the value of a new element:" << endl;
		cin >> value;
		cin.clear();
		start = chrono::system_clock::now();
		if (id != 0)
		{
			for (int i = 0; i < id; i++)
				n_arr[i] = arr[i];
			n_arr[id] = value;
			for (int i = (id + 1); i < n_size; i++)
				n_arr[i] = arr[i - 1];
		}
		else
		{
			n_arr[id] = value;
			for (int i = 1; i < n_size; i++)
				n_arr[i] = arr[i - 1];
		}
		delete[] arr;
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "The array was updated:" << endl;
		for (int i = 0; i < n_size; i++)
			cout << n_arr[i] << " ";
		cout << endl << "Inserting a new element took " << dur << " seconds." << endl;
	}
}

void a_del_by_id(int *&arr, int &size, int id)
{
	int n_size;
	n_size = size - 1;
	int *n_arr = new int[n_size];
	if (id != 0)
	{
		for (int i = 0; i < id; i++)
			n_arr[i] = arr[i];
		for (int i = id; i < n_size; i++)
			n_arr[i] = arr[i + 1];
	}
	else
	{
		for (int i = 0; i < n_size; i++)
			n_arr[i] = arr[i + 1];
	}
	delete[] arr;
	cout << "The array was updated:" << endl;
	for (int i = 0; i < n_size; i++)
		cout << n_arr[i] << " ";
}

void a_del_by_value(int *&arr, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	cout << "Enter the value of the element you want to delete:" << endl;
	int value;
	cin >> value;
	cin.clear();
	int n_size;
	n_size = size - 1;
	int *n_arr = new int[n_size];
	int count = 0, id;
	start = chrono::system_clock::now();
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			id = i;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "There is no such element! Please try again." << endl;
		a_del_by_value(arr, size);
	}
	else
	{
		a_del_by_id(arr, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Deleting an element took " << dur << " seconds." << endl;
	}
}

void a_get_by_id(int *&arr, int &size, int id)
{
	int *element = &(arr[id]);
}

void a_get_by_value(int *&arr, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	int id, value, count =0;
	cout << endl << "Enter the value of the element you want to get from the array:" << endl;
	start = chrono::system_clock::now();
	cin >> value;
	cin.clear();
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			id = i;
			count++;
		}
	}
	if (count == 0)

	{
		cout << "There is no such element in the array! Please try again." << endl;
		a_get_by_value(arr, size);
	}
	else
	{
		a_get_by_id(arr, size, id);
	}
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "Getting your element from the array took " << dur << " seconds." << endl;
}

void array_by_size()
{
	chrono::time_point<chrono::system_clock> start, end;
	int size;
	cout << "Please enter the size of an array:" << endl;
	cin >> size;
	if (size==0)
	{
		cout << "Invalid size! Please try again." << endl;
		array_by_size();
	}
	else
	{
		srand(time(NULL));
		start = chrono::system_clock::now();
		int *arr = new int[size];
		start = chrono::system_clock::now();
		cout << "Your array of " << size << " randomised elements:" << endl;
		for (int i = 0; i < size; i++)
		{
			arr[i] = rand() % 100;
			cout << arr[i] << " ";
		}
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Creating your array took " << dur << " seconds." << endl;
	}
	//delete [] arr;
}

void array_from_file()
{
	cout << "Enter your array of integers in array.txt. Use arabic numerals." << endl;
	cout << "To start the reading of the array type in any number and press enter." << endl;
	int start;
	cin >> start;
	cin.clear();
	ifstream data("array.txt");
	if (!data.is_open())
		cout << "Error! Can't acces the file." << endl;
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		int temp, size = 0;
		while (!data.eof())
		{
			data >> temp;
			size++;
		}
		if (size == 0)
		{
			cout << "The file is empty! Please try again." << endl;
			data.close();
			array_from_file();
		}
		else
		{
			cout << "Your array of "<<  size << " elements:" << endl;
			int *arr = new int[size];
			data.seekg(0, data.beg);
			for (int i = 0; i < size; i++)
				data >> arr[i];
			data.close();
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			for (int i = 0; i < size; i++)
				cout << arr[i] << " ";
			cout << endl << "Reading your array took " << dur << " seconds." << endl;
			//delete [] arr;
		}
	}
}

