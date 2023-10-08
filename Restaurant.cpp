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
				customer *temp = this->current->next;
				while (temp != this->current) {
					customer *temp2 = temp;
					temp = temp->next;
					delete temp2;
				}
				delete this->current;
				count = 0;
				current = NULL;
			}
			if (this->order != NULL) {
				customer *temp = this->order->next;
				while (temp != this->order) {
					customer *temp2 = temp;
					temp = temp->next;
					delete temp2;
				}
				delete this->order;
				this->order = NULL;
			}
			if (this->queue != NULL) {
				customer *temp = this->queue->next;
				while (temp != this->queue) {
					customer *temp2 = temp;
					temp = temp->next;
					delete temp2;
				}
				delete this->queue;
				countQueue = 0;
				this->queue = NULL;
			} 
		};
		void addCusRight(customer* cus) {
			cus->next = this->current->next;
			cus->prev = this->current;
			this->current->next->prev = cus;
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

		void deleteCus(string name) {

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
			
			

			customer *cus = new customer (name, energy, cus, cus);
			if (this->count == 0) {
				this->current = cus;
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
				} else {
					addCusLeft(cus);
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
				} else addCusRight(cus);

			}
			
			
			
			

	
		}
		void BLUE(int num) {
			cout << "blue " << num << endl;

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