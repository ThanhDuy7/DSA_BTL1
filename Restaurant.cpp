#include "main.h"

class imp_res : public Restaurant
{
	public:
	int count;
	int countQueue;
	customer* current;
	customer* queue;
	customer* order;
	public:	
		imp_res() : count(0), countQueue(0), current(NULL), queue(NULL), order(NULL) {};
		~imp_res() {
			
			if (this->current != NULL) {
				customer *temp = current;
				customer *temp2 = order;
				for (int i = 0; i <count; i++) {
					temp = current->next;
					temp2 = order->next;
					if (temp == current) {
						delete current;
						delete order;
						break;
					}
					delete current;
					delete order;
					current = temp;
					order = temp2;
				}
				
				count = 0;
			}
			
			if (this->queue != NULL) {
				customer *temp = this->queue;
				for (int i = 0; i < countQueue; i++) {
					temp = this->queue->next;
					if (temp == this->queue) {
						delete this->queue;
						break;
					}
					delete this->queue;
					this->queue = temp;
				}
				countQueue = 0;
			} 
			
		};
		void addCusRight(customer* cus) {
			cus->next = this->current->next;
			cus->prev = this->current;
			current->next->prev = cus;
			this->current->next = cus;
			this->current = cus;
			this->count++;
		}
		
		void addCusLeft(customer* cus) {
			cus->next = this->current;
			cus->prev = this->current->prev;
			this->current->prev->next = cus;
			this->current->prev = cus;
			this->current = cus;
			this->count++;
		}

		void addOrder(customer* cus) {
			customer* temp = new customer(cus->name, cus->energy, NULL, NULL);
			temp->next = temp;
			temp->prev = temp;
			if (this->count == 0) {
				this->order = temp;
				return;
			}
			order->prev->next = temp;
			temp->prev = order->prev;
			temp->next = order;
			order->prev = temp;
		}
		void addQueue(customer* cus) {
			if (this->countQueue == 0) {
				this->queue = cus;
				this->countQueue++;
				return;
			}
			queue->prev->next = cus;
			cus->prev = queue->prev;
			cus->next = queue;
			queue->prev = cus;
			this->countQueue++;
		}

		void deleteCus(int num) {
			if (num == count) {
				for (int i = 0; i < count; i++) {
					customer* temp1 = this->current;
					this->current = this->current->next;
					customer* temp2 = this->order;
					this->order = this->order->next;
					delete temp1;
					delete temp2;
				}
				count = 0;
				return;	
			}
			string name;
			
			for (int i = 0; i < num; i++) {
				customer* temp1 = this->current;
				customer* temp2 = this->order;
				name = temp2->name;
				
				while(temp1->name != name) {
					temp1 = temp1->next;
				}
				temp1->prev->next = temp1->next;
				temp1->next->prev = temp1->prev;
				
				temp2->prev->next = temp2->next;
				temp2->next->prev = temp2->prev;

				if (temp1->energy > 0 ) this->current = temp1->next;
				else this->current = temp1->prev;
				this->order = temp2->next;
				delete temp2;
				delete temp1;
				this->count--;
			}
		}
		
		void deleteQueue() {
			customer* temp = queue;
			queue->prev->next = temp->next;
			temp->next->prev = temp->prev;
			queue = temp->next;
			delete temp;
			countQueue--;
		}
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;

			//base case
			if (energy == 0 || countQueue == MAXSIZE) return;
			
			if (count != 0) 
			{
				customer *temp = this->current;
				for (int i = 0; i < count; i++) {
					if (temp->name == name) return;
					temp = temp->next;
				}
			}

			if (countQueue != 0) {
				customer *temp = this->queue;
				for (int i = 0; i < countQueue; i++) {
					if (temp->name == name) return;
					temp = temp->next;
				}
			}
			
			

			customer *cus = new customer (name, energy, NULL, NULL);
			cus->next = cus;
			cus->prev = cus;
			if (this->count == 0) {
				this->current = cus;
				addOrder(cus);
				this->count++;
				return;
			}
			if (this->count == MAXSIZE) {
				addQueue(cus);
				return;
			}
			if (this->count < MAXSIZE/2) 
			{
				if (cus->energy >=current->energy)
				{
					addCusRight(cus);
					addOrder(cus);
				} else {
					addCusLeft(cus);
					addOrder(cus);
				}
			} else {
				int RES = abs(energy - current->energy);
				string largest = current->name;
				customer* temp = this->current->next;
				while (temp != this->current) {
					if (abs(energy - temp->energy)  > RES) {
						RES = abs(energy - temp->energy);
						largest = temp->name;
					}
					temp = temp->next;
				}
				while (largest != temp->name) {
					temp = temp->next;
				}
				if ((energy - temp->energy) < 0) {
					addCusLeft(cus);
					addOrder(cus);
				} else {
					addCusRight(cus);
					addOrder(cus);
				}

			}
			
			
			
		
		}
		void BLUE(int num) {
			cout << "blue " << num << endl;
			if (this->count == 0) return;
			if (num >= count) {
				num = count;
			}
			for (int i = 0; i < count;i++) {
				cout<<current->name<<"1"<<endl;
				current = current->next;
			}
			
			deleteCus(num);
			for (int i = 0; i < count; i++) {
				cout<<current->name<<"3"<<endl;
				current = current->next;
			}
			if (countQueue > 0) {
				while (count < MAXSIZE && countQueue > 0) {
					string s = queue->name;
					int e = queue->energy;
					deleteQueue();
					RED(s, e);
				}
			}
			
			
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
			customer* temp = this->queue;
			customer* maxEnergy = temp;
			int index = 1;
			for (int i = 1; i < countQueue+1; i++) {
				if (abs(temp->energy) >= abs(maxEnergy->energy)) {
					maxEnergy = temp;
					index = i;
				}
				temp = temp->next;
			}
			cout<<maxEnergy->name<<index<<" "<<maxEnergy->energy<<endl;
			for (int i = 1; i < index; i+= index/2) {
				temp = temp->next;
			}

		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
		}
};