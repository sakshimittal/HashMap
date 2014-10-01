#include "iostream"
#include <math.h>
#include <vector>

using namespace std;

template <class T1, class T2> class List
{
	public:
		T1 key;
		T2 val;	
		List *next;

		List(T1 key, T2 val) {
			this->key = key;
			this->val = val;
			this->next = NULL;
		}

};

template <class T1, class T2> class HashMap
{
	private:
		vector<List<T1, T2>*> indices;
		
		int hashFunction(T1 key) {
			return floor(key/10); 
		}

		void insertAtIndex(int index, T1 key, T2 val) {
			
			if(indices.at(index) == NULL) {
				List<T1, T2> *node = new List<T1, T2>(key, val);
				indices[index] = node;
			}
			else {
				List<T1, T2> *pointer = indices[index];
				if(pointer->key == key) {
					pointer->val = val;
					return;
				}
				
				while(pointer->next != NULL) {
					pointer = pointer->next;
					
					if(pointer->key == key) {
						pointer->val = val;
						return;
					}
				}

				List<T1, T2> *node = new List<T1, T2>(key, val);
				pointer->next = node;
			}
		}

	public:
		
		void insert(T1 key, T2 val) {
			int index = hashFunction(key);

			if(indices.size() < index+1) {
				indices.resize(index+1, NULL);
			}
			
			insertAtIndex(index, key, val);
		}

		void display() {
			
			int flag = 0;
			
			if(indices.empty()) {
				cout << "Map is empty!"<<endl;
			}
			else {
				for(int i=0 ; i < indices.size() ; i++) {

					flag = 0;

					if(indices[i] != NULL) {
						
						flag = 1;
						cout << i << " --> ";

						List<T1, T2> *pointer = indices[i];

						while(pointer != NULL) {
							cout << "(" << pointer->key << "," << pointer->val << ") ";
							pointer = pointer->next;
						}

					}

					if(flag == 1)
						cout<<endl;
				}
			}
		}

		void remove(T1 key) {
			if(indices.empty()) {
				cout<<"Map is empty!"<<endl;
				return;
			} 

			int index = hashFunction(key);
			if(indices[index] == NULL) {
				cout<<"Key not present!";
				return;
			}	

			List<T1, T2> *pointer = indices[index];

			if(pointer->key == key) {
				indices[index] = pointer->next;
				return;
			}

			while(pointer->next != NULL) {
	
				if(pointer->next->key == key) {
					List<T1, T2> *temp = pointer->next;
					pointer->next = pointer->next->next;
					delete(temp);
					return;
				}

				pointer = pointer->next;
			}

			cout<<"Key not present";
		}
};


int main() {
	
	HashMap<int, char> *head = new HashMap<int, char>();
	head->display();

	head->insert(6,'a');
	head->insert(20,'b');
	head->insert(5,'c');
	head->insert(9,'d');
	cout<<endl;
	head->display();
	head->insert(5,'e');
	head->remove(9);
	cout<<endl;
	head->display();
	return 0;
}