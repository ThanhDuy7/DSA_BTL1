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
				while (current != NULL) {
					temp = current;
					current = current->next;
					delete temp;
					temp = order;
					order = order->next;
					delete temp;
				}
				count = 0;
			}
			
			if (this->queue != NULL) {
				customer *temp = this->queue;
				while (queue != NULL) {
					temp = queue;
					queue = queue ->next;
					delete temp;
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
			temp->next = this->order->next;
			temp->prev = this->order;
			this->order->next = temp;
			this->order = temp;
		}
		void addQueue(customer* cus) {
			if (this->countQueue == 0) {
				this->queue = cus;
				this->countQueue++;
				return;
			}
			cus->next = this->queue->next;
			cus->prev = this->queue;
			this->queue->next = cus;
			this->queue = cus;
			this->countQueue++;
		}

		void deleteCus(int num) {
			this->order = this->order->next;
			if (num == count) {
				for (int i = 0; i < count+1; i++) {
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
			this->order = this->order->prev;
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
				temp = this->current;
				while (largest != temp->name) {
					temp = temp->next;
				}
				if (energy - temp->energy < 0) {
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
			//deleteCus(num);
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
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