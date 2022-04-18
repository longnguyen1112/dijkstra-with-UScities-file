#pragma once
#include <string>

template <typename T>
struct Node {
	Node<T>* next = NULL;
	std::string key;
	T value;
};

template <typename Q>
class AArray
{
private:
	Node<Q>** AA;
	int arrSize;
	int elementCount;
	Node<Q>* Ptr;
	Node<Q>* findPtr;
	bool* primeArr;
	void initPrimeArr();
	void rehash();
	int getHash(std::string&, int);
	//void addKeyVal(Node<Q>, std::string, Q);
	const int MAX_SIZE = 10000000;
public:
	AArray();
	AArray(int);
	~AArray();
	Q& operator [] (std::string);
	bool remove(std::string);
	bool find(std::string);
	bool first();
	bool next();
	std::string keyvalue();
	Q datavalue();
};

template <typename Q>
AArray<Q> ::AArray()
{
	arrSize = 11;
	elementCount = 0;
	primeArr = NULL;
	initPrimeArr();
	AA = new Node<Q>*[arrSize];
	for (int i = 0; i < arrSize; i++)
	{
		AA[i] = NULL;
	}

}

template <typename Q>
AArray<Q> ::AArray(int sizearray)
{
	arrSize = sizearray;
	elementCount = 0;
	primeArr = NULL;
	initPrimeArr();
	AA = new Node<Q>*[arrSize];
	for (int i = 0; i < arrSize; i++)
	{
		AA[i] = NULL;
	}

}

template <typename Q>
AArray<Q> :: ~AArray()
{
	delete AA;
	delete Ptr;
}

template <typename Q>
Q& AArray<Q> :: operator [] (std::string key)
{
	if (elementCount * 2 >= arrSize)
	{
		rehash();
	}
	int hash = getHash(key, arrSize);
	Node<Q>* temp = AA[hash];
	while (temp)
	{
		if (temp->key == key)
		{
			return temp->value;
		}
		temp = temp->next;
	}
	Node<Q>* newnode = new Node<Q>;
	newnode->key = key;
	temp = AA[hash];
	AA[hash] = newnode;
	newnode->next = temp;
	elementCount++;
	return newnode->value;
}

template <typename Q>
void AArray<Q> ::initPrimeArr()
{
	unsigned int boolcount = arrSize + MAX_SIZE;
	if (primeArr != NULL)
	{
		delete primeArr;
	}
	primeArr = new bool[boolcount];
	for (unsigned int x = 2; x < boolcount; x++)
	{
		primeArr[x] = true;
	}
	/*int curIdx;*/
	unsigned int loc = 2;
	while (loc < boolcount / 2)
	{
		//curIdx = loc;
		while (!primeArr[loc])
		{
			loc++;
		}
		for (unsigned int x = loc * 2; x < boolcount; x += loc)
		{
			primeArr[x] = false;
		}
		loc++;
	}
}

template <typename Q>
void AArray<Q> ::rehash()
{
	Node<Q>* Trav = NULL;
	int newsize = NULL;
	int curLoc = arrSize * 2;
	bool found = false;
	while (found == false)
	{
		if (primeArr[curLoc])
		{
			found = true;
			newsize = curLoc;
		}
		curLoc++;
	}
	Node<Q>** longArr = new Node<Q>*[newsize];
	for (int i = 0; i < newsize; i++)
	{
		longArr[i] = NULL;
	}
	for (int i = 0; i < arrSize; i++)
	{
		Trav = AA[i];
		while (Trav)
		{
			int newhash = getHash(Trav->key, newsize);
			Node<Q>* temp = longArr[newhash];
			if (temp)
			{
				while (temp->next)
				{
					temp = temp->next;
				}
				temp->next = new Node<Q>;
				temp->next->key = Trav->key;
				temp->next->value = Trav->value;
			}
			else
			{
				longArr[newhash] = new Node<Q>;
				longArr[newhash]->key = Trav->key;
				longArr[newhash]->value = Trav->value;
			}
			Trav = Trav->next;
		}
	}
	arrSize = newsize;
	Node<Q>** temp = AA;
	AA = longArr;
	delete temp;
	delete Trav;
	Ptr = NULL;
}

//template <typename Q>
//void rehash() {
//	unsigned int newSize = getNewSize();
//	Node<Q>** temp = new Node<Q> *[newSize];
//	for (unsigned int i = 0; i < newSize; i++)
//		temp[i] = NULL;
//
//	for (unsigned int i = 0; i < arraySize; i++) {
//		Node<Q>* current = AArray[i];
//		while (current) {
//
//			int newHash = gethash(current->key, newSize);
//
//			Node<Q>* nextNode = current->Next;
//			addCurrentValue(temp[newHash], current);
//			current = nextNode;
//		}
//	}
//	arraySize = newSize;
//	delete[] AArray;
//	AArray = temp;
//}

template <typename Q>
int AArray<Q> ::getHash(std::string& key, int size)
{
	long long int hashVal = 0;
	for (unsigned int i = 0; i < key.length(); i++)
	{
		hashVal = hashVal * 10 + key[i];
	}
	return hashVal % size;
}

template <typename Q>
bool AArray<Q> ::first()
{
	for (int i = 0; i < arrSize; i++)
	{
		if (AA[i])
		{
			Ptr = AA[i];
			return true;
		}
	}
	return false;
}

template <typename Q>
bool AArray<Q> ::next()
{
	if (Ptr->next)
	{
		Ptr = Ptr->next;
		return true;
	}
	int nextidx = getHash(Ptr->key, arrSize) + 1;
	for (int i = nextidx; i < arrSize; i++)
	{
		if (AA[i])
		{
			Ptr = AA[i];
			return true;
		}
	}
	return false;
}

template <typename Q>
bool AArray<Q> ::find(std::string key)
{
	int hashofFind = getHash(key, arrSize);
	if (!AA[hashofFind])
	{
		return false;
	}
	else
	{
		int found = false;
		findPtr = AA[hashofFind];
		while (!found)
		{
			if (findPtr->key == key)
			{
				found = true;
			}
			else
			{
				findPtr = findPtr->next;
			}
		}
	}
}

template <typename Q>
bool AArray<Q> ::remove(std::string key)
{
	if (!find(key))
	{
		return false;
	}
	else
	{
		for (int i = 0; i < arrSize; i++)
		{
			if (AA[i])
			{
				if (findPtr->key == AA[i]->key)
				{
					AA[i] = findPtr->next;
					delete findPtr;
					return true;
				}
				else
				{
					Node<Q>* prev = NULL;
					int removeHash = getHash(findPtr->key, arrSize);
					while (AA[removeHash]->next->key != findPtr->key)
					{
						AA[removeHash] = AA[removeHash]->next;
					}
					prev = AA[removeHash];
					prev->next = findPtr->next;
					delete findPtr;
					return true;
				}
			}
		}
	}
	Ptr = NULL;
}

template <typename Q>
std::string AArray<Q> ::keyvalue()
{
	if (Ptr)
	{
		return Ptr->key;
	}
}

template <typename Q>
Q AArray<Q> ::datavalue()
{
	if (Ptr)
	{
		return Ptr->value;
	}
}
