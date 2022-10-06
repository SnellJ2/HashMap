

template <typename t1, typename t2>
class hashMap
{
public:
	struct hashPair
	{
		t1 key;
		t2 value;
		hashPair * link;
	};

	struct iteratorPair
	{
		t1 * key;
		t2 * value;
		iteratorPair * link;
	};

	class iterator
	{
	public:
		friend class hashMap;

		iterator()
		{
			this->element = NULL;
		}

		const iterator& operator ++(int)
		{
			if(element != NULL)
			{
				this->element = this->element->link;
			}
			return *this;
		}

		bool operator ==( const iterator &rhs) const
		{
			if(this->element == rhs.element)
			{
				return true;
			}
			return false;
		}

		bool operator !=( const hashMap<t1, t2>::iterator &rhs) const
		{
			if(this->element != rhs.element)
			{
				return true;
			}

			return false;
		}

		t1 first()
		{

			return *(this->element->key);
		}

		t2 second()
		{
			return *(this->element->value);
		}

	private:

		iterator(iteratorPair * p)
		{
			this->element = p;
		}

		iteratorPair * element;
	};
	
	hashMap ()
	{
		size = 5;
		head = NULL;
		items = 0;
		table =  new hashPair*[size];
		for (int i = 0; i < size; i++)
		{
			*(table + i) = NULL;
		}
	}

	~hashMap ()
	{
		hashPair * current;
		hashPair * next;
		for(int i = 0; i < size; i++)
		{
			current = table[i];
			while(current!= NULL)
			{
				next = current->link;
				delete current;
				current = next;
			}
		}
		delete table;
	}

	t2& operator [](t1 key)
	{


		int loop = 1;
		float itemsTest = items;
		float itemsSize = size;
		float amount = itemsTest/itemsSize;
		if(amount > .5)
		{
			this->resize();

		}

		int x = h(key);

		int tracker = 0;
		while(true)
		{
			loop = 1;


			hashPair * nextNode = table[x];

			tracker = 0;
			if(nextNode != NULL)
			{
				while(loop == 1)
				{
					if(nextNode->key == key)
					{
						return nextNode->value;
					}
					if(nextNode->link == NULL)
					{
						loop = 0;
					}
					else
					{
						nextNode = nextNode->link;
					}

					tracker++;
				}
			}
			else
			{

				hashPair *node;
				node = new hashPair; 
				node->key = key;
				node->value = t2();
				iteratorPair *node3;
				node3 = new iteratorPair;
				
				node3->key = &(node->key);
				node3->value = &(node->value); 
				node3->link = NULL;

				if(head != NULL)
				{
					node3->link = head;
				}
				head = node3;
				table[x] = node;

				return table[x]->value;
			}

			if(tracker < 2)
			{
				loop = 1;
				hashPair *node1;
				
				iteratorPair*node2;
				node2 = new iteratorPair;
				node1 = new hashPair;
				table[x]->link = node1;
				node1->key = key;
				node1->value = t2();
 				
				node2->key = &(node1->key);
				node2->value = &(node1->value); 
				node2->link = NULL;


				if(head != NULL)
				{
					node2->link = head;
				}
				head = node2;
				
				tracker++;
				if(tracker == 2)
				{
					items++;
				}

				return node1->value;
			}
			else
			{
				x = (x + 1) % size;

			}
		}
	}

	iterator begin () const
	{
		return iterator(head);
	}

	iterator end() const
	{
		
		return iterator(NULL); 
	}

private:

	void resize ()
	{
		std::vector<std::string> keys;
		std::vector<int> values;

		hashPair ** oldTable;

		oldTable = table;

		size = size*2;
		items = 0;

		hashMap<std::string, int>::iterator it1;
		it1 = this->begin();
		while(it1 != this->end())
		{
			keys.push_back(it1.first());
			values.push_back(it1.second());

			it1++;
		}
		head = NULL;

		table =  new hashPair*[size];

		for (int i = 0; i < size; i++)
		{
			*(table + i) = NULL;
		}
		for(int i = 0; i < keys.size(); i++)
		{

			(*this)[keys[i]] = values[i];
		}
		delete oldTable;
	}

	int h(std::string key) const
	{
		int sum = 0;

		for (int i = 0; i < key.length(); i++)
		{
			sum += (int)(key[i]);

		}
		sum = sum%size;
		return sum;
	}
	int items;
	int size;
	hashPair ** table;
	iteratorPair * head;
};