#pragma once
#define NULL 0

template<class T>
class SBTNode
{
public:
	int iSize;
	SBTNode<T>* pkLeft;
	SBTNode<T>* pkRight;
	T Item;
};

/*需要Item对<=、>、==、!=四种运算符号,以及=赋值的支持*/
template<class T>
class oSBT
{
public:
	oSBT();
	~oSBT();
	void Insert(const T& Item);
	void Remove(const T& Item);
	T* GetItemAt(int i);
	int GetSize();
	int GetArray(T*& pArray); 
	SBTNode<T>* Search(const T& Item);
	SBTNode<T>* SearchFrom(const T& Item, SBTNode<T>* pkRoot);
	void Clear();
private:
	inline void Rotate_Left(SBTNode<T>*& pkNode);
	inline void Rotate_Right(SBTNode<T>*& pkNode);
	void Insert(const T& Item, SBTNode<T>*& pkRoot);
	void Maintain(SBTNode<T>*& pkRoot, bool bRight);
	void Clear(SBTNode<T>* pkRoot);
	void Remove(const T& Item, SBTNode<T>*& pkRoot);
	void Record(SBTNode<T>* pkRoot, T* pArray, int& iCount);
	SBTNode<T>* m_pkRoot;
	SBTNode<T>* m_pkNULL;
};

template<class T>
void oSBT<T>::Record( SBTNode<T>* pkRoot, T* pArray, int& iCount )
{
	if (pkRoot != m_pkNULL)
	{
		Record(pkRoot->pkLeft, pArray, iCount);
		pArray[iCount] = pkRoot->Item;
		iCount++;
		Record(pkRoot->pkRight, pArray, iCount);
	}
}

template<class T>
int oSBT<T>::GetArray( T*& pArray )
{
	int iSize = GetSize();
	T* pNew = new T[iSize];
	pArray = pNew;
	int iCount = 0;
	Record(m_pkRoot, pArray, iCount);
	return iCount;
}

template<class T>
int oSBT<T>::GetSize()
{
	return m_pkRoot->iSize;
}

template<class T>
oSBT<T>::oSBT()
{
	m_pkNULL = new SBTNode<T>;
	m_pkNULL->iSize = 0;
	m_pkNULL->pkLeft = m_pkNULL;
	m_pkNULL->pkRight = m_pkNULL;
	m_pkRoot = m_pkNULL;
}

template<class T>
oSBT<T>::~oSBT()
{
	Clear();
	m_pkRoot = NULL;
	delete m_pkNULL;
	m_pkNULL = NULL;
}

template<class T>
T* oSBT<T>::GetItemAt(int i)
{
	SBTNode<T>* pkTemp = m_pkRoot;
	for(;;)
	{
		if(pkTemp->pkLeft->iSize > i)
		{
			pkTemp = pkTemp->pkLeft;
		}
		else if(i > pkTemp->pkLeft->iSize)
		{
			i -= (pkTemp->pkLeft->iSize + 1);
			pkTemp = pkTemp->pkRight;
		}
		else break;
	}
	return &(pkTemp->Item);
}

template<class T>
void oSBT<T>::Remove(const T& Item)
{
	Remove(Item, m_pkRoot);
}

template<class T>
void oSBT<T>::Remove(const T& Item, SBTNode<T>*& pkRoot)
{
	if(pkRoot== m_pkNULL)
	{
		return;
	}
	pkRoot->iSize--;
	if(pkRoot->Item == Item)
	{
		SBTNode<T>* pkTemp;
		if(pkRoot->pkLeft != m_pkNULL && pkRoot->pkRight == m_pkNULL)
		{
			pkTemp = pkRoot;
			pkRoot = pkTemp->pkLeft;
			delete pkTemp;
			pkTemp = NULL;
		}
		else if(pkRoot->pkLeft == m_pkNULL && pkRoot->pkRight == m_pkNULL)
		{
			pkTemp = pkRoot;
			pkRoot= m_pkNULL;
			delete pkTemp;
			pkTemp = NULL;
		}
		else
		{
			pkTemp = pkRoot->pkRight; 
			while(pkTemp->pkLeft != m_pkNULL)
			{
				pkTemp = pkTemp->pkLeft;
			}
			pkRoot->Item = pkTemp->Item;
			Remove(pkTemp->Item, pkRoot->pkRight);
		}
	}
	else if (Item < pkRoot->Item)
	{
		Remove(Item, pkRoot->pkLeft);
	}
	else
	{
		Remove(Item, pkRoot->pkRight);
	}
}

template<class T>
SBTNode<T>* oSBT<T>::Search( const T& Item )
{
	return SearchFrom(Item, m_pkRoot);
}

template<class T>
SBTNode<T>* oSBT<T>::SearchFrom( const T& Item, SBTNode<T>* pkRoot )
{
	SBTNode<T>* pkResult = pkRoot;
	while (pkResult != m_pkNULL && Item != pkResult->Item)
	{
		pkResult = Item <= pkResult->Item ? pkResult->pkLeft: pkResult->pkRight;
	}
	return pkResult == m_pkNULL ? NULL: pkResult;
}

template<class T>
void oSBT<T>::Clear()
{
	Clear(m_pkRoot);
}

template<class T>
void oSBT<T>::Clear( SBTNode<T>* pkRoot )
{
	if (pkRoot != m_pkNULL)
	{
		Clear(pkRoot->pkLeft);
		Clear(pkRoot->pkRight);
		delete pkRoot;
		pkRoot = NULL;
	}
}

template<class T>
void oSBT<T>::Insert( const T& Item )
{
	Insert(Item, m_pkRoot);
}

template<class T>
void oSBT<T>::Insert( const T& Item, SBTNode<T>*& pkRoot )
{
	if (m_pkNULL == pkRoot)
	{
		pkRoot = new SBTNode<T>;
		pkRoot->Item = Item;
		pkRoot->iSize = 1;
		pkRoot->pkLeft = m_pkNULL;
		pkRoot->pkRight = m_pkNULL;
	}
	else
	{
		pkRoot->iSize++;
		if (Item <= pkRoot->Item)
		{
			Insert(Item, pkRoot->pkLeft);
		}
		else
		{
			Insert(Item, pkRoot->pkRight);
		}
		Maintain(pkRoot, Item > pkRoot->Item);
	}
}

template<class T>
void oSBT<T>::Maintain( SBTNode<T>*& pkRoot ,bool bRight )
{
	if (!bRight)
	{
		if (pkRoot->pkLeft->pkLeft->iSize > pkRoot->pkRight->iSize)
		{
			Rotate_Right(pkRoot);
		}
		else if (pkRoot->pkLeft->pkRight->iSize > pkRoot->pkRight->iSize)
		{
			Rotate_Left(pkRoot->pkLeft);
			Rotate_Right(pkRoot);
		}
		else return;
	}
	else
	{
		if (pkRoot->pkRight->pkRight->iSize > pkRoot->pkLeft->iSize)
		{
			Rotate_Left(pkRoot);
		}
		else if (pkRoot->pkRight->pkLeft->iSize > pkRoot->pkLeft->iSize)
		{
			Rotate_Right(pkRoot->pkRight);
			Rotate_Left(pkRoot);
		}
		else return;
	}
	Maintain(pkRoot->pkLeft, false);
	Maintain(pkRoot->pkRight, true);
	Maintain(pkRoot, false);
	Maintain(pkRoot, true);
}

template<class T>
void oSBT<T>::Rotate_Right( SBTNode<T>*& pkNode )
{
	SBTNode<T>* pkTemp = pkNode->pkLeft;
	pkNode->pkLeft = pkTemp->pkRight;
	pkTemp->pkRight = pkNode;
	pkTemp->iSize = pkNode->iSize;
	pkNode->iSize = pkNode->pkLeft->iSize + pkNode->pkRight->iSize + 1;
	pkNode = pkTemp;
}

template<class T>
void oSBT<T>::Rotate_Left( SBTNode<T>*& pkNode )
{
	SBTNode<T>* pkTemp = pkNode->pkRight;
	pkNode->pkRight = pkTemp->pkLeft;
	pkTemp->pkLeft = pkNode;
	pkTemp->iSize = pkNode->iSize;
	pkNode->iSize = pkNode->pkLeft->iSize + pkNode->pkRight->iSize + 1;
	pkNode = pkTemp;
}