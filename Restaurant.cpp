#include "main.h"

class imp_res : public Restaurant
{
	public:
	int count;
	int countQueue;
	customer* current;
	public:	
		imp_res() {};
		imp_res() : count(0), countQueue(0), current(NULL) {};
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
		};
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;

			//base case
			if (count != 0) 
			{
				customer *temp = this->current;
				for (int i = 0; i < count; i++) {
					if (temp->name == name) return;
					temp = temp->next;
				}
			}
			
			if (energy == 0 || countQueue == MAXSIZE) return;

			customer *cus = new customer (name, energy, nullptr, nullptr);
			if (this->count < MAXSIZE/2) 
			{
				this->count++;
				if (this->count == 1) {
					this->current = cus;
					return;
				}

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