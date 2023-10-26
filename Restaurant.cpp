#include "main.h"

class imp_res : public Restaurant
{
	public:
	int count;
	int countOrder;
	int countQueue;
	customer* current;
	customer* queue;
	customer* order;
	public:	
		imp_res() : count(0), countOrder(0), countQueue(0), current(NULL), queue(NULL), order(NULL) {};
		~imp_res() {
			if (this->current != NULL) {
				customer *temp = current;
				customer *temp2 = order;
				for (int i = 0; i <count; i++) {
					temp = current->next;
					if (temp == current) {
						delete current;
						break;
					}
					delete current;
					current = temp;
				}
				
				for (int i = 0; i < countOrder; i++) {
					temp2 = order->next;
					if (temp2 == order) {
						delete order;
						break;
					}
					delete order;
					order = temp2;
				}
				countOrder = 0;
				
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
			if (countOrder != 0) {
				customer* temp = order;
				for (int i = 0; i < countOrder; i++) {
					if (temp->name == cus->name) {
						return;
					}
					temp = temp->next;
				}
			}
			customer* temp = new customer(cus->name, cus->energy, NULL, NULL);
			temp->next = temp;
			temp->prev = temp;
			if (this->count == 0) {
				this->order = temp;
				countOrder++;
				return;
			}
			order->prev->next = temp;
			temp->prev = order->prev;
			temp->next = order;
			order->prev = temp;
			countOrder++;
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
		void deleteOrder(string name) {
			customer* temp = order;
			while (temp->name != name) {
				temp = temp->next;
			}
			if (temp == order) {
				order = temp->next;
			}
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			
			delete temp;
			countOrder--;
			return;
			
		}
		void deleteCus(int num) {
			if (num == count) {
				for (int i = 0; i < count; i++) {
					customer* temp1 = current;
					current = current->next;
					deleteOrder(temp1->name);
					delete temp1;
				}
				count = 0;
				return;	
			}
			string name;
			
			for (int i = 0; i < num; i++) {
				customer* temp1 = current;
				customer* temp2 = order;
				
				for (int j = 0; j < countOrder; j++) {
					name = temp2->name;
					int flag = 0;
					for (int g = 0; g < count; g++) {
						if (temp1->name == name) {
							flag = 1;
							break;
						}
						temp1 = temp1->next;
					}
					if (flag == 1) break;
					temp2 = temp2->next;
				}
				
				temp1->prev->next = temp1->next;
				temp1->next->prev = temp1->prev;
				
				temp2->prev->next = temp2->next;
				temp2->next->prev = temp2->prev;

				if (temp1->energy > 0 ) current = temp1->next;
				else current = temp1->prev;
				if (temp2 == order) order = temp2->next;
				delete temp2;
				delete temp1;
				count--;
				countOrder--;
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
		
		void deleteDomain(int flag, string name) {
			customer* temp = current;
			for (int i = 0; i < count; i++) {
				if (temp->name == name) {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					if (temp->next != temp)	{
						if (flag == 1) current = temp->next;
						else current = temp->prev;
					}
						delete temp;
						count--;
						return;
					
				}
				temp = temp->next;
			}	
		}
		
		void addFromQueue () {
			if (countQueue > 0) {
				
				while (count < MAXSIZE && countQueue > 0) {
					string s = queue->name;
					int e = queue->energy;
					
					deleteQueue();
					RED(s, e);
				}
			}
		}
		void RED(string name, int energy)
		{
			//base case
			//cout<<"red"<<" "<<name<<" "<<energy<<endl;
			if (energy == 0 || countQueue == MAXSIZE) return;
			
			if (count != 0) 
			{
				customer *temp = current;
				for (int i = 0; i < count; i++) {
					if (temp->name == name) return;
					temp = temp->next;
				}
			}
			if (countQueue != 0) {
				customer *temp = queue;
				for (int i = 0; i < countQueue; i++) {
					if (temp->name == name) return;
					temp = temp->next;
				}
			}

			customer *cus = new customer (name, energy, NULL, NULL);
			cus->next = cus;
			cus->prev = cus;
			if (count == 0) {
				current = cus;
				addOrder(cus);
				count++;
				return;
			}
			if (count == MAXSIZE) {
				addQueue(cus);
				addOrder(cus);
				return;
			}
			if (count < MAXSIZE/2) 
			{
				if (cus->energy >= current->energy)
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
				customer* temp = current->next;
				while (temp != current) {
					if (abs(energy - temp->energy)  > RES) {
						RES = abs(energy - temp->energy);
						largest = temp->name;
					}
					temp = temp->next;
				}
				while (largest != current->name) {
					current = current->next;
				}
				if ((energy - current->energy) < 0) {
					addCusLeft(cus);
					addOrder(cus);
				} else {
					addCusRight(cus);
					addOrder(cus);
				}
				
			}
		}
		void BLUE(int num) {
			//cout<<"blue"<<" "<<num<<endl;
			if (num == 0) return;
			if (this->count == 0) return;
			if (num >= count) {
				num = count;
			}
			deleteCus(num);
			addFromQueue();
		}

	void swap(customer *&temp2, customer* &temp1,int &swp) {
		swp++;
		//cout<<"swap"<<temp2->name<<" "<<temp1->name<<" "<<swp<<endl;
		string name = temp1->name;
		int energy = temp1->energy;
		temp1->name = temp2->name;
		temp1->energy = temp2->energy;
		temp2->name = name;
		temp2->energy = energy;
	}
void insort(customer *temp,int n, int incre, int & swp) {
	customer* temp2 = temp;
	customer* temp1 = temp;
	for (int i = incre; i < n; i+=incre) {
		for (int j = i; j>=incre; j-=incre) {
			temp2 = temp;
			for (int a = 0; a < j; a++) {
				temp2 = temp2->next;
			}
			temp1 = temp2;
			for (int a = 0; a < incre ;a++) {
				temp1 = temp1->prev;
			}
			if (abs(temp2->energy) > abs(temp1->energy)) {
				swap(temp2, temp1,swp);
			} else if (abs(temp2->energy) == abs(temp1->energy)) {
				customer* run = order;
				for (int i = 0; i < countOrder; i++) {
					if (run->name == temp2->name) {
						swap(temp2, temp1,swp);
						break;
					} else if (run->name == temp1->name) {
						break;
					} else {
						run = run->next;
					}
				}
			}
		}
	}
}
		void PURPLE()
		{
			//cout<<"purple"<<endl;
			if (countQueue <= 1 ) return;
			customer* temp = queue;
			customer* maxEnergy = temp;
			int swap = 0;
			int index = 1;
			for (int i = 1; i < countQueue+1; i++) {
				if (abs(temp->energy) >= abs(maxEnergy->energy)) {
					maxEnergy = temp;
					index = i;
				}
				temp = temp->next;
			}
			
			for (int gap = index/2; gap > 2; gap /= 2) {

				customer* jump = queue;
				for (int j = 0; j < gap; j++, jump = jump->next) {
					insort(jump,index - j, gap,swap);
				}
				
			}
			insort(queue, index, 1,swap);
			BLUE(swap%MAXSIZE);
			
		}
		void REVERSAL()
		{
			//cout<<"reversal"<<endl;
			if (count <= 1) {
				return;
			}
			
			string s = current->name;
			customer* temp1 = current;
			customer* temp2 = current->next;
			while (true) {
				int swp = 0;
				if (temp1->energy < 0) {
					if (temp2->energy < 0) {
						if (temp1 == temp2) break;
						swap(temp1, temp2,swp);
						temp1 = temp1->prev;
						if (temp2->next == temp1 || temp1 == temp2) {
							break;
						}
					}
					if (temp1 == temp2) {
						break;
					}
					temp2 = temp2->next;
				} else temp1 = temp1->prev;
				if (temp1 == temp2) break;
			}
			temp1 = current;
			temp2 = current->next;
			while (true) {
				int swp = 0;
				if (temp1->energy > 0) {
					if (temp2->energy > 0) {
						if (temp1 == temp2) break;
						swap(temp1, temp2,swp);
						temp1 = temp1->prev;
						if (temp2->next == temp1 || temp1 == temp2) {
							break;
						}
					}
					if (temp1 == temp2) {
						break;
					}
					temp2 = temp2->next;
				} else temp1 = temp1->prev;
				if (temp1 == temp2) break;
			}
			while (current->name != s) {
				current = current->next;
			}
		}
		void UNLIMITED_VOID()
		{
			//cout<<"unlimited void"<<endl;
			if (count < 4) return;
			customer* temp = current;
			if (count == 4) {
				customer* maxList = current;
				for (int i = 0; i < count-1; i++) {
					maxList = maxList->next;
				}
				customer* temp1 = maxList;
				customer* smallest = maxList;
				int minIndex = 0;
				int minEnergy = maxList->energy;
				for (int i = 0; i < 4; i++) {
					if (temp1->energy < minEnergy) {
						minEnergy = temp1->energy;
						smallest = temp1;
						minIndex = i;
					}
					temp1 = temp1->next;
				}
				for (int i = minIndex; i < 4;i++) {
					smallest->print();
					smallest = smallest->next;
				}
				for (int i = 0; i < minIndex; i++) {
					maxList->print();
					maxList = maxList->next;
				}
				return;
			}


			int minSum = 0;
			int maxLength = 4;
			customer* maxList = current;
			for (int i = 0; i < maxLength; i++) {
				minSum += temp->energy;
				temp = temp->next;
			}
			
			for (int i = 0; i < count; i++) {
				int sum = 0;
				int length = 0;
				temp = current;
				for (int j =0; j < 4; j++) {
					sum += temp->energy;
					length++;
					temp = temp->next;
				}
				if (sum == minSum) {
					if (length >= maxLength) {
						maxLength = length;
						maxList = current;
					}
				} else if (sum < minSum) {
					minSum = sum;
					maxLength = length;
					maxList = current;
				}
				for (int j = 0; j < count - 4; j++) {
					sum += temp->energy;
					length++;
					if (sum == minSum) {
						if (length >= maxLength) {
							maxLength = length;
							maxList = current;
						}
					} else if (sum < minSum) {
						minSum = sum;
						maxLength = length;
						maxList = current;
					}
					temp = temp->next;
				}
				current = current->next;
			}
			customer* temp1 = maxList;
			customer* smallest = maxList;
			int minIndex = 0;
			int minEnergy = maxList->energy;
			for (int i = 0; i < maxLength; i++) {
				if (temp1->energy < minEnergy) {
					minEnergy = temp1->energy;
					smallest = temp1;
					minIndex = i;
				}
				temp1 = temp1->next;
			}
			for (int i = minIndex; i < maxLength;i++) {
				smallest->print();
				smallest = smallest->next;
			}
			for (int i = 0; i < minIndex; i++) {
				maxList->print();
				maxList = maxList->next;
			}
		}
		void DOMAIN_EXPANSION()
		{
			//cout<<"domain expansion"<<endl;
			if (count == 0) return;
			int positiveGuest = 0;
			int negativeGuest = 0;
			customer* temp1 = order;
			customer* temp2 = queue;
			for (int i = 0; i < countOrder; i++) {
				if (temp1->energy > 0) {
					positiveGuest+= temp1->energy;
				} else negativeGuest+= temp1->energy;
				temp1 = temp1->next;
			}
			if (positiveGuest < abs(negativeGuest)) {
				temp1 = order;
				temp2 = order;
				int a = countOrder;
				order = order->prev;
				for (int i = 0; i <countOrder; i++) {
					if (order->energy > 0) {
						order->print();
					}
					order = order->prev;
				}
				order = order->next;
				for (int i = 0; i < a; i++) {
					if (temp1->energy > 0) {
						customer* temp3 = current;
						int x =count;
						for (int j = 0; j < x; j++) {
							if (temp3->name == temp1->name) {
								deleteDomain(1, temp1->name);
								break;
							}
							temp3 = temp3->next;
						}
						temp1->prev->next = temp1->next;
						temp1->next->prev = temp1->prev;
						if (temp1 == order) {
							order = order->next;
						}
						temp2 = temp1->next;
						delete temp1;
						countOrder--;
						if (countOrder == 0) break;
						temp1 = temp2;

					} else {
						temp1 = temp1->next;
					}
				}
				a = countQueue;
				temp1 = queue;
				temp2 = queue;
				for (int i = 0; i <a; i++) {
					if (temp1->energy > 0) {
						temp1->prev->next = temp1->next;
						temp1->next->prev = temp1->prev;
						
						temp2 = temp1->next;
						if (temp1 == queue) queue = temp2;
						delete temp1;
						countQueue--;
						if (countOrder == 0) break;
						temp1 = temp2;
					} else {
						temp1 = temp1->next;
					}
				}

				
			} else {
				temp1 = order;
				temp2 = order;
				int a = countOrder;
				order = order->prev;
				for (int i = 0; i < a; i++) {
					if (order->energy < 0) {
						order->print();
					}
					order = order->prev;
				}
				order = order->next;
				
				for (int i = 0; i < a; i++) {
					if (temp1->energy < 0) {
						customer* temp3 = current;
						int x = count;
						for (int j = 0; j < x; j++) {
							if (temp3->name == temp1->name) {
								deleteDomain(-1, temp1->name);
								break;
							}
							temp3 = temp3->next;
						}
						temp1->prev->next = temp1->next;
						temp1->next->prev = temp1->prev;
						if (temp1 == order) {
							order = order->next;
						}
						temp2 = temp1->next;
						delete temp1;
						countOrder--;
						if (temp2 == temp1) break;
						temp1 = temp2;

					} else {
						temp1 = temp1->next;
					}
				}
				
				a = countQueue;
				customer* temp1 = queue;
				customer* temp2 = queue;
				for (int i = 0; i <a; i++) {
					if (temp1->energy < 0) {
						temp1->prev->next = temp1->next;
						temp1->next->prev = temp1->prev;
						
						temp2 = temp1->next;
						if (temp1 == queue) {
							queue = temp1->next;
						} 

						delete temp1;
						countQueue--;
						if (countQueue == 0) break;
						temp1 = temp2;
					} else {
						temp1 = temp1->next;
					}
				}
				
			}
			
			addFromQueue();
			
		}
		void LIGHT(int num)
		{
			//cout<<"light"<<" "<<num<<endl;
			if (num == 0) {
				for (int i = 0; i < countQueue; i++) {
					queue->print();
					queue = queue->next;
				}
			} else if (num > 0) {
				for (int i = 0; i < count; i++) {
					current->print();
					current = current->next;
				}
			} else {
				for (int i = 0; i < count; i++) {
					current->print();
					current = current->prev;
				}
			}
		}
};